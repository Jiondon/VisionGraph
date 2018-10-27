//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_KINECT_H
#define AVL_KINECT_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Cameras/Kinect/KinectInterface.h"

namespace avl
{


	struct OpenNI_GrabImageState : public BaseState
	{
		KinectInterface* kinect;

		OpenNI_GrabImageState()
			: kinect(nullptr)
		{}

		~OpenNI_GrabImageState()
		{
			delete kinect;
		}

	private:
		OpenNI_GrabImageState(const OpenNI_GrabImageState&); //=delete
		OpenNI_GrabImageState& operator=(const OpenNI_GrabImageState&); //=delete
	};

	typedef OpenNI_GrabImageState OpenNI_SkeletonTracingState;



	/// <summary>Captures a frame using Kinect.</summary>
	/// <param name="outImage">Captured frame.</param>
	AVL_FUNCTION bool OpenNI_GrabImage
	(
		OpenNI_GrabImageState&	ioState,
		avl::Image&				outImage,				
		avl::Image&				outDepthImage
	)
	THROW_AVL_ERRORS;

	/// <summary>Captures a skeleton using Kinect.</summary>
	AVL_FUNCTION bool OpenNI_SkeletonTracing
	(
		OpenNI_SkeletonTracingState&			ioState,
		int&									outNumberOfPersons,
		atl::Array<atl::Array<avl::Point2D>>&	outSkeletons,
		avl::Region&							outPlayerRegion
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_KINECT_H

