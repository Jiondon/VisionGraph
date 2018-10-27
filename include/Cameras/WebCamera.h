//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_WEBCAMERA_H
#define AVL_WEBCAMERA_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Cameras/WebCamera/WebCameraInterface.h"
#include "Cameras/WebCamera/WebCameraInputFormat.h"

namespace avl
{


	struct WebCamera_GrabImageState : public BaseState
	{
	public:
		WebCameraInterface* webCamera;

		WebCamera_GrabImageState()
			: webCamera(nullptr)
		{}

		~WebCamera_GrabImageState()
		{
			delete webCamera;
		}

	private:
		WebCamera_GrabImageState(const WebCamera_GrabImageState&); //=delete
		WebCamera_GrabImageState& operator=(const WebCamera_GrabImageState&); //=delete
	};



	/// <summary>Captures a frame from a camera using Direct Show interface.</summary>
	/// <param name="inCameraIndex">Index number of camera device to connect with. Default value: atl::NIL.</param>
	/// <param name="inFrameSize">Requested size of source frame in pixels selected from camera output formats. Default value: atl::NIL.</param>
	/// <param name="inPixelType">Requested specific pixel type from camera (may change image quality).</param>
	/// <param name="outFrame">Captured frame.</param>
	AVL_FUNCTION bool WebCamera_GrabImage
	(
		WebCamera_GrabImageState&	    ioState,
		atl::Optional<int>			    inCameraIndex,		
		atl::Optional<avl::Size>	    inFrameSize,		
		avl::WebCameraInputFormat::Type inPixelType,        
		avl::Image&					    outFrame			
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_WEBCAMERA_H

