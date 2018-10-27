//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef ATL_STRING_H
#define ATL_STRING_H

#include "Platform.h"
#include "AtlTypes.h"

namespace atl
{
	typedef uint8 wchar8;
	typedef uint16 wchar16;
	typedef uint32 wchar32;


	class String
	{
	private:
		static const int smallSizeString = 7;

		//UTF8
		static const int utf8MaxLen = 6;

		//UTF16
		static const wchar16 utf16SingleUnitMax = 0xFFFF;

		//UFT32
		static const wchar32 utf32Max = 0x7FFFFFFFUL;
		static const sint32 utf32LeadOffset = 0xD800 - (0x10000 >> 10);
		static const sint32 utf32SurrogateOffset = (0x10000 - (0xD800 << 10) - 0xDC00);

		union	// Null terminated string of WChar
		{
			wchar16* heapbuf;						// heap buffer
			wchar16 stackbuf[smallSizeString + 1];	// stack buffer
		} data;

		bool uses_heap_buffer;
		mutable char* tempCStr8;	// Platform dependent.
		int size;					// Number of characters without ending 0
		int capacity;				// Cells available for character heap storage ( cells reserved minus 1 )


		static void wstrcpy( wchar16* dst, const wchar16* src, const int size );
		static int wstrsize( const wchar16* s );
		static sint32 wstrcmp( const wchar16* s1, const wchar16* s2 );
		static sint32 wstrcmp( const wchar16* s1, const wchar32* s2 );
		static sint32 wstrncmp( const wchar16* s1, const wchar16* s2, int n );
		static wchar16* wstrnchr( const wchar16* str, wchar16 c, int n );

		static int utf8Len ( wchar32 codepoint );
		static void UTF16SurrogatesToUTF32( wchar32& c, const wchar16 hi, const wchar16 lo );
		static void UTF32ToUTF16Surrogates( const wchar32 c, wchar16& hi, wchar16& lo );
		static int UTF32ToUTF16Impl( wchar16* dst, bool writeOutput , const wchar32* src );
		static int UTF32ToUTF16Length( const wchar32* src );
		static int UTF32ToUTF16( wchar16* dst, const wchar32* src );
		static int UTF16ToUTF8Impl( wchar8* dst, bool writeOutput, const wchar16* src );
		static int UTF16ToUTF8Length( const wchar16* s );
		static int UTF16ToUTF8( wchar8* dst, const wchar16* src );
		static int UTF8ToUTF16Impl( wchar16* dst, const wchar8* src, const wchar8* srcEnd );
		static int UTF8ToUTF16Length( const wchar8* src, const wchar8* srcEnd );
		static int UTF8ToUTF16( wchar16* dst, const wchar8* src, const wchar8* srcEnd );

		void Init( void );
		static bool ShouldUseDynamicBuffer( int _size );

		void AssignHeapBuffer( wchar16 *buf, int newCapacity );
		void InvalidateTempCStr8Buffer( void );
		wchar16* Alloc( int _capacity );
		void DisposeData( void );

		wchar16 *Ptr()					{ return uses_heap_buffer ? data.heapbuf : data.stackbuf;	}
		const wchar16 *Ptr() const		{ return uses_heap_buffer ? data.heapbuf : data.stackbuf;	}

	public:
		enum { NPos = -1 };
		typedef int SizeType;

		String();

		String( const String& str );
		explicit String( const wchar32* str );
		explicit String( const wchar16* str );
		String( const char* str );
		String( const wchar_t* str );

		String( int n, wchar16 c );
		String( int n, char c );
		String( int n, wchar_t c );

		~String();

		int	Size() const				{ return size;			}
		int Length() const				{ return size;			}
		int MaxSize() const				{ return NPos - 1;		}
		bool Empty() const				{ return size == 0;		}
		int Capacity() const			{ return capacity;		}

		wchar16* Begin()				{ return Ptr();			}
		const wchar16* Begin() const	{ return Ptr();			}
		wchar16* End()					{ return Ptr() + size;	}
		const wchar16* End() const		{ return Ptr() + size;	}

		int Compare(const String& str ) const;
		void Swap( String& str );

		wchar16& At(int index);
		const wchar16& At(int index) const;

		void Reserve( int newCapacity );
		void Clear( void );

		void PushBack( wchar32 c );
		void PushBack( wchar16 c );
		void PushBack( char c );
		void PushBack( wchar_t c );

		void Resize( int n, wchar32 c );
		void Resize( int n, wchar16 c = 0 );
		void Resize( int n, char c );
		void Resize( int n, wchar_t c );

		int Copy( wchar16* buff, int n, int Pos = 0 ) const;
		String& Erase( int pos = 0, int n = NPos );

