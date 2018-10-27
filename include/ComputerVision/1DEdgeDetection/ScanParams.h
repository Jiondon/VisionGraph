//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _SCANPARAMS_H
#define _SCANPARAMS_H

#include "ATL/AtlTypes.h"
#include "ATL/Optional.h"
#include "Enums/EdgeTransition.h"
#include "Enums/Polarity.h"
#include "Enums/ProfileInterpolationMethod.h"
#include "Enums/RidgeOperator.h"

namespace avl
{
	struct EdgeScanParams
	{
		ProfileInterpolationMethod::Type	profileInterpolation;
		float								smoothingStdDev;
		float								minMagnitude;
		EdgeTransition::Type				edgeTransition;

		explicit EdgeScanParams
		(
			ProfileInterpolationMethod::Type profileInterpolation_ = ProfileInterpolationMethod::Quadratic4,
			float smoothingStdDev_ = 0.6f,
			float minMagnitude_ = 5.0f,
			EdgeTransition::Type edgeTransition_ = EdgeTransition::BrightToDark 
		) :
			 profileInterpolation(profileInterpolation_),
			 smoothingStdDev(smoothingStdDev_),
			 minMagnitude(minMagnitude_),
			 edgeTransition(edgeTransition_) 
		{}

		ProfileInterpolationMethod::Type ProfileInterpolation() const	{ return profileInterpolation;	};
		float SmoothingStdDev() const									{ return smoothingStdDev;		};
		float MinMagnitude() const										{ return minMagnitude;			};
		EdgeTransition::Type EdgeTransition() const						{ return edgeTransition;		};

		bool operator == ( const avl::EdgeScanParams& rhs ) const
		{
			return profileInterpolation == rhs.profileInterpolation && 
			smoothingStdDev == rhs.smoothingStdDev && 
			minMagnitude == rhs.minMagnitude && 
			edgeTransition == rhs.edgeTransition;
		}

		bool operator != ( const avl::EdgeScanParams& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

	struct RidgeScanParams
	{
		ProfileInterpolationMethod::Type	profileInterpolation;
		float								smoothingStdDev;
		int									ridgeWidth;
		int									ridgeMargin;
		RidgeOperator::Type					ridgeOperator;
		float								minMagnitude;
		Polarity::Type						ridgePolarity;

		explicit RidgeScanParams
		(
			ProfileInterpolationMethod::Type profileInterpolation_ = ProfileInterpolationMethod::Quadratic4,
			float smoothingStdDev_ = 0.6f,
			int ridgeWidth_ = 5,
			int ridgeMargin_ = 2,
			RidgeOperator::Type ridgeOperator_ = RidgeOperator::Minimum,
			float minMagnitude_ = 5.0f,
			Polarity::Type ridgePolarity_ = Polarity::Bright 
		) :
			 profileInterpolation(profileInterpolation_),
			 smoothingStdDev(smoothingStdDev_),
			 ridgeWidth(ridgeWidth_),
			 ridgeMargin(ridgeMargin_),
			 ridgeOperator(ridgeOperator_),
			 minMagnitude(minMagnitude_),
			 ridgePolarity(ridgePolarity_) 
		{}

		ProfileInterpolationMethod::Type ProfileInterpolation() const	{ return profileInterpolation;	};
		float SmoothingStdDev() const									{ return smoothingStdDev;		};
		int RidgeWidth() const											{ return ridgeWidth;			};
		int RidgeMargin() const											{ return ridgeMargin;			};
		RidgeOperator::Type RidgeOperator() const						{ return ridgeOperator;			};
		float MinMagnitude() const										{ return minMagnitude;			};
		Polarity::Type RidgePolarity() const							{ return ridgePolarity;			};

		bool operator == ( const avl::RidgeScanParams& rhs ) const
		{
			return profileInterpolation == rhs.profileInterpolation && 
			smoothingStdDev == rhs.smoothingStdDev && 
			ridgeWidth == rhs.ridgeWidth && 
			ridgeMargin == rhs.ridgeMargin && 
			ridgeOperator == rhs.ridgeOperator && 
			minMagnitude == rhs.minMagnitude && 
			ridgePolarity == rhs.ridgePolarity;
		}

		bool operator != ( const avl::RidgeScanParams& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

	struct StripeScanParams
	{
		ProfileInterpolationMethod::Type	profileInterpolation;
		float								smoothingStdDev;
		float								minMagnitude;
		atl::Optional<float>				maxInnerEdgeMagnitude;
		Polarity::Type						stripePolarity;
		float								minStripeWidth;
		atl::Optional<float>				maxStripeWidth;

		explicit StripeScanParams
		(
			ProfileInterpolationMethod::Type profileInterpolation_ = ProfileInterpolationMethod::Quadratic4,
			float smoothingStdDev_ = 0.6f,
			float minMagnitude_ = 5.0f,
			atl::Optional<float> maxInnerEdgeMagnitude_ = atl::NIL,
			Polarity::Type stripePolarity_ = Polarity::Bright,
			float minStripeWidth_ = 0.0f,
			atl::Optional<float> maxStripeWidth_ = atl::NIL 
		) :
			 profileInterpolation(profileInterpolation_),
			 smoothingStdDev(smoothingStdDev_),
			 minMagnitude(minMagnitude_),
			 maxInnerEdgeMagnitude(maxInnerEdgeMagnitude_),
			 stripePolarity(stripePolarity_),
			 minStripeWidth(minStripeWidth_),
			 maxStripeWidth(maxStripeWidth_) 
		{}

		ProfileInterpolationMethod::Type ProfileInterpolation() const	{ return profileInterpolation;	};
		float SmoothingStdDev() const									{ return smoothingStdDev;		};
		float MinMagnitude() const										{ return minMagnitude;			};
		atl::Optional<float> MaxInnerEdgeMagnitude() const				{ return maxInnerEdgeMagnitude;	};
		Polarity::Type StripePolarity() const							{ return stripePolarity;		};
		float MinStripeWidth() const									{ return minStripeWidth;		};
		atl::Optional<float> MaxStripeWidth() const						{ return maxStripeWidth;		};

		bool operator == ( const avl::StripeScanParams& rhs ) const
		{
			return profileInterpolation == rhs.profileInterpolation && 
			smoothingStdDev == rhs.smoothingStdDev && 
			minMagnitude == rhs.minMagnitude && 
			maxInnerEdgeMagnitude == rhs.maxInnerEdgeMagnitude && 
			stripePolarity == rhs.stripePolarity && 
			minStripeWidth == rhs.minStripeWidth && 
			maxStripeWidth == rhs.maxStripeWidth;
		}

		bool operator != ( const avl::StripeScanParams& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

	struct LocalBlindness
	{
		atl::Optional<float>	radius;
		float					threshold;
		float					fuzziness;

		explicit LocalBlindness
		(
			atl::Optional<float> radius_ = atl::NIL,
			float threshold_ = 0.5f,
			float fuzziness_ = 0.0f 
		) :
			 radius(radius_),
			 threshold(threshold_),
			 fuzziness(fuzziness_) 
		{}

		atl::Optional<float> Radius() const	{ return radius;	};
		float Threshold() const				{ return threshold;	};
		float Fuzziness() const				{ return fuzziness;	};

		bool operator == ( const avl::LocalBlindness& rhs ) const
		{
			return radius == rhs.radius && 
			threshold == rhs.threshold && 
			fuzziness == rhs.fuzziness;
		}

		bool operator != ( const avl::LocalBlindness& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

} //namespace avl


#endif

