//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_SURFACESPATIALTRANSFORMS_H
#define AVL_SURFACESPATIALTRANSFORMS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Surface/Surface.h"
#include "Geometry3D/Geometry3D.h"
#include "Region/Region.h"
#include "Enums/Metric3D.h"
#include "Enums/Axis.h"
#include "Enums/KernelShape.h"

namespace avl
{


	/// <summary>Translates a surface by a vector.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inDelta">Translation vector.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	/// <param name="outSurface">Translated surface.</param>
	AVL_FUNCTION void TranslateSurface
	(
		const avl::Surface&		inSurface,	
		const avl::Vector3D&	inDelta,	
		bool					inInverse,	
		avl::Surface&			outSurface	
	)
	THROW_AVL_ERRORS;

	/// <summary>Changes the distances of surface points to a reference point.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inReferencePoint">Point to which the distances will be changed.</param>
	/// <param name="inScaleX">Scaling factor along X axis. Default value: 1.0f.</param>
	/// <param name="inScaleY">Scaling factor along Y axis. Default value: atl::NIL.</param>
	/// <param name="inScaleZ">Scaling factor along Z axis. Default value: atl::NIL.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	/// <param name="outSurface">Rescaled surface.</param>
	AVL_FUNCTION void RescaleSurface
	(
		const avl::Surface&		inSurface,			
		const avl::Point3D&		inReferencePoint,	
		float					inScaleX,			
		atl::Optional<float>	inScaleY,			
		atl::Optional<float>	inScaleZ,			
		bool					inInverse,			
		avl::Surface&			outSurface			
	)
	THROW_AVL_ERRORS;

