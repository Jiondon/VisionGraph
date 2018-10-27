//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_2DEDGEDETECTION_H
#define AVL_2DEDGEDETECTION_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.h"
#include "ATL/Optional.h"
#include "Enums/Polarity.h"
#include "Image/Image.h"
#include "Path/Path.h"
#include "Region/Region.h"

namespace avl
{


	namespace EdgeFilter
	{
		enum Type
		{
			Canny,
			Deriche,
			Lanser
		};
	}

	namespace EdgeMaskFilter
	{
		enum Type
		{
			Sobel,
			Prewitt
		};
	}


	/// <summary>Extracts a pixel-precise region of continuous edges.</summary>
	/// <param name="inImage">Image from which edges will be extracted.</param>
	/// <param name="inRoi">Region of the image from which edges will be extracted. Default value: atl::NIL.</param>
	/// <param name="inEdgeFilter">Type of edge filter used for computing gradients.</param>
	/// <param name="inStdDevX">Amount of horizontal smoothing used by the edge filter. Default value: 2.0f.</param>
	/// <param name="inStdDevY">Amount of vertical smoothing used by the edge filter. Default value: atl::NIL.</param>
	/// <param name="inEdgeThreshold">Sufficient edge strength; edges of that strength will always be detected. Default value: 15.0f.</param>
	/// <param name="inEdgeHysteresis">Value by which the edge threshold is decreased for edge points neighboring with sufficiently strong edges. Default value: 5.0f.</param>
	/// <param name="inMaxJoiningDistance">Maximal distance between edges that can be joined. Default value: 0.0f.</param>
	/// <param name="inMinBlobArea">Minimal area of an edge blob. Default value: 1.</param>
	/// <param name="outEdgeRegion">Region of the found edges.</param>
	/// <param name="diagGradientMagnitudeImage">Visualization of the gradient magnitude.</param>
	AVL_FUNCTION void DetectEdges_AsRegion
	(
		const avl::Image&			inImage,					
		atl::Optional<const avl::Region&>	inRoi,				
		avl::EdgeFilter::Type		inEdgeFilter,				
		float					inStdDevX,					
		atl::Optional<float>	inStdDevY,					
		float					inEdgeThreshold,			
		float					inEdgeHysteresis,			
		float					inMaxJoiningDistance,		
		const int					inMinBlobArea,				
		avl::Region&				outEdgeRegion,				
		avl::Image&					diagGradientMagnitudeImage = atl::Dummy<avl::Image>()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Extracts a pixel-precise image of continuous edges.</summary>
	/// <param name="inImage">Image from which edges will be extracted.</param>
	/// <param name="inRoi">Region of the image from which edges will be extracted. Default value: atl::NIL.</param>
	/// <param name="inEdgeFilter">Type of edge filter used for computing gradients.</param>
	/// <param name="inStdDevX">Amount of horizontal smoothing used by the edge filter. Default value: 2.0f.</param>
	/// <param name="inStdDevY">Amount of vertical smoothing used by the edge filter (Auto = inStdDevX). Default value: atl::NIL.</param>
	/// <param name="inEdgeThreshold">Sufficient edge strength; edges of that strength will always be detected. Default value: 15.0f.</param>
	/// <param name="inEdgeHysteresis">Value by which the edge threshold is decreased for edge points neighboring with sufficiently strong edges. Default value: 5.0f.</param>
	/// <param name="inMaxJoiningDistance">Maximal distance between edges that can be joined. Default value: 0.0f.</param>
	/// <param name="inMinBlobArea">Minimal area of an edge blob. Default value: 1.</param>
	/// <param name="outEdgesImage">Image of found edges.</param>
	/// <param name="diagGradientMagnitudeImage">Visualization of the gradient magnitude.</param>
	AVL_FUNCTION void DetectEdges
	(
		const avl::Image&			inImage,					
		atl::Optional<const avl::Region&>	inRoi,				
		avl::EdgeFilter::Type		inEdgeFilter,				
		float					inStdDevX,					
		atl::Optional<float>	inStdDevY,					
		float					inEdgeThreshold,			
		float					inEdgeHysteresis,			
		float					inMaxJoiningDistance,		
		const int					inMinBlobArea,				
		avl::Image&					outEdgesImage,				
		avl::Image&					diagGradientMagnitudeImage = atl::Dummy<avl::Image>()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Extracts subpixel-precise paths that represent continuous edges.</summary>
	/// <param name="inImage">Image from which edges will be extracted.</param>
	/// <param name="inRoi">Region of the image from which edges will be extracted. Default value: atl::NIL.</param>
	/// <param name="inEdgeFilter">Type of edge filter used for computing gradients.</param>
	/// <param name="inStdDevX">Amount of horizontal smoothing used by the edge filter. Default value: 2.0f.</param>
	/// <param name="inStdDevY">Amount of vertical smoothing used by the edge filter (Auto = inStdDevX). Default value: atl::NIL.</param>
	/// <param name="inEdgeThreshold">Sufficient edge strength; edges of that strength will always be detected. Default value: 15.0f.</param>
	/// <param name="inEdgeHysteresis">Value by which the edge threshold is decreased for edge points neighboring with sufficiently strong edges. Default value: 5.0f.</param>
	/// <param name="inMaxJoiningDistance">Maximal distance between edges that can be joined. Default value: atl::NIL.</param>
	/// <param name="inMaxJoiningAngle">Maximal allowed angle between edges being joined. Default value: 30.0f.</param>
	/// <param name="inJoiningDistanceBalance">Determines how important distance between edges is according to their angle difference. Default value: 0.0f.</param>
	/// <param name="inJoiningEndingLength">Determines the length of the edge end used for edge angle computing. Default value: atl::NIL.</param>
	/// <param name="inMinEdgeLength">Minimal length of an edge. Default value: 0.0f.</param>
	/// <param name="outEdges">Paths representing found edges.</param>
	/// <param name="diagGradientMagnitudeImage">Visualization of the gradient magnitude.</param>
	/// <param name="diagEdgeRegion">Region representing found edges.</param>
	AVL_FUNCTION void DetectEdges_AsPaths
	(
		const avl::Image&			inImage,					
		atl::Optional<const avl::Region&>	inRoi,				
		avl::EdgeFilter::Type		inEdgeFilter,				
		float					inStdDevX,					
		atl::Optional<float>	inStdDevY,					
		float					inEdgeThreshold,			
		float					inEdgeHysteresis,			
		atl::Optional<float>	inMaxJoiningDistance,		
		float					inMaxJoiningAngle,			
		float					inJoiningDistanceBalance,	
		atl::Optional<float>	inJoiningEndingLength,		
		float					inMinEdgeLength,			
		atl::Array<avl::Path>&		outEdges,					
		avl::Image&					diagGradientMagnitudeImage = atl::Dummy<avl::Image>(),	
		avl::Region&				diagEdgeRegion = atl::Dummy<avl::Region>()				
	)
	THROW_AVL_ERRORS;

	/// <summary>Extracts a pixel-precise region of continuous edges. Faster, yet less accurate version.</summary>
	/// <param name="inImage">Image from which edges will be extracted.</param>
	/// <param name="inRoi">Region of the image from which edges will be extracted. Default value: atl::NIL.</param>
	/// <param name="inEdgeMaskFilter">Type of edge filter used for computing gradients.</param>
	/// <param name="inEdgeThreshold">Sufficient edge strength; edges of that strength will always be detected. Default value: 35.0f.</param>
	/// <param name="inEdgeHysteresis">Value by which the edge threshold is decreased for edge points neighboring with sufficiently strong edges. Default value: 15.0f.</param>
	/// <param name="inMaxJoiningDistance">Maximal distance between edges that can be joined. Default value: 0.0f.</param>
	/// <param name="inMinBlobArea">Minimal area of an edge blob. Default value: 1.</param>
	/// <param name="outEdgeRegion">Region of the found edges.</param>
	/// <param name="diagGradientMagnitudeImage">Visualization of the gradient magnitude.</param>
	AVL_FUNCTION void DetectEdges_AsRegion_Mask
	(
		const avl::Image&					inImage,					
		atl::Optional<const avl::Region&>	inRoi,						
		avl::EdgeMaskFilter::Type			inEdgeMaskFilter,			
		float							inEdgeThreshold,			
		float							inEdgeHysteresis,			
		float							inMaxJoiningDistance,		
		const int							inMinBlobArea,				
		avl::Region&						outEdgeRegion,				
		avl::Image&							diagGradientMagnitudeImage = atl::Dummy<avl::Image>()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Extracts subpixel-precise paths that represent continuous edges. Faster, yet less accurate version.</summary>
	/// <param name="inImage">Image from which edges will be extracted.</param>
	/// <param name="inRoi">Region of the image from which edges will be extracted. Default value: atl::NIL.</param>
	/// <param name="inEdgeMaskFilter">Type of edge filter used for computing gradients.</param>
	/// <param name="inEdgeThreshold">Sufficient edge strength; edges of that strength will always be detected. Default value: 35.0f.</param>
	/// <param name="inEdgeHysteresis">Value by which the edge threshold is decreased for edge points neighboring with sufficiently strong edges. Default value: 15.0f.</param>
	/// <param name="inMaxJoiningDistance">Maximal distance between edges that can be joined. Default value: atl::NIL.</param>
	/// <param name="inMaxJoiningAngle">Maximal allowed angle between edges being joined. Default value: 30.0f.</param>
	/// <param name="inJoiningDistanceBalance">Determines how important distance between edges is according to their angle difference. Default value: 0.0f.</param>
	/// <param name="inJoiningEndingLength">Determines the length of the edge end used for edge angle computing. Default value: atl::NIL.</param>
	/// <param name="inMinEdgeLength">Minimal length of an edge. Default value: 0.0f.</param>
	/// <param name="outEdges">Paths representing found edges.</param>
	/// <param name="diagGradientMagnitudeImage">Visualization of the gradient magnitude.</param>
	/// <param name="diagEdgeRegion">Region representing found edges.</param>
	AVL_FUNCTION void DetectEdges_AsPaths_Mask
	(
		const avl::Image&					inImage,					
		atl::Optional<const avl::Region&>	inRoi,						
		avl::EdgeMaskFilter::Type			inEdgeMaskFilter,			
		float							inEdgeThreshold,			
		float							inEdgeHysteresis,			
		atl::Optional<float>			inMaxJoiningDistance,		
		float							inMaxJoiningAngle,			
		float							inJoiningDistanceBalance,	
		atl::Optional<float>			inJoiningEndingLength,		
		float							inMinEdgeLength,			
		atl::Array<avl::Path>&				outEdges,					
		avl::Image&							diagGradientMagnitudeImage = atl::Dummy<avl::Image>(),	
		avl::Region&						diagEdgeRegion = atl::Dummy<avl::Region>()				
	)
	THROW_AVL_ERRORS;

	/// <summary>Extracts a pixel-precise region of bright or dark thin lines.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="inStdDevX">Smoothing standard deviation (horizontal). Default value: 3.0f.</param>
	/// <param name="inStdDevY">Smoothing standard deviation (vertical, or Auto = horizontal). Default value: atl::NIL.</param>
	/// <param name="inRidgeThreshold">Sufficient ridge strength; ridges of that strength will always be detected. Default value: 5.0f.</param>
	/// <param name="inRidgeHysteresis">Value by which the ridge threshold is decreased for ridge points neighboring with sufficiently strong edges. Default value: 4.0f.</param>
	/// <param name="inMinBlobArea">Minimal area of a ridge blob. Default value: 1.</param>
	AVL_FUNCTION void DetectRidges_AsRegion
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,						
		float							inStdDevX,					
		atl::Optional<float>			inStdDevY,					
		float							inRidgeThreshold,			
		float							inRidgeHysteresis,			
		avl::Polarity::Type					inPolarity,
		const int							inMinBlobArea,				
		avl::Region&						outRidgeRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Extracts subpixel-precise paths that represent bright or dark thin lines.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="inStdDevX">Smoothing standard deviation (horizontal). Default value: 3.0f.</param>
	/// <param name="inStdDevY">Smoothing standard deviation (vertical, or Auto = horizontal). Default value: atl::NIL.</param>
	/// <param name="inRidgeThreshold">Sufficient ridge strength; ridges of that strength will always be detected. Default value: 5.0f.</param>
	/// <param name="inRidgeHysteresis">Value by which the ridge threshold is decreased for ridge points neighboring with sufficiently strong edges. Default value: 4.0f.</param>
	AVL_FUNCTION void DetectRidges_AsPaths
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,				
		float							inStdDevX,			
		atl::Optional<float>			inStdDevY,			
		float							inRidgeThreshold,	
		float							inRidgeHysteresis,	
		avl::Polarity::Type					inPolarity,
		atl::Array<avl::Path>&				outRidges
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_2DEDGEDETECTION_H

