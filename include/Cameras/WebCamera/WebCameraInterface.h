//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#ifndef WEB_CAMERA_KIT_INTERFACE_H
#define WEB_CAMERA_KIT_INTERFACE_H


#include "Image/Image.h"
#include "WebCameraInputFormat.h"

namespace avl
{

	class WebCameraInterface
	{
	public:
		virtual ~WebCameraInterface() {}

		virtual void Initialize( int cameraIndex, int preferredWidth, int preferredHeight, WebCameraInputFormat::Type) = 0;
		virtual bool AwaitImage( Image& outImage, int timeout ) = 0;
	};

}


#endif // WEB_CAMERA_KIT_INTERFACE_H
