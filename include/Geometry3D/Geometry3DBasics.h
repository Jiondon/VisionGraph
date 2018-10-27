//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVS_GEOMETRY3DBASICS_H
#define AVS_GEOMETRY3DBASICS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Geometry3D/Geometry3D.h"
#include "Enums/Anchor3D.h"
#include "AVLCommon/RandomTypes.h"

namespace avl
{


	/// <summary>Creates random 3D point inside given box</summary>
	/// <param name="ioState">State of generator.</param>
	/// <param name="inSeed">Random seed. Default value: atl::NIL.</param>
	AVL_FUNCTION void RandomPoint3D
	(
		RandomState&		ioState,	
		const float&		inMinX,
		const float&		inMaxX,
		const float&		inMinY,
		const float&		inMaxY,
		const float&		inMinZ,
		const float&		inMaxZ,
		atl::Optional<int>	inSeed,		
		avl::Point3D&		outPoint3D
	)
	THROW_AVL_ERRORS;

	/// <summary>If the input box in 3D has all dimensions different from zero, then it is copied to the output; otherwise Nil is returned.</summary>
	AVL_FUNCTION void SkipEmptyBox3D
	(
		const avl::Box3D&				inBox3D,
		atl::Conditional<avl::Box3D>&	outNotEmptyBox3D,
		bool&							outIsNotEmpty
	)
	THROW_AVL_ERRORS;

	/// <summary>Tests whether the box in 3D is empty.</summary>
	AVL_FUNCTION void TestBox3DEmpty
	(
		const avl::Box3D&	inBox3D,
		bool&				outIsEmpty
	)
	THROW_AVL_ERRORS;

	/// <summary>Tests whether the box in 3D is not empty.</summary>
	AVL_FUNCTION void TestBox3DNotEmpty
	(
		const avl::Box3D&	inBox3D,
		bool&				outIsNotEmpty
	)
	THROW_AVL_ERRORS;

	/// <summary>Tests whether a box in 3D is contained in another one.</summary>
	AVL_FUNCTION void TestBox3DInBox3D
	(
		const avl::Box3D&	inSubBox3D,
		const avl::Box3D&	inBox3D,
		bool&				outIsContained
	)
	THROW_AVL_ERRORS;

