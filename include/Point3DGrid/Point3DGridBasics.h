//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVS_POINT3DGRIDBASICS_H
#define AVS_POINT3DGRIDBASICS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Geometry3D/Geometry3D.h"
#include "Point3DGrid/Point3DGrid.h"
#include "Image/Image.h"

namespace avl
{


	/// <summary>If the input Point3DGrid has at least one point defined, then it is copied to the output; otherwise Nil is returned.</summary>
	/// <param name="outNotEmptyPoint3DGrid">A copy of the input grid, if it is not empty, or Nil otherwise.</param>
	/// <param name="outIsNotEmpty">Indication if the input grid is not empty.</param>
	AVL_FUNCTION void SkipEmptyPoint3DGrid
	(
		const avl::Point3DGrid&				inPoint3DGrid,
		atl::Conditional<avl::Point3DGrid>&	outNotEmptyPoint3DGrid,	
		bool&								outIsNotEmpty			
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a Point3DGrid structure from coordinates encoded in pixels of a 3 channel image.</summary>
	/// <param name="inImage">Source 3 channel image with per pixel encoded XYZ coordinates.</param>
	/// <param name="inRoi">Region determining valid points in resulting point grid. Default value: atl::NIL.</param>
	/// <param name="inXOffset">Default value: 0.0D.</param>
	/// <param name="inXScale">Default value: 1.0D.</param>
	/// <param name="inYOffset">Default value: 0.0D.</param>
	/// <param name="inYScale">Default value: 1.0D.</param>
	/// <param name="inZOffset">Default value: 0.0D.</param>
	/// <param name="inZScale">Default value: 1.0D.</param>
	AVL_FUNCTION void MakePoint3DGridFromImage
	(
		const avl::Image&					inImage,		
		atl::Optional<const avl::Region&>	inRoi,			
		double								inXOffset,
		double								inXScale,
		double								inYOffset,
		double								inYScale,
		double								inZOffset,
		double								inZScale,
		avl::Point3DGrid&					outPoint3DGrid
	)
	THROW_AVL_ERRORS;

	struct TestPoint3DGridState : public avl::BaseState
	{
		float density;
		float scaleX, scaleY, scaleZ;

		avl::Point3DGrid grid;
	};


	/// <summary>Returns a sample 3D object.</summary>
	/// <param name="inDensity">Density of points in output object. Default value: 4.0f.</param>
	/// <param name="inScaleX">Scaling of output object on X axis. Default value: 1.0f.</param>
	/// <param name="inScaleY">Scaling of output object on Y axis. Default value: 1.0f.</param>
	/// <param name="inScaleZ">Scaling of output object on Z axis. Default value: 1.0f.</param>
	/// <param name="outPoint3DGrid">Output object.</param>
	AVL_FUNCTION void TestPoint3DGrid
	(
		TestPoint3DGridState&	ioState,
		const float&			inDensity,		
		const float&			inScaleX,		
		const float&			inScaleY,		
		const float&			inScaleZ,		
		avl::Point3DGrid&		outPoint3DGrid	
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns an interpolated single point of a point 3D grid.</summary>
	/// <param name="inPoint3DGrid">Input point 3D grid.</param>
	/// <param name="inOffsetX">Defines offset of the input grid along X axis.</param>
	/// <param name="inOffsetY">Defines offset of the input grid along Y axis.</param>
	/// <param name="inStepX">Defines step of the input grid along X axis. Default value: 1.0f.</param>
	/// <param name="inStepY">Defines step of the input grid along Y axis. Default value: 1.0f.</param>
	/// <param name="inX">X coordinate of the input point.</param>
	/// <param name="inY">Y coordinate of the input point.</param>
	/// <param name="inInterpolationRadius">Radius of vicinity taking into account to interpolate not existing point. Default value: 1.</param>
	/// <param name="outPoint">Output point.</param>
	AVL_FUNCTION void GetPoint3DGridPoint_Interpolated
	(
		const avl::Point3DGrid&	inPoint3DGrid,	
		float				inOffsetX,		
		float				inOffsetY,		
		float				inStepX,		
		float				inStepY,		
		float				inX,			
		float				inY,			
		int					inInterpolationRadius,	
		avl::Point3D&			outPoint		
	)
	THROW_AVL_ERRORS;

} // namespace avl

namespace avs
{

	/// <summary>Creates a point 3D grid structure from individual fields.</summary>
	AVL_FUNCTION void AvsFilter_MakePoint3DGrid
	(
		const int						inWidth,
		const int						inHeight,
		const atl::Array<avl::Point3D>&	inPoints,
		avl::Point3DGrid&				outPoint3DGrid
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns individual fields of a point 3D grid.</summary>
	/// <param name="inPoint3DGrid">Input point 3D grid.</param>
	/// <param name="outWidth">Grid width.</param>
	/// <param name="outHeight">Grid height.</param>
	/// <param name="outPoints">Points of the grid.</param>
	AVL_FUNCTION void AvsFilter_AccessPoint3DGrid
	(
		const avl::Point3DGrid&		inPoint3DGrid,	
		int&						outWidth,		
		int&						outHeight,		
		atl::Array<avl::Point3D>&	outPoints		
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets the value of a single point of a point 3D grid.</summary>
	/// <param name="inPoint3DGrid">Input point 3D grid.</param>
	/// <param name="outPoint">Output point of the input grid.</param>
	AVL_FUNCTION void AvsFilter_GetPoint3DGridElement
	(
		const avl::Point3DGrid&	inPoint3DGrid,	
		const int				inRow,
		const int				inColumn,
		avl::Point3D&			outPoint		
	)
	THROW_AVL_ERRORS;

} // namespace avs

#endif // AVS_POINT3DGRIDBASICS_H

