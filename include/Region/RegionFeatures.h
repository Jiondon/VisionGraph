//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_REGIONFEATURES_H
#define AVL_REGIONFEATURES_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Enums/BoundingRectangleFeature.h"
#include "Enums/RectangleOrientation.h"
#include "Enums/CircularityMeasure.h"
#include "Enums/ProjectionDirection.h"
#include "Enums/RegionSkeletonMethod.h"
#include "Enums/RegionConnectivity.h"
#include "Path/Path.h"
#include "Profile/Profile.h"
#include "Region/Region.h"

namespace avl
{


	namespace RegionContourMode
	{
		enum Type
		{
			PixelCenters,
			PixelEdges
		};
	}

	namespace RegionMomentType
	{
		enum Type
		{
			_02,
			_11,
			_20
		};
	}


	/// <summary>Computes selected second-order moment of a region in regular and normalized ( divided by region area ) variant.</summary>
	/// <param name="inRegion">Input region.</param>
	AVL_FUNCTION void RegionMoment
	(
		const avl::Region&			inRegion,
		avl::RegionMomentType::Type	inMomentType,
		bool						inCentral,
		float&					outMoment,
		float&					outNormMoment
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the orientation of a region as an angle of value in range 0.0 - 180.0.</summary>
	/// <param name="inRegion">Input region.</param>
	AVL_FUNCTION void RegionOrientation
	(
		const avl::Region&	inRegion,
		float&			outOrientationAngle
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the elongation factor of a region ( perfect circle has minimal elongation equal 1.0 ).</summary>
	/// <param name="inRegion">Input region.</param>
	AVL_FUNCTION void RegionElongation
	(
		const avl::Region&	inRegion,
		float&			outElongation
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes axes of an ellipse having the same first and second order moments as the given region.</summary>
	/// <param name="inRegion">Input region.</param>
	AVL_FUNCTION void RegionEllipticAxes
	(
		const avl::Region&	inRegion,
		avl::Segment2D&		outMajorAxis,
		avl::Segment2D&		outMinorAxis
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes a point with coordinates equal to the average coordinates of the region's pixels.</summary>
	/// <param name="inRegion">Input region.</param>
	AVL_FUNCTION void RegionMassCenter
	(
		const avl::Region&	inRegion,
		avl::Point2D&		outMassCenter
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes a point with coordinates equal to the average coordinates of the region's pixels; returns NIL if the region is empty.</summary>
	/// <param name="inRegion">Input region.</param>
	AVL_FUNCTION void RegionMassCenter_OrNil
	(
		const avl::Region&				inRegion,
		atl::Conditional<avl::Point2D>&	outMassCenter
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the number of pixels contained in a region.</summary>
	/// <param name="inRegion">Input region.</param>
	AVL_FUNCTION void RegionArea
	(
		const avl::Region&	inRegion,
		int&				outArea
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the longest segment connecting two pixels contained in region and its length.</summary>
	/// <param name="inRegion">Input region.</param>
	AVL_FUNCTION void RegionDiameter
	(
		const avl::Region&				inRegion,
		atl::Optional<avl::Segment2D&>	outDiameter = atl::NIL,
		atl::Optional<float&>		outDiameterLength = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the length of the input region perimeter.</summary>
	/// <param name="inRegion">Input region.</param>
	AVL_FUNCTION void RegionPerimeterLength
	(
		const avl::Region&	inRegion,
		float&			outPerimeterLength
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the area of a region divided by the area of a circular region having the same feature.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inCircularityMeasure">Which algorithm should be used to compute a circle. Default value: RadiusPreserving.</param>
	/// <param name="diagCircle">Computed circle which area was compared.</param>
	AVL_FUNCTION void RegionCircularity
	(
		const avl::Region&					inRegion,
		const avl::CircularityMeasure::Type	inCircularityMeasure,	
		float&							outCircularity,
		avl::Circle2D&						diagCircle = atl::Dummy<avl::Circle2D>()				
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the area of a region divided by area of its convex hull.</summary>
	/// <param name="inRegion">Input region.</param>
	AVL_FUNCTION void RegionConvexity
	(
		const avl::Region&	inRegion,
		float&			outConvexity
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the area of a region divided by the area of its bounding rectangle.</summary>
	/// <param name="inRegion">Input region.</param>
	AVL_FUNCTION void RegionRectangularity
	(
		const avl::Region&	inRegion,
		float&			outRectangularity
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest box containing a region.</summary>
	/// <param name="inRegion">Input region.</param>
	AVL_FUNCTION void RegionBoundingBox
	(
		const avl::Region&	inRegion,
		avl::Box&			outBoundingBox
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest box containing a region; returns NIL if the region is empty.</summary>
	/// <param name="inRegion">Input region.</param>
	AVL_FUNCTION void RegionBoundingBox_OrNil
	(
		const avl::Region&			inRegion,
		atl::Conditional<avl::Box>&	outBoundingBox
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the number of holes in a region.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inConnectivity">Region connectivity semantics.</param>
	/// <param name="inMinHoleArea">Minimal area of a hole. Default value: 1.</param>
	/// <param name="inMaxHoleArea">Maximal area of a hole. Default value: atl::NIL.</param>
	AVL_FUNCTION void RegionNumberOfHoles
	(
		const avl::Region&				inRegion,
		avl::RegionConnectivity::Type	inConnectivity,	
		int								inMinHoleArea,	
		atl::Optional<int>				inMaxHoleArea,	
		int&							outNumberOfHoles
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates regions of the holes of the input region.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inConnectivity">Region connectivity semantics.</param>
	/// <param name="inMinHoleArea">Minimal area of a resulting hole. Default value: 1.</param>
	/// <param name="inMaxHoleArea">Maximal area of a resulting hole. Default value: atl::NIL.</param>
	AVL_FUNCTION void RegionHoles
	(
		const avl::Region&				inRegion,
		avl::RegionConnectivity::Type	inConnectivity,	
		int								inMinHoleArea,	
		atl::Optional<int>				inMaxHoleArea,	
		atl::Array<avl::Region> &		outHoles
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes an array of closed paths corresponding to the contours of the input region.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inRegionConnectivity">Region connectivity semantics. Default value: EightDirections.</param>
	AVL_FUNCTION void RegionContours
	(
		const avl::Region&					inRegion,
		const avl::RegionContourMode::Type	inContourMode,
		avl::RegionConnectivity::Type		inRegionConnectivity,  
		atl::Array<avl::Path>&				outContours
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest circle enclosing a region.</summary>
	/// <param name="inRegion">Input region.</param>
	AVL_FUNCTION void RegionBoundingCircle
	(
		const avl::Region&	inRegion,
		avl::Circle2D&		outBoundingCircle
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest circle enclosing a region; returns NIL if the region is empty.</summary>
	/// <param name="inRegion">Input region.</param>
	AVL_FUNCTION void RegionBoundingCircle_OrNil
	(
		const avl::Region&					inRegion,
		atl::Conditional<avl::Circle2D>&	outBoundingCircle
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest rectangle with the given orientation angle containing a region.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inAngle">Expected angle of the resulting rectangle.</param>
	/// <param name="outBoundingRectangle">Smallest bounding rectangle of the input region.</param>
	/// <param name="outCenter">Center of the bounding rectangle.</param>
	/// <param name="outLongSide">Length of the bounding rectangle long side.</param>
	/// <param name="outShortSide">Length of the bounding rectangle short side.</param>
	AVL_FUNCTION void RegionBoundingRectangle_FixedAngle
	(
		const avl::Region&				inRegion,				
		float						inAngle,				
		avl::Rectangle2D&				outBoundingRectangle,	
		atl::Optional<avl::Point2D&>	outCenter = atl::NIL,	
		atl::Optional<float&>		outLongSide = atl::NIL,	
		atl::Optional<float&>		outShortSide = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest rectangle with the given orientation angle containing a region; returns NIL if the region is empty.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inAngle">Expected angle of the resulting rectangle.</param>
	/// <param name="outBoundingRectangle">Smallest bounding rectangle of the input region.</param>
	/// <param name="outCenter">Center of the bounding rectangle.</param>
	/// <param name="outLongSide">Length of the bounding rectangle long side.</param>
	/// <param name="outShortSide">Length of the bounding rectangle short side.</param>
	AVL_FUNCTION void RegionBoundingRectangle_FixedAngle_OrNil
	(
		const avl::Region&					inRegion,				
		float								inAngle,				
		atl::Conditional<avl::Rectangle2D>&	outBoundingRectangle,	
		atl::Conditional<avl::Point2D>&		outCenter,				
		atl::Conditional<float>&			outLongSide,			
		atl::Conditional<float>&			outShortSide			
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest rectangle containing a region.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inBoundingRectangleFeature">Determines what kind of bounding rectangle will be computed. Default value: MinimalArea.</param>
	/// <param name="inReferenceAngle">The middle angle of the valid range of the output rectangle's angle. Default value: 0.0f.</param>
	/// <param name="inRectangleOrientation">Orientation of the output rectangle. Default value: Horizontal.</param>
	/// <param name="outBoundingRectangle">The smallest bounding rectangle of the input region.</param>
	/// <param name="outCenter">Center of the bounding rectangle.</param>
	/// <param name="outLongSide">Length of the bounding rectangle long side.</param>
	/// <param name="outShortSide">Length of the bounding rectangle short side.</param>
	AVL_FUNCTION void RegionBoundingRectangle
	(
		const avl::Region&					inRegion,					
		avl::BoundingRectangleFeature::Type	inBoundingRectangleFeature,	
		float								inReferenceAngle,			
		avl::RectangleOrientation::Type		inRectangleOrientation,		
		avl::Rectangle2D&					outBoundingRectangle,		
		atl::Optional<avl::Point2D&>		outCenter = atl::NIL,		
		atl::Optional<float&>				outLongSide = atl::NIL,		
		atl::Optional<float&>				outShortSide = atl::NIL		
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest rectangle containing a region; returns NIL if the region is empty.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inBoundingRectangleFeature">Determines what kind of bounding rectangle will be computed. Default value: MinimalArea.</param>
	/// <param name="inReferenceAngle">The middle angle of the valid range of the output rectangle's angle. Default value: 0.0f.</param>
	/// <param name="inRectangleOrientation">Orientation of the output rectangle. Default value: Horizontal.</param>
	/// <param name="outBoundingRectangle">Smallest bounding rectangle of the input region.</param>
	/// <param name="outCenter">Center of the bounding rectangle.</param>
	/// <param name="outLongSide">Length of the bounding rectangle long side.</param>
	/// <param name="outShortSide">Length of the bounding rectangle short side.</param>
	AVL_FUNCTION void RegionBoundingRectangle_OrNil
	(
		const avl::Region&					inRegion,					
		avl::BoundingRectangleFeature::Type	inBoundingRectangleFeature,	
		float								inReferenceAngle,			
		avl::RectangleOrientation::Type		inRectangleOrientation,		
		atl::Conditional<avl::Rectangle2D>&	outBoundingRectangle,		
		atl::Conditional<avl::Point2D>&		outCenter,					
		atl::Conditional<float>&			outLongSide,				
		atl::Conditional<float>&			outShortSide				
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest parallelogram containing a region.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inBoundingParallelogramFeature">Determines what kind of bounding parallelogram will be computed. Default value: MinimalArea.</param>
	/// <param name="outBoundingParallelogram">Smallest bounding parallelogram of the input points.</param>
	/// <param name="outCenter">Center of the bounding parallelogram.</param>
	/// <param name="outLongSide">Length of the bounding parallelogram long side.</param>
	/// <param name="outShortSide">Length of the bounding parallelogram short side.</param>
	/// <param name="outAngle">Angle of the bounding parallelogram.</param>
	AVL_FUNCTION void RegionBoundingParallelogram
	(
		const avl::Region&					inRegion,					
		avl::BoundingRectangleFeature::Type	inBoundingParallelogramFeature,	
		avl::Path&							outBoundingParallelogram,	
		atl::Optional<avl::Point2D&>		outCenter = atl::NIL,		
		atl::Optional<float&>				outLongSide = atl::NIL,		
		atl::Optional<float&>				outShortSide = atl::NIL,	
		atl::Optional<float&>				outAngle = atl::NIL			
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes an array of paths corresponding to the skeleton of the input region.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inRegionSkeletonMethod">Default value: TwelveConnected.</param>
	AVL_FUNCTION void RegionMedialAxis
	(
		const avl::Region&				inRegion,
		avl::RegionSkeletonMethod::Type	inRegionSkeletonMethod,
		atl::Array<avl::Path>&			outSkeletonPaths
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the largest box contained in a region.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inMinAspectRatio">Minimal aspect ratio of found box. Default value: 0.0f.</param>
	/// <param name="inMaxAspectRatio">Maximal aspect ratio of found box (reciprocal of inMinAspectRatio by default). Default value: atl::NIL.</param>
	/// <param name="inMinWidth">Minimal width of found box. Default value: 1.</param>
	/// <param name="inMaxWidth">Maximal width of found box. Default value: atl::NIL.</param>
	/// <param name="inMinHeight">Minimal height of found box. Default value: 1.</param>
	/// <param name="inMaxHeight">Maximal height of found box. Default value: atl::NIL.</param>
	/// <param name="outBox">Found box with largest area.</param>
	AVL_FUNCTION void RegionInscribedBox
	(
		const avl::Region&			inRegion,
		const float				inMinAspectRatio,	
		atl::Optional<float>	inMaxAspectRatio,	
		const int					inMinWidth,			
		atl::Optional<int>			inMaxWidth,			
		const int					inMinHeight,		
		atl::Optional<int>			inMaxHeight,		
		atl::Conditional<avl::Box>&	outBox				
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the profile of the region pixel count in consecutive rows or columns.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inProjectionDirection">Direction in which the pixel occurrences are counted, 'horizontal' means summation row after row, 'vertical' indicates summation column after column.</param>
	/// <param name="outProfile">Profile of pixel count in consecutive rows/columns.</param>
	AVL_FUNCTION void RegionProjection
	(
		const avl::Region&						inRegion, 
		const avl::ProjectionDirection::Type	inProjectionDirection, 
		avl::Profile&							outProfile 
	)
	THROW_AVL_ERRORS;

	/// <summary>Internal character normalization.</summary>
	AVL_FUNCTION void RegionSimilarity
	(
		const avl::Size&	inNormalizationSize,
		const avl::Region&	inA,
		const avl::Region&	inB,
		float&			outFactor
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the lengths of horizontal sequences of locations that constitute the input region.</summary>
	/// <param name="inRegion">Input region.</param>
	AVL_FUNCTION void RegionPointRunLengths
	(
		const avl::Region&	inRegion,
		atl::Array< int >&	outPointRunLengths
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest rectangle containing a region.</summary>
	/// <param name="inRegion">Input array of points.</param>
	/// <param name="inRectangleOrientation">Expected orientation of the resulting rectangle. Default value: atl::NIL.</param>
	/// <param name="inBoundingRectangleFeature">Determines what kind of bounding rectangle will be computed. Default value: MinimalArea.</param>
	/// <param name="outBoundingRectangle">The smallest bounding rectangle of the input region.</param>
	/// <param name="outCenter">Center of the bounding rectangle.</param>
	/// <param name="outLongSide">Length of the bounding rectangle long side.</param>
	/// <param name="outShortSide">Length of the bounding rectangle short side.</param>
	AVL_FUNCTION void RegionBoundingRectangle_Deprecated
	(
		const avl::Region&				inRegion,				
		atl::Optional<float>		inRectangleOrientation, 
		avl::BoundingRectangleFeature::Type	inBoundingRectangleFeature,	
		avl::Rectangle2D&				outBoundingRectangle,	
		atl::Optional<avl::Point2D&>	outCenter = atl::NIL,	
		atl::Optional<float&>		outLongSide = atl::NIL,	
		atl::Optional<float&>		outShortSide = atl::NIL	
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_REGIONFEATURES_H

