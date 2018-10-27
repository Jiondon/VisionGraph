//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVS_IMAGEDRAWING_H
#define AVS_IMAGEDRAWING_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ComputerVision/ImageAnalysis/ShapeRegion.h"
#include "Path/Path.h"
#include "Image/Image.h"
#include "Image/DrawingStyle.h"
#include "Basic/Types.h"
#include "Enums/Anchor2D.h"
#include "Geometry/Geometry.h"
#include "Region/RegionOfInterest.h"

namespace avl
{


	namespace MarkerType
	{
		enum Type
		{
			Arrow,
			None,
			TwoArrows,
			Circle,
			Cross,
			Square
		};
	}


	/// <summary>Draws a circle on an image.</summary>
	AVL_FUNCTION void DrawCircle
	(
		avl::Image&							ioImage,
		const avl::Circle2D&				inCircle,
		atl::Optional<const avl::CoordinateSystem2D&>	inCircleAlignment,
		const avl::Pixel&					inColor,
		const avl::DrawingStyle&			inDrawingStyle
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws an ellipse on an image.</summary>
	AVL_FUNCTION void DrawEllipse
	(
		avl::Image&							ioImage,
		const avl::Rectangle2D&				inEllipse,
		atl::Optional<const avl::CoordinateSystem2D&>	inEllipseAlignment,
		const avl::Pixel&					inColor,
		const avl::DrawingStyle&			inDrawingStyle
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws an arc on an image.</summary>
	AVL_FUNCTION void DrawArc
	(
		avl::Image&							ioImage,
		const avl::Arc2D&					inArc,
		atl::Optional<const avl::CoordinateSystem2D&>	inArcAlignment,
		const avl::Pixel&					inColor,
		const avl::DrawingStyle&			inDrawingStyle
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws a segment on an image.</summary>
	/// <param name="inMarkerType">Default value: Arrow.</param>
	/// <param name="inMarkerSize">Default value: 5.0f.</param>
	AVL_FUNCTION void DrawSegment
	(
		avl::Image&							ioImage,
		const avl::Segment2D&				inSegment,
		atl::Optional<const avl::CoordinateSystem2D&>	inSegmentAlignment,
		const avl::Pixel&					inColor,
		const avl::DrawingStyle&			inDrawingStyle,
		const avl::MarkerType::Type			inMarkerType,
		const float						inMarkerSize
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws a vector at an associated initial point on an image.</summary>
	/// <param name="inHeadSize">Default value: 5.0f.</param>
	AVL_FUNCTION void DrawVector
	(
		avl::Image&							ioImage,
		const avl::Vector2D&				inVector,
		const avl::Point2D&					inInitialPoint,
		atl::Optional<const avl::CoordinateSystem2D&>	inVectorAlignment,
		const avl::Pixel&					inColor,
		const avl::DrawingStyle&			inDrawingStyle,
		const float						inHeadSize
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws a line on an image.</summary>
	AVL_FUNCTION void DrawLine
	(
		avl::Image&							ioImage,
		const avl::Line2D&					inLine,
		atl::Optional<const avl::CoordinateSystem2D&>	inLineAlignment,
		const avl::Pixel&					inColor,
		const avl::DrawingStyle&			inDrawingStyle
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws a path on an image.</summary>
	/// <param name="inPath">Input path.</param>
	AVL_FUNCTION void DrawPath
	(
		avl::Image&							ioImage,
		const avl::Path&					inPath,
		atl::Optional<const avl::CoordinateSystem2D&>	inPathAlignment,
		const avl::Pixel&					inColor,
		const avl::DrawingStyle&			inDrawingStyle
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws a point on an image.</summary>
	AVL_FUNCTION void DrawPoint
	(
		avl::Image&					ioImage,
		const avl::Point2D&			inPoint,
		atl::Optional<const avl::CoordinateSystem2D&>	inPointAlignment,
		const avl::Pixel&			inColor,
		const avl::DrawingStyle&	inDrawingStyle
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws a rectangle on an image.</summary>
	AVL_FUNCTION void DrawRectangle
	(
		avl::Image&					ioImage,
		const avl::Rectangle2D&		inRectangle,
		atl::Optional<const avl::CoordinateSystem2D&>	inRectangleAlignment,
		const avl::Pixel&			inColor,
		const avl::DrawingStyle&	inDrawingStyle
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws a pair of arrows representing a coordinate system on an image.</summary>
	/// <param name="inArrowSize">Default value: 5.0f.</param>
	/// <param name="inPixelScale">How many pixels long will be axis of a coordinate system with unit scale. Default value: 20.0f.</param>
	AVL_FUNCTION void DrawCoordinateSystem
	(
		avl::Image&							ioImage,
		const avl::CoordinateSystem2D&		inCoordinateSystem,
		atl::Optional<const avl::CoordinateSystem2D&>	inCoordinateSystemAlignment,
		const avl::Pixel&					inColor,
		const avl::DrawingStyle&			inDrawingStyle,
		const float						inArrowSize,
		const float						inPixelScale 
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws a box on an image.</summary>
	AVL_FUNCTION void DrawBox
	(
		avl::Image&			ioImage,
		const avl::Box&		inBox,
		const avl::Pixel&	inColor,
		const float		inOpacity
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws a region on an image.</summary>
	/// <param name="inRegion">Input region.</param>
	AVL_FUNCTION void DrawRegion
	(
		avl::Image&										ioImage,
		const avl::Region&								inRegion,
		atl::Optional<const avl::CoordinateSystem2D&>	inRegionAlignment,
		const avl::Pixel&								inColor,
		const float										inOpacity
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws a region of interest on an image.</summary>
	/// <param name="inRoi">Range of pixels to be processed.</param>
	AVL_FUNCTION void DrawRegionOfInterest
	(
		avl::Image&										ioImage,
		const avl::RegionOfInterest&					inRoi,
		atl::Optional<const avl::CoordinateSystem2D&>	inRegionAlignment,
		const avl::Pixel&								inColor,
		const float										inOpacity
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws a string on an image.</summary>
	/// <param name="inLocationAnchor">Default value: MiddleCenter.</param>
	/// <param name="inSize">Height of a character. Default value: 12.0f.</param>
	/// <param name="inOrientationAngle">Default value: 0.0f.</param>
	AVL_FUNCTION void DrawString
	(
		avl::Image&										ioImage,
		const atl::String&								inString,
		const avl::Location&							inLocation,
		atl::Optional<const avl::CoordinateSystem2D&>	inLocationAlignment,
		const avl::Anchor2D::Type						inLocationAnchor,
		const avl::Pixel&								inColor,
		const avl::DrawingStyle&						inDrawingStyle,
		float										inSize,				
		float										inOrientationAngle,
		const atl::Optional<avl::Pixel>&				inBackgroundColor
	)
	THROW_AVL_ERRORS;

	namespace MetricUnit
	{  
		enum Type
		{
			Millimetres,
			Centimetres,
			Decimetres,
			Metres
		};
	}


	/// <summary>Draws a dimension line on an image.</summary>
	/// <param name="inHeadSize">Default value: 5.0f.</param>
	/// <param name="inScale">px / mm. Default value: 1.0f.</param>
	/// <param name="inMetricUnit">Default value: avl::MetricUnit::Millimeters.</param>
	/// <param name="inTextSize">Default value: 12.0f.</param>
	AVL_FUNCTION void DrawDimensionLine
	(
		avl::Image&					ioImage,
		const avl::Segment2D&		inSegment,
		atl::Optional<const avl::CoordinateSystem2D&>	inSegmentAlignment,
		const avl::Pixel&			inColor,
		const avl::DrawingStyle&	inDrawingStyle,
		float					inHeadSize,
		float					inScale, 
		avl::MetricUnit::Type		inMetricUnit,
		float					inTextSize = 12
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws a ShapeRegion object on an image.</summary>
	AVL_FUNCTION void DrawShapeRegion
	(
		avl::Image&					ioImage,
		const avl::ShapeRegion&		inShapeRegion,
		atl::Optional<const avl::CoordinateSystem2D&>	inShapeRegionAlignment,
		const avl::Pixel&			inColor,
		const avl::DrawingStyle&	inDrawingStyle
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws an image on another one.</summary>
	/// <param name="inDrawnImage">Image to be pasted on ioImage.</param>
	/// <param name="inLocation">Location at which the image will be pasted.</param>
	AVL_FUNCTION void DrawImage
	(
		avl::Image&				ioImage,
		const avl::Image&		inDrawnImage,	
		const avl::Location&	inLocation		
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws an array of images on an image.</summary>
	/// <param name="inDrawnImages">Images to be pasted on ioImage.</param>
	/// <param name="inLocations">Locations at which the image will be pasted.</param>
	AVL_FUNCTION void DrawImages
	(
		avl::Image&																ioImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Image> > >&		inDrawnImages,	
		const atl::Conditional<atl::Array<atl::Conditional<avl::Location> > >&	inLocations		
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws an image as a tile on an image considered to be a grid of tiles.</summary>
	/// <param name="inTileImage">Image to be pasted to the grid.</param>
	/// <param name="inColumnIndex">Column index in the grid.</param>
	/// <param name="inRowIndex">Row index in the grid.</param>
	AVL_FUNCTION void DrawGridImage
	(
		avl::Image&			ioImage,
		const avl::Image&	inTileImage,	
		int					inColumnIndex,	
		int					inRowIndex		
	)
	THROW_AVL_ERRORS;

} // namespace avl

namespace avs
{

	/// <summary>Draws circles on an image with a single color.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inCircles">Default value: { }.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawCircles_SingleColor
	(
		const avl::Image&					inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Circle2D> > >&	inCircles,
		atl::Optional<const avl::CoordinateSystem2D&>	inCircleAlignment,
		const avl::Pixel&					inColor,
		const avl::DrawingStyle&			inDrawingStyle,
		const bool							inForceRgb, 
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws circles on an image with two colors, depending on the status of each circle (usually: green or red for pass/fail status).</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inCircles">Default value: { }.</param>
	/// <param name="inColorIfTrue">Default value: Pixel ( X: 0.0f Y: 200.0f Z: 0.0f W: 0.0f ).</param>
	/// <param name="inColorIfFalse">Default value: Pixel ( X: 200.0f Y: 0.0f Z: 0.0f W: 0.0f ).</param>
	/// <param name="inConditions">Default value: { }.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawCircles_TwoColors
	(
		const avl::Image&					inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Circle2D> > >&	inCircles,
		atl::Optional<const avl::CoordinateSystem2D&>	inCircleAlignment,
		const avl::Pixel&					inColorIfTrue,
		const avl::Pixel&					inColorIfFalse,
		const atl::Conditional<atl::Array<atl::Conditional<bool> > >&	inConditions,
		const avl::DrawingStyle&			inDrawingStyle,
		const bool							inForceRgb, 
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws circles on an image with multiple colors.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inCircles">Default value: { }.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawCircles_Palette
	(
		const avl::Image&								inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Circle2D> > >&	inCircles,
		atl::Optional<const avl::CoordinateSystem2D&>	inCircleAlignment,
		const atl::Optional<atl::Array<avl::Pixel> >&	inColors,
		const avl::DrawingStyle&						inDrawingStyle,
		const bool										inForceRgb,	
		avl::Image&										outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws ellipses on an image with a single color.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inEllipses">Default value: { }.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawEllipses_SingleColor
	(
		const avl::Image&										inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Rectangle2D> > >&	inEllipses,
		atl::Optional<const avl::CoordinateSystem2D&>			inEllipseAlignment,
		const avl::Pixel&										inColor,
		const avl::DrawingStyle&								inDrawingStyle,
		const bool												inForceRgb, 
		avl::Image&												outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws ellipses on an image with two colors, depending on the status of each ellipse (usually: green or red for pass/fail status).</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inEllipses">Default value: { }.</param>
	/// <param name="inColorIfTrue">Default value: Pixel ( X: 0.0f Y: 200.0f Z: 0.0f W: 0.0f ).</param>
	/// <param name="inColorIfFalse">Default value: Pixel ( X: 200.0f Y: 0.0f Z: 0.0f W: 0.0f ).</param>
	/// <param name="inConditions">Default value: { }.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawEllipses_TwoColors
	(
		const avl::Image&					inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Rectangle2D> > >&	inEllipses,
		atl::Optional<const avl::CoordinateSystem2D&>	inEllipseAlignment,
		const avl::Pixel&					inColorIfTrue,
		const avl::Pixel&					inColorIfFalse,
		const atl::Conditional< atl::Array<atl::Conditional<bool> > >&	inConditions,
		const avl::DrawingStyle&			inDrawingStyle,
		const bool							inForceRgb, 
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws ellipses on an image with multiple colors.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inEllipses">Default value: { }.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawEllipses_Palette
	(
		const avl::Image&								inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Rectangle2D> > >&	inEllipses,
		atl::Optional<const avl::CoordinateSystem2D&>	inEllipseAlignment,
		const atl::Optional<atl::Array<avl::Pixel> >&	inColors,
		const avl::DrawingStyle&						inDrawingStyle,
		const bool										inForceRgb,	
		avl::Image&										outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws arcs on an image with a single color.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inArcs">Default value: { }.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawArcs_SingleColor
	(
		const avl::Image&					inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Arc2D> > >&	inArcs,
		atl::Optional<const avl::CoordinateSystem2D&>	inArcAlignment,
		const avl::Pixel&					inColor,
		const avl::DrawingStyle&			inDrawingStyle,
		const bool							inForceRgb, 
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws arcs on an image with two colors, depending on the status of each arc (usually: green or red for pass/fail status).</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inArcs">Default value: { }.</param>
	/// <param name="inColorIfTrue">Default value: Pixel ( X: 0.0f Y: 200.0f Z: 0.0f W: 0.0f ).</param>
	/// <param name="inColorIfFalse">Default value: Pixel ( X: 200.0f Y: 0.0f Z: 0.0f W: 0.0f ).</param>
	/// <param name="inConditions">Default value: { }.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawArcs_TwoColors
	(
		const avl::Image&					inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Arc2D> > >&	inArcs,
		atl::Optional<const avl::CoordinateSystem2D&>	inArcAlignment,
		const avl::Pixel&					inColorIfTrue,
		const avl::Pixel&					inColorIfFalse,
		const atl::Conditional< atl::Array<atl::Conditional<bool> > >&	inConditions,
		const avl::DrawingStyle&			inDrawingStyle,
		const bool							inForceRgb, 
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws arcs on an image with multiple colors.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inArcs">Default value: { }.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawArcs_Palette
	(
		const avl::Image&								inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Arc2D> > >&	inArcs,
		atl::Optional<const avl::CoordinateSystem2D&>	inArcAlignment,
		const atl::Optional<atl::Array<avl::Pixel> >&	inColors,
		const avl::DrawingStyle&						inDrawingStyle,
		const bool										inForceRgb, 
		avl::Image&										outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws segments on an image with a single color.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inSegments">Default value: { }.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inMarkerType">Default value: Arrow.</param>
	/// <param name="inMarkerSize">Default value: 5.0f.</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawSegments_SingleColor
	(
		const avl::Image&					inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Segment2D> > >&	inSegments,
		atl::Optional<const avl::CoordinateSystem2D&>	inSegmentAlignment,
		const avl::Pixel&					inColor,
		const avl::DrawingStyle&			inDrawingStyle,
		const avl::MarkerType::Type&		inMarkerType,
		const float						inMarkerSize,
		const bool							inForceRgb, 
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws segments on an image with two colors, depending on the status of each segment (usually: green or red for pass/fail status).</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inSegments">Default value: { }.</param>
	/// <param name="inColorIfTrue">Default value: Pixel ( X: 0.0f Y: 200.0f Z: 0.0f W: 0.0f ).</param>
	/// <param name="inColorIfFalse">Default value: Pixel ( X: 200.0f Y: 0.0f Z: 0.0f W: 0.0f ).</param>
	/// <param name="inConditions">Default value: { }.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inMarkerType">Default value: Arrow.</param>
	/// <param name="inMarkerSize">Default value: 5.0f.</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawSegments_TwoColors
	(
		const avl::Image&					inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Segment2D> > >&	inSegments,
		atl::Optional<const avl::CoordinateSystem2D&>	inSegmentAlignment,
		const avl::Pixel&					inColorIfTrue,
		const avl::Pixel&					inColorIfFalse,
		const atl::Conditional< atl::Array<atl::Conditional<bool> > >&	inConditions,
		const avl::DrawingStyle&			inDrawingStyle,
		const avl::MarkerType::Type&		inMarkerType,
		const float						inMarkerSize,
		const bool							inForceRgb, 
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws segments on an image with multiple colors.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inSegments">Default value: { }.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inMarkerType">Default value: Arrow.</param>
	/// <param name="inMarkerSize">Default value: 5.0f.</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawSegments_Palette
	(
		const avl::Image&								inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Segment2D> > >&	inSegments,
		atl::Optional<const avl::CoordinateSystem2D&>	inSegmentAlignment,
		const atl::Optional<atl::Array<avl::Pixel> >&	inColors,
		const avl::DrawingStyle&						inDrawingStyle,
		const avl::MarkerType::Type&					inMarkerType,
		const float									inMarkerSize,
		const bool										inForceRgb, 
		avl::Image&										outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws vectors on an image with a single color.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inVectors">Default value: { }.</param>
	/// <param name="inInitialPoints">Default value: { }.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inHeadSize">Default value: 5.0f.</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawVectors_SingleColor
	(
		const avl::Image&					inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Vector2D> > >&	inVectors,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Point2D> > >&	inInitialPoints,
		atl::Optional<const avl::CoordinateSystem2D&>	inVectorAlignment,
		const avl::Pixel&					inColor,
		const avl::DrawingStyle&			inDrawingStyle,
		float							inHeadSize,
		const bool							inForceRgb, 
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws vectors on an image with two colors, depending on the status of each vector (usually: green or red for pass/fail status).</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inVectors">Default value: { }.</param>
	/// <param name="inInitialPoints">Default value: { }.</param>
	/// <param name="inColorIfTrue">Default value: Pixel ( X: 0.0f Y: 200.0f Z: 0.0f W: 0.0f ).</param>
	/// <param name="inColorIfFalse">Default value: Pixel ( X: 200.0f Y: 0.0f Z: 0.0f W: 0.0f ).</param>
	/// <param name="inConditions">Default value: { }.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inHeadSize">Default value: 5.0f.</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawVectors_TwoColors
	(
		const avl::Image&					inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Vector2D> > >&	inVectors,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Point2D> > >&	inInitialPoints,
		atl::Optional<const avl::CoordinateSystem2D&>	inVectorAlignment,
		const avl::Pixel&					inColorIfTrue,
		const avl::Pixel&					inColorIfFalse,
		const atl::Conditional< atl::Array<atl::Conditional<bool> > >&	inConditions,
		const avl::DrawingStyle&			inDrawingStyle,
		float							inHeadSize,
		const bool							inForceRgb, 
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws vectors at associated initial points on an image with multiple colors.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inVectors">Default value: { }.</param>
	/// <param name="inInitialPoints">Default value: { }.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inHeadSize">Default value: 5.0f.</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawVectors_Palette
	(
		const avl::Image&								inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Vector2D> > >&	inVectors,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Point2D> > >&	inInitialPoints,
		atl::Optional<const avl::CoordinateSystem2D&>	inVectorAlignment,
		const atl::Optional<atl::Array<avl::Pixel> >&	inColors,
		const avl::DrawingStyle&						inDrawingStyle,
		float										inHeadSize,
		const bool										inForceRgb, 
		avl::Image&										outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws lines on an image with a single color.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inLines">Default value: { }.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawLines_SingleColor
	(
		const avl::Image&				inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Line2D> > >&	inLines,
		atl::Optional<const avl::CoordinateSystem2D&>	inLineAlignment,
		const avl::Pixel&				inColor,
		const avl::DrawingStyle&		inDrawingStyle,
		const bool						inForceRgb, 
		avl::Image&						outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws lines on an image with two colors, depending on the status of each line (usually: green or red for pass/fail status).</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inLines">Default value: { }.</param>
	/// <param name="inColorIfTrue">Default value: Pixel ( X: 0.0f Y: 200.0f Z: 0.0f W: 0.0f ).</param>
	/// <param name="inColorIfFalse">Default value: Pixel ( X: 200.0f Y: 0.0f Z: 0.0f W: 0.0f ).</param>
	/// <param name="inConditions">Default value: { }.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawLines_TwoColors
	(
		const avl::Image&				inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Line2D> > >&	inLines,
		atl::Optional<const avl::CoordinateSystem2D&>	inLineAlignment,
		const avl::Pixel&				inColorIfTrue,
		const avl::Pixel&				inColorIfFalse,
		const atl::Conditional< atl::Array<atl::Conditional<bool> > >&	inConditions,
		const avl::DrawingStyle&		inDrawingStyle,
		const bool						inForceRgb, 
		avl::Image&						outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws lines on an image with multiple colors.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inLines">Default value: { }.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawLines_Palette
	(
		const avl::Image&								inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Line2D> > >&	inLines,
		atl::Optional<const avl::CoordinateSystem2D&>	inLineAlignment,
		const atl::Optional<atl::Array<avl::Pixel> >&	inColors,
		const avl::DrawingStyle&						inDrawingStyle,
		const bool										inForceRgb, 
		avl::Image&										outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws paths on an image with a single color.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inPaths">Default value: { }.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawPaths_SingleColor
	(
		const avl::Image&				inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Path> > >&	inPaths,
		atl::Optional<const avl::CoordinateSystem2D&>	inPathAlignment,
		const avl::Pixel&				inColor,
		const avl::DrawingStyle&		inDrawingStyle,
		const bool						inForceRgb, 
		avl::Image&						outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws paths on an image with two colors, depending on the status of each path (usually: green or red for pass/fail status).</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inPaths">Default value: { }.</param>
	/// <param name="inColorIfTrue">Default value: Pixel ( X: 0.0f Y: 200.0f Z: 0.0f W: 0.0f ).</param>
	/// <param name="inColorIfFalse">Default value: Pixel ( X: 200.0f Y: 0.0f Z: 0.0f W: 0.0f ).</param>
	/// <param name="inConditions">Default value: { }.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawPaths_TwoColors
	(
		const avl::Image&				inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Path> > >&	inPaths,
		atl::Optional<const avl::CoordinateSystem2D&>	inPathAlignment,
		const avl::Pixel&				inColorIfTrue,
		const avl::Pixel&				inColorIfFalse,
		const atl::Conditional< atl::Array<atl::Conditional<bool> > >&	inConditions,
		const avl::DrawingStyle&		inDrawingStyle,
		const bool						inForceRgb, 
		avl::Image&						outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws paths on an image with multiple colors.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inPaths">Default value: { }.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawPaths_Palette
	(
		const avl::Image&								inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Path> > >&	inPaths,
		atl::Optional<const avl::CoordinateSystem2D&>	inPathAlignment,
		const atl::Optional<atl::Array<avl::Pixel> >&	inColors,
		const avl::DrawingStyle&						inDrawingStyle,
		const bool										inForceRgb, 
		avl::Image&										outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws points on an image with a single color.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inPoints">Default value: { }.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawPoints_SingleColor
	(
		const avl::Image&				inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Point2D> > >&	inPoints,
		atl::Optional<const avl::CoordinateSystem2D&>	inPointAlignment,
		const avl::Pixel&				inColor,
		const avl::DrawingStyle&		inDrawingStyle,
		const bool						inForceRgb, 
		avl::Image&						outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws points on an image with two colors, depending on the status of each point (usually: green or red for pass/fail status).</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inPoints">Default value: { }.</param>
	/// <param name="inColorIfTrue">Default value: Pixel ( X: 0.0f Y: 200.0f Z: 0.0f W: 0.0f ).</param>
	/// <param name="inColorIfFalse">Default value: Pixel ( X: 200.0f Y: 0.0f Z: 0.0f W: 0.0f ).</param>
	/// <param name="inConditions">Default value: { }.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawPoints_TwoColors
	(
		const avl::Image&				inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Point2D> > >&	inPoints,
		atl::Optional<const avl::CoordinateSystem2D&>	inPointAlignment,
		const avl::Pixel&				inColorIfTrue,
		const avl::Pixel&				inColorIfFalse,
		const atl::Conditional< atl::Array<atl::Conditional<bool> > >&	inConditions,
		const avl::DrawingStyle&		inDrawingStyle,
		const bool						inForceRgb, 
		avl::Image&						outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws points on an image with multiple colors.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inPoints">Default value: { }.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawPoints_Palette
	(
		const avl::Image&							inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Point2D> > >&	inPoints,
		atl::Optional<const avl::CoordinateSystem2D&>	inPointAlignment,
		const atl::Optional<atl::Array<avl::Pixel> >&	inColors,
		const avl::DrawingStyle&					inDrawingStyle,
		const bool									inForceRgb, 
		avl::Image&									outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws rectangles on an image with a single color.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRectangles">Default value: { }.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawRectangles_SingleColor
	(
		const avl::Image&					inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Rectangle2D> > >&	inRectangles,
		atl::Optional<const avl::CoordinateSystem2D&>	inRectangleAlignment,
		const avl::Pixel&					inColor,
		const avl::DrawingStyle&			inDrawingStyle,
		const bool							inForceRgb, 
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws rectangles on an image with two colors, depending on the status of each rectangle (usually: green or red for pass/fail status).</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRectangles">Default value: { }.</param>
	/// <param name="inColorIfTrue">Default value: Pixel ( X: 0.0f Y: 200.0f Z: 0.0f W: 0.0f ).</param>
	/// <param name="inColorIfFalse">Default value: Pixel ( X: 200.0f Y: 0.0f Z: 0.0f W: 0.0f ).</param>
	/// <param name="inConditions">Default value: { }.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawRectangles_TwoColors
	(
		const avl::Image&					inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Rectangle2D> > >&	inRectangles,
		atl::Optional<const avl::CoordinateSystem2D&>	inRectangleAlignment,
		const avl::Pixel&					inColorIfTrue,
		const avl::Pixel&					inColorIfFalse,
		const atl::Conditional< atl::Array<atl::Conditional<bool> > >&	inConditions,
		const avl::DrawingStyle&			inDrawingStyle,
		const bool							inForceRgb, 
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws rectangles on an image with multiple colors.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRectangles">Default value: { }.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawRectangles_Palette
	(
		const avl::Image&					inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Rectangle2D> > >&	inRectangles,
		atl::Optional<const avl::CoordinateSystem2D&>	inRectangleAlignment,
		const atl::Optional<atl::Array<avl::Pixel> >&	inColors,
		const avl::DrawingStyle&			inDrawingStyle,
		const bool							inForceRgb, 
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws coordinate systems on an image with a single color.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inCoordinateSystems">Default value: { }.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inArrowSize">Default value: 5.0f.</param>
	/// <param name="inPixelScale">How many pixels long will be axis of a coordinate system with unit scale. Default value: 20.0f.</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawCoordinateSystems_SingleColor
	(
		const avl::Image&					inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::CoordinateSystem2D> > >&	inCoordinateSystems,
		atl::Optional<const avl::CoordinateSystem2D&>	inCoordinateSystemAlignment,
		const avl::Pixel&					inColor,
		const avl::DrawingStyle&			inDrawingStyle,
		const float						inArrowSize,
		const float						inPixelScale, 
		const bool							inForceRgb, 
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws coordinate systems on an image with two colors, depending on the status of each coordinate system (usually: green or red for pass/fail status).</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inCoordinateSystems">Default value: { }.</param>
	/// <param name="inColorIfTrue">Default value: Pixel ( X: 0.0f Y: 200.0f Z: 0.0f W: 0.0f ).</param>
	/// <param name="inColorIfFalse">Default value: Pixel ( X: 200.0f Y: 0.0f Z: 0.0f W: 0.0f ).</param>
	/// <param name="inConditions">Default value: { }.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inArrowSize">Default value: 5.0f.</param>
	/// <param name="inPixelScale">How many pixels long will be axis of a coordinate system with unit scale. Default value: 20.0f.</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawCoordinateSystems_TwoColors
	(
		const avl::Image&					inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::CoordinateSystem2D> > >&	inCoordinateSystems,
		atl::Optional<const avl::CoordinateSystem2D&>	inCoordinateSystemAlignment,
		const avl::Pixel&					inColorIfTrue,
		const avl::Pixel&					inColorIfFalse,
		const atl::Conditional< atl::Array<atl::Conditional<bool> > >&	inConditions,
		const avl::DrawingStyle&			inDrawingStyle,
		const float						inArrowSize,
		const float						inPixelScale, 
		const bool							inForceRgb, 
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws coordinate systems on an image with multiple colors.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inCoordinateSystems">Default value: { }.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inArrowSize">Default value: 5.0f.</param>
	/// <param name="inPixelScale">How many pixels long will be axis of a coordinate system with unit scale. Default value: 20.0f.</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawCoordinateSystems_Palette
	(
		const avl::Image&					inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::CoordinateSystem2D> > >&	inCoordinateSystems,
		atl::Optional<const avl::CoordinateSystem2D&>	inCoordinateSystemAlignment,
		const atl::Optional<atl::Array<avl::Pixel> >&	inColors,
		const avl::DrawingStyle&			inDrawingStyle,
		const float						inArrowSize,
		const float						inPixelScale, 
		const bool							inForceRgb, 
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws boxes on an image with a single color.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inBoxes">Default value: { }.</param>
	/// <param name="inOpacity">Default value: 1.0f.</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawBoxes_SingleColor
	(
		const avl::Image&			inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Box> > >&	inBoxes,
		const avl::Pixel&			inColor,
		const float					inOpacity,
		const bool					inForceRgb, 
		avl::Image&					outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws boxes on an image with two colors, depending on the status of each box (usually: green or red for pass/fail status).</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inBoxes">Default value: { }.</param>
	/// <param name="inColorIfTrue">Default value: Pixel ( X: 0.0f Y: 200.0f Z: 0.0f W: 0.0f ).</param>
	/// <param name="inColorIfFalse">Default value: Pixel ( X: 200.0f Y: 0.0f Z: 0.0f W: 0.0f ).</param>
	/// <param name="inConditions">Default value: { }.</param>
	/// <param name="inOpacity">Default value: 1.0f.</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawBoxes_TwoColors
	(
		const avl::Image&			inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Box> > >&	inBoxes,
		const avl::Pixel&			inColorIfTrue,
		const avl::Pixel&			inColorIfFalse,
		const atl::Conditional< atl::Array<atl::Conditional<bool> > >&	inConditions,
		const float					inOpacity,
		const bool					inForceRgb, 
		avl::Image&					outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws boxes on an image with multiple colors.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inBoxes">Default value: { }.</param>
	/// <param name="inOpacity">Default value: 1.0f.</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawBoxes_Palette
	(
		const avl::Image&								inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Box> > >&	inBoxes,
		const atl::Optional<atl::Array<avl::Pixel> >&	inColors,
		const float										inOpacity,
		const bool										inForceRgb, 
		avl::Image&										outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws regions on an image with a single color.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRegions">Default value: { }.</param>
	/// <param name="inOpacity">Default value: 1.0f.</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawRegions_SingleColor
	(
		const avl::Image&														inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Region> > >&	inRegions,
		atl::Optional<const avl::CoordinateSystem2D&>							inRegionAlignment,
		const avl::Pixel&														inColor,
		const float																inOpacity,
		const bool																inForceRgb, 
		avl::Image&																outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws regions on an image with a single color. In-place version.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRegions">Default value: { }.</param>
	/// <param name="inOpacity">Default value: 1.0f.</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawRegions_SingleColor_Linked
	(
		avl::Image&																inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Region> > >&	inRegions,
		atl::Optional<const avl::CoordinateSystem2D&>							inRegionAlignment,
		const avl::Pixel&														inColor,
		const float																inOpacity,
		const bool																inForceRgb, 
		avl::Image&																outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws regions on an image with two colors, depending on the status of each region (usually: green or red for pass/fail status).</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRegions">Default value: { }.</param>
	/// <param name="inColorIfTrue">Default value: Pixel ( X: 0.0f Y: 200.0f Z: 0.0f W: 0.0f ).</param>
	/// <param name="inColorIfFalse">Default value: Pixel ( X: 200.0f Y: 0.0f Z: 0.0f W: 0.0f ).</param>
	/// <param name="inConditions">Default value: { }.</param>
	/// <param name="inOpacity">Default value: 1.0f.</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawRegions_TwoColors
	(
		const avl::Image&														inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Region> > >&	inRegions,
		atl::Optional<const avl::CoordinateSystem2D&>							inRegionAlignment,
		const avl::Pixel&														inColorIfTrue,
		const avl::Pixel&														inColorIfFalse,
		const atl::Conditional< atl::Array<atl::Conditional<bool> > >&			inConditions,
		const float																inOpacity,
		const bool																inForceRgb, 
		avl::Image&																outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws regions on an image with multiple colors.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRegions">Default value: { }.</param>
	/// <param name="inOpacity">Default value: 1.0f.</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawRegions_Palette
	(
		const avl::Image&								inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Region> > >&	inRegions,
		atl::Optional<const avl::CoordinateSystem2D&>	inRegionAlignment,
		const atl::Optional<atl::Array<avl::Pixel> >&	inColors,
		const float										inOpacity,
		const bool										inForceRgb, 
		avl::Image&										outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws regions of interest on an image with a single color.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRois">Default value: { }.</param>
	/// <param name="inOpacity">Default value: 1.0f.</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawRegionsOfInterest_SingleColor
	(
		const avl::Image&																inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::RegionOfInterest> > >&	inRois,
		atl::Optional<const avl::CoordinateSystem2D&>									inRegionAlignment,
		const avl::Pixel&																inColor,
		const float																		inOpacity,
		const bool																		inForceRgb, 
		avl::Image&																		outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws regions of interest on an image with two colors, depending on the status of each region (usually: green or red for pass/fail status).</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRois">Default value: { }.</param>
	/// <param name="inColorIfTrue">Default value: Pixel ( X: 0.0f Y: 200.0f Z: 0.0f W: 0.0f ).</param>
	/// <param name="inColorIfFalse">Default value: Pixel ( X: 200.0f Y: 0.0f Z: 0.0f W: 0.0f ).</param>
	/// <param name="inConditions">Default value: { }.</param>
	/// <param name="inOpacity">Default value: 1.0f.</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawRegionsOfInterest_TwoColors
	(
		const avl::Image&																inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::RegionOfInterest> > >&	inRois,
		atl::Optional<const avl::CoordinateSystem2D&>									inRegionAlignment,
		const avl::Pixel&																inColorIfTrue,
		const avl::Pixel&																inColorIfFalse,
		const atl::Conditional< atl::Array<atl::Conditional<bool> > >&					inConditions,
		const float																		inOpacity,
		const bool																		inForceRgb, 
		avl::Image&																		outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws regions of interest on an image with multiple colors.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRois">Default value: { }.</param>
	/// <param name="inOpacity">Default value: 1.0f.</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawRegionsOfInterest_Palette
	(
		const avl::Image&																inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::RegionOfInterest> > >&	inRois,
		atl::Optional<const avl::CoordinateSystem2D&>									inRegionAlignment,
		const atl::Optional<atl::Array<avl::Pixel> >&									inColors,
		const float																		inOpacity,
		const bool																		inForceRgb, 
		avl::Image&																		outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws strings (text) on an image with a single color.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inStrings">Strings to be drawn. Default value: { }.</param>
	/// <param name="inLocations">Center position of strings. Default value: { }.</param>
	/// <param name="inLocationAnchor">Default value: MiddleCenter.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inSize">Height of a character in pixels. Default value: 16.0f.</param>
	/// <param name="inOrientationAngle">Orientation of text in degrees. Default value: 0.0f.</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="inBackgroundColor">Color of pixels drawn on image in text row. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawStrings_SingleColor
	(
		const avl::Image&					inImage,
		const atl::Conditional<atl::Array<atl::Conditional<atl::String> > >&	inStrings,			
		const atl::Conditional<atl::Array<atl::Conditional<avl::Location> > >&	inLocations,			
		atl::Optional<const avl::CoordinateSystem2D&>							inLocationAlignment,
		const avl::Anchor2D::Type												inLocationAnchor,
		const avl::Pixel&														inColor,
		const avl::DrawingStyle&												inDrawingStyle,
		float																inSize,				
		float																inOrientationAngle, 
		const bool																inForceRgb,			
		const atl::Optional<avl::Pixel>&										inBackgroundColor,  
		avl::Image&																outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws strings (text) on an image with two colors, depending on the status of each string (usually: green or red for pass/fail status).</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inStrings">Default value: { }.</param>
	/// <param name="inLocations">Default value: { }.</param>
	/// <param name="inLocationAnchor">Default value: MiddleCenter.</param>
	/// <param name="inColorIfTrue">Color corresponding to True value on inCondition input. Default value: Pixel ( X: 0.0f Y: 200.0f Z: 0.0f W: 0.0f ).</param>
	/// <param name="inColorIfFalse">Color corresponding to False value on inCondition input. Default value: Pixel ( X: 200.0f Y: 0.0f Z: 0.0f W: 0.0f ).</param>
	/// <param name="inConditions">Default value: { }.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inSize">Height of a character in pixels. Default value: 16.0f.</param>
	/// <param name="inOrientationAngle">Orientation of text in degrees. Default value: 0.0f.</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="inBackgroundColor">Color of pixels drawn on image in text row. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawStrings_TwoColors
	(
		const avl::Image&														inImage,
		const atl::Conditional<atl::Array<atl::Conditional<atl::String> > >&	inStrings,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Location> > >&	inLocations,
		atl::Optional<const avl::CoordinateSystem2D&>							inLocationAlignment,
		const avl::Anchor2D::Type												inLocationAnchor,
		const avl::Pixel&														inColorIfTrue,			   
		const avl::Pixel&														inColorIfFalse,			   
		const atl::Conditional< atl::Array<atl::Conditional<bool> > >&			inConditions,
		const avl::DrawingStyle&												inDrawingStyle,
		float																inSize,						
		float																inOrientationAngle,			
		const bool																inForceRgb,					
		const atl::Optional<avl::Pixel>&										inBackgroundColor,			
		avl::Image&																outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws strings (text) on an image with multiple colors.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inStrings">String to draw. Default value: { }.</param>
	/// <param name="inLocations">Center point of each string to draw. Default value: { }.</param>
	/// <param name="inLocationAnchor">Default value: MiddleCenter.</param>
	/// <param name="inColors">Color for each string to be drawn. Default value: atl::NIL.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inSize">Height of a character in pixels. Default value: 16.0f.</param>
	/// <param name="inOrientationAngle">Orientation of text in degrees. Default value: 0.0f.</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="inBackgroundColor">Color of pixels drawn on image in text row. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawStrings_Palette
	(
		const avl::Image&					inImage,
		const atl::Conditional<atl::Array<atl::Conditional<atl::String> > >&	inStrings,  
		const atl::Conditional<atl::Array<atl::Conditional<avl::Location> > >&	inLocations,	
		atl::Optional<const avl::CoordinateSystem2D&>							inLocationAlignment,
		const avl::Anchor2D::Type			inLocationAnchor,
		const atl::Optional<atl::Array<avl::Pixel> >&							inColors,	
		const avl::DrawingStyle&			inDrawingStyle,
		float							inSize,											
		float							inOrientationAngle,								
		const bool							inForceRgb,										
		const atl::Optional<avl::Pixel>&	inBackgroundColor,								
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws strings (text) on an image with a single color.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inLabels">Strings to be drawn. Default value: { }.</param>
	/// <param name="inLocationAnchor">Default value: MiddleCenter.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inSize">Height of a character in pixels. Default value: 16.0f.</param>
	/// <param name="inOrientationAngle">Orientation of text in degrees. Default value: 0.0f.</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="inBackgroundColor">Color of pixels drawn on image in text row. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawStringLabels_SingleColor
	(
		const avl::Image&					inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::StringLabel> > >&	inLabels,			
		atl::Optional<const avl::CoordinateSystem2D&>							inLocationAlignment,
		const avl::Anchor2D::Type												inLocationAnchor,
		const avl::Pixel&														inColor,
		const avl::DrawingStyle&												inDrawingStyle,
		float																inSize,				
		float																inOrientationAngle, 
		const bool																inForceRgb,			
		const atl::Optional<avl::Pixel>&										inBackgroundColor,  
		avl::Image&																outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws strings (text) on an image with two colors, depending on the status of each string (usually: green or red for pass/fail status).</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inLabels">Default value: { }.</param>
	/// <param name="inLocationAnchor">Default value: MiddleCenter.</param>
	/// <param name="inColorIfTrue">Color corresponding to True value on inCondition input. Default value: Pixel ( X: 0.0f Y: 200.0f Z: 0.0f W: 0.0f ).</param>
	/// <param name="inColorIfFalse">Color corresponding to False value on inCondition input. Default value: Pixel ( X: 200.0f Y: 0.0f Z: 0.0f W: 0.0f ).</param>
	/// <param name="inConditions">Default value: { }.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inSize">Height of a character in pixels. Default value: 16.0f.</param>
	/// <param name="inOrientationAngle">Orientation of text in degrees. Default value: 0.0f.</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="inBackgroundColor">Color of pixels drawn on image in text row. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawStringLabels_TwoColors
	(
		const avl::Image&														inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::StringLabel> > >&	inLabels,
		atl::Optional<const avl::CoordinateSystem2D&>							inLocationAlignment,
		const avl::Anchor2D::Type												inLocationAnchor,
		const avl::Pixel&														inColorIfTrue,			   
		const avl::Pixel&														inColorIfFalse,			   
		const atl::Conditional< atl::Array<atl::Conditional<bool> > >&			inConditions,
		const avl::DrawingStyle&												inDrawingStyle,
		float																	inSize,						
		float																	inOrientationAngle,			
		const bool																inForceRgb,					
		const atl::Optional<avl::Pixel>&										inBackgroundColor,			
		avl::Image&																outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws strings (text) on an image with multiple colors.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inLabels">String to draw. Default value: { }.</param>
	/// <param name="inLocationAnchor">Default value: MiddleCenter.</param>
	/// <param name="inColors">Color for each string to be drawn. Default value: atl::NIL.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inSize">Height of a character in pixels. Default value: 16.0f.</param>
	/// <param name="inOrientationAngle">Orientation of text in degrees. Default value: 0.0f.</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="inBackgroundColor">Color of pixels drawn on image in text row. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawStringLabels_Palette
	(
		const avl::Image&					inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::StringLabel> > >&	inLabels,  
		atl::Optional<const avl::CoordinateSystem2D&>					inLocationAlignment,
		const avl::Anchor2D::Type			inLocationAnchor,
		const atl::Optional<atl::Array<avl::Pixel> >&					inColors,			
		const avl::DrawingStyle&			inDrawingStyle,
		float								inSize,											
		float								inOrientationAngle,								
		const bool							inForceRgb,										
		const atl::Optional<avl::Pixel>&	inBackgroundColor,								
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws dimension lines on an image with a single color.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inSegments">Default value: { }.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inHeadSize">Default value: 5.0f.</param>
	/// <param name="inScale">px / mm. Default value: 1.0f.</param>
	/// <param name="inMetricUnit">Default value: Millimetres.</param>
	/// <param name="inTextSize">Default value: 12.0f.</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawDimensionLines_SingleColor
	(
		const avl::Image&					inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Segment2D> > >&	inSegments,
		atl::Optional<const avl::CoordinateSystem2D&>	inSegmentAlignment,
		const avl::Pixel&					inColor,
		const avl::DrawingStyle&			inDrawingStyle,
		float							inHeadSize,
		float							inScale, 
		avl::MetricUnit::Type				inMetricUnit,
		float							inTextSize,
		const bool							inForceRgb, 
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws dimension lines on an image with two colors, depending on the status of each dimension line (usually: green or red for pass/fail status).</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inSegments">Default value: { }.</param>
	/// <param name="inColorIfTrue">Default value: Pixel ( X: 0.0f Y: 200.0f Z: 0.0f W: 0.0f ).</param>
	/// <param name="inColorIfFalse">Default value: Pixel ( X: 200.0f Y: 0.0f Z: 0.0f W: 0.0f ).</param>
	/// <param name="inConditions">Default value: { }.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inHeadSize">Default value: 5.0f.</param>
	/// <param name="inScale">px / mm. Default value: 1.0f.</param>
	/// <param name="inMetricUnit">Default value: Millimetres.</param>
	/// <param name="inTextSize">Default value: 12.0f.</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawDimensionLines_TwoColors
	(
		const avl::Image&					inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Segment2D> > >&	inSegments,
		atl::Optional<const avl::CoordinateSystem2D&>	inSegmentAlignment,
		const avl::Pixel&					inColorIfTrue,
		const avl::Pixel&					inColorIfFalse,
		const atl::Conditional< atl::Array<atl::Conditional<bool> > >&	inConditions,
		const avl::DrawingStyle&			inDrawingStyle,
		float							inHeadSize,
		float							inScale, 
		avl::MetricUnit::Type				inMetricUnit,
		float							inTextSize,
		const bool							inForceRgb, 
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws dimension lines on an image with multiple colors.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inSegments">Default value: { }.</param>
	/// <param name="inDrawingStyle">Default value: DrawingStyle ( DrawingMode: HighQuality  Opacity: 1.0f  Thickness: 1.0f  Filled: False  PointShape: Nil  PointSize: 1.0f ).</param>
	/// <param name="inHeadSize">Default value: 5.0f.</param>
	/// <param name="inScale">px / mm. Default value: 1.0f.</param>
	/// <param name="inMetricUnit">Default value: Millimetres.</param>
	/// <param name="inTextSize">Default value: 12.0f.</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawDimensionLines_Palette
	(
		const avl::Image&					inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::Segment2D> > >&	inSegments,
		atl::Optional<const avl::CoordinateSystem2D&>	inSegmentAlignment,
		const atl::Optional<atl::Array<avl::Pixel> >&	inColors,
		const avl::DrawingStyle&			inDrawingStyle,
		float							inHeadSize,
		float							inScale, 
		avl::MetricUnit::Type				inMetricUnit,
		float							inTextSize,
		const bool							inForceRgb, 
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws ShapeRegion objects on an image with a single color.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inShapeRegions">Default value: { }.</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawShapeRegions_SingleColor
	(
		const avl::Image&				inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::ShapeRegion> > >&	inShapeRegions,
		atl::Optional<const avl::CoordinateSystem2D&>	inShapeRegionAlignment,
		const avl::Pixel&				inColor,
		const avl::DrawingStyle&		inDrawingStyle,
		const bool						inForceRgb, 
		avl::Image&						outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws ShapeRegion objects on an image with two colors, depending on the status of each ShapeRegion (usually: green or red for pass/fail status).</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inShapeRegions">Default value: { }.</param>
	/// <param name="inColorIfTrue">Default value: Pixel ( X: 0.0f Y: 200.0f Z: 0.0f W: 0.0f ).</param>
	/// <param name="inColorIfFalse">Default value: Pixel ( X: 200.0f Y: 0.0f Z: 0.0f W: 0.0f ).</param>
	/// <param name="inConditions">Default value: { }.</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawShapeRegions_TwoColors
	(
		const avl::Image&				inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::ShapeRegion> > >&	inShapeRegions,
		atl::Optional<const avl::CoordinateSystem2D&>	inShapeRegionAlignment,
		const avl::Pixel&				inColorIfTrue,
		const avl::Pixel&				inColorIfFalse,
		const atl::Conditional< atl::Array<atl::Conditional<bool> > >&	inConditions,
		const avl::DrawingStyle&		inDrawingStyle,
		const bool						inForceRgb, 
		avl::Image&						outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Draws ShapeRegion objects on an image with multiple colors.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inShapeRegions">Default value: { }.</param>
	/// <param name="inForceRgb">Filter will convert monochromatic image to RGB if needed. Default value: True.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DrawShapeRegions_Palette
	(
		const avl::Image&								inImage,
		const atl::Conditional<atl::Array<atl::Conditional<avl::ShapeRegion> > >&	inShapeRegions,
		atl::Optional<const avl::CoordinateSystem2D&>	inShapeRegionAlignment,
		const atl::Optional<atl::Array<avl::Pixel> >&	inColors,
		const avl::DrawingStyle&						inDrawingStyle,
		const bool										inForceRgb, 
		avl::Image&										outImage
	)
	THROW_AVL_ERRORS;

} // namespace avs

#endif // AVS_IMAGEDRAWING_H

