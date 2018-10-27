//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_MATRIX_H
#define AVL_MATRIX_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/AtlTypes.h"
#include "ATL/Array.h"
#include "AVLCommon/MatrixTypes.h"

namespace avl
{


	/// <summary>Create a matrix of specified dimensions with initial elements given row-by-row.</summary>
	AVL_FUNCTION void MakeMatrix
	(
		int inRowCount,
		int inColumnCount,
		const atl::Array<float>& inElements,
		avl::Matrix& outMatrix
	)
	THROW_AVL_ERRORS;

	/// <summary>Return matrix dimensions and its elements row-by-row as a real array.</summary>
	AVL_FUNCTION void AccessMatrix
	(
		const avl::Matrix& inMatrix,
		int& outRowCount,
		int& outColumnCount,
		atl::Array<float>& outElements
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a matrix to an array of its rows.</summary>
	AVL_FUNCTION void MatrixToRealArrayArray
	(
		const avl::Matrix&				inMatrix,
		atl::Array<atl::Array<float> >& outRealArrayArray
	)
	THROW_AVL_ERRORS;

	/// <summary>Create a matrix with the specified dimensions and filled with an uniform element value.</summary>
	AVL_FUNCTION void CreateUniformMatrix
	(
		int inRowCount,
		int inColumnCount,
		float inValue,
		avl::Matrix& outMatrix
	)
	THROW_AVL_ERRORS;

	/// <summary>Create a square matrix with ones on the main diagonal, and zeros elsewhere.</summary>
	AVL_FUNCTION void CreateIdentityMatrix
	(
		int inSize,
		avl::Matrix& outMatrix
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets a single element of a matrix.</summary>
	AVL_FUNCTION void SetMatrixElement
	(
		avl::Matrix& ioMatrix,
		int inRow,
		int inColumn,
		float inValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets the value of a single element of a matrix.</summary>
	AVL_FUNCTION void GetMatrixElement
	(
		const avl::Matrix& inMatrix,
		int inRow,
		int inColumn,
		float& outValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets elements of a matrix row.</summary>
	AVL_FUNCTION void SetMatrixRow
	(
		avl::Matrix&					ioMatrix,
		int								inRow,
		const atl::Array<float>&	inValues
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets the values from a single row of a matrix.</summary>
	AVL_FUNCTION void GetMatrixRow
	(
		const avl::Matrix&		inMatrix,
		int						inRow,
		atl::Array<float>&	outValues
	)
	THROW_AVL_ERRORS;

	/// <summary>Sets elements of a matrix column.</summary>
	AVL_FUNCTION void SetMatrixColumn
	(
		avl::Matrix&					ioMatrix,
		int								inColumn,
		const atl::Array<float>&	inValues
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets the values from a single column of a matrix.</summary>
	AVL_FUNCTION void GetMatrixColumn
	(
		const avl::Matrix&		inMatrix,
		int						inColumn,
		atl::Array<float>&	outValues
	)
	THROW_AVL_ERRORS;

	/// <summary>Combine two matrices horizontally</summary>
	AVL_FUNCTION void ConcatenateMatrices
	(
		const avl::Matrix& inMatrix1,
		const avl::Matrix& inMatrix2,
		avl::Matrix& outMatrix
	)
	THROW_AVL_ERRORS;

	/// <summary>Combine two matrices horizontally</summary>
	AVL_FUNCTION void CombineMatrices
	(
		const avl::Matrix& inMatrix1,
		const avl::Matrix& inMatrix2,
		avl::Matrix& outMatrix
	)
	THROW_AVL_ERRORS;

	/// <summary>Combine two matrices vertically</summary>
	AVL_FUNCTION void StackMatrices
	(
		const avl::Matrix& inMatrix1,
		const avl::Matrix& inMatrix2,
		avl::Matrix& outMatrix
	)
	THROW_AVL_ERRORS;

	/// <summary>Add two matrices of identical dimensions</summary>
	AVL_FUNCTION void AddMatrices
	(
		const avl::Matrix& inMatrix1,
		const avl::Matrix& inMatrix2,
		avl::Matrix& outMatrix
	)
	THROW_AVL_ERRORS;

	/// <summary>Subtract two matrices of identical dimensions</summary>
	AVL_FUNCTION void SubtractMatrices
	(
		const avl::Matrix& inMatrix1,
		const avl::Matrix& inMatrix2,
		avl::Matrix& outMatrix
	)
	THROW_AVL_ERRORS;

	/// <summary>Combine two matrices horizontally</summary>
	AVL_FUNCTION void MultiplyMatrices
	(
		const avl::Matrix& inMatrix1,
		const avl::Matrix& inMatrix2,
		avl::Matrix& outMatrix
	)
	THROW_AVL_ERRORS;

	/// <summary>Find the inverse of a square matrix.</summary>
	AVL_FUNCTION void InvertMatrix
	(
		const avl::Matrix& inMatrix,
		avl::Matrix& outInverseMatrix
	)
	THROW_AVL_ERRORS;

	/// <summary>Find the transpose of a matrix.</summary>
	AVL_FUNCTION void TransposeMatrix
	(
		const avl::Matrix& inMatrix,
		avl::Matrix& outTranspose
	)
	THROW_AVL_ERRORS;

	/// <summary>Multiply all elements of a matrix by a value.</summary>
	AVL_FUNCTION void MultiplyMatrixByReal
	(
		const avl::Matrix&	inMatrix,
		float			inValue,
		avl::Matrix&			outMatrix
	)
	THROW_AVL_ERRORS;

	/// <summary>If the input matrix dimensions are non-zero, then the matrix is copied to the output; otherwise Nil value is returned.</summary>
	AVL_FUNCTION void SkipEmptyMatrix
	(
		const avl::Matrix&				inMatrix,
		atl::Conditional<avl::Matrix>&	outNotEmptyMatrix,
		bool&							outIsNotEmpty
	)
	THROW_AVL_ERRORS;

	/// <summary>Saves serialized Matrix object as avdata file.</summary>
	/// <param name="inMatrix">Matrix to be serialized.</param>
	/// <param name="inFilename">Name of the target file.</param>
	AVL_FUNCTION void SaveMatrix
	(
		const avl::Matrix&	inMatrix,	
		const atl::File&	inFilename	
	)
	THROW_AVL_ERRORS;

	/// <summary>Loads serialized Matrix object from avdata file.</summary>
	/// <param name="inFilename">Name of the source file.</param>
	/// <param name="outMatrix">Deserialized Matrix.</param>
	AVL_FUNCTION void LoadMatrix
	(
		const atl::File& inFilename,	
		avl::Matrix&	outMatrix		
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_MATRIX_H

