//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _TEXTSEGMENTATIONMETHOD_H
#define _TEXTSEGMENTATIONMETHOD_H

#include "ATL/AtlTypes.h"
#include "ATL/Optional.h"
#include "Basic/Types.h"
#include "Enums/OpticalCharacterRecognitionEnums.h"

namespace avl
{
	struct TextSegmentationMethod
	{
		SegmentationAlgorithm::Type	algorithm;
		int							minBlobSize;
		atl::Optional<int>			maxBlobSize;
		int							characterSize;
		atl::Optional<float>		smoothProjection;
		float						maxDistance;
		float						distanceBalance;
		CharacterSortingOrder::Type	sorting;
		atl::Optional<Size>			minimalSize;
		atl::Optional<Size>			maximalSize;

		explicit TextSegmentationMethod
		(
			SegmentationAlgorithm::Type algorithm_ = SegmentationAlgorithm::SimpleBlobs,
			int minBlobSize_ = 0,
			atl::Optional<int> maxBlobSize_ = atl::NIL,
			int characterSize_ = 15,
			atl::Optional<float> smoothProjection_ = atl::NIL,
			float maxDistance_ = 5.0f,
			float distanceBalance_ = 0.0f,
			CharacterSortingOrder::Type sorting_ = CharacterSortingOrder::LeftToRight,
			atl::Optional<Size> minimalSize_ = atl::NIL,
			atl::Optional<Size> maximalSize_ = atl::NIL 
		) :
			 algorithm(algorithm_),
			 minBlobSize(minBlobSize_),
			 maxBlobSize(maxBlobSize_),
			 characterSize(characterSize_),
			 smoothProjection(smoothProjection_),
			 maxDistance(maxDistance_),
			 distanceBalance(distanceBalance_),
			 sorting(sorting_),
			 minimalSize(minimalSize_),
			 maximalSize(maximalSize_) 
		{}

		SegmentationAlgorithm::Type Algorithm() const	{ return algorithm;			};
		int MinBlobSize() const							{ return minBlobSize;		};
		atl::Optional<int> MaxBlobSize() const			{ return maxBlobSize;		};
		int CharacterSize() const						{ return characterSize;		};
		atl::Optional<float> SmoothProjection() const	{ return smoothProjection;	};
		float MaxDistance() const						{ return maxDistance;		};
		float DistanceBalance() const					{ return distanceBalance;	};
		CharacterSortingOrder::Type Sorting() const		{ return sorting;			};
		atl::Optional<Size> MinimalSize() const			{ return minimalSize;		};
		atl::Optional<Size> MaximalSize() const			{ return maximalSize;		};

		bool operator == ( const avl::TextSegmentationMethod& rhs ) const
		{
			return algorithm == rhs.algorithm && 
			minBlobSize == rhs.minBlobSize && 
			maxBlobSize == rhs.maxBlobSize && 
			characterSize == rhs.characterSize && 
			smoothProjection == rhs.smoothProjection && 
			maxDistance == rhs.maxDistance && 
			distanceBalance == rhs.distanceBalance && 
			sorting == rhs.sorting && 
			minimalSize == rhs.minimalSize && 
			maximalSize == rhs.maximalSize;
		}

		bool operator != ( const avl::TextSegmentationMethod& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

} //namespace avl


#endif

