//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#pragma once
#ifndef XIAPIENUMS_H
#define XIAPIENUMS_H

namespace avl
{

// structure containing information about output image format
namespace XiApiImageDataFormat
{
	enum Type
	{
		MONO8                     =0, // 8 bits per pixel
		MONO16                    =1, // 16 bits per pixel
		RGB24                     =2, // RGB data format
		RGB32                     =3, // RGBA data format
		RAW8                      =4, // 8 bits per pixel raw data from sensor
		RAW16                     =5, // 16 bits per pixel raw data from sensor
	};
}

// structure containing information about trigger functionality
namespace XiApiTriggerSource
{
	enum Type
	{
		TRG_OFF                   =0, // Capture of next image is automatically started after previous
		TRG_EDGE_RISING           =1, // Capture is started on rising edge of selected input
		TRG_EDGE_FALLING          =2, // Capture is started on falling edge of selected input
		TRG_SOFTWARE              =3  // Capture is started with software trigger
	};
}

// structure containing information about GPI functionality
namespace XiApiGPIMode
{
	enum Type
	{
		GPI_OFF                   =0, // Input is off (zero voltage or switched_off)
		GPI_TRIGGER               =1, // Input can be used for triggering
		GPI_EXT_EVENT             =2  // External signal input
	};
}

// structure containing information about GPO functionality
namespace XiApiGPOMode
{
	enum Type
	{
		GPO_OFF                   =0, // Output is off (zero voltage or switched_off)
		GPO_ON                    =1, // Output is on (voltage or switched_on)
		GPO_FRAME_ACTIVE          =2, // Output is on while frame exposure,read,transfer
		GPO_FRAME_ACTIVE_NEG      =3, // Output is off while frame exposure,read,transfer
		GPO_EXPOSURE_ACTIVE       =4, // Output is on while frame exposure
		GPO_EXPOSURE_ACTIVE_NEG   =5  // Output is off while frame exposure
	};
}


namespace XiApiDownsampling
{
	enum Type
	{
		X1_BINNING = 0,	//1 sensor pixel = 1 image pixel
		X2_BINNING = 1,	//2x2 sensor pixels = 1 image pixel
		X4_BINNING = 2,	//4x4 sensor pixels = 1 image pixel
		X1_SKIPPING = 3,	//1 sensor pixel = 1 image pixel
		X2_SKIPPING = 4,	//2x2 sensor pixels = 1 image pixel
		X4_SKIPPING = 5	//4x4 sensor pixels = 1 image pixel
	};
}

}

#endif //XIAPIENUMS_H