//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_MATRIX_TYPES_H
#define AVL_MATRIX_TYPES_H

#include "ATL/AtlTypes.h"
#include "ATL/Array2D.hxx"
#include "ATL/Array.h"
#include <algorithm>
#include <cassert>

namespace avl
{

	using atl::Array2D;
	using atl::Array;


	class Matrix : public Array2D<float>
	{
	public:

#ifdef HAS_CPP11
		using Array2D<float>::Array2D;
#else

		Matrix(int nRows, int nCols) : Array2D<float>(nRows, nCols)
		{}

		Matrix(int nRows, int nCols, const float& value) : Array2D<float>(nRows, nCols, value)
		{}

		Matrix( const Matrix& rhs ) : Array2D<float>(rhs)
		{}
#endif

		Matrix() : Array2D<float>() {}

		Matrix(int nRows, int nCols, const Array<float>& rhs )
		{
			assert(rhs.Size() == nRows*nCols);
			Array2D<float>::ResetWithData(nRows, nCols, rhs.Begin());
		}

		Matrix(int nRows, int nCols, const float* data)
		{
			Array2D<float>::ResetWithData(nRows, nCols, data);
		}

		static Matrix eye( int n )
		{
			Matrix result(n, n, 0.0f);
			for(int i=0; i<n; ++i)
				result.data[i*n+i] = 1.0f;
			return result;
		}

		Matrix operator * ( float c ) const
		{
			Matrix result(*this);
			int n = nRows * nCols;
			for(int i=0; i<n; ++i)
				result.data[i] *= c;
			return result;
		}

		Matrix operator* ( const Matrix& rhs ) const
		{
			Matrix result(nRows, rhs.nCols, (float)0);
			for (int i = 0; i < nRows; ++i)
			{
				for (int j = 0; j < rhs.nCols; ++j)
				{
					for (int k = 0; k<nCols; ++k)
						result[i][j] += (*this)[i][k] * rhs[k][j];
				}
			}
			return result;
		}

		Matrix& operator+= (const Matrix& rhs)
		{
			if (rhs.nCols != nCols || rhs.nRows != nRows)
				throw atl::DomainError("Matrix size mismatch in addition");
			int n = nRows * nCols;
			for (int i = 0; i<n; ++i)
			{
				this->data[i] += rhs.data[i];
			}
			return *this;
		}

		Matrix operator+ (const Matrix& rhs) const
		{
			Matrix ret(*this);
			ret += rhs;
			return ret;
		}

		Matrix t() const
		{
			Matrix result(nCols, nRows);
			for(int i=0; i<nCols; ++i)
				for(int j=0; j<nRows; ++j)
					result.data[i*nRows+j] = data[j*nCols+i];
			return result;		
		}

		float* Data()
		{
			return Array2D<float>::data;
		}

		const float* Data() const
		{
			return Array2D<float>::data;
		}

	};


} // namespace avl


#endif // AVL_MATRIX_TYPES_H
