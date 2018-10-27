//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_TEMPLATEMATCHING_H
#define AVL_TEMPLATEMATCHING_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/AtlString.h"
#include "ATL/Array.h"
#include "ATL/Optional.h"
#include "Geometry/Geometry.h"
#include "Image/Image.h"
#include "Path/Path.h"
#include "ComputerVision/TemplateMatching/EdgeModel.h"
#include "ComputerVision/TemplateMatching/GrayModel.h"
#include "ComputerVision/TemplateMatching/Object2D.h"

namespace avl
{


	/// <summary>Saves serialized template matching EdgeModel object as avdata file.</summary>
	/// <param name="inEdgeModel">Model to be serialized.</param>
	/// <param name="inFilename">Name of the target file.</param>
	AVL_FUNCTION void SaveEdgeModel
	(
		const avl::EdgeModel&	inEdgeModel,	
		const atl::File&			inFilename		
	)
	THROW_AVL_ERRORS;

	/// <summary>Loads serialized template matching EdgeModel object from avdata file.</summary>
	/// <param name="inFilename">Name of the source file.</param>
	/// <param name="outEdgeModel">Deserialized output model.</param>
	AVL_FUNCTION void LoadEdgeModel
	(
		const atl::File& inFilename,		
		avl::EdgeModel&	outEdgeModel	
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a model for edge-based template matching.</summary>
	/// <param name="inImage">Image from which model will be extracted.</param>
	/// <param name="inTemplateRegion">Region of the image from which model will be extracted. Default value: atl::NIL.</param>
	/// <param name="inReferenceFrame">Exact position of the model object in the image. Default value: atl::NIL.</param>
	/// <param name="inMinPyramidLevel">Defines the index of the lowest reduced resolution level used to speed up computations. Default value: 0.</param>
	/// <param name="inMaxPyramidLevel">Defines the number of reduced resolution levels used to speed up computations. Default value: atl::NIL.</param>
	/// <param name="inSmoothingStdDev">Standard deviation of the gaussian smoothing applied before edge extraction. Default value: 0.0f.</param>
	/// <param name="inEdgeThreshold">Higher threshold for edge magnitude. Default value: 35.0f.</param>
	/// <param name="inEdgeHysteresis">Threshold hysteresis value for edge magnitude. Default value: 15.0f.</param>
	/// <param name="inMinAngle">Start of range of possible rotations. Default value: -180.0f.</param>
	/// <param name="inMaxAngle">End of range of possible rotations. Default value: 180.0f.</param>
	/// <param name="inAnglePrecision">Defines angular resolution of the matching process. Default value: 1.0f.</param>
	/// <param name="inMinScale">Start of range of possible scales. Default value: 1.0f.</param>
	/// <param name="inMaxScale">End of range of possible scales. Default value: 1.0f.</param>
	/// <param name="inScalePrecision">Defines scale resolution of the matching process. Default value: 1.0f.</param>
	/// <param name="inEdgeCompleteness">Determines what fraction of the edges will be present in the created model. Default value: 1.0f.</param>
	/// <param name="outEdgeModel">Created model that can be used by LocateMultipleObjects_Edges.</param>
	/// <param name="outEdgeModelPoint">The middle point of the created model.</param>
	/// <param name="diagEdges">Visualization of the model edges found at the original resolution.</param>
	/// <param name="diagEdgePyramid">Visualization of the edges found at different resolution levels.</param>
	AVL_FUNCTION void CreateEdgeModel
	(
		const avl::Image&			inImage,				
		atl::Optional<const avl::Region&> inTemplateRegion,		
		atl::Optional<const avl::Rectangle2D&>	inReferenceFrame,	
		int							inMinPyramidLevel,		
		atl::Optional<int>			inMaxPyramidLevel,		
		float						inSmoothingStdDev,		
		float						inEdgeThreshold,		
		float						inEdgeHysteresis,		
		float						inMinAngle,				
		float						inMaxAngle,				
		float						inAnglePrecision,		
		float						inMinScale,				
		float						inMaxScale,				
		float						inScalePrecision,		
		float						inEdgeCompleteness,		
		atl::Conditional<avl::EdgeModel>&	outEdgeModel,	
		atl::Optional<atl::Conditional<avl::Point2D>&>	outEdgeModelPoint = atl::NIL,	
		atl::Conditional<atl::Array<avl::Path> >&	diagEdges = atl::Dummy< atl::Conditional<atl::Array<avl::Path> > >(),	
		atl::Conditional<atl::Array<avl::Image> >&	diagEdgePyramid = atl::Dummy< atl::Conditional<atl::Array<avl::Image> > >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds a single occurrence of a predefined template on an image by comparing object edges.</summary>
	/// <param name="inImage">Image on which object occurrence will be searched.</param>
	/// <param name="inSearchRegion">Region of possible object centers. Default value: atl::NIL.</param>
	/// <param name="inEdgeModel">Model of objects to be searched.</param>
	/// <param name="inMinPyramidLevel">Defines the lowest pyramid level at which object position is still refined. Default value: 0.</param>
	/// <param name="inMaxPyramidLevel">Defines the total number of reduced resolution levels that can be used to speed up computations. Default value: 3.</param>
	/// <param name="inEdgeThreshold">Minimum strength of edges used for matching with the model. Default value: 10.0f.</param>
	/// <param name="inIgnoreEdgePolarity">Flag indicating whether edges of negated polarity should be ignored or not. Default value: False.</param>
	/// <param name="inIgnoreBoundaryObjects">Flag indicating whether objects crossing image boundary should be ignored or not. Default value: False.</param>
	/// <param name="inMinScore">Minimum score of object candidates accepted at each pyramid level. Default value: 0.7f.</param>
	/// <param name="outObject">Found object.</param>
	/// <param name="outObjectEdges">Model edges of the found object.</param>
	/// <param name="outPyramidHeight">Highest pyramid level used to speed up computations.</param>
	/// <param name="diagEdgePyramid">Image edges used for matching at each pyramid level.</param>
	/// <param name="diagMatchPyramid">Candidate object locations found at each pyramid level.</param>
	/// <param name="diagScores">Scores of the found object at each pyramid level.</param>
	AVL_FUNCTION void LocateSingleObject_Edges
	(
		const avl::Image&					inImage,				
		atl::Optional<const avl::Region&>	inSearchRegion,			
		const avl::EdgeModel&				inEdgeModel,			
		int									inMinPyramidLevel,		
		atl::Optional<int>					inMaxPyramidLevel,		
		float							inEdgeThreshold,		
		bool								inIgnoreEdgePolarity,	
		bool								inIgnoreBoundaryObjects,
		float							inMinScore,				
		atl::Conditional<avl::Object2D>&	outObject,				
		atl::Optional<atl::Conditional<atl::Array<avl::Path>>&>	outObjectEdges = atl::NIL,
		atl::Optional<int&>					outPyramidHeight = atl::NIL, 
		atl::Array<avl::Image>&				diagEdgePyramid = atl::Dummy< atl::Array<avl::Image> >(),		
		atl::Array<avl::Image>&				diagMatchPyramid = atl::Dummy< atl::Array<avl::Image> >(),		
		atl::Conditional<atl::Array<float> >&	diagScores = atl::Dummy< atl::Conditional<atl::Array<float> > >()		
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds all occurrences of a predefined template on an image by comparing object edges.</summary>
	/// <param name="inImage">Image on which object occurrences will be searched.</param>
	/// <param name="inSearchRegion">Region of possible object centers. Default value: atl::NIL.</param>
	/// <param name="inEdgeModel">Model of objects to be searched.</param>
	/// <param name="inMinPyramidLevel">Defines the lowest pyramid level at which object position is still refined. Default value: 0.</param>
	/// <param name="inMaxPyramidLevel">Defines the total number of reduced resolution levels that can be used to speed up computations. Default value: 3.</param>
	/// <param name="inEdgeThreshold">Minimum strength of edges used for matching with the model. Default value: 10.0f.</param>
	/// <param name="inIgnoreEdgePolarity">Flag indicating whether edges of negated polarity should be ignored or not. Default value: False.</param>
	/// <param name="inIgnoreBoundaryObjects">Flag indicating whether objects crossing image boundary should be ignored or not. Default value: False.</param>
	/// <param name="inMinScore">Minimum score of object candidates accepted at each pyramid level. Default value: 0.7f.</param>
	/// <param name="inMinDistance">Minimum distance between two found objects. Default value: 10.0f.</param>
	/// <param name="outObjects">Found objects.</param>
	/// <param name="outObjectEdges">Model edges of the found objects.</param>
	/// <param name="outPyramidHeight">Highest pyramid level used to speed up computations.</param>
	/// <param name="diagEdgePyramid">Image edges used for matching at each pyramid level.</param>
	/// <param name="diagMatchPyramid">Candidate object locations found at each pyramid level.</param>
	/// <param name="diagScores">Scores of the found objects at each pyramid level.</param>
	AVL_FUNCTION void LocateMultipleObjects_Edges
	(
		const avl::Image&			inImage,					
		atl::Optional<const avl::Region&> inSearchRegion,		
		const avl::EdgeModel&			inEdgeModel,			
		int								inMinPyramidLevel,		
		atl::Optional<int>				inMaxPyramidLevel,		
		float						inEdgeThreshold,		
		bool							inIgnoreEdgePolarity,	
		bool							inIgnoreBoundaryObjects,
		float						inMinScore,				
		float						inMinDistance,			
		atl::Array<avl::Object2D>&		outObjects,				
		atl::Optional<atl::Array<atl::Array<avl::Path>>&>	outObjectEdges = atl::NIL,	
		atl::Optional<int&>				outPyramidHeight = atl::NIL, 
		atl::Array<avl::Image>&			diagEdgePyramid = atl::Dummy< atl::Array<avl::Image> >(),		
		atl::Array<avl::Image>&			diagMatchPyramid = atl::Dummy< atl::Array<avl::Image> >(),		
		atl::Array<atl::Array<float> >&	diagScores = atl::Dummy< atl::Array<atl::Array<float> > >()			
	)
	THROW_AVL_ERRORS;

	/// <summary>Saves serialized template matching GrayModel object as avdata file.</summary>
	/// <param name="inGrayModel">Model to be serialized.</param>
	/// <param name="inFilename">Name of the target file.</param>
	AVL_FUNCTION void SaveGrayModel
	(
		const avl::GrayModel&	inGrayModel,	
		const atl::File&		inFilename		
	)
	THROW_AVL_ERRORS;

	/// <summary>Loads serialized template matching GrayModel object from avdata file.</summary>
	/// <param name="inFilename">Name of the source file.</param>
	/// <param name="outGrayModel">Deserialized output model.</param>
	AVL_FUNCTION void LoadGrayModel
	(
		const atl::File& inFilename,	
		avl::GrayModel&	outGrayModel	
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a model for NCC or SAD template matching.</summary>
	/// <param name="inImage">Image from which model will be extracted.</param>
	/// <param name="inTemplateRegion">Region of the image from which model will be extracted. Default value: atl::NIL.</param>
	/// <param name="inReferenceFrame">Exact position of the model object in the image. Default value: atl::NIL.</param>
	/// <param name="inMinPyramidLevel">Defines the index of the lowest reduced resolution level used to speed up computations. Default value: 0.</param>
	/// <param name="inMaxPyramidLevel">Defines the number of reduced resolution levels used to speed up computations. Default value: atl::NIL.</param>
	/// <param name="inMinAngle">Start of range of possible rotations. Default value: 0.0f.</param>
	/// <param name="inMaxAngle">End of range of possible rotations. Default value: 0.0f.</param>
	/// <param name="inAnglePrecision">Defines angular resolution of the matching process. Default value: 1.0f.</param>
	/// <param name="inMinScale">Start of range of possible scales. Default value: 1.0f.</param>
	/// <param name="inMaxScale">End of range of possible scales. Default value: 1.0f.</param>
	/// <param name="inScalePrecision">Defines scale resolution of the matching process. Default value: 1.0f.</param>
	/// <param name="outGrayModel">Created model that can be used by LocateMultipleObjects_NCC and LocateMultipleObjects_SAD filters.</param>
	/// <param name="outGrayModelPoint">The middle point of the created model.</param>
	/// <param name="diagTemplatePyramid">Visualization of the model at different resolution levels.</param>
	AVL_FUNCTION void CreateGrayModel
	(
		const avl::Image&			inImage,				
		atl::Optional<const avl::Region&> inTemplateRegion,	
		atl::Optional<const avl::Rectangle2D&>	inReferenceFrame,	
		int							inMinPyramidLevel,		
		atl::Optional<int>			inMaxPyramidLevel,		
		float					inMinAngle,				
		float					inMaxAngle,				
		float					inAnglePrecision,		
		float					inMinScale,				
		float					inMaxScale,				
		float					inScalePrecision,		
		avl::GrayModel&				outGrayModel,			
		atl::Optional<avl::Point2D&>	outGrayModelPoint = atl::NIL,	
		atl::Array<avl::Image>&		diagTemplatePyramid = atl::Dummy< atl::Array<avl::Image> >()		
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds a single occurrence of a predefined template on an image by analysing the normalized correlation between pixel values.</summary>
	/// <param name="inImage">Image on which object occurrence will be searched.</param>
	/// <param name="inSearchRegion">Range of possible object centers. Default value: atl::NIL.</param>
	/// <param name="inGrayModel">Model of objects to be searched.</param>
	/// <param name="inMinPyramidLevel">Defines the lowest pyramid level at which object position is still refined. Default value: 0.</param>
	/// <param name="inMaxPyramidLevel">Defines the total number of reduced resolution levels that can be used to speed up computations. Default value: 3.</param>
	/// <param name="inIgnoreBoundaryObjects">Flag indicating whether objects crossing image boundary should be ignored or not. Default value: False.</param>
	/// <param name="inMinScore">Minimum score of object candidates accepted at each pyramid level. Default value: 0.7f.</param>
	/// <param name="inMaxBrightnessRatio">Defines the maximal deviation of the mean brightness of the model object and the object present in the image. Default value: atl::NIL.</param>
	/// <param name="inMaxContrastRatio">Defines the maximal deviation of the brightness standard deviation of the model object and the object present in the image. Default value: atl::NIL.</param>
	/// <param name="outObject">Found object.</param>
	/// <param name="outPyramidHeight">Highest pyramid level used to speed up computations.</param>
	/// <param name="diagImagePyramid">Pyramid of iteratively downsampled input image.</param>
	/// <param name="diagMatchPyramid">Candidate object locations found at each pyramid level.</param>
	/// <param name="diagScores">Scores of the found object at each pyramid level.</param>
	AVL_FUNCTION void LocateSingleObject_NCC
	(
		const avl::Image&					inImage,			
		atl::Optional<const avl::Region&>	inSearchRegion,		
		const avl::GrayModel&				inGrayModel,		
		int									inMinPyramidLevel,	
		atl::Optional<int>					inMaxPyramidLevel,	
		bool								inIgnoreBoundaryObjects,
		float								inMinScore,			
		atl::Optional<float>				inMaxBrightnessRatio,	
		atl::Optional<float>				inMaxContrastRatio,	
		atl::Conditional<avl::Object2D>&	outObject,			
		atl::Optional<int&>					outPyramidHeight = atl::NIL, 
		atl::Array<avl::Image>&				diagImagePyramid = atl::Dummy< atl::Array<avl::Image> >(),	
		atl::Array<avl::Image>&				diagMatchPyramid = atl::Dummy< atl::Array<avl::Image> >(),	
		atl::Conditional<atl::Array<float> >&	diagScores = atl::Dummy< atl::Conditional<atl::Array<float> > >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds all occurrences of a predefined template on an image by analysing the normalized correlation between pixel values.</summary>
	/// <param name="inImage">Image on which model occurrences will be searched.</param>
	/// <param name="inSearchRegion">Range of possible object centers. Default value: atl::NIL.</param>
	/// <param name="inGrayModel">Model of objects to be searched.</param>
	/// <param name="inMinPyramidLevel">Defines the lowest pyramid level at which object position is still refined. Default value: 0.</param>
	/// <param name="inMaxPyramidLevel">Defines the total number of reduced resolution levels that can be used to speed up computations. Default value: 3.</param>
	/// <param name="inIgnoreBoundaryObjects">Flag indicating whether objects crossing image boundary should be ignored or not. Default value: False.</param>
	/// <param name="inMinScore">Minimum score of object candidates accepted at each pyramid level. Default value: 0.7f.</param>
	/// <param name="inMinDistance">Minimum distance between two found objects. Default value: 10.0f.</param>
	/// <param name="inMaxBrightnessRatio">Defines the maximal deviation of the mean brightness of the model object and the object present in the image. Default value: atl::NIL.</param>
	/// <param name="inMaxContrastRatio">Defines the maximal deviation of the brightness standard deviation of the model object and the object present in the image. Default value: atl::NIL.</param>
	/// <param name="outObjects">Found objects.</param>
	/// <param name="outPyramidHeight">Highest pyramid level used to speed up computations.</param>
	/// <param name="diagImagePyramid">Pyramid of iteratively downsampled input image.</param>
	/// <param name="diagMatchPyramid">Candidate object locations found at each pyramid level.</param>
	/// <param name="diagScores">Scores of the found objects at each pyramid level.</param>
	AVL_FUNCTION void LocateMultipleObjects_NCC
	(
		const avl::Image&				inImage,				
		atl::Optional<const avl::Region&>	inSearchRegion,		
		const avl::GrayModel&			inGrayModel,			
		int								inMinPyramidLevel,		
		atl::Optional<int>				inMaxPyramidLevel,		
		bool							inIgnoreBoundaryObjects,
		float							inMinScore,				
		float							inMinDistance,			
		atl::Optional<float>			inMaxBrightnessRatio,	
		atl::Optional<float>			inMaxContrastRatio,		
		atl::Array<avl::Object2D>&		outObjects,				
		atl::Optional<int&>				outPyramidHeight = atl::NIL, 
		atl::Array<avl::Image>&			diagImagePyramid = atl::Dummy<atl::Array<avl::Image> >(), 
		atl::Array<avl::Image>&			diagMatchPyramid = atl::Dummy<atl::Array<avl::Image> >(), 
		atl::Array<atl::Array<float> >&	diagScores = atl::Dummy<atl::Array<atl::Array<float> > >() 
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds a single occurrence of a predefined template on an image by analysing the Square Average Difference between pixel values.</summary>
	/// <param name="inImage">Image on which model occurrence will be searched.</param>
	/// <param name="inSearchRegion">Possible centers of the object occurrence. Default value: atl::NIL.</param>
	/// <param name="inGrayModel">Model which will be sought.</param>
	/// <param name="inMinPyramidLevel">Defines the highest resolution level. Default value: 0.</param>
	/// <param name="inMaxPyramidLevel">Defines the number of reduced resolution levels that can be used to speed up computations. Default value: 3.</param>
	/// <param name="inIgnoreBoundaryObjects">Flag indicating whether objects crossing image boundary should be ignored or not. Default value: False.</param>
	/// <param name="inMaxDifference">Maximum accepted average difference between pixel values. Default value: 0.0f.</param>
	/// <param name="outObject">Found object.</param>
	/// <param name="outPyramidHeight">Highest pyramid level used to speed up computations.</param>
	/// <param name="diagImagePyramid">Pyramid of iteratively downsampled input image.</param>
	/// <param name="diagMatchPyramid">Locations found on each pyramid level.</param>
	/// <param name="diagScores">Scores of found match on each pyramid level.</param>
	AVL_FUNCTION void LocateSingleObject_SAD
	(
		const avl::Image&					inImage,			
		atl::Optional<const avl::Region&>	inSearchRegion,		
		const avl::GrayModel&				inGrayModel,		
		int									inMinPyramidLevel,	
		atl::Optional<int>					inMaxPyramidLevel,	
		bool								inIgnoreBoundaryObjects,
		float								inMaxDifference,	
		atl::Conditional<avl::Object2D>&	outObject,			
		atl::Optional<int&>					outPyramidHeight = atl::NIL, 
		atl::Array<avl::Image>&				diagImagePyramid = atl::Dummy< atl::Array<avl::Image> >(),	
		atl::Array<avl::Image>&				diagMatchPyramid = atl::Dummy< atl::Array<avl::Image> >(),	
		atl::Conditional<atl::Array<float> >&	diagScores = atl::Dummy< atl::Conditional<atl::Array<float> > >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds multiple occurrences of a predefined template on an image by analysing the Square Average Difference between pixel values.</summary>
	/// <param name="inImage">Image on which model occurrences will be searched.</param>
	/// <param name="inSearchRegion">Possible centers of the object occurrences. Default value: atl::NIL.</param>
	/// <param name="inGrayModel">Model which will be sought.</param>
	/// <param name="inMinPyramidLevel">Defines the highest resolution level. Default value: 0.</param>
	/// <param name="inMaxPyramidLevel">Defines the number of reduced resolution levels that can be used to speed up computations. Default value: 3.</param>
	/// <param name="inIgnoreBoundaryObjects">Flag indicating whether objects crossing image boundary should be ignored or not. Default value: False.</param>
	/// <param name="inMaxDifference">Maximum accepted average difference between pixel values. Default value: 5.0f.</param>
	/// <param name="inMinDistance">Minimum distance between two matches. Default value: 10.0f.</param>
	/// <param name="outObjects">Found objects.</param>
	/// <param name="outPyramidHeight">Highest pyramid level used to speed up computations.</param>
	/// <param name="diagImagePyramid">Pyramid of iteratively downsampled input image.</param>
	/// <param name="diagMatchPyramid">Locations found on each pyramid level.</param>
	/// <param name="diagScores">Scores of found matches on each pyramid level.</param>
	AVL_FUNCTION void LocateMultipleObjects_SAD
	(
		const avl::Image&			inImage,			
		atl::Optional<const avl::Region&>	inSearchRegion,		
		const avl::GrayModel&		inGrayModel,		
		int							inMinPyramidLevel,	
		atl::Optional<int>			inMaxPyramidLevel,	
		bool						inIgnoreBoundaryObjects,
		float						inMaxDifference,	
		float						inMinDistance,		
		atl::Array<avl::Object2D>&	outObjects,			
		atl::Optional<int&>			outPyramidHeight = atl::NIL, 
		atl::Array<avl::Image>&		diagImagePyramid = atl::Dummy<atl::Array<avl::Image>>(), 
		atl::Array<avl::Image>&		diagMatchPyramid = atl::Dummy<atl::Array<avl::Image>>(), 
		atl::Array<atl::Array<float> >&	diagScores = atl::Dummy<atl::Array<atl::Array<float> >>() 
	)
	THROW_AVL_ERRORS;

	/// <summary>Combines results from multiple LocateSingleObject instances.</summary>
	/// <param name="inMinScore">Default value: 0.0f.</param>
	AVL_FUNCTION void MergeLocationResults_Single
	(
		const atl::Conditional<avl::Object2D>&	inObject1,
		const atl::Conditional<avl::Object2D>&	inObject2,
		const atl::Conditional<avl::Object2D>&	inObject3,
		const atl::Conditional<avl::Object2D>&	inObject4,
		float								inMinScore,
		atl::Conditional<avl::Object2D>&		outObject,
		atl::Conditional<int>&					outIndex
	)
	THROW_AVL_ERRORS;

	/// <summary>Combines results from multiple LocateMultipleObject instances.</summary>
	/// <param name="inMinDistance">Default value: 10.0f.</param>
	/// <param name="inMinScore">Default value: 0.0f.</param>
	AVL_FUNCTION void MergeLocationResults_Multiple
	(
		const atl::Array<avl::Object2D>&	inObjects1,
		const atl::Array<avl::Object2D>&	inObjects2,
		const atl::Array<avl::Object2D>&	inObjects3,
		const atl::Array<avl::Object2D>&	inObjects4,
		float							inMinDistance,
		float							inMinScore,
		atl::Array<avl::Object2D>&			outObjects,
		atl::Array<int>&					outIndices
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_TEMPLATEMATCHING_H

