//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_HOUGHTRANSFORM_H
#define AVL_HOUGHTRANSFORM_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.hxx"
#include "Image/Image.h"
#include "Path/Path.h"
#include "Region/Region.h"
#include "Geometry/Geometry.h"
#include "ComputerVision/HoughTransform/HoughCircle.h"

namespace avl
{


	/// <summary>Finds circles of a given radius in the input image.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Input region of interest. Default value: atl::NIL.</param>
	/// <param name="inRadius">Circles' radius. Default value: 10.0f.</param>
	/// <param name="inMaxOverlap">Maximum accepted overlapping coefficient. Default value: 0.1f.</param>
	/// <param name="inMinScore">Minimum matching score. Default value: 20.0f.</param>
	/// <param name="inEdgeThreshold">Minimum accepted edge magnitude. Default value: 10.0f.</param>
	/// <param name="outCircles">Found circles.</param>
	/// <param name="diagGradientMagnitudeImage">Visualized gradients magnitude of an input image.</param>
	/// <param name="diagScoreImage">Calculated score for each pixel of an input image.</param>
	AVL_FUNCTION void DetectMultipleCircles
	(
		const avl::Image&					inImage,						
		atl::Optional<const avl::Region&>	inRoi,							
		float							inRadius,						
		float							inMaxOverlap,					
		float							inMinScore,						
		float							inEdgeThreshold,				
		atl::Array<avl::HoughCircle>&		outCircles,						
		avl::Image&							diagGradientMagnitudeImage = atl::Dummy<avl::Image>(),		
		avl::Image&							diagScoreImage = atl::Dummy<avl::Image>()					
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds the strongest circle of a given radius in the input image.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Input region of interest. Default value: atl::NIL.</param>
	/// <param name="inRadius">Circle's radius. Default value: 10.0f.</param>
	/// <param name="inMinScore">Minimum matching score. Default value: 20.0f.</param>
	/// <param name="inEdgeThreshold">Minimum accepted edge magnitude. Default value: 10.0f.</param>
	/// <param name="outCircle">Found circle.</param>
	/// <param name="diagGradientMagnitudeImage">Visualized gradients magnitude of an input image.</param>
	/// <param name="diagScoreImage">Calculated score for each pixel of an input image.</param>
	AVL_FUNCTION void DetectSingleCircle
	(
		const avl::Image&					inImage,					
		atl::Optional<const avl::Region&>	inRoi,						
		float							inRadius,					
		float							inMinScore,					
		float							inEdgeThreshold,			
		atl::Conditional<avl::HoughCircle>&	outCircle,					
		avl::Image&							diagGradientMagnitudeImage = atl::Dummy<avl::Image>(),	
		avl::Image&							diagScoreImage = atl::Dummy<avl::Image>()				
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds lines in an image.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Input region of interest. Default value: atl::NIL.</param>
	/// <param name="inAngleResolution">Resolution of lines' orientation. Default value: 1.0f.</param>
	/// <param name="inMinAngleDelta">Minimum angle between two lines. Default value: 20.0f.</param>
	/// <param name="inMinDistance">Minimum distance between two lines. Default value: 20.0f.</param>
	/// <param name="inMinScore">Minimum matching score. Default value: 20.0f.</param>
	/// <param name="inEdgeThreshold">Minimum accepted edge magnitude. Default value: 10.0f.</param>
	/// <param name="outLines">Output lines.</param>
	/// <param name="outScores">Output scores.</param>
	/// <param name="diagGradientMagnitudeImage">Visualized gradients magnitude of an input image.</param>
	/// <param name="diagScoreImage">Calculated score for each pixel of an input image.</param>
	AVL_FUNCTION void DetectLines
	(
		const avl::Image&			inImage,							
		atl::Optional<const avl::Region&> inRoi,						
		float					inAngleResolution,					
		float					inMinAngleDelta,					
		float					inMinDistance,						
		float					inMinScore,							
		float					inEdgeThreshold,					
		atl::Array<avl::Line2D>&	outLines,							
		atl::Array<float>&		outScores,							
		avl::Image&					diagGradientMagnitudeImage = atl::Dummy<avl::Image>(),			
		avl::Image&					diagScoreImage = atl::Dummy<avl::Image>()						
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds segments in an image.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Input region of interest. Default value: atl::NIL.</param>
	/// <param name="inAngleResolution">Resolution of segments' orientation. Default value: 1.0f.</param>
	/// <param name="inMinAngleDelta">Minimum angle between two segments. Default value: 20.0f.</param>
	/// <param name="inMinDistance">Minimum distance between two segments. Default value: 20.0f.</param>
	/// <param name="inMinLength">Minimum segment length. Default value: 20.0f.</param>
	/// <param name="inMinScore">Minimum matching score. Default value: 20.0f.</param>
	/// <param name="inEdgeThreshold">Minimum accepted edge magnitude. Default value: 10.0f.</param>
	/// <param name="outSegments">Output segments.</param>
	/// <param name="diagGradientMagnitudeImage">Visualized gradients magnitude of an input image.</param>
	/// <param name="diagScoreImage">Calculated score for each pixel of an input image.</param>
	AVL_FUNCTION void DetectSegments
	(
		const avl::Image&			inImage,						
		atl::Optional<const avl::Region&> inRoi,					
		float					inAngleResolution,				
		float					inMinAngleDelta,				
		float					inMinDistance,					
		float					inMinLength,					
		float					inMinScore,						
		float					inEdgeThreshold,				
		atl::Array<avl::Segment2D>&	outSegments,					
		avl::Image&					diagGradientMagnitudeImage = atl::Dummy<avl::Image>(),		
		avl::Image&					diagScoreImage = atl::Dummy<avl::Image>()					
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds paths in an image.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Input region of interest. Default value: atl::NIL.</param>
	/// <param name="inPath">Input path.</param>
	/// <param name="inMinScore">Minimum matching score. Default value: 20.0f.</param>
	/// <param name="inEdgeThreshold">Minimum accepted edge magnitude. Default value: 10.0f.</param>
	/// <param name="outPaths">Output paths.</param>
	/// <param name="outScores">Output scores.</param>
	/// <param name="diagGradientMagnitudeImage">Visualized gradients magnitude of an input image.</param>
	/// <param name="diagScoreImage">Calculated score for each pixel of an input image.</param>
	AVL_FUNCTION void DetectPaths
	(
		const avl::Image&			inImage,						
		atl::Optional<const avl::Region&> inRoi,					
		const avl::Path&			inPath,							
		float					inMinScore,						
		float					inEdgeThreshold,				
		atl::Array<avl::Path>&		outPaths,						
		atl::Array<float>&		outScores,						
		avl::Image&					diagGradientMagnitudeImage = atl::Dummy<avl::Image>(),		
		avl::Image&					diagScoreImage = atl::Dummy<avl::Image>()					
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_HOUGHTRANSFORM_H

