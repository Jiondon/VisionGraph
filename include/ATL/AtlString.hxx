//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef ATL_STRING_HXX
#define ATL_STRING_HXX

#include "Utils.h"
#include "Error.h"
#include "AtlMemory.h"
#include <memory.h>
#include <cwctype>

namespace atl
{
	namespace StringInternal
	{
		template< int Size > struct WCharTBaseTypeHelper;

		template<> struct WCharTBaseTypeHelper<1>
		{
			typedef char Type;
		};

		template<> struct WCharTBaseTypeHelper<2>
		{
			typedef wchar16 Type;
		};

		template<> struct WCharTBaseTypeHelper<4>
		{
			typedef wchar32 Type;
		};

		typedef WCharTBaseTypeHelper<sizeof(wchar_t)>::Type WCharTBaseType;


		inline signed char ValidHexDigit( atl::wchar16 c )
		{
			if ( c >= '0' && c <= '9' )
				return (char)(c - 48);
			if ( 'A' <= c && c <= 'F' )
				return (char)(c - 'A' + 10);
			if ( 'a' <= c && c <= 'f' )
				return (char)(c - 'a' + 10);
			return (char)-1;
		}

	} // namespace StringInternal


	inline void String::wstrcpy( wchar16* dst, const wchar16* src, const int size )
	{
		memcpy( dst, src, sizeof(wchar16) * size );
		dst[size] = 0;
	}


	//
	// UTF16
	//
	inline int String::wstrsize( const wchar16* s )
	{
		int l = 0;
		while( *( s++ ) != 0 ) ++l;
		return l;
	}


	inline sint32 String::wstrcmp( const wchar16* s1, const wchar16* s2 )
	{
		while( *s1 != 0 && *s2 != 0 )
		{
			sint32 d = (sint32)*(s1++) - (sint32)*(s2++);
			if ( d != 0 ) return d;
		}

		return (sint32)*s1 - (sint32)*s2;
	}


	inline sint32 String::wstrcmp( const wchar16* s1, const wchar32* s2 )
	{
		return wstrcmp( s1, atl::String(s2).Ptr() );
	}


	inline sint32 String::wstrncmp( const wchar16* s1, const wchar16* s2, int n )
	{
		while( *s1 != 0 && *s2 != 0 && n-- !=0 )
		{
			sint32 d = (sint32)*(s1++) - (sint32)*(s2++);
			if ( d != 0 ) return d;
		}

		if ( n == 0 )
			return 0;

		return (sint32)*s1 - (sint32)*s2;
	}


	inline wchar16* String::wstrnchr( const wchar16* str, wchar16 c, int n )
	{
		while( *str != 0 && n-- != 0 )
		{
			if ( *str == c ) return const_cast<wchar16*>( str );
			++str;
		}

		return 0;
	}


	inline int String::utf8Len ( wchar32 codepoint )
	{
		static const wchar32 utf8LenThreshold[utf8MaxLen] = { 0x7F, 0x7FF, 0xFFFF, 0x1FFFFF, 0x3FFFFFF, 0x7FFFFFFF };

		if ( codepoint <= utf8LenThreshold[0] ) return 1;
		else if ( codepoint <= utf8LenThreshold[1] ) return 2;
		else if ( codepoint <= utf8LenThreshold[2] ) return 3;
		else if ( codepoint <= utf8LenThreshold[3] ) return 4;
		else if ( codepoint <= utf8LenThreshold[4] ) return 5;
		else if ( codepoint <= utf8LenThreshold[5] ) return 6;
		else return -1;
	}


	//
	// UTF16 -> UTF32 ( http://unicode.org/faq/utf_bom.html#utf16-4 )
	//
	inline void String::UTF16SurrogatesToUTF32( wchar32& c, const wchar16 hi, const wchar16 lo )
	{
		c = (hi << 10) + lo + utf32SurrogateOffset;
	}


	//
	// UTF32 -> UTF16 ( http://unicode.org/faq/utf_bom.html#utf16-4 )
	//
	inline void String::UTF32ToUTF16Surrogates( const wchar32 c, wchar16& hi, wchar16& lo )
	{
		if ( c > utf32Max )
		{
			throw atl::RuntimeError( "Incorrect code point in UTF32" );
		}

		hi = (wchar16)utf32LeadOffset + (wchar16)( c >> 10 );
		lo = 0xDC00 + ( c & 0x3FF );
	}


	inline int String::UTF32ToUTF16Impl( wchar16* dst, bool writeOutput , const wchar32* src )
	{
		int l = 0;
		while ( *src != 0 )
		{
			if ( *src <= (wchar32) utf16SingleUnitMax )
			{
				l++;
				if ( writeOutput )
				{
					*dst++ = (wchar16)*src;
				}
			}
			else
			{
				l += 2;
				if ( writeOutput )
				{
					wchar16 hi, low;
					UTF32ToUTF16Surrogates( *src, hi, low );
					*dst++ = hi;
					*dst++ = low;
				}
			}
			++src;
		}

		if ( writeOutput )
		{
			*dst++ = 0;
		}

		return l;
	}


