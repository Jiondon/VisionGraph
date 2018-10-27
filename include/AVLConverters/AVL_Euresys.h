
#pragma once
#ifndef AVL_EURESYS_H
#define AVL_EURESYS_H

#include <MultiCamCpp.h>
#include <AVL.h>

namespace avl
{
	inline void EuresysSignalToAvlImage_Linked( Euresys::MultiCam::Channel& channel, Euresys::MultiCam::SignalInfo& info, Image& outImage )
	{
		PVOID buffer;
		int imageWidth, imageHeight, pitch, colorFormat;

		// Read size of image
		channel.GetParam(MC_ImageSizeX, imageWidth);
		channel.GetParam(MC_ImageSizeY, imageHeight);
		channel.GetParam(MC_BufferPitch, pitch);
		channel.GetParam(MC_ColorFormat, colorFormat);

		// Get pointer to a buffer with image data
		info.Surf->GetParam(MC_SurfaceAddr, buffer);

		int depth = 1;
		if( colorFormat ==  MC_ColorFormat_RGB24 )
			depth = 3;


		avl::Image tmpImage( imageWidth, imageHeight, pitch, avl::PlainType::UInt8, depth, buffer );
	}

	inline void EuresysSignalToAvlImage( Euresys::MultiCam::Channel& channel, Euresys::MultiCam::SignalInfo& info, Image& outImage )
	{
		PVOID buffer;
		int imageWidth, imageHeight, pitch;

		// Read size of image
		channel.GetParam(MC_ImageSizeX, imageWidth);
		channel.GetParam(MC_ImageSizeY, imageHeight);
		channel.GetParam(MC_BufferPitch, pitch);

		// Get pointer to a buffer with image data
		info.Surf->GetParam(MC_SurfaceAddr, buffer);

		// Reset image
		outImage.Reset(imageWidth, imageHeight, avl::PlainType::UInt8, 1, atl::NIL);

		// Copy image data to avl::Image object line by line
		for ( int i = 0; i < outImage.Height(); ++i )
			memcpy(outImage.RowBegin<atl::uint8>(i), (atl::uint8*)buffer + i * pitch, outImage.Width());
	}

} // namespace avl

#endif //AVL_EURESYS_H
