//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_SURFACEFEATURES_H
#define AVL_SURFACEFEATURES_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Surface/Surface.h"
#include "Geometry3D/Geometry3D.h"
#include "Image/Image.h"
#include "Region/Region.h"

namespace avl
{


	/// <summary>Computes region of locations where points are valid in a surface and where they are invalid.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="outValidPointsRegion">Region of locations where points are valid.</param>
	/// <param name="outInvalidPointsRegion">Region of locations where points are invalid.</param>
	AVL_FUNCTION void SurfaceValidPointsRegion
	(
		const avl::Surface&					inSurface,				
		atl::Optional<const avl::Region&>	inRoi,					
		avl::Region&						outValidPointsRegion,	
		avl::Region&						outInvalidPointsRegion	
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the mass center of surface points.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="outMassCenter">Mass center of the surface points.</param>
	AVL_FUNCTION void SurfaceMassCenter
	(
		const avl::Surface&					inSurface,		
		atl::Optional<const avl::Region&>	inRoi,			
		avl::Point3D&						outMassCenter	
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds the surface point with maximal Z coordinate.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="outMaximalPoint">Point with maximal Z coordinate.</param>
	AVL_FUNCTION void SurfaceMaximalPoint
	(
		const avl::Surface&					inSurface,		
		atl::Optional<const avl::Region&>	inRoi,			
		avl::Point3D&						outMaximalPoint	
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds the surface point with minimal Z coordinate.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="outMinimalPoint">Point with minimal Z coordinate.</param>
	AVL_FUNCTION void SurfaceMinimalPoint
	(
		const avl::Surface&					inSurface,		
		atl::Optional<const avl::Region&>	inRoi,			
		avl::Point3D&						outMinimalPoint	
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds the median Z coordinate of the surface.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="outMedian">Median Z coordinate of the surface points.</param>
	AVL_FUNCTION void SurfaceMedian
	(
		const avl::Surface&					inSurface,	
		atl::Optional<const avl::Region&>	inRoi,		
		float&								outMedian	
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the bounding box 3D of given surface; returns NIL if no valid point is present.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="outBoundingBox3D">Bounding box of the surface points.</param>
	AVL_FUNCTION void SurfaceBoundingBox_OrNil
	(
		const avl::Surface&					inSurface,			
		atl::Optional<const avl::Region&>	inRoi,				
		atl::Conditional<avl::Box3D>&		outBoundingBox3D	
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the bounding box 3D of given surface.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="outBoundingBox3D">Bounding box of the surface points.</param>
	AVL_FUNCTION void SurfaceBoundingBox
	(
		const avl::Surface&					inSurface,			
		atl::Optional<const avl::Region&>	inRoi,				
		avl::Box3D&							outBoundingBox3D	
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the surface area of given surface.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="outArea">Area of the input surface.</param>
	AVL_FUNCTION void SurfaceArea
	(
		const avl::Surface&	inSurface,	
		float&				outArea		
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the surface flatness i.e. how thick the surface is according to the input plane.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inPlane">Input plane.</param>
	/// <param name="outMaximumPoint1">Surface point with the largest distance on one side of the plane.</param>
	/// <param name="outMaximumPoint2">Surface point with the largest distance on the other side of the plane.</param>
	/// <param name="outMaximumDistance1">Distance of the first maximum point from the input plane.</param>
	/// <param name="outMaximumDistance2">Distance of the second maximum point from the input plane.</param>
	/// <param name="outFlatness">Difference between two extremal distances of surface points from the input plane.</param>
	AVL_FUNCTION void SurfaceFlatness
	(
		const avl::Surface&	inSurface,	
		atl::Optional<const avl::Region&>	inRoi,
		const avl::Plane3D&	inPlane,	
		avl::Point3D&		outMaximumPoint1,	
		avl::Point3D&		outMaximumPoint2,	
		float&				outMaximumDistance1,	
		float&				outMaximumDistance2,	
		float&				outFlatness			
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the image of the distances of the input surface points from a given plane.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inPlane">Input plane.</param>
	/// <param name="inResolution">Number of real-world units per one pixel. Default value: 1.0f.</param>
	AVL_FUNCTION void SurfaceToPlaneDistanceImage
	(
		const avl::Surface&	inSurface,	
		atl::Optional<const avl::Region&>	inRoi,
		const avl::Plane3D&	inPlane,	
		float				inResolution,	
		avl::Image&			outDistanceImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the volume of given surface.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="outVolume">Volume of the input surface.</param>
	AVL_FUNCTION void SurfaceVolume
	(
		const avl::Surface&	inSurface,	
		atl::Optional<const avl::Region&>	inRoi,
		const float			inZ,
		float&				outVolume	
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_SURFACEFEATURES_H

