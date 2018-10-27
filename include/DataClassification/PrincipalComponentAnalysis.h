//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_PRINCIPALCOMPONENTANALYSIS_H
#define AVL_PRINCIPALCOMPONENTANALYSIS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Optional.h"
#include "ATL/Array.h"
#include "AVLCommon/MatrixTypes.h"
#include "DataClassification/PCAModel.h"

namespace avl
{


	/// <summary>Find the determinant of a square matrix.</summary>
	AVL_FUNCTION void MatrixDeterminant
	(
		const avl::Matrix& inMatrix,
		float& outDeterminant
	)
	THROW_AVL_ERRORS;

	/// <summary>Find the pseudo-eigenvalues and pseudo-eigenvectors of a symmetrical square matrix.</summary>
	/// <param name="outEigenvectors">Row matrix of eigenvectors.</param>
	/// <param name="outEigenvalues">Array of eigenvalues.</param>
	AVL_FUNCTION void MatrixPseudoEigenvectors
	(
		const avl::Matrix& inMatrix,
		avl::Matrix& outEigenvectors,	
		atl::Array<float>& outEigenvalues	
	)
	THROW_AVL_ERRORS;

	/// <summary>Treats Matrix as a data frame, where examples are in rows while columns represent features, and normalizes the data by subtracting mean from each column and dividing it by its standard deviation.</summary>
	/// <param name="inMatrix">Input data frame.</param>
	/// <param name="inMeansVector">If provided, will be used in normalization of inMatrix. Default value: atl::NIL.</param>
	/// <param name="inStandardDeviationsVector">If provided, will be used in normalization of inMatrix. Default value: atl::NIL.</param>
	/// <param name="outNormalizedMatrix">Resulting normalized matrix.</param>
	/// <param name="outMeansVector">Resulting Means vector - copy of inMeansVector, or calculated Means, if inMeansVector was set NIL.</param>
	/// <param name="outStandardDeviationsVector">Resulting StdDevs vector - copy of inStandardDeviationsVector, or calculated Means, if inStandardDeviationsVector was set NIL.</param>
	AVL_FUNCTION void NormalizeMatrixData
	(
		const avl::Matrix&					inMatrix,					
		const atl::Optional<avl::Matrix&>	inMeansVector,				
		const atl::Optional<avl::Matrix&>	inStandardDeviationsVector, 
		avl::Matrix&						outNormalizedMatrix,		
		avl::Matrix&						outMeansVector,				
		avl::Matrix&						outStandardDeviationsVector 
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs the Principal Component Analysis (PCA) on provided data, creates the feature vector and normalization coefficients (mean and standard deviation of variables).</summary>
	/// <param name="inMatrix">Input data, where variables are in column, and examples are in rows.</param>
	/// <param name="inDimensions">How many data dimensions (variables) to be left in transformed data.</param>
	/// <param name="inVarianceToLeave">How many of input data variance should be left in transformed data; overrides inDimensions input. Default value: 0.95f.</param>
	/// <param name="outPCAModel">Resulting PCA model.</param>
	/// <param name="outTransformedMatrix">Transformed inMatrix with reduced dimensionality.</param>
	/// <param name="diagCovarianceMatrix">Covariance matrix of input data.</param>
	/// <param name="diagNormalizedData">Input data after normalization: scaling and centering.</param>
	/// <param name="diagUsedFeatureIndices">Indices of columns in inMatrix, which were used as Principal Components.</param>
	AVL_FUNCTION void CreatePCATransform
	(
		const avl::Matrix&	inMatrix,					
		const int			inDimensions,				
		atl::Optional<float> inVarianceToLeave,		
		avl::PCAModel&		outPCAModel,				
		avl::Matrix&		outTransformedMatrix,		
		avl::Matrix&		diagCovarianceMatrix = atl::Dummy<avl::Matrix>(),			
		avl::Matrix&		diagNormalizedData = atl::Dummy<avl::Matrix>(),				
		atl::Array<int>&		diagUsedFeatureIndices = atl::Dummy< atl::Array<int> >()			

	)
	THROW_AVL_ERRORS;

	/// <summary>Applies previously obtained Principal Component Analysis (PCA) transformation coefficients to new data.</summary>
	/// <param name="inMatrix">Input data with variables in columns and examples in rows.</param>
	/// <param name="inPCAModel">Previously created PCA model to apply to data provided in inMatrix.</param>
	/// <param name="outTransformedMatrix">Transformed inMatrix.</param>
	AVL_FUNCTION void ApplyPCATransform
	(
		const avl::Matrix&		inMatrix,				
		const avl::PCAModel&	inPCAModel,				
		avl::Matrix&			outTransformedMatrix	
	)
	THROW_AVL_ERRORS;

	/// <summary>Reverses Principal Component Analysis (PCA) process. Can be used to transform data back to original feature space.</summary>
	/// <param name="inTransformedMatrix">Data that was transformed earlier.</param>
	/// <param name="inPCAModel">PCA model used to create inTransformedMatrix.</param>
	/// <param name="outMatrix">inTransformedMatrix transformed back to its original feature space.</param>
	AVL_FUNCTION void ReversePCATransform
	(
		const avl::Matrix&		inTransformedMatrix,		
		const avl::PCAModel&	inPCAModel,					
		avl::Matrix&			outMatrix					
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_PRINCIPALCOMPONENTANALYSIS_H

