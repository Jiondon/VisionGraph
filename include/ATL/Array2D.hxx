//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef ATL_ARRAY_2D_HXX
#define ATL_ARRAY_2D_HXX


#include "Array2D.h"
#include "Error.h"
#include "AtlMemory.h"

#include <climits>
#include <algorithm>
#include <cassert>

#pragma push_macro("new")
#ifdef new
#	undef new
#endif

namespace atl
{
	template <typename T>
	Array2D<T>::Array2D()
		: nRows(0) , nCols(0) , data(0)
	{
	}


	template <typename T>
	Array2D<T>::Array2D( int nRows, int nCols )
		: nRows(0) , nCols(0) , data(0)
	{
		Reset( nRows, nCols );
	}


	template <typename T>
	Array2D<T>::Array2D( int nRows, int nCols, const T& value )
		: nRows(0) , nCols(0) , data(0)
	{
		Reset( nRows, nCols, value );
	}


	template <typename T>
	Array2D<T>::Array2D( const Array2D& rhs )
		: nRows(0) , nCols(0) , data(0)
	{
		Reset(rhs.RowCount(), rhs.ColCount());

		for (int i = 0; i < nRows; i++)
		{
			for (int j = 0; j < nCols; j++)
			{
				data[ i * nCols + j ] = rhs[i][j];
			}
		}
	}


	template <typename T>
	Array2D<T>::~Array2D()
	{
		Delete();
	}


	template <typename T>
	Array2D<T>& Array2D<T>::operator = ( const Array2D& rhs )
	{
		if ( this == &rhs )
			return *this;

		Reset(rhs.RowCount(), rhs.ColCount());

		for (int i = 0; i < nRows; i++)
		{
			for (int j = 0; j < nCols; j++)
			{
				data[i * nCols + j ] = rhs[i][j];
			}
		}

		return *this;
	}


#ifdef HAS_CPP0X

	template <typename T>
	Array2D<T>::Array2D( Array2D&& rhs )
	{
		data = rhs.data;
		nRows = rhs.nRows;
		nCols = rhs.nCols;

		rhs.data = 0;
		rhs.nRows = 0;
		rhs.nCols = 0;
	}


	template <typename T>
	Array2D<T>& Array2D<T>::operator = ( Array2D&& rhs )
	{
		if ( this == &rhs )
			return *this;

		Delete();

		data = rhs.data;
		nRows = rhs.nRows;
		nCols = rhs.nCols;

		rhs.data = 0;
		rhs.nRows = 0;
		rhs.nCols = 0;

		return *this;
	}

#endif

#ifdef HAS_CPP11

	template <typename T>
	Array2D<T>::Array2D(int nRows, int nCols, std::initializer_list<T> il)
		: Array2D(nRows, nCols)
	{
		assert(nRows*nCols == int(il.size()));
		std::copy(il.begin(), il.end(), data);
	}

#endif

	template <typename T>
	void Array2D<T>::Delete( void )
	{
		for (int i = 0; i < nRows; i++)
			for (int j = 0; j < nCols; j++)
				data[ i * nCols + j ].~T();

		AtlFree( static_cast<void*>(data) );
		data = 0;
	}


	template <typename T>
	T* Array2D<T>::Alloc( int rows, int cols )
	{
		if (rows < 0 || cols < 0)
			throw atl::RuntimeError( "Bad dimension values in Array2D allocation." );

		if (rows == 0 || cols == 0)
			return 0;

		if (INT_MAX / (int)sizeof(T) / cols < rows)
			throw atl::OutOfMemoryError("Allocation error - array dimensions too big in Array2D::Reset().");

		void* ptr = AtlAlloc((std::size_t)cols * (std::size_t)rows * sizeof(T));
		if (!ptr)
			throw atl::OutOfMemoryError("Allocation error - array dimensions too big in Array2D::Reset().");

		return static_cast<T*>(ptr);
	}


	template <typename T>
	void Array2D<T>::SetDimensions( int rows, int cols )
	{
		if (rows <= 0 || cols <= 0)
		{
			nRows = 0;
			nCols = 0;
		}
		else
		{
			nRows = rows;
			nCols = cols;
		}
	}


