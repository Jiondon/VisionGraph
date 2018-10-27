
#pragma once
#ifndef AVL_WINAPI_H
#define AVL_WINAPI_H

#ifndef _WINDOWS_
	#error Windows.h is not included.
#endif

#include "Image/Image.h"
#include "Image/ImageSpatialTransforms.h"

namespace avl
{
	///
	/// Convert AVL Image to HBITMAP (RGBA).
	//
	inline HBITMAP AVLImageToHBitmap(const avl::Image& inImage, const float inZoomX = 1.0, const float inZoomY = 1.0)
	{
		if (inImage.Empty())
		{
			throw atl::DomainError("Unable to convert empty image.");
		}

		if (inZoomX < 0 || inZoomY < 0)
		{
			throw atl::DomainError("Invalid scale.");
		}

		if (inImage.Format().type != avl::PlainType::UInt8)
		{
			throw atl::DomainError("Wrong pixel type. Only UINT8 pixel format is permitted.");
		}

		avl::Image img;

		if ( fabs(inZoomX-1.0) < 0.001 && fabs(inZoomY-1.0) < 0.001)
		{
			img = inImage;
		}
		else
		{
			avl::ResizeImage_Relative(inImage, inZoomX, inZoomY, avl::ResizeMethod::Bilinear, img);
		}


		RGBQUAD * pixels = new RGBQUAD[img.Width() * img.Height()];

		atl::byte * src = (atl::byte *) img.Data();
		atl::byte * out = (atl::byte *) pixels;

		int fill = img.Pitch()-img.Width()*img.PixelSize();

		if (img.PixelSize() == 4)
		{
			for(int y = 0; y < img.Height(); y++)
			{
				for(int x = 0; x < img.Width(); x++)
				{
					out[0] = src[2];
					out[1] = src[1];
					out[2] = src[0];
					out[3] = src[3];

					out+=4;
					src+=4;
				}

				src += fill;
			}
		}
		else if (img.PixelSize() == 3)
		{
			for(int y = 0; y < img.Height(); y++)
			{
				for(int x = 0; x < img.Width(); x++)
				{
					out[0] = src[2];
					out[1] = src[1];
					out[2] = src[0];
					out[3] = 0;

					out+=4;
					src+=3;
				}
				src += fill;
			}

		}
		else if (img.PixelSize() == 2)
		{
			for(int y = 0; y < img.Height(); y++)
			{
				for(int x = 0; x < img.Width(); x++)
				{
					out[0] = 0;
					out[1] = src[1];
					out[2] = src[0];
					out[3] = 0;

					out+=4;
					src+=2;
				}
				src += fill;
			}
		}
		else if (img.PixelSize() == 1)
		{
			for(int y = 0; y < img.Height(); y++)
			{
				for(int x = 0; x < img.Width(); x++)
				{
					out[0] = src[0];
					out[1] = src[0];
					out[2] = src[0];
					out[3] = 0;

					out+=4;
					src++;
				}
				src += fill;
			}
		}
		else
			throw atl::DomainError("Unable to create HBITMAP. Invalid pixel size.");

		/////////////////////////////////////////////////////////////////////////////////////////////
		BITMAPINFO info;
		memset(&info, 0, sizeof(BITMAPINFO));

		BITMAPINFOHEADER& bmih = info.bmiHeader;

		bmih.biHeight = -img.Height();
		bmih.biWidth = img.Width();
		bmih.biSizeImage = img.Height()*img.Width();
		bmih.biBitCount = 32;

		bmih.biCompression = BI_RGB;
		bmih.biSize = sizeof(BITMAPINFOHEADER);
		bmih.biPlanes = 1;

		HDC hdc = ::GetDC(NULL);

		HBITMAP hbmp = CreateDIBitmap(hdc, &bmih, CBM_INIT, (void*)pixels, &info, DIB_RGB_COLORS);

		::ReleaseDC(NULL, hdc);

		delete[] pixels;

		if (hbmp == NULL)
			throw atl::DomainError("Unable to create HBITMAP.");

		return hbmp;
	}

	///
	/// Display image on prepared HDC
	///
	inline void DisplayImageHDC(const HDC inHdc, const avl::Image& inImage, const float inZoomX = 1.0, const float inZoomY = 1.0)
	{
		if (inImage.Empty())
			return;

		BITMAP bitmap;
		HGDIOBJ oldBitmap;

		HBITMAP hBitmap = AVLImageToHBitmap(inImage, inZoomX, inZoomY);

		GetObject(hBitmap, sizeof(bitmap), &bitmap);

		HDC hdcMem = CreateCompatibleDC(inHdc);
		oldBitmap = SelectObject(hdcMem, hBitmap);

		GetObject(hBitmap, sizeof(bitmap), &bitmap);
		BitBlt(inHdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);

		SelectObject(hdcMem, oldBitmap);
		DeleteDC(hdcMem);
		DeleteObject(hBitmap);
	}
} // namespace avl

#endif // AVL_WINAPI_H
