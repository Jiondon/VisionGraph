//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_FOURIERANALYSIS_H
#define AVL_FOURIERANALYSIS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Image/Image.h"

namespace avl
{


	namespace FrequencyDomainOrigin 
	{ 
		enum Type
		{
			ImageCenter, 
			Standard 
		};
	}


	/// <summary>Transforms an image into frequency domain using Fourier transformation</summary>
	AVL_FUNCTION void FourierTransform
	(
		const avl::Image&	inSpatialDomainImage,
		avl::Image&			outFrequencyDomainImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Transforms an image in frequency domain back to spatial domain using inverse Fourier transformation</summary>
	AVL_FUNCTION void InverseFourierTransform
	(
		const avl::Image&	inFrequencyDomainImage,
		avl::Image&			outSpatialDomainImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the modulus of each frequency domain image pixel.</summary>
	AVL_FUNCTION void FrequencyDomain_ModulusImage
	(
		const avl::Image&	inFrequencyDomainImage,
		avl::Image&			outModulusImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes the phase of each frequency domain image pixel.</summary>
	AVL_FUNCTION void FrequencyDomain_PhaseImage
	(
		const avl::Image&	inFrequencyDomainImage,
		avl::Image&			outPhaseImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Filters the frequencies in a frequency domain image suppressing the elements of too low or too high frequency.</summary>
	/// <param name="inFrequencyDomainImage">Input image in frequency domain.</param>
	/// <param name="inMinFrequency">Minimum frequency that will be kept. Default value: atl::NIL.</param>
	/// <param name="inMaxFrequency">Maximum frequency that will be kept. Default value: atl::NIL.</param>
	/// <param name="outFrequencyDomainImage">Filtered image in frequency domain.</param>
	AVL_FUNCTION void FrequencyDomain_FilterFrequencies
	(
		const avl::Image&	inFrequencyDomainImage, 
		const atl::Optional<float>& inMinFrequency, 
		const atl::Optional<float>& inMaxFrequency, 
		avl::Image&			outFrequencyDomainImage 
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_FOURIERANALYSIS_H