		String& Assign( const String& str );
		String& Assign( const wchar32* str );
		String& Assign( const wchar16* str );
		String& Assign( const char* str );
		String& Assign( const char* strBegin, const char* strEnd );
		String& Assign( const wchar_t* str );
		String& Assign( wchar32 c );
		String& Assign( wchar16 c );
		String& Assign( char c );
		String& Assign( wchar_t c );

		String& Append( const String& rhs );
		String& Append( const wchar32* str );
		String& Append( const wchar16* str );
		String& Append( const char* str );
		String& Append( const char* strBegin, const char* strEnd );
		String& Append( const wchar_t* str );
		String& Append( wchar32 c );
		String& Append( wchar16 c );
		String& Append( wchar_t c );
		String& Append( char c );

		String& Insert ( int pos1, const String& str, int pos2, int n );
		String& Insert ( int pos1, const String& str );
		String& Insert ( int pos1, const char* s, int n);
		String& Insert ( int pos1, const char* s );
		String& Insert ( int pos1, int n, char c );
		String& Insert ( int pos1, const wchar_t* s, int n);
		String& Insert ( int pos1, const wchar_t* s );
		String& Insert ( int pos1, int n, wchar_t c );

		String& Unescape();
		String& Escape();

		wchar16& operator[]( int index );
		const wchar16& operator[]( int index ) const;

		bool operator== ( const String& str ) const;
		bool operator== ( const wchar_t* str ) const;
		bool operator< ( const String& str ) const;
		bool operator< ( const wchar_t* str ) const;
		bool operator<= ( const String& str ) const;
		bool operator<= ( const wchar_t* str ) const;
		bool operator> ( const String& str ) const;
		bool operator> ( const wchar_t* str ) const;
		bool operator>= ( const String& str ) const;
		bool operator>= ( const wchar_t* str ) const;
		bool operator!= ( const String& str ) const;
		bool operator!= ( const wchar_t* str ) const;

		String& operator+= ( const String& rhs );
		String& operator+= ( wchar_t c );
		String& operator+= ( char c );
		String& operator+= ( wchar16 c );
		String& operator+= ( const wchar_t* str );
		String& operator+= ( const char* str );

		String& operator= ( const String& str );
		String& operator= ( const wchar_t* str );
		String& operator= ( const char* str );
		String& operator= ( char c );
		String& operator= ( wchar_t c );

		const wchar16* CStr16() const;
		const char* CStr8() const;

		String Substr( int pos = 0u, int len = NPos ) const;
		String Replace( const String& find, const String& replace ) const;

		bool EndsWith( const atl::String& str ) const;
		bool EndsWith( const wchar32* str ) const;
		bool EndsWith( const wchar16* str ) const;
		bool EndsWith( const char* str ) const;
		bool EndsWith( const wchar_t* str ) const;

		bool StartsWith( const atl::String& str ) const;
		bool StartsWith( const wchar32* str ) const;
		bool StartsWith( const wchar16* str ) const;
		bool StartsWith( const char* str ) const;
		bool StartsWith( const wchar_t* str ) const;

		int Find( const atl::String& str, int pos = 0, bool ignoreCase = false ) const;
		int RFind( const atl::String& str, int pos = -1, bool ignoreCase = false ) const;

		String Strip( void ) const;

#ifdef HAS_CPP0X

		String( String&& str );
		String& Assign( String&& str );
		String& operator= ( String&& str );

#endif // HAS_CPP0X

	};

	String operator+ (const String& lhs, const String& rhs);
	String operator+ (wchar_t lhs, const String& rhs);
	String operator+ (char lhs, const String& rhs);
	String operator+ (wchar16 lhs, const String& rhs);
	String operator+ (const wchar_t* lhs, const String& rhs);
	String operator+ (const char* lhs, const String& rhs);
	String operator+ (const String& lhs, wchar_t rhs);
	String operator+ (const String& lhs, char rhs);
	String operator+ (const String& lhs, wchar16 rhs);
	String operator+ (const String& lhs, const wchar_t* rhs);
	String operator+ (const String& lhs, const char* rhs);

#ifdef HAS_CPP0X
	String operator+ (String&& lhs, const String& rhs);
	String operator+ (String&& lhs, wchar_t rhs);
	String operator+ (String&& lhs, char rhs);
	String operator+ (String&& lhs, wchar16 rhs);
	String operator+ (String&& lhs, const wchar_t* rhs);
	String operator+ (String&& lhs, const char* rhs);
#endif // HAS_CPP0X

}

#ifndef NO_ATL_STRING_HXX
#include "AtlString.hxx"
#endif


#endif // ATL_STRING_H
