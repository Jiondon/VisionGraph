//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _EXTRACTBLOBSSTRUCTS_H
#define _EXTRACTBLOBSSTRUCTS_H

#include "ATL/AtlTypes.h"
#include "ATL/Optional.h"
#include "Basic/Types.h"
#include "Enums/RegionConnectivity.h"

namespace avl
{
	struct IntensityThresholdParams
	{
		atl::Optional<float>	minIntensity;
		atl::Optional<float>	maxIntensity;
		float					hysteresis;

		explicit IntensityThresholdParams
		(
			atl::Optional<float> minIntensity_ = 128,
			atl::Optional<float> maxIntensity_ = atl::NIL,
			float hysteresis_ = 0.0f 
		) :
			 minIntensity(minIntensity_),
			 maxIntensity(maxIntensity_),
			 hysteresis(hysteresis_) 
		{}

		atl::Optional<float> MinIntensity() const	{ return minIntensity;	};
		atl::Optional<float> MaxIntensity() const	{ return maxIntensity;	};
		float Hysteresis() const					{ return hysteresis;	};

		bool operator == ( const avl::IntensityThresholdParams& rhs ) const
		{
			return minIntensity == rhs.minIntensity && 
			maxIntensity == rhs.maxIntensity && 
			hysteresis == rhs.hysteresis;
		}

		bool operator != ( const avl::IntensityThresholdParams& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

	struct DynamicThresholdParams
	{
		int						radius;
		atl::Optional<float>	minRelativeValue;
		atl::Optional<float>	maxRelativeValue;
		float					hysteresis;

		explicit DynamicThresholdParams
		(
			int radius_ = 5,
			atl::Optional<float> minRelativeValue_ = 5,
			atl::Optional<float> maxRelativeValue_ = atl::NIL,
			float hysteresis_ = 0.0f 
		) :
			 radius(radius_),
			 minRelativeValue(minRelativeValue_),
			 maxRelativeValue(maxRelativeValue_),
			 hysteresis(hysteresis_) 
		{}

		int Radius() const								{ return radius;			};
		atl::Optional<float> MinRelativeValue() const	{ return minRelativeValue;	};
		atl::Optional<float> MaxRelativeValue() const	{ return maxRelativeValue;	};
		float Hysteresis() const						{ return hysteresis;		};

		bool operator == ( const avl::DynamicThresholdParams& rhs ) const
		{
			return radius == rhs.radius && 
			minRelativeValue == rhs.minRelativeValue && 
			maxRelativeValue == rhs.maxRelativeValue && 
			hysteresis == rhs.hysteresis;
		}

		bool operator != ( const avl::DynamicThresholdParams& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

	struct ColorThresholdParams
	{
		Pixel	rgbColor;
		float	chromaAmount;
		float	maxDifference;
		float	hysteresis;

		explicit ColorThresholdParams
		(
			Pixel rgbColor_ = Pixel(),
			float chromaAmount_ = 0.7f,
			float maxDifference_ = 5,
			float hysteresis_ = 0.0f 
		) :
			 rgbColor(rgbColor_),
			 chromaAmount(chromaAmount_),
			 maxDifference(maxDifference_),
			 hysteresis(hysteresis_) 
		{}

		Pixel RgbColor() const		{ return rgbColor;		};
		float ChromaAmount() const	{ return chromaAmount;	};
		float MaxDifference() const	{ return maxDifference;	};
		float Hysteresis() const	{ return hysteresis;	};

		bool operator == ( const avl::ColorThresholdParams& rhs ) const
		{
			return rgbColor == rhs.rgbColor && 
			chromaAmount == rhs.chromaAmount && 
			maxDifference == rhs.maxDifference && 
			hysteresis == rhs.hysteresis;
		}

		bool operator != ( const avl::ColorThresholdParams& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

	struct BlobSplittingParams
	{
		RegionConnectivity::Type	connectivity;
		int							minArea;
		atl::Optional<int>			maxArea;
		bool						removeBoundaryBlobs;

		explicit BlobSplittingParams
		(
			RegionConnectivity::Type connectivity_ = RegionConnectivity::EightDirections,
			int minArea_ = 0,
			atl::Optional<int> maxArea_ = atl::NIL,
			bool removeBoundaryBlobs_ = false 
		) :
			 connectivity(connectivity_),
			 minArea(minArea_),
			 maxArea(maxArea_),
			 removeBoundaryBlobs(removeBoundaryBlobs_) 
		{}

		RegionConnectivity::Type Connectivity() const	{ return connectivity;			};
		int MinArea() const								{ return minArea;				};
		atl::Optional<int> MaxArea() const				{ return maxArea;				};
		bool RemoveBoundaryBlobs() const				{ return removeBoundaryBlobs;	};

		bool operator == ( const avl::BlobSplittingParams& rhs ) const
		{
			return connectivity == rhs.connectivity && 
			minArea == rhs.minArea && 
			maxArea == rhs.maxArea && 
			removeBoundaryBlobs == rhs.removeBoundaryBlobs;
		}

		bool operator != ( const avl::BlobSplittingParams& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

} //namespace avl


#endif