	inline int String::UTF32ToUTF16Length( const wchar32* src )
	{
		return UTF32ToUTF16Impl( 0, false, src );
	}


	inline int String::UTF32ToUTF16( wchar16* dst, const wchar32* src )
	{
		return UTF32ToUTF16Impl( dst, true, src );
	}


	//
	// UTF16 -> UTF8
	//
	inline int String::UTF16ToUTF8Impl( wchar8* dst, bool writeOutput, const wchar16* src )
	{
		static const wchar8 utf8LengthToHeader[utf8MaxLen] = { 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC};

		int l = 0;

		while( *src != 0 )
		{
			wchar32 codepoint = 0;
			if ( *src < 0xD800 || *src > 0xDFFF )
			{
				codepoint = *(src++);
			}
			else
			{
				wchar16 hi = *(src++);
				wchar16 lo = *(src++);
				UTF16SurrogatesToUTF32(codepoint, hi, lo);
			}

			int len = utf8Len( codepoint );
			if ( len > 0 )
			{
				l += len;
			}
			else
			{
				return NPos;
			}

			if( writeOutput )
			{
				const wchar32 mask = 0xBF;
				const wchar32 mark = 0x80;
				dst += len;
				switch (len)
				{
					case 6:	*--dst = ( codepoint | mark ) & mask; codepoint >>= 6;
					case 5:	*--dst = ( codepoint | mark ) & mask; codepoint >>= 6;
					case 4:	*--dst = ( codepoint | mark ) & mask; codepoint >>= 6;
					case 3:	*--dst = ( codepoint | mark ) & mask; codepoint >>= 6;
					case 2:	*--dst = ( codepoint | mark ) & mask; codepoint >>= 6;
					case 1:	*--dst =  (wchar8) (codepoint | utf8LengthToHeader[ len-1 ]);
				};
				dst += len;
			}
		}
		if ( writeOutput )
		{
			*dst++ = 0;
		}
		return l;
	}

	inline int String::UTF16ToUTF8Length( const wchar16* s )
	{
		return UTF16ToUTF8Impl( 0, false, s );
	}

	inline int String::UTF16ToUTF8( wchar8* dst, const wchar16* src )
	{
		return UTF16ToUTF8Impl( dst, true, src );
	}


	//
	// UTF8 -> UTF16
	//
	inline int String::UTF8ToUTF16Impl( wchar16* dst, const wchar8* src, const wchar8* srcEnd )
	{
		static const int utf8HeaderToLength[256] =
		{
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
			2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,4,4,4,4,5,5,0,0
		};

		static const wchar32 utf8Offset[utf8MaxLen] = { 0x00000000, 0x00003080, 0x000E2080, 0x03C82080, 0xFA082080, 0x82082080 };
		static const int utf8MinValue[utf8MaxLen] = { 1, 0x0080, 0x0800, 0x10000, 0x200000, 0x4000000 };

		int l = 0;
		while( src < srcEnd )
		{
			wchar32 codepoint = static_cast<wchar32>(*(src++));

			if (codepoint & 0x80)
			{
				int len				= utf8HeaderToLength[codepoint];
				wchar32 offset		= utf8Offset[len];
				wchar32 minValue	= utf8MinValue[len];

				if (len == 0 || src + len > srcEnd)
					return -1;

				while(len--)
				{
					wchar8 c = *(src++);
					if ((c & 0xC0) != 0x80)
						return -1;

					codepoint = (codepoint << 6) + static_cast<wchar32>(c);
				}

				codepoint -= offset;

				if (codepoint < minValue)
					return -1;
			}
			else if (codepoint == 0)
			{
				return -1;
			}

			if ( codepoint <= utf16SingleUnitMax )
			{
				if ( dst )
					dst[l] = (wchar16)codepoint;

				l += 1;
			}
			else if ( codepoint <= utf32Max )
			{
				if ( dst )
					UTF32ToUTF16Surrogates( codepoint, dst[l], dst[l + 1] );

				l += 2;
			}
			else
			{
				return -1;
			}
		}

		if ( dst )
			dst[l] = 0;

		return l;
	}


	inline int String::UTF8ToUTF16Length( const wchar8* src, const wchar8* srcEnd )
	{
		return UTF8ToUTF16Impl(0, src, srcEnd);
	}


	inline int String::UTF8ToUTF16( wchar16* dst, const wchar8* src, const wchar8* srcEnd )
	{
		return UTF8ToUTF16Impl(dst, src, srcEnd);
	}


	inline void String::Init( void )
	{
		size = 0;
		data.stackbuf[size] = 0;
		uses_heap_buffer = false;
		capacity = smallSizeString;
		tempCStr8 = 0;
	}


	inline bool String::ShouldUseDynamicBuffer( int _size )
	{
		return _size > smallSizeString;
	}


