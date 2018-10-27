//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_IMAGELOCALTRANSFORMS_H
#define AVL_IMAGELOCALTRANSFORMS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "AVLCommon/MatrixTypes.h"
#include "Basic/Types.h"
#include "Image/Image.h"
#include "Enums/AngleRange.h"
#include "Enums/KernelShape.h"
#include "Profile/Profile.h"
#include "Enums/ImageLocalTransformsEnums.h"

namespace avl
{


	/// <summary>Replaces each pixel with the maximum of pixels within a kernel.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of outImage pixels to be computed. Default value: atl::NIL.</param>
	/// <param name="inSourceRoi">Range of inImage pixels to be considered in computations. Default value: atl::NIL.</param>
	/// <param name="inBorderColor">Color of the imaginary pixels outside the image boundaries. Default value: atl::NIL.</param>
	/// <param name="inKernel">Kernel shape.</param>
	/// <param name="inRadiusX">Nearly half of the kernel's width (2*R+1). Default value: 1.</param>
	/// <param name="inRadiusY">Nearly half of the kernel's height (2*R+1), or same as inRadiusX. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	/// <param name="diagKernel">Kernel shape.</param>
	AVL_FUNCTION void DilateImage
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,			
		atl::Optional<const avl::Region&>	inSourceRoi,	
		atl::Optional<avl::Pixel>			inBorderColor,	
		avl::KernelShape::Type				inKernel,		
		int									inRadiusX,		
		atl::Optional<int>					inRadiusY,		
		avl::Image&							outImage,
		avl::Region&						diagKernel = atl::Dummy<avl::Region>()		
	)
	THROW_AVL_ERRORS;

	/// <summary>Replaces each pixel with the minimum of pixels within a kernel.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of outImage pixels to be computed. Default value: atl::NIL.</param>
	/// <param name="inSourceRoi">Range of inImage pixels to be considered in computations. Default value: atl::NIL.</param>
	/// <param name="inBorderColor">Color of the imaginary pixels outside the image boundaries. Default value: atl::NIL.</param>
	/// <param name="inKernel">Kernel shape.</param>
	/// <param name="inRadiusX">Nearly half of the kernel's width (2*R+1). Default value: 1.</param>
	/// <param name="inRadiusY">Nearly half of the kernel's height (2*R+1), or same as inRadiusX. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	/// <param name="diagKernel">Kernel shape.</param>
	AVL_FUNCTION void ErodeImage
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,			
		atl::Optional<const avl::Region&>	inSourceRoi,	
		atl::Optional<avl::Pixel>			inBorderColor,	
		avl::KernelShape::Type				inKernel,		
		int									inRadiusX,		
		atl::Optional<int>					inRadiusY,		
		avl::Image&							outImage,
		avl::Region&						diagKernel = atl::Dummy<avl::Region>()		
	)
	THROW_AVL_ERRORS;

	/// <summary>Removes small bright structures from an image (or fills in dark ones) by applying consecutive erosion and dilation.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of outImage pixels to be computed. Default value: atl::NIL.</param>
	/// <param name="inSourceRoi">Range of inImage pixels to be considered in computations. Default value: atl::NIL.</param>
	/// <param name="inBorderColor">Color of the imaginary pixels outside the image boundaries. Default value: atl::NIL.</param>
	/// <param name="inKernel">Kernel shape.</param>
	/// <param name="inRadiusX">Nearly half of the kernel's width (2*R+1). Default value: 1.</param>
	/// <param name="inRadiusY">Nearly half of the kernel's height (2*R+1), or same as inRadiusX. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	/// <param name="diagKernel">Kernel shape.</param>
	AVL_FUNCTION void OpenImage
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,			
		atl::Optional<const avl::Region&>	inSourceRoi,	
		atl::Optional<avl::Pixel>			inBorderColor,	
		avl::KernelShape::Type				inKernel,		
		int									inRadiusX,		
		atl::Optional<int>					inRadiusY,		
		avl::Image&							outImage,
		avl::Region&						diagKernel = atl::Dummy<avl::Region>()		
	)
	THROW_AVL_ERRORS;

	/// <summary>Removes small dark structures from an image (or fills in bright ones) by applying consecutive dilation and erosion.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of outImage pixels to be computed. Default value: atl::NIL.</param>
	/// <param name="inSourceRoi">Range of inImage pixels to be considered in computations. Default value: atl::NIL.</param>
	/// <param name="inBorderColor">Color of the imaginary pixels outside the image boundaries. Default value: atl::NIL.</param>
	/// <param name="inKernel">Selects kernel shape.</param>
	/// <param name="inRadiusX">Nearly half of the kernel's width (2*R+1). Default value: 1.</param>
	/// <param name="inRadiusY">Nearly half of the kernel's height. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	/// <param name="diagKernel">Kernel shape.</param>
	AVL_FUNCTION void CloseImage
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,			
		atl::Optional<const avl::Region&>	inSourceRoi,	
		atl::Optional<avl::Pixel>			inBorderColor,	
		avl::KernelShape::Type				inKernel,		
		int									inRadiusX,		
		atl::Optional<int>					inRadiusY,		
		avl::Image&							outImage,
		avl::Region&						diagKernel = atl::Dummy<avl::Region>()		
	)
	THROW_AVL_ERRORS;

	/// <summary>Smooths an image by averaging pixels within a rectangular kernel.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of outImage pixels to be computed. Default value: atl::NIL.</param>
	/// <param name="inSourceRoi">Range of inImage pixels to be read. Default value: atl::NIL.</param>
	/// <param name="inBorderColor">Color of the imaginary pixels outside the image boundaries. Default value: atl::NIL.</param>
	/// <param name="inKernel">Kernel shape.</param>
	/// <param name="inRadiusX">Nearly half of the kernel's width (2*R+1). Default value: 1.</param>
	/// <param name="inRadiusY">Nearly half of the kernel's height (2*R+1), or same as inRadiusX. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void SmoothImage_Mean
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,			
		atl::Optional<const avl::Region&>	inSourceRoi,	
		atl::Optional<avl::Pixel>			inBorderColor,	
		avl::KernelShape::Type				inKernel,		
		int									inRadiusX,		
		atl::Optional<int>					inRadiusY,		
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Replaces each pixel with the median of pixels within a kernel.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of outImage pixels being written. Default value: atl::NIL.</param>
	/// <param name="inSourceRoi">Range of inImage pixels being read. Default value: atl::NIL.</param>
	/// <param name="inRadius">Nearly half of the kernel's size (2*R+1). Default value: 1.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void SmoothImage_Median
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,			
		atl::Optional<const avl::Region&>	inSourceRoi,	
		avl::SmoothImageMedianKernel::Type	inKernel,
		int									inRadius,		
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes a convolution of the input image with a user-specified mask.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of outImage pixels to be computed. Default value: atl::NIL.</param>
	/// <param name="inMask">Image convolution kernel.</param>
	/// <param name="inNormalizeMaskValues">Normalize sum of weights in mask to one. Default value: False.</param>
	/// <param name="inMaskOrigin">Relative location of point to its mask. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void ConvolveImage
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,					
		const avl::Matrix&					inMask,					
		bool								inNormalizeMaskValues,	
		atl::Optional<const avl::Location&>	inMaskOrigin,			
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Smooths an image by averaging pixels within a small rectangular kernel.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of outImage pixels to be computed. Default value: atl::NIL.</param>
	/// <param name="inKernel">Selects a predefined kernel.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void SmoothImage_Mean_Mask
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,		
		avl::MeanKernel::Type				inKernel,	
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Replaces each pixel with the maximum of pixels within a small rectangular kernel.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of outImage pixels to be computed. Default value: atl::NIL.</param>
	/// <param name="inKernel">Selects a predefined kernel.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DilateImage_Mask
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,			
		avl::MorphologyKernel::Type			inKernel,		
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Replaces each pixel with the minimum of pixels within a small rectangular kernel.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of outImage pixels to be computed. Default value: atl::NIL.</param>
	/// <param name="inKernel">Selects a predefined kernel.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void ErodeImage_Mask
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,			
		avl::MorphologyKernel::Type			inKernel,		
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Replaces each pixel with the median of pixels within a 3x3 rectangular kernel (faster).</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of outImage pixels to be computed. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void SmoothImage_Median_Mask
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,		
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Smooths an image by averaging pixels within an arbitrary kernel.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of outImage pixels to be computed. Default value: atl::NIL.</param>
	/// <param name="inSourceRoi">Range of inImage pixels to be considered in computations. Default value: atl::NIL.</param>
	/// <param name="inBorderColor">Color of the imaginary pixels outside the image boundaries. Default value: atl::NIL.</param>
	/// <param name="inKernel">Kernel shape (any).</param>
	/// <param name="inKernelAnchor">A location within inKernel, defining its center. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void SmoothImage_Mean_AnyKernel
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,			
		atl::Optional<const avl::Region&>	inSourceRoi,	
		atl::Optional<avl::Pixel>			inBorderColor,	
		const avl::Region&					inKernel,		
		atl::Optional<const avl::Location&>	inKernelAnchor,	
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Replaces each pixel with the maximum of pixels within an arbitrary kernel.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of outImage pixels to be computed. Default value: atl::NIL.</param>
	/// <param name="inSourceRoi">Range of inImage pixels to be considered in computations. Default value: atl::NIL.</param>
	/// <param name="inBorderColor">Color of the imaginary pixels outside the image boundaries. Default value: atl::NIL.</param>
	/// <param name="inKernel">Kernel shape (any).</param>
	/// <param name="inKernelAnchor">A location within inKernel, defining its center. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DilateImage_AnyKernel
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,			
		atl::Optional<const avl::Region&>	inSourceRoi,	
		atl::Optional<avl::Pixel>			inBorderColor,	
		const avl::Region&					inKernel,		
		atl::Optional<const avl::Location&>	inKernelAnchor,	
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Replaces each pixel with the minimum of pixels within an arbitrary kernel.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of outImage pixels to be computed. Default value: atl::NIL.</param>
	/// <param name="inSourceRoi">Range of inImage pixels to be considered in computations. Default value: atl::NIL.</param>
	/// <param name="inBorderColor">Color of the imaginary pixels outside the image boundaries. Default value: atl::NIL.</param>
	/// <param name="inKernel">Kernel shape (any).</param>
	/// <param name="inKernelAnchor">A location within inKernel, defining its center. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void ErodeImage_AnyKernel
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,			
		atl::Optional<const avl::Region&>	inSourceRoi,	
		atl::Optional<avl::Pixel>			inBorderColor,	
		const avl::Region&					inKernel,		
		atl::Optional<const avl::Location&>	inKernelAnchor,	
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes a gradient image with a Sobel or Prewitt operator.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of outGradientImage pixels to be computed. Default value: atl::NIL.</param>
	/// <param name="inOperator">Defines how the gradient is computed.</param>
	/// <param name="inScale">Scales the resulting gradients. Default value: 1.</param>
	/// <param name="outGradientImage">Gradients of the image.</param>
	/// <param name="diagGradientDirections">Gradient directions presented in a human readable format.</param>
	AVL_FUNCTION void GradientImage_Mask
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,					
		avl::GradientMaskOperator::Type		inOperator,				
		const int							inScale,				
		avl::Image&							outGradientImage,		
		avl::Image&							diagGradientDirections = atl::Dummy<avl::Image>()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes a gradient image with smoothing operator of any size. The output pixels are signed.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of outGradientImage pixels to be computed. Default value: atl::NIL.</param>
	/// <param name="inOperator">Defines how the gradient is computed.</param>
	/// <param name="inStdDevX">Horizontal smoothing standard deviation. Default value: 2.0f.</param>
	/// <param name="inStdDevY">Vertical smoothing standard deviation. Default value: atl::NIL.</param>
	/// <param name="outGradientImage">Gradients of the image.</param>
	/// <param name="diagGradientDirections">Gradient directions presented in a human readable format.</param>
	AVL_FUNCTION void GradientImage
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,					
		avl::GradientOperator::Type			inOperator,				
		const float						inStdDevX,				
		atl::Optional<float>			inStdDevY,				
		avl::Image&							outGradientImage,		
		avl::Image&							diagGradientDirections = atl::Dummy<avl::Image>()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Measures the strength of gradient at each pixel location with Sobel or Prewitt operator.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of output pixels to be computed. Default value: atl::NIL.</param>
	/// <param name="inOperator">Defines how the gradient is computed.</param>
	/// <param name="inMeasure">Defines how the gradient magnitude is computed. Default value: Hypot.</param>
	/// <param name="inScale">Scales the resulting gradient magnitudes. Default value: 1.</param>
	/// <param name="outValueImage">Gradient magnitudes of the image.</param>
	AVL_FUNCTION void GradientMagnitudeImage
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,			
		avl::GradientMaskOperator::Type		inOperator,		
		avl::MagnitudeMeasure::Type			inMeasure,		
		const int							inScale,		
		avl::Image&							outValueImage	
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes an image of gradient directions mapped to the range from 1 to 255. Zero means "no edge".</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of output pixels to be computed. Default value: atl::NIL.</param>
	/// <param name="inOperator">Defines how the gradient is computed.</param>
	/// <param name="inEdgeThreshold">Minimum edge magnitude (other pixels will be set to 0). Default value: 10.0f.</param>
	AVL_FUNCTION void GradientDirAndPresenceImage
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,				
		avl::GradientMaskOperator::Type		inOperator,			
		float							inEdgeThreshold,	
		avl::Image&							outDirectionsImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Smooths an image using a gaussian kernel.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of output pixels to be computed. Default value: atl::NIL.</param>
	/// <param name="inStdDevX">Horizontal smoothing standard deviation. Default value: 1.0f.</param>
	/// <param name="inStdDevY">Vertical smoothing standard deviation. Default value: atl::NIL.</param>
	/// <param name="inKernelRelativeSize">A multiple of the standard deviation determining the size of the kernel. Default value: 2.0f.</param>
	/// <param name="outImage">Output image.</param>
	/// <param name="diagKernelRadiusX">Horizontal radius of Gaussian kernel being used.</param>
	/// <param name="diagKernelRadiusY">Vertical radius of Gaussian kernel being used.</param>
	AVL_FUNCTION void SmoothImage_Gauss
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,					
		float							inStdDevX,				
		atl::Optional<float>			inStdDevY,				
		const float						inKernelRelativeSize,	
		avl::Image&							outImage,
		int&								diagKernelRadiusX = atl::Dummy<int>(),		
		int&								diagKernelRadiusY = atl::Dummy<int>()		
	)
	THROW_AVL_ERRORS;

	/// <summary>Smooths an image using a predefined gaussian kernel.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of outImage pixels to be computed. Default value: atl::NIL.</param>
	/// <param name="inKernel">Predefined Gauss kernel.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void SmoothImage_Gauss_Mask
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,		
		avl::GaussKernel::Type				inKernel,	
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Smooths an image using Deriche filter.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of output pixels to be computed. Default value: atl::NIL.</param>
	/// <param name="inAlphaX">Horizontal coefficient. Default value: 1.0f.</param>
	/// <param name="inAlphaY">Vertical coefficient. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void SmoothImage_Deriche
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,		
		const float						inAlphaX,	
		atl::Optional<float>			inAlphaY,	
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Applies difference of Gaussians on an image, i.e. computes difference of two Gaussian smoothed images.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of output pixels to be computed. Default value: atl::NIL.</param>
	/// <param name="inStdDev">Smoothing standard deviation for the smaller kernel. Default value: 3.0f.</param>
	/// <param name="inStdDevRatio">Defines how many times larger is the second kernel. Default value: 1.6f.</param>
	/// <param name="inKernelRelativeSize">A multiple of the standard deviation determining the size of the kernel. Default value: 3.0f.</param>
	/// <param name="inScale">Output image scaling factor. Default value: 1.0f.</param>
	/// <param name="outImage">Output image.</param>
	/// <param name="diagKernelShape">Middle row of the kernel being used.</param>
	AVL_FUNCTION void DifferenceOfGaussians
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,					
		float							inStdDev,				
		float							inStdDevRatio,			
		float							inKernelRelativeSize,	
		float							inScale,				
		avl::Image&							outImage,
		avl::Profile&						diagKernelShape = atl::Dummy<avl::Profile>()			
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes illumination invariant magnitude image</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inNoiseLevel">Default value: 4.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void GradientMagnitudeImage_Adaptive
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		int									inNoiseLevel,
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes a gradient image using selected operator.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	AVL_FUNCTION void GradientImage_Mask_Deprecated
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,
		avl::GradientMaskOperator::Type		inOperator,
		avl::Image&							outGradientImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Dilates an image across the direction of associated gradients</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inMinMagnitude">Minimum length of the gradient. Default value: 5.0f.</param>
	/// <param name="inMinValue">Minimum value of the pixel of the input image. Default value: 0.0f.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DilateImage_Directional
	(
		const avl::Image&	inImage,
		const avl::Image&	inGradientImage,
		float			inMinMagnitude,		
		float			inMinValue,			
		avl::Image&			outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Replaces each pixel with the average of maximum and minimum calculated within a kernel.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of outImage pixels to be computed. Default value: atl::NIL.</param>
	/// <param name="inSourceRoi">Range of inImage pixels to be read. Default value: atl::NIL.</param>
	/// <param name="inBorderColor">Color of the imaginary pixels outside the image boundaries. Default value: atl::NIL.</param>
	/// <param name="inKernel">Kernel shape.</param>
	/// <param name="inRadiusX">Nearly half of the kernel's width (2*R+1). Default value: 1.</param>
	/// <param name="inRadiusY">Nearly half of the kernel's height (2*R+1), or same as inRadiusX. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void SmoothImage_Middle
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,			
		atl::Optional<const avl::Region&>	inSourceRoi,	
		atl::Optional<avl::Pixel>			inBorderColor,	
		avl::KernelShape::Type				inKernel,		
		int									inRadiusX,		
		atl::Optional<int>					inRadiusY,		
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Calculates dilation and erosion simultaneously for faster execution.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of outImage pixels to be computed. Default value: atl::NIL.</param>
	/// <param name="inSourceRoi">Range of inImage pixels to be read. Default value: atl::NIL.</param>
	/// <param name="inBorderColor">Color of the imaginary pixels outside the image boundaries. Default value: atl::NIL.</param>
	/// <param name="inKernel">Kernel shape.</param>
	/// <param name="inRadiusX">Nearly half of the kernel's width (2*R+1). Default value: 1.</param>
	/// <param name="inRadiusY">Nearly half of the kernel's height (2*R+1), or same as inRadiusX. Default value: atl::NIL.</param>
	AVL_FUNCTION void DilateAndErodeImage
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,			
		atl::Optional<const avl::Region&>	inSourceRoi,	
		atl::Optional<avl::Pixel>			inBorderColor,	
		avl::KernelShape::Type				inKernel,		
		int									inRadiusX,		
		atl::Optional<int>					inRadiusY,		
		avl::Image&							outDilated,
		avl::Image&							outEroded
	)
	THROW_AVL_ERRORS;

	/// <summary>Calculates dilation, erosion and then averages them, all simultaneously for faster execution.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Range of outImage pixels to be computed. Default value: atl::NIL.</param>
	/// <param name="inSourceRoi">Range of inImage pixels to be read. Default value: atl::NIL.</param>
	/// <param name="inBorderColor">Color of the imaginary pixels outside the image boundaries. Default value: atl::NIL.</param>
	/// <param name="inKernel">Kernel shape.</param>
	/// <param name="inRadiusX">Nearly half of the kernel's width (2*R+1). Default value: 1.</param>
	/// <param name="inRadiusY">Nearly half of the kernel's height (2*R+1), or same as inRadiusX. Default value: atl::NIL.</param>
	AVL_FUNCTION void DilateErodeAndAverageImage
	(
		const avl::Image&					inImage,
		atl::Optional<const avl::Region&>	inRoi,			
		atl::Optional<const avl::Region&>	inSourceRoi,	
		atl::Optional<avl::Pixel>			inBorderColor,	
		avl::KernelShape::Type				inKernel,		
		int									inRadiusX,		
		atl::Optional<int>					inRadiusY,		
		avl::Image&							outDilated,
		avl::Image&							outEroded,
		avl::Image&							outAveraged
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates image of pixels' local standard deviations.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRoi">Region of Interest. Default value: atl::NIL.</param>
	/// <param name="inSourceRoi">Range of inImage pixels to be read. Default value: atl::NIL.</param>
	/// <param name="inKernelRadius">Radius of square kernel (width and height are 2r+1). Default value: 4.</param>
	/// <param name="outStdDevImage">Resulting image.</param>
	AVL_FUNCTION void StandardDeviationImage
	(
		const avl::Image&					inImage,		
		atl::Optional<const avl::Region&>	inRoi,			
		atl::Optional<const avl::Region&>	inSourceRoi,	
		const int							inKernelRadius,	
		avl::Image&							outStdDevImage	
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_IMAGELOCALTRANSFORMS_H

