//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_INTEROPERABILITY_H
#define AVL_INTEROPERABILITY_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/AtlString.h"
#include "ATL/Optional.h"
#include "Geometry/Geometry.h"
#include "Geometry3D/Geometry3D.h"
#include "Point3DGrid/Point3DGrid.h"
#include "Image/Image.h"
#include "Basic/Types.h"
#include "Path/Path.h"

namespace avl
{


	/// <summary>Loads a JPG image from an array of byte values.</summary>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void LoadJpegImageFromBytes_Deprecated
	(
		const atl::Array<int>&	inBytes,
		avl::Image&				outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts an image to a byte-value array of its JPG representation.</summary>
	/// <param name="inImage">Input image.</param>
	AVL_FUNCTION void SaveJpegImageToBytes_Deprecated
	(
		const avl::Image&	inImage, 
		atl::Array<int>&	outArray
	)
	THROW_AVL_ERRORS;

	/// <summary>Loads a JPG image from a website.</summary>
	/// <param name="inLogin">Login for Basic authorization. Default value: atl::NIL.</param>
	/// <param name="inPassword">Password for Basic authorization. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void LoadImage_FromWebsite
	(
		const atl::String&					inAddress, 
		atl::Optional<const atl::String&>	inLogin,		
		atl::Optional<const atl::String&>	inPassword,	
		avl::Image&							outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Loads data from a DXF file as an image.</summary>
	/// <param name="inImageWidth">Default value: 640.</param>
	/// <param name="inImageHeight">Default value: 480.</param>
	/// <param name="inLayersToDraw">Names of layers to draw. Names of all layers are available at the 'diagFileLayersNames' output. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	/// <param name="diagFileLayersNames">Names of all layers in DXF file.</param>
	AVL_FUNCTION void LoadImage_FromDxf_Deprecated
	(
		const atl::File&								inDxfFile,
		const int										inImageWidth,
		const int										inImageHeight,
		const avl::Pixel&								inBackgroundColor,
		const atl::Optional<atl::Array<atl::String> >&	inLayersToDraw,		
		avl::Image&										outImage,
		atl::Array<atl::String>&						diagFileLayersNames = atl::Dummy< atl::Array<atl::String> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Loads data from a DXF file as an image.</summary>
	/// <param name="inScale">Scale (pixels per millimeter). Default value: 10.0f.</param>
	/// <param name="inSize">Size of the output image. Scaled entities from file will be centered on image. Default value: atl::NIL.</param>
	/// <param name="inLayersToDraw">Names of layers to draw. Names of all layers are available at the 'diagFileLayersNames' output. Default value: atl::NIL.</param>
	/// <param name="outOrigin">Location of the origin from DXF on 'outImage'.</param>
	/// <param name="outImage">Output image.</param>
	/// <param name="diagFileLayersNames">Names of all layers in DXF file.</param>
	AVL_FUNCTION void LoadImage_FromDxf
	(
		const atl::File&								inDxfFile,
		const float									inScale,			
		const atl::Optional<avl::Size>					inSize,				
		const avl::Pixel&								inBackgroundColor,
		const atl::Optional<atl::Array<atl::String> >&	inLayersToDraw,		
		avl::Point2D&									outOrigin,			
		avl::Image&										outImage,
		atl::Array<atl::String>&						diagFileLayersNames = atl::Dummy< atl::Array<atl::String> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Loads data from a DXF file as an array of paths.</summary>
	/// <param name="inCanvasWidth">Default value: 640.</param>
	/// <param name="inCanvasHeight">Default value: 480.</param>
	/// <param name="inLayers">Names of layers to import paths from. Names of all layers are available at the 'diagFileLayersNames' output. Default value: atl::NIL.</param>
	/// <param name="diagFileLayersNames">Names of all layers in DXF file.</param>
	AVL_FUNCTION void LoadEntities_FromDxf_Deprecated
	(
		const atl::File&								inDxfFile,
		const int										inCanvasWidth,
		const int										inCanvasHeight,
		const atl::Optional<atl::Array<atl::String> >&	inLayers,		
		atl::Array<atl::Array<avl::Point2D> >&			outEntities,
		atl::Array<atl::String>&						diagFileLayersNames = atl::Dummy< atl::Array<atl::String> >()	
	)
	THROW_AVL_ERRORS;

	/// <summary>Loads entities from a DXF file as an array of point arrays.</summary>
	/// <param name="inScale">Scale (pixels per millimeter). Default value: 10.0f.</param>
	/// <param name="inLayersToDraw">Names of layers to draw. Names of all layers are available at the 'diagFileLayersNames' output. Default value: atl::NIL.</param>
	/// <param name="outOrigin">Location of the origin from DXF on 'outImage'.</param>
	/// <param name="diagFileLayersNames">Names of all layers in DXF file.</param>
	AVL_FUNCTION void LoadEntities_FromDxf
	(
		const atl::File&								inDxfFile,
		const float									inScale,			
		const atl::Optional<atl::Array<atl::String> >&	inLayersToDraw,		
		avl::Point2D&									outOrigin,			
		atl::Array<atl::Array<avl::Point2D> >&			outEntities,
		atl::Array<atl::String>&						diagFileLayersNames = atl::Dummy< atl::Array<atl::String> >()	
	)
	THROW_AVL_ERRORS;

	namespace Point3DFileFormat 
	{  
		enum Type
		{
			STL,
			PLY
		};
	}


	/// <summary>Loads entities from a file of one of available types as an array of points in 3D.</summary>
	AVL_FUNCTION void LoadPoint3DGrid
	(
		const atl::File&				inFile,
		avl::Point3DFileFormat::Type	inFileFormat,
		avl::Point3DGrid&				outPoint3DGrid
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_INTEROPERABILITY_H

