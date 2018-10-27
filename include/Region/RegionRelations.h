//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_REGIONRELATIONS_H
#define AVL_REGIONRELATIONS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "AVLCommon/Enums/SortingOrder.h"
#include "Geometry/Geometry.h"
#include "Path/Path.h"
#include "Region/Region.h"
#include "Enums/RegionConnectivity.h"
#include "Enums/RegionFeature.h"

namespace avl
{


	namespace MatchingCriterion
	{
		enum Type
		{
			Intersection, 
			Inclusion
		};
	}


	/// <summary>Tests whether given regions are equal.</summary>
	/// <param name="inRegion">Input region.</param>
	AVL_FUNCTION void TestRegionEqualTo
	(
		const avl::Region&	inRegion,
		const avl::Region&	inReferenceRegion,
		bool&				outIsEqual
	)
	THROW_AVL_ERRORS;

	/// <summary>Tests whether given regions are not equal.</summary>
	/// <param name="inRegion">Input region.</param>
	AVL_FUNCTION void TestRegionUnequalTo
	(
		const avl::Region&	inRegion,
		const avl::Region&	inReferenceRegion,
		bool&				outIsUnequal
	)
	THROW_AVL_ERRORS;

	/// <summary>Tests whether two regions have non-empty intersection.</summary>
	/// <param name="inRegion">Input region.</param>
	AVL_FUNCTION void TestRegionIntersectsWith
	(
		const avl::Region&	inRegion,
		const avl::Region&	inReferenceRegion,
		bool&				outRegionsIntersect
	)
	THROW_AVL_ERRORS;

	/// <summary>Tests whether a region is contained in another one.</summary>
	/// <param name="inRegion">Input region.</param>
	AVL_FUNCTION void TestRegionInRegion
	(
		const avl::Region& inSubregion,
		const avl::Region& inRegion,
		bool& outIsContained
		)
	THROW_AVL_ERRORS;

	/// <summary>Tests whether a point lies inside a region.</summary>
	/// <param name="inRegion">Input region.</param>
	AVL_FUNCTION void TestPointInRegion
	(
		const avl::Point2D&	inPoint,
		const avl::Region&	inRegion,
		bool&			outIsContained
	)
	THROW_AVL_ERRORS;

