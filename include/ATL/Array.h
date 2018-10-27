//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef ATL_ARRAY_H
#define ATL_ARRAY_H

#include "Utils.h"

#ifdef HAS_CPP11
#include <initializer_list>
#endif

namespace atl
{

	/*
	*	Like std::vector: random-access and growable.
	*	Created mainly for passing data between filters, but dynamic growth
	*	is also supported for convenience.
	*	Fixed binary representation in 12 bytes (for interoperability):
	*		0x00:	pointer to data (warning: on x64 pointer has 8 bytes)
	*		0x04:	int size;
	*		0x08:	int capacity;
	*/
	template <typename T>
	class Array
	{
	public:
		int      Size() const               { return size; }
		int      Capacity() const			{ return capacity; }
		bool	 Empty() const				{ return size==0; }

		T&       Front();
		const T& Front() const;
		T&       Back();
		const T& Back() const;

		T*       Begin()                    { return data; }
		const T* Begin() const              { return data; }
		T*       End()                      { return data + size; }
		const T* End() const                { return data + size; }

		void	 Clear();
		T*		 Release();

		Array();
		explicit Array( int size );
		explicit Array( int size, const T& value );
		explicit Array(const T* begin, const T* end);
		// creates a view (own == false) or passes data together with ownership (own == true)
		explicit Array(int size, T* data, bool own);

		Array( const Array& rhs );
		Array<T>& operator = ( const Array& rhs );
		~Array();

		bool operator == ( const Array& rhs ) const;
		bool operator != ( const Array& rhs ) const;

		// Recreates the array
		void Reset( int newSize = 0 );
		void Reset( int newSize, const T& value );
		void Reset(int newSize, T* data, bool own);
		void Resize( int newSize );
		void Resize( int newSize, const T& c );
		void Reserve( int newCapacity );
		T& operator[]( int k );
		const T& operator[]( int k ) const;
		void PushBack( const T& value );
		void PopBack();
		void Insert( int index, const T& value );
		void Insert( const T *target, const T& value );
		void Insert( const T* begin, const T* end );
		void Insert( const T* target, const T* begin, const T* end );
		T* Erase( T *target );
		T* Erase( T* begin, T* end );
		void Swap( Array& rhs );

		bool IsDataOwn(void) const;
		void MakeDataOwn(void);

#ifdef HAS_CPP0X

		Array( Array&& rhs );
		Array<T>& operator = ( Array&& rhs );

		void PushBack( T&& value );
		void Insert( int index, T&& value );
		void Insert( const T *target, T&& value );

//we have variadic templates in CPP11
#ifndef HAS_CPP11
		template <typename A0>
		void EmplaceBack( A0&& arg0 );

		template <typename A0, typename A1>
		void EmplaceBack( A0&& arg0, A1&& arg1 );

		template <typename A0, typename A1, typename A2>
		void EmplaceBack( A0&& arg0, A1&& arg1, A2&& arg2 );

		template <typename A0, typename A1, typename A2, typename A3>
		void EmplaceBack( A0&& arg0, A1&& arg1, A2&& arg2, A3&& arg3 );
#endif

#endif
#ifdef HAS_CPP11

		Array(std::initializer_list<T>);
		Array<T>& operator=(std::initializer_list<T>);
		void Insert(const T* target, std::initializer_list<T>);

		template <typename... Args>
		T& EmplaceBack(Args&&... args);

#endif

	private:
		T*  data;
		int size;
		int capacity;

		void Enlarge( int requestedCapacity = 0 );
		void Delete( void );

		T* Alloc( int n );
		void Free( T* ptr );
	};

	template <typename T>
	Array<T> ToArray( const T& elem )
	{
		return Array<T>( 1, elem );
	}

	template <typename T>
	inline T* begin(Array<T>& inArray)
	{
		return inArray.Begin();
	}

	template <typename T>
	inline const T* begin(const Array<T>& inArray)
	{
		return inArray.Begin();
	}

	template <typename T>
	inline T* end(Array<T>& inArray)
	{
		return inArray.End();
	}

	template <typename T>
	inline const T* end(const Array<T>& inArray)
	{
		return inArray.End();
	}

} // namespace atl


#endif
