//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_IMAGESPATIALTRANSFORMS_H
#define AVL_IMAGESPATIALTRANSFORMS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.hxx"
#include "Enums/PolarSpaceType.h"
#include "Enums/RotationSizeMode.h"
#include "Enums/Axis.h"
#include "Enums/InterpolationMethod.h"
#include "Enums/MirrorDirection.h"
#include "Enums/ImageLocalTransformsEnums.h"
#include "Enums/CropScaleMode.h"
#include "Image/Image.h"
#include "Basic/Types.h"
#include "Path/Path.h"
#include "AVLCommon/MatrixTypes.h"

namespace avl
{


	namespace PolarInterpolationMethod
	{
		enum Type
		{
			Linear,
			Nearest,
			Cubic,
			Area,
			Lanczos4
		};
	}


	/// <summary>Flips and rotates an image so that columns are exchanged with rows.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void TransposeImage
	(
		const avl::Image&	inImage,
		avl::Image&			outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Rotates an image clockwise.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inAngle">Rotation angle (clockwise). Default value: 45.0f.</param>
	/// <param name="inInterpolationMethod">Default value: Bilinear.</param>
	/// <param name="inInverse">'True' changes rotation to counter-clockwise. Default value: False.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void RotateImage
	(
		const avl::Image&					inImage,
		float							inAngle,				
		avl::RotationSizeMode::Type			inSizeMode,
		avl::InterpolationMethod::Type		inInterpolationMethod,
		const bool							inInverse,				
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Shrinks an image by the factor of two along each axis.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inScaleStep">Defines how many times the image size is divided by 2. Default value: 1.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void DownsampleImage
	( 
		const avl::Image&	inImage,
		const int			inScaleStep,	
		avl::Image&			outImage 
	)
	THROW_AVL_ERRORS;

	/// <summary>Shrinks an image by a natural factor along each axis.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inNX">Default value: 2.</param>
	/// <param name="inNY">Default value: 2.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void ShrinkImageNTimes
	(
		const avl::Image&	inImage,
		int					inNX,
		int					inNY,
		avl::Image&			outImage
	)
	THROW_AVL_ERRORS;

	namespace ResizeMethod
	{
		enum Type
		{
			NearestNeighbour,
			Bilinear,
			Area
		};
	}


	/// <summary>Enlarges or shrinks an image to new dimensions.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void ResizeImage
	(
		const avl::Image&		inImage,
		atl::Optional<int>		inNewWidth,
		atl::Optional<int>		inNewHeight,
		avl::ResizeMethod::Type	inResizeMethod,
		avl::Image&				outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Resizes an image by a factor along each axis.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inHorizontalScale">Default value: 1.0f.</param>
	/// <param name="inVerticalScale">Default value: 1.0f.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void ResizeImage_Relative
	(
		const avl::Image&		inImage,
		float				inHorizontalScale,
		float				inVerticalScale,
		avl::ResizeMethod::Type	inResizeMethod,
		avl::Image&				outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates an array of images, each downsampled from the previous one.</summary>
	/// <param name="inImage">Input image.</param>
	AVL_FUNCTION void CreateImagePyramid
	( 
		const avl::Image&		inImage,
		int						inMinPyramidLevel,
		int						inMaxPyramidLevel,
		atl::Array<avl::Image>&	outImagePyramid
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates an array of images, each downsampled from the previous, gauss-smoothed one.</summary>
	/// <param name="inImage">Input image.</param>
	AVL_FUNCTION void CreateImagePyramid_Gauss
	(
		const avl::Image&		inImage,
		avl::GaussKernel::Type inGaussKernelSize,
		int						inMinPyramidLevel,
		int						inMaxPyramidLevel,
		atl::Array<avl::Image>&	outImagePyramid
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates an array of images, each downsampled from the previous one. The output images may keep references to data owned by the input image.</summary>
	/// <param name="inImage">Input image.</param>
	AVL_FUNCTION void CreateImagePyramid_Linked
	(
		avl::Image&				inImage,
		int						inMinPyramidLevel,
		int						inMaxPyramidLevel,
		atl::Array<avl::Image>&	outImagePyramid
	)
	THROW_AVL_ERRORS;

	/// <summary>Reverses the order of the input image columns or rows depending on inMirrorDirection value.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inMirrorDirection">Reverse the order of image columns (horizontal direction) or rows (vertical direction). Default value: Vertical.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void MirrorImage
	(
		const avl::Image&			inImage,
		avl::MirrorDirection::Type	inMirrorDirection, 
		avl::Image&					outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes a leant image (shifts the rows).</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inShear">Relative shift between consecutive rows or columns of the image. Default value: 0.0f.</param>
	/// <param name="inAxis">Switches between horizontal or vertical shearing.</param>
	/// <param name="inInterpolationMethod">Default value: Bilinear.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void ShearImage
	(
		const avl::Image&				inImage,
		float						inShear,				
		avl::Axis::Type					inAxis,					
		avl::InterpolationMethod::Type	inInterpolationMethod,
		avl::Image&						outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates an image from a box-shaped fragment of the input image (with margins if requested).</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inSelection">Box defining a subimage to be cropped.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void CropImage
	(
		const avl::Image&	inImage, 
		const avl::Box&		inSelection,	
		avl::Image&			outImage 
	)
	THROW_AVL_ERRORS;

	/// <summary>Inverse of CropImage.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inSelection">The same value as in CropImage.</param>
	/// <param name="inWidth">Width of the original image.</param>
	/// <param name="inHeight">Height of the original image.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void UncropImage
	(
		const avl::Image&	inImage,
		const avl::Box&		inSelection,	
		int					inWidth,		
		int					inHeight,		
		avl::Image&			outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates an image from a rectangular fragment of another image (with black margins if requested).</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRectangle">Rectangle defining a rotated subimage.</param>
	/// <param name="inRectangleAlignment">Adjusts the rectangle to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScaleMode">InputScale keeps the input scale unchanged, AlignedScale rescales according to the input alignment scale. Default value: InputScale.</param>
	/// <param name="inInterpolationMethod">Default value: Bilinear.</param>
	/// <param name="inMargin">Width of an additional margin for the output image.</param>
	/// <param name="outImage">Output image.</param>
	/// <param name="outAlignedRectangle">Input rectangle after transformation (in the image coordinates).</param>
	/// <param name="outOutputAlignment">Alignment of the output image.</param>
	AVL_FUNCTION void CropImageToRectangle
	(
		const avl::Image&								inImage,
		const avl::Rectangle2D&							inRectangle,					
		atl::Optional<const avl::CoordinateSystem2D&>	inRectangleAlignment,			
		avl::CropScaleMode::Type						inScaleMode,					
		avl::InterpolationMethod::Type					inInterpolationMethod,
		float											inMargin,						
		avl::Image&										outImage,
		atl::Optional<avl::Rectangle2D&>				outAlignedRectangle = atl::NIL,	
		atl::Optional<avl::CoordinateSystem2D&>			outOutputAlignment = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Crops an image to the area of the specified region.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inRegion">Input region.</param>
	/// <param name="inOutsidePixel">Color used for locations outside the region.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void CropImageToRegion
	(
		const avl::Image&	inImage,
		const avl::Region&	inRegion,		
		const avl::Pixel&	inOutsidePixel,	
		avl::Image&			outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Translates an image by a vector, without changing its dimensions.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inBorder">Color used to fill pixels outside of the translated image.</param>
	/// <param name="inDeltaX">Horizontal shift.</param>
	/// <param name="inDeltaY">Vertical shift.</param>
	/// <param name="inInverse">Switches to the inverse operation.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void TranslateImage
	(
		const avl::Image&		inImage,
		const avl::Pixel&		inBorder,	
		int						inDeltaX,	
		int						inDeltaY,	
		bool					inInverse,	
		avl::Image&				outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Transforms an image to polar or log-polar space.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inCenter">Center of the coordinate system in input image.</param>
	/// <param name="inOutputSpaceType">Method of transformation.</param>
	/// <param name="inInterpolation">Method of underlying interpolation.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void ImagePolarTransform
	(
		const avl::Image&					inImage,
		const avl::Point2D&					inCenter,			
		avl::PolarSpaceType::Type			inOutputSpaceType,	
		avl::PolarInterpolationMethod::Type	inInterpolation,	
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Transforms an image from polar or log-polar space to euclidean space.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inCenter">Center of the coordinate system in output image.</param>
	/// <param name="inInputSpaceType">Method of transformation.</param>
	/// <param name="inInterpolation">Method of underlying interpolation.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void ImageInversePolarTransform
	(
		const avl::Image&						inImage,
		const avl::Point2D&						inCenter,			
		avl::PolarSpaceType::Type				inInputSpaceType,	
		avl::PolarInterpolationMethod::Type		inInterpolation,	
		avl::Image&								outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates an image from pixels traversed along a path.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inAxisPath">Input path.</param>
	/// <param name="inAxisPathAlignment">Adjusts the axis path to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanWidth">The width of the stripe of pixels along the given path. Default value: 5.</param>
	/// <param name="inAxisType">Type of axis the transformed axis path will be parallel to. Default value: Y.</param>
	/// <param name="inInterpolationMethod">The interpolation method used to compute pixel brightness in locations of not-integer coordinates. Default value: Bilinear.</param>
	/// <param name="outImage">Output image.</param>
	/// <param name="outAlignedAxisPath">Input path after transformation (in the image coordinates).</param>
	/// <param name="diagSamplingPoints">Array of paths each one containing the sampling points corresponding to one row of the resulting image.</param>
	AVL_FUNCTION void ImageAlongPath
	(
		const avl::Image&						inImage,				
		const avl::Path&						inAxisPath,				
		atl::Optional<const avl::CoordinateSystem2D&>	inAxisPathAlignment,	
		int										inScanWidth,			
		avl::Axis::Type							inAxisType,				
		avl::InterpolationMethod::Type			inInterpolationMethod,	
		avl::Image&								outImage,				
		atl::Optional<avl::Path&>				outAlignedAxisPath = atl::NIL, 
		atl::Array<avl::Path>&					diagSamplingPoints = atl::Dummy<atl::Array<avl::Path>>() 
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates an image from pixels traversed along an arc.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inAxisArc">Input arc.</param>
	/// <param name="inAxisArcAlignment">Adjusts the axis arc to the position of the inspected object. Default value: atl::NIL.</param>
	/// <param name="inScanWidth">The width of the stripe of pixels along the given arc. Default value: 5.</param>
	/// <param name="inAxisType">Type of axis the transformed axis arc will be parallel to. Default value: Y.</param>
	/// <param name="inInterpolationMethod">The interpolation method used to compute pixel brightness in locations of not-integer coordinates. Default value: Bilinear.</param>
	/// <param name="outImage">Output image.</param>
	/// <param name="outAlignedAxisArc">Input arc after transformation (in the image coordinates).</param>
	/// <param name="diagSamplingPoints">Array of paths each one containing the sampling points corresponding to one row of the resulting image.</param>
	AVL_FUNCTION void ImageAlongArc
	(
		const avl::Image&						inImage,				
		const avl::Arc2D&						inAxisArc,				
		atl::Optional<const avl::CoordinateSystem2D&>	inAxisArcAlignment,	
		int										inScanWidth,			
		avl::Axis::Type							inAxisType,				
		avl::InterpolationMethod::Type			inInterpolationMethod,	
		avl::Image&								outImage,				
		atl::Optional<avl::Arc2D&>				outAlignedAxisArc = atl::NIL, 
		atl::Array<avl::Path>&					diagSamplingPoints = atl::Dummy<atl::Array<avl::Path> >() 
	)
	THROW_AVL_ERRORS;

	namespace JoinDirection
	{
		enum Type
		{
			Horizontal,
			Vertical
		};
	}


	/// <summary>Creates a single image by glueing together the two input images in horizontal or vertical direction.</summary>
	/// <param name="inImage1">First input image.</param>
	/// <param name="inImage2">Second input image.</param>
	/// <param name="inDirection">Direction in which images are joined.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void JoinImages
	(
		const avl::Image&			inImage1,
		const avl::Image&			inImage2,
		avl::JoinDirection::Type	inDirection,	
		avl::Image&					outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a single image by glueing together many input images in horizontal or vertical direction.</summary>
	/// <param name="inImages">Array of input images.</param>
	/// <param name="inDirection">Direction in which images are joined.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void JoinImages_OfArray
	(
		const atl::Array<avl::Image>&	inImages,		
		avl::JoinDirection::Type		inDirection,	
		avl::Image&						outImage
	)
	THROW_AVL_ERRORS;

	struct JoinImages_OfSeriesState : public BaseState
	{
		int singleImageWidth;
		int singleImageHeight;
		int numOfImage;
		Image wholeImage;

		JoinImages_OfSeriesState()
			: numOfImage(0)
		{}
	};


	/// <summary>Creates a single image by glueing together a series of input images in horizontal or vertical direction.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inDirection">Direction in which images are joined.</param>
	/// <param name="inSeriesSize">Number of images which are joined.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void JoinImages_OfSeries
	(
		JoinImages_OfSeriesState&		ioState,
		const avl::Image&				inImage,
		avl::JoinDirection::Type		inDirection,	
		const int						inSeriesSize,	
		atl::Conditional<avl::Image>&	outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Moves the pixels of the input image by the vectors specified with inVectorImage.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inVectorImage">Two-channel image specifying translation vector for each pixel.</param>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void TranslatePixels
	(
		const avl::Image&					inImage,
		const avl::Image&					inVectorImage,			
		atl::Optional<const avl::Region&>	inRoi,
		avl::InterpolationMethod::Type		inImageInterpolation,
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Applies division model lens distortion to an image.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void UndistortImage_DivisionModel_Deprecated
	(
		const avl::Image&					inImage,
		const float&					inKappa,	
		const atl::Optional<avl::Point2D>&	inCenter,
		avl::InterpolationMethod::Type		inImageInterpolation,
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates affine transform matrix matrix. Return product of matrices: Translation * Rotation * Scale * Shearing.</summary>
	/// <param name="inScaleX">Image scale in X axis. Default value: 1.0f.</param>
	/// <param name="inScaleY">Image scale in Y axis. Default value: 1.0f.</param>
	/// <param name="inTranslation">Image translation.</param>
	/// <param name="inRotation">Image rotation in degree. Default value: 0.0f.</param>
	/// <param name="inShearingX">Shearing in X axis coefficient.</param>
	/// <param name="inShearingY">Shearing in Y axis coefficient.</param>
	/// <param name="outTransformMatrix">Return product of matrices: Translation * Rotation * Scale * Shearing.</param>
	AVL_FUNCTION void CreateAffineTransformMatrix
	(
		const float&		inScaleX,				
		const float&		inScaleY,				
		const avl::Vector2D&	inTranslation,			
		const float&		inRotation,				
		const float&		inShearingX,			
		const float&		inShearingY,			
		avl::Matrix&			outTransformMatrix		
	)
	THROW_AVL_ERRORS;

	/// <summary>Transforms an image by the provided transformation matrix.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inTransformMatrix">Transform matrix.</param>
	/// <param name="inInterpolation">Image quality.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void TransformImage
	(
		const avl::Image&						inImage,				
		const avl::Matrix&						inTransformMatrix,		
		const bool&								inInverse,				
		const avl::InterpolationMethod::Type&	inInterpolation,		
		avl::Image&								outImage
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_IMAGESPATIALTRANSFORMS_H

