//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_PATHCLASSIFICATION_H
#define AVL_PATHCLASSIFICATION_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Path/Path.h"
#include "AVLCommon/Enums/SortingOrder.h"

namespace avl
{


	/// <summary>Selects paths which are open.</summary>
	/// <param name="inPaths">Input paths.</param>
	/// <param name="outOpenPaths">Paths classified as open.</param>
	AVL_FUNCTION void SelectOpenPaths
	(
		const atl::Array<avl::Path>&	inPaths,		
		atl::Array<avl::Path>&			outOpenPaths	
	)
	THROW_AVL_ERRORS;

	/// <summary>Selects paths which are closed.</summary>
	/// <param name="inPaths">Input paths.</param>
	/// <param name="outClosedPaths">Paths classified as closed.</param>
	AVL_FUNCTION void SelectClosedPaths
	(
		const atl::Array<avl::Path>&	inPaths,		
		atl::Array<avl::Path>&			outClosedPaths	
	)
	THROW_AVL_ERRORS;

	/// <summary>Selects paths which do not obstruct visibility of other paths from a point.</summary>
	/// <param name="inPaths">Input paths from which the outer ones will be selected.</param>
	/// <param name="inCenterPoint">Reference point used to determine path visibility.</param>
	/// <param name="inTolerance">Fraction of the path sections that are allowed to obstruct visibility of other paths not rendering the path not-outer. Default value: 0.0f.</param>
	/// <param name="outOuterPaths">Paths classified as outer.</param>
	AVL_FUNCTION void SelectOuterPaths
	(
		const atl::Array<avl::Path>& inPaths, 
		const avl::Point2D& inCenterPoint, 
		float inTolerance, 
		atl::Array<avl::Path>& outOuterPaths 
	)
	THROW_AVL_ERRORS;

	/// <summary>Selects paths which are visible from a point.</summary>
	/// <param name="inPaths">Input paths from which the inner ones will be selected.</param>
	/// <param name="inCenterPoint">Reference point used to determine path visibility.</param>
	/// <param name="inTolerance">Fraction of the path characteristic points that are allowed to be invisible from the inCenterPoint not rendering the path not-inner. Default value: 0.0f.</param>
	/// <param name="outInnerPaths">Paths classified as inner.</param>
	AVL_FUNCTION void SelectInnerPaths
	(
		const atl::Array<avl::Path>& inPaths, 
		const avl::Point2D& inCenterPoint, 
		float inTolerance,
		atl::Array<avl::Path>& outInnerPaths 
	)
	THROW_AVL_ERRORS;

	namespace PathFeature
	{
		enum Type
		{
			BoundingBoxBottom,
			BoundingBoxLeft,
			BoundingBoxRight,
			BoundingBoxTop,
			DiameterLength,
			Length,
			MassCenterX,
			MassCenterY,
			ShapeArea,
			ShapeCircularity_BoundingCirclePreserving,
			ShapeCircularity_PerimeterPreserving,
			ShapeCircularity_RadiusPreserving,
			ShapeConvexity,
			ShapeElongation,
			ShapeMajorAxisLength,
			ShapeMinorAxisLength,
			ShapeRectangularity,
			Size
		};
	}

	namespace PathFilter
	{
		enum Type
		{
			All,
			ClosedOnly,
			OpenOnly
		};
	}