	/// <summary>Tests which points lie inside a region.</summary>
	/// <param name="inRegion">Input region.</param>
	AVL_FUNCTION void TestPointArrayInRegion
	(
		const atl::Array<avl::Point2D>&				inPoints,
		const avl::Region&							inRegion,
		atl::Array<bool>&							outIsContainedArray,
		atl::Optional<atl::Array<avl::Point2D>&>	outPoints = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>For each region returns which points lie inside of it.</summary>
	AVL_FUNCTION void GroupPointsByRegions
	(
		const atl::Array<avl::Point2D>&								inPoints,
		const atl::Array<avl::Region>&								inRegions,
		atl::Array<atl::Array<int> >&								outGroupedIndices,
		atl::Optional<atl::Array<atl::Array<avl::Point2D> >&>		outGroupedPoints
	)
	THROW_AVL_ERRORS;

	/// <summary>For each region returns which paths lie inside of it or intersect with it.</summary>
	/// <param name="inPaths">Array of paths that will be classified into multiple groups.</param>
	/// <param name="inRegions">Array of regions that define the groups.</param>
	/// <param name="inMatchingCriterion">Specifies whether a path must fully belong to a group region or if it is enough that it intersects.</param>
	/// <param name="outGroupedIndices">Indices of input paths classified into multiple groups.</param>
	/// <param name="outGroupedPaths">Input paths classified into multiple groups.</param>
	AVL_FUNCTION void GroupPathsByRegions
	(
		const atl::Array<avl::Path>&						inPaths,					
		const atl::Array<avl::Region>&						inRegions,					
		avl::MatchingCriterion::Type						inMatchingCriterion,		
		atl::Array<atl::Array<int> >&						outGroupedIndices,			
		atl::Optional<atl::Array<atl::Array<avl::Path> >&>	outGroupedPaths = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>For each region returns which regions lie inside of it or intersect with it.</summary>
	/// <param name="inRegions">Array of regions that will be classified into multiple groups.</param>
	/// <param name="inGroupRegions">Array of regions that define the groups.</param>
	/// <param name="inMatchingCriterion">Specifies whether a region must fully belong to a group region or if it is enough that it intersects.</param>
	/// <param name="outGroupedIndices">Indices of input regions classified into multiple groups.</param>
	/// <param name="outGroupedRegions">Input regions classified into multiple groups.</param>
	AVL_FUNCTION void GroupRegionsByRegions
	(
		const atl::Array<avl::Region>&							inRegions,						
		const atl::Array<avl::Region>&							inGroupRegions,					
		avl::MatchingCriterion::Type							inMatchingCriterion,			
		atl::Array<atl::Array<int> >&							outGroupedIndices,				
		atl::Optional<atl::Array<atl::Array<avl::Region> >&>	outGroupedRegions = atl::NIL	
	)
	THROW_AVL_ERRORS;

	namespace ShiftType 
	{
		enum Type 
		{
			Any,
			Horizontal,
			Vertical
		};
	}

	namespace FitType
	{
		enum Type
		{
			FirstFit,
			BestFit
		};
	}


	/// <summary>Shifts source region so that it is contained in target region.</summary>
	/// <param name="inTargetRegion">Region to contain source region.</param>
	/// <param name="inSourceRegion">Region to be shifted.</param>
	/// <param name="inPossibleShift">Possible directions of shift.</param>
	/// <param name="inFitType">Determines if the common border length should be maximized.</param>
	/// <param name="outShiftX">X coordinate of the shift.</param>
	/// <param name="outShiftY">Y coordinate of the shift.</param>
	/// <param name="outShiftedRegion">Shifted source region.</param>
	AVL_FUNCTION void InscribeRegionInRegion
	(
		const avl::Region&			inTargetRegion, 
		const avl::Region&			inSourceRegion, 
		avl::ShiftType::Type		inPossibleShift, 
		avl::FitType::Type			inFitType, 
		atl::Conditional<int>&		outShiftX, 
		atl::Conditional<int>&		outShiftY, 
		atl::Conditional<avl::Region>&	outShiftedRegion 
	)
	THROW_AVL_ERRORS;

	/// <summary>Splits an array of regions according to the selected feature and range.</summary>
	/// <param name="inRegions">Input regions.</param>
	/// <param name="inFeature">Region feature value to be computed.</param>
	/// <param name="inMinimum">Lowest value of the range. Default value: atl::NIL.</param>
	/// <param name="inMaximum">Highest value of the range. Default value: atl::NIL.</param>
	/// <param name="outAccepted">Regions with feature values matching the range.</param>
	/// <param name="outRejected">Regions with feature values outside the range.</param>
	/// <param name="outBelow">Regions with feature values lower than inMinimum.</param>
	/// <param name="outAbove">Regions with feature values higher than inMaximum.</param>
	/// <param name="outValues">Computed feature values.</param>
	AVL_FUNCTION void ClassifyRegions
	(
		const atl::Array<avl::Region>&	inRegions,	
		avl::RegionFeature::Type		inFeature,	
		atl::Optional<float>		inMinimum,	
		atl::Optional<float>		inMaximum,	
		atl::Optional<atl::Array<avl::Region>&>	outAccepted,			
		atl::Optional<atl::Array<avl::Region>&>	outRejected = atl::NIL,	
		atl::Optional<atl::Array<avl::Region>&>	outBelow = atl::NIL,	
		atl::Optional<atl::Array<avl::Region>&>	outAbove = atl::NIL,	
		atl::Optional<atl::Array<float>&>	outValues = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes region feature and checks whether its value is in range.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inFeature">Region feature value to be computed.</param>
	/// <param name="inMinimum">Lowest value of the range. Default value: atl::NIL.</param>
	/// <param name="inMaximum">Highest value of the range. Default value: atl::NIL.</param>
	/// <param name="outConditionalRegion">The region if the condition is met or nothing otherwise.</param>
	AVL_FUNCTION void MakeRegionConditional
	(
		const avl::Region&				inRegion,				
		avl::RegionFeature::Type		inFeature,				
		atl::Optional<float>		inMinimum,				
		atl::Optional<float>		inMaximum,				
		atl::Conditional<avl::Region>&	outConditionalRegion	
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes the order of regions from the input array accordingly to an ascending/descending sequence of their computed feature values.</summary>
	/// <param name="inRegions">Input regions.</param>
	/// <param name="inFeature">Region feature value to be computed.</param>
	/// <param name="inSortingOrder">Sorting order.</param>
	/// <param name="outSortedRegions">Regions sorted according to the computed feature values.</param>
	/// <param name="outSortedValues">Computed feature values.</param>
	AVL_FUNCTION void SortRegions
	(
		const atl::Array<avl::Region>&	inRegions,	
		avl::RegionFeature::Type		inFeature,	
		avl::SortingOrder::Type			inSortingOrder,	
		atl::Array<avl::Region>&		outSortedRegions,	
		atl::Optional<atl::Array<float>&>	outSortedValues = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the region from the input array that corresponds to the smallest computed feature value.</summary>
	/// <param name="inRegions">Input regions.</param>
	/// <param name="inFeature">Region feature value to be computed.</param>
	/// <param name="outRegion">Output region.</param>
	/// <param name="outValue">Computed feature value of the output region.</param>
	AVL_FUNCTION void GetMinimumRegion
	(
		const atl::Array<avl::Region>&	inRegions,	
		avl::RegionFeature::Type		inFeature,	
		avl::Region&					outRegion,
		atl::Optional<float&>			outValue = atl::NIL,	
		atl::Optional<int&>				outIndex = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the region from the input array that corresponds to the smallest computed feature value; returns NIL if the array or any region inside it is empty.</summary>
	/// <param name="inRegions">Input regions.</param>
	/// <param name="inFeature">Region feature value to be computed.</param>
	/// <param name="outRegion">Output region.</param>
	/// <param name="outValue">Computed feature value of the output region.</param>
	AVL_FUNCTION void GetMinimumRegion_OrNil
	(
		const atl::Array<avl::Region>&	inRegions,	
		avl::RegionFeature::Type		inFeature,	
		atl::Conditional<avl::Region>&	outRegion,
		atl::Conditional<float>&		outValue,	
		atl::Conditional<int>&			outIndex
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the region from the input array that corresponds to the largest computed feature value.</summary>
	/// <param name="inRegions">Input regions.</param>
	/// <param name="inFeature">Region feature value to be computed.</param>
	/// <param name="outRegion">Output region.</param>
	/// <param name="outValue">Computed feature value of the output region.</param>
	AVL_FUNCTION void GetMaximumRegion
	(
		const atl::Array<avl::Region>&	inRegions,	
		avl::RegionFeature::Type		inFeature,	
		avl::Region&					outRegion,
		atl::Optional<float&>			outValue = atl::NIL,	
		atl::Optional<int&>				outIndex = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the region from the input array that corresponds to the largest computed feature value; returns NIL if the array or any region inside it is empty.</summary>
	/// <param name="inRegions">Input regions.</param>
	/// <param name="inFeature">Region feature value to be computed.</param>
	/// <param name="outRegion">Output region.</param>
	/// <param name="outValue">Computed feature value of the output region.</param>
	AVL_FUNCTION void GetMaximumRegion_OrNil
	(
		const atl::Array<avl::Region>&	inRegions,	
		avl::RegionFeature::Type		inFeature,	
		atl::Conditional<avl::Region>&	outRegion,
		atl::Conditional<float>&		outValue,	
		atl::Conditional<int>&			outIndex
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_REGIONRELATIONS_H

