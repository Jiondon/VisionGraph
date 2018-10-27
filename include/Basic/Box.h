//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVS_BOX_H
#define AVS_BOX_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Enums/Anchor2D.h"
#include "Enums/SplitDirection.h"
#include "Basic/Types.h"
#include "ATL/Array.hxx"
#include "ATL/Optional.h"
#include "Geometry/Geometry.h"

namespace avl
{


	/// <summary>Creates a box.</summary>
	AVL_FUNCTION void CreateBox
	(
		const avl::Location&	inLocation,
		avl::Anchor2D::Type		inLocationAnchor,
		int						inWidth,
		int						inHeight,
		avl::Box&				outBox
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns center of a box.</summary>
	AVL_FUNCTION void BoxCenter
	(
		const avl::Box&	inBox,
		avl::Point2D&	outCenter
	)
	THROW_AVL_ERRORS;

	/// <summary>Splits a box into two along a direction.</summary>
	AVL_FUNCTION void SplitBox
	(
		const avl::Box&						inBox,
		const avl::SplitDirection::Type		inSplitDirection,
		avl::Box&							outBox1,
		avl::Box&							outBox2
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns corners of a box.</summary>
	AVL_FUNCTION void BoxCorners_Deprecated
	(
		const avl::Box&	inBox,
		avl::Point2D&	outTopLeftCorner,
		avl::Point2D&	outTopRightCorner,
		avl::Point2D&	outBottomRightCorner,
		avl::Point2D&	outBottomLeftCorner
	)
	THROW_AVL_ERRORS;

	/// <summary>Shifts a box by a discreet vector.</summary>
	/// <param name="inBox">Input box.</param>
	/// <param name="inDeltaX">Shift along the x axis.</param>
	/// <param name="inDeltaY">Shift along the y axis.</param>
	/// <param name="inInverse">Switches to inverse operation.</param>
	/// <param name="outBox">Shifted box.</param>
	AVL_FUNCTION void TranslateBox
	(
		const avl::Box&	inBox,		
		int			inDeltaX,   
		int			inDeltaY,   
		bool		inInverse,	
		avl::Box&		outBox		
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes the dimensions of a box.</summary>
	/// <param name="inBox">Input box.</param>
	/// <param name="inAnchor">Point of the box which position will not change. Default value: TopLeft.</param>
	/// <param name="inNewWidth">Target width of the box. Default value: atl::NIL.</param>
	/// <param name="inNewHeight">Target height of the box. Default value: atl::NIL.</param>
	/// <param name="outBox">Resized box.</param>
	AVL_FUNCTION void ResizeBox
	(
		const avl::Box&				inBox,		
		avl::Anchor2D::Type	inAnchor,	
		atl::Optional<int>			inNewWidth, 
		atl::Optional<int>			inNewHeight,
		avl::Box&					outBox		
	)
	THROW_AVL_ERRORS;

	/// <summary>Resizes a box to relatively defined dimensions.</summary>
	/// <param name="inBox">Input box.</param>
	/// <param name="inAnchor">Point of the box which position will not change. Default value: TopLeft.</param>
	/// <param name="inHorizontalScale">Scale factor of the horizontal resize. Default value: 1.0f.</param>
	/// <param name="inVerticalScale">Scale factor of the vertical resize. Default value: 1.0f.</param>
	/// <param name="outBox">Resized box.</param>
	AVL_FUNCTION void ResizeBox_Relative
	(
		const avl::Box&		inBox,				
		avl::Anchor2D::Type	inAnchor,			
		float			inHorizontalScale,  
		float			inVerticalScale,	
		avl::Box&			outBox				
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes the dimensions of a box by adding some values.</summary>
	/// <param name="inBox">Input box.</param>
	/// <param name="inAnchor">Point of the box which position will not change. Default value: TopLeft.</param>
	/// <param name="inWidthDelta">Value added to width of the box. Default value: 0.</param>
	/// <param name="inHeightDelta">Value added to height of the box. Default value: 0.</param>
	/// <param name="outBox">Resized box.</param>
	AVL_FUNCTION void ResizeBox_Delta
	(
		const avl::Box&		inBox,		
		avl::Anchor2D::Type	inAnchor,	
		int					inWidthDelta,	
		int					inHeightDelta,	
		avl::Box&			outBox		
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a morphological dilation on a box using box kernel.</summary>
	/// <param name="inBox">Input box.</param>
	/// <param name="inRadiusX">Horizontal radius of the box kernel. Default value: 1.</param>
	/// <param name="inRadiusY">Vertical radius of the box kernel. Default value: atl::NIL.</param>
	/// <param name="outBox">Dilated box.</param>
	AVL_FUNCTION void DilateBox
	(
		const avl::Box&		inBox,		
		const int			inRadiusX,	
		atl::Optional<int>	inRadiusY,	
		avl::Box&			outBox		
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a morphological erosion on a box using box kernel.</summary>
	/// <param name="inBox">Input box.</param>
	/// <param name="inRadiusX">Horizontal radius of the box kernel. Default value: 1.</param>
	/// <param name="inRadiusY">Vertical radius of the box kernel. Default value: atl::NIL.</param>
	/// <param name="outBox">Eroded box.</param>
	AVL_FUNCTION void ErodeBox
	(
		const avl::Box&		inBox,		
		const int			inRadiusX,	
		atl::Optional<int>	inRadiusY,	
		avl::Box&			outBox		
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns a characteristic point (e.g. the top-left) of a box.</summary>
	/// <param name="inPointAnchor">Selecting one of the 9 characteristic points. Default value: TopLeft.</param>
	AVL_FUNCTION void BoxCharacteristicPoint
	(
		const avl::Box&				inBox,
		const avl::Anchor2D::Type	inPointAnchor,	
		avl::Point2D&				outPoint
	)
	THROW_AVL_ERRORS;

	/// <summary>If the input box has both dimensions different from zero, then it is copied to the output; otherwise Nil is returned.</summary>
	AVL_FUNCTION void SkipEmptyBox
	(
		const avl::Box&				inBox,
		atl::Conditional<avl::Box>&	outNotEmptyBox,
		bool&						outIsNotEmpty
	)
	THROW_AVL_ERRORS;

	/// <summary>The input boxes which have both dimensions different from zero are copied to the output.</summary>
	AVL_FUNCTION void RemoveEmptyBoxes
	(
		const atl::Array<avl::Box>&	inBoxes,
		atl::Array<avl::Box>&		outNotEmptyBoxes,
		atl::Array<bool>&			outIsNotEmpty
	)
	THROW_AVL_ERRORS;

	/// <summary>Tests whether the box is empty.</summary>
	AVL_FUNCTION void TestBoxEmpty
	(
		const avl::Box&	inBox,
		bool&			outIsEmpty
	)
	THROW_AVL_ERRORS;

	/// <summary>Tests whether the box is not empty.</summary>
	AVL_FUNCTION void TestBoxNotEmpty
	(
		const avl::Box&	inBox,
		bool&			outIsNotEmpty
	)
	THROW_AVL_ERRORS;

	/// <summary>Tests whether given boxes are equal.</summary>
	AVL_FUNCTION void TestBoxEqualTo
	(
		const avl::Box&	inBox,
		const avl::Box&	inReferenceBox,
		bool&			outIsEqual
	)
	THROW_AVL_ERRORS;

	/// <summary>Tests whether a box is contained in another one.</summary>
	AVL_FUNCTION void TestBoxInBox
	(
		const avl::Box&	inSubBox,
		const avl::Box&	inBox,
		bool&			outIsContained
	)
	THROW_AVL_ERRORS;

	/// <summary>Tests whether two boxes have non-empty intersection.</summary>
	AVL_FUNCTION void TestBoxIntersectsWith
	(
		const avl::Box&	inBox,
		const avl::Box&	inReferenceBox,
		bool&			outBoxesIntersect
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the common part of two boxes.</summary>
	AVL_FUNCTION void BoxIntersection
	(
		const avl::Box& inBox1,
		const avl::Box& inBox2,
		avl::Box&		outBox
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes minimal distance between one of the points of the first box with one of the points of the second box.</summary>
	/// <param name="inResolution">Default value: 1.0f.</param>
	AVL_FUNCTION void BoxToBoxDistance
	(
		const avl::Box&				inBox1,
		const avl::Box&				inBox2,
		float					inResolution,
		float&					outDistance,
		atl::Optional<avl::Segment2D&>	outConnectingSegment = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the bounding box of given boxes.</summary>
	AVL_FUNCTION void BoxesBoundingBox
	(
		const atl::Array<avl::Box>& inBoxes,
		avl::Box&					outBoundingBox
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the bounding box of given boxes; returns NIL if the array is empty.</summary>
	AVL_FUNCTION void BoxesBoundingBox_OrNil
	(
		const atl::Array<avl::Box>& inBoxes,
		atl::Conditional<avl::Box>&	outBoundingBox
	)
	THROW_AVL_ERRORS;

} // namespace avl

namespace avs
{

	/// <summary>Creates a box structure from individual fields.</summary>
	/// <param name="inX">Input x-coordinate.</param>
	/// <param name="inY">Input y-coordinate.</param>
	/// <param name="inWidth">Input width.</param>
	/// <param name="inHeight">Input height.</param>
	/// <param name="outBox">Output box.</param>
	AVL_FUNCTION void AvsFilter_MakeBox
	(
		int			inX,		
		int			inY,		
		int			inWidth,	
		int			inHeight,	
		avl::Box&	outBox		
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns individual fields of box.</summary>
	/// <param name="inBox">Input box.</param>
	/// <param name="outX">Output x-coordinate.</param>
	/// <param name="outY">Output y-coordinate.</param>
	/// <param name="outWidth">Output width.</param>
	/// <param name="outHeight">Output height.</param>
	AVL_FUNCTION void AvsFilter_AccessBox
	(
		const avl::Box&	inBox,		
		int&		outX,			
		int&		outY,			
		int&		outWidth,		
		int&		outHeight		
	)
	THROW_AVL_ERRORS;

} // namespace avs

#endif // AVS_BOX_H