	/// <summary>Splits the paths of the input array - in accordance to the relation between computed feature values and the specified range.</summary>
	/// <param name="inPaths">Input paths.</param>
	/// <param name="inPathFilter">Determines which paths will take part in computation.</param>
	/// <param name="inFeature">Path feature value to be computed.</param>
	/// <param name="inMinimum">Lowest value of the range. Default value: atl::NIL.</param>
	/// <param name="inMaximum">Highest value of the range. Default value: atl::NIL.</param>
	/// <param name="outAccepted">Paths with feature values matching the range.</param>
	/// <param name="outRejected">Paths with feature values outside the range.</param>
	/// <param name="outBelow">Paths with feature values lower than inMinimum.</param>
	/// <param name="outAbove">Paths with feature values higher than inMaximum.</param>
	/// <param name="outValues">Computed feature values.</param>
	AVL_FUNCTION void ClassifyPaths
	(
		const atl::Array<avl::Path>&	inPaths,	
		avl::PathFilter::Type			inPathFilter,	
		avl::PathFeature::Type			inFeature,	
		atl::Optional<float>		inMinimum,	
		atl::Optional<float>		inMaximum,	
		atl::Optional<atl::Array<avl::Path>&>	outAccepted,			
		atl::Optional<atl::Array<avl::Path>&>	outRejected = atl::NIL,	
		atl::Optional<atl::Array<avl::Path>&>	outBelow = atl::NIL,	
		atl::Optional<atl::Array<avl::Path>&>	outAbove = atl::NIL,	
		atl::Optional<atl::Array<float>&>	outValues = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes path feature and checks whether its value is in range.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="inFeature">Path feature value to be computed.</param>
	/// <param name="inMinimum">Lowest value of the range. Default value: atl::NIL.</param>
	/// <param name="inMaximum">Highest value of the range. Default value: atl::NIL.</param>
	/// <param name="outConditionalPath">The path if the condition is met or nothing otherwise.</param>
	AVL_FUNCTION void MakePathConditional
	(
		const avl::Path&				inPath,				
		avl::PathFeature::Type			inFeature,			
		atl::Optional<float>		inMinimum,			
		atl::Optional<float>		inMaximum,			
		atl::Conditional<avl::Path>&	outConditionalPath	
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes the order of paths from the input array accordingly to an ascending/descending sequence of their computed feature values.</summary>
	/// <param name="inPaths">Input paths.</param>
	/// <param name="inPathFilter">Determines which paths will take part in computation.</param>
	/// <param name="inFeature">Path feature value to be computed.</param>
	/// <param name="inSortingOrder">Sorting order.</param>
	/// <param name="outSortedPaths">Paths sorted according to the computed feature values.</param>
	/// <param name="outSortedValues">Computed feature values.</param>
	AVL_FUNCTION void SortPaths
	(
		const atl::Array<avl::Path>&	inPaths,	
		avl::PathFilter::Type			inPathFilter,	
		avl::PathFeature::Type			inFeature,	
		avl::SortingOrder::Type			inSortingOrder,	
		atl::Array<avl::Path>&			outSortedPaths,	
		atl::Optional<atl::Array<float>&>	outSortedValues = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the path from the input array that corresponds to the smallest computed feature value.</summary>
	/// <param name="inPaths">Input paths.</param>
	/// <param name="inFeature">Path feature value to be computed.</param>
	/// <param name="outPath">Output path.</param>
	/// <param name="outValue">Computed feature value of the output path.</param>
	AVL_FUNCTION void GetMinimumPath
	(
		const atl::Array<avl::Path>&	inPaths,	
		avl::PathFeature::Type			inFeature,	
		avl::Path&						outPath,
		atl::Optional<float&>			outValue = atl::NIL,	
		atl::Optional<int&>				outIndex = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the path from the input array that corresponds to the smallest computed feature value; returns NIL if the array or any path inside it is empty.</summary>
	/// <param name="inPaths">Input paths.</param>
	/// <param name="inFeature">Path feature value to be computed.</param>
	/// <param name="outPath">Output path.</param>
	/// <param name="outValue">Computed feature value of the output path.</param>
	AVL_FUNCTION void GetMinimumPath_OrNil
	(
		const atl::Array<avl::Path>&	inPaths,	
		avl::PathFeature::Type			inFeature,	
		atl::Conditional<avl::Path>&	outPath,
		atl::Conditional<float>&		outValue,	
		atl::Conditional<int>&			outIndex
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the path from the input array that corresponds to the largest computed feature value.</summary>
	/// <param name="inPaths">Input paths.</param>
	/// <param name="inFeature">Path feature value to be computed.</param>
	/// <param name="outPath">Output path.</param>
	/// <param name="outValue">Computed feature value of the output path.</param>
	AVL_FUNCTION void GetMaximumPath
	(
		const atl::Array<avl::Path>&	inPaths,	
		avl::PathFeature::Type			inFeature,	
		avl::Path&						outPath,
		atl::Optional<float&>			outValue = atl::NIL,	
		atl::Optional<int&>				outIndex = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the path from the input array that corresponds to the largest computed feature value; returns NIL if the array or any path inside it is empty.</summary>
	/// <param name="inPaths">Input paths.</param>
	/// <param name="inFeature">Path feature value to be computed.</param>
	/// <param name="outPath">Output path.</param>
	/// <param name="outValue">Computed feature value of the output path.</param>
	AVL_FUNCTION void GetMaximumPath_OrNil
	(
		const atl::Array<avl::Path>&	inPaths,	
		avl::PathFeature::Type			inFeature,	
		atl::Conditional<avl::Path>&	outPath,
		atl::Conditional<float>&		outValue,	
		atl::Conditional<int>&			outIndex
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_PATHCLASSIFICATION_H