	/// <summary>Removes from the surface points that are too distant from their neighbor points.</summary>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="inNeighborRadius">Radius of neighbors to search for real neighbors. Default value: 1.</param>
	/// <param name="inMaxDistance">Maximal distance from another point to consider them real neighbors. Default value: 2.0f.</param>
	/// <param name="inMetric">Metric used for measuring distance between points. Default value: Z.</param>
	/// <param name="inMinNeighborRatio">Fraction of valid neighbors in a given radius that have to be real neighbors. Default value: 1.0f.</param>
	/// <param name="inPreserveDimensions">Flag indicating whether the surface dimensions should be preserved or not. Default value: False.</param>
	/// <param name="outRejected">Region of locations where points are too distant from their neighbors.</param>
	AVL_FUNCTION void CropSurfaceByNeighborsProximity
	(
		const avl::Surface&	inSurface,
		atl::Optional<const avl::Region&>	inRoi,	
		const int			inNeighborRadius,	
		const float			inMaxDistance,		
		avl::Metric3D::Type	inMetric,			
		const float			inMinNeighborRatio,	
		bool				inPreserveDimensions,	
		avl::Surface&		outSurface,
		atl::Optional<avl::Region&>	outRejected = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Removes points that are not present in a given region.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inRegion">Region from which the points are not removed.</param>
	/// <param name="inPreserveDimensions">Flag indicating whether the surface dimensions should be preserved or not. Default value: False.</param>
	/// <param name="outSurface">Output surface.</param>
	AVL_FUNCTION void CropSurfaceToRegion
	(
		const avl::Surface&	inSurface,	
		const avl::Region&	inRegion,	
		bool				inPreserveDimensions,	
		avl::Surface&		outSurface	
	)
	THROW_AVL_ERRORS;

	/// <summary>Removes from the surface points that are not contained in a given rectangular box.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="inPreserveDimensions">Flag indicating whether the surface dimensions should be preserved or not. Default value: False.</param>
	/// <param name="outSurface">Output surface.</param>
	/// <param name="outRejected">Region of locations where points are not contained in a given rectangular box.</param>
	AVL_FUNCTION void CropSurface
	(
		const avl::Surface&		inSurface,	
		atl::Optional<const avl::Region&>	inRoi,	
		atl::Optional<double>	inMinX,
		atl::Optional<double>	inMaxX,
		atl::Optional<double>	inMinY,
		atl::Optional<double>	inMaxY,
		atl::Optional<double>	inMinZ,
		atl::Optional<double>	inMaxZ,
		bool					inPreserveDimensions,	
		avl::Surface&			outSurface,	
		atl::Optional<avl::Region&>	outRejected = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Removes from the surface points that are not contained in a given box in 3D.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="inBox3D">Box defining a subspace to be cropped.</param>
	/// <param name="inPreserveDimensions">Flag indicating whether the surface dimensions should be preserved or not. Default value: False.</param>
	/// <param name="outSurface">Output surface.</param>
	/// <param name="outRejected">Region of locations where points are not contained in a given box in 3D.</param>
	AVL_FUNCTION void CropSurfaceToBox3D
	(
		const avl::Surface&		inSurface,	
		atl::Optional<const avl::Region&>	inRoi,	
		const avl::Box3D&		inBox3D,	
		bool					inPreserveDimensions,	
		avl::Surface&			outSurface,	
		atl::Optional<avl::Region&>	outRejected = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Removes from the surface points that are too distant from a given plane.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="inPlane">Plane to which distance is measured.</param>
	/// <param name="inMinDistance">Minimal distance from a given plane. Default value: atl::NIL.</param>
	/// <param name="inMaxDistance">Maximal distance from a given plane. Default value: 1.0f.</param>
	/// <param name="inPreserveDimensions">Flag indicating whether the surface dimensions should be preserved or not. Default value: False.</param>
	/// <param name="outSurface">Output surface.</param>
	/// <param name="outRejected">Region of locations where points are too distant from the input plane.</param>
	AVL_FUNCTION void CropSurfaceByPlaneProximity
	(
		const avl::Surface&	inSurface,		
		atl::Optional<const avl::Region&>	inRoi,	
		const avl::Plane3D&	inPlane,		
		atl::Optional<float>	inMinDistance,	
		atl::Optional<float>	inMaxDistance,	
		bool					inPreserveDimensions,	
		avl::Surface&		outSurface,		
		atl::Optional<avl::Region&>	outRejected = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Projects a surface on another plane, replacing Z coordinate of a point with its distance from a given plane.</summary>
	AVL_FUNCTION void ProjectSurfaceOntoPlane
	(
		const avl::Surface&		inSurface,
		const avl::Plane3D&		inPlane,
		const bool				inUseAbsoluteDistance,
		avl::Surface&			outSurface
	)
	THROW_AVL_ERRORS;

	/// <summary>Combines two surfaces into one.</summary>
	/// <param name="inSurface1">First input surface to join.</param>
	/// <param name="inSurface2">Second input surface to join.</param>
	/// <param name="outSurface">Combination of two input surfaces.</param>
	AVL_FUNCTION void JoinSurfaces
	(
		const avl::Surface&	inSurface1,	
		const avl::Surface&	inSurface2,	
		avl::Surface&		outSurface	
	)
	THROW_AVL_ERRORS;

	/// <summary>Reduces surface dimensions as much as possible.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="outSurface">Reduced surface.</param>
	AVL_FUNCTION void ReduceSurface
	(
		const avl::Surface&		inSurface,	
		atl::Optional<const avl::Region&>	inRoi,	
		avl::Surface&			outSurface	
	)
	THROW_AVL_ERRORS;

	/// <summary>Transforms Z coordinate of each surface point to its absolute value.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="outSurface">Output surface.</param>
	AVL_FUNCTION void AbsoluteSurface
	(
		const avl::Surface&	inSurface,	
		avl::Surface&		outSurface	
	)
	THROW_AVL_ERRORS;

	/// <summary>Flattens a curved surface.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inCurvatureAxis">Axis along which the input surface is curved.</param>
	/// <param name="inStdDev">Standard deviation for smoothing of the surface.</param>
	/// <param name="outSurface">Output surface.</param>
	/// <param name="diagSmoothedSurface">Surface smoothed with a Gaussian kernel.</param>
	AVL_FUNCTION void FlattenSurface
	(
		const avl::Surface&		inSurface,			
		const avl::Axis::Type	inCurvatureAxis,	
		const float				inStdDev,			
		avl::Surface&			outSurface,			
		avl::Surface&			diagSmoothedSurface = atl::Dummy<avl::Surface>()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Removes some existing points from the input surface when some points in their vicinity are missing.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="inKernel">Kernel shape (predefined).</param>
	/// <param name="inRadiusX">Nearly half of the kernel's width (2*R+1). Default value: 1.</param>
	/// <param name="inRadiusY">Nearly half of the kernel's height (2*R+1), or same as inRadiusX. Default value: atl::NIL.</param>
	/// <param name="inPreserveDimensions">Flag indicating whether the surface dimensions should be preserved or not.</param>
	/// <param name="outSurface">Output surface.</param>
	AVL_FUNCTION void ErodeSurfacePoints
	(
		const avl::Surface&		inSurface,	
		atl::Optional<const avl::Region&>	inRoi,	
		avl::KernelShape::Type	inKernel,	
		int						inRadiusX,	
		atl::Optional<int>		inRadiusY,	
		bool					inPreserveDimensions,	
		avl::Surface&			outSurface	
	)
	THROW_AVL_ERRORS;

	/// <summary>Removes some existing points from the input surface when some points in their vicinity are missing.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="inKernel">Kernel shape (predefined).</param>
	/// <param name="inRadiusX">Nearly half of the kernel's width (2*R+1). Default value: 1.</param>
	/// <param name="inRadiusY">Nearly half of the kernel's height (2*R+1), or same as inRadiusX. Default value: atl::NIL.</param>
	/// <param name="inPreserveDimensions">Flag indicating whether the surface dimensions should be preserved or not.</param>
	/// <param name="outSurface">Output surface.</param>
	AVL_FUNCTION void OpenSurfacePoints
	(
		const avl::Surface&		inSurface,	
		atl::Optional<const avl::Region&>	inRoi,	
		avl::KernelShape::Type	inKernel,	
		int						inRadiusX,	
		atl::Optional<int>		inRadiusY,	
		bool					inPreserveDimensions,	
		avl::Surface&			outSurface	
	)
	THROW_AVL_ERRORS;

	/// <summary>Reconstructs missing points of the input surface by interpolating neighboring points.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="inKernel">Kernel shape (predefined).</param>
	/// <param name="inRadiusX">Nearly half of the kernel's width (2*R+1). Default value: 1.</param>
	/// <param name="inRadiusY">Nearly half of the kernel's height (2*R+1), or same as inRadiusX. Default value: atl::NIL.</param>
	/// <param name="outSurface">Output surface.</param>
	AVL_FUNCTION void DilateSurfacePoints
	(
		const avl::Surface&		inSurface,	
		atl::Optional<const avl::Region&>	inRoi,	
		avl::KernelShape::Type	inKernel,	
		int						inRadiusX,	
		atl::Optional<int>		inRadiusY,	
		avl::Surface&			outSurface	
	)
	THROW_AVL_ERRORS;

	/// <summary>Reconstructs missing points of the input surface by interpolating neighboring points.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inRoi">Region of interest. Default value: atl::NIL.</param>
	/// <param name="inKernel">Kernel shape (predefined).</param>
	/// <param name="inRadiusX">Nearly half of the kernel's width (2*R+1). Default value: 1.</param>
	/// <param name="inRadiusY">Nearly half of the kernel's height (2*R+1), or same as inRadiusX. Default value: atl::NIL.</param>
	/// <param name="outSurface">Output surface.</param>
	AVL_FUNCTION void CloseSurfacePoints
	(
		const avl::Surface&		inSurface,	
		atl::Optional<const avl::Region&>	inRoi,	
		avl::KernelShape::Type	inKernel,	
		int						inRadiusX,	
		atl::Optional<int>		inRadiusY,	
		avl::Surface&			outSurface	
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_SURFACESPATIALTRANSFORMS_H