	template <typename T>
	void Array2D<T>::Reset( int newRowCount, int newColCount )
	{
		if (newRowCount == this->nRows && newColCount == this->nCols)
			return;

		Delete();

		data = Alloc(newRowCount, newColCount);

		for (int i = 0; i < newRowCount; i++)
			for (int j = 0; j < newColCount; j++)
				new (data + i * newColCount + j) T;

		SetDimensions(newRowCount, newColCount);
	}


	template <typename T>
	void Array2D<T>::Reset( int newRowCount, int newColCount, const T& value )
	{
		if (newRowCount == this->nRows && newColCount == this->nCols)
		{
			for (int i = 0; i < newRowCount; i++)
				for (int j = 0; j < newColCount; j++)
					data[i * newColCount + j] = value;
		}
		else
		{
			Delete();

			data = Alloc(newRowCount, newColCount);

			for (int i = 0; i < newRowCount; i++)
				for (int j = 0; j < newColCount; j++)
					new (data + i * newColCount + j) T(value);

			SetDimensions(newRowCount, newColCount);
		}
	}


	template <typename T>
	void Array2D<T>::ResetWithData( int newRowCount, int newColCount, const T* rhs )
	{

		if (newRowCount == this->nRows && newColCount == this->nCols)
		{
			for (int i = 0; i < newRowCount; i++)
				for (int j = 0; j < newColCount; j++)
					data[i * newColCount + j] = *(rhs++);
		}
		else
		{
			Delete();

			data = Alloc(newRowCount, newColCount);

			for (int i = 0; i < newRowCount; i++)
				for (int j = 0; j < newColCount; j++)
					new (data + i * newColCount + j) T(*(rhs++));

			SetDimensions(newRowCount, newColCount);
		}
	}


	template <typename T>
	int Array2D<T>::RowCount() const
	{
		return nRows;
	}


	template <typename T>
	int Array2D<T>::ColCount() const
	{
		return nCols;
	}


	template <typename T>
	bool Array2D<T>::Empty() const
	{
		return nRows == 0 || nCols == 0;
	}


	template <typename T>
	T* Array2D<T>::operator[]( int i )
	{
		#ifdef _DEBUG
			if (i < 0 || i >= nRows)
			{
				throw atl::RuntimeError("atl::Array2D: Index out of range.");
			}
		#endif

		return data + nCols * i;
	}


	template <typename T>
	const T* Array2D<T>::operator[]( int i ) const
	{
		#ifdef _DEBUG
			if (i < 0 || i >= nRows)
			{
				throw atl::RuntimeError("atl::Array2D: Index out of range.");
			}
		#endif

		return data + nCols * i;
	}


	template <typename T>
	T* Array2D<T>::RowBegin( int i )
	{
		#ifdef _DEBUG
			if (i < 0 || i >= nRows)
			{
				throw atl::RuntimeError("atl::Array2D: Index out of range.");
			}
		#endif

		return data + nCols * i;
	}


	template <typename T>
	const T* Array2D<T>::RowBegin( int i ) const
	{
		#ifdef _DEBUG
			if (i < 0 || i >= nRows)
			{
				throw atl::RuntimeError("atl::Array2D: Index out of range.");
			}
		#endif

		return data + nCols * i;
	}


	template <typename T>
	T* Array2D<T>::RowEnd( int i )
	{
		#ifdef _DEBUG
			if (i < 0 || i >= nRows)
			{
				throw atl::RuntimeError("atl::Array2D: Index out of range.");
			}
		#endif

		return data + (i + 1) * nCols;
	}


	template <typename T>
	const T* Array2D<T>::RowEnd( int i ) const
	{
		#ifdef _DEBUG
			if (i < 0 || i >= nRows)
			{
				throw atl::RuntimeError("atl::Array2D: Index out of range.");
			}
		#endif

		return data + (i + 1) * nCols;
	}


	template <typename T>
	bool Array2D<T>::operator == ( const Array2D<T>& rhs ) const
	{
		if (this == &rhs)
			return true;

		if (nRows != rhs.nRows || nCols != rhs.nCols)
			return false;

		for ( int i = 0; i < nRows; ++i )
		{
			const T* p = RowBegin(i);
			const T* e = RowEnd(i);
			const T* r = rhs.RowBegin(i);

			while ( p < e )
			{
				if (*(p++) != *(r++))
					return false;
			}
		}

		return true;
	}


	template <typename T>
	bool Array2D<T>::operator != ( const Array2D<T>& rhs ) const
	{
		return !(operator == (rhs));
	}

} // namespace atl

#pragma pop_macro("new")

#endif