	/// <summary>Tests whether two boxes in 3D have non-empty intersection.</summary>
	AVL_FUNCTION void TestBox3DIntersectsWith
	(
		const avl::Box3D&	inBox3D,
		const avl::Box3D&	inReferenceBox3D,
		bool&				outBoxes3DIntersect
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a box in 3D.</summary>
	AVL_FUNCTION void CreateBox3D
	(
		const avl::Point3D&		inPoint3D,
		const avl::Anchor3D&	inPoint3DAnchor3D,
		float					inXLength,
		float					inYLength,
		float					inZLength,
		avl::Box3D&				outBox3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Produces a segment in 3D of given parameters.</summary>
	/// <param name="inPoint3D">A point on the created segment.</param>
	/// <param name="inPointAnchor">Anchor point, 0 means the beginning, 1 means the end of the segment.</param>
	/// <param name="inDirectionVector">Desired direction of the segment.</param>
	/// <param name="inLength">Desired length of the segment in pixels.</param>
	/// <param name="outSegment3D">The resulting segment.</param>
	AVL_FUNCTION void CreateSegment3D
	(
		const avl::Point3D&		inPoint3D,		
		float					inPointAnchor,	
		const avl::Vector3D&	inDirectionVector,	
		float					inLength,		
		avl::Segment3D&			outSegment3D	
	)
	THROW_AVL_ERRORS;

	/// <summary>Removes invalid 3D points from an array (i.e. points with NaN or INF coordinates).</summary>
	AVL_FUNCTION void RemoveInvalidPoints3D
	(
		const atl::Array<avl::Point3D>& inPoints3D,
		atl::Array<avl::Point3D>&		outPoints3D
	)
	THROW_AVL_ERRORS;

} // namespace avl

namespace avs
{

	/// <summary>Creates a plane structure from individual fields.</summary>
	/// <param name="inA">First plane parameter.</param>
	/// <param name="inB">Second plane parameter.</param>
	/// <param name="inC">Third plane parameter.</param>
	/// <param name="inD">Fourth plane parameter.</param>
	AVL_FUNCTION void AvsFilter_MakePlane
	(
		float inA,				
		float inB,				
		float inC,				
		float inD,				
		avl::Plane3D& outPlane
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a segment 3D structure from individual fields.</summary>
	/// <param name="inPoint1">First point of the segment.</param>
	/// <param name="inPoint2">Second point of the segment.</param>
	AVL_FUNCTION void AvsFilter_MakeSegment3D
	(
		const avl::Point3D&	inPoint1,	
		const avl::Point3D&	inPoint2,	
		avl::Segment3D&		outSegment
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a line in 3D structure from individual fields.</summary>
	AVL_FUNCTION void AvsFilter_MakeLine3D
	(
		float			inX0,
		float			inY0,
		float			inZ0,
		float			inDeltaX,
		float			inDeltaY,
		float			inDeltaZ,
		avl::Line3D&	outLine3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a 3D point.</summary>
	AVL_FUNCTION void AvsFilter_MakePoint3D
	(
		const float				inX,
		const float				inY,
		const float				inZ,
		avl::Point3D&				outPoint3D
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a 3D circle structure from individual fields.</summary>
	/// <param name="inCenter">Center of the circle.</param>
	/// <param name="inPlane">Plane the circle is parallel to.</param>
	/// <param name="inRadius">Circle radius.</param>
	AVL_FUNCTION void AvsFilter_MakeCircle3D
	(
		const avl::Point3D&	inCenter,	
		const avl::Plane3D&	inPlane,	
		float			inRadius,	
		avl::Circle3D&		outCircle
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a 3D box structure from individual fields.</summary>
	/// <param name="inX">Input x-coordinate.</param>
	/// <param name="inY">Input y-coordinate.</param>
	/// <param name="inZ">Input z-coordinate.</param>
	/// <param name="inXLength">Input length in X axis.</param>
	/// <param name="inYLength">Input length in Y axis.</param>
	/// <param name="inZLength">Input length in Z axis.</param>
	/// <param name="outBox3D">Output box 3D.</param>
	AVL_FUNCTION void AvsFilter_MakeBox3D
	(
		float		inX,		
		float		inY,		
		float		inZ,		
		float		inXLength,	
		float		inYLength,	
		float		inZLength,	
		avl::Box3D&	outBox3D	
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a sphere structure from individual fields.</summary>
	/// <param name="inCenter">Center of the sphere.</param>
	/// <param name="inRadius">Sphere radius.</param>
	AVL_FUNCTION void AvsFilter_MakeSphere
	(
		const avl::Point3D&	inCenter,	
		float			inRadius,	
		avl::Sphere3D&		outSphere
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns individual fields of a 3d point.</summary>
	/// <param name="inPoint">Input point.</param>
	/// <param name="outX">Output x-coordinate.</param>
	/// <param name="outY">Output y-coordinate.</param>
	/// <param name="outZ">Output z-coordinate.</param>
	AVL_FUNCTION void AvsFilter_AccessPoint3D
	(
		const avl::Point3D& inPoint,		
		float&			outX,			
		float&			outY,			
		float&			outZ			
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns individual fields of a plane.</summary>
	/// <param name="inPlane">Input plane.</param>
	/// <param name="outA">Output plane parameter A.</param>
	/// <param name="outB">Output plane parameter B.</param>
	/// <param name="outC">Output plane parameter C.</param>
	/// <param name="outD">Output plane parameter D.</param>
	AVL_FUNCTION void AvsFilter_AccessPlane
	(
		const avl::Plane3D&	inPlane,	
		float&			outA,		
		float&			outB,		
		float&			outC,		
		float&			outD		
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns individual fields of a segment 3D.</summary>
	/// <param name="inSegment">Input segment.</param>
	/// <param name="outPoint1">First point of the segment.</param>
	/// <param name="outPoint2">Second point of the segment.</param>
	AVL_FUNCTION void AvsFilter_AccessSegment3D
	(
		const avl::Segment3D&	inSegment,	
		avl::Point3D&			outPoint1,	
		avl::Point3D&			outPoint2	
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns individual fields of a line in 3D.</summary>
	/// <param name="inLine3D">Input line in 3D.</param>
	/// <param name="outPoint">Point on the input line.</param>
	/// <param name="outDelta">Vector of the input line.</param>
	AVL_FUNCTION void AvsFilter_AccessLine3D
	(
		const avl::Line3D&	inLine3D,	
		avl::Point3D&		outPoint,	
		avl::Vector3D&		outDelta	
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns individual fields of a circle in 3D.</summary>
	/// <param name="inCircle">Input circle.</param>
	/// <param name="outCenter">Center of the circle.</param>
	/// <param name="outPlane">Plane the circle lies on.</param>
	/// <param name="outRadius">Output radius.</param>
	AVL_FUNCTION void AvsFilter_AccessCircle3D
	(
		const avl::Circle3D&	inCircle,
		avl::Point3D&			outCenter,
		avl::Plane3D&			outPlane,
		float&				outRadius
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns individual fields of a box in 3D.</summary>
	/// <param name="inBox3D">Input box in 3D.</param>
	/// <param name="outX">Input box x-coordinate.</param>
	/// <param name="outY">Input box y-coordinate.</param>
	/// <param name="outZ">Input box z-coordinate.</param>
	/// <param name="outXLength">Length in X axis.</param>
	/// <param name="outYLength">Length in Y axis.</param>
	/// <param name="outZLength">Length in Z axis.</param>
	AVL_FUNCTION void AvsFilter_AccessBox3D
	(
		const avl::Box3D&	inBox3D,	
		float&				outX,		
		float&				outY,		
		float&				outZ,		
		float&				outXLength,	
		float&				outYLength,	
		float&				outZLength	
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns individual fields of a sphere.</summary>
	/// <param name="inSphere">Input sphere.</param>
	/// <param name="outCenter">Center of the sphere.</param>
	/// <param name="outRadius">Output radius.</param>
	AVL_FUNCTION void AvsFilter_AccessSphere
	(
		const avl::Sphere3D&	inSphere,
		avl::Point3D&			outCenter,
		float&				outRadius
	)
	THROW_AVL_ERRORS;

} // namespace avs

#endif // AVS_GEOMETRY3DBASICS_H