	inline void String::AssignHeapBuffer( wchar16 *buf, int newCapacity )
	{
		data.heapbuf = buf;
		uses_heap_buffer = true;
		capacity = newCapacity;
	}


	inline void String::InvalidateTempCStr8Buffer( void )
	{
		AtlFree(tempCStr8);
		tempCStr8 = 0;
	}


	inline wchar16* String::Alloc( int _capacity )
	{
		wchar16* ptr = (wchar16*)AtlAlloc( ((std::size_t)_capacity + 1) * sizeof(wchar16) );
		if (!ptr)
			throw atl::RuntimeError( "String buffer allocation error." );

		return ptr;
	}


	inline void String::DisposeData( void )
	{
		if (uses_heap_buffer)
		{
			AtlFree(data.heapbuf);
			uses_heap_buffer = false;
			capacity = smallSizeString;
		}
	}


	inline String::String()
	{
		Init();
	}


	inline String::String( const String& str )
	{
		Init();
		Append( str );
	}


	inline String::String( const wchar32* str )
	{
		Init();
		Append( str );
	}


	inline String::String( const wchar16* str )
	{
		Init();
		Append( str );
	}


	inline String::String( const char* str )
	{
		Init();
		Append( str );
	}


	inline String::String( const wchar_t* str )
	{
		Init();
		Append( str );
	}


	inline String::String( int n, wchar16 c )
	{
		Init();
		Resize( n, c );
	}


	inline String::String( int n, char c )
	{
		Init();
		Resize( n, (wchar16)c );
	}


	inline String::String( int n, wchar_t c )
	{
		Init();
		Resize( n, c );
	}


	inline String::~String()
	{
		DisposeData();
		InvalidateTempCStr8Buffer();
	}


	inline int String::Compare( const String& str ) const
	{
		return wstrcmp( Ptr(), str.Ptr() );
	}


	inline void String::Swap( String& str )
	{
		if (uses_heap_buffer && str.uses_heap_buffer)
		{
			std::swap( data.heapbuf, str.data.heapbuf );
			std::swap( size, str.size );
			std::swap( capacity, str.capacity );
			std::swap( tempCStr8, str.tempCStr8 );
		}
		else
		{
			// this needs optimization
			String temp(*this);
			Assign(str);
			str.Assign(temp);
		}
	}


	inline wchar16& String::At( int index )
	{
		if ( index < 0 || index >= size )
		{
			throw atl::RuntimeError("Index out of bounds in String::At.");
		}

		return Ptr()[index];
	}


	inline const wchar16& String::At( int index ) const
	{
		if ( index < 0 || index >= size )
		{
			throw atl::RuntimeError("Index out of bounds in String::At.");
		}

		return Ptr()[index];
	}


	// Reserve place for at least newCapacity characters. ( at least newCapacity + 1 cells )
	inline void String::Reserve( int newCapacity )
	{
		if (!ShouldUseDynamicBuffer(newCapacity))
			return;
			
		if ( newCapacity > capacity )
		{
			newCapacity = (newCapacity > capacity + capacity / 2) ? newCapacity : capacity + capacity / 2;
			wchar16* temp = Alloc(newCapacity);
			if ( size > 0 )
			{
				wstrcpy(temp, Ptr(), size);
			}
			else
			{
				temp[0] = 0;
			}

			DisposeData();
			AssignHeapBuffer(temp, newCapacity);
		}
	}


	inline void String::Clear( void )
	{
		size = 0;
		Ptr()[0] = 0;
		InvalidateTempCStr8Buffer();
	}


	inline void String::PushBack( wchar32 c )
	{
		Append(c);
	}


	inline void String::PushBack( wchar16 c )
	{
		Append(c);
	}


	inline void String::PushBack( char c )
	{
		Append(c);
	}


	inline void String::PushBack( wchar_t c )
	{
		Append(c);
	}


	inline void String::Resize( int n, wchar32 c )
	{
		if (n < 0)
			throw atl::RuntimeError("atl::String Resize: Size can't be negative.");

		if ( c <= (wchar32)utf16SingleUnitMax )
		{
			Resize(n, (wchar16)c);
		}
		else
		{
			if ( n > size )
			{
				Reserve(n);
				n &= ~1;

				wchar16 hi, low;
				UTF32ToUTF16Surrogates( c, hi, low );

				wchar16* ptr = Ptr();
				for ( int i = size; i < n; i += 2 )
				{
					ptr[i] = hi;
					ptr[i + 1] = low;
				}
			}

			size = n;
			Ptr()[n] = 0;
			InvalidateTempCStr8Buffer();
		}
	}


	inline void String::Resize( int n, wchar16 c )
	{
		if (n < 0)
			throw atl::RuntimeError("atl::String Resize: Size can't be negative.");

		if ( n > size )
		{
			Reserve(n);

			wchar16* ptr = Ptr();
			for ( int i = size; i < n; ++i )
				ptr[i] = c;
		}

		size = n;
		Ptr()[n] = 0;
		InvalidateTempCStr8Buffer();
	}


