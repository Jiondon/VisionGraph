//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_REGIONBASICS_H
#define AVL_REGIONBASICS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Enums/Anchor2D.h"
#include "Image/Image.h"
#include "Path/Path.h"
#include "Region/Region.h"
#include "Region/RegionOfInterest.h"

namespace avl
{


	namespace BorderPosition
	{
		enum Type
		{
			Internal,
			External,
			Centered
		};
	}


	/// <summary>Changes the width and the height of a region's frame (but does not rescale the content).</summary>
	/// <param name="inWidth">New frame width.</param>
	/// <param name="inHeight">New frame height.</param>
	AVL_FUNCTION void SetRegionFrame
	(
		avl::Region&		ioRegion,
		int					inWidth,	
		int					inHeight	
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the width and height of the entire region's frame (not to be confused with RegionBoundingBox!)</summary>
	/// <param name="inRegion">Input region.</param>
	AVL_FUNCTION void GetRegionFrame
	(
		const avl::Region&	inRegion,
		int&				outFrameWidth,
		int&				outFrameHeight
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a region to an array of its pixels locations.</summary>
	/// <param name="inRegion">Input region.</param>
	AVL_FUNCTION void RegionToLocations
	(
		const avl::Region&			inRegion,
		atl::Array<avl::Location>&	outLocations
	)
	THROW_AVL_ERRORS;

	/// <summary>Forms a region containing pixels of given locations.</summary>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void LocationsToRegion
	(
		const atl::Array<avl::Location>&	inLocations,
		int									inFrameWidth,
		int									inFrameHeight,
		avl::Region&						outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a closed path to region of interest.</summary>
	/// <param name="inPath">Input path.</param>
	AVL_FUNCTION void PathToRegionOfInterest
	(
		const avl::Path&				inPath,
		avl::RegionOfInterest&			outRegionOfInterest
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a region of interest to a region with automatically computed frame.</summary>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void RegionOfInterestToRegion
	(
		const avl::RegionOfInterest&	inRegionOfInterest,
		avl::Region&					outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a region corresponding to a given region of interest.</summary>
	/// <param name="inFrameWidth">Width of the created region's frame.</param>
	/// <param name="inFrameHeight">Height of the created region's frame.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void CreateRegionOfInterestRegion
	(
		const avl::RegionOfInterest&	inRegionOfInterest,
		int								inFrameWidth,			
		int								inFrameHeight,			
		avl::Region&					outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a rectangular region corresponding to a given box.</summary>
	/// <param name="inBox">A box defining pixels that will be converted to white elements.</param>
	/// <param name="inFrameWidth">Width of the created region's frame (not to be confused with the width of the box!).</param>
	/// <param name="inFrameHeight">Height of the created region's frame (not to be confused with the height of the box!).</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void CreateBoxRegion
	(
		const avl::Box&		inBox,			
		int					inFrameWidth,	
		int					inFrameHeight,	
		avl::Region&		outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a frame-shaped region with given parameters.</summary>
	/// <param name="inBorderWidth">Default value: 1.</param>
	/// <param name="inBorderPosition">Default value: Centered.</param>
	/// <param name="inFrameWidth">Width of the created region's frame.</param>
	/// <param name="inFrameHeight">Height of the created region's frame.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void CreateBoxBorderRegion
	(
		const avl::Box&				inBox,
		int							inBorderWidth,
		avl::BorderPosition::Type	inBorderPosition,
		int							inFrameWidth,		
		int							inFrameHeight,		
		avl::Region&				outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates an elliptic region of given bounding rectangle.</summary>
	/// <param name="inEllipseAlignment">Adjusts the ellipse to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inFrameWidth">Width of the created region's frame (not to be confused with the width of the ellipse!).</param>
	/// <param name="inFrameHeight">Height of the created region's frame (not to be confused with the height of the ellipse!).</param>
	/// <param name="outRegion">Output region.</param>
	/// <param name="outAlignedEllipse">The input ellipse transformed to the absolute coordinate system.</param>
	AVL_FUNCTION void CreateEllipseRegion
	(
		const avl::Rectangle2D&							inEllipse,
		atl::Optional<const avl::CoordinateSystem2D&>	inEllipseAlignment,				
		int												inFrameWidth,					
		int												inFrameHeight,					
		avl::Region&									outRegion,
		atl::Optional<avl::Rectangle2D&>				outAlignedEllipse = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a ring-shaped region with given parameters.</summary>
	/// <param name="inCircle">Input circle.</param>
	/// <param name="inCircleAlignment">Adjusts the circle to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inRingWidth">Default value: 1.0f.</param>
	/// <param name="inBorderPosition">Default value: Centered.</param>
	/// <param name="inFrameWidth">Width of the created region's frame.</param>
	/// <param name="inFrameHeight">Height of the created region's frame.</param>
	/// <param name="outRegion">Output region.</param>
	/// <param name="outAlignedCircle">The input circle transformed to the absolute coordinate system.</param>
	AVL_FUNCTION void CreateRingRegion
	(
		const avl::Circle2D&							inCircle,					
		atl::Optional<const avl::CoordinateSystem2D&>	inCircleAlignment,			
		float										inRingWidth,
		avl::BorderPosition::Type						inBorderPosition,
		int												inFrameWidth,				
		int												inFrameHeight,				
		avl::Region&									outRegion,
		atl::Optional<avl::Circle2D&>					outAlignedCircle = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a cross-shaped region with given parameters.</summary>
	/// <param name="inFrameWidth">Width of the created region's frame.</param>
	/// <param name="inFrameHeight">Height of the created region's frame.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void CreateCrossRegion
	(
		const avl::Box&		inCrossBoundingBox,
		int					inFrameWidth,			
		int					inFrameHeight,			
		avl::Region&		outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a grid-shaped region with given parameters.</summary>
	/// <param name="inHorizontalStep">Horizontal distance between vertical grid lines.</param>
	/// <param name="inVerticalStep">Vertical distance between horizontal grid lines.</param>
	/// <param name="inFrameWidth">Width of the created region's frame.</param>
	/// <param name="inFrameHeight">Height of the created region's frame.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void CreateGridRegion
	(
		const avl::Box&		inGridBoundingBox,
		int					inHorizontalStep,	
		int					inVerticalStep,		
		int					inFrameWidth,		
		int					inFrameHeight,		
		avl::Region&		outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a circular region corresponding to a given circle.</summary>
	/// <param name="inCircleAlignment">Adjusts the circle to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inFrameWidth">Width of the created region's frame (not to be confused with the size of the circle!).</param>
	/// <param name="inFrameHeight">Height of the created region's frame (not to be confused with the size of the circle!).</param>
	/// <param name="outRegion">Output region.</param>
	/// <param name="outAlignedCircle">The input circle transformed to the absolute coordinate system.</param>
	AVL_FUNCTION void CreateCircleRegion
	(
		const avl::Circle2D&							inCircle,
		atl::Optional<const avl::CoordinateSystem2D&>	inCircleAlignment,			
		int												inFrameWidth,				
		int												inFrameHeight,				
		avl::Region&									outRegion,
		atl::Optional<avl::Circle2D&>					outAlignedCircle = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a polygonal region corresponding to a given closed path.</summary>
	/// <param name="inPolygonAlignment">Adjusts the polygon to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inFrameWidth">Width of the created region's frame.</param>
	/// <param name="inFrameHeight">Height of the created region's frame.</param>
	/// <param name="outRegion">Output region.</param>
	/// <param name="outAlignedPolygon">The input polygon transformed to the absolute coordinate system.</param>
	AVL_FUNCTION void CreatePolygonRegion
	(
		const avl::Path&								inPolygon,
		atl::Optional<const avl::CoordinateSystem2D&>	inPolygonAlignment,				
		int												inFrameWidth,					
		int												inFrameHeight,					
		avl::Region&									outRegion,
		atl::Optional<avl::Path&>						outAlignedPolygon = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a region from a path with given parameters.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="inPathAlignment">Adjusts the path to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inBorderWidth">Default value: 1.0f.</param>
	/// <param name="inBorderPosition">Default value: Centered.</param>
	/// <param name="inFrameWidth">Width of the created region's frame.</param>
	/// <param name="inFrameHeight">Height of the created region's frame.</param>
	/// <param name="outRegion">Output region.</param>
	/// <param name="outAlignedPath">The input path transformed to the absolute coordinate system.</param>
	AVL_FUNCTION void CreatePathBorderRegion
	(
		const avl::Path&			inPath,
		atl::Optional<const avl::CoordinateSystem2D&>	inPathAlignment,	
		float					inBorderWidth,
		avl::BorderPosition::Type	inBorderPosition,
		int							inFrameWidth,		
		int							inFrameHeight,		
		avl::Region&				outRegion,
		atl::Optional<avl::Path&>	outAlignedPath = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a region corresponding to a given rectangle.</summary>
	/// <param name="inRectangleAlignment">Adjusts the rectangle to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inFrameWidth">Width of the created region's frame (not to be confused with the width of the rectangle!).</param>
	/// <param name="inFrameHeight">Height of the created region's frame (not to be confused with the height of the rectangle!).</param>
	/// <param name="outRegion">Output region.</param>
	/// <param name="outAlignedRectangle">The input rectangle transformed to the absolute coordinate system.</param>
	AVL_FUNCTION void CreateRectangleRegion
	(
		const avl::Rectangle2D&							inRectangle,
		atl::Optional<const avl::CoordinateSystem2D&>	inRectangleAlignment,			
		int												inFrameWidth,					
		int												inFrameHeight,					
		avl::Region&									outRegion,
		atl::Optional<avl::Rectangle2D&>				outAlignedRectangle = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a frame-shaped region with given parameters.</summary>
	/// <param name="inRectangleAlignment">Adjusts the rectangle to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inBorderWidth">Default value: 1.0f.</param>
	/// <param name="inBorderPosition">Default value: Centered.</param>
	/// <param name="inFrameWidth">Width of the created region's frame.</param>
	/// <param name="inFrameHeight">Height of the created region's frame.</param>
	/// <param name="outRegion">Output region.</param>
	/// <param name="outAlignedRectangle">The input rectangle transformed to the absolute coordinate system.</param>
	AVL_FUNCTION void CreateRectangleBorderRegion
	(
		const avl::Rectangle2D&		inRectangle,
		atl::Optional<const avl::CoordinateSystem2D&>	inRectangleAlignment,	
		float					inBorderWidth,
		avl::BorderPosition::Type	inBorderPosition,
		int							inFrameWidth,		
		int							inFrameHeight,		
		avl::Region&				outRegion,
		atl::Optional<avl::Rectangle2D&>	outAlignedRectangle = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Tests whether a region is adjacent to its border.</summary>
	/// <param name="inRegion">Input region.</param>
	AVL_FUNCTION void TestRegionOnBorder
	(
		const avl::Region&	inRegion,
		bool&				outIsOnBorder
	)
	THROW_AVL_ERRORS;

	/// <summary>Tests whether the size of a region equals zero.</summary>
	/// <param name="inRegion">Input region.</param>
	AVL_FUNCTION void TestRegionEmpty
	(
		const avl::Region&	inRegion,
		bool&				outIsEmpty
	)
	THROW_AVL_ERRORS;

	/// <summary>Tests whether the size of a region doesn't equal zero.</summary>
	/// <param name="inRegion">Input region.</param>
	AVL_FUNCTION void TestRegionNotEmpty
	(
		const avl::Region&	inRegion,
		bool&				outIsNotEmpty
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns a characteristic point of the input's region bounding box.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inPointAnchor">Default value: TopLeft.</param>
	AVL_FUNCTION void RegionCharacteristicPoint
	(
		const avl::Region&			inRegion,
		const avl::Anchor2D::Type	inPointAnchor,
		avl::Point2D&				outPoint
	)
	THROW_AVL_ERRORS;

	/// <summary>If the input region contains at least one pixel, then it is copied to the output; otherwise Nil is returned.</summary>
	/// <param name="inRegion">Input region.</param>
	AVL_FUNCTION void SkipEmptyRegion
	(
		const avl::Region&				inRegion,
		atl::Conditional<avl::Region>&	outNotEmptyRegion,
		bool&							outIsNotEmpty
	)
	THROW_AVL_ERRORS;

	/// <summary>Saves serialized Region object as avdata file.</summary>
	/// <param name="inRegion">Region to be serialized.</param>
	/// <param name="inFilename">Name of the target file.</param>
	AVL_FUNCTION void SaveRegion
	(
		const avl::Region&	inRegion,		
		const atl::File&	inFilename		
	)
	THROW_AVL_ERRORS;

	/// <summary>Loads serialized Region object from avdata file.</summary>
	/// <param name="inFilename">Name of the source file.</param>
	/// <param name="outRegion">Deserialized output Region.</param>
	AVL_FUNCTION void LoadRegion
	(
		const atl::File&	inFilename,			
		avl::Region&		outRegion			
	)
	THROW_AVL_ERRORS;

	/// <summary>Checks if the input region has well sorted, not overlapping and in-range point-runs.</summary>
	/// <param name="inRegion">Input region.</param>
	AVL_FUNCTION void TestRegionValid
	(
		const avl::Region&	inRegion,
		bool&				outIsValid
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a segment region.</summary>
	/// <param name="inWidth">Segment width.</param>
	/// <param name="inRound">Make ends of segment round.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void CreateSegmentRegion
	(
		const avl::Segment2D&							inSegment,
		atl::Optional<const avl::CoordinateSystem2D&>	inSegmentAlignment,
		int												inWidth,			
		int												inFrameWidth,					
		int												inFrameHeight,		
		bool											inRound,			
		avl::Region&									outRegion,
		atl::Optional<avl::Segment2D&>					outAlignedSegment = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a line region.</summary>
	/// <param name="inWidth">Width of output region line.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void CreateLineRegion
	(
		const avl::Line2D&								inLine,
		atl::Optional<const avl::CoordinateSystem2D&>	inLineAlignment,
		int												inWidth,			
		int												inFrameWidth,
		int												inFrameHeight,
		avl::Region&									outRegion,
		atl::Optional<avl::Line2D&>						outAlignedLine = atl::NIL
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_REGIONBASICS_H

