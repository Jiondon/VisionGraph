//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_AVLCONVERSIONS_H
#define AVL_AVLCONVERSIONS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/AtlString.h"
#include "ATL/Array.hxx"
#include "Geometry/Geometry.h"
#include "Geometry3D/Geometry3D.h"
#include "Point3DGrid/Point3DGrid.h"
#include "Surface/Surface.h"
#include "Surface/SurfaceFormat.h"
#include "Histogram/Histogram.h"
#include "Image/Image.h"
#include "Image/ImageFormat.h"
#include "Path/Path.h"
#include "Profile/Profile.h"
#include "Region/Region.h"
#include "Region/RegionOfInterest.h"
#include "ComputerVision/1DEdgeDetection/ScanStructs.h"
#include "ComputerVision/ImageAnalysis/ShapeRegion.h"

namespace avl
{


	/// <summary>Converts an integer value to pixel.</summary>
	AVL_FUNCTION void IntegerToPixel
	(
		const int		inValue,
		avl::Pixel&		outPixel
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a real value to pixel.</summary>
	AVL_FUNCTION void RealToPixel
	(
		const float	inValue,
		avl::Pixel&		outPixel
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts an array of real values to an array of pixels.</summary>
	AVL_FUNCTION void RealArrayToPixelArray
	(
		const atl::Array<float>&	inValues,
		atl::Array<avl::Pixel>&			outPixels
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a location to its center point.</summary>
	AVL_FUNCTION void LocationToPoint2D
	(
		const avl::Location&	inLocation,
		avl::Point2D&			outPoint
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a point to a location its contained within.</summary>
	AVL_FUNCTION void Point2DToLocation
	(
		const avl::Point2D&		inPoint,
		avl::Location&			outLocation
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts an array of locations to an array of points.</summary>
	AVL_FUNCTION void LocationArrayToPoint2DArray
	(
		const atl::Array<avl::Location>&	inLocationArray,
		atl::Array<avl::Point2D>&			outPointArray
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts an array of points to an array of locations.</summary>
	AVL_FUNCTION void Point2DArrayToLocationArray
	(
		const atl::Array<avl::Point2D>&	inPointArray,
		atl::Array<avl::Location>&		outLocationArray 
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a region to an image.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void RegionToImage
	(
		const avl::Region&	inRegion,
		avl::Image&			outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a rectangle to region of interest.</summary>
	AVL_FUNCTION void Rectangle2DToRegionOfInterest
	(
		const avl::Rectangle2D&			inRectangle,
		avl::RegionOfInterest&			outRegionOfInterest
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a circle to region of interest.</summary>
	AVL_FUNCTION void Circle2DToRegionOfInterest
	(
		const avl::Circle2D&			inCircle,
		avl::RegionOfInterest&			outRegionOfInterest
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a region to region of interest.</summary>
	/// <param name="inRegion">Input region.</param>
	AVL_FUNCTION void RegionToRegionOfInterest
	(
		const avl::Region&				inRegion,
		avl::RegionOfInterest&			outRegionOfInterest
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a box to a rectangle.</summary>
	AVL_FUNCTION void BoxToRectangle2D
	(
		const avl::Box&		inBox,
		avl::Rectangle2D&	outRectangle
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a path to an array of points.</summary>
	/// <param name="inPath">Input path.</param>
	AVL_FUNCTION void PathToPoint2DArray
	(
		const avl::Path&			inPath,
		atl::Array<avl::Point2D >&	outPoints
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a segment to a path.</summary>
	/// <param name="outPath">Output path.</param>
	AVL_FUNCTION void Segment2DToPath
	(
		const avl::Segment2D&	inSegment,
		avl::Path&				outPath
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a profile to an array of real numbers.</summary>
	/// <param name="inProfile">Input profile.</param>
	AVL_FUNCTION void ProfileToRealArray
	(
		const avl::Profile&			inProfile,
		atl::Array<float>&		outArray
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts an array of real numbers to a profile.</summary>
	/// <param name="outProfile">Output profile.</param>
	AVL_FUNCTION void RealArrayToProfile
	(
		const atl::Array<float>&	inArray,
		avl::Profile&				outProfile
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a profile to an array of points.</summary>
	/// <param name="inProfile">Input profile.</param>
	AVL_FUNCTION void ProfileToPoint2DArray
	(
		const avl::Profile&			inProfile,
		atl::Array<avl::Point2D>&	outPoints
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a segment to a line.</summary>
	AVL_FUNCTION void Segment2DToLine2D
	(
		const avl::Segment2D&		inSegment,
		avl::Line2D&				outLine
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a stripe to a segment.</summary>
	AVL_FUNCTION void Stripe1DToSegment2D
	(
		const avl::Stripe1D&	inStripe,
		avl::Segment2D&			outSegment
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a gap to a segment.</summary>
	AVL_FUNCTION void Gap1DToSegment2D
	(
		const avl::Gap1D&	inGap,
		avl::Segment2D&		outSegment
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts an image to an image format.</summary>
	/// <param name="inImage">Input image.</param>
	AVL_FUNCTION void ImageToImageFormat
	(
		const avl::Image&	inImage,
		avl::ImageFormat&	outImageFormat
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a surface to a surface format.</summary>
	AVL_FUNCTION void SurfaceToSurfaceFormat
	(
		const avl::Surface&		inSurface,
		avl::SurfaceFormat&	outSurfaceFormat
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a rectangle to a shape region.</summary>
	AVL_FUNCTION void Rectangle2DToShapeRegion
	(
		const avl::Rectangle2D&	inRectangle,
		avl::ShapeRegion&		outShapeRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a circle to a shape region.</summary>
	AVL_FUNCTION void Circle2DToShapeRegion
	(
		const avl::Circle2D&	inCircle,
		avl::ShapeRegion&		outShapeRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a box to a shape region.</summary>
	AVL_FUNCTION void BoxToShapeRegion
	(
		const avl::Box&		inBox,
		avl::ShapeRegion&	outShapeRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a point in 3D to a point in 2D by ignoring its Z coordinate.</summary>
	AVL_FUNCTION void Point3DToPoint2D
	(
		const avl::Point3D&	inPoint3D,
		avl::Point2D&		outPoint2D
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts an array of points in 3D to an array of points in 2D by ignoring their Z coordinates.</summary>
	AVL_FUNCTION void Point3DArrayToPoint2DArray
	(
		const atl::Array<avl::Point3D>&	inPoint3DArray,
		atl::Array<avl::Point2D>&		outPoint2DArray 
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a grid of points to an array of points.</summary>
	AVL_FUNCTION void Point3DGridToPoint3DArray
	(
		const avl::Point3DGrid&		inPoint3DGrid,
		atl::Array<avl::Point3D>&	outPoint3DArray
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a surface object to a grid of points.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="outPoint3DGrid">Output point grid.</param>
	AVL_FUNCTION void SurfaceToPoint3DGrid
	(
		const avl::Surface&	inSurface,		
		avl::Point3DGrid&	outPoint3DGrid	
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a surface object to an array of points.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="outPoint3DArray">Output point array.</param>
	AVL_FUNCTION void SurfaceToPoint3DArray
	(
		const avl::Surface&			inSurface,		
		atl::Array<avl::Point3D>&	outPoint3DArray	
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a surface object to an image.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void SurfaceToImage
	(
		const avl::Surface&	inSurface,	
		avl::Image&			outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a StringLabel object to a String.</summary>
	AVL_FUNCTION void StringLabelToString
	(
		const avl::StringLabel&	inStringLabel,
		atl::String&			outString
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a path to an array of line segments.</summary>
	/// <param name="inPath">Input path.</param>
	AVL_FUNCTION void PathToSegment2DArray_Deprecated
	(
		const avl::Path&				inPath,
		atl::Array<avl::Segment2D >&	outSegments
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a histogram to an array of its bin values.</summary>
	/// <param name="inHistogram">Input histogram.</param>
	AVL_FUNCTION void HistogramToIntegerArray_Deprecated
	(
		const avl::Histogram&	inHistogram,
		atl::Array<int>&		outArray
		)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_AVLCONVERSIONS_H