	inline void String::Resize( int n, char c )
	{
		Resize( n, (wchar16)c );
	}


	inline void String::Resize( int n, wchar_t c )
	{
		Resize( n, (StringInternal::WCharTBaseType)c );
	}


	inline int String::Copy( wchar16* buff, int n, int Pos ) const
	{
		if (Pos < 0)
			throw atl::RuntimeError("atl::String Copy: Position can't be negative.");

		const wchar16* ptr = Ptr();
		int l = 0;
		for ( l = 0; Pos + l < size && l < n; ++l )
		{
			buff[l] = ptr[ Pos + l ];
		}

		return l;
	}


	inline String& String::Erase( int pos, int n )
	{
		if ( pos < 0 || pos >= size )
			throw atl::RuntimeError( "Index out of bounds in String::Erase." );

		if ( n == NPos )
		{
			n = size - pos;
		}

		wchar16* ptr = Ptr();
		for ( int i = pos; i + n < size; ++i )
			ptr[i] = ptr[i + n];

		size -= ( n < size-pos ) ? n : size-pos;
		ptr[size] = 0;

		InvalidateTempCStr8Buffer();
		return *this;
	}


	inline String& String::Assign( const String& str )
	{
		if ( &str == this )
		{
			return *this;
		}
		else
		{
			Clear();
			return Append( str );
		}
	}


	inline String& String::Assign( const wchar32* str )
	{
		Clear();
		return Append( str );
	}


	inline String& String::Assign( const wchar16* str )
	{
		if (str >= Ptr() && str <= Ptr() + size)
			return Assign( String(str) );

		Clear();
		return Append( str );
	}


	inline String& String::Assign( const char* str )
	{
		Clear();
		return Append( str );
	}


	inline String& String::Assign( const char* strBegin, const char* strEnd )
	{
		Clear();
		return Append( strBegin, strEnd );
	}


	inline String& String::Assign( const wchar_t* str )
	{
		return Assign( (const StringInternal::WCharTBaseType*)str );
	}


	inline String& String::Assign( wchar32 c )
	{
		Clear();
		return Append( c );
	}


	inline String& String::Assign( wchar16 c )
	{
		Clear();
		return Append( c );
	}


	inline String& String::Assign( char c )
	{
		Clear();
		return Append( c );
	}


	inline String& String::Assign( wchar_t c )
	{
		Clear();
		return Append( c );
	}


	inline String& String::Append( const String& rhs )
	{
		if ( !rhs.Ptr() )
			throw atl::RuntimeError( "Null string passed as argument in String::Append( const String& )" );

		Reserve( size + rhs.size );
		wstrcpy( Ptr() + size, rhs.Ptr(), rhs.size );
		size += rhs.size;

		InvalidateTempCStr8Buffer();
		return *this;
	}


	inline String& String::Append( const wchar32* str )
	{
		if ( !str )
			throw atl::RuntimeError( "NULL pointer passed as argument in String::Append( const wchar16* )" );

		int l = UTF32ToUTF16Length( (const wchar32*)str );
		if ( l < 0 )
			throw atl::RuntimeError( "Not valid Unicode string in String::Append( const wchar_t* )" );

		Reserve( size + l );
		UTF32ToUTF16( Ptr() + size, str );
		size += l;

		InvalidateTempCStr8Buffer();
		return *this;
	}


	inline String& String::Append( const wchar16* str )
	{
		if ( !str )
			throw atl::RuntimeError( "NULL pointer passed as argument in String::Append( const wchar16* )" );

		if (str >= Ptr() && str <= Ptr() + size)
			return Append( String(str) );

		int len = wstrsize( str );
		Reserve( size + len );
		wstrcpy( Ptr() + size, str, len );
		size += len;

		InvalidateTempCStr8Buffer();
		return *this;
	}


	inline String& String::Append( const char* str )
	{
		if ( !str )
			throw atl::RuntimeError( "NULL pointer passed as argument in String::Append( const char* )" );

		const char* strEnd = str;
		while(0 != *strEnd)
			++strEnd;

		Append(str, strEnd);
		return *this;
	}


	inline String& String::Append( const char* strBegin, const char* strEnd )
	{
		if ( !strBegin || !strEnd )
			throw atl::RuntimeError( "NULL pointer passed as argument in String::Append" );

		if (strBegin > strEnd)
			throw atl::RuntimeError( "Invalid pointers range passed as arguments in String::Append" );

		int l = UTF8ToUTF16Length(reinterpret_cast<const wchar8*>(strBegin), reinterpret_cast<const wchar8*>(strEnd));
		if ( l < 0 )
			throw atl::RuntimeError( "Not valid Unicode UTF-8 string in String::Append");

		Reserve( size + l );
		UTF8ToUTF16(Ptr() + size, reinterpret_cast<const wchar8*>(strBegin), reinterpret_cast<const wchar8*>(strEnd));
		size += l;

		InvalidateTempCStr8Buffer();
		return *this;
	}


