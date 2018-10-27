
#pragma once
#ifndef AVL_MVACQUIRE_H
#define AVL_MVACQUIRE_H

#include <mvIMPACT_CPP/mvIMPACT_acquire.h>
#include <AVL.h>

namespace avl
{

	inline void MVRequestToAvlImage(const Request* inRequest, avl::Image& outImage)
	{
		if ( inRequest && inRequest->isOK() )
		{
			// Read image parameters
			int imageWidth = inRequest->imageWidth.read();
			int imageHeight = inRequest->imageHeight.read();
			int channelCount = inRequest->imageChannelCount.read();
			int pitch = inRequest->imageLinePitch.read();

			// Detect type of image pixel
			int bitDepth = inRequest->imageChannelBitDepth.read();
			avl::PlainType::Type imagePixelType;

			switch ( bitDepth )
			{
			case 8:
				imagePixelType = avl::PlainType::UInt8;
				break;
			case 16:
				imagePixelType = avl::PlainType::UInt16;
				break;
			default:
				throw atl::DomainError( L"Unsupported pixel type." );
			}

			outImage.Reset(imageWidth, imageHeight, imagePixelType, channelCount, atl::NIL);

			// Calculate size of pixel
			int pixelSize = channelCount * bitDepth / 8;

			atl::uint8* source = (atl::uint8*)inRequest->imageData.read();
			int lineSize = pixelSize * imageWidth;

			// Go through image line by line
			for ( int i = 0; i < outImage.Height(); ++i )
			{
				atl::uint8* destination = outImage.RowBegin<atl::uint8>(i);
				memcpy(destination, source, lineSize);
				source += pitch;
			}
		}
		else
		{
			throw atl::RuntimeError("Invalid request.");
		}
	}

} // namespace avl

#endif //AVL_MVACQUIRE_H
