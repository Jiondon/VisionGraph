//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _GOLDENTEMPLATE2MODEL_INTENSITY_H
#define _GOLDENTEMPLATE2MODEL_INTENSITY_H

#include "ATL/Array.h"
#include "ATL/AtlString.h"
#include "Basic/Types.h"
#include "Geometry/Geometry.h"
#include "Image/Image.h"
#include "Region/Region.h"

namespace avl
{
	struct GoldenTemplate2Model_Intensity
	{
		atl::Array<int>				featureSizes;
		atl::Array<atl::String>		diagFeatureNames;
		atl::Array<Image>			brightImages;
		atl::Array<Image>			darkImages;
		atl::Array<int>				brightThresholds;
		atl::Array<int>				darkThresholds;
		Rectangle2D		croppingRectangle;
		Region			objectRoi;
		Region			erodedObjectRoi;
		atl::Array<Image>			diagMaxImages;
		atl::Array<Image>			diagMinImages;
		atl::Array<Location>		diagDarkLocations;
		atl::Array<Location>		diagBrightLocations;

		explicit GoldenTemplate2Model_Intensity
		(
			const atl::Array<int>& featureSizes_ = atl::Array<int>(),
			const atl::Array<atl::String>& diagFeatureNames_ = atl::Array<atl::String>(),
			const atl::Array<Image>& brightImages_ = atl::Array<Image>(),
			const atl::Array<Image>& darkImages_ = atl::Array<Image>(),
			const atl::Array<int>& brightThresholds_ = atl::Array<int>(),
			const atl::Array<int>& darkThresholds_ = atl::Array<int>(),
			Rectangle2D croppingRectangle_ = Rectangle2D(),
			Region objectRoi_ = Region(),
			Region erodedObjectRoi_ = Region(),
			const atl::Array<Image>& diagMaxImages_ = atl::Array<Image>(),
			const atl::Array<Image>& diagMinImages_ = atl::Array<Image>(),
			const atl::Array<Location>& diagDarkLocations_ = atl::Array<Location>(),
			const atl::Array<Location>& diagBrightLocations_ = atl::Array<Location>() 
		) :
			 featureSizes(featureSizes_),
			 diagFeatureNames(diagFeatureNames_),
			 brightImages(brightImages_),
			 darkImages(darkImages_),
			 brightThresholds(brightThresholds_),
			 darkThresholds(darkThresholds_),
			 croppingRectangle(croppingRectangle_),
			 objectRoi(objectRoi_),
			 erodedObjectRoi(erodedObjectRoi_),
			 diagMaxImages(diagMaxImages_),
			 diagMinImages(diagMinImages_),
			 diagDarkLocations(diagDarkLocations_),
			 diagBrightLocations(diagBrightLocations_) 
		{}

		const atl::Array<int>& FeatureSizes() const				{ return featureSizes;			};
		const atl::Array<atl::String>& DiagFeatureNames() const	{ return diagFeatureNames;		};
		const atl::Array<Image>& BrightImages() const			{ return brightImages;			};
		const atl::Array<Image>& DarkImages() const				{ return darkImages;			};
		const atl::Array<int>& BrightThresholds() const			{ return brightThresholds;		};
		const atl::Array<int>& DarkThresholds() const			{ return darkThresholds;		};
		Rectangle2D CroppingRectangle() const					{ return croppingRectangle;		};
		Region ObjectRoi() const								{ return objectRoi;				};
		Region ErodedObjectRoi() const							{ return erodedObjectRoi;		};
		const atl::Array<Image>& DiagMaxImages() const			{ return diagMaxImages;			};
		const atl::Array<Image>& DiagMinImages() const			{ return diagMinImages;			};
		const atl::Array<Location>& DiagDarkLocations() const	{ return diagDarkLocations;		};
		const atl::Array<Location>& DiagBrightLocations() const	{ return diagBrightLocations;	};

		bool operator == ( const avl::GoldenTemplate2Model_Intensity& rhs ) const
		{
			return featureSizes == rhs.featureSizes && 
			diagFeatureNames == rhs.diagFeatureNames && 
			brightImages == rhs.brightImages && 
			darkImages == rhs.darkImages && 
			brightThresholds == rhs.brightThresholds && 
			darkThresholds == rhs.darkThresholds && 
			croppingRectangle == rhs.croppingRectangle && 
			objectRoi == rhs.objectRoi && 
			erodedObjectRoi == rhs.erodedObjectRoi && 
			diagMaxImages == rhs.diagMaxImages && 
			diagMinImages == rhs.diagMinImages && 
			diagDarkLocations == rhs.diagDarkLocations && 
			diagBrightLocations == rhs.diagBrightLocations;
		}

		bool operator != ( const avl::GoldenTemplate2Model_Intensity& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

} //namespace avl


#endif

