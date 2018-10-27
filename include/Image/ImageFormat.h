//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _IMAGEFORMAT_H
#define _IMAGEFORMAT_H

#include "Image/PlainTypes.h"

namespace avl
{
	struct ImageFormat
	{
		int				width;
		int				height;
		PlainType::Type	type;
		int				depth;
		int				pitchAlignment;

		explicit ImageFormat
		(
			int width_ = 0,
			int height_ = 0,
			PlainType::Type type_ = PlainType::UInt8,
			int depth_ = 1,
			int pitchAlignment_ = 16 
		) :
			 width(width_),
			 height(height_),
			 type(type_),
			 depth(depth_),
			 pitchAlignment(pitchAlignment_) 
		{}

		int Width() const				{ return width;				};
		int Height() const				{ return height;			};
		PlainType::Type Type() const	{ return type;				};
		int Depth() const				{ return depth;				};
		int PitchAlignment() const		{ return pitchAlignment;	};

		bool operator == ( const avl::ImageFormat& rhs ) const
		{
			return width == rhs.width && 
			height == rhs.height && 
			type == rhs.type && 
			depth == rhs.depth && 
			pitchAlignment == rhs.pitchAlignment;
		}

		bool operator != ( const avl::ImageFormat& rhs ) const
		{
			return !(operator==(rhs));
		}

		
			explicit ImageFormat(const Image& inImage)
		  :
			 width(inImage.Width()),
			 height(inImage.Height()),
			 type(inImage.Type()),
			 depth(inImage.Depth()),
			 pitchAlignment(16)
		{
			if ((depth * _sizeof(type) * width + pitchAlignment - 1) / pitchAlignment * pitchAlignment != inImage.Pitch())
			{
				throw atl::DomainError("Invalid image pitch alignment. Please use RealignImagePitch filter.");
			}
		}
		
	};

} //namespace avl


#endif

