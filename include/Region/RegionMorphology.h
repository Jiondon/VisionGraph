//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_REGIONMORPHOLOGY_H
#define AVL_REGIONMORPHOLOGY_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Enums/KernelShape.h"
#include "Enums/RegionSkeletonMethod.h"
#include "Enums/Metric.h"
#include "Geometry/Geometry.h"
#include "Region/Region.h"

namespace avl
{


	/// <summary>Performs a morphological dilation on a region using an arbitrary kernel.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inKernel">Kernel shape (any).</param>
	/// <param name="inKernelAnchor">Location within inKernel, defining its center. Default value: atl::NIL.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void DilateRegion_AnyKernel
	(
		const avl::Region&					inRegion,
		const avl::Region&					inKernel,		
		atl::Optional<const avl::Location&> inKernelAnchor,	
		avl::Region&						outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a morphological dilation on a region using a predefined kernel.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inKernel">Kernel shape (predefined).</param>
	/// <param name="inRadiusX">Nearly half of the kernel's width (2*R+1). Default value: 1.</param>
	/// <param name="inRadiusY">Nearly half of the kernel's height (2*R+1), or same as inRadiusX. Default value: atl::NIL.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void DilateRegion
	(
		const avl::Region&					inRegion,
		avl::KernelShape::Type	inKernel,	
		int									inRadiusX,	
		atl::Optional<int>					inRadiusY,	
		avl::Region&						outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary></summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void DilateRegion_AnyKernel_Old
	(
		const avl::Region&					inRegion,
		const avl::Region&					inKernel,
		atl::Optional<const avl::Location&> inKernelAnchor,
		avl::Region&						outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a morphological erosion on a region using an arbitrary kernel.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inKernel">Kernel shape (any).</param>
	/// <param name="inKernelAnchor">Location within inKernel, defining its center. Default value: atl::NIL.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void ErodeRegion_AnyKernel
	(
		const avl::Region&					inRegion,
		const avl::Region&					inKernel,		
		atl::Optional<const avl::Location&> inKernelAnchor,	
		avl::Region&						outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary></summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inKernel">Kernel shape (any).</param>
	/// <param name="inKernelAnchor">Location within inKernel, defining its center. Default value: atl::NIL.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void ErodeRegion_AnyKernel_Old
	(
		const avl::Region&					inRegion,
		const avl::Region&					inKernel,		
		atl::Optional<const avl::Location&> inKernelAnchor,	
		avl::Region&						outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a morphological erosion on a region using a predefined kernel.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inKernel">Kernel shape (predefined).</param>
	/// <param name="inRadiusX">Nearly half of the kernel's width (2*R+1). Default value: 1.</param>
	/// <param name="inRadiusY">Nearly half of the kernel's height (2*R+1), or same as inRadiusX. Default value: atl::NIL.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void ErodeRegion
	(
		const avl::Region&					inRegion,
		avl::KernelShape::Type	inKernel,	
		int									inRadiusX,	
		atl::Optional<int>					inRadiusY,	
		avl::Region&						outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Erodes a region with inThresholdValue pixels of inKernel.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void ErodeRegion_Threshold
	(
		const avl::Region&				inRegion,
		const avl::Region&				inKernel,
		atl::Optional<avl::Location&>	inKernelAnchor,
		const int&						inThresholdValue,
		avl::Region&					outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a morphological opening on a region using an arbitrary kernel.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inKernel">Kernel shape (any).</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void OpenRegion_AnyKernel
	(
		const avl::Region&	inRegion,
		const avl::Region&	inKernel,	
		avl::Region&		outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a morphological opening on a region using a predefined kernel.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inKernel">Kernel shape (predefined).</param>
	/// <param name="inRadiusX">Nearly half of the kernel's width (2*R+1). Default value: 1.</param>
	/// <param name="inRadiusY">Nearly half of the kernel's height (2*R+1), or same as inRadiusX. Default value: atl::NIL.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void OpenRegion
	(
		const avl::Region&					inRegion,
		avl::KernelShape::Type	inKernel,	
		int									inRadiusX,	
		atl::Optional<int>					inRadiusY,	
		avl::Region&						outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a morphological closing on a region using an arbitrary kernel.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inKernel">Kernel shape (any).</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void CloseRegion_AnyKernel
	(
		const avl::Region&	inRegion,
		const avl::Region&	inKernel,	
		avl::Region&		outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a morphological closing on a region using selected predefined kernel.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inKernel">Kernel shape (predefined).</param>
	/// <param name="inRadiusX">Nearly half of the kernel's width (2*R+1). Default value: 1.</param>
	/// <param name="inRadiusY">Nearly half of the kernel's height (2*R+1), or same as inRadiusX. Default value: atl::NIL.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void CloseRegion
	(
		const avl::Region&					inRegion,
		avl::KernelShape::Type	inKernel,	
		int									inRadiusX,	
		atl::Optional<int>					inRadiusY,	
		avl::Region&						outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a hit-and-miss transformation on a region using arbitrary kernels.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inHitKernel">The kernel of pixels that should be present.</param>
	/// <param name="inHitKernelAnchor">Location withing inHitKernel, defining its center. Default value: atl::NIL.</param>
	/// <param name="inMissKernel">The kernel of pixels that should be missing.</param>
	/// <param name="inMissKernelAnchor">Location withing inMissKernel, defining its center. Default value: atl::NIL.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void RegionHitAndMissTransform
	(
		const avl::Region&					inRegion,
		const avl::Region&					inHitKernel,		
		atl::Optional<const avl::Location&>	inHitKernelAnchor,	
		const avl::Region&					inMissKernel,		
		atl::Optional<const avl::Location&>	inMissKernelAnchor,	
		avl::Region&						outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a morphological thinning on a region using predefined kernels.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void ThinRegion
	(
		const avl::Region&	inRegion,
		avl::Region&		outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Performs a morphological thickening on a region using predefined kernels.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void ThickenRegion
	(
		const avl::Region&	inRegion,
		avl::Region&		outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Removes one pixel wide branches from a region.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inMaxLength">Maximal length of a branch of the input region to be pruned. Default value: 3.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void PruneRegion
	(
		const avl::Region&	inRegion,
		const int			inMaxLength,	
		avl::Region&		outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Thins a region to its skeleton.</summary>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inRegionSkeletonMethod">Default value: TwelveConnected.</param>
	/// <param name="outRegion">Output region.</param>
	AVL_FUNCTION void SkeletonizeRegion
	(
		const avl::Region&				inRegion,
		avl::RegionSkeletonMethod::Type	inRegionSkeletonMethod,
		avl::Region&					outRegion
	)
	THROW_AVL_ERRORS;

	/// <summary>Splits common pixels of the input regions among these regions.</summary>
	/// <param name="inMetric">Metric used for deciding which region owns a pixel; if set to NIL, region with lowest index in the input array is chosen. Default value: atl::NIL.</param>
	AVL_FUNCTION void DemarcateRegions
	(
		const atl::Array<avl::Region>&		inRegions,
		atl::Optional<avl::Metric::Type>	inMetric,	
		atl::Array<avl::Region>&			outRegions
	)
	THROW_AVL_ERRORS;

	/// <summary>Splits pixels of the input regions and their complement among these regions.</summary>
	/// <param name="inMetric">Metric used for deciding which region receives a pixel; if set to NIL, Taxi metric is used after demarcating with NIL metric. Default value: atl::NIL.</param>
	AVL_FUNCTION void ExpandRegions
	(
		const atl::Array<avl::Region>&		inRegions,
		atl::Optional<avl::Metric::Type>	inMetric,	
		atl::Array<avl::Region>&			outRegions
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_REGIONMORPHOLOGY_H

