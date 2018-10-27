
#pragma once
#ifndef AVL_SYNVIEW_H
#define AVL_SYNVIEW_H

#include <sv.synview.class.h>
#include "Image/Image.h"


namespace avl
{

	void LvBufferToAvlImage_Linked(LvBuffer* inBuffer, avl::Image& outImage)
	{
		LvipImgInfo imgInfo;
		inBuffer->GetImgInfo( imgInfo );

		if(imgInfo.PixelFormat == LvPixelFormat_Mono8 )
		{
			outImage.Reset( imgInfo.Width, imgInfo.Height, imgInfo.LinePitch, avl::PlainType::UInt8, 1, imgInfo.pData );
		}
		else if( imgInfo.PixelFormat == LvPixelFormat_Mono12 )
		{
			outImage.Reset( imgInfo.Width, imgInfo.Height, imgInfo.LinePitch, avl::PlainType::UInt16, 1, imgInfo.pData );
		}
		else if( imgInfo.PixelFormat == LvPixelFormat_RGB8Packed )
		{
			outImage.Reset( imgInfo.Width, imgInfo.Height, imgInfo.LinePitch, avl::PlainType::UInt8, 3, imgInfo.pData );
		}
		else
		{
			throw atl::DomainError( L"Not supported image pixel format" );
		}
	}

	void LvBufferToAvlImage(LvBuffer* inBuffer, avl::Image& outImage)
	{
		void* pData = NULL;
		inBuffer->GetPtr(LvBuffer_UniBase, &pData);

		LvipImgInfo imgInfo;
		inBuffer->GetImgInfo( imgInfo );

		if(imgInfo.PixelFormat == LvPixelFormat_Mono8 || imgInfo.PixelFormat == LvPixelFormat_RGB8 || imgInfo.PixelFormat == LvPixelFormat_RGB8Packed)
		{
			int depth = (imgInfo.PixelFormat == LvPixelFormat_Mono8) ? 1 : 3;

			outImage.Reset(imgInfo.Width, imgInfo.Height, avl::PlainType::UInt8, depth, atl::NIL);

			unsigned int lineSize = imgInfo.Width * depth;
			for (int j = 0; j < outImage.Height(); ++j)
			{
				atl::uint8*		dst = outImage.RowBegin<atl::uint8>(j);
				unsigned char*	src = (unsigned char*)pData + j * imgInfo.LinePitch;

				memcpy(dst, src, lineSize);
			}
		}
		else
		{
			throw atl::DomainError( L"Not supported image pixel format." );
		}
	}

} //namespace avl

#endif // AVL_SYNVIEW_H
