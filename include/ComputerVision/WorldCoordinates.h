//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_WORLDCOORDINATES_H
#define AVL_WORLDCOORDINATES_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Geometry3D/Geometry3D.h"
#include "Path/Path.h"
#include "ComputerVision/CameraCalibration/CameraCalibrationStructs.h"

namespace avl
{


	/// <summary>Calculates the world plane for the given sets of corresponding 2D and 3D points.</summary>
	/// <param name="outWorldPlane">Calibrated world plane.</param>
	/// <param name="outError">Average distance between provided points and points found on calibration plane.</param>
	/// <param name="outCorrectedImagePoints">Points projected to the found plane.</param>
	/// <param name="outCorrectedWorldPoints">World points found using output plane.</param>
	AVL_FUNCTION void CalibrateWorldCoordinates
	(
		const atl::Array<avl::Point2D>&		inImagePoints,
		const atl::Array<avl::Point3D>&		inWorldPoints,
		float&							outResolution,
		avl::Position3D&					outWorldPlane,					
		float&							outError,						
		atl::Array<avl::Point2D>&			outCorrectedImagePoints,		
		atl::Array<avl::Point3D>&			outCorrectedWorldPoints			
	)
	THROW_AVL_ERRORS;

	/// <summary>Calculates a world plane from the given coordinate system.</summary>
	AVL_FUNCTION void CoordinateSystem2DToPosition3D
	(
		const avl::CoordinateSystem2D&		inCoordinateSystem2D,
		avl::Position3D&					outPosition3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Calculates real-world coordinates corresponding to the specified image coordinates.</summary>
	/// <param name="inWorldPlane">Calibrated world plane.</param>
	/// <param name="inResolution">Number of real-world units per pixel, usually mm/px. Default value: 1.0f.</param>
	AVL_FUNCTION void PointToWorldCoordinates
	(
		const avl::Point2D&			inImagePoint,
		const avl::Position3D&		inWorldPlane,	
		float					inResolution,	
		avl::Point3D&				outWorldPoint
	)
	THROW_AVL_ERRORS;

	/// <summary>Calculates image coordinates corresponding to the specified real-world coordinates.</summary>
	/// <param name="inWorldPlane">Calibrated world plane.</param>
	/// <param name="inResolution">Number of real-world units per pixel, usually mm/px. Default value: 1.0f.</param>
	AVL_FUNCTION void PointToImageCoordinates
	(
		const avl::Point3D&					inWorldPoint,
		const avl::Position3D&				inWorldPlane,	
		float							inResolution,	
		avl::Point2D&						outImagePoint
	)
	THROW_AVL_ERRORS;

	/// <summary>Calculates a path in real-world coordinates corresponding to the specified path in image coordinates.</summary>
	/// <param name="inPath">Input path.</param>
	/// <param name="inWorldPlane">Calibrated world plane.</param>
	/// <param name="inResolution">Number of real-world units per pixel, usually mm/px. Default value: 1.0f.</param>
	AVL_FUNCTION void PathToWorldCoordinates
	(
		const avl::Path&			inPath,
		const avl::Position3D&		inWorldPlane,	
		float					inResolution,	
		atl::Array<avl::Point3D>&	outWorldPoints
	)
	THROW_AVL_ERRORS;

	/// <summary>Calculates a segment in real-world coordinates corresponding to the specified segment in image coordinates.</summary>
	/// <param name="inWorldPlane">Calibrated world plane.</param>
	/// <param name="inResolution">Number of real-world units per pixel, usually mm/px. Default value: 1.0f.</param>
	AVL_FUNCTION void SegmentToWorldCoordinates
	(
		const avl::Segment2D&		inSegment,
		const avl::Position3D&		inWorldPlane,	
		float					inResolution,	
		atl::Array<avl::Point3D>&	outWorldPoints
	)
	THROW_AVL_ERRORS;

	/// <summary>Calculates a distance in real-world units.</summary>
	/// <param name="inPixelDistance">Distance between two points in an image.</param>
	/// <param name="inResolution">Number of real-world units per pixel, usually mm/px. Default value: 1.0f.</param>
	/// <param name="inBias">Compensation for systematic error in measurements (in real-world units). Default value: 0.0f.</param>
	/// <param name="outRealDistance">Distance between two points in real-world units.</param>
	AVL_FUNCTION void PixelToRealDistance
	(
		const float	inPixelDistance,	
		const float	inResolution,		
		const float	inBias,				
		float&		outRealDistance		
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_WORLDCOORDINATES_H

