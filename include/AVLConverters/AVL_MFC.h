
#pragma once
#ifndef AVL_MFC_H
#define AVL_MFC_H

#include "atlimage.h"
#include "Image/Image.h"
#include "Image/ImageConversions.h"
#include <algorithm>
#include <memory>

namespace avl
{
	inline void AVLImageToCImage(const avl::Image& inImage, CImage& outImage)
	{
		if (outImage.IsNull() || !outImage.IsDIBSection() || outImage.GetWidth() != inImage.Width() || outImage.GetHeight() != inImage.Height() || outImage.GetBPP() != 24)
		{
			outImage.Destroy();

			if (!outImage.Create( inImage.Width(), inImage.Height(), 24 ))
				throw atl::RuntimeError("Unable to create ATL::CImage instance.");
		}

		FillImagePreviewBuffer( inImage, inImage.Width(), inImage.Height(), (atl::byte*)outImage.GetPixelAddress(0, 0), outImage.GetPitch(), true);
	}

	inline void AVLImageToCImage(const avl::Image& inImage, int inWidth, int inHeight, bool inHighQualityScaling, CImage& outImage)
	{
		if (outImage.IsNull() || !outImage.IsDIBSection() || outImage.GetWidth() != inWidth || outImage.GetHeight() != inHeight || outImage.GetBPP() != 24)
		{
			outImage.Destroy();

			if (!outImage.Create( inWidth, inHeight, 24 ))
				throw atl::RuntimeError("Unable to create ATL::CImage instance.");
		}

		FillImagePreviewBuffer( inImage, inWidth, inHeight, (atl::byte*)outImage.GetPixelAddress(0, 0), outImage.GetPitch(), inHighQualityScaling); 
	}


	inline void CImageToAvlImage(const CImage& inImage, avl::Image& outImage)
	{
		int bpp = inImage.GetBPP();
		int pitch = inImage.GetPitch();
		int width = inImage.GetWidth();
		int height = inImage.GetHeight();
		bool flipped = pitch < 0;

		if( bpp == 24 || bpp == 32 )
		{
			int channels = bpp / 8;
			outImage.Reset( inImage.GetWidth(), inImage.GetHeight(), avl::PlainType::UInt8, bpp / 8, atl::NIL );

			for( int i = 0; i < height; ++i )
			{
				atl::uint8* px = outImage.Ptr<atl::uint8>( 0, flipped ? (height-1-i) : i );
				memcpy( px, inImage.GetPixelAddress(0, i), width * channels );
				for (int j = 0; j < (int)width; ++j)
				{
					std::swap( px[0], px[2] );
					px += channels;
				}
			}
		}
		else if( bpp == 8 )
		{
			std::unique_ptr<RGBQUAD[]> palette(new RGBQUAD[inImage.GetMaxColorTableEntries()]);
			inImage.GetColorTable( 0, 256, palette.get() );

			outImage.Reset(width, height, avl::PlainType::UInt8, 3, atl::NIL );
			for( int i = 0; i < height; ++i )
			{
				atl::uint8* buff = (atl::uint8*)inImage.GetPixelAddress(0, i);
				atl::uint8* px = outImage.Ptr<atl::uint8>( 0, flipped ? height-1-i : i );
				for( int j = 0 ; j < width; ++j )
				{
					px[0] = (atl::uint8)palette[ buff[j] ].rgbRed;
					px[1] = (atl::uint8)palette[ buff[j] ].rgbGreen;
					px[2] = (atl::uint8)palette[ buff[j] ].rgbBlue;
					px += 3;
				}
			}
		}
		else
		{
			throw atl::DomainError("Unsupported image format in CImageToAvlImage");
		}
	}


} // namespace avl

#endif // AVL_MFC_H
