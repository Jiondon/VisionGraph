//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVS_CAMERACALIBRATION_H
#define AVS_CAMERACALIBRATION_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "AVLCommon/MatrixTypes.h"
#include "Enums/InterpolationMethod.h"
#include "Geometry/Geometry.h"
#include "Geometry3D/Geometry3D.h"
#include "Image/Image.h"
#include "Image/ImageFormat.h"
#include "Image/SpatialMap.h"
#include "ComputerVision/CameraCalibration/CameraCalibrationStructs.h"

namespace avl
{


	/// <summary>Returns LensDistortion as a Matrix of distortion coefficients.</summary>
	AVL_FUNCTION void LensDistortionToMatrix
	(
		const avl::LensDistortion&	inDistortion,
		avl::Matrix&				outMatrix
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds the telecentric camera intrinsic parameters from the input arrays of image and real-world coordinates. Uses telecentric camera model (affine camera).</summary>
	/// <param name="inObjectPoints">Array, for each view: array of 3D points of the calibration pattern.</param>
	/// <param name="inImagePoints">Array, for each view: array of corresponding 2D points in the picture.</param>
	/// <param name="inImageWidth">Image width, only used to initialize camera matrix, not used when inInitialCameraMatrix present.</param>
	/// <param name="inImageHeight">Image height, only used to initialize camera matrix, not used when inInitialCameraMatrix present.</param>
	/// <param name="inUseRationalModel">Estimate radial denominator coefficients k4, k5, k6. Default value: False.</param>
	/// <param name="inUseTangentialModel">Estimate tangential distortion coefficients p1, p2. Default value: True.</param>
	/// <param name="inUseThinPrismModel">Estimate thin prism distortion coefficients s1, s2, s3, s4. Default value: True.</param>
	/// <param name="outError">Final reprojection RMS error.</param>
	AVL_FUNCTION void CalibrateCamera_Telecentric
	(
		const atl::Array<atl::Array<avl::Point3D> >&	inObjectPoints,					
		const atl::Array<atl::Array<avl::Point2D> >&	inImagePoints,					
		int												inImageWidth,					
		int												inImageHeight,					
		bool											inUseRationalModel,				
		bool											inUseTangentialModel,			
		bool											inUseThinPrismModel,			
		avl::Matrix&									outCameraMatrix,
		avl::LensDistortion&							outDistortion,
		atl::Optional<float&>							outError = atl::NIL				
	)
	THROW_AVL_ERRORS;

	/// <summary></summary>
	/// <param name="inPointsX">Default value: 10.</param>
	/// <param name="inPointsY">Default value: 10.</param>
	/// <param name="inPointSpacing">Default value: 1.0f.</param>
	/// <param name="inPlaneRotationAxis">Default value: (DeltaX: 0.0, DeltaY: 0.0, DeltaZ: 1.0).</param>
	/// <param name="inPlaneRotationAngle">Default value: 0.0f.</param>
	/// <param name="inPlaneTranslation">Default value: (DeltaX: 0.0, DeltaY: 0.0, DeltaZ: 10.0).</param>
	/// <param name="inCameraType">0 - pinhole, 1 - telecentric. Default value: 0.</param>
	/// <param name="inFocalLengthOrMagnificationX">Default value: 100.0f.</param>
	/// <param name="inPrincipalPoint">by default pp is on the center of output image. Default value: atl::NIL.</param>
	/// <param name="inImageSize">Default value: (Width: 640, Height: 480).</param>
	AVL_FUNCTION void GenerateCalibrationPoints
	(
		int inPointsX,
		int inPointsY,
		float inPointSpacing,
		const avl::Vector3D& inPlaneRotationAxis,
		float inPlaneRotationAngle,
		const avl::Vector3D& inPlaneTranslation,
		int inCameraType,						
		float inFocalLengthOrMagnificationX,
		atl::Optional<float> inFocalLengthOrMagnificationY,
		atl::Optional<avl::Point2D> inPrincipalPoint,	
		const avl::Size& inImageSize,
		atl::Array<avl::Point3D>& outObjectPoints,
		atl::Array<avl::Point2D>& outImagePoints
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds the camera intrinsic parameters from the input arrays of image and real-world coordinates. Uses pinhole camera model (perspective camera).</summary>
	/// <param name="inObjectPoints">Array, for each view: array of 3D points of the calibration pattern.</param>
	/// <param name="inImagePoints">Array, for each view: array of corresponding 2D points in the picture.</param>
	/// <param name="inImageWidth">Image width, only used to initialize camera matrix, not used when inInitialCameraMatrix present.</param>
	/// <param name="inImageHeight">Image height, only used to initialize camera matrix, not used when inInitialCameraMatrix present.</param>
	/// <param name="inDistortionModelType">0 - divisional (k4), 1 - polynomial (k1,k2,k3,p1,p2), 2 - poly_with_thin_prism (k1,k2,k3,p1,p2,s1,s2,s3,s4), 3 - custom (not implemented yet). Default value: 0.</param>
	/// <param name="outError">Final reprojection RMS error.</param>
	AVL_FUNCTION void CalibrateCamera_Pinhole2
	(
		const atl::Array<atl::Array<avl::Point3D> >&	inObjectPoints,				
		const atl::Array<atl::Array<avl::Point2D> >&	inImagePoints,				
		int												inImageWidth,				
		int												inImageHeight,				
		int												inDistortionModelType,		
		atl::Optional<float>							inFocalLength,
		avl::Matrix&									outCameraMatrix,
		avl::LensDistortion&							outDistortion,
		atl::Optional<float&>							outError = atl::NIL			
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds the camera intrinsic and extrinsic parameters from the input arrays of image and real-world coordinates. Uses pinhole camera model (perspective camera).</summary>
	/// <param name="inObjectPoints">Array, for each view: array of 3D points of the calibration pattern.</param>
	/// <param name="inImagePoints">Array, for each view: array of corresponding 2D points in the picture.</param>
	/// <param name="inImageWidth">Image width, only used to initialize camera matrix, not used when inInitialCameraMatrix present. Default value: 640.</param>
	/// <param name="inImageHeight">Image height, only used to initialize camera matrix, not used when inInitialCameraMatrix present. Default value: 480.</param>
	/// <param name="inFixPrincipalPoint">The principal point is not changed during the global optimization. It stays in the center of the image, or as in the initial camera matrix.</param>
	/// <param name="inFixAspectRatio">The functions considers only fy as a free parameter. The ratio fx/fy stays 1, or as in the initial camera matrix.</param>
	/// <param name="inZeroTangentDist">Tangential distortion coefficients (p_1, p_2) are assumed zero.</param>
	/// <param name="inInitialCameraMatrix">Optional initial camera matrix, required for inFixPrincipalPoint and inFixAspectRatio. Default value: atl::NIL.</param>
	/// <param name="outUnitScales">Image scale: px / mm.</param>
	/// <param name="outCameraPositions">Positions of cameras in world coordinate system for the views.</param>
	/// <param name="outError">Final re-projection error value.</param>
	AVL_FUNCTION void CalibrateCamera
	(
		const atl::Array<atl::Array<avl::Point3D> >&	inObjectPoints,					
		const atl::Array<atl::Array<avl::Point2D> >&	inImagePoints,					
		int												inImageWidth,					
		int												inImageHeight,					
		bool											inFixPrincipalPoint,			
		bool											inFixAspectRatio,				
		bool											inZeroTangentDist,				
		atl::Optional<const avl::Matrix&>				inInitialCameraMatrix,			
		bool											inUseRationalModel,
		bool											inUseThinPrismModel,		
		avl::Matrix&									outCameraMatrix,
		avl::LensDistortion&							outDistortion,
		atl::Array<float>&							outUnitScales,					
		atl::Optional<atl::Array<avl::Position3D>&>		outCameraPositions = atl::NIL,	
		atl::Optional<float&>						outError = atl::NIL				
	)
	THROW_AVL_ERRORS;

	/// <summary>Select a subset of the given points that forms a grid and assign world plane coordinates to them.</summary>
	/// <param name="inPoints">Points to calculate a grid.</param>
	/// <param name="inScale">Distance between two rows or two columns of the grid in world units. Default value: 1.0f.</param>
	/// <param name="outPoints3D">Calculated points in the world units.</param>
	/// <param name="outSelectedPoints">Which points were selected to calculate the grid.</param>
	/// <param name="diagAxes">Points which lays on X and Y axis.</param>
	AVL_FUNCTION void AnnotateGridPoints_Deprecated
	(
		const atl::Array<avl::Point2D>&		inPoints,				
		float							inScale,				
		atl::Array<avl::Point3D>&			outPoints3D,			
		atl::Array<avl::Point2D>&			outSelectedPoints,		
		atl::Array<avl::Point2D>&			diagAxes = atl::Dummy< atl::Array<avl::Point2D> >()				
	)
	THROW_AVL_ERRORS;

	/// <summary>Select a subset of the given points that forms a grid and assign world plane coordinates to them.</summary>
	/// <param name="inPoints">Points to calculate a grid.</param>
	/// <param name="inScale">Distance between two rows or two columns of the grid in world units. Default value: 1.0f.</param>
	/// <param name="inMinDistance">Minimum distance between two rows or two columns in pixels. Default value: atl::NIL.</param>
	/// <param name="inMaxDistance">Maximum distance between two rows or two columns in pixels. Default value: 10.0f.</param>
	/// <param name="inAngleTolerance">Maximum deviation from right angles in the grid. Default value: 10.0f.</param>
	/// <param name="outPoints3D">Calculated points in the world units.</param>
	/// <param name="outSelectedPoints">Which points were selected to calculate the grid.</param>
	/// <param name="diagValidSubgraph">Graph forming a valid grid.</param>
	AVL_FUNCTION void AnnotateGridPoints
	(
		const atl::Array<avl::Point2D>&			inPoints,				
		const float							inScale,				
		atl::Optional<float>				inMinDistance,			
		const float							inMaxDistance,			
		const float							inAngleTolerance,		
		atl::Array<avl::Point3D>&				outPoints3D,			
		atl::Array<avl::Point2D>&				outSelectedPoints,		
		atl::Array<avl::Segment2D>&				diagValidSubgraph = atl::Dummy< atl::Array<avl::Segment2D> >()		
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns a spatial map with undistortion map.</summary>
	/// <param name="inImages">Images with calibration boards.</param>
	/// <param name="inColumnCount">Chessboards columns count.</param>
	/// <param name="inRowsCount">Chessboards rows count.</param>
	/// <param name="inMapWidth">Output map width.</param>
	/// <param name="inMapHeight">Output map height.</param>
	/// <param name="inUseRationalModel">Rational model.</param>
	/// <param name="inGridScale">Size of each cell.</param>
	/// <param name="inDisableTangentialDistortion">Disable lens tilt distortion.</param>
	/// <param name="outSpatialMap">Output spatial map.</param>
	/// <param name="outError">Calibration approximation error.</param>
	AVL_FUNCTION void CalibrateCameraFromImages_Chessboard
	(
		const atl::Array<avl::Image>&	inImages,						
		int								inColumnCount,					
		int								inRowsCount,					
		int								inMapWidth,						
		int								inMapHeight,					
		bool							inUseRationalModel,				
		float						inGridScale,					
		bool							inDisableTangentialDistortion,  
		avl::SpatialMap&				outSpatialMap,					
		atl::Conditional<float>&	outError						
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns a spatial map with undistortion map.</summary>
	/// <param name="inImages">Images with calibration boards.</param>
	/// <param name="outSpatialMap">Output spatial map.</param>
	/// <param name="outError">Calibration approximation error.</param>
	AVL_FUNCTION void CalibrateCameraFromImages_CustomGrid
	(
		const atl::Array<avl::Image>&		 inImages,			
		const int							 inRadius,
		const float						 inMinRelative,
		const float						 inHysteresis,
		int									 inPatternMinWidth,
		int									 inPatternMaxWidth,
		int									 inPatternMinHeight,
		int									 inPatternMaxHeight,
		const bool							 inCreateMap,
		const float						 inGridScale,
		atl::Conditional<avl::SpatialMap>&	 outSpatialMap,		
		atl::Conditional<float>&		 outError,			
		atl::Array<atl::Array<avl::Region>>& outRegions
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns a spatial map with undistortion map.</summary>
	/// <param name="inImages">Images with calibration boards.</param>
	/// <param name="inSymmetricPattern">Is grid symmetrical.</param>
	/// <param name="outSpatialMap">Output spatial map.</param>
	AVL_FUNCTION void CalibrateCameraFromImages_CustomCircleGrid
	(
		const atl::Array<avl::Image>&		 inImages,				
		int									 inPatternWidth,
		int									 inPatternHeight,
		bool								 inSymmetricPattern,		
		int									 inCellWidth,
		bool								 inUseClustering,
		atl::Conditional<avl::SpatialMap>&	 outSpatialMap,				
		atl::Conditional<float>&		 outError
	)
	THROW_AVL_ERRORS;

	/// <summary>Detects a chessboard on the image, and returns the points where 4 chessboard squares meet.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inChessboardWidth">Number of ranks (columns) of the chessboard.</param>
	/// <param name="inChessboardHeight">Number of files (rows) of the chessboard.</param>
	/// <param name="outImageGridPoints">Approximated position of grid points.</param>
	AVL_FUNCTION void IsChessBoardPresent
	(
		const avl::Image&								inImage,
		int												inChessboardWidth,		
		int												inChessboardHeight,		
		atl::Conditional<atl::Array<avl::Point2D> >&	outImageGridPoints		
	)
	THROW_AVL_ERRORS;

	/// <summary>Detects a circle board on an image. Returns the center of each circle.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inBoardColumns">Number of ranks (columns) of the chessboard.</param>
	/// <param name="inBoardRows">Number of files (rows) of the chessboard.</param>
	/// <param name="inSymmetricPattern">Board has symmetric pattern.</param>
	/// <param name="outImageGridPoints">Approximated position of grid points.</param>
	AVL_FUNCTION void IsCircleGridPresent
	(
		const avl::Image&								inImage,
		int												inBoardColumns,			
		int												inBoardRows,			
		bool											inSymmetricPattern,		
		atl::Conditional<atl::Array<avl::Point2D> >&	outImageGridPoints		
	)
	THROW_AVL_ERRORS;

	/// <summary>Detects a chessboard on the image, and returns the points where 4 chessboard squares meet.</summary>
	/// <param name="inImage">Input image.</param>
	/// <param name="inChessboardWidth">Number of ranks (columns) of the chessboard.</param>
	/// <param name="inChessboardHeight">Number of files (rows) of the chessboard.</param>
	/// <param name="inGridOrigin">Real-world coordinates of top-left grid point.</param>
	/// <param name="inSquareDimension">Real-world length of a single chessboard square (mm). Default value: 1.0f.</param>
	/// <param name="inAdaptiveThresholding">Use adaptive thresholding instead of a global threshold of average.</param>
	/// <param name="inImageNormalization">Normalize input image using histogram equalization prior to detection.</param>
	/// <param name="inAdditionalFiltering">Use more criteria for eliminating false chessboards.</param>
	/// <param name="inPresenceCheck">Perform a fast approximate test of chessboard presence before locating it.</param>
	/// <param name="inSubpixelRefinement">If corners are found, post-process them to improve precision.</param>
	/// <param name="outWorldGridPoints">Corresponding 3D (World) points, generated from grid origin and square dimension.</param>
	AVL_FUNCTION void DetectChessboardGrid
	(
		const avl::Image&								inImage,
		int												inChessboardWidth,		
		int												inChessboardHeight,		
		const avl::Point3D&								inGridOrigin,			
		float										inSquareDimension,		
		bool											inAdaptiveThresholding,	
		bool											inImageNormalization,	
		bool											inAdditionalFiltering,	
		bool											inPresenceCheck,		
		bool											inSubpixelRefinement,	
		atl::Conditional<atl::Array<avl::Point2D> >&	outImageGridPoints,
		atl::Conditional<atl::Array<avl::Point3D> >&	outWorldGridPoints		
	)
	THROW_AVL_ERRORS;

	/// <summary>Estimate the scale for points in the Z=0 plane in a perpendicular view.</summary>
	/// <param name="inCameraMatrix">Camera matrix obtained from calibration.</param>
	/// <param name="inCameraPosition">Camera position for which the scale is estimated.</param>
	/// <param name="outUnitsPerPixel">Scale factor, or physical dimensions of 1 pixel in the world plane.</param>
	AVL_FUNCTION void EstimateRealScale
	(
		const avl::Matrix&		inCameraMatrix,		
		const avl::Position3D&	inCameraPosition,	
		float&				outUnitsPerPixel	
	)
	THROW_AVL_ERRORS;

	/// <summary>Remove lens distortion for a single point.</summary>
	/// <param name="inPoint">Point on distorted image.</param>
	/// <param name="inCameraMatrix">Camera matrix obtained from calibration.</param>
	/// <param name="inDistortion">Distortion parameters obtained from calibration.</param>
	/// <param name="outPoint">Point on undistorted image.</param>
	AVL_FUNCTION void UndistortPoint
	(
		const avl::Point2D&			inPoint,			
		const avl::Matrix&			inCameraMatrix,		
		const avl::LensDistortion&	inDistortion,		
		avl::Point2D& outPoint							
	)
	THROW_AVL_ERRORS;

} // namespace avl

namespace avs
{

	/// <summary>Returns individual fields of a 3D position.</summary>
	/// <param name="outX">x-coordinate.</param>
	/// <param name="outY">y-coordinate.</param>
	/// <param name="outZ">z-coordinate.</param>
	/// <param name="outPhi">First rotation, around Y axis (Yaw, Azimuth).</param>
	/// <param name="outTheta">First rotation, around X axis (Pitch, Elevation).</param>
	/// <param name="outPsi">First rotation, around Z axis (Roll, Bank).</param>
	AVL_FUNCTION void AvsFilter_AccessPosition3D
	(
		const avl::Position3D&	inPosition3D,
		float&	outX,	
		float&	outY,	
		float&	outZ,	
		float&	outPhi,		
		float&	outTheta,	
		float&	outPsi		
	)
	THROW_AVL_ERRORS;

} // namespace avs

#endif // AVS_CAMERACALIBRATION_H

