//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_PATHGLOBALTRANSFORMS_H
#define AVL_PATHGLOBALTRANSFORMS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Path/Path.h"

namespace avl
{


	/// <summary>Reduces the number of points in a path preserving its shape with the specified precision.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="inMaxDistance">Maximum distance between (possibly removed in the process) characteristic point of the input path and the output path. Default value: 0.5f.</param>
	/// <param name="outPath">Reduced path.</param>
	/// <param name="diagIntermediatePaths">Intermediate results on all levels of recursion of the Ramer algorithm.</param>
	AVL_FUNCTION void ReducePath
	(
		const avl::Path&		inPath,					
		float				inMaxDistance,			
		avl::Path&				outPath,				
		atl::Array<avl::Path>&	diagIntermediatePaths = atl::Dummy< atl::Array<avl::Path> >()	
	)
	THROW_AVL_ERRORS;

	namespace EquidistanceType
	{
		enum Type
		{
			InputPathEquidistance,
			OutputPathEquidistance
		};
	}


	/// <summary>Creates a new path whose characteristic points lie on the input path, but are equally spaced.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="inStep">Requested distance between consecutive points. Default value: 1.0f.</param>
	/// <param name="inEquidistanceType">Defines how the distance is measured.</param>
	/// <param name="outPath">Output path.</param>
	AVL_FUNCTION void ConvertToEquidistantPath
	(
		const avl::Path&			inPath,
		float					inStep,				
		avl::EquidistanceType::Type	inEquidistanceType,	
		avl::Path&					outPath
	)
	THROW_AVL_ERRORS;

	namespace PathSegmentationMode
	{
		enum Type
		{
			SegmentsAndArcs,
			Segments
		};
	}


	/// <summary>Splits a path into parts that can be approximated as segments or arcs.</summary>
	/// <param name="inPath">Path to be segmented.</param>
	/// <param name="inSmoothingStdDev">Standard deviation used for initial gaussian smoothing of the segmented path.</param>
	/// <param name="inMaxDeviation">Maximal distance between any point of a classified segment to the abstract shape. Default value: 0.5f.</param>
	/// <param name="inSegmentationMode">Whether to use arcs for segmentation.</param>
	/// <param name="inMaxArcRadius">Maximal radius of an arc fitted to segment. Default value: 10.0f.</param>
	/// <param name="outStraight">Parts classified as straight segments.</param>
	/// <param name="outArciform">Parts classified as arciform segments.</param>
	/// <param name="outSegments">Segments corresponding to sections of path from outStraight.</param>
	/// <param name="outArcs">Arcs corresponding to sections of path from outArciform.</param>
	AVL_FUNCTION void SegmentPath
	(
		const avl::Path&				inPath,					
		float						inSmoothingStdDev,		
		float						inMaxDeviation,			
		avl::PathSegmentationMode::Type	inSegmentationMode,		
		atl::Optional<float>		inMaxArcRadius,			
		atl::Array<avl::Path>&			outStraight,			
		atl::Array<avl::Path>&			outArciform,			
		atl::Array<avl::Segment2D>&		outSegments,			
		atl::Array<avl::Arc2D>&			outArcs					
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a bicircular curve passing through the points of the leading path.</summary>
	/// <param name="inLeadingPath">The path that will have its corners rounded.</param>
	/// <param name="inInterpolationPointCount">Number of points used for interpolation between each pair of points on the input path. Default value: 8.</param>
	/// <param name="outBicircularCurve">A smooth output path.</param>
	AVL_FUNCTION void CreateBicircularCurve
	(
		const avl::Path&		inLeadingPath,				
		int						inInterpolationPointCount,	
		avl::Path&				outBicircularCurve			
	)
	THROW_AVL_ERRORS;

	/// <summary>Removes all self-intersections from a given path.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="outPath">Path with no self-intersections.</param>
	AVL_FUNCTION void RemovePathSelfIntersections
	(
		const avl::Path&	inPath,		
		avl::Path&			outPath		
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_PATHGLOBALTRANSFORMS_H

