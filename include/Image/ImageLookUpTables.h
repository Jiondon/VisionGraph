//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_IMAGELOOKUPTABLES_H
#define AVL_IMAGELOOKUPTABLES_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Image/Image.h"
#include "PixelLut.h"
#include "Pixel.hxx"
#include <functional>

namespace avl
{


	typedef std::function<float(float)> LutOperatorType;


	/// <summary>Applies previously created Look Up transformation to provided image.</summary>
	/// <param name="inImage">Image to which LUT transformation will be applied.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inLut">LUT object, which defines transformation.</param>
	/// <param name="outImage">Transformed image.</param>
	AVL_FUNCTION void ApplyPixelLut
	(
		const avl::Image&					inImage,			
		atl::Optional<const avl::Region&>	inRoi,
		const avl::PixelLut&				inLut,				
		avl::Image&							outImage			
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates Look Up Table for power operation on image pixels.</summary>
	/// <param name="inValue">Default value: 2.0f.</param>
	AVL_FUNCTION void CreatePowerLut
	(
		float					inValue,
		const avl::PlainType::Type&	inOutputType,
		avl::PixelLut&				outLut
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates Look Up Table for logarithm operation on image pixels.</summary>
	/// <param name="inScale">Scaling factor (default: 255). Default value: atl::NIL.</param>
	/// <param name="inOffset">Offset factor.</param>
	/// <param name="inNormalizeZero">Specifies whether the output range should be rescaled to start from 0.</param>
	AVL_FUNCTION void CreateLogarithmLut
	(
		atl::Optional<const float&>		inScale,			
		float							inOffset,			
		bool								inNormalizeZero,	
		const avl::PlainType::Type&			inOutputType,
		avl::PixelLut&						outLut
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates Look Up Table for gamma correction operation on image pixels.</summary>
	/// <param name="inValue">Default value: 2.0f.</param>
	AVL_FUNCTION void CreateGammaCorrectionLut
	(
		const float				inValue,
		const avl::PlainType::Type&	inOutputType,
		avl::PixelLut&				outLut
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates Look Up Table for user provided operation on image pixels.</summary>
	AVL_FUNCTION void CreateCustomLut
	(
		const LutOperatorType& inLutFunction,
		const avl::PlainType::Type&	inOutputType,
		avl::PixelLut&				outLut
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_IMAGELOOKUPTABLES_H

