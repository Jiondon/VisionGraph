//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVS_PATHBASICS_H
#define AVS_PATHBASICS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Geometry/Geometry.h"
#include "Path/Path.h"

namespace avl
{


	/// <summary>Appends a point to a path.</summary>
	/// <param name="inPoint">Input point.</param>
	AVL_FUNCTION void AppendPointToPath
	(
		avl::Path&				ioPath,
		const avl::Point2D&		inPoint		
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates an open path containing collinear, equidistant points.</summary>
	/// <param name="inBegin">First point of the path.</param>
	/// <param name="inEnd">Last point of the path.</param>
	/// <param name="inPointCount">Number of points in the created path. Default value: 2.</param>
	/// <param name="outPath">Output path.</param>
	AVL_FUNCTION void CreateSegmentPath
	(
		const avl::Point2D&		inBegin,		
		const avl::Point2D&		inEnd,			
		int						inPointCount,	
		avl::Path&				outPath
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates an open path containing cocircular, equidistant points.</summary>
	/// <param name="inPointCount">Number of points in the resulting path. Default value: 8.</param>
	/// <param name="outPath">Output path.</param>
	AVL_FUNCTION void CreateArcPath
	(
		const avl::Arc2D&	inArc,
		int					inPointCount,	
		avl::Path&			outPath
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a closed path containing cocircular, equidistant points.</summary>
	/// <param name="inPointCount">Number of points in the resulting path. Default value: 8.</param>
	/// <param name="outPath">Output path.</param>
	AVL_FUNCTION void CreateCirclePath
	(
		const avl::Circle2D&	inCircle,
		int						inPointCount,	
		avl::Path&				outPath
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a closed path containing elliptical, equidistant points.</summary>
	/// <param name="inPointCount">Number of points in the resulting path. Default value: 8.</param>
	/// <param name="outPath">Output path.</param>
	AVL_FUNCTION void CreateEllipsePath
	(
		const avl::Point2D&		inCenter,
		float				inRadiusX,
		float				inRadiusY,
		int						inPointCount,	
		avl::Path&				outPath
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a closed path containing four vertices of rectangle.</summary>
	/// <param name="outPath">Output path.</param>
	AVL_FUNCTION void CreateRectanglePath
	(
		const avl::Rectangle2D&	inRectangle,
		avl::Path&				outPath
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the selected characteristic point of a path.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="inIndex">Index of a point of the input path.</param>
	/// <param name="inInverse">Reversed order of points.</param>
	AVL_FUNCTION void GetPathCharacteristicPoint
	(
		const avl::Path&	inPath,
		int					inIndex,	
		const bool			inInverse,	
		avl::Point2D&		outPoint
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns linear interpolation between two consecutive characteristic points of a path.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="inIndex">Real-valued point index; fractional values result in interpolation.</param>
	AVL_FUNCTION void GetPathCharacteristicPoint_Interpolated
	(
		const avl::Path&	inPath,
		float			inIndex,	
		avl::Point2D&		outPoint
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns a path point of desired distance (measured along path) from the first point of the path.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="inDistanceAlongPath">Distance along path from the first characteristic point to the desired point.</param>
	AVL_FUNCTION void GetPointOnPath
	(
		const avl::Path&	inPath,
		const float		inDistanceAlongPath, 
		avl::Point2D&		outPoint
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the selected segment of a path.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="inInverse">Reversed order of segments.</param>
	AVL_FUNCTION void GetPathSegment
	(
		const avl::Path&	inPath,
		int					inIndex,
		const bool			inInverse,	
		avl::Segment2D&		outSegment
	)
	THROW_AVL_ERRORS;

	/// <summary>Removes the segment connecting last point to the first one from a path.</summary>
	AVL_FUNCTION void OpenPath
	(
		avl::Path&	ioPath
	)
	THROW_AVL_ERRORS;

	/// <summary>Adds the segment connecting last point to the first one to a path.</summary>
	AVL_FUNCTION void ClosePath
	(
		avl::Path&	ioPath
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes an open path that consists of contiguous subsequence of another path points.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="inStart">Index of the first point of the subpath.</param>
	/// <param name="inPointCount">Number of points in the subpath. Default value: 1.</param>
	/// <param name="outPath">The resulting subpath.</param>
	AVL_FUNCTION void Subpath
	(
		const avl::Path&	inPath,			
		const int			inStart,		
		const int			inPointCount,	
		avl::Path&			outPath			
	)
	THROW_AVL_ERRORS;

	/// <summary>If the input path has at least one point, then it is copied to the output; otherwise Nil is returned.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="outNotEmptyPath">A copy of the input path, if it is not empty, or Nil otherwise.</param>
	/// <param name="outIsNotEmpty">Indication if the input path is not empty.</param>
	AVL_FUNCTION void SkipEmptyPath
	(
		const avl::Path&				inPath,
		atl::Conditional<avl::Path>&	outNotEmptyPath,	
		bool&							outIsNotEmpty		
	)
	THROW_AVL_ERRORS;

	/// <summary>If the input path is closed and has no self-intersections, then it is copied to the output; otherwise Nil is returned.</summary>
	/// <param name="inPath">Input path.</param>
	AVL_FUNCTION void SkipNotShape
	(
		const avl::Path&				inPath,
		atl::Conditional<avl::Path>&	outShape,
		bool&							outIsShape
	)
	THROW_AVL_ERRORS;

	/// <summary>Saves serialized Path object as avdata file.</summary>
	/// <param name="inPath">Path to be serialized.</param>
	/// <param name="inFilename">Name of the target file.</param>
	AVL_FUNCTION void SavePath
	(
		const avl::Path&	inPath,			
		const atl::File&	inFilename		
	)
	THROW_AVL_ERRORS;

	/// <summary>Loads serialized Path object from avdata file.</summary>
	/// <param name="inFilename">Name of the source file.</param>
	/// <param name="outPath">Deserialized output Path.</param>
	AVL_FUNCTION void LoadPath
	(
		const atl::File&	inFilename,		
		avl::Path&			outPath			
	)
	THROW_AVL_ERRORS;

} // namespace avl

namespace avs
{

	/// <summary>Creates a path structure.</summary>
	/// <param name="inPoints">Input points of the path.</param>
	/// <param name="inClosed">Input whether the path is closed.</param>
	/// <param name="outPath">Output path.</param>
	AVL_FUNCTION void AvsFilter_MakePath
	(
		const atl::Array<avl::Point2D>&		inPoints,		
		bool								inClosed,		
		avl::Path&							outPath			
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns individual fields of a path.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="outPoints">Output points of the path.</param>
	/// <param name="outClosed">Output whether the path is closed.</param>
	AVL_FUNCTION void AvsFilter_AccessPath
	(
		const avl::Path&			inPath,			
		atl::Array<avl::Point2D>&	outPoints,		
		bool&						outClosed		
	)
	THROW_AVL_ERRORS;

} // namespace avs

#endif // AVS_PATHBASICS_H

