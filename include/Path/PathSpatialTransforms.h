//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_PATHSPATIALTRANSFORMS_H
#define AVL_PATHSPATIALTRANSFORMS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Path/Path.h"
#include "Basic/Types.h"
#include "Enums/Axis.h"
#include "Profile/Profile.h"

namespace avl
{


	/// <summary>Translates a path by a vector.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="inDelta">Translation vector.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	/// <param name="outPath">Output path.</param>
	AVL_FUNCTION void TranslatePath
	(
		const avl::Path&		inPath,
		const avl::Vector2D&	inDelta,	
		bool					inInverse,	
		avl::Path&				outPath
	)
	THROW_AVL_ERRORS;

	/// <summary>Rotates a path clockwise around a center point.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="inCenter">Center of rotation (the mass center by default). Default value: atl::NIL.</param>
	/// <param name="inAngle">Clockwise rotation angle.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	/// <param name="outPath">Output path.</param>
	AVL_FUNCTION void RotatePath
	(
		const avl::Path&					inPath,
		atl::Optional<const avl::Point2D&>	inCenter,	
		float							inAngle,	
		bool								inInverse,	
		avl::Path&							outPath
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a path contained in a box from another path.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="outPath">Output path.</param>
	AVL_FUNCTION void CropPath
	(
		const avl::Path&	inPath,
		const avl::Box&		inBox,
		avl::Path&			outPath
	)
	THROW_AVL_ERRORS;

	/// <summary>Translates each point of a path proportionally to its distance to a reference point.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="inReferencePoint">The point to which all distances change linearly (the mass center by default). Default value: atl::NIL.</param>
	/// <param name="inScale">Scaling factor. Default value: 1.0f.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	/// <param name="outPath">Output path.</param>
	AVL_FUNCTION void RescalePath
	(
		const avl::Path&					inPath,
		atl::Optional<const avl::Point2D&>	inReferencePoint,	
		float							inScale,			
		bool								inInverse,			
		avl::Path&							outPath
	)
	THROW_AVL_ERRORS;

	/// <summary>Moves a path from a local coordinate system to the absolute one.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="inAlignment">Coordinate system to align to.</param>
	/// <param name="inInverse">Switches to the inverse transform.</param>
	AVL_FUNCTION void AlignPath
	(
		const avl::Path&				inPath,
		const avl::CoordinateSystem2D&	inAlignment,	
		bool							inInverse,		
		avl::Path&						outAlignedPath
	)
	THROW_AVL_ERRORS;

	/// <summary>Translates an array of paths by a vector.</summary>
	/// <param name="inDelta">Translation vector.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void TranslatePathArray
	(
		const atl::Array<avl::Path>&	inPaths,
		const avl::Vector2D&			inDelta,	
		bool							inInverse,	
		atl::Array<avl::Path>&			outPaths
	)
	THROW_AVL_ERRORS;

	/// <summary>Rotates an array of paths clockwise around a center point.</summary>
	/// <param name="inCenter">Center of rotation (the mass center by default). Default value: atl::NIL.</param>
	/// <param name="inAngle">Clockwise rotation angle.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RotatePathArray
	(
		const atl::Array<avl::Path>&	inPaths,
		atl::Optional<const avl::Point2D&>	inCenter,	
		float						inAngle,	
		bool							inInverse,	
		atl::Array<avl::Path>&			outPaths
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates an array of paths contained in a box from another array of paths.</summary>
	AVL_FUNCTION void CropPathArray
	(
		const atl::Array<avl::Path>&	inPaths,
		const avl::Box&					inBox,
		atl::Array<avl::Path>&			outPaths
	)
	THROW_AVL_ERRORS;

	/// <summary>Translates each point of each path proportionally to its distance to a reference point.</summary>
	/// <param name="inReferencePoint">The point to which all distances change linearly (the mass center by default). Default value: atl::NIL.</param>
	/// <param name="inScale">Scaling factor. Default value: 1.0f.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RescalePathArray
	(
		const atl::Array<avl::Path>&	inPaths,
		atl::Optional<const avl::Point2D&>	inReferencePoint,	
		float						inScale,			
		bool							inInverse,			
		atl::Array<avl::Path>&			outPaths
	)
	THROW_AVL_ERRORS;

	/// <summary>Moves an array of paths from a local coordinate system to the absolute one.</summary>
	/// <param name="inAlignment">Coordinate system to align to.</param>
	/// <param name="inInverse">Switches to the inverse transform.</param>
	AVL_FUNCTION void AlignPathArray
	(
		const atl::Array<avl::Path>&	inPaths,
		const avl::CoordinateSystem2D&	inAlignment,	
		bool							inInverse,		
		atl::Array<avl::Path>&			outAlignedPaths
	)
	THROW_AVL_ERRORS;

	/// <summary>Reverses the order of points in a path.</summary>
	AVL_FUNCTION void ReversePath
	(
		avl::Path&	ioPath
	)
	THROW_AVL_ERRORS;

	namespace PathOrientationAlignment
	{
		enum Type
		{
			EllipticAxes,
			None
		};
	}


	/// <summary>Rotates and shifts a path to minimize average distance between its points and a reference path.</summary>
	/// <param name="inPath">Path to be aligned.</param>
	/// <param name="inReferencePath">Path to align to.</param>
	/// <param name="inPathOrientationAlignment">Determines how to align paths orientation before the main algorithm. Default value: EllipticAxes.</param>
	/// <param name="inIterations">Number of algorithm steps. Default value: 5.</param>
	/// <param name="inFirstShift">Magnitude of possible shift at the first step in pixels. Default value: 10.0f.</param>
	/// <param name="inFirstRotation">Magnitude of possible rotation at the first step in degrees. Default value: 10.0f.</param>
	/// <param name="outPath">Aligned path.</param>
	/// <param name="outAlignment">The coordinate system that geometrical objects defined in the context of the path should be aligned to.</param>
	/// <param name="outPathDistance">Average distance of characteristic points of the input path from the reference path.</param>
	AVL_FUNCTION void FitPathToPath
	(
		const avl::Path&					inPath,				
		const avl::Path&					inReferencePath,	
		avl::PathOrientationAlignment::Type	inPathOrientationAlignment,	
		const int							inIterations,		
		const float						inFirstShift,		
		const float						inFirstRotation,	
		avl::Path&							outPath,			
		avl::CoordinateSystem2D&			outAlignment,		
		float&							outPathDistance		
	)
	THROW_AVL_ERRORS;

	/// <summary>Flips and rotates a path so that x-coordinates are exchanged with y-coordinates.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="outPath">Output path.</param>
	AVL_FUNCTION void TransposePath
	(
		const avl::Path&	inPath,
		avl::Path&			outPath
	)
	THROW_AVL_ERRORS;

	namespace ShiftDirection
	{
		enum Type
		{
			Left,
			Right
		};
	}


	/// <summary>Moves every vertex of path along bisector of the angle between incident segments.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="outPath">Output path.</param>
	AVL_FUNCTION void ShiftPath
	(
		const avl::Path&			inPath,
		float					inDistance,
		avl::ShiftDirection::Type	inDirection,
		avl::Path&					outPath
	)
	THROW_AVL_ERRORS;

	/// <summary>Transforms a path to a coordinate system in which the 'axis' path is vertical or horizontal.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="inAxis">Input axis path.</param>
	/// <param name="inAxisType">Type of axis the input axis path is parallel to. Default value: Y.</param>
	/// <param name="inAxisCoordinate">Coordinate of the axis path. Default value: 0.0f.</param>
	/// <param name="inInverse">Switches to the inverse operation. Default value: True.</param>
	/// <param name="outPath">Transformed path.</param>
	AVL_FUNCTION void PathAlongPath
	(
		const avl::Path&	inPath,				
		const avl::Path&	inAxis,				
		avl::Axis::Type		inAxisType,			
		float				inAxisCoordinate,	
		bool				inInverse,			
		avl::Path&			outPath				
	)
	THROW_AVL_ERRORS;

	/// <summary>Transforms a path to a coordinate system in which the 'axis' arc is vertical or horizontal.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="inAxis">Input axis arc.</param>
	/// <param name="inAxisType">Type of axis the input axis arc is parallel to. Default value: Y.</param>
	/// <param name="inAxisCoordinate">Coordinate of the axis arc. Default value: 0.0f.</param>
	/// <param name="inInverse">Switches to the inverse operation. Default value: True.</param>
	/// <param name="outPath">Transformed path.</param>
	AVL_FUNCTION void PathAlongArc
	(
		const avl::Path&	inPath,				
		const avl::Arc2D&	inAxis,				
		avl::Axis::Type		inAxisType,			
		float				inAxisCoordinate,	
		bool				inInverse,			
		avl::Path&			outPath				
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the distance from the line to the path.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="inLine">Input line to project to.</param>
	/// <param name="outProjectionProfile">Output path projection.</param>
	/// <param name="diagProjectionSegments">Segments corresponding to every profile value.</param>
	AVL_FUNCTION void PathProjectionProfile
	(
		const avl::Path&				inPath, 
		const avl::Line2D&				inLine, 
		avl::Profile&					outProjectionProfile, 
		atl::Array<avl::Segment2D>&		diagProjectionSegments = atl::Dummy< atl::Array<avl::Segment2D> >() 
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_PATHSPATIALTRANSFORMS_H

