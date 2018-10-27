//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_GEOMETRY3DFEATURES_H
#define AVL_GEOMETRY3DFEATURES_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Enums/Anchor3D.h"
#include "Geometry3D/Geometry3D.h"

namespace avl
{


	/// <summary>Computes the length of a 3D vector.</summary>
	AVL_FUNCTION void Vector3DLength
	(
		const avl::Vector3D&	inVector3D,
		float&					outLength
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the angle between a 3D vector's projection to the XY plane and the X axis measured toward Y axis, as an angle in the range from 0 to 360.</summary>
	AVL_FUNCTION void Vector3DAzimuth
	(
		const avl::Vector3D&	inVector3D,
		float&					outAzimuth
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the angle between a 3D vector's projection to the XY plane and itself measured toward Z axis, as an angle in the range from -90 to 90.</summary>
	AVL_FUNCTION void Vector3DElevation
	(
		const avl::Vector3D&	inVector3D,
		float&					outElevation
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest box in 3D containing an array of points in 3D.</summary>
	AVL_FUNCTION void PointsBoundingBox3D
	(
		const atl::Array<avl::Point3D>& inPoints,
		avl::Box3D&						outBoundingBox3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest box in 3D containing an array of points in 3D; returns NIL if the array is empty.</summary>
	AVL_FUNCTION void PointsBoundingBox3D_OrNil
	(
		const atl::Array<avl::Point3D>& inPoints,
		atl::Conditional<avl::Box3D>&	outBoundingBox3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the orientation of a plane as angles in the range from 0 to 180 between the plane and coordinate planes.</summary>
	/// <param name="outPointOnPlane">Projection of the beginning of the coordinate axes on the input plane.</param>
	AVL_FUNCTION void Plane3DOrientation
	(
		const avl::Plane3D&	inPlane,
		float&				outAngleXY,
		float&				outAngleXZ,
		float&				outAngleYZ,
		atl::Optional<avl::Point3D&>	outPointOnPlane = atl::NIL 
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the normal vector of a line</summary>
	AVL_FUNCTION void Plane3DNormalVector
	(
		const avl::Plane3D&	inPlane,
		avl::Vector3D&		outNormalVector
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the central point of the input points.</summary>
	/// <param name="inPoints">Input array of points.</param>
	/// <param name="outMassCenter">Central point of input points.</param>
	AVL_FUNCTION void PointsMassCenter3D
	(
		const atl::Array<avl::Point3D>&	inPoints,		
		avl::Point3D&					outMassCenter	
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns a characteristic point of a box in 3D.</summary>
	/// <param name="inPoint3DAnchor">Selecting one of the 27 characteristic points.</param>
	AVL_FUNCTION void Box3DCharacteristicPoint
	(
		const avl::Box3D&		inBox3D,
		const avl::Anchor3D&	inPoint3DAnchor,	
		avl::Point3D&			outPoint3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the volume of the input box in 3D.</summary>
	AVL_FUNCTION void Box3DVolume
	(
		const avl::Box3D&	inBox3D,
		float&				outVolume
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the surface area of the input box in 3D.</summary>
	AVL_FUNCTION void Box3DSurfaceArea
	(
		const avl::Box3D&	inBox3D,
		float&				outSurfaceArea
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the center of the input box in 3D.</summary>
	AVL_FUNCTION void Box3DCenter
	(
		const avl::Box3D&	inBox3D,
		avl::Point3D&		outCenter
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the bounding box 3D of given boxes in 3D.</summary>
	AVL_FUNCTION void BoxesBoundingBox3D
	(
		const atl::Array<avl::Box3D>&	inBoxes3D,
		avl::Box3D&						outBoundingBox3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the bounding box 3D of given boxes in 3D; returns NIL if the array is empty.</summary>
	AVL_FUNCTION void Boxes3DBoundingBox3D_OrNil
	(
		const atl::Array<avl::Box3D>&	inBoxes3D,
		atl::Conditional<avl::Box3D>&	outBoundingBox3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the center point of a segment in 3D.</summary>
	AVL_FUNCTION void Segment3DCenter
	(
		const avl::Segment3D&	inSegment3D,
		avl::Point3D&			outCenterPoint
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the length of a segment in 3D.</summary>
	AVL_FUNCTION void Segment3DLength
	(
		const avl::Segment3D&	inSegment3D,
		float&					outLength
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes a plane passing through the center of a segment in 3D at a right angle.</summary>
	AVL_FUNCTION void Segment3DBisector
	(
		const avl::Segment3D&	inSegment3D,
		avl::Plane3D&			outBisector
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns the vector [x2 - x1, y2 - y1, z2 - z1]</summary>
	AVL_FUNCTION void Segment3DVector
	(
		const avl::Segment3D&	inSegment3D,
		avl::Vector3D&			outVector3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the line in 3D passing through a segment.</summary>
	/// <param name="inSegment3D">Input segment in 3D.</param>
	/// <param name="outLine3D">The resulting line.</param>
	AVL_FUNCTION void Segment3DLine
	(
		const avl::Segment3D&	inSegment3D,	
		avl::Line3D&			outLine3D		
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest box in 3D containing a segment in 3D.</summary>
	AVL_FUNCTION void Segment3DBoundingBox
	(
		const avl::Segment3D&	inSegment3D,
		avl::Box3D&				outBoundingBox3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the area of a circle in 3D.</summary>
	AVL_FUNCTION void Circle3DArea
	(
		const avl::Circle3D&	inCircle3D,
		float&					outArea
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the length of a circle in 3D perimeter.</summary>
	AVL_FUNCTION void Circle3DPerimeterLength
	(
		const avl::Circle3D&	inCircle3D,
		float&					outPerimeterLength
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the smallest box in 3D containing a circle in 3D.</summary>
	AVL_FUNCTION void Circle3DBoundingBox
	(
		const avl::Circle3D&	inCircle3D,
		avl::Box3D&				outBoundingBox3D
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_GEOMETRY3DFEATURES_H

