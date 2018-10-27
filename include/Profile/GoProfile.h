//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should be included directly in your program.
//

#ifndef AVL_GOPROFILE_H
#define AVL_GOPROFILE_H

#include "Profile/Profile.h"

namespace avl
{

	class YTransform
	{
	protected:
		YTransform(float yOffset_, float yScale_) : yOffset(yOffset_), yScale(yScale_) {}

		float yOffset;
		float yScale;
	};

	class GoProfile : public YTransform, public Profile
	{
	public:
		GoProfile() : YTransform(0.0f, 1.0f), Profile()
		{}

		GoProfile(float xOffset_, float xScale_, float yOffset_, float yScale_) : YTransform(yOffset_, yScale_), Profile(xOffset_, xScale_)
		{}

		GoProfile(float xOffset_, float xScale_, float yOffset_, float yScale_, const atl::Array<float>& values_) : YTransform(yOffset_, yScale_), Profile(xOffset_, xScale_, values_)
		{}

		GoProfile(float xOffset_, float xScale_, float yOffset_, float yScale_, void* data_, int count, bool own)
			: YTransform(yOffset_, yScale_)
			, Profile(xOffset_, xScale_, data_, count, own)
		{}

		GoProfile(float xOffset_, float xScale_, float yOffset_, float yScale_, void* data_, int count)
			: YTransform(yOffset_, yScale_)
			, Profile(xOffset_, xScale_, data_, count)
		{}

		GoProfile(float xOffset_, float xScale_, float yOffset_, float yScale_, int count, float value)
			: YTransform(yOffset_, yScale_), Profile(xOffset_, xScale_, count, value)
		{}

		GoProfile(int count, float value)
			: YTransform(0.0f, 1.0f), Profile(count, value)
		{}

#ifdef HAS_CPP0X

		GoProfile(const GoProfile& rhs)
			: YTransform(rhs)
			, Profile(rhs)
		{}

		GoProfile(GoProfile&& rhs)
			: YTransform(std::move(rhs))
			, Profile(std::move(rhs))
		{}

		GoProfile& operator = (const GoProfile& rhs)
		{
			YTransform::operator=( rhs );
			Profile::operator=( rhs );

			return *this;
		}

		GoProfile& operator = (GoProfile&& rhs)
		{
			YTransform::operator=( std::move(rhs) );
			Profile::operator=( std::move(rhs) );

			return *this;
		}

#endif

		void Reset(float xOffset_, float xScale_, float yOffset_, float yScale_, int newSize = 0, float value = 0.0f)
		{
			xOffset = xOffset_;
			xScale = xScale_;
			yOffset = yOffset_;
			yScale = yScale_;
			atl::Array<float>::Reset( newSize, value );
		}

		void Reset(int newSize = 0, float value = 0.0f)
		{
			atl::Array<float>::Reset( newSize, value );
		}

		void Reset(float xOffset_, float xScale_, float yOffset_, float yScale_, const void* data_, int count)	// Creates a copy
		{
			yOffset = yOffset_;
			yScale = yScale_;
			Profile::Reset( xOffset_, xScale_, data_, count );
		}

		void Reset(float xOffset_, float xScale_, float yOffset_, float yScale_, void* data_, int count, bool own)	// Creates a view
		{
			yOffset = yOffset_;
			yScale = yScale_;
			Profile::Reset( xOffset_, xScale_, data_, count, own );
		}

		float			XOffset() const					{ return xOffset; }
		float			XScale() const					{ return xScale; }
		float			X(const int index) const		{ return xOffset + index * xScale; }
		float			X(const float index) const		{ return xOffset + index * xScale; }
		float			YOffset() const					{ return yOffset; }
		float			YScale() const					{ return yScale; }
		float			Y(const int index) const		{ return yOffset + (*this)[index] * yScale; }
		float			Y(const float y) const			{ return yOffset + y * yScale; }

		void SetYOffset(float yOffset_)						{ yOffset = yOffset_; }
		void SetYScale(float yScale_)						{ yScale = yScale_; }
		void SetYTransform(float yOffset_, float yScale_)	{ yOffset = yOffset_; yScale = yScale_; }
		void SetYTransform(const YTransform& yTransform)	{ YTransform::operator=( yTransform ); }
		void ResetDomain(const GoProfile& rhs)				{ YTransform::operator=( rhs ); Profile::ResetDomain( rhs ); }

		bool operator == (const GoProfile& rhs) const
		{
			return yOffset == rhs.yOffset && yScale == rhs.yScale && this->Profile::operator==( rhs );
		}

		bool operator != (const GoProfile& rhs) const
		{
			return !(operator==( rhs ));
		}
	};

}


#endif
