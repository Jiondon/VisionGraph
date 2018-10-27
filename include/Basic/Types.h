//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef BASIC_TYPES_H
#define BASIC_TYPES_H

#include "ATL/Error.h"

namespace avl
{

	struct Box
	{
		int x;
		int y;
		int width;
		int height;

		Box() : x(0), y(0), width(0), height(0) {}
		Box(int x, int y, int width, int height)
			: x(x), y(y), width(width), height(height)
		{
			if (width < 0)
			{
				throw atl::DomainError( "Negative width of box." );
			}
			if (height < 0)
			{
				throw atl::DomainError( "Negative height of box." );
			}
		}

		int X( void ) const			{ return x;			}
		int Y( void ) const			{ return y;			}
		int Width( void ) const		{ return width;		}
		int Height( void ) const	{ return height;	}

		bool operator == (const Box& rhs) const
		{
			return x == rhs.x && y == rhs.y && width == rhs.width && height == rhs.height;
		}

		bool operator != (const Box& rhs) const
		{
			return !(operator==(rhs));
		}
	};

	struct Location
	{
		int x;
		int y;

		Location() : x(0), y(0) {}
		Location( int x, int y ) : x(x), y(y) {}

		int X( void ) const		{ return x;	}
		int Y( void ) const		{ return y;	}

		bool operator == (const Location& rhs) const
		{
			return x == rhs.x && y == rhs.y;
		}

		bool operator != (const Location& rhs) const
		{
			return x != rhs.x || y != rhs.y;
		}
	};

	struct Pixel
	{
		explicit Pixel(float x = 0, float y = 0, float z = 0, float w = 0)
		{
			Set(x, y, z, w);
		}

		void Set(float x = 0, float y = 0, float z = 0, float w = 0)
		{
			element[0] = x;
			element[1] = y;
			element[2] = z;
			element[3] = w;
		}

		float& operator[](int index)
		{
			return element[index];
		}

		float operator[](int index) const
		{
			return element[index];
		}

		float X( void ) const	{ return element[0];	}
		float Y( void ) const	{ return element[1];	}
		float Z( void ) const	{ return element[2];	}
		float W( void ) const	{ return element[3];	}

		bool operator == (const Pixel& rhs) const
		{
			return element[0] == rhs.element[0] && element[1] == rhs.element[1] &&element[2] == rhs.element[2] && element[3] == rhs.element[3];
		}

		bool operator != (const Pixel& rhs) const
		{
			return !(operator == (rhs));
		}

	private:
		float element[4];
	};

	struct Size
	{
		int width, height;

		Size() : width(1), height(1) { }
		Size(int width, int height) : width(width), height(height) { }

		int Width( void ) const		{ return width;		}
		int Height( void ) const	{ return height;	}

		bool operator == (const Size& size) const
		{
			return width == size.width && height == size.height;
		}

		bool operator != (const Size& size) const
		{
			return width != size.width || height != size.height;
		}			
	};

}

#endif // BASIC_TYPES_H
