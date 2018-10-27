//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_POINT3DGRID_H
#define AVL_POINT3DGRID_H

#include "Geometry3D/Geometry3D.h"
#include "ATL/Blob.h"
#include "ATL/NumericRange.h"
#include <cmath>

namespace avl
{

	struct Point3DGrid
	{
	protected:
		int			width;
		int			height;
		atl::Blob	blob;

	public:

		Point3DGrid()
			: width(0), height(0)
		{}

		#ifdef HAS_CPP0X

		Point3DGrid( Point3DGrid&& rhs )
		{
			operator=(std::move(rhs));
		}

		Point3DGrid& operator=( Point3DGrid&& rhs )
		{
			if (this != &rhs)
			{
				if (!rhs.blob.Own())
				{
					operator=( static_cast<const Point3DGrid&>(rhs) );
				}
				else
				{
					width = rhs.width;
					height = rhs.height;
					blob = std::move(rhs.blob);

					rhs.Reset( 0, 0, nullptr );
				}
			}
			return *this;
		}

		#endif

		Point3DGrid(int width_, int height_)
			: width(0), height(0)
		{
			Reset( width_, height_ );
		}

		Point3DGrid(int width_, int height_, void* data)
			: width(0), height(0)
		{
			Reset( width_, height_, data );
		}

		Point3DGrid(const Point3DGrid& rhs)
			: width(0), height(0)
		{
			operator=(rhs);
		}

		Point3DGrid& operator=( const Point3DGrid& rhs )
		{
			if (this != &rhs)
			{
				Reset( rhs.width, rhs.height );
				std::memcpy( (Point3D*)blob.Pointer(), (const Point3D*)rhs.blob.Pointer(), rhs.Size() * sizeof(Point3D) );
			}
			return *this;
		}

		~Point3DGrid()
		{}

		void Reset(int newWidth, int newHeight)
		{
			if (!blob.Own() || width != newWidth || height != newHeight)
			{
				if (newWidth == 0 || newHeight == 0)
				{
					newWidth = 0;
					newHeight = 0;
				}

				width = newWidth;
				height = newHeight;

				try
				{
					blob.Reset( Size() * sizeof(Point3D) );
				}
				catch ( const atl::Error& )
				{
					throw atl::OutOfMemoryError("Allocation error - grid dimensions too big in Point3DGrid::Reset().");
				}
			}
		}

		void Reset(int newWidth, int newHeight, void* data)
		{
			if (newWidth == 0 || newHeight == 0)
			{
				newWidth = 0;
				newHeight = 0;
			}

			width = newWidth;
			height = newHeight;
			blob.Reset( Size() * sizeof(Point3D), data );
		}

		int Width() const			{ return width; }
		int Height() const			{ return height; }
		int Size() const			{ return width * height; }
		bool Empty() const			{ return width == 0 || height == 0; }
		Point3D* Data()				{ return (Point3D*)blob.Pointer(); }
		const Point3D* Data() const	{ return (const Point3D*)blob.Pointer(); }

		Point3D* operator[](const int index)				{ return Data() + width * index; }
		const Point3D* operator[](const int index) const	{ return Data() + width * index; }

		void SetPoints(const Point3D& point = InvalidPoint())
		{
			Point3D* data = Data();
			for (int i = 0, size = Size(); i < size; ++i)
			{
				*data++ = point;
			}
		}

		bool MakeDataOwn()
		{
			if (!blob.Own() && Data() != 0)
			{
				const Point3D* oldData = Data();
				Reset( width, height );
				std::memcpy( blob.Pointer(), oldData, Size() * sizeof(Point3D) );
				return true;
			}
			return false;
		}

		bool operator == (const Point3DGrid& rhs) const
		{
			if (this != &rhs)
			{
				if (width != rhs.width || height != rhs.height)
				{
					return false;
				}
				if (0 != std::memcmp(blob.Pointer(), rhs.blob.Pointer(), Size() * sizeof(Point3D)))
				{
					return false;
				}
			}
			return true;
		}

		bool operator != (const Point3DGrid& rhs) const
		{
			return !(operator==(rhs));
		}

		static inline Point3D InvalidPoint()
		{
			const float infinity = atl::NumericRange<float>::Max();
			return Point3D(infinity, infinity, infinity);
		}

		static inline bool IsPointValid(const Point3D& inPoint)
		{
			return inPoint.x != atl::NumericRange<float>::Min() && inPoint.x != atl::NumericRange<float>::Max() &&
				   inPoint.y != atl::NumericRange<float>::Min() && inPoint.y != atl::NumericRange<float>::Max() &&
				   inPoint.z != atl::NumericRange<float>::Min() && inPoint.z != atl::NumericRange<float>::Max() &&
				   !(inPoint.x != inPoint.x || inPoint.y != inPoint.y || inPoint.z != inPoint.z);
		}
	};

}

#endif
