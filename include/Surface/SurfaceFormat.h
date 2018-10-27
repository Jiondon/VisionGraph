//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _SURFACEFORMAT_H
#define _SURFACEFORMAT_H

#include "Image/PlainTypes.h"

namespace avl
{
	struct SurfaceFormat
	{
		int				width;
		int				height;
		PlainType::Type	type;
		double			xOffset;
		double			xScale;
		double			yOffset;
		double			yScale;
		double			zOffset;
		double			zScale;

		explicit SurfaceFormat
		(
			int width_ = 0,
			int height_ = 0,
			PlainType::Type type_ = PlainType::Int16,
			double xOffset_ = 0.0,
			double xScale_ = 0.0,
			double yOffset_ = 0.0,
			double yScale_ = 0.0,
			double zOffset_ = 0.0,
			double zScale_ = 0.0 
		) :
			 width(width_),
			 height(height_),
			 type(type_),
			 xOffset(xOffset_),
			 xScale(xScale_),
			 yOffset(yOffset_),
			 yScale(yScale_),
			 zOffset(zOffset_),
			 zScale(zScale_) 
		{}

		int Width() const				{ return width;		};
		int Height() const				{ return height;	};
		PlainType::Type Type() const	{ return type;		};
		double XOffset() const			{ return xOffset;	};
		double XScale() const			{ return xScale;	};
		double YOffset() const			{ return yOffset;	};
		double YScale() const			{ return yScale;	};
		double ZOffset() const			{ return zOffset;	};
		double ZScale() const			{ return zScale;	};

		bool operator == ( const avl::SurfaceFormat& rhs ) const
		{
			return width == rhs.width && 
			height == rhs.height && 
			type == rhs.type && 
			xOffset == rhs.xOffset && 
			xScale == rhs.xScale && 
			yOffset == rhs.yOffset && 
			yScale == rhs.yScale && 
			zOffset == rhs.zOffset && 
			zScale == rhs.zScale;
		}

		bool operator != ( const avl::SurfaceFormat& rhs ) const
		{
			return !(operator==(rhs));
		}

		
			explicit SurfaceFormat(const Surface& inSurface)
		  :
			 width(inSurface.Width()),
			 height(inSurface.Height()),
			 type(inSurface.Type()),
			 xOffset(inSurface.XOffset()),
			 xScale(inSurface.XScale()),
			 yOffset(inSurface.YOffset()),
			 yScale(inSurface.YScale()),
			 zOffset(inSurface.ZOffset()),
			 zScale(inSurface.ZScale())
		{
		}
		
	};

} //namespace avl


#endif

