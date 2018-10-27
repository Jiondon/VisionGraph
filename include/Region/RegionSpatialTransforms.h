//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_REGIONSPATIALTRANSFORMS_H
#define AVL_REGIONSPATIALTRANSFORMS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Enums/Axis.h"
#include "Enums/MirrorDirection.h"
#include "Geometry/Geometry.h"
#include "Region/Region.h"

namespace avl
{


	/// <summary>Mirrors a region across vertical or horizontal axis.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inMirrorDirection">Reverse the order of region columns (horizontal direction) or rows (vertical direction). Default value: Horizontal.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void MirrorRegion
	(
		const avl::Region&					inRegion,
		const avl::MirrorDirection::Type	inMirrorDirection, 
		avl::Region&						outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Translates a region by a given number of pixels along each axis.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inDeltaX">Horizontal shift.</param>
	/// <param name="inDeltaY">Vertical shift.</param>
	/// <param name="inInverse">Negates the delta values.</param>
	/// <param name="inFrameWidth">Output region frame width. Default value: atl::NIL.</param>
	/// <param name="inFrameHeight">Output region frame height. Default value: atl::NIL.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void TranslateRegion
	(
		const avl::Region&		inRegion,
		int						inDeltaX,	
		int						inDeltaY,	
		bool					inInverse,	
		atl::Optional<int>		inFrameWidth, 
		atl::Optional<int>		inFrameHeight, 
		avl::Region&			outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Enlarges a region by a natural factor.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inN">The scaling coefficient. Default value: 2.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void EnlargeRegionNTimes
	(
		const avl::Region&	inRegion,
		int					inN,		
		avl::Region&		outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Flips and rotates a region so that x-coordinates are exchanged with y-coordinates.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void TransposeRegion
	(
		const avl::Region&	inRegion,
		avl::Region&		outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Reflects a region through the given location.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void ReflectRegion
	(
		const avl::Region&		inRegion,
		const avl::Location&	inReflectionCenter,
		avl::Region&			outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Rotates a region around a point.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inCenter">Center of rotation. Default value: atl::NIL.</param>
	/// <param name="inAngle">Clockwise rotation angle.</param>
	/// <param name="inInverse">Switches to counter-clockwise rotation.</param>
	/// <param name="inFrameWidth">Output region frame width. Default value: atl::NIL.</param>
	/// <param name="inFrameHeight">Output region frame height. Default value: atl::NIL.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void RotateRegion
	(
		const avl::Region&					inRegion,
		atl::Optional<const avl::Point2D&>	inCenter,	
		float								inAngle,	
		const bool							inInverse,	
		atl::Optional<int>					inFrameWidth,
		atl::Optional<int>					inFrameHeight,
		avl::Region&						outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes a leant region.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inShear">The relative shift of each consecutive row or column.</param>
	/// <param name="inAxis">Switches between shifting rows or columns.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void ShearRegion
	(
		const avl::Region&	inRegion,
		float			inShear,	
		avl::Axis::Type		inAxis,		
		avl::Region&		outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a region from a rectangular fragment of another one.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inSelection">Box defining the range of cropping.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void CropRegion
	(
		const avl::Region&	inRegion,
		const avl::Box&		inSelection,	
		avl::Region&		outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Inverse of CropRegion</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inSelection">Box defining the range of the original cropping.</param>
	/// <param name="inWidth">Width of the uncropped region.</param>
	/// <param name="inHeight">Height of the uncropped region.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void UncropRegion
	(
		const avl::Region&	inRegion,
		const avl::Box&		inSelection,	
		int					inWidth,		
		int					inHeight,		
		avl::Region&		outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a region from a rectangular fragment of another one.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inRectangle">Rectangle defining a rotated subregion.</param>
	/// <param name="inRectangleAlignment">Adjusts the rectangle to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="outRegion">Output region.</param>
	/// <param name="outAlignedRectangle">Input rectangle after transformation (in the region coordinates).</param>
	/// <param name="outOutputAlignment">Alignment of the output region.</param>
	AVL_FUNCTION void CropRegionToRectangle
	(
		const avl::Region&						inRegion,
		const avl::Rectangle2D&					inRectangle,					
		atl::Optional<const avl::CoordinateSystem2D&>	inRectangleAlignment,	
		avl::Region&							outRegion,
		atl::Optional<avl::Rectangle2D&>		outAlignedRectangle = atl::NIL,	
		atl::Optional<avl::CoordinateSystem2D&>	outOutputAlignment = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Enlarges or shrinks a region to new dimensions.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void ResizeRegion
	(
		const avl::Region&	inRegion,
		atl::Optional<int>	inNewWidth,
		atl::Optional<int>	inNewHeight,
		avl::Region&		outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Resizes region relatively along each axis.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inHorizontalScale">Default value: 1.0f.</param>
	/// <param name="inVerticalScale">Default value: 1.0f.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void ResizeRegion_Relative
	(
		const avl::Region&	inRegion,
		float			inHorizontalScale,
		float			inVerticalScale,
		avl::Region&		outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Aligns a region to a coordinate system.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inAlignment">Coordinate system to align to.</param>
	/// <param name="inInverse">Switches to the inverse transform.</param>
	/// <param name="inFrameWidth">Output region's frame width. Default value: atl::NIL.</param>
	/// <param name="inFrameHeight">Output region's frame height. Default value: atl::NIL.</param>
	AVL_FUNCTION void AlignRegion
	(
		const avl::Region&		inRegion,
		const avl::CoordinateSystem2D&	inAlignment,	
		bool					inInverse,				
		atl::Optional<int>		inFrameWidth,			
		atl::Optional<int>		inFrameHeight,			
		avl::Region&			outAlignedRegion
	)
	THROW_AVL_ERRORS;

	namespace DownsampleRegionMode
	{
		enum Type
		{
			Any,
			All
		};
	}


	/// <summary>Shrinks a region by the factor of two along each axis.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inScaleStep">Defines how many times the region size is divided by 2. Default value: 1.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void DownsampleRegion
	(
		const avl::Region&				inRegion,
		avl::DownsampleRegionMode::Type	inDownsampleRegionMode,
		const int						inScaleStep,	
		avl::Region&					outRegion
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_REGIONSPATIALTRANSFORMS_H

