//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_RANDOM_H
#define AVL_RANDOM_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/AtlTypes.h"
#include "AVLCommon/MatrixTypes.h"
#include "AVLCommon/RandomTypes.h"
#include "ATL/Array.hxx"

namespace avl
{


	struct RandomSeed_OfState : public BaseState
	{
		atl::uint64 nextSeed;
	};



	AVL_FUNCTION void InitRandomGenerator
	(
		RandomState&			ioState,
		atl::Optional<int>		inSeed
	)
	THROW_AVL_ERRORS;

	AVL_FUNCTION void CreateRandomSeed
	(
		atl::uint64& outSeed
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates random integer value in given closed interval.</summary>
	/// <param name="ioState">State of generator.</param>
	/// <param name="inMinValue">Minimal generated value.</param>
	/// <param name="inMaxValue">Maximal generated value. Default value: 10.</param>
	/// <param name="inSeed">Random seed used to generate values. Default value: atl::NIL.</param>
	AVL_FUNCTION void RandomInteger_Deprecated
	(
		RandomSeed_OfState&		ioState,		
		const int				inMinValue,		
		const int				inMaxValue,		
		atl::Optional<int>		inSeed,			
		int&					outValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates random integer value in given closed interval.</summary>
	/// <param name="ioState">State of generator.</param>
	/// <param name="inMinValue">Minimal generated value.</param>
	/// <param name="inMaxValue">Maximal generated value. Default value: 10.</param>
	/// <param name="inSeed">Random seed used to generate values. Default value: atl::NIL.</param>
	AVL_FUNCTION void RandomInteger
	(
		RandomState&			ioState,		
		const int				inMinValue,		
		const int				inMaxValue,		
		atl::Optional<int>		inSeed,			
		int&					outValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates random real value in given closed interval.</summary>
	/// <param name="ioState">State of generator.</param>
	/// <param name="inMinValue">Minimal generated value.</param>
	/// <param name="inMaxValue">Maximal generated value. Default value: 1.0f.</param>
	/// <param name="inSeed">Random seed used to generate values. Default value: atl::NIL.</param>
	AVL_FUNCTION void RandomReal_Deprecated
	(
		RandomSeed_OfState&		ioState,	
		const float				inMinValue, 
		const float				inMaxValue, 
		atl::Optional<int>		inSeed,		
		float&					outValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates random real value in given closed interval.</summary>
	/// <param name="ioState">State of generator.</param>
	/// <param name="inMinValue">Minimal generated value.</param>
	/// <param name="inMaxValue">Maximal generated value. Default value: 1.0f.</param>
	/// <param name="inSeed">Random seed used to generate values. Default value: atl::NIL.</param>
	AVL_FUNCTION void RandomReal
	(
		RandomState&			ioState,	
		const float				inMinValue, 
		const float				inMaxValue, 
		atl::Optional<int>		inSeed,		
		float&					outValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates matrix with random values in closed interval.</summary>
	/// <param name="inColumnCount">Columns count of generated matrix. Default value: 10.</param>
	/// <param name="inRowCount">Rows count of generated matrix. Default value: 10.</param>
	/// <param name="inMinValue">Minimal generated value.</param>
	/// <param name="inMaxValue">Maximal generated value. Default value: 10.0f.</param>
	/// <param name="inStep">Minimal difference between two random values. Default value: 1.0f.</param>
	/// <param name="inSeed">Random seed used to generate values. Default value: atl::NIL.</param>
	AVL_FUNCTION void CreateRandomMatrix_Deprecated
	(
		const int				inColumnCount,	
		const int				inRowCount,		
		const float				inMinValue,		
		const float				inMaxValue,		
		const float				inStep,			
		atl::Optional<int>		inSeed,			
		avl::Matrix&			outMatrix
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates matrix with random values in closed interval.</summary>
	/// <param name="inColumnCount">Columns count of generated matrix. Default value: 10.</param>
	/// <param name="inRowCount">Rows count of generated matrix. Default value: 10.</param>
	/// <param name="inMinValue">Minimal generated value.</param>
	/// <param name="inMaxValue">Maximal generated value. Default value: 10.0f.</param>
	/// <param name="inStep">Minimal difference between two random values. Default value: 1.0f.</param>
	/// <param name="inSeed">Random seed used to generate values. Default value: atl::NIL.</param>
	AVL_FUNCTION void CreateRandomMatrix
	(
		const int				inColumnCount,	
		const int				inRowCount,		
		const float				inMinValue,		
		const float				inMaxValue,		
		const float				inStep,			
		atl::Optional<int>		inSeed,			
		avl::Matrix&			outMatrix
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates array with random values.</summary>
	/// <param name="inLength">Length of output array. Default value: 10.</param>
	/// <param name="inMinValue">Minimal generated value.</param>
	/// <param name="inMaxValue">Maximal generated value. Default value: 10.0f.</param>
	/// <param name="inStep">Minimal difference between two generated values. Default value: 1.0f.</param>
	/// <param name="inSeed">Random seed used to generate values. Default value: atl::NIL.</param>
	AVL_FUNCTION void CreateRandomArray_Deprecated
	(
		const int					inLength,	
		const float					inMinValue,	
		const float					inMaxValue, 
		const float					inStep,		
		atl::Optional<int>			inSeed,		
		atl::Array<float>&			outArray
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates array with random values.</summary>
	/// <param name="inLength">Length of output array. Default value: 10.</param>
	/// <param name="inMinValue">Minimal generated value.</param>
	/// <param name="inMaxValue">Maximal generated value. Default value: 10.0f.</param>
	/// <param name="inStep">Minimal difference between two generated values. Default value: 1.0f.</param>
	/// <param name="inSeed">Random seed used to generate values. Default value: atl::NIL.</param>
	AVL_FUNCTION void CreateRandomArray
	(
		const int					inLength,	
		const float					inMinValue,	
		const float					inMaxValue, 
		const float					inStep,		
		atl::Optional<int>			inSeed,		
		atl::Array<float>&			outArray
	)
	THROW_AVL_ERRORS;

	AVL_FUNCTION void CreatePermutationTable_Deprecated
	(
		int inSize, 
		const atl::uint64& inSeed,
		atl::Array<int>& outArray
	)
	THROW_AVL_ERRORS;

	/// Creates an array by setting input array values in the random positions.
	/// <param name="inArray">Array to shuffle.</param>
	/// <param name="inSeed">Random seed used to generate values. Default value: atl::NIL.</param>
	template <typename Type>
	void ShuffleArray_Deprecated
	(
		const atl::Array<Type>&		inArray,	
		atl::Optional<int>			inSeed,		
		atl::Array<Type>&			outArray
	)
	{
		const int ArraySize = inArray.Size();
		atl::uint64 random = 0;
		atl::Array<int> permutations;

		// Create seed
		if (inSeed == atl::NIL)
			CreateRandomSeed(random);
		else
			random = inSeed.Get();

		CreatePermutationTable_Deprecated(ArraySize, random, permutations);

		outArray.Resize( ArraySize );

		for(int i = 0; i < ArraySize; ++i)
			outArray[i] = inArray[ permutations[i] ];
	}

	AVL_FUNCTION void CreatePermutationTable
	(
		int inSize,
		atl::Optional<int> inSeed,
		atl::Array<int>& outArray
	)
	THROW_AVL_ERRORS;

	/// Creates an array by setting input array values in the random positions.
	/// <param name="inArray">Array to shuffle.</param>
	/// <param name="inSeed">Random seed used to generate values. Default value: atl::NIL.</param>
	template <typename Type>
	void ShuffleArray
	(
		const atl::Array<Type>&		inArray,	
		atl::Optional<int>			inSeed,		
		atl::Array<Type>&			outArray
	)
	{
		const int ArraySize = inArray.Size();
		atl::Array<int> permutations;

		CreatePermutationTable(ArraySize, inSeed, permutations);

		outArray.Resize(ArraySize);

		for (int i = 0; i < ArraySize; ++i)
		{
			outArray[i] = inArray[permutations[i]];
		}
	}

} // namespace avl

#endif // AVL_RANDOM_H

