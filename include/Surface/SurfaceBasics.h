//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVS_SURFACEBASICS_H
#define AVS_SURFACEBASICS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Surface/Surface.h"
#include "Surface/SurfaceFormat.h"
#include "Geometry3D/Geometry3D.h"
#include "Point3DGrid/Point3DGrid.h"
#include "Image/Image.h"
#include "Path/Path.h"
#include "Basic/Types.h"

namespace avl
{


	struct TestSurfaceState : public BaseState
	{
		avl::PlainType::Type pointType;
		float density;
		float scaleX, scaleY, scaleZ;

		avl::Surface surface;
	};


	/// <summary>Returns a sample 3D surface.</summary>
	/// <param name="inPointType">Type of single point Z coordinate. Default value: Int16.</param>
	/// <param name="inDensity">Density of points in output object. Default value: 4.0f.</param>
	/// <param name="inScaleX">Scaling of output object on X axis. Default value: 1.0f.</param>
	/// <param name="inScaleY">Scaling of output object on Y axis. Default value: 1.0f.</param>
	/// <param name="inScaleZ">Scaling of output object on Z axis. Default value: 1.0f.</param>
	/// <param name="outSurface">Output object.</param>
	AVL_FUNCTION void TestSurface
	(
		TestSurfaceState&			ioState,
		const avl::PlainType::Type&	inPointType,	
		const float&				inDensity,		
		const float&				inScaleX,		
		const float&				inScaleY,		
		const float&				inScaleZ,		
		avl::Surface&				outSurface		
	)
	THROW_AVL_ERRORS;