	inline String& String::Append( const wchar_t* str )
	{
		return Append( (const StringInternal::WCharTBaseType*)str );
	}


	inline String& String::Append( wchar32 c )
	{
		if ( c <= (wchar32)utf16SingleUnitMax )
		{
			return Append( (wchar16)c );
		}
		else
		{
			wchar16 hi, low;
			UTF32ToUTF16Surrogates( c, hi, low );
			Append(hi);
			return Append(low);
		}
	}


	inline String& String::Append( wchar16 c )
	{
		Reserve( size + 1 );
		Ptr()[size++] = c;
		Ptr()[size] = 0;

		InvalidateTempCStr8Buffer();
		return *this;
	}


	inline String& String::Append( char c )
	{
		return Append( (wchar16)c );
	}


	inline String& String::Append( wchar_t c )
	{
		return Append( (StringInternal::WCharTBaseType)c );
	}


	inline String& String::Insert ( int pos1, const String& str, int pos2, int n )
	{
		if (n < 0)
			throw atl::RuntimeError("Invalid size value in String::Insert.");

		if ( pos2 < 0 || pos2 > str.size  || pos1 < 0 || pos1 > size )
			throw atl::RuntimeError("Index out of bounds in String::Insert.");

		const int count = ( n < str.Size() - pos2 ) ? n : str.Size() - pos2;
		const int newCapacity = ( Capacity() > size + count ) ? Capacity() : size + count;

		wchar16 buf[smallSizeString+1];
		wchar16 *next = buf;
		if (ShouldUseDynamicBuffer(newCapacity))
			next = Alloc(newCapacity);

		for ( int i = 0; i < pos1; ++i ) next[i] = Ptr()[i];
		for ( int i = 0; i < count; ++i ) next[ pos1 + i ] = str[ pos2 + i ];
		for ( int i = pos1; i < Size(); ++i ) next[ count + i ] = Ptr()[ i ];
		next[ count + Size() ] = 0;

		DisposeData();

		if (ShouldUseDynamicBuffer(newCapacity))
			AssignHeapBuffer(next, newCapacity);
		else
			wstrcpy(data.stackbuf, next, newCapacity);

		size = size + count;

		InvalidateTempCStr8Buffer();
		return *this;
	}


	inline String& String::Insert ( int pos1, const String& str )
	{
		return Insert( pos1, str, 0, str.size );
	}


	inline String& String::Insert ( int pos1, const char* s, int n)
	{
		return Insert( pos1, String(s), 0, n );
	}


	inline String& String::Insert ( int pos1, const char* s )
	{
		return Insert( pos1, String(s) );
	}


	inline String& String::Insert ( int pos1, int n, char c )
	{
		String temp;
		temp.Resize( n, (wchar16)c );
		return Insert( pos1, temp );
	}


	inline String& String::Insert ( int pos1, const wchar_t* s, int n)
	{
		return Insert( pos1, String(s), 0, n );
	}


	inline String& String::Insert ( int pos1, const wchar_t* s )
	{
		return Insert( pos1, String(s) );
	}


	inline String& String::Insert ( int pos1, int n, wchar_t c )
	{
		String temp;
		temp.Resize( n, c );
		return Insert( pos1, temp );
	}


	inline String& String::Unescape()
	{
		int j = 0;
		int i;
		signed char c1, c2;
		wchar16 *str = Ptr();
		for(i=0; i<size-1; ++i)
		{
			if (str[i] == '\\')
			{
				switch(str[++i])
				{
				case '\'':
					str[j++] = '\''; break;
				case '"':
					str[j++] = '\"'; break;
				case '?':
					str[j++] = '\?'; break;
				case '0':
					str[j++] = '\0'; break;
				case 'a':
					str[j++] = '\a'; break;
				case 'b':
					str[j++] = '\b'; break;
				case 'f':
					str[j++] = '\f'; break;
				case 'v':
					str[j++] = '\v'; break;
				case 'n':
					str[j++] = '\n'; break;
				case 'r':
					str[j++] = '\r'; break;
				case 't':
					str[j++] = '\t'; break;
				case 'x':
					if ( i >= size - 2 )
					{
						str[j++] = str[i];
						break;
					}
					c1 = StringInternal::ValidHexDigit(str[i + 1]);
					c2 = StringInternal::ValidHexDigit(str[i + 2]);

					if ( c1 < 0 || c2 < 0 )
					{
						str[j++] = str[i];
						break;
					}

					str[j++] = (wchar16)c1 * 16 + c2;
					i += 2;
					break;

				default:
					str[j++] = str[i];
				}
			}
			else
			{
				str[j++] = str[i];
			}
		}

		if (i<size) str[j++] = str[i]; // last wasn't part of escape seq
		Resize(j, ' ');
		return *this;
	}


