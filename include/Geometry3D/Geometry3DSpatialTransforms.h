//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_GEOMETRY3DSPATIALTRANSFORMS_H
#define AVL_GEOMETRY3DSPATIALTRANSFORMS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Geometry3D/Geometry3D.h"
#include "Enums/Anchor3D.h"

namespace avl
{


	/// <summary>Translates a point by a vector.</summary>
	/// <param name="inDelta">Translation vector.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void TranslatePoint3D
	(
		const avl::Point3D&		inPoint3D,
		const avl::Vector3D&	inDelta,	
		bool					inInverse,	
		avl::Point3D&			outPoint3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Translates an array of points by a vector.</summary>
	/// <param name="inDelta">Translation vector.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void TranslatePoint3DArray
	(
		const atl::Array<avl::Point3D>&	inPoints3D,
		const avl::Vector3D&			inDelta,	
		bool							inInverse,	
		atl::Array<avl::Point3D>&		outPoints3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Translates a point in 3D towards another point in 3D by a specified distance.</summary>
	/// <param name="inTargetPoint">Defines the direction of the translation.</param>
	/// <param name="inDistance">The distance between inPoint3D and outPoint3D.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void TranslatePoint3D_Toward
	(
		const avl::Point3D&	inPoint3D,
		const avl::Point3D&	inTargetPoint,		
		float				inDistance,			
		bool				inInverse,			
		avl::Point3D&		outPoint3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes the distance of a point to a reference point.</summary>
	/// <param name="inReferencePoint">Point to which the distance will be changed.</param>
	/// <param name="inScale">Scaling factor. Default value: 1.0f.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RescalePoint3D
	(
		const avl::Point3D&	inPoint3D,
		const avl::Point3D&	inReferencePoint,	
		float				inScale,			
		bool				inInverse,			
		avl::Point3D&		outPoint3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes the distances of array points to a reference point.</summary>
	/// <param name="inReferencePoint">Point to which the distances will be changed.</param>
	/// <param name="inScale">Scaling factor. Default value: 1.0f.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RescalePoint3DArray
	(
		const atl::Array<avl::Point3D>&	inPoints3D,
		const avl::Point3D&				inReferencePoint,	
		float							inScale,			
		bool							inInverse,			
		atl::Array<avl::Point3D>&		outPoints3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Applies a general transformation expressed by a matrix to a 3D point.</summary>
	/// <param name="inTransform">Transformation 3x3 matrix.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void TransformPoint3D
	(
		const avl::Point3D&	inPoint3D,
		const avl::Matrix&	inTransform,	
		bool				inInverse,		
		avl::Point3D&		outPoint3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Applies a general transformation expressed by a matrix to an array of 3D points.</summary>
	/// <param name="inTransform">Transformation 3x3 matrix.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void TransformPoint3DArray
	(
		const atl::Array<avl::Point3D>&	inPoints3D,
		const avl::Matrix&				inTransform,	
		bool							inInverse,		
		atl::Array<avl::Point3D>&		outPoints3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a point through a simple orthogonal projection, parallel to the Z axis.</summary>
	/// <param name="inCenter">Center of projection, i.e. the target for projected points (0, 0, z).</param>
	AVL_FUNCTION void ProjectPointOrthogonal
	(
		const avl::Point3D&	inPoint3D,
		const avl::Point2D&	inCenter,	
		avl::Point2D&		outPoint2D
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a point through a perspective projection, parallel to the Z axis.</summary>
	/// <param name="inCenter">Center of projection, i.e. the target for projected points (x_focal, y_focal, z).</param>
	/// <param name="inFocalPoint">The camera center, i.e. the point we measure (x, y, z) against.</param>
	/// <param name="inFocalLength">The multiplier for the x and y coordinates, which is divided by z. If negative, projects in opposite direction.</param>
	AVL_FUNCTION void ProjectPointPerspective
	(
		const avl::Point3D&	inPoint3D,
		const avl::Point2D&	inCenter,		
		const avl::Point3D&	inFocalPoint,	
		float			inFocalLength,	
		avl::Point2D&		outPoint2D
	)
	THROW_AVL_ERRORS;

	/// <summary>Projects a point 3D onto a line in 3D.</summary>
	/// <param name="outPointOnLine3D">Point projected on a line orthogonally.</param>
	AVL_FUNCTION void ProjectPointOnLine3D
	(
		const avl::Point3D&	inPoint3D,
		const avl::Line3D&	inLine3D,
		avl::Point3D&		outPointOnLine3D	
	)
	THROW_AVL_ERRORS;

	/// <summary>Projects a point 3D onto a plane.</summary>
	/// <param name="outPointOnPlane">Point projected on a plane orthogonally.</param>
	AVL_FUNCTION void ProjectPointOntoPlane3D
	(
		const avl::Point3D&	inPoint3D,
		const avl::Plane3D&	inPlane,
		avl::Point3D&		outPointOnPlane	
	)
	THROW_AVL_ERRORS;

	/// <summary>Projects a point on a plane Z=0 onto a given plane, translating it parallel to Z axis.</summary>
	/// <param name="outPointOnPlane">Point projected on a plane parallel to Z axis.</param>
	AVL_FUNCTION void ProjectPoint2DOntoPlane3D
	(
		const avl::Point2D&	inPoint2D,
		const avl::Plane3D&	inPlane,
		avl::Point3D&		outPointOnPlane	
	)
	THROW_AVL_ERRORS;

	/// <summary>Projects a line 3D onto a plane.</summary>
	/// <param name="outLineOnPlane">Line in 3D projected on a plane orthogonally.</param>
	AVL_FUNCTION void ProjectLineOntoPlane3D
	(
		const avl::Line3D&	inLine3D,
		const avl::Plane3D&	inPlane,
		avl::Line3D&		outLineOnPlane	
	)
	THROW_AVL_ERRORS;

	/// <summary>Shifts a box in 3D by a vector.</summary>
	/// <param name="inBox3D">Input box in 3D.</param>
	/// <param name="inDelta">Translation vector.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	/// <param name="outBox3D">Shifted box.</param>
	AVL_FUNCTION void TranslateBox3D
	(
		const avl::Box3D&		inBox3D,		
		const avl::Vector3D&	inDelta,		
		bool					inInverse,		
		avl::Box3D&				outBox3D		
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes the dimensions of a box in 3D.</summary>
	/// <param name="inBox3D">Input box in 3D.</param>
	/// <param name="inAnchor">Point of the box in 3D which position will not change.</param>
	/// <param name="inNewXLength">Target length of the box in x-coordinate. Default value: atl::NIL.</param>
	/// <param name="inNewYLength">Target length of the box in y-coordinate. Default value: atl::NIL.</param>
	/// <param name="inNewZLength">Target length of the box in z-coordinate. Default value: atl::NIL.</param>
	/// <param name="outBox3D">Resized box.</param>
	AVL_FUNCTION void ResizeBox3D
	(
		const avl::Box3D&		inBox3D,		
		const avl::Anchor3D&	inAnchor,		
		atl::Optional<float>	inNewXLength,	
		atl::Optional<float>	inNewYLength,	
		atl::Optional<float>	inNewZLength,	
		avl::Box3D&				outBox3D		
	)
	THROW_AVL_ERRORS;

	/// <summary>Resizes a box in 3D to relatively defined dimensions.</summary>
	/// <param name="inBox3D">Input box in 3D.</param>
	/// <param name="inAnchor">Point of the box in 3D which position will not change.</param>
	/// <param name="inXScale">Scale factor in X axis. Default value: 1.0f.</param>
	/// <param name="inYScale">Scale factor in Y axis. Default value: 1.0f.</param>
	/// <param name="inZScale">Scale factor in Z axis. Default value: 1.0f.</param>
	/// <param name="outBox3D">Resized box.</param>
	AVL_FUNCTION void ResizeBox3D_Relative
	(
		const avl::Box3D&		inBox3D,	
		const avl::Anchor3D&	inAnchor,	
		float					inXScale,	
		float					inYScale,	
		float					inZScale,	
		avl::Box3D&				outBox3D	
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes the dimensions of a box in 3D by adding some values.</summary>
	/// <param name="inBox3D">Input box.</param>
	/// <param name="inAnchor">Point of the box in 3D which position will not change.</param>
	/// <param name="inXLengthDelta">Value added to length of the box in X axis. Default value: 0.0f.</param>
	/// <param name="inYLengthDelta">Value added to length of the box in X axis. Default value: 0.0f.</param>
	/// <param name="inZLengthDelta">Value added to length of the box in X axis. Default value: 0.0f.</param>
	/// <param name="outBox3D">Resized box.</param>
	AVL_FUNCTION void ResizeBox3D_Delta
	(
		const avl::Box3D&		inBox3D,		
		const avl::Anchor3D&	inAnchor,		
		float					inXLengthDelta,	
		float					inYLengthDelta,	
		float					inZLengthDelta,	
		avl::Box3D&				outBox3D		
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes the distances of box in 3D to a reference point.</summary>
	/// <param name="inReferencePoint">Point to which the distances will be changed.</param>
	/// <param name="inScale">Scaling factor. Default value: 1.0f.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RescaleBox3D
	(
		const avl::Box3D&	inBox3D,
		const avl::Point3D&	inReferencePoint,	
		float				inScale,			
		bool				inInverse,			
		avl::Box3D&			outBox3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Shifts a segment in 3D by a vector.</summary>
	/// <param name="inSegment3D">Input segment in 3D.</param>
	/// <param name="inDelta">Translation vector.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	/// <param name="outSegment3D">Shifted segment.</param>
	AVL_FUNCTION void TranslateSegment3D
	(
		const avl::Segment3D&	inSegment3D,	
		const avl::Vector3D&	inDelta,		
		bool					inInverse,		
		avl::Segment3D&			outSegment3D	
	)
	THROW_AVL_ERRORS;

	/// <summary>Lengthens or shortens a segment in 3D to a new length preserving its orientation and center point.</summary>
	/// <param name="inNewLength">Default value: 1.0f.</param>
	/// <param name="inAnchor">Anchor point, 0 means the beginning, 1 means the end of the segment. Default value: 0.5f.</param>
	AVL_FUNCTION void ResizeSegment3D
	(
		const avl::Segment3D&	inSegment3D,
		float					inNewLength,
		float					inAnchor,		
		avl::Segment3D&			outSegment3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes length of a segment in 3D by adding a value preserving its orientation and center point.</summary>
	/// <param name="inDelta">Value added to segment length. Default value: 0.0f.</param>
	/// <param name="inAnchor">Anchor point, 0 means the beginning, 1 means the end of the segment. Default value: 0.5f.</param>
	AVL_FUNCTION void ResizeSegment3D_Delta
	(
		const avl::Segment3D&	inSegment3D,
		float					inDelta,	
		float					inAnchor,	
		avl::Segment3D&			outSegment3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Lengthens or shortens a segment in 3D relatively.</summary>
	/// <param name="inSegment3D">Input segment in 3D.</param>
	/// <param name="inReferencePoint">The point to which all distances change linearly (the mass center by default). Default value: atl::NIL.</param>
	/// <param name="inScale">Scaling factor (negative values invert the segment). Default value: 1.0f.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RescaleSegment3D
	(
		const avl::Segment3D&				inSegment3D,		
		atl::Optional<const avl::Point3D&>	inReferencePoint,	
		float								inScale,			
		bool								inInverse,			
		avl::Segment3D&						outSegment3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Swaps the two endpoints of a segment in 3D.</summary>
	AVL_FUNCTION void ReverseSegment3D
	(
		const avl::Segment3D&	inSegment3D,
		avl::Segment3D&			outSegment3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Shifts a line in 3D by a vector.</summary>
	/// <param name="inLine3D">Input line in 3D.</param>
	/// <param name="inDelta">Translation vector.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	/// <param name="outLine3D">Shifted line.</param>
	AVL_FUNCTION void TranslateLine3D
	(
		const avl::Line3D&		inLine3D,		
		const avl::Vector3D&	inDelta,		
		bool					inInverse,		
		avl::Line3D&			outLine3D		
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes the input line in 3D distance to a reference point.</summary>
	/// <param name="inLine3D">Input line in 3D.</param>
	/// <param name="inReferencePoint">The point to which the distance of line in 3D is changed.</param>
	/// <param name="inScale">Scaling factor. Default value: 1.0f.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RescaleLine3D
	(
		const avl::Line3D&	inLine3D,			
		const avl::Point3D&	inReferencePoint,	
		float				inScale,			
		bool				inInverse,			
		avl::Line3D&		outLine3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Shifts a plane in 3D by a vector.</summary>
	/// <param name="inPlane">Input plane.</param>
	/// <param name="inDelta">Translation vector.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	/// <param name="outPlane">Shifted plane.</param>
	AVL_FUNCTION void TranslatePlane
	(
		const avl::Plane3D&		inPlane,		
		const avl::Vector3D&	inDelta,		
		bool					inInverse,		
		avl::Plane3D&			outPlane		
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes the input plane distance to a reference point.</summary>
	/// <param name="inReferencePoint">The point to which the distance of plane is changed.</param>
	/// <param name="inScale">Scaling factor. Default value: 1.0f.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RescalePlane
	(
		const avl::Plane3D&	inPlane,
		const avl::Point3D&	inReferencePoint,	
		float				inScale,			
		bool				inInverse,			
		avl::Plane3D&		outPlane
	)
	THROW_AVL_ERRORS;

	/// <summary>Shifts a circle in 3D by a vector.</summary>
	/// <param name="inCircle3D">Input circle.</param>
	/// <param name="inDelta">Translation vector.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	/// <param name="outCircle3D">Shifted circle.</param>
	AVL_FUNCTION void TranslateCircle3D
	(
		const avl::Circle3D&	inCircle3D,		
		const avl::Vector3D&	inDelta,		
		bool					inInverse,		
		avl::Circle3D&			outCircle3D		
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes radius of a circle in 3D and translates its center in relation to a reference point.</summary>
	/// <param name="inReferencePoint">The point to which the distance of the circle center is changed (circle center by default). Default value: atl::NIL.</param>
	/// <param name="inScale">Scaling factor. Default value: 1.0f.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RescaleCircle3D
	(
		const avl::Circle3D&				inCircle3D,
		atl::Optional<const avl::Point3D&>	inReferencePoint,	
		float								inScale,			
		bool								inInverse,			
		avl::Circle3D&						outCircle3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes radius of a circle in 3D.</summary>
	/// <param name="inNewSize">New value for radius. Default value: 1.0f.</param>
	AVL_FUNCTION void ResizeCircle3D
	(
		const avl::Circle3D&	inCircle3D,
		float					inNewSize,	
		avl::Circle3D&			outCircle3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes radius of a circle in 3D by adding a value.</summary>
	/// <param name="inDelta">Value added to circle radius. Default value: 0.0f.</param>
	AVL_FUNCTION void ResizeCircle3D_Delta
	(
		const avl::Circle3D&	inCircle3D,
		float					inDelta,	
		avl::Circle3D&			outCircle3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Lengthens or shortens a 3D vector preserving its direction.</summary>
	/// <param name="inNewLength">Default value: 1.0f.</param>
	AVL_FUNCTION void ResizeVector3D
	( 
		const avl::Vector3D&	inVector3D, 
		float					inNewLength,
		avl::Vector3D&			outVector3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Extends length of a 3D vector by adding a value preserving its direction.</summary>
	/// <param name="inDelta">Value added to vector length. Default value: 0.0f.</param>
	AVL_FUNCTION void ResizeVector3D_Delta
	( 
		const avl::Vector3D&	inVector3D, 
		float					inDelta,	
		avl::Vector3D&			outVector3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Lengthens or shortens a 3D vector relatively preserving its direction.</summary>
	/// <param name="inScale">Scaling factor. Default value: 1.0f.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RescaleVector3D
	( 
		const avl::Vector3D&	inVector3D, 
		float					inScale,	
		bool					inInverse,	
		avl::Vector3D&			outVector3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Rotates a 3D point around an axis in 3D.</summary>
	/// <param name="inAxis">The rotation axis.</param>
	/// <param name="inAngle">Clockwise angle of rotation.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RotatePoint3D
	(
		const avl::Point3D&		inPoint3D,
		const avl::Line3D&		inAxis,				
		float					inAngle,			
		bool					inInverse,			
		avl::Point3D&			outPoint3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Rotates an array of 3D points around an axis in 3D.</summary>
	/// <param name="inAxis">The rotation axis.</param>
	/// <param name="inAngle">Clockwise angle of rotation.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RotatePoint3DArray
	( 
		const atl::Array<avl::Point3D>&	inPoints3D,
		const avl::Line3D&				inAxis,				
		float							inAngle,			
		bool							inInverse,			
		atl::Array<avl::Point3D>&		outPoints3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Rotates a 3D vector around another 3D vector (the axis).</summary>
	/// <param name="inAxisVector">Vector to rotate around.</param>
	/// <param name="inAngle">Clockwise angle of rotation.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RotateVector3D
	( 
		const avl::Vector3D&	inVector3D,
		const avl::Vector3D&	inAxisVector,		
		float					inAngle,			
		bool					inInverse,			
		avl::Vector3D&			outVector3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Rotates a segment in 3D around an axis in 3D.</summary>
	/// <param name="inAxis">The rotation axis.</param>
	/// <param name="inAngle">Clockwise angle of rotation.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RotateSegment3D
	(
		const avl::Segment3D&	inSegment3D,
		const avl::Line3D&		inAxis,				
		float					inAngle,			
		bool					inInverse,			
		avl::Segment3D&			outSegment3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Rotates a line in 3D around an axis in 3D.</summary>
	/// <param name="inAxis">The rotation axis.</param>
	/// <param name="inAngle">Clockwise angle of rotation.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RotateLine3D
	(
		const avl::Line3D&		inLine3D,
		const avl::Line3D&		inAxis,				
		float					inAngle,			
		bool					inInverse,			
		avl::Line3D&			outLine3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Rotates a plane in 3D around an axis in 3D.</summary>
	/// <param name="inAxis">The rotation axis.</param>
	/// <param name="inAngle">Clockwise angle of rotation.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RotatePlane
	(
		const avl::Plane3D&		inPlane,
		const avl::Line3D&		inAxis,				
		float					inAngle,			
		bool					inInverse,			
		avl::Plane3D&			outPlane
	)
	THROW_AVL_ERRORS;

	/// <summary>Rotates a circle in 3D around an axis in 3D.</summary>
	/// <param name="inAxis">The rotation axis.</param>
	/// <param name="inAngle">Clockwise angle of rotation.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RotateCircle3D
	(
		const avl::Circle3D&	inCircle3D,
		const avl::Line3D&		inAxis,				
		float					inAngle,			
		bool					inInverse,			
		avl::Circle3D&			outCircle3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a segment contained in a box in 3D from a line in 3D.</summary>
	AVL_FUNCTION void CropLine3D
	(
		const avl::Line3D&					inLine3D,
		const avl::Box3D&					inBox3D,
		atl::Conditional<avl::Segment3D>&	outSegment3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a segment contained in a box in 3D from another segment in 3D.</summary>
	AVL_FUNCTION void CropSegment3D
	(
		const avl::Segment3D&				inSegment3D,
		const avl::Box3D&					inBox3D,
		atl::Conditional<avl::Segment3D>&	outSegment3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Rotates a 3D point around an axis (point+vector) in 3D.</summary>
	/// <param name="inAxisVector">The direction vector of the rotation axis.</param>
	/// <param name="inCenter">An arbitrary point on the rotation axis.</param>
	/// <param name="inAngle">Clockwise angle of rotation.</param>
	/// <param name="inUseAxisLength">Assume axis length to be the rotation angle, ignore inAngle (Rodrigues' Rotation).</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RotatePoint3D_Deprecated
	(
		const avl::Point3D&		inPoint3D,
		const avl::Vector3D&	inAxisVector,		
		const avl::Point3D&		inCenter,			
		float					inAngle,			
		bool					inUseAxisLength,	
		bool					inInverse,			
		avl::Point3D&			outPoint3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Rotates an array of 3D points around an axis (point+vector) in 3D.</summary>
	/// <param name="inAxisVector">The direction vector of the rotation axis.</param>
	/// <param name="inCenter">An arbitrary point on the rotation axis.</param>
	/// <param name="inAngle">Clockwise angle of rotation.</param>
	/// <param name="inUseAxisLength">Assume axis length to be the rotation angle, ignore inAngle (Rodrigues' Rotation).</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RotatePoint3DArray_Deprecated
	( 
		const atl::Array<avl::Point3D>&	inPoints3D,
		const avl::Vector3D&			inAxisVector,		
		const avl::Point3D&				inCenter,			
		float							inAngle,			
		bool							inUseAxisLength,	
		bool							inInverse,			
		atl::Array<avl::Point3D>&		outPoints3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Rotates a 3D vector around another 3D vector (the axis).</summary>
	/// <param name="inAxisVector">Vector to rotate around,.</param>
	/// <param name="inAngle">Clockwise angle of rotation.</param>
	/// <param name="inUseAxisLength">Assume axis length to be the rotation angle, ignore inAngle (Rodrigues' Rotation).</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	AVL_FUNCTION void RotateVector3D_Deprecated
	( 
		const avl::Vector3D&	inVector3D,
		const avl::Vector3D&	inAxisVector,		
		float					inAngle,			
		bool					inUseAxisLength,	
		bool					inInverse,			
		avl::Vector3D&			outVector3D
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_GEOMETRY3DSPATIALTRANSFORMS_H

