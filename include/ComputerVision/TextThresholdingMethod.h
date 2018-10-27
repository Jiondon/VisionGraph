//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _TEXTTHRESHOLDINGMETHOD_H
#define _TEXTTHRESHOLDINGMETHOD_H

#include "ATL/AtlTypes.h"
#include "ATL/Optional.h"
#include "Enums/OpticalCharacterRecognitionEnums.h"
#include "Enums/ThresholdMethod.h"

namespace avl
{
	struct TextThresholdingMethod
	{
		ThresholdingAlgorithm::Type		algorithm;
		atl::Optional<float>			minValue;
		atl::Optional<float>			maxValue;
		float							hysteresis;
		float							hysteresisDynamic;
		float							hysteresisAutomatic;
		int								radius;
		atl::Optional<float>			minDynamic;
		atl::Optional<float>			maxDynamic;
		ThresholdSelectionMethod::Type	automaticMethod;
		bool							blackText;
		float							smoothing;
		float							shearing;
		int								dilation;

		explicit TextThresholdingMethod
		(
			ThresholdingAlgorithm::Type algorithm_ = ThresholdingAlgorithm::Simple,
			atl::Optional<float> minValue_ = 128.0f,
			atl::Optional<float> maxValue_ = atl::NIL,
			float hysteresis_ = 0.0f,
			float hysteresisDynamic_ = 0.0f,
			float hysteresisAutomatic_ = 0.0f,
			int radius_ = 5,
			atl::Optional<float> minDynamic_ = 128.0f,
			atl::Optional<float> maxDynamic_ = atl::NIL,
			ThresholdSelectionMethod::Type automaticMethod_ = ThresholdSelectionMethod::ClusteringKittler,
			bool blackText_ = false,
			float smoothing_ = 0.0f,
			float shearing_ = 0.0f,
			int dilation_ = 0 
		) :
			 algorithm(algorithm_),
			 minValue(minValue_),
			 maxValue(maxValue_),
			 hysteresis(hysteresis_),
			 hysteresisDynamic(hysteresisDynamic_),
			 hysteresisAutomatic(hysteresisAutomatic_),
			 radius(radius_),
			 minDynamic(minDynamic_),
			 maxDynamic(maxDynamic_),
			 automaticMethod(automaticMethod_),
			 blackText(blackText_),
			 smoothing(smoothing_),
			 shearing(shearing_),
			 dilation(dilation_) 
		{}

		ThresholdingAlgorithm::Type Algorithm() const			{ return algorithm;				};
		atl::Optional<float> MinValue() const					{ return minValue;				};
		atl::Optional<float> MaxValue() const					{ return maxValue;				};
		float Hysteresis() const								{ return hysteresis;			};
		float HysteresisDynamic() const							{ return hysteresisDynamic;		};
		float HysteresisAutomatic() const						{ return hysteresisAutomatic;	};
		int Radius() const										{ return radius;				};
		atl::Optional<float> MinDynamic() const					{ return minDynamic;			};
		atl::Optional<float> MaxDynamic() const					{ return maxDynamic;			};
		ThresholdSelectionMethod::Type AutomaticMethod() const	{ return automaticMethod;		};
		bool BlackText() const									{ return blackText;				};
		float Smoothing() const									{ return smoothing;				};
		float Shearing() const									{ return shearing;				};
		int Dilation() const									{ return dilation;				};

		bool operator == ( const avl::TextThresholdingMethod& rhs ) const
		{
			return algorithm == rhs.algorithm && 
			minValue == rhs.minValue && 
			maxValue == rhs.maxValue && 
			hysteresis == rhs.hysteresis && 
			hysteresisDynamic == rhs.hysteresisDynamic && 
			hysteresisAutomatic == rhs.hysteresisAutomatic && 
			radius == rhs.radius && 
			minDynamic == rhs.minDynamic && 
			maxDynamic == rhs.maxDynamic && 
			automaticMethod == rhs.automaticMethod && 
			blackText == rhs.blackText && 
			smoothing == rhs.smoothing && 
			shearing == rhs.shearing && 
			dilation == rhs.dilation;
		}

		bool operator != ( const avl::TextThresholdingMethod& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

} //namespace avl


#endif