	inline String& String::Escape()
	{
		int numSpecial = 0;
		int i;
		wchar16 *str = Ptr();
		for(i=0; i<size; ++i)
		{
			switch(str[i])
			{
			case '\\':
			case '\r':
			case '\t':
			case '\n':
			case '"':
				++numSpecial; break;
			default:
				;
			}
		}

		if ( !numSpecial )
			return *this;

		i = size-1;
		Resize(size+numSpecial);
		str = Ptr();
		int j = i + numSpecial;
		while ( numSpecial )
		{
			switch(str[i])
			{
			case '\\':
				str[j--] = '\\';
				str[j--] = '\\';
				--numSpecial; break;
			case '\r':
				str[j--] = 'r';
				str[j--] = '\\';
				--numSpecial; break;
			case '\t':
				str[j--] = 't';
				str[j--] = '\\';
				--numSpecial; break;
			case '\n':
				str[j--] = 'n';
				str[j--] = '\\';
				--numSpecial; break;
			case '"':
				str[j--] = '"';
				str[j--] = '\\';
				--numSpecial; break;
			default:
				str[j--] = str[i];
			}
			--i;
		}

		return *this;
	}


	inline wchar16& String::operator[]( int index )
	{
#ifdef _DEBUG
		if (index < 0 || index > (int)size)
			throw atl::RuntimeError("atl::String operator[]: Index out of range.");
#endif
		return Ptr()[index];
	}


	inline const wchar16& String::operator[]( int index ) const
	{
#ifdef _DEBUG
		if (index < 0 || index > (int)size)
			throw atl::RuntimeError("atl::String operator[]: Index out of range.");
#endif
		return Ptr()[index];
	}


	inline bool String::operator== ( const String& str ) const
	{
		return wstrcmp( Ptr(), str.Ptr() ) == 0;
	}


	inline bool String::operator== ( const wchar_t* str ) const
	{
		return wstrcmp( Ptr(), (const StringInternal::WCharTBaseType*)str ) == 0;
	}


	inline bool String::operator< ( const String& str ) const
	{
		return wstrcmp( Ptr(), str.Ptr() ) < 0;
	}


	inline bool String::operator< ( const wchar_t* str ) const
	{
		return wstrcmp( Ptr(), (const StringInternal::WCharTBaseType*)str ) < 0;
	}


	inline bool String::operator<= ( const String& str ) const
	{
		return wstrcmp( Ptr(), str.Ptr() ) <= 0;
	}


	inline bool String::operator<= ( const wchar_t* str ) const
	{
		return wstrcmp( Ptr(), (const StringInternal::WCharTBaseType*)str ) <= 0;
	}


	inline bool String::operator> ( const String& str ) const
	{
		return wstrcmp( Ptr(), str.Ptr() ) > 0;
	}


	inline bool String::operator> ( const wchar_t* str ) const
	{
		return wstrcmp( Ptr(), (const StringInternal::WCharTBaseType*)str ) > 0;
	}


	inline bool String::operator>= ( const String& str ) const
	{
		return wstrcmp( Ptr(), str.Ptr() ) >= 0;
	}


	inline bool String::operator>= ( const wchar_t* str ) const
	{
		return wstrcmp( Ptr(), (const StringInternal::WCharTBaseType*)str ) >= 0;
	}


	inline bool String::operator!= ( const String& str ) const
	{
		return wstrcmp( Ptr(), str.Ptr() ) != 0;
	}


	inline bool String::operator!= ( const wchar_t* str ) const
	{
		return wstrcmp( Ptr(), (const StringInternal::WCharTBaseType*)str ) != 0;
	}

	inline String& String::operator+= ( const String& rhs )
	{
		return Append(rhs);
	}


	inline String& String::operator+= ( wchar_t c )
	{
		return Append(c);
	}


	inline String& String::operator+= ( char c )
	{
		return Append(c);
	}


	inline String& String::operator+= ( wchar16 c )
	{
		return Append(c);
	}


	inline String& String::operator+= ( const wchar_t* str )
	{
		return Append(str);
	}


	inline String& String::operator+= ( const char* str )
	{
		return Append(str);
	}


	inline String& String::operator= ( const String& str )
	{
		return Assign(str);
	}


	inline String& String::operator= ( const wchar_t* str )
	{
		return Assign(str);
	}


	inline String& String::operator= ( const char* str )
	{
		return Assign(str);
	}


	inline String& String::operator= ( char c )
	{
		return Assign(c);
	}


	inline String& String::operator= ( wchar_t c )
	{
		return Assign(c);
	}


	inline const wchar16* String::CStr16() const
	{
		return Ptr();
	}


	inline const char* String::CStr8() const
	{
		if ( tempCStr8 )
		{
			AtlFree(tempCStr8);
			tempCStr8 = 0;
		}

		tempCStr8 = (char*)AtlAlloc( ((std::size_t)UTF16ToUTF8Length(Ptr()) + 1) * sizeof(char) );
		if (!tempCStr8)
			throw atl::RuntimeError( "String temporary buffer allocation error." );

		UTF16ToUTF8((wchar8*)tempCStr8, Ptr());

		return tempCStr8;
	}


