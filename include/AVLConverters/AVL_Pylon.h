
#pragma once
#ifndef AVL_PYLON_H
#define AVL_PYLON_H

#include <pylon/PylonIncludes.h>
#include <AVL.h>

namespace avl
{

	inline void CGrabResultPtrToAvlImage( const  Pylon::CGrabResultPtr& inResult, avl::Image& outImage )
	{
		static Pylon::CImageFormatConverter converter;
		int height  = inResult->GetHeight();
		int width   = inResult->GetWidth();
		int pixelSize = ( (Pylon::BitPerPixel(inResult->GetPixelType()) + 7) / 8 ) * 8;

		avl::PlainType::Type imagePlainType;
		Pylon::EPixelType pixelType;
		int depth;

		imagePlainType = pixelSize == 8 ? avl::PlainType::UInt8 : avl::PlainType::UInt16;

		if( Pylon::IsMonoImage(inResult->GetPixelType()) )
		{
			depth = 1;
			pixelType = pixelSize == 8 ? Pylon::PixelType_Mono8 : Pylon::PixelType_Mono16;
		}
		else
		{
			depth = 3;
			pixelType = pixelSize == 8 ? Pylon::PixelType_RGB8packed: Pylon::PixelType_RGB16packed;
			if( Pylon::IsYUV(inResult->GetPixelType()) )
			{
				pixelType = Pylon::PixelType_RGB8packed;
				imagePlainType = avl::PlainType::UInt8;
			}

		}

		outImage.Reset( width, height, imagePlainType, depth, atl::NIL );
		int paddingX = outImage.Pitch() - outImage.Width() * outImage.PixelSize();

		if( converter.IsInitialized( inResult->GetPixelType() ) == false
			|| converter.OutputPixelFormat.GetValue() != pixelType
			|| converter.OutputPaddingX.GetValue() != paddingX )
		{
			converter.OutputPixelFormat = pixelType;
			converter.OutputPaddingX = paddingX;

			converter.Initialize( inResult->GetPixelType() );
		}
		converter.Convert( outImage.Data(), outImage.Pitch() * outImage.Height(), inResult);
	}

} //namespace avl

#endif //AVL_PYLON_H
