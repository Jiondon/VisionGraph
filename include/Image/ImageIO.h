//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVS_IMAGEIO_H
#define AVS_IMAGEIO_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/AtlString.h"
#include "Image/Image.h"
#include "AVLCommon/BaseState.h"
#include "AVLCommon/Enums/FileSortingOrder.h"
#include "Enums/TiffImageCompressionScheme.h"
#include "Enums/ImageFileFormat.h"
#include "System/EnumerateFilesState.h"
#include "System/ByteBuffer.h"
#include "SaveImageStateImplBase.h"

namespace avl
{


	#pragma push_macro("LoadImage")
	#undef LoadImage


	/// <summary>Loads a single image from a file.</summary>
	/// <param name="inFile">Path to a file.</param>
	/// <param name="inLoadAlphaChannel">Whether to load the alpha channel (if exists) as an additional image channel.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void LoadImage
	(
		const atl::File&				inFile,				
		bool							inLoadAlphaChannel,	
		avl::Image&						outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Loads a single image from a file stored in memory.</summary>
	/// <param name="inBuffer">Source buffer containing image file data.</param>
	/// <param name="inOffset">Image data start position in source buffer. Default value: 0.</param>
	/// <param name="inLength">Image data length in source buffer. Default value: atl::NIL.</param>
	/// <param name="inLoadAlphaChannel">Whether to load the alpha channel (if exists) as an additional image channel.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION void LoadImageFromBuffer
	(
		const avl::ByteBuffer&	inBuffer,				
		int						inOffset,				
		atl::Optional<int>		inLength,				
		bool					inLoadAlphaChannel,		
		avl::Image&				outImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Scans a disk directory for image files and then returns the images one by one in consecutive iterations.</summary>
	/// <param name="inDirectory">Input directory.</param>
	/// <param name="inFileType">File format of the images. Default value: atl::NIL.</param>
	/// <param name="inSortingOrder">Sorting order.</param>
	/// <param name="inRepeat">Determines whether to repeat reading directory after reading all files.</param>
	/// <param name="inProcessSubdirectories">Flag indicating whether to load images from the subdirectories or not.</param>
	/// <param name="inInvert">Flag indicating whether to enumerate images backwards or not.</param>
	/// <param name="inLoadAlphaChannel">Flag indicating whether to load alpha channel of the image or not.</param>
	/// <param name="outImage">Output image.</param>
	/// <param name="outFilePath">Output file path.</param>
	/// <param name="outFileName">Output file name.</param>
	AVL_FUNCTION bool EnumerateImages
	(
		EnumerateFilesState&						ioState,
		const atl::Directory&						inDirectory,	
		atl::Optional<avl::ImageFileFormat::Type>	inFileType,		
		avl::FileSortingOrder::Type					inSortingOrder,	
		bool										inRepeat,		
		bool										inProcessSubdirectories,	
		bool										inInvert,		
		bool										inLoadAlphaChannel,	
		avl::Image&									outImage,		
		atl::File&									outFilePath,	
		atl::String&								outFileName		
	)
	THROW_AVL_ERRORS;

	/// <summary>Simulates capturing a frame from a camera.</summary>
	/// <param name="inDirectory">Input directory.</param>
	/// <param name="inFileType">File format of the images. Default value: atl::NIL.</param>
	/// <param name="inSortingOrder">Sorting order.</param>
	/// <param name="inRepeat">Determines whether to repeat reading directory after reading all files.</param>
	/// <param name="inProcessSubdirectories">Flag indicating whether to load images from the subdirectories or not.</param>
	/// <param name="inInvert">Flag indicating whether to enumerate images backwards or not.</param>
	/// <param name="inLoadAlphaChannel">Flag indicating whether to load alpha channel of the image or not.</param>
	/// <param name="outImage">Output image.</param>
	/// <param name="outFilePath">Output file path.</param>
	/// <param name="outFileName">Output file name.</param>
	AVL_FUNCTION bool GrabImage_FromFiles
	(
		const atl::Directory&						inDirectory,	
		atl::Optional<avl::ImageFileFormat::Type>	inFileType,		
		avl::FileSortingOrder::Type					inSortingOrder,	
		bool										inRepeat,		
		bool										inProcessSubdirectories,	
		bool										inInvert,		
		bool										inLoadAlphaChannel,	
		avl::Image&									outImage,		
		atl::File&									outFilePath,	
		atl::String&								outFileName		
	)
	THROW_AVL_ERRORS;

	/// <summary>Resets global state of GrabImage_FromFiles filter</summary>
	AVL_FUNCTION void GrabImage_FromFiles_ResetState
	(
	)
	THROW_AVL_ERRORS;

	#ifndef __INTELLISENSE__

	// don't use this function. it's just a work-around for problem with LoadImage macro defined in WinUser.h. use avl::LoadImage().
	inline void LoadImageA
	(
		const atl::File& inFile,
		bool inLoadAlphaChannel,
		Image& outImage
	)
	{
		avl::LoadImage(inFile, inLoadAlphaChannel, outImage);
	}

	// don't use this function. it's just a work-around for problem with LoadImage macro defined in WinUser.h. use avl::LoadImage().
	inline void LoadImageW
	(
		const atl::File& inFile, 
		bool inLoadAlphaChannel,
		Image& outImage
	)
	{
		avl::LoadImage(inFile, inLoadAlphaChannel, outImage);
	}	

	#endif // __INTELLISENSE__

	#pragma pop_macro("LoadImage")


	struct SaveImageState : public BaseState
	{
	public:
		SaveImageState()
		{
			impl = pImpl_helpers::CreateSaveImageStateImpl();
		}
		~SaveImageState()
		{
			delete impl;
		}
		SaveImageStateImplBase* Impl()
		{
			return impl;
		}

	private:
		SaveImageState(const SaveImageState&);// = delete;
		SaveImageState(SaveImageState&&);// = delete;
		SaveImageState& operator=(const SaveImageState&);// = delete;
		SaveImageState& operator=(SaveImageState&&);// = delete;

	private:
		SaveImageStateImplBase* impl;
	};


	/// <summary>Saves an image to a file.</summary>
	/// <param name="inImage">An image to be saved.</param>
	/// <param name="inImageFileFormat">If Nil the format will be chosen on the basis of extension. Default value: atl::NIL.</param>
	/// <param name="inFile">Path to a file.</param>
	/// <param name="inIgnoreErrors">Switches to re-trying and canceling in case of errors (e.g. when the disk is full).</param>
	AVL_FUNCTION void SaveImage
	(
		const avl::Image&							inImage,					
		atl::Optional<avl::ImageFileFormat::Type>	inImageFileFormat,			
		const atl::File&							inFile,						
		bool										inIgnoreErrors = false		
	)
	THROW_AVL_ERRORS;

	/// <summary>Saves an image to a file in the background thread.</summary>
	/// <param name="ioState">State containing information about asynchronous execution.</param>
	/// <param name="inImage">An image to be saved.</param>
	/// <param name="inImageFileFormat">If Nil the format will be chosen on the basis of extension. Default value: atl::NIL.</param>
	/// <param name="inFile">Path to a file.</param>
	AVL_FUNCTION void SaveImage_Asynchronous
	(
		SaveImageState&								ioState,			
		const avl::Image&							inImage,			
		atl::Optional<avl::ImageFileFormat::Type>	inImageFileFormat,	
		const atl::File&							inFile				
	)
	THROW_AVL_ERRORS;

	/// <summary>Saves an image to a file stored in memory.</summary>
	/// <param name="inImage">An image to be saved.</param>
	/// <param name="inImageFileFormat">Image file format.</param>
	/// <param name="outBuffer">Buffer containing image file data.</param>
	AVL_FUNCTION void SaveImageToBuffer
	(
		const avl::Image&			inImage,			
		avl::ImageFileFormat::Type	inImageFileFormat,	
		avl::ByteBuffer&			outBuffer			
	)
	THROW_AVL_ERRORS;

	/// <summary>Saves an image to a JPEG file.</summary>
	/// <param name="inImage">An image to be saved.</param>
	/// <param name="inFile">Path to a file.</param>
	/// <param name="inQuality">Quality. Default value: atl::NIL.</param>
	/// <param name="inIgnoreErrors">Switches to re-trying and canceling in case of errors (e.g. when the disk is full).</param>
	AVL_FUNCTION void SaveImageToJpeg
	(
		const avl::Image&							inImage,			
		const atl::File&							inFile,				
		atl::Optional<int>							inQuality,			
		bool										inIgnoreErrors		
	)
	THROW_AVL_ERRORS;

	/// <summary>Saves an image to a JPEG file in the background thread.</summary>
	/// <param name="ioState">State containing information about asynchronous execution.</param>
	/// <param name="inImage">An image to be saved.</param>
	/// <param name="inFile">Path to a file.</param>
	/// <param name="inQuality">Quality. Default value: atl::NIL.</param>
	AVL_FUNCTION void SaveImageToJpeg_Asynchronous
	(
		SaveImageState&								ioState,			
		const avl::Image&							inImage,			
		const atl::File&							inFile,				
		atl::Optional<int>							inQuality			
	)
	THROW_AVL_ERRORS;

	/// <summary>Saves an image to a PNG file.</summary>
	/// <param name="inImage">An image to be saved.</param>
	/// <param name="inFile">Path to a file.</param>
	/// <param name="inCompressionLevel">Compression level. Default value: atl::NIL.</param>
	/// <param name="inIgnoreErrors">Switches to re-trying and canceling in case of errors (e.g. when the disk is full).</param>
	AVL_FUNCTION void SaveImageToPng
	(
		const avl::Image&							inImage,			
		const atl::File&							inFile,				
		atl::Optional<int>							inCompressionLevel,	
		bool										inIgnoreErrors		
	)
	THROW_AVL_ERRORS;

	/// <summary>Saves an image to a PNG file in the background thread.</summary>
	/// <param name="ioState">State containing information about asynchronous execution.</param>
	/// <param name="inImage">An image to be saved.</param>
	/// <param name="inFile">Path to a file.</param>
	/// <param name="inCompressionLevel">Compression level. Default value: atl::NIL.</param>
	AVL_FUNCTION void SaveImageToPng_Asynchronous
	(
		SaveImageState&								ioState,			
		const avl::Image&							inImage,			
		const atl::File&							inFile,				
		atl::Optional<int>							inCompressionLevel	
	)
	THROW_AVL_ERRORS;

	/// <summary>Saves an image to a TIFF file.</summary>
	/// <param name="inImage">An image to be saved.</param>
	/// <param name="inFile">Path to a file.</param>
	/// <param name="inCompressionScheme">Compression scheme. Default value: atl::NIL.</param>
	/// <param name="inJpegQuality">Quality - used only for JPEG compression scheme. Default value: atl::NIL.</param>
	/// <param name="inIgnoreErrors">Switches to re-trying and canceling in case of errors (e.g. when the disk is full).</param>
	AVL_FUNCTION void SaveImageToTiff
	(
		const avl::Image&										inImage,				
		const atl::File&										inFile,					
		atl::Optional<avl::TiffImageCompressionScheme::Type>	inCompressionScheme,	
		atl::Optional<int>										inJpegQuality,			
		bool													inIgnoreErrors			
	)
	THROW_AVL_ERRORS;

	/// <summary>Saves an image to a TIFF file in the background thread.</summary>
	/// <param name="ioState">State containing information about asynchronous execution.</param>
	/// <param name="inImage">An image to be saved.</param>
	/// <param name="inFile">Path to a file.</param>
	/// <param name="inCompressionScheme">Compression scheme. Default value: atl::NIL.</param>
	/// <param name="inJpegQuality">Quality (0-100) - used only for JPEG compression scheme. Default value: atl::NIL.</param>
	AVL_FUNCTION void SaveImageToTiff_Asynchronous
	(
		SaveImageState&											ioState,				
		const avl::Image&										inImage,				
		const atl::File&										inFile,					
		atl::Optional<avl::TiffImageCompressionScheme::Type>	inCompressionScheme,	
		atl::Optional<int>										inJpegQuality			
	)
	THROW_AVL_ERRORS;

	class InputVideoStream;
	class InputVideoStreamImpl;

	namespace pImpl_helpers
	{
		/* For internal use only */
		AVL_FUNCTION void DestructInputVideoStream(InputVideoStream&);
	}

	class InputVideoStream : public avl::BaseState
	{
	public:
		InputVideoStream() : pImpl(0)
		{}

		~InputVideoStream()
		{
			pImpl_helpers::DestructInputVideoStream(*this);
		}

		InputVideoStreamImpl* pImpl;

	private:
		InputVideoStream(const InputVideoStream&);
		InputVideoStream& operator=(const InputVideoStream&);
	};


	class OutputVideoStream;
	class OutputVideoStreamImpl;

	namespace pImpl_helpers
	{
		/* For internal use only */
		AVL_FUNCTION void DestructOutputVideoStream(OutputVideoStream&);
	}

	class OutputVideoStream : public avl::BaseState
	{
	public:
		OutputVideoStream() : pImpl(0)
		{}

		~OutputVideoStream()
		{
			pImpl_helpers::DestructOutputVideoStream(*this);
		}

		OutputVideoStreamImpl* pImpl;

	private:
		OutputVideoStream(const OutputVideoStream&);
		OutputVideoStream& operator=(const OutputVideoStream&);
	};


	namespace VideoEncoder
	{
		enum Type
		{
			Cinepak,
			FFDShow,
			Xvid
		};
	}

	typedef atl::String VideoEncoderName;




	/// <summary>Opens and creates a video stream from a file.</summary>
	/// <param name="inFile">Video file.</param>
	/// <param name="inStartFrame">Number of first frame to fetch.</param>
	/// <param name="outInputVideoStream">Initialized input video stream.</param>
	/// <param name="outFPS">Frames per second.</param>
	/// <param name="outMaxFrame">Last frame number.</param>
	AVL_FUNCTION void OpenInputVideoStream
	(
		const atl::File&	inFile,				
		int					inStartFrame,		
		avl::InputVideoStream&	outInputVideoStream,
		float&			outFPS,				
		int&				outMaxFrame			
	)
	THROW_AVL_ERRORS;

	/// <summary>Acquires frame from the previously opened video stream.</summary>
	/// <param name="inInputVideoStream">Previously opened input video stream.</param>
	/// <param name="inRepeat">Determines whether to repeat video playback.</param>
	/// <param name="outFrameNum">Current frame number.</param>
	/// <param name="outImage">Current frame.</param>
	AVL_FUNCTION bool ReadVideoStream
	(
		const avl::InputVideoStream&	inInputVideoStream, 
		bool							inRepeat,			
		int&							outFrameNum,		
		avl::Image&						outImage			
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a video stream which will be saved to a selected file.</summary>
	/// <param name="inFile">File path of the output file.</param>
	/// <param name="inVideoEncoder">Video encoder.</param>
	/// <param name="inFPS">Desired frame rate of the produced video file.</param>
	/// <param name="inFrameWidth">Width of frame being added.</param>
	/// <param name="inFrameHeight">Height of frame being added.</param>
	/// <param name="outOutputVideoStream">Initialized output video stream.</param>
	AVL_FUNCTION void OpenOutputVideoStream
	(
		const atl::File&				inFile,				
		const avl::VideoEncoder::Type	inVideoEncoder,		
		const float						inFPS,				
		const int						inFrameWidth,		
		const int						inFrameHeight,		
		avl::OutputVideoStream&			outOutputVideoStream
	)
	THROW_AVL_ERRORS;

	/// <summary>Grabs a screenshot of the Desktop.</summary>
	/// <param name="inSelection">Bounding box of screen area to capture, whole desktop if not specified. Default value: atl::NIL.</param>
	/// <param name="outImage">Desktop screenshot image.</param>
	AVL_FUNCTION void GrabScreenshot
	(
		const atl::Optional<avl::Box>&	inSelection, 
		avl::Image&						outImage 
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a video stream which will be saved to a selected file.</summary>
	/// <param name="inFile">File path of the output file.</param>
	/// <param name="inVideoEncoderName">Video encoder.</param>
	/// <param name="inFPS">Desired frame rate of the produced video file.</param>
	/// <param name="inFrameWidth">Width of frame being added.</param>
	/// <param name="inFrameHeight">Height of frame being added.</param>
	/// <param name="outOutputVideoStream">Initialized output video stream.</param>
	AVL_FUNCTION void OpenOutputVideoStream_Any
	(
		const atl::File&				inFile,				
		const avl::VideoEncoderName&	inVideoEncoderName,	
		const float						inFPS,				
		const int						inFrameWidth,		
		const int						inFrameHeight,		
		avl::OutputVideoStream&			outOutputVideoStream
	)
	THROW_AVL_ERRORS;

	/// <summary>Writes an image to a previously opened video stream.</summary>
	/// <param name="inOutputVideoStream">Previously opened output video stream.</param>
	/// <param name="inImage">Frame to be added to stream.</param>
	AVL_FUNCTION void WriteVideoStream
	(
		const avl::OutputVideoStream&	inOutputVideoStream,	
		const avl::Image&				inImage					
	)
	THROW_AVL_ERRORS;

	/// <summary>List fourCCs names of available video compressors.</summary>
	/// <param name="outCompressors">Available compressors.</param>
	AVL_FUNCTION void GetAvailableVideoCompressors
	(
		atl::Array<atl::String>& outCompressors		
	)
	THROW_AVL_ERRORS;

} // namespace avl

namespace avs
{

	typedef avl::InputVideoStream InputVideoStream;
	typedef avl::OutputVideoStream OutputVideoStream;


	/// <summary>Reads a frame sequence from a video file.</summary>
	/// <param name="inFile">Video file.</param>
	/// <param name="inStartFrame">Number of first frame to fetch.</param>
	/// <param name="inRepeat">Determines whether to repeat video playback.</param>
	/// <param name="outImage">Output image.</param>
	/// <param name="outFPS">FPS.</param>
	/// <param name="outFrameNum">Current frame number.</param>
	/// <param name="outMaxFrame">Last frame number.</param>
	AVL_FUNCTION bool AvsFilter_ReadVideo
	(
		avs::InputVideoStream&	ioState,
		const atl::File&		inFile,				
		int						inStartFrame,		
		bool					inRepeat,			
		avl::Image&				outImage,			
		float&					outFPS,				
		int&					outFrameNum,		
		int&					outMaxFrame			
	)
	THROW_AVL_ERRORS;

	/// <summary>Writes an image sequence to a video file one frame per iteration.</summary>
	/// <param name="inImage">Current frame.</param>
	/// <param name="inFile">File path of the output file.</param>
	/// <param name="inFourCC">Four-character code, designating which codec to use.</param>
	/// <param name="inFPS">Desired frame rate of the produced video file. Default value: 20.0f.</param>
	AVL_FUNCTION void AvsFilter_WriteVideo_Deprecated
	(
		avs::OutputVideoStream&			ioState,
		const avl::Image&				inImage,			
		const atl::File&				inFile,				
		const avl::VideoEncoder::Type&	inFourCC,			
		float							inFPS				
	)
	THROW_AVL_ERRORS;

	/// <summary>Writes an image sequence to a video file one frame per iteration.</summary>
	/// <param name="inImage">Current frame.</param>
	/// <param name="inFile">File path of the output file.</param>
	/// <param name="inFourCC">Four-character code, designating which codec to use.</param>
	/// <param name="inFPS">Requested frame rate of the produced video file. Default value: 20.0f.</param>
	AVL_FUNCTION void AvsFilter_WriteVideo
	(
		avs::OutputVideoStream&			ioState,
		const avl::Image&				inImage,	
		const atl::File&				inFile,		
		const avl::VideoEncoderName&	inFourCC,	
		atl::Optional<float>			inFPS		
	)
	THROW_AVL_ERRORS;

} // namespace avs

#endif // AVS_IMAGEIO_H