	inline String String::Substr( int pos, int len ) const
	{
		if (pos < 0 || pos > size)
			throw atl::RuntimeError( "Invalid position value in String::Substr." );

		if (len < -1)
			throw atl::RuntimeError("Invalid length value in String::Substr.");

		if (len == NPos || len > size - pos)
			len = size - pos;

		String str;
		str.Reserve( len );
		wstrcpy(str.Ptr(), Ptr() + pos, len);
		str.size = len;

		return str;
	}


	inline String String::Replace( const String& find, const String& replace ) const
	{
		if (find.Size() > Size() || find.Empty())
			return *this;

		int matchCount = 0;

		int pos = 0;
		while((pos = Find(find, pos)) != atl::String::NPos)
		{
			++matchCount;
			pos += find.Size();
		}

		if (matchCount == 0)
			return *this;

		String result;
		result.Resize(Size() + matchCount * (replace.Size() - find.Size()));

		const wchar16* pSrc = Ptr();
		wchar16* pDst = result.Ptr();

		int prevPos = 0, dst = 0;
		pos = 0;
		while((pos = Find(find, pos)) != atl::String::NPos)
		{
			if (prevPos < pos)
			{
				memcpy(pDst + dst, pSrc + prevPos, (pos - prevPos) * sizeof(wchar16));
				dst += pos - prevPos;
			}

			memcpy(pDst + dst, replace.Begin(), replace.Size() * sizeof(wchar16));
			dst += replace.Size();

			pos += find.Size();
			prevPos = pos;
		}

		if (prevPos < Size())
			memcpy(pDst + dst, pSrc + prevPos, (Size() - prevPos) * sizeof(wchar16));

		return result;
	}


	inline bool String::EndsWith( const atl::String& str ) const
	{
		if(  Length() < str.Length() )
			return false;

		const wchar16* ptr = Ptr();
		for(int j = 0, i = Length() - str.Length(); i < Length(); ++i, ++j)
		{
			if( str[j] != ptr[i] )
				return false;
		}

		return true;
	}


	inline bool String::EndsWith( const wchar32* str ) const
	{
		if ( !str )
			throw atl::RuntimeError( "NULL pointer passed as argument in String::EndsWith" );

		return EndsWith( String(str) );
	}


	inline bool String::EndsWith( const wchar16* str ) const
	{
		if ( !str )
			throw atl::RuntimeError( "NULL pointer passed as argument in String::EndsWith" );

		const int len = wstrsize( str );
		if( size < len )
			return false;

		const wchar16* ptr = Ptr() + (size - len);
		for( int i = 0; i < len; ++i )
			if (ptr[i] != str[i])
				return false;

		return true;
	}


	inline bool String::EndsWith( const char* str ) const
	{
		if ( !str )
			throw atl::RuntimeError( "NULL pointer passed as argument in String::EndsWith" );

		return EndsWith( String(str) );
	}


	inline bool String::EndsWith( const wchar_t* str ) const
	{
		return EndsWith( (const StringInternal::WCharTBaseType*)str );
	}


	inline bool String::StartsWith( const atl::String& str ) const
	{
		if(  Length() < str.Length() )
			return false;

		const wchar16* ptr = Ptr();
		for(int i = 0; i < str.Length(); ++i)
		{
			if( str[i] != ptr[i] )
				return false;
		}
		return true;
	}

	inline bool String::StartsWith( const wchar32* str ) const
	{
		if ( !str )
			throw atl::RuntimeError( "NULL pointer passed as argument in String::EndsWith( const wchar_t* )" );

		return StartsWith( String(str) );
	}


	inline bool String::StartsWith( const wchar16* str ) const
	{
		if ( !str )
			throw atl::RuntimeError( "NULL pointer passed as argument in String::EndsWith( const wchar_t* )" );

		int len = wstrsize( str );
		if( size < len )
			return false;

		const wchar16* ptr = Ptr();
		for( int i = 0; i < len; ++i )
			if (ptr[i] != str[i])
				return false;

		return true;
	}


	inline bool String::StartsWith( const char* str ) const
	{
		if ( !str )
			throw atl::RuntimeError( "NULL pointer passed as argument in String::EndsWith( const wchar_t* )" );

		return StartsWith( String(str) );
	}


	inline bool String::StartsWith( const wchar_t* str ) const
	{
		return StartsWith( (const StringInternal::WCharTBaseType*)str );
	}


	inline int String::Find( const atl::String& str, int pos, bool ignoreCase) const
	{
		for ( int i = pos; i < size - str.size + 1; ++i )
		{
			bool found = true;
			for ( int j = 0; j < str.size; ++j )
			{
				wchar16	lhs = Ptr()[i + j];
				wchar16	rhs = str[j];
				if (ignoreCase)
				{
					lhs = towlower(lhs);
					rhs = towlower(rhs);
				}
				if (rhs != lhs)
				{
					found = false;
					break;
				}
			}
			if ( found )
			{
				return i;
			}
		}
		return NPos;
	}

