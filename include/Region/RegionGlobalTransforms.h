//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_REGIONGLOBALTRANSFORMS_H
#define AVL_REGIONGLOBALTRANSFORMS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Region/Region.h"
#include "Enums/RegionConnectivity.h"
#include "Enums/RegionFeature.h"

namespace avl
{


	/// <summary>Computes the smallest convex region containing the input region.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void RegionConvexHull
	(
		const avl::Region&	inRegion,
		avl::Region&		outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Removes boundary pixels from a region.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inConnectivity">Type of connectivity used for the region foreground.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void RegionInteriors
	(
		const avl::Region& inRegion,
		avl::RegionConnectivity::Type inConnectivity,	
		avl::Region& outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Removes interior pixels from a region.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inConnectivity">Type of connectivity used for the region foreground.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void RegionBoundaries
	(
		const avl::Region&				inRegion,
		avl::RegionConnectivity::Type	inConnectivity, 
		avl::Region&					outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the top, right, bottom and left boundaries of the input region.</summary>
	/// <param name="inRegion">Input region.</param>
	AVL_FUNCTION void RegionOuterBoundaries
	(
		const avl::Region&				inRegion,
		atl::Array< avl::Location >&	outTopBoundary,
		atl::Array< avl::Location >&	outRightBoundary,
		atl::Array< avl::Location >&	outBottomBoundary,
		atl::Array< avl::Location >&	outLeftBoundary
	)
	THROW_AVL_ERRORS;

	/// <summary>Splits a region into an array of regions corresponding to its connected components.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inConnectivity">Type of connectivity used for the region foreground.</param>
	/// <param name="inMinBlobArea">Minimal area of a resulting blob. Default value: 1.</param>
	/// <param name="inMaxBlobArea">Maximal area of a resulting blob. Default value: atl::NIL.</param>
	/// <param name="inRemoveBoundaryBlobs">Flag indicating whether the blobs on border of the input region should be removed or not. Default value: False.</param>
	/// <param name="diagBlobAreas">Areas of extracted blobs.</param>
	AVL_FUNCTION void SplitRegionIntoBlobs
	(
		const avl::Region&				inRegion,
		avl::RegionConnectivity::Type	inConnectivity,			
		const int						inMinBlobArea,			
		atl::Optional<int>				inMaxBlobArea,			
		bool							inRemoveBoundaryBlobs,	
		atl::Array<avl::Region>&		outBlobs,
		atl::Array<int>&				diagBlobAreas = atl::Dummy< atl::Array<int> >()			
	)
	THROW_AVL_ERRORS;

	/// <summary>Extends the input region so that it contains also all the pixels previously lying in its holes.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inConnectivity">Type of connectivity used for the region foreground.</param>
	/// <param name="inMinHoleArea">Minimal area of a hole to be filled.</param>
	/// <param name="inMaxHoleArea">Maximal area of a hole to be filled. Default value: atl::NIL.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void FillRegionHoles
	(
		const avl::Region&				inRegion,
		avl::RegionConnectivity::Type	inConnectivity,	
		int								inMinHoleArea,	
		atl::Optional<int>				inMaxHoleArea,	
		avl::Region&					outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Splits a region into an array of regions. Operates by merging blobs in accordance to the inMaxDistance parameter.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inMaxDistance">Default value: 5.</param>
	/// <param name="inDistanceBalance">Defines how much important the distance between regions in x coordinate is according to distance in y coordinate.</param>
	/// <param name="inMinComponentArea">Minimal area of a resulting component. Default value: 1.</param>
	/// <param name="inMaxComponentArea">Maximal area of a resulting component. Default value: atl::NIL.</param>
	/// <param name="inRemoveBoundaryBlobs">Flag indicating whether the blobs on border of the input region should be removed or not. Default value: False.</param>
	AVL_FUNCTION void SplitRegionIntoComponents
	(
		const avl::Region&								inRegion,
		atl::Optional<int>								inMaxDistance,
		float										inDistanceBalance,		
		atl::Optional<float>						inMaxJointDiameter,
		atl::Optional<int>								inMaxJointWidth,
		atl::Optional<int>								inMaxJointHeight,
		const int										inMinComponentArea,		
		atl::Optional<int>								inMaxComponentArea,		
		bool											inRemoveBoundaryBlobs,	
		atl::Array<avl::Region>&						outComponents
	)
	THROW_AVL_ERRORS;

	/// <summary>Splits a region into a fixed-size array of regions.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inMaxDistance">Default value: 5.</param>
	/// <param name="inDistanceBalance">Defines how much important the distance between regions in x coordinate is according to distance in y coordinate.</param>
	/// <param name="inRemoveBoundaryBlobs">Flag indicating whether the blobs on border of the input region should be removed or not. Default value: False.</param>
	AVL_FUNCTION void SplitRegionIntoExactlyNComponents
	(
		const avl::Region&							inRegion,
		int											inComponentCount,
		atl::Optional<int>							inMaxDistance,
		float									inDistanceBalance,		
		atl::Optional<float>					inMaxJointDiameter,
		atl::Optional<int>							inMaxJointWidth,
		atl::Optional<int>							inMaxJointHeight,
		bool										inRemoveBoundaryBlobs,	
		atl::Conditional<atl::Array<avl::Region> >&	outComponents
	)
	THROW_AVL_ERRORS;

	/// <summary>Removes from a region the pixels that lie very close to the region's borders.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inMarginX">Horizontal margin from the region border.</param>
	/// <param name="inMarginY">Vertical margin from the region border.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void CropBordersFromRegion
	(
		const avl::Region&	inRegion,
		int					inMarginX,	
		int					inMarginY,	
		avl::Region&		outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Removes regions not fulfilling specific conditions</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inConnectivity">Type of connectivity used for the region foreground.</param>
	/// <param name="inFeature">Region feature value to be computed.</param>
	/// <param name="inMinimum">Minimal value of the considered feature. Default value: 1.0f.</param>
	/// <param name="inMaximum">Maximal value of the considered feature. Default value: atl::NIL.</param>
	/// <param name="inRemoveBoundaryBlobs">Flag indicating whether the blobs on border of the input region should be removed or not. Default value: False.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void RemoveRegionBlobs
	(
		const avl::Region&				inRegion,
		avl::RegionConnectivity::Type	inConnectivity,			
		avl::RegionFeature::Type		inFeature,				
		atl::Optional<float>			inMinimum,				
		atl::Optional<float>			inMaximum,				
		bool							inRemoveBoundaryBlobs,	
		avl::Region&					outRegion				
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_REGIONGLOBALTRANSFORMS_H

