//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _TEXTUREMODEL_H
#define _TEXTUREMODEL_H

#include "ATL/AtlString.h"
#include "ATL/AtlTypes.h"
#include "ATL/Array.h"
#include "DataClassification/Gaussian.h"

namespace avl
{
	struct TextureModel
	{
		atl::Array<atl::Array<avl::Gaussian>> gaussians;
		atl::Array<atl::String>	models;
		atl::Array<double>	thresholds;
		atl::Array<double>	logThresholds;
		bool gaussian;
		int pyramid;
		int patch;
		int overlap;

		explicit TextureModel
		(
			atl::Array<atl::Array<avl::Gaussian>> gaussians_ = atl::Array<atl::Array<avl::Gaussian>>(),
			atl::Array<atl::String> models_ = atl::Array<atl::String>(),
			atl::Array<double> thresholds_ = atl::Array<double>(),
			atl::Array<double> logThresholds_ = atl::Array<double>(),
			bool gaussian_ = false,
			int pyramid_ = 5,
			int patch_ = 5,
			int overlap_ = 1
		) :
			gaussians(gaussians_),
			models(models_),
			thresholds(thresholds_),
			logThresholds(logThresholds_),
			gaussian(gaussian_),
			pyramid(pyramid_),
			patch(patch_),
			overlap(overlap_)
		{}

		atl::Array<atl::Array<avl::Gaussian>> Gaussians(void) { return gaussians; }
		atl::Array<atl::String> Models(void) const { return models; };
		atl::Array<double> Thresholds(void) const { return thresholds; };
		atl::Array<double> LogThresholds(void) const { return logThresholds; };
		bool Gaussian(void) const { return gaussian; };
		int Pyramid(void) const { return pyramid; };
		int Patch(void) const { return patch; };
		int Overlap(void) const { return overlap; }

		bool operator == (const avl::TextureModel& rhs) const
		{
			return models == rhs.models &&
				thresholds == rhs.thresholds && logThresholds == rhs.logThresholds && gaussian == rhs.gaussian
				&& pyramid == rhs.pyramid && patch == rhs.patch && overlap == rhs.overlap;
			;
		}

		bool operator != (const avl::TextureModel& rhs) const
		{
			return !(operator==(rhs));
		}

	};

} //namespace avl


#endif

