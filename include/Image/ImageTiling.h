//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_IMAGETILING_H
#define AVL_IMAGETILING_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Image/Image.h"
#include "Image/ImageFormat.h"

namespace avl
{


	/// <summary>Generates array of Boxes, which divide image in, potentially overlapping, tiles.</summary>
	/// <param name="inImageFormat">Format of image for which tiles will be produced.</param>
	/// <param name="inTileWidth">Demanded tile width. Default value: 1.</param>
	/// <param name="inTileHeight">Demanded tile height; equals inTileWidth when set to Auto. Default value: atl::NIL.</param>
	/// <param name="inHorizontalStep">Defines horizontal space between consecutive tiles; defaults to tile width. Can be used to produce overlapping tiles. Default value: atl::NIL.</param>
	/// <param name="inVerticalStep">Defines vertical space between consecutive tiles; defaults to tile height. Can be used to produce overlapping tiles. Default value: atl::NIL.</param>
	/// <param name="inOverflowControl">When set to true, overflowing tiles will be removed form outTiles array. Default value: False.</param>
	/// <param name="outTiles">Array containing produced tiles.</param>
	/// <param name="outRowCount">Number of generated tiles rows.</param>
	/// <param name="outColumnCount">Number of generated tiles per row.</param>
	AVL_FUNCTION void CreateImageTiles_AsBoxes
	(
		const avl::ImageFormat&			inImageFormat,			
		const int						inTileWidth,			
		atl::Optional<int>				inTileHeight,			
		atl::Optional<int>				inHorizontalStep,		
		atl::Optional<int>				inVerticalStep,			
		const bool						inOverflowControl,		
		atl::Array<avl::Box>&			outTiles,				
		int&							outRowCount,			
		int&							outColumnCount			
	)
	THROW_AVL_ERRORS;

	/// <summary>Generates array of Regions, which divide image in, potentially overlapping, tiles.</summary>
	/// <param name="inImageFormat">Format of image for which tiles will be produced.</param>
	/// <param name="inTileWidth">Demanded tile width. Default value: 1.</param>
	/// <param name="inTileHeight">Demanded tile height; equals inTileWidth when set to Auto. Default value: atl::NIL.</param>
	/// <param name="inHorizontalStep">Defines horizontal space between consecutive tiles; defaults to tile width. Can be used to produce overlapping tiles. Default value: atl::NIL.</param>
	/// <param name="inVerticalStep">Defines vertical space between consecutive tiles; defaults to tile height. Can be used to produce overlapping tiles. Default value: atl::NIL.</param>
	/// <param name="inOverflowControl">When set to true, overflowing tiles will be removed form outTiles array. Default value: False.</param>
	/// <param name="outTiles">Array containing produced tiles.</param>
	/// <param name="outRowCount">Number of generated tiles rows.</param>
	/// <param name="outColumnCount">Number of generated tiles per row.</param>
	AVL_FUNCTION void CreateImageTiles_AsRegions
	(
		const avl::ImageFormat&			inImageFormat,			
		const int						inTileWidth,			
		atl::Optional<int>				inTileHeight,			
		atl::Optional<int>				inHorizontalStep,		
		atl::Optional<int>				inVerticalStep,			
		const bool						inOverflowControl,		
		atl::Array<avl::Region>&		outTiles,				
		int&							outRowCount,			
		int&							outColumnCount			
	)
	THROW_AVL_ERRORS;

	/// <summary>Generates array of image tiles, which are cut from inImage.</summary>
	/// <param name="inImage">Image to be cut into tiles.</param>
	/// <param name="inTileWidth">Demanded tile width. Default value: 1.</param>
	/// <param name="inTileHeight">Demanded tile height; equals inTileWidth when set to Auto. Default value: atl::NIL.</param>
	/// <param name="inHorizontalStep">Defines horizontal space between consecutive tiles; defaults to tile width. Can be used to produce overlapping tiles. Default value: atl::NIL.</param>
	/// <param name="inVerticalStep">Defines vertical space between consecutive tiles; defaults to tile height. Can be used to produce overlapping tiles. Default value: atl::NIL.</param>
	/// <param name="inOverflowControl">When set to true, overflowing tiles will be removed form outTiles array.</param>
	/// <param name="outImageTiles">Resulting image tiles.</param>
	AVL_FUNCTION void CutImageIntoTiles
	(
		const avl::Image&					inImage,				
		const int							inTileWidth,			
		atl::Optional<int>					inTileHeight,			
		atl::Optional<int>					inHorizontalStep,		
		atl::Optional<int>					inVerticalStep,			
		const bool							inOverflowControl,		
		atl::Array<avl::Image>&				outImageTiles			
	)
	THROW_AVL_ERRORS;

	/// <summary>Joins previously cut tiles into single image.</summary>
	/// <param name="inImages">Array of image tiles.</param>
	/// <param name="inRowCount">Defines how many output image rows there are in inImages.</param>
	/// <param name="inColumnCount">Defines how many images builds one row in inImages.</param>
	/// <param name="outJoinedImage">Glued image.</param>
	AVL_FUNCTION void JoinImageTiles
	(
		const atl::Array<avl::Image>&	inImages,		
		const int						inRowCount,		
		const int						inColumnCount,	
		avl::Image&						outJoinedImage	
	)
	THROW_AVL_ERRORS;

	struct EnumerateImageTilesState : BaseState
	{
		EnumerateImageTilesState() {};
		avl::Location currentLoc;
		avl::Location endTileForward;
		avl::Location endTileBackward;
		int tileHeight;
		int tileWidth;
		bool heightOverflow;
		bool widthOverflow;
	};


	/// <summary>Enumerates tiles from image.</summary>
	/// <param name="inImage">Image to be enumerated.</param>
	/// <param name="inTileWidth">Tile width. Default value: 1.</param>
	/// <param name="inTileHeight">Tile height. Default value: atl::NIL.</param>
	/// <param name="inOverflowControl">Allow overflow.</param>
	AVL_FUNCTION bool EnumerateImageTiles
	(
		EnumerateImageTilesState&	ioState,
		const avl::Image&			inImage,
		int							inTileWidth,	
		atl::Optional<int>			inTileHeight, 
		bool						inOverflowControl, 
		avl::Image&					outTile,
		avl::Box&					diagTilePosition = atl::Dummy<avl::Box>()
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_IMAGETILING_H

