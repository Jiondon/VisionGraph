//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_IMAGECOLORSPACES_H
#define AVL_IMAGECOLORSPACES_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Image/Image.h"

namespace avl
{


	namespace BayerType
	{
		enum Type
		{
			GR,
			RG,
			GB,
			BG
		};
	}


	/// <summary>Converts color space from Red-Green-Blue to Hue-Saturation-Value.</summary>
	AVL_FUNCTION void RgbToHsv
	(
		const avl::Image&	inRgbImage,
		avl::Image&			outHsvImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts color space from Hue-Saturation-Value to Red-Green-Blue.</summary>
	AVL_FUNCTION void HsvToRgb
	(
		const avl::Image&	inHsvImage,
		avl::Image&			outRgbImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a YUV-encoded image into RGB color space.</summary>
	AVL_FUNCTION void Yuv442ToRgb
	(
		const avl::Image&	inYuvImage,
		avl::Image&			outRgbImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a Bayer-encoded color image into RGB color space.</summary>
	AVL_FUNCTION void BayerToRgb
	(
		const avl::Image&	inMonoImage,
		avl::BayerType::Type	inBayerType,
		avl::Image&			outRgbImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a RGB color image into Bayer-encoded color image.</summary>
	AVL_FUNCTION void RgbToBayer
	(
		const avl::Image&		inRgbImage,
		avl::BayerType::Type	inBayerType,
		avl::Image&				outBayerImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts color space from Hue-Saturation-Luminance to Red-Green-Blue.</summary>
	AVL_FUNCTION void HslToRgb
	(
		const avl::Image&	inHslImage,
		avl::Image&			outRgbImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts color space from Red-Green-Blue to Hue-Saturation-Luminance.</summary>
	AVL_FUNCTION void RgbToHsl
	(
		const avl::Image&	inRgbImage,
		avl::Image&			outHslImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts color space from Red-Green-Blue to XYZ.</summary>
	AVL_FUNCTION void RgbToXyz
	(
		const avl::Image&	inRgbImage,
		avl::Image&			outXyzImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts color space from XYZ to Red-Green-Blue.</summary>
	AVL_FUNCTION void XyzToRgb
	(
		const avl::Image&	inXyzImage,
		avl::Image&			outRgbImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts color space from Red-Green-Blue into YUV.</summary>
	AVL_FUNCTION void RgbToYuv
	(
		const avl::Image&	inRgbImage,
		avl::Image&			outYuvImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts color space from YUV into Red-Green-Blue.</summary>
	AVL_FUNCTION void YuvToRgb
	(
		const avl::Image&	inYuvImage,
		avl::Image&			outRgbImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts color space from Hue-Saturation-Intensity into Red-Green-Blue.</summary>
	AVL_FUNCTION void HsiToRgb
	(
		const avl::Image&	inHsiImage,
		avl::Image&			outRgbImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts color space from Red-Green-Blue into Hue-Saturation-Intensity.</summary>
	AVL_FUNCTION void RgbToHsi
	(
		const avl::Image&	inRgbImage,
		avl::Image&			outHsiImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts color space from Red-Green-Blue into Cyan-Magenta-Yellow-Key.</summary>
	AVL_FUNCTION void RgbToCmyk
	(
		const avl::Image&	inRgbImage,
		avl::Image&			outCmykImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts color space from Cyan-Magenta-Yellow-Key into Red-Green-Blue.</summary>
	AVL_FUNCTION void CmykToRgb
	(
		const avl::Image&	inCmykImage,
		avl::Image&			outRgbImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts color space from Red-Green-Blue into pseudointensitY-Orange-Green.</summary>
	AVL_FUNCTION void RgbToYCoCg
	(
		const avl::Image&	inRgbImage,
		avl::Image&			outYCoCgImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts color space from pseudointensitY-Orange-Green into Red-Green-Blue.</summary>
	AVL_FUNCTION void YCoCgToRgb
	(
		const avl::Image&	inYCoCgImage,
		avl::Image&			outRgbImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a RGB888 image into a RGB565 one.</summary>
	AVL_FUNCTION void Rgb888ToRgb565
	(
		const avl::Image&	inRgb888Image,
		avl::Image&			outRgb565Image
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a RGB565 image into a RGB888 one.</summary>
	AVL_FUNCTION void Rgb565ToRgb888
	(
		const avl::Image&	inRgb565Image,
		avl::Image&			outRgb888Image
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a RGB888 image into a RGB555 one.</summary>
	AVL_FUNCTION void Rgb888ToRgb555
	(
		const avl::Image&	inRgb888Image,
		avl::Image&			outRgb555Image
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts a RGB555 image into a RGB888 one.</summary>
	AVL_FUNCTION void Rgb555ToRgb888
	(
		const avl::Image&	inRgb555Image,
		avl::Image&			outRgb888Image
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts color space from Red-Green-Blue to L*a*b*.</summary>
	AVL_FUNCTION void RgbToLab
	(
		const avl::Image&	inRgbImage,
		avl::Image&			outLabImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts color space from L*a*b* to Red-Green-Blue.</summary>
	AVL_FUNCTION void LabToRgb
	(
		const avl::Image&	inLabImage,
		avl::Image&			outRgbImage
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_IMAGECOLORSPACES_H

