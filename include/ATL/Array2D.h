//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef ATL_ARRAY_2D_H
#define ATL_ARRAY_2D_H

#include "Platform.h"

#ifdef HAS_CPP11
#include <initializer_list>
#endif

namespace atl
{

	template <typename T>
	class Array2D
	{
	public:
		Array2D();
		Array2D( int nRows, int nCols );
		Array2D( int nRows, int nCols, const T& value );
		Array2D( const Array2D& rhs );
		~Array2D();

		Array2D& operator = ( const Array2D& rhs );

#ifdef HAS_CPP0X

		Array2D( Array2D&& rhs );
		Array2D& operator = ( Array2D&& rhs );

#endif
#ifdef HAS_CPP11

		Array2D(int nRows, int nCols, std::initializer_list<T>);

#endif

		void	Reset( int nRows, int nCols );
		void	Reset( int nRows, int nCols, const T& value );
		void	ResetWithData( int nRows, int nCols, const T* data );

		int		RowCount() const;
		int		ColCount() const;
		bool	Empty() const;

		T*		 operator[]( int i );
		const T* operator[]( int i ) const;

		T*       RowBegin( int i );
		const T* RowBegin( int i ) const;

		T*       RowEnd( int i );
		const T* RowEnd( int i ) const;

		bool operator == ( const Array2D& rhs ) const;
		bool operator != ( const Array2D& rhs ) const;

	protected:

		void Delete( void );
		T* Alloc( int rows, int cols );
		void SetDimensions( int rows, int cols );

		int nRows;
		int nCols;
		T*  data;
	};
}

#endif
