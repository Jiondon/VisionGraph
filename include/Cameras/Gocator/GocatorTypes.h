//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#pragma once
#ifndef AVL_GOCATOR_TYPES_H
#define AVL_GOCATOR_TYPES_H


#include "ATL/AtlString.h"
#include "ATL/AtlTypes.h"

namespace avl
{

	typedef atl::String GocatorAddress;

	struct GocatorFrameInfo
	{
		GocatorFrameInfo()
			: frameIndex(0)
			, timestamp(0)
			, encoder(0)
			, encoderAtZ(0)
		{}

		GocatorFrameInfo
		(
			atl::int64 _frameIndex,
			atl::int64 _timestamp,
			atl::int64 _encoder,
			atl::int64 _encoderAtZ
		)
			: frameIndex(_frameIndex)
			, timestamp(_timestamp)
			, encoder(_encoder)
			, encoderAtZ(_encoderAtZ)
		{}

		atl::int64 FrameIndex( void )	const { return frameIndex;	}
		atl::int64 Timestamp( void )	const { return timestamp;	}
		atl::int64 Encoder( void )		const { return encoder;		}
		atl::int64 EncoderAtZ( void )	const { return encoderAtZ;	}

		bool operator == ( const avl::GocatorFrameInfo& rhs ) const
		{
			return frameIndex == rhs.frameIndex && timestamp == rhs.timestamp && encoder == rhs.encoder && encoderAtZ == rhs.encoderAtZ;
		}

		bool operator != ( const avl::GocatorFrameInfo& rhs ) const
		{
			return !(operator==(rhs));
		}

		atl::int64 frameIndex;	// Frame index (counts up from zero).
		atl::int64 timestamp;   // Timestamp in internal units approximating microseconds where the true time in us = timestamp value / 1.024.
		atl::int64 encoder;     // Position (encoder ticks).
		atl::int64 encoderAtZ;  // Encoder value latched at z-index mark (encoder ticks).
	};
}


#endif // AVL_GOCATOR_TYPES_H
