//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_PROFILEFEATURES_H
#define AVL_PROFILEFEATURES_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.hxx"
#include "Enums/EdgeTransition.h"
#include "Enums/ExtremumType.h"
#include "Enums/Polarity.h"
#include "Enums/ProfileInterpolationMethod.h"
#include "Profile/Profile.h"
#include "Profile/ProfileScanStructs.h"
#include "Profile/Extremum1D.h"
#include "ComputerVision/1DEdgeDetection/ScanParams.h"

namespace avl
{


	/// <summary>Computes the number of elements in a profile.</summary>
	/// <param name="inProfile">Input profile.</param>
	AVL_FUNCTION void ProfileSize
	(
		const avl::Profile&	inProfile,
		int&				outSize
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the sum of the profile values.</summary>
	/// <param name="inProfile">Input profile.</param>
	AVL_FUNCTION void ProfileSum
	(
		const avl::Profile&	inProfile,
		float&			outSum
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds the locations at which the values of the input profile are locally highest or lowest.</summary>
	/// <param name="inProfile">Input profile.</param>
	/// <param name="inCyclic">Indicates whether the last element should be considered a neighbour of the first element.</param>
	/// <param name="inExtremumType">Type of extremum to find.</param>
	/// <param name="inInterpolationMethod">When interpolation is set to Quadratic each non-plateau extremum is located using a parabola fit. Default value: Quadratic4.</param>
	/// <param name="inConsiderPlateaus">Indicates whether the result should include centers of plateau extrema. Default value: True.</param>
	/// <param name="inMinValue">Minimum value of an extremum. Default value: atl::NIL.</param>
	/// <param name="inMaxValue">Maximum value of an extremum. Default value: atl::NIL.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker extrema can be detected in the vicinity of stronger ones. Default value: atl::NIL.</param>
	/// <param name="outLocalExtrema">Extrema of the profile values.</param>
	AVL_FUNCTION void ProfileLocalExtrema
	(
		const avl::Profile&						inProfile, 
		const bool								inCyclic, 
		const avl::ExtremumType::Type			inExtremumType, 
		avl::ProfileInterpolationMethod::Type	inInterpolationMethod, 
		const bool								inConsiderPlateaus, 
		atl::Optional<float>					inMinValue, 
		atl::Optional<float>					inMaxValue, 
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		atl::Array<avl::Extremum1D>&			outLocalExtrema	
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds the points of a profile at which the profile intersects the x-axis.</summary>
	/// <param name="inProfile">Input profile.</param>
	/// <param name="outZeroCrossings">X coordinates of the locations where the profile crosses the y=0 axis.</param>
	AVL_FUNCTION void ProfileZeroCrossings
	(
		const avl::Profile&		inProfile, 
		atl::Array<float>&	outZeroCrossings 
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the average value of a profile.</summary>
	/// <param name="inProfile">Input profile.</param>
	AVL_FUNCTION void ProfileAverage
	(
		const avl::Profile&	inProfile,
		float&			outAverage
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds the highest value of the input profile, its precise location and the corresponding index.</summary>
	/// <param name="inProfile">Input profile.</param>
	/// <param name="inInterpolationMethod">Profile points' interpolation method. Default value: Quadratic4.</param>
	/// <param name="outMaximumPoint">Position of highest value with respect to profile's offset and scale.</param>
	/// <param name="outMaximumIndex">Index of highest value.</param>
	/// <param name="outMaximumValue">Highest value.</param>
	AVL_FUNCTION void ProfileMaximum
	(
		const avl::Profile&						inProfile,	
		avl::ProfileInterpolationMethod::Type	inInterpolationMethod,	
		float&								outMaximumPoint,	
		atl::Optional<int&>						outMaximumIndex = atl::NIL,	
		atl::Optional<float&>				outMaximumValue = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds the lowest value of the input profile, its precise location and the corresponding index.</summary>
	/// <param name="inProfile">Input profile.</param>
	/// <param name="inInterpolationMethod">Profile points' interpolation method. Default value: Quadratic4.</param>
	/// <param name="outMinimumPoint">Position of lowest value with respect to profile's offset and scale.</param>
	/// <param name="outMinimumIndex">Index of lowest value.</param>
	/// <param name="outMinimumValue">Lowest value.</param>
	AVL_FUNCTION void ProfileMinimum
	(
		const avl::Profile&						inProfile,	
		avl::ProfileInterpolationMethod::Type	inInterpolationMethod,	
		float&									outMinimumPoint,	
		atl::Optional<int&>						outMinimumIndex = atl::NIL,	
		atl::Optional<float&>					outMinimumValue = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds subprofiles whose values fall into the specified range.</summary>
	/// <param name="inProfile">Input profile.</param>
	/// <param name="inMinValue">Lower bound for profile values. Default value: 5.0f.</param>
	/// <param name="inMaxValue">Upper bound for profile values. Default value: atl::NIL.</param>
	/// <param name="inMinSectionWidth">Minimal width of the found section. Default value: 0.0f.</param>
	/// <param name="inMaxSectionWidth">Maximal width of the found section. Default value: atl::NIL.</param>
	/// <param name="inMinGapWidth">Minimal distance between consecutive sections. Default value: 0.0f.</param>
	/// <param name="inMaxGapWidth">Maximal distance between consecutive sections. Default value: atl::NIL.</param>
	/// <param name="inMaxInnerGapWidth">Maximal possible gap width between two sections to join them into one. Default value: 0.0f.</param>
	/// <param name="outSections">Output profile sections.</param>
	/// <param name="outBoundingSection">The smallest section that contains all outSections.</param>
	AVL_FUNCTION void ProfileSections
	(
		const avl::Profile&						inProfile,
		atl::Optional<float>					inMinValue,			
		atl::Optional<float>					inMaxValue,			
		const float								inMinSectionWidth,	
		atl::Optional<float>					inMaxSectionWidth,	
		float									inMinGapWidth,		
		atl::Optional<float>					inMaxGapWidth,		
		atl::Optional<float>					inMaxInnerGapWidth,	
		atl::Array<avl::ProfileSection>&		outSections,		
		atl::Conditional<avl::ProfileSection>&	outBoundingSection	
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns coefficients of linear function (in form y = Ax + B) that illustrates the trend of profile. Uses ordinary least squares method.</summary>
	/// <param name="inProfile">Input profile.</param>
	AVL_FUNCTION void ProfileLinearRegression_Deprecated
	(
		const avl::Profile&	inProfile,
		float&			outA,
		float&			outB
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds the locations at which the profile values raise or fall quickly.</summary>
	/// <param name="inProfile">Input profile.</param>
	/// <param name="inEdgeScanParams">Parameters controlling the edge extraction process. Default value: EdgeScanParams ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 0.6f MinMagnitude: 5.0f EdgeTransition: BrightToDark ).</param>
	/// <param name="inMinDistance">Minimal distance between consecutive edges. Default value: 0.0f.</param>
	/// <param name="inMaxDistance">Maximal distance between consecutive edges. Default value: atl::NIL.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="outEdges">Found edges.</param>
	/// <param name="outDistances">Output distances between consecutive edges.</param>
	/// <param name="diagResponseProfile">Profile of the edge (derivative) operator response.</param>
	AVL_FUNCTION void ProfileEdges
	(
		const avl::Profile&						inProfile,
		bool									inCyclic,
		const avl::EdgeScanParams&				inEdgeScanParams,	
		float								inMinDistance,		
		atl::Optional<float>				inMaxDistance,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		atl::Array<avl::ProfileEdge>&			outEdges,			
		atl::Optional<atl::Array<float>&>	outDistances = atl::NIL,	
		avl::Profile&							diagResponseProfile = atl::Dummy<avl::Profile>()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds the high or low peaks in the input profile.</summary>
	/// <param name="inProfile">Input profile.</param>
	/// <param name="inRidgeScanParams">Parameters controlling the ridge extraction process. Default value: RidgeScanParams ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 0.6f RidgeWidth: 5 RidgeMargin: 2 MinMagnitude: 5.0f RidgePolarity: Bright ).</param>
	/// <param name="inMinDistance">Minimal distance between consecutive ridges. Default value: 0.0f.</param>
	/// <param name="inMaxDistance">Maximal distance between consecutive ridges. Default value: atl::NIL.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker ridges can be detected in the vicinity of stronger ridges. Default value: atl::NIL.</param>
	/// <param name="outRidges">Found ridges.</param>
	/// <param name="outDistances">Output distances between consecutive ridges.</param>
	/// <param name="diagResponseProfile">Profile of the ridge operator response.</param>
	AVL_FUNCTION void ProfileRidges
	(
		const avl::Profile&						inProfile,
		bool									inCyclic,
		const avl::RidgeScanParams&				inRidgeScanParams,	
		float									inMinDistance,		
		atl::Optional<float>					inMaxDistance,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		atl::Array<avl::ProfileRidge>&			outRidges,			
		atl::Optional<atl::Array<float>&>		outDistances = atl::NIL,	
		avl::Profile&							diagResponseProfile = atl::Dummy<avl::Profile>()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds pairs of opposite (raising and falling) edges in the input profile.</summary>
	/// <param name="inProfile">Input profile.</param>
	/// <param name="inStripeScanParams">Parameters controlling the stripe extraction process. Default value: StripeScanParams ( ProfileInterpolation: Quadratic4 SmoothingStdDev: 0.6f MinMagnitude: 5.0f MaxInnerEdgeMagnitude: Nil StripePolarity: Bright MinStripeWidth: 0.0f MaxStripeWidth: Nil ).</param>
	/// <param name="inMinGapWidth">Minimal distance between consecutive stripes. Default value: 0.0f.</param>
	/// <param name="inMaxGapWidth">Maximal distance between consecutive stripes. Default value: atl::NIL.</param>
	/// <param name="inLocalBlindness">Defines conditions in which weaker edges can be detected in the vicinity of stronger edges. Default value: atl::NIL.</param>
	/// <param name="outStripes">Found stripes.</param>
	/// <param name="outGapWidths">Distances between consecutive stripes.</param>
	/// <param name="diagResponseProfile">Profile of the edge (derivative) operator response.</param>
	AVL_FUNCTION void ProfileStripes
	(
		const avl::Profile&						inProfile,
		bool									inCyclic,
		const avl::StripeScanParams&			inStripeScanParams,	
		float									inMinGapWidth,		
		atl::Optional<float>					inMaxGapWidth,		
		atl::Optional<const avl::LocalBlindness&>	inLocalBlindness,	
		atl::Array<avl::ProfileStripe>&			outStripes,			
		atl::Optional<atl::Array<float>&>		outGapWidths = atl::NIL,	
		avl::Profile&							diagResponseProfile = atl::Dummy<avl::Profile>()	
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_PROFILEFEATURES_H