	/// <summary>If the input Surface has at least one point defined, then it is copied to the output; otherwise Nil is returned.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="outNotEmptySurface">A copy of the input surface, if it is not empty, or Nil otherwise.</param>
	/// <param name="outIsNotEmpty">Indication if the input surface is not empty.</param>
	AVL_FUNCTION void SkipEmptySurface
	(
		const avl::Surface&				inSurface,			
		atl::Conditional<avl::Surface>&	outNotEmptySurface,	
		bool&							outIsNotEmpty		
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a surface structure from Point3D array taking into account X and Y coordinates.</summary>
	/// <param name="inXScale">Default value: 1.0D.</param>
	/// <param name="inYScale">Default value: 1.0D.</param>
	/// <param name="inZScale">Default value: 1.0D.</param>
	/// <param name="inPointType">Type of single point Z coordinate. Default value: Int16.</param>
	AVL_FUNCTION void ArrangePoint3DArray
	(
		const atl::Array<avl::Point3D>&	inPoints,
		atl::Optional<double>		inMinX,
		atl::Optional<double>		inMaxX,
		const double				inXScale,
		atl::Optional<double>		inMinY,
		atl::Optional<double>		inMaxY,
		const double				inYScale,
		const double				inZOffset,
		const double				inZScale,
		const avl::PlainType::Type&	inPointType,	
		avl::Surface&				outSurface,
		atl::Optional<double&>		outMinX = atl::NIL,
		atl::Optional<double&>		outMinY = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a surface structure from Point3DGrid taking into account X and Y coordinates.</summary>
	/// <param name="inZScale">Default value: 1.0D.</param>
	/// <param name="inPointType">Type of single point Z coordinate. Default value: Int16.</param>
	AVL_FUNCTION void ArrangePoint3DGrid
	(
		const avl::Point3DGrid&		inPoint3DGrid,
		atl::Optional<double>		inMinX,
		atl::Optional<double>		inMaxX,
		atl::Optional<double>		inMinY,
		atl::Optional<double>		inMaxY,
		const double				inZOffset,
		const double				inZScale,
		const avl::PlainType::Type&	inPointType,	
		avl::Surface&				outSurface,
		atl::Optional<double&>		outMinX = atl::NIL,
		atl::Optional<double&>		outMinY = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns an interpolated single point of a surface given its surface grid coordinates.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inPoint">Surface grid coordinates of the input point.</param>
	/// <param name="inInterpolationRadius">Radius of vicinity taking into account to interpolate not existing point. Default value: 0.</param>
	/// <param name="outPoint">Output point.</param>
	AVL_FUNCTION void GetSurfacePoint
	(
		const avl::Surface&	inSurface,	
		const avl::Point2D&	inPoint,	
		int					inInterpolationRadius,	
		avl::Point3D&		outPoint	
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns an interpolated single point of a surface given its coordinates in surface coordinate system.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inPoint">Coordinates of the input point in surface coordinate system.</param>
	/// <param name="outSurfaceRealPoint">Output point in surface coordinate system.</param>
	/// <param name="outSurfaceGridPoint">Output point in surface grid coordinate system.</param>
	AVL_FUNCTION void ProjectPointOntoSurface
	(
		const avl::Surface&				inSurface,	
		const avl::Point2D&				inPoint,	
		atl::Optional<avl::Point3D&>	outSurfaceRealPoint = atl::NIL,	
		atl::Optional<avl::Point2D&>	outSurfaceGridPoint = atl::NIL		
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns a path consisting of interpolated single points of a surface given their surface grid coordinates.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inPath">Surface grid coordinates of the input path points.</param>
	/// <param name="outPath">Output path in surface coordinates.</param>
	AVL_FUNCTION void GetSurfacePath
	(
		const avl::Surface&	inSurface,	
		const avl::Path&	inPath,		
		avl::Path&			outPath		
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns a path consisting of interpolated single points of a surface given their coordinates in surface coordinate system.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inPath">Coordinates of the input path points in surface coordinate system.</param>
	/// <param name="outSurfaceGridPath">Output path in surface grid coordinate system.</param>
	AVL_FUNCTION void ProjectPathOntoSurface
	(
		const avl::Surface&	inSurface,	
		const avl::Path&	inPath,		
		avl::Path&			outSurfaceGridPath	
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a uniform surface.</summary>
	/// <param name="inWidth">Width of the created surface. Default value: 320.</param>
	/// <param name="inHeight">Height of the created surface. Default value: 240.</param>
	/// <param name="inPointType">Type of single point Z coordinate. Default value: Int16.</param>
	/// <param name="inXOffset">Default value: 0.0D.</param>
	/// <param name="inXScale">Default value: 1.0D.</param>
	/// <param name="inYOffset">Default value: 0.0D.</param>
	/// <param name="inYScale">Default value: 1.0D.</param>
	/// <param name="inZOffset">Default value: 0.0D.</param>
	/// <param name="inZScale">Default value: 1.0D.</param>
	/// <param name="inZ">Z coordinate of all points of the created surface. Default value: 0.0D.</param>
	AVL_FUNCTION void CreateFlatSurface
	(
		const int					inWidth,		
		const int					inHeight,		
		const avl::PlainType::Type&	inPointType,	
		const double				inXOffset,
		const double				inXScale,
		const double				inYOffset,
		const double				inYScale,
		const double				inZOffset,
		const double				inZScale,
		atl::Optional<double>		inZ,			
		avl::Surface&				outSurface
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a Surface structure from depth map mono image.</summary>
	/// <param name="inImage">Source mono image with depth map.</param>
	/// <param name="inRoi">Region determining valid points in resulting Surface. Default value: atl::NIL.</param>
	/// <param name="inXOffset">Default value: 0.0D.</param>
	/// <param name="inXScale">Default value: 1.0D.</param>
	/// <param name="inYOffset">Default value: 0.0D.</param>
	/// <param name="inYScale">Default value: 1.0D.</param>
	/// <param name="inZOffset">Default value: 0.0D.</param>
	/// <param name="inZScale">Default value: 1.0D.</param>
	AVL_FUNCTION void MakeSurfaceFromImage
	(
		const avl::Image&					inImage,		
		atl::Optional<const avl::Region&>	inRoi,			
		double								inXOffset,
		double								inXScale,
		double								inYOffset,
		double								inYScale,
		double								inZOffset,
		double								inZScale,
		avl::Surface&						outSurface
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes the point Z coordinate type.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inNewPointType">Point Z coordinate type of the output surface.</param>
	/// <param name="inNewZOffset">Offset along Z axis in output surface. Default value: atl::NIL.</param>
	/// <param name="inNewZScale">Scale along Z axis in output surface. Default value: atl::NIL.</param>
	/// <param name="outSurface">Surface with changed internal surface type.</param>
	AVL_FUNCTION void ConvertSurfaceType
	(
		const avl::Surface&			inSurface,		
		avl::PlainType::Type		inNewPointType,	
		atl::Optional<double>		inNewZOffset,	
		atl::Optional<double>		inNewZScale,	
		avl::Surface&				outSurface		
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a coordinate system connected with the surface image to a coordinate system connected with the surface.</summary>
	/// <param name="inCoordinateSystem">Coordinate system connected with the surface image.</param>
	/// <param name="inSurfaceFormat">Format of the surface.</param>
	/// <param name="outCoordinateSystem">Coordinate system connected with the surface.</param>
	AVL_FUNCTION void ConvertCoordinateSystem2DTo3D
	(
		const avl::CoordinateSystem2D&	inCoordinateSystem,	
		const avl::SurfaceFormat&		inSurfaceFormat,	
		avl::CoordinateSystem2D&		outCoordinateSystem	
	)
	THROW_AVL_ERRORS;

} // namespace avl

namespace avs
{

	/// <summary>Returns individual fields of a surface.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="outWidth">Surface width.</param>
	/// <param name="outHeight">Surface height.</param>
	/// <param name="outPointType">Point Z coordinate type.</param>
	/// <param name="outPointByteSize">Point Z coordinate size in bytes.</param>
	/// <param name="outPitch">Length of surface point line with padding.</param>
	/// <param name="outXOffset">Offset in X axis.</param>
	/// <param name="outXScale">Scale in X axis.</param>
	/// <param name="outYOffset">Offset in Y axis.</param>
	/// <param name="outYScale">Scale in Y axis.</param>
	/// <param name="outZOffset">Offset in Z axis.</param>
	/// <param name="outZScale">Scale in Z axis.</param>
	AVL_FUNCTION void AvsFilter_AccessSurface
	(
		const avl::Surface&		inSurface,		
		int&					outWidth,		
		int&					outHeight,		
		avl::PlainType::Type&	outPointType,	
		int&					outPointByteSize,	
		int&					outPitch,		
		double&					outXOffset,		
		double&					outXScale,		
		double&					outYOffset,		
		double&					outYScale,		
		double&					outZOffset,		
		double&					outZScale		
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets the value of a single point of a surface.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inLocation">Location of the surface point to be accessed.</param>
	/// <param name="outPoint">Output point of the input surface.</param>
	AVL_FUNCTION void AvsFilter_GetSurfaceElement
	(
		const avl::Surface&		inSurface,	
		const avl::Location&	inLocation,	
		avl::Point3D&			outPoint	
	)
	THROW_AVL_ERRORS;

} // namespace avs

#endif // AVS_SURFACEBASICS_H

