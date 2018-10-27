//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should be included directly in your program.
//

#ifndef AVL_GOPOINTPLOT_H
#define AVL_GOPOINTPLOT_H

#include "Profile/GoProfile.h"
#include "Geometry/Geometry.h"

namespace avl
{
	
	class GoPointPlot : public XTransform, public YTransform, public atl::Array<Point2D>
	{
	public:
		GoPointPlot() : XTransform(0.0f, 1.0f), YTransform(0.0f, 1.0f)
		{}

		GoPointPlot(float xOffset_, float xScale_, float yOffset_, float yScale_) : XTransform(xOffset_, xScale_), YTransform(yOffset_, yScale_)
		{}

		GoPointPlot(float xOffset_, float xScale_, float yOffset_, float yScale_, const atl::Array<Point2D>& values_) : XTransform(xOffset_, xScale_), YTransform(yOffset_, yScale_), atl::Array<Point2D>(values_)
		{}

		GoPointPlot(float xOffset_, float xScale_, float yOffset_, float yScale_, void* data_, int count, bool own)
			: XTransform(xOffset_, xScale_)
			, YTransform(yOffset_, yScale_)
			, atl::Array<Point2D>(count, static_cast<Point2D*>(data_), own)
		{}

		GoPointPlot(float xOffset_, float xScale_, float yOffset_, float yScale_, void* data_, int count)
			: XTransform(xOffset_, xScale_)
			, YTransform(yOffset_, yScale_)
		{
			const Point2D* newData = (const Point2D*)data_;
			atl::Array<Point2D>::Insert( newData, newData + count );
		}

#ifdef HAS_CPP0X

		GoPointPlot(const GoPointPlot& rhs)
			: XTransform(rhs)
			, YTransform(rhs)
			, atl::Array<Point2D>(rhs)
		{}

		GoPointPlot(GoPointPlot&& rhs)
			: XTransform(std::move(rhs))
			, YTransform(std::move(rhs))
			, atl::Array<Point2D>(std::move(rhs))
		{}

		GoPointPlot& operator = (const GoPointPlot& rhs)
		{
			XTransform::operator=( rhs );
			YTransform::operator=( rhs );
			atl::Array< Point2D >::operator=( rhs );

			return *this;
		}

		GoPointPlot& operator = (GoPointPlot&& rhs)
		{
			XTransform::operator=( std::move(rhs) );
			YTransform::operator=( std::move(rhs) );
			atl::Array< Point2D >::operator=( std::move(rhs) );

			return *this;
		}

#endif

		void Reset(float xOffset_, float xScale_, float yOffset_, float yScale_, int newSize = 0)
		{
			xOffset = xOffset_;
			xScale = xScale_;
			yOffset = yOffset_;
			yScale = yScale_;
			atl::Array<Point2D>::Reset( newSize );
		}

		void Reset(int newSize = 0)
		{
			atl::Array<Point2D>::Reset( newSize );
		}

		void Reset(float xOffset_, float xScale_, float yOffset_, float yScale_, const void* data_, int count)	// Creates a copy
		{
			xOffset = xOffset_;
			xScale = xScale_;
			yOffset = yOffset_;
			yScale = yScale_;
			atl::Array<Point2D>::Resize( count );
			std::memcpy( (void*)Begin(), data_, count * sizeof(Point2D) );
		}

		void Reset(float xOffset_, float xScale_, float yOffset_, float yScale_, void* data_, int count, bool own)	// Creates a view
		{
			xOffset = xOffset_;
			xScale = xScale_;
			yOffset = yOffset_;
			yScale = yScale_;
			atl::Array<Point2D>::Reset( count, static_cast<Point2D*>(data_), own );
		}

		float			XOffset() const					{ return xOffset; }
		float			XScale() const					{ return xScale; }
		float			X(const int index) const		{ return xOffset + (*this)[index].x * xScale; }
		float			YOffset() const					{ return yOffset; }
		float			YScale() const					{ return yScale; }
		float			Y(const int index) const		{ return yOffset + (*this)[index].y * yScale; }

		void SetXOffset(float xOffset_)						{ xOffset = xOffset_; }
		void SetXScale(float xScale_)						{ xScale = xScale_; }
		void SetXTransform(float xOffset_, float xScale_)	{ xOffset = xOffset_; xScale = xScale_; }
		void SetXTransform(const XTransform& xTransform)	{ XTransform::operator=( xTransform ); }
		void SetYOffset(float yOffset_)						{ yOffset = yOffset_; }
		void SetYScale(float yScale_)						{ yScale = yScale_; }
		void SetYTransform(float yOffset_, float yScale_)	{ yOffset = yOffset_; yScale = yScale_; }
		void SetYTransform(const YTransform& yTransform)	{ YTransform::operator=( yTransform ); }
		void ResetDomain(const GoPointPlot& rhs)				{ XTransform::operator=( rhs ); YTransform::operator=( rhs ); Resize( rhs.Size() ); }

		bool operator == (const GoPointPlot& rhs) const
		{
			return xOffset == rhs.xOffset && xScale == rhs.xScale && yOffset == rhs.yOffset && yScale == rhs.yScale && this->atl::Array<Point2D>::operator==( rhs );
		}

		bool operator != (const GoPointPlot& rhs) const
		{
			return !(operator==( rhs ));
		}
	};

}


#endif
