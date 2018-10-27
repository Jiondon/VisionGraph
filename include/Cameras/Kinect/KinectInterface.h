//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#ifndef AVL_KINECT_INTERFACE_H
#define AVL_KINECT_INTERFACE_H

#include "ATL/Optional.h"
#include "Image/PlainTypes.h"
#include "Image/Image.h"
#include "Geometry/Geometry.h"
#include "AVLCommon/CancellationTypes.h"

namespace avl
{	class KinectInterface
	{
	public:
		virtual ~KinectInterface() {}
		
		virtual void Start( void ) = 0;
		virtual void Stop( void ) = 0;
		
		//Grab Image Functions
		virtual bool GrabImage( avl::Image& outImage, avl::Image& outDepthImage ) = 0;
		virtual void SetParams( ) = 0;

		virtual void SetCancellationObject( ICancellationProvider* workCancellation ) = 0;

		//Skeleton Tracing functions
		virtual void GetSkeletons( int& outNumberOfPersons,  atl::Array< atl::Array< avl::Point2D > >& Position, avl::Region& outPlayerRegion) = 0;

		virtual bool IsStarted() = 0;
	};
}

#endif // AVL_KINECT_INTERFACE_H
