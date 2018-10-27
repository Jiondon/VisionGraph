//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVS_1DEDGEDETECTION3D_H
#define AVS_1DEDGEDETECTION3D_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Optional.h"
#include "Enums/Selection.h"
#include "Enums/InterpolationMethod.h"
#include "Enums/ProfileInterpolationMethod.h"
#include "Geometry3D/Geometry3D.h"
#include "Surface/Surface.h"
#include "Surface/SurfaceFormat.h"
#include "Path/Path.h"
#include "Profile/Profile.h"
#include "ComputerVision/1DEdgeDetection/ScanMap.h"
#include "ComputerVision/1DEdgeDetection/ScanMapState.h"
#include "ComputerVision/1DEdgeDetection/ScanParams3D.h"
#include "ComputerVision/1DEdgeDetection/ScanParams.h"
#include "ComputerVision/1DEdgeDetection/ScanStructs3D.h"

namespace avl
{


	/// <summary>Precomputes a data object that is required for fast 1D edge detection in 3D.</summary>
	/// <param name="inSurfaceFormat">Dimensions, depth image pixel type, coordinate offsets and scales of a surface on which edge detection will be performed.</param>
	/// <param name="inScanPath">Path along which the scan is performed.</param>
	/// <param name="inScanPathAlignment">Adjusts the scan path to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanWidth">Width of the scan field in pixels of the surface depth image. Default value: 5.</param>
	/// <param name="inSurfaceInterpolation">Interpolation method used for extraction of depth image pixel values. Default value: Bilinear.</param>
	/// <param name="outScanMap">Optimized data object required for 1D edge detection in 3D.</param>
	/// <param name="outAlignedScanPath">Transformed input path.</param>
	AVL_FUNCTION void CreateSurfaceScanMap
	(
		const avl::SurfaceFormat&						inSurfaceFormat,		
		const avl::Path&								inScanPath,				
		atl::Optional<const avl::CoordinateSystem2D&>	inScanPathAlignment,	
		int												inScanWidth,			
		avl::InterpolationMethod::Type					inSurfaceInterpolation,	
		avl::ScanMap&									outScanMap,				
		atl::Optional<avl::Path&>						outAlignedScanPath = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Locates the strongest change of surface height along a given path.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inScanMap">Data precomputed with CreateSurfaceScanMap.</param>
	/// <param name="inEdgeScanParams">Parameters controlling the surface edge extraction process.</param>
	/// <param name="inEdgeSelection">Selection mode of the resulting edge. Default value: avl::Selection::Best.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxInterpolationLength">Maximal number of consecutive not existing profile points. Default value: 1.</param>
	/// <param name="outEdge">Found surface edge.</param>
	/// <param name="diagHeightProfile">Extracted surface height profile.</param>
	/// <param name="diagResponseProfile">Profile of the edge (derivative) operator response.</param>
	AVL_FUNCTION void ScanSingleEdge3D
	(
		const avl::Surface&					inSurface,			
		const avl::ScanMap&					inScanMap,			
		const avl::EdgeScanParams3D&		inEdgeScanParams,	
		avl::Selection::Type				inEdgeSelection,	
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		atl::Optional<int>					inMaxInterpolationLength,	
		atl::Conditional<avl::SurfaceEdge1D>&	outEdge,		
		avl::Profile&						diagHeightProfile = atl::Dummy<avl::Profile>(),	
		avl::Profile&						diagResponseProfile = atl::Dummy<avl::Profile>()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Locates multiple changes of surface height along a given path.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inScanMap">Data precomputed with CreateSurfaceScanMap.</param>
	/// <param name="inEdgeScanParams">Parameters controlling the surface edge extraction process.</param>
	/// <param name="inMinDistance">Minimal distance between consecutive edges.</param>
	/// <param name="inMaxDistance">Maximal distance between consecutive edges. Default value: atl::NIL.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxInterpolationLength">Maximal number of consecutive not existing profile points. Default value: atl::NIL.</param>
	/// <param name="outEdges">Found surface edges.</param>
	/// <param name="diagHeightProfile">Extracted surface height profile.</param>
	/// <param name="diagResponseProfile">Profile of the edge (derivative) operator response.</param>
	AVL_FUNCTION void ScanMultipleEdges3D
	(
		const avl::Surface&				inSurface,			
		const avl::ScanMap&				inScanMap,			
		const avl::EdgeScanParams3D&	inEdgeScanParams,	
		float							inMinDistance,		
		atl::Optional<float>			inMaxDistance,		
		atl::Optional<const avl::LocalBlindness&>		inLocalBlindness,	
		atl::Optional<int>				inMaxInterpolationLength,	
		atl::Array<avl::SurfaceEdge1D>&	outEdges,			
		avl::Profile&					diagHeightProfile = atl::Dummy<avl::Profile>(),	
		avl::Profile&					diagResponseProfile = atl::Dummy<avl::Profile>()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Locates a specified number of the strongest changes of surface height along a given path.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inScanMap">Data precomputed with CreateSurfaceScanMap.</param>
	/// <param name="inEdgeScanParams">Parameters controlling the surface edge extraction process.</param>
	/// <param name="inEdgeCount">Number of surface edges to be found. Default value: 1.</param>
	/// <param name="inEdgeSelection">Selection mode of the resulting edges. Default value: avl::Selection::Best.</param>
	/// <param name="inMinDistance">Minimal distance between consecutive edges. Default value: 0.0f.</param>
	/// <param name="inMaxDistance">Maximal distance between consecutive edges. Default value: atl::NIL.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxInterpolationLength">Maximal number of consecutive not existing profile points. Default value: 1.</param>
	/// <param name="outEdges">Found surface edges.</param>
	/// <param name="diagHeightProfile">Extracted surface height profile.</param>
	/// <param name="diagResponseProfile">Profile of the edge (derivative) operator response.</param>
	AVL_FUNCTION void ScanExactlyNEdges3D
	(
		const avl::Surface&					inSurface,			
		const avl::ScanMap&					inScanMap,			
		const avl::EdgeScanParams3D&		inEdgeScanParams,	
		int									inEdgeCount,		
		avl::Selection::Type				inEdgeSelection,	
		float								inMinDistance,		
		atl::Optional<float>				inMaxDistance,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		atl::Optional<int>					inMaxInterpolationLength,	
		atl::Conditional<atl::Array<avl::SurfaceEdge1D> >&	outEdges,		
		avl::Profile&						diagHeightProfile = atl::Dummy<avl::Profile>(),	
		avl::Profile&						diagResponseProfile = atl::Dummy<avl::Profile>()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Locates the strongest pair of changes of surface height along a given path.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inScanMap">Data precomputed with CreateSurfaceScanMap.</param>
	/// <param name="inStripeScanParams">Parameters controlling the surface stripe extraction process.</param>
	/// <param name="inStripeSelection">Selection mode of the resulting stripe. Default value: avl::Selection::Best.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxInterpolationLength">Maximal number of consecutive not existing profile points. Default value: 1.</param>
	/// <param name="outStripe">Found surface stripe.</param>
	/// <param name="diagHeightProfile">Extracted surface height profile.</param>
	/// <param name="diagResponseProfile">Profile of the edge (derivative) operator response.</param>
	AVL_FUNCTION void ScanSingleStripe3D
	(
		const avl::Surface&				inSurface,			
		const avl::ScanMap&				inScanMap,			
		const avl::StripeScanParams3D&	inStripeScanParams,	
		avl::Selection::Type			inStripeSelection,	
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		atl::Optional<int>				inMaxInterpolationLength,	
		atl::Conditional<avl::SurfaceStripe1D>&	outStripe,		
		avl::Profile&					diagHeightProfile = atl::Dummy<avl::Profile>(),		
		avl::Profile&					diagResponseProfile = atl::Dummy<avl::Profile>()		
	)
	THROW_AVL_ERRORS;

	/// <summary>Locates multiple pairs of changes of surface height along a given path.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inScanMap">Data precomputed with CreateSurfaceScanMap.</param>
	/// <param name="inStripeScanParams">Parameters controlling the surface stripe extraction process.</param>
	/// <param name="inMinGapWidth">Minimal distance between consecutive surface stripes. Default value: 0.0f.</param>
	/// <param name="inMaxGapWidth">Maximal distance between consecutive surface stripes. Default value: atl::NIL.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxInterpolationLength">Maximal number of consecutive not existing profile points. Default value: 1.</param>
	/// <param name="outStripes">Found surface stripes.</param>
	/// <param name="diagHeightProfile">Extracted surface height profile.</param>
	/// <param name="diagResponseProfile">Profile of the edge (derivative) operator response.</param>
	AVL_FUNCTION void ScanMultipleStripes3D
	(
		const avl::Surface&			inSurface,			
		const avl::ScanMap&			inScanMap,			
		const avl::StripeScanParams3D&	inStripeScanParams,	
		float						inMinGapWidth,		
		atl::Optional<float>		inMaxGapWidth,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		atl::Optional<int>			inMaxInterpolationLength,	
		atl::Array<avl::SurfaceStripe1D>&	outStripes,	
		avl::Profile&				diagHeightProfile = atl::Dummy<avl::Profile>(),	
		avl::Profile&				diagResponseProfile = atl::Dummy<avl::Profile>()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Locates a specified number of multiple pairs of changes of surface height along a given path.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inScanMap">Data precomputed with CreateSurfaceScanMap.</param>
	/// <param name="inStripeScanParams">Parameters controlling the surface stripe extraction process.</param>
	/// <param name="inStripeCount">Number of surface stripes to be found. Default value: 1.</param>
	/// <param name="inStripeSelection">Selection mode of the resulting stripes. Default value: avl::Selection::Best.</param>
	/// <param name="inMinGapWidth">Minimal distance between consecutive surface stripes.</param>
	/// <param name="inMaxGapWidth">Maximal distance between consecutive surface stripes. Default value: atl::NIL.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxInterpolationLength">Maximal number of consecutive not existing profile points. Default value: 1.</param>
	/// <param name="outStripes">Found surface stripes.</param>
	/// <param name="diagHeightProfile">Extracted surface height profile.</param>
	/// <param name="diagResponseProfile">Profile of the edge (derivative) operator response.</param>
	AVL_FUNCTION void ScanExactlyNStripes3D
	(
		const avl::Surface&					inSurface,			
		const ScanMap&						inScanMap,			
		const StripeScanParams3D&			inStripeScanParams,	
		int									inStripeCount,		
		avl::Selection::Type				inStripeSelection,	
		float								inMinGapWidth,		
		atl::Optional<float>				inMaxGapWidth,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		atl::Optional<int>					inMaxInterpolationLength,	
		atl::Conditional<atl::Array<avl::SurfaceStripe1D> >&	outStripes,		
		avl::Profile&						diagHeightProfile = atl::Dummy<avl::Profile>(),	
		avl::Profile&						diagResponseProfile = atl::Dummy<avl::Profile>()	
	)
	THROW_AVL_ERRORS;

} // namespace avl

namespace avs
{

	typedef avl::ScanMapState ScanSingleEdge3DState;
	typedef avl::ScanMapState ScanMultipleEdges3DState;
	typedef avl::ScanMapState ScanExactlyNEdges3DState;
	typedef avl::ScanMapState ScanSingleStripe3DState;
	typedef avl::ScanMapState ScanMultipleStripes3DState;
	typedef avl::ScanMapState ScanExactlyNStripes3DState;


	/// <summary>Locates the strongest change of surface height along a given path.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inScanPath">Path along which the scan is performed.</param>
	/// <param name="inScanPathAlignment">Adjusts the scan path to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanWidth">Width of the scan field in pixels. Default value: 5.</param>
	/// <param name="inSurfaceInterpolation">Interpolation method used for extraction of surface points. Default value: Bilinear.</param>
	/// <param name="inEdgeScanParams">Parameters controlling the surface edge extraction process. Default value: EdgeScanParams3D ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 0.6f MinMagnitude: 5.0f EdgeTransition: LowToHigh ).</param>
	/// <param name="inEdgeSelection">If many edge points are possible, defines which one is selected.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxInterpolationLength">Maximal number of consecutive not existing profile points. Default value: 1.</param>
	/// <param name="outEdge">Found surface edge.</param>
	/// <param name="outAlignedScanPath">Path along which the scan is performed; in the image coordinate system.</param>
	/// <param name="diagHeightProfile">Extracted surface height profile.</param>
	/// <param name="diagResponseProfile">Profile of the edge (derivative) operator response.</param>
	AVL_FUNCTION void AvsFilter_ScanSingleEdge3D
	(
		ScanSingleEdge3DState&					ioState,
		const avl::Surface&						inSurface,					
		const avl::Path&						inScanPath,					
		atl::Optional<const avl::CoordinateSystem2D&> inScanPathAlignment,	
		int										inScanWidth,				
		avl::InterpolationMethod::Type			inSurfaceInterpolation,		
		const avl::EdgeScanParams3D&			inEdgeScanParams,			
		avl::Selection::Type					inEdgeSelection,			
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,		
		atl::Optional<int>						inMaxInterpolationLength,	
		atl::Conditional<avl::SurfaceEdge1D>&	outEdge,					
		atl::Optional<avl::Path&>				outAlignedScanPath = atl::NIL, 
		avl::Profile&							diagHeightProfile = atl::Dummy<avl::Profile>(),			
		avl::Profile&							diagResponseProfile = atl::Dummy<avl::Profile>()		
	)
	THROW_AVL_ERRORS;

	/// <summary>Locates multiple changes of surface height along a given path.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inScanPath">Path along which the scan is performed.</param>
	/// <param name="inScanPathAlignment">Adjusts the scan path to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanWidth">Width of the scan field in pixels. Default value: 5.</param>
	/// <param name="inSurfaceInterpolation">Interpolation method used for extraction of surface points. Default value: Bilinear.</param>
	/// <param name="inEdgeScanParams">Parameters controlling the surface edge extraction process. Default value: EdgeScanParams3D ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 0.6f MinMagnitude: 5.0f EdgeTransition: LowToHigh ).</param>
	/// <param name="inMinDistance">Minimal distance between consecutive edges. Default value: 0.0f.</param>
	/// <param name="inMaxDistance">Maximal distance between consecutive edges. Default value: atl::NIL.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxInterpolationLength">Maximal number of consecutive not existing profile points. Default value: 1.</param>
	/// <param name="outEdges">Found surface edges.</param>
	/// <param name="outAlignedScanPath">Path along which the scan is performed; in the image coordinate system.</param>
	/// <param name="diagHeightProfile">Extracted surface height profile.</param>
	/// <param name="diagResponseProfile">Profile of the edge (derivative) operator response.</param>
	AVL_FUNCTION void AvsFilter_ScanMultipleEdges3D
	(
		ScanMultipleEdges3DState&			ioState,
		const avl::Surface&					inSurface,			
		const avl::Path&					inScanPath,				
		atl::Optional<const avl::CoordinateSystem2D&>	inScanPathAlignment,
		int									inScanWidth,			
		avl::InterpolationMethod::Type		inSurfaceInterpolation,	
		const avl::EdgeScanParams3D&		inEdgeScanParams,		
		float								inMinDistance,			
		atl::Optional<float>				inMaxDistance,			
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		atl::Optional<int>					inMaxInterpolationLength,	
		atl::Array<avl::SurfaceEdge1D>&		outEdges,				
		atl::Optional<avl::Path&>			outAlignedScanPath = atl::NIL,	
		avl::Profile&						diagHeightProfile = atl::Dummy<avl::Profile>(),			
		avl::Profile&						diagResponseProfile = atl::Dummy<avl::Profile>()		
	)
	THROW_AVL_ERRORS;

	/// <summary>Locates a specified number of the strongest changes of surface height along a given path.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inScanPath">Path along which the scan is performed.</param>
	/// <param name="inScanPathAlignment">Adjusts the scan path to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanWidth">Width of the scan field in pixels. Default value: 5.</param>
	/// <param name="inSurfaceInterpolation">Interpolation method used for extraction of surface points. Default value: Bilinear.</param>
	/// <param name="inEdgeScanParams">Parameters controlling the surface edge extraction process. Default value: EdgeScanParams3D ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 0.6f MinMagnitude: 5.0f EdgeTransition: LowToHigh ).</param>
	/// <param name="inEdgeCount">Number of surface edges to be found. Default value: 1.</param>
	/// <param name="inEdgeSelection">Selection mode of the resulting edges.</param>
	/// <param name="inMinDistance">Minimal distance between consecutive edges. Default value: 0.0f.</param>
	/// <param name="inMaxDistance">Maximal distance between consecutive edges. Default value: atl::NIL.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxInterpolationLength">Maximal number of consecutive not existing profile points. Default value: 1.</param>
	/// <param name="outEdges">Found surface edges.</param>
	/// <param name="outAlignedScanPath">Path along which the scan is performed; in the image coordinate system.</param>
	/// <param name="diagHeightProfile">Extracted surface height profile.</param>
	/// <param name="diagResponseProfile">Profile of the edge (derivative) operator response.</param>
	AVL_FUNCTION void AvsFilter_ScanExactlyNEdges3D
	(
		ScanExactlyNEdges3DState&				ioState,
		const avl::Surface&						inSurface,			
		const avl::Path&						inScanPath,			
		atl::Optional<const avl::CoordinateSystem2D&>	inScanPathAlignment,
		int										inScanWidth,		
		avl::InterpolationMethod::Type			inSurfaceInterpolation, 
		const avl::EdgeScanParams3D&			inEdgeScanParams,	
		int										inEdgeCount,		
		avl::Selection::Type					inEdgeSelection,	
		float									inMinDistance,		
		atl::Optional<float>					inMaxDistance,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		atl::Optional<int>						inMaxInterpolationLength,	
		atl::Conditional<atl::Array<avl::SurfaceEdge1D> >&	outEdges,		
		atl::Optional<avl::Path&>				outAlignedScanPath = atl::NIL,		
		avl::Profile&							diagHeightProfile = atl::Dummy<avl::Profile>(),			
		avl::Profile&							diagResponseProfile = atl::Dummy<avl::Profile>() 
	)
	THROW_AVL_ERRORS;

	/// <summary>Locates the strongest pair of changes of surface height along a given path.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inScanPath">Path along which the scan is performed.</param>
	/// <param name="inScanPathAlignment">Adjusts the scan path to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanWidth">Width of the scan field in pixels. Default value: 5.</param>
	/// <param name="inSurfaceInterpolation">Interpolation method used for extraction of surface points. Default value: Bilinear.</param>
	/// <param name="inStripeScanParams">Parameters controlling the surface stripe extraction process. Default value: StripeScanParams3D ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 0.6f MinMagnitude: 5.0f MaxInnerEdgeMagnitude: Nil StripePolarity: Low MinStripeWidth: 0.0f MaxStripeWidth: Nil ).</param>
	/// <param name="inStripeSelection">Selection mode of the resulting surface stripe.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxInterpolationLength">Maximal number of consecutive not existing profile points. Default value: 1.</param>
	/// <param name="outStripe">Found surface stripe.</param>
	/// <param name="outAlignedScanPath">Path along which the scan is performed; in the image coordinate system.</param>
	/// <param name="diagHeightProfile">Extracted surface height profile.</param>
	/// <param name="diagResponseProfile">Profile of the edge (derivative) operator response.</param>
	AVL_FUNCTION void AvsFilter_ScanSingleStripe3D
	(
		ScanSingleStripe3DState&				ioState,
		const avl::Surface&						inSurface,			
		const avl::Path&						inScanPath,			
		atl::Optional<const avl::CoordinateSystem2D&>	inScanPathAlignment,
		int										inScanWidth,		
		avl::InterpolationMethod::Type			inSurfaceInterpolation, 
		const avl::StripeScanParams3D&			inStripeScanParams,	
		avl::Selection::Type					inStripeSelection,	
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		atl::Optional<int>						inMaxInterpolationLength,	
		atl::Conditional<avl::SurfaceStripe1D>&		outStripe,			
		atl::Optional<avl::Path&>				outAlignedScanPath = atl::NIL,		
		avl::Profile&							diagHeightProfile = atl::Dummy<avl::Profile>(),		
		avl::Profile&							diagResponseProfile = atl::Dummy<avl::Profile>()		
	)
	THROW_AVL_ERRORS;

	/// <summary>Locates multiple pairs of changes of surface height along a given path.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inScanPath">Path along which the scan is performed.</param>
	/// <param name="inScanPathAlignment">Adjusts the scan path to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanWidth">Width of the scan field in pixels. Default value: 5.</param>
	/// <param name="inSurfaceInterpolation">Interpolation method used for extraction of surface points. Default value: Bilinear.</param>
	/// <param name="inStripeScanParams">Parameters controlling the surface stripe extraction process. Default value: StripeScanParams3D ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 0.6f MinMagnitude: 5.0f MaxInnerEdgeMagnitude: Nil StripePolarity: Low MinStripeWidth: 0.0f MaxStripeWidth: Nil ).</param>
	/// <param name="inMinGapWidth">Minimal distance between consecutive surface stripes. Default value: 0.0f.</param>
	/// <param name="inMaxGapWidth">Maximal distance between consecutive surface stripes. Default value: atl::NIL.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxInterpolationLength">Maximal number of consecutive not existing profile points. Default value: 1.</param>
	/// <param name="outStripes">Found surface stripes.</param>
	/// <param name="outAlignedScanPath">Path along which the scan is performed; in the image coordinate system.</param>
	/// <param name="diagHeightProfile">Extracted surface height profile.</param>
	/// <param name="diagResponseProfile">Profile of the edge (derivative) operator response.</param>
	AVL_FUNCTION void AvsFilter_ScanMultipleStripes3D
	(
		ScanMultipleStripes3DState&				ioState,
		const avl::Surface&						inSurface,				
		const avl::Path&						inScanPath,				
		atl::Optional<const avl::CoordinateSystem2D&>	inScanPathAlignment,	
		int										inScanWidth,			
		avl::InterpolationMethod::Type			inSurfaceInterpolation,	
		const avl::StripeScanParams3D&			inStripeScanParams,		
		float									inMinGapWidth,		
		atl::Optional<float>					inMaxGapWidth,		
		atl::Optional<const avl::LocalBlindness&>				inLocalBlindness,	
		atl::Optional<int>						inMaxInterpolationLength,	
		atl::Array<avl::SurfaceStripe1D>&		outStripes,			
		atl::Optional<avl::Path&>				outAlignedScanPath = atl::NIL,		
		avl::Profile&							diagHeightProfile = atl::Dummy<avl::Profile>(),	
		avl::Profile&							diagResponseProfile = atl::Dummy<avl::Profile>()   
	)
	THROW_AVL_ERRORS;

	/// <summary>Locates a specified number of multiple pairs of changes of surface height along a given path.</summary>
	/// <param name="inSurface">Input surface.</param>
	/// <param name="inScanPath">Path along which the scan is performed.</param>
	/// <param name="inScanPathAlignment">Adjusts the scan path to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanWidth">Width of the scan field in pixels. Default value: 5.</param>
	/// <param name="inSurfaceInterpolation">Interpolation method used for extraction of surface points. Default value: Bilinear.</param>
	/// <param name="inStripeScanParams">Parameters controlling the surface stripe extraction process. Default value: StripeScanParams3D ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 0.6f MinMagnitude: 5.0f MaxInnerEdgeMagnitude: Nil StripePolarity: Low MinStripeWidth: 0.0f MaxStripeWidth: Nil ).</param>
	/// <param name="inStripeCount">Number of surface stripes to be found. Default value: 1.</param>
	/// <param name="inStripeSelection">Selection mode of the resulting stripes.</param>
	/// <param name="inMinGapWidth">Minimal distance between consecutive surface stripes. Default value: 0.0f.</param>
	/// <param name="inMaxGapWidth">Maximal distance between consecutive surface stripes. Default value: atl::NIL.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="inMaxInterpolationLength">Maximal number of consecutive not existing profile points. Default value: 1.</param>
	/// <param name="outStripes">Found surface stripes.</param>
	/// <param name="outAlignedScanPath">Path along which the scan is performed; in the image coordinate system.</param>
	/// <param name="diagHeightProfile">Extracted surface height profile.</param>
	/// <param name="diagResponseProfile">Profile of the edge (derivative) operator response.</param>
	AVL_FUNCTION void AvsFilter_ScanExactlyNStripes3D
	(
		ScanExactlyNStripes3DState&				ioState,
		const avl::Surface&						inSurface,			
		const avl::Path&						inScanPath,			
		atl::Optional<const avl::CoordinateSystem2D&>	inScanPathAlignment,
		int										inScanWidth,		
		avl::InterpolationMethod::Type			inSurfaceInterpolation, 
		const avl::StripeScanParams3D&			inStripeScanParams,	
		int										inStripeCount,		
		avl::Selection::Type					inStripeSelection,	
		float									inMinGapWidth,	
		atl::Optional<float>					inMaxGapWidth,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		atl::Optional<int>						inMaxInterpolationLength,	
		atl::Conditional<atl::Array<avl::SurfaceStripe1D> >&	outStripes,	
		atl::Optional<avl::Path&>				outAlignedScanPath = atl::NIL,		
		avl::Profile&							diagHeightProfile = atl::Dummy<avl::Profile>(),	
		avl::Profile&							diagResponseProfile = atl::Dummy<avl::Profile>()    
	)
	THROW_AVL_ERRORS;

} // namespace avs

#endif // AVS_1DEDGEDETECTION3D_H

