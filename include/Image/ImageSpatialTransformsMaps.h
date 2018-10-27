//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_IMAGESPATIALTRANSFORMSMAPS_H
#define AVL_IMAGESPATIALTRANSFORMSMAPS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Enums/PolarSpaceType.h"
#include "Enums/RotationSizeMode.h"
#include "Enums/InterpolationMethod.h"
#include "Image/Image.h"
#include "Region/Region.h"
#include "Image/ImageFormat.h"
#include "Image/SpatialMap.h"
#include "Path/Path.h"
#include "ComputerVision/CameraCalibration/CameraCalibrationStructs.h"
#include "AVLCommon/MatrixTypes.h"

namespace avl
{


	/// <summary>Returns individual fields of a spatial map.</summary>
	AVL_FUNCTION void AccessSpatialMap
	(
		const avl::SpatialMap&			inSpatialMap,
		int&							outImageWidth,
		int&							outImageHeight,
		int&							outImagePitch,
		avl::PlainType::Type&			outImageType,
		int&							outImageDepth,
		int&							outWidth,
		int&							outHeight,
		avl::ImageFormat&				outImageFormat,
		avl::InterpolationMethod::Type& outInterpolationMethod
	)
	THROW_AVL_ERRORS;

	/// <summary>Checks if a spatial map may be applied to transform the given image.</summary>
	/// <param name="inImage">Input image.</param>
	AVL_FUNCTION void TestSpatialMapApplicability
	(
		const avl::Image&				inImage,
		const avl::SpatialMap&			inSpatialMap,
		bool&							outAreCompatible						
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a spatial map representing an image rotation.</summary>
	/// <param name="inImageFormat">Information about dimensions, depth and pixel type of the image.</param>
	/// <param name="inAngle">The angle of rotation. Default value: 45.0f.</param>
	/// <param name="inInterpolationMethod">Interpolation method used in extraction of image pixel values. Default value: Bilinear.</param>
	/// <param name="outRotationMap">Output spatial map.</param>
	/// <param name="outOutputRegion">Pixels set by the spatial map application.</param>
	AVL_FUNCTION void CreateImageRotationMap
	(
		const avl::ImageFormat&			inImageFormat,				
		float						inAngle,					
		avl::RotationSizeMode::Type		inSizeMode,
		avl::InterpolationMethod::Type	inInterpolationMethod,		
		avl::SpatialMap&				outRotationMap,				
		atl::Optional<avl::Region&>		outOutputRegion = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a spatial map representing an image resizing.</summary>
	/// <param name="inImageFormat">Information about dimensions, depth and pixel type of the image.</param>
	/// <param name="inNewWidth">Width of an image created by output spatial map application.</param>
	/// <param name="inNewHeight">Height of an image created by output spatial map application.</param>
	/// <param name="inInterpolationMethod">Interpolation method used in extraction of image pixel values. Default value: Bilinear.</param>
	/// <param name="outResizeMap">Output spatial map.</param>
	/// <param name="outOutputRegion">Pixels set by the spatial map application.</param>
	AVL_FUNCTION void CreateImageResizeMap
	(
		const avl::ImageFormat&			inImageFormat,			
		int								inNewWidth,				
		int								inNewHeight,			
		avl::InterpolationMethod::Type	inInterpolationMethod,	
		avl::SpatialMap&				outResizeMap,			
		atl::Optional<avl::Region&>		outOutputRegion = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a spatial map representing an image polar transform.</summary>
	/// <param name="inImageFormat">Information about dimensions, depth and pixel type of the image.</param>
	/// <param name="inSpaceType">Method of transformation.</param>
	/// <param name="inInterpolationMethod">Interpolation method used in extraction of image pixel values. Default value: Bilinear.</param>
	/// <param name="outPolarMap">Output spatial map.</param>
	/// <param name="outOutputRegion">Pixels set by the spatial map application.</param>
	AVL_FUNCTION void CreateImagePolarTransformMap
	(
		const avl::ImageFormat&				inImageFormat,		
		const avl::Point2D&					inCenter,
		avl::PolarSpaceType::Type			inSpaceType,		
		avl::InterpolationMethod::Type		inInterpolationMethod,	
		avl::SpatialMap&					outPolarMap,		
		atl::Optional<avl::Region&>			outOutputRegion = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a spatial map representing an image inverse polar transform.</summary>
	/// <param name="inImageFormat">Information about dimensions, depth and pixel type of the image.</param>
	/// <param name="inSpaceType">Method of transformation.</param>
	/// <param name="inInterpolationMethod">Interpolation method used in extraction of image pixel values. Default value: Bilinear.</param>
	/// <param name="outPolarMap">Output spatial map.</param>
	/// <param name="outOutputRegion">Pixels set by the spatial map application.</param>
	AVL_FUNCTION void CreateImageInversePolarTransformMap
	(
		const avl::ImageFormat&				inImageFormat,		
		const avl::Point2D&					inCenter,
		avl::PolarSpaceType::Type			inSpaceType,		
		avl::InterpolationMethod::Type		inInterpolationMethod,	
		avl::SpatialMap&					outPolarMap,		
		atl::Optional<avl::Region&>			outOutputRegion = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Applies a precomputed image transform, defined by a spatial map object.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inSpatialMap">Definition of the transformation.</param>
	/// <param name="inMapRoi">Defines which elements of the spatial map are valid. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void RemapImage
	(
		const avl::Image&					inImage,
		const avl::SpatialMap&				inSpatialMap,	
		atl::Optional<const avl::Region&>	inMapRoi,		
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Combines two spatial maps.</summary>
	AVL_FUNCTION void CombineSpatialMaps
	(
		const avl::SpatialMap&	inSpatialMap1,
		const avl::SpatialMap&	inSpatialMap2,
		avl::SpatialMap&		outSpatialMap
	)
	THROW_AVL_ERRORS;

	/// <summary>Combines two spatial maps.</summary>
	AVL_FUNCTION void AddSpatialMaps
	(
		const avl::SpatialMap&				inSpatialMap1,
		const avl::SpatialMap&				inSpatialMap2,
		avl::SpatialMap&					outSpatialMap
	)
	THROW_AVL_ERRORS;

	/// <summary>Removes lens distortion from an image. To be used with a GUI based on chessboard pattern recognition.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inUndistortionMap">Definition of the transformation.</param>
	/// <param name="inMapRoi">Defines which elements of the spatial map are valid. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void UndistortImage
	(
		const avl::Image&					inImage,
		const avl::SpatialMap&				inUndistortionMap,	
		atl::Optional<const avl::Region&>	inMapRoi,			
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Serializes a SpatialMap object to an AVDATA file.</summary>
	/// <param name="inSpatialMap">SpatialMap to be serialized.</param>
	/// <param name="inFilename">Name of the target file.</param>
	AVL_FUNCTION void SaveSpatialMap
	(
		const avl::SpatialMap&	inSpatialMap,	
		const atl::File&			inFilename		
	)
	THROW_AVL_ERRORS;

	/// <summary>Deserializes a SpatialMap object from a AVDATA file.</summary>
	/// <param name="inFilename">Name of the source file.</param>
	/// <param name="outSpatialMap">Deserialized SpatialMap.</param>
	AVL_FUNCTION void LoadSpatialMap
	(
		const atl::File& inFilename,		
		avl::SpatialMap&	outSpatialMap	
	)
	THROW_AVL_ERRORS;

	/// <summary>Joins two matrices of coordinates to produce a SpatialMap for use in RemapImage.</summary>
	/// <param name="inImageFormat">Information about dimensions, depth and pixel type of the image.</param>
	/// <param name="inMatrixX">Map of real X coordinates.</param>
	/// <param name="inMatrixY">Map of real Y coordinates.</param>
	/// <param name="inInterpolationMethod">Default value: Bilinear.</param>
	/// <param name="inRoundingOpenCV">Use same interpolation convention as cvRemap.</param>
	/// <param name="outSpatialMap">Output spatial map.</param>
	/// <param name="outOutputRegion">Pixels set by the spatial map application.</param>
	AVL_FUNCTION void ConvertMatrixMapsToSpatialMap
	(
		const avl::ImageFormat&	inImageFormat, 
		const avl::Matrix&		inMatrixX, 
		const avl::Matrix&		inMatrixY, 
		avl::InterpolationMethod::Type	inInterpolationMethod,
		bool					inRoundingOpenCV, 
		avl::SpatialMap&		outSpatialMap,	
		atl::Optional<avl::Region&>	outOutputRegion = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Splits a spatial map into two matrices of source coordinates.</summary>
	/// <param name="inRoundingOpenCV">Use same interpolation convention as cvRemap.</param>
	/// <param name="outMatrixX">Map of real X coordinates.</param>
	/// <param name="outMatrixY">Map of real Y coordinates.</param>
	AVL_FUNCTION void ConvertSpatialMapToMatrixMaps
	(
		const avl::SpatialMap&	inSpatialMap,
		bool					inRoundingOpenCV, 
		avl::Matrix&			outMatrixX,	
		avl::Matrix&			outMatrixY	
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts any spatial map to NearestNeighbour interpolation.</summary>
	AVL_FUNCTION void ConvertSpatialMap_ToNearest
	(
		const avl::SpatialMap&	inSpatialMap,
		avl::SpatialMap&		outSpatialMap
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a spatial map for transformations from a cylinder surface to a flat rectangle.</summary>
	/// <param name="inImageFormat">Information about dimensions, depth and pixel type of the image.</param>
	/// <param name="inCylinderRectangle">Bounding rectangle of the cylinder.</param>
	/// <param name="inCylinderRadiusCorrection">How many pixels the cylinder radius is larger than the visible circle radius. Default value: 0.0f.</param>
	/// <param name="inOpticalAxis">Coordinates of the camera optical axis (Auto = image center). Default value: atl::NIL.</param>
	/// <param name="inNewWidth">Width of an image created by output spatial map application. Default value: atl::NIL.</param>
	/// <param name="inNewHeight">Height of an image created by output spatial map application. Default value: atl::NIL.</param>
	/// <param name="inMargin">Width of the cylinder extreme points zone excluded from spatial map. Default value: 0.</param>
	/// <param name="inInterpolationMethod">Interpolation method used in extraction of image pixel values. Default value: Bilinear.</param>
	/// <param name="outSpatialMap">Output spatial map.</param>
	/// <param name="outOutputRegion">Pixels set by the spatial map application.</param>
	AVL_FUNCTION void CreateCylinderMap
	(
		const avl::ImageFormat&			inImageFormat,					
		const avl::Rectangle2D&			inCylinderRectangle,			
		const float						inCylinderRadiusCorrection,		
		atl::Optional<avl::Point2D>		inOpticalAxis,					
		atl::Optional<int>				inNewWidth,						
		atl::Optional<int>				inNewHeight,					
		const int						inMargin,						
		avl::InterpolationMethod::Type	inInterpolationMethod,			
		avl::SpatialMap&				outSpatialMap,					
		atl::Optional<avl::Region&>		outOutputRegion = atl::NIL		
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a spatial map for transformations from a sphere surface to a flat rectangle.</summary>
	/// <param name="inImageFormat">Information about dimensions, depth and pixel type of the image.</param>
	/// <param name="inSphereRectangle">Bounding rectangle of a sphere.</param>
	/// <param name="inSphereRadiusCorrection">How many pixels the sphere radius is larger than the visible circle radius. Default value: 0.0f.</param>
	/// <param name="inNewDimension">Width and height of an image created by output spatial map application. Default value: atl::NIL.</param>
	/// <param name="inMargin">Width of the sphere extreme points zone excluded from spatial map. Default value: 0.</param>
	/// <param name="inInterpolationMethod">Interpolation method used in extraction of image pixel values. Default value: Bilinear.</param>
	/// <param name="outSpatialMap">Output spatial map.</param>
	/// <param name="outOutputRegion">Pixels set by the spatial map application.</param>
	AVL_FUNCTION void CreateSphereMap
	(
		const avl::ImageFormat&			inImageFormat,				
		const avl::Rectangle2D&			inSphereRectangle,			
		const float						inSphereRadiusCorrection,	
		atl::Optional<int>				inNewDimension,				
		const int						inMargin,					
		avl::InterpolationMethod::Type	inInterpolationMethod,		
		avl::SpatialMap&				outSpatialMap,				
		atl::Optional<avl::Region&>		outOutputRegion = atl::NIL	
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a spatial map which performs transform defined as a matrix.</summary>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inTransformMatrix">3x3 transform matrix.</param>
	/// <param name="inNewSize">New image size after remapping. Default value: atl::NIL.</param>
	/// <param name="inInterpolationMethod">Interpolation method used in extraction of image pixel values.</param>
	/// <param name="outSpatialMap">Calculated spatial map.</param>
	AVL_FUNCTION void CreateMatrixTransformMap
	(
		const avl::ImageFormat&						inImageFormat,
		const atl::Optional<avl::Region>&			inRoi,
		const avl::Matrix&							inTransformMatrix,			
		const atl::Optional<avl::Size>&				inNewSize,					
		avl::InterpolationMethod::Type				inInterpolationMethod,		
		avl::SpatialMap&							outSpatialMap				
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a perspective transform map from four points denoting a rectangle in the world coordinates.</summary>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inImagePoints">Points define real object plane corners.</param>
	/// <param name="inTargetPoints">Points define target plane corners. If NIL then image corners are used starting from (0,0) (Width, 0) (Width, Height), (0, Height). Default value: atl::NIL.</param>
	/// <param name="inNewSize">New image size after remapping. Default value: atl::NIL.</param>
	/// <param name="inInterpolationMethod">Interpolation method used in extraction of image pixel values.</param>
	/// <param name="outSpatialMap">Created SpatialMap with perspective transform.</param>
	/// <param name="outTransformMatrix">Used transform matrix.</param>
	AVL_FUNCTION void CreatePerspectiveMap_Points
	(
		const avl::ImageFormat&							inImageFormat,
		const atl::Optional<avl::Region>&				inRoi,
		const atl::Array<avl::Point2D>&					inImagePoints,				
		const atl::Optional<atl::Array<avl::Point2D>>&	inTargetPoints,				
		const atl::Optional<avl::Size>&					inNewSize,					
		const avl::InterpolationMethod::Type			inInterpolationMethod,		
		avl::SpatialMap&								outSpatialMap,				
		avl::Matrix&									outTransformMatrix			
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a perspective transform map from planes defined by paths.</summary>
	/// <param name="inRoi">Range of pixels to be processed. Default value: atl::NIL.</param>
	/// <param name="inImagePath">Plane defined by a closed path made of 4 points.</param>
	/// <param name="inTargetPath">Target plane. If NIL then image corners are used starting from (0,0) (Width, 0) (Width, Height), (0, Height). Default value: atl::NIL.</param>
	/// <param name="inNewSize">New image size after remapping. Default value: atl::NIL.</param>
	/// <param name="inInterpolationMethod">Interpolation method used in extraction of image pixel values.</param>
	/// <param name="outSpatialMap">Calculated spatial map.</param>
	/// <param name="outTransformMatrix">Used transform matrix.</param>
	AVL_FUNCTION void CreatePerspectiveMap_Path
	(
		const avl::ImageFormat&							inImageFormat,
		const atl::Optional<avl::Region>&				inRoi,
		const avl::Path&								inImagePath,				
		const atl::Optional<avl::Path>&					inTargetPath,				
		const atl::Optional<avl::Size>&					inNewSize,					
		const avl::InterpolationMethod::Type			inInterpolationMethod,		
		avl::SpatialMap&								outSpatialMap,				
		avl::Matrix&									outTransformMatrix			
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes a spatial transform map for undistorting images from a calibrated camera.</summary>
	/// <param name="inMapWidth">Width of output map, default: same as example image. Default value: atl::NIL.</param>
	/// <param name="inMapHeight">Height of output map, default: same as example image. Default value: atl::NIL.</param>
	/// <param name="inMapShift">Translation from the principal point on the image plane.</param>
	/// <param name="inMapRotation">Rotation of the principal point on the image plane.</param>
	/// <param name="inCameraRotationY">Rotation of view around Y axis (a.k.a. Pan, Azimuth or Yaw).</param>
	/// <param name="inCameraRotationX">Rotation of view around X axis (a.k.a. Tilt, Elevation or Pitch).</param>
	/// <param name="inCameraRotationZ">Rotation of view around Z axis (a.k.a. Roll, Horizon).</param>
	/// <param name="inImageFormat">Information about dimensions, depth and pixel type of the image.</param>
	/// <param name="inInterpolationMethod">Default value: Bilinear.</param>
	AVL_FUNCTION void CreateUndistortionMap
	(
		const avl::Matrix&				inCameraMatrix,
		const avl::LensDistortion&		inDistortion,
		atl::Optional<int>				inMapWidth,			
		atl::Optional<int>				inMapHeight,		
		const avl::Vector2D&			inMapShift,			
		float						inMapRotation,		
		float						inCameraRotationY,	
		float						inCameraRotationX,	
		float						inCameraRotationZ,	
		const avl::ImageFormat&			inImageFormat,		
		avl::InterpolationMethod::Type	inInterpolationMethod,
		avl::SpatialMap&				outSpatialMap,
		atl::Optional<avl::Region&>		outOutputRegion = atl::NIL
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes a spatial transform map for undistorting images using divisional model.</summary>
	AVL_FUNCTION void CreateUndistortionMap_Divisional
	(
		const avl::ImageFormat&				inImageFormat,
		const float&					inKappa,	
		const atl::Optional<avl::Point2D>&	inCenter,
		avl::InterpolationMethod::Type		inInterpolationMethod,
		avl::SpatialMap&					outMap
	)
	THROW_AVL_ERRORS;

	/// <summary>Computes a reverse image transform, defined by a spatial map object.</summary>
	/// <param name="inSpatialMap">Definition of the transformation.</param>
	AVL_FUNCTION void CreateReverseMap
	(
		const avl::SpatialMap&	inSpatialMap,	
		avl::SpatialMap&		outReverseSpatialMap
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_IMAGESPATIALTRANSFORMSMAPS_H

