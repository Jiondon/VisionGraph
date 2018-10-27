//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_AXIS_H
#define AVL_AXIS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Cameras/AXIS/AXISInterface.h"

namespace avl
{


	namespace AXISResolution
	{
		enum Type
		{
			_1024x768=0, 
			_800x600, 
			_640x480, 
			_480x360, 
			_240x180, 
			_160x120, 
		};
	}

	namespace AXISRotation
	{
		enum Type
		{
			_0=0, 
			_90=90, 
			_180=180,
			_270=270, 
		};
	}

	struct AXIS_BaseStructState : public BaseState
	{
		AXISInterface* AXIS;

		AXIS_BaseStructState()
		{
			AXIS = nullptr;
		}

		~AXIS_BaseStructState()
		{
			delete AXIS;
		}

	private:
		AXIS_BaseStructState(const AXIS_BaseStructState&); //=delete
		AXIS_BaseStructState& operator=(const AXIS_BaseStructState&); //=delete
	};

	struct AXIS_GrabImageState : public AXIS_BaseStructState 
	{
	};


	/// <summary>Captures a frame using AXIS.</summary>
	/// <param name="inAddress">Source device host or ip address.</param>
	/// <param name="inCameraID">ID of camera.</param>
	/// <param name="inLogin">Login for Basic authorization. Default value: atl::NIL.</param>
	/// <param name="inPassword">Login for Basic authorization. Default value: atl::NIL.</param>
	/// <param name="inResolution">Resolution of the returned image. Default value: atl::NIL.</param>
	/// <param name="inRotation">Rotates the image clockwise. Default value: atl::NIL.</param>
	/// <param name="inCompression">Compression level of the image. Default value: atl::NIL.</param>
	/// <param name="outImage">Output image.</param>
	AVL_FUNCTION bool AXIS_GrabImage
	(
		AXIS_GrabImageState&						ioState,	
		const atl::String&							inAddress,		
		int											inCameraID,		
		atl::Optional<const atl::String&>			inLogin,		
		atl::Optional<const atl::String&>			inPassword,		
		atl::Optional<avl::AXISResolution::Type>	inResolution,	
		atl::Optional<avl::AXISRotation::Type>		inRotation,		
		atl::Optional<int>							inCompression,	
		atl::Optional<const atl::String&>			inTextString,
		avl::Image&									outImage		
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_AXIS_H

