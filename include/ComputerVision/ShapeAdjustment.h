//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_SHAPEADJUSTMENT_H
#define AVL_SHAPEADJUSTMENT_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Enums/AdjustmentMetric.h"
#include "Geometry/Geometry.h"
#include "Image/Image.h"
#include "Path/Path.h"

namespace avl
{


	/// <summary>Translates, rotates and scales the given contour set to the edges of the input image with subpixel precision.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inPaths">Paths to be adjusted. For sparse, synthetic paths the inPointSpacing needs to be specified.</param>
	/// <param name="inPointSpacing">If set, sampling points of the input path will be equidistant with specified spacing. Useful for increasing density of synthetic, sparse paths. Default value: atl::NIL.</param>
	/// <param name="inAlignment">Alignment to be corrected, usually connects to outObject.Alignment of LocateObjects filter. Default value: atl::NIL.</param>
	/// <param name="inAttractionRadius">Expected initial distance between inPaths and edges of the input image. Default value: 2.0f.</param>
	/// <param name="inAdjustmentMetric">Metric used for path attraction. The SegmentDistance minimizes distances along path normal vectors, and thus adjustment is more accurate. PointDistance_* minimize euclidean distance, adjustment tends to be more stable. Default value: SegmentDistance.</param>
	/// <param name="inAdjustTranslation">Compute the translation part of adjustment transform. Must be true when using AttractPathTangents estimation method. Default value: True.</param>
	/// <param name="inAdjustRotation">Compute the rotation part of adjustment transform. Default value: True.</param>
	/// <param name="inAdjustScale">Compute the scale part of adjustment transform. Default value: False.</param>
	/// <param name="inIterationCount">Number of iterations of internal adjustment algorithm. Default value: 6.</param>
	/// <param name="inBaseGradient">Threshold for suppression of weak input image gradients. Increase for very noisy images. Default value: 1.0f.</param>
	/// <param name="outAdjustedPaths">Adjusted output paths.</param>
	/// <param name="outAlignment">Corrected alignment - the inAlignment input modified with estimated adjustment parameters.</param>
	/// <param name="diagAttractionVectors">Attraction vectors from first iteration.</param>
	AVL_FUNCTION void AdjustPathArrayToEdges
	(
		const avl::Image&				inImage, 
		const atl::Array< avl::Path >&	inPaths, 
		atl::Optional<float>			inPointSpacing, 
		atl::Optional<const avl::CoordinateSystem2D&>	inAlignment, 
		float							inAttractionRadius, 
		avl::AdjustmentMetric::Type		inAdjustmentMetric, 
		bool							inAdjustTranslation, 
		bool							inAdjustRotation, 
		bool							inAdjustScale, 
		int								inIterationCount, 
		float							inBaseGradient, 
		atl::Array< avl::Path >&		outAdjustedPaths, 
		avl::CoordinateSystem2D&		outAlignment, 
		atl::Array<avl::Segment2D>&		diagAttractionVectors = atl::Dummy< atl::Array<avl::Segment2D> >() 
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_SHAPEADJUSTMENT_H