	inline int String::RFind( const atl::String& str, int pos, bool ignoreCase ) const
	{
		if (str.size > size)
			return NPos;

		if ( pos < 0 || pos > size - str.size )
			pos = size - str.size;

		for ( int i = pos; i >= 0; --i )
		{
			bool found = true;
			for ( int j = 0; j < str.size; ++j )
			{
				wchar16	lhs = Ptr()[i + j];
				wchar16	rhs = str[j];
				if (ignoreCase)
				{
					lhs = towlower(lhs);
					rhs = towlower(rhs);
				}
				if (rhs != lhs)
				{
					found = false;
					break;
				}
			}
			if ( found )
			{
				return i;
			}
		}

		return NPos;
	}

	inline String String::Strip() const
	{
		int start = 0;
		int end = Size();

		for(int i = 0; i < Size(); ++i)
			if ( std::iswspace(Ptr()[i]) )
				start++;
			else
				break;

		for(int i = Size()-1; i > 0; --i)
			if ( std::iswspace(Ptr()[i])  )
				end = i;
			else
				break;

		int length = end-start;

		if (length > 0)
		{
			return Substr(start, end-start);
		}
		else
		{
			String emptyString;
			return emptyString;
		}
	}

#ifdef HAS_CPP0X

	inline String::String( String&& str )
	{
		uses_heap_buffer = false;
		tempCStr8 = 0;
		Assign(std::move(str));
	}

	inline String& String::operator= ( String&& str )
	{
		Assign(std::move(str));
		return *this;
	}

	inline String& String::Assign( String&& str )
	{
		if ( &str == this )
			return *this;

		DisposeData();
		InvalidateTempCStr8Buffer();

		uses_heap_buffer = str.uses_heap_buffer;
		size = str.size;
		capacity = str.capacity;

		if (uses_heap_buffer)
		{
			data.heapbuf = str.data.heapbuf;

			str.uses_heap_buffer = false;
			str.size = 0;
			str.capacity = smallSizeString;
			str.data.stackbuf[0] = 0;
			str.InvalidateTempCStr8Buffer();
		}
		else
		{
			wstrcpy(data.stackbuf, str.data.stackbuf, size);
		}

		return *this;
	}

#endif // HAS_CPP0X

	inline String operator+ (const String& lhs, const String& rhs)
	{
		return String(lhs).Append(rhs);
	}

	inline String operator+ (wchar_t lhs, const String& rhs)
	{
		return String().Append(lhs).Append(rhs);
	}

	inline String operator+ (char lhs, const String& rhs)
	{
		return String().Append(lhs).Append(rhs);
	}

	inline String operator+ (wchar16 lhs, const String& rhs)
	{
		return String().Append(lhs).Append(rhs);
	}

	inline String operator+ (const wchar_t* lhs, const String& rhs)
	{
		return String(lhs).Append(rhs);
	}

	inline String operator+ (const char* lhs, const String& rhs)
	{
		return String(lhs).Append(rhs);
	}

	inline String operator+ (const String& lhs, wchar_t rhs)
	{
		return String(lhs).Append(rhs);
	}

	inline String operator+ (const String& lhs, char rhs)
	{
		return String(lhs).Append(rhs);
	}

	inline String operator+ (const String& lhs, wchar16 rhs)
	{
		return String(lhs).Append(rhs);
	}

	inline String operator+ (const String& lhs, const wchar_t* rhs)
	{
		return String(lhs).Append(rhs);
	}

	inline String operator+ (const String& lhs, const char* rhs)
	{
		return String(lhs).Append(rhs);
	}

#ifdef HAS_CPP0X
	inline String operator+ (String&& lhs, const String& rhs)
	{
		return String(std::move(lhs)).Append(rhs);
	}

	inline String operator+ (String&& lhs, wchar_t rhs)
	{
		return String(std::move(lhs)).Append(rhs);
	}

	inline String operator+ (String&& lhs, char rhs)
	{
		return String(std::move(lhs)).Append(rhs);
	}

	inline String operator+ (String&& lhs, wchar16 rhs)
	{
		return String(std::move(lhs)).Append(rhs);
	}

	inline String operator+ (String&& lhs, const wchar_t* rhs)
	{
		return String(std::move(lhs)).Append(rhs);
	}

	inline String operator+ (String&& lhs, const char* rhs)
	{
		return String(std::move(lhs)).Append(rhs);
	}
#endif // HAS_CPP0X


	inline bool IsFilePathWithoutExtension( const atl::String& path )
	{
		int i = path.Size() - 1;

		while(i >= 0 && path[i] == L' ')
			--i;

		if (i < 0)
			return false;

		if (path[i] == L'\\' || path[i] == L'/' || path[i] == L':')
			return false;

		for( ; i >= 0; --i )
		{
			atl::wchar16 c = path[i];

			if (c == L'.')
				return false;

			if (c == L'\\' || c == L'/' || c == L':')
				return true;
		}

		return true;
	}

} // namespace atl

#endif // ATL_STRING_HXX
