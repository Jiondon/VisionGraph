//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_PROFILE_H
#define AVL_PROFILE_H

#include "ATL/Utils.h"
#include "ATL/AtlTypes.h"
#include "ATL/Array.hxx"
#include <cstring>

namespace avl
{

	class XTransform
	{
	protected:
		XTransform(float xOffset_, float xScale_) : xOffset(xOffset_), xScale(xScale_) {}

		float xOffset;
		float xScale;
	};

	class Profile : public XTransform, public atl::Array< float >
	{
	public:
		Profile() : XTransform(0.0f, 1.0f)
		{}

		Profile(float xOffset_, float xScale_) : XTransform(xOffset_, xScale_)
		{}

		Profile(float xOffset_, float xScale_, const atl::Array<float>& values_) : XTransform(xOffset_, xScale_), atl::Array<float>(values_)
		{}

		Profile(float xOffset_, float xScale_, void* data_, int count, bool own)
			: XTransform(xOffset_, xScale_)
			, atl::Array<float>(count, static_cast<float*>(data_), own)
		{}

		Profile(float xOffset_, float xScale_, void* data_, int count)
			: XTransform(xOffset_, xScale_)
		{
			const float* newData = (const float*)data_;
			atl::Array<float>::Insert( newData, newData + count );
		}

		Profile(float xOffset_, float xScale_, int count, float value)
			: XTransform(xOffset_, xScale_)
		{
			atl::Array<float>::Reset( count, value );
		}

		Profile(int count, float value)
			: XTransform(0.0f, 1.0f)
		{
			atl::Array<float>::Reset( count, value );
		}

#ifdef HAS_CPP0X

		Profile(const Profile& rhs)
			: XTransform(rhs)
			, atl::Array< float >(rhs)
		{}

		Profile(Profile&& rhs)
			: XTransform(std::move(rhs))
			, atl::Array< float >(std::move(rhs))
		{}

		Profile& operator = (const Profile& rhs)
		{
			XTransform::operator=( rhs );
			atl::Array< float >::operator=( rhs );

			return *this;
		}

		Profile& operator = (Profile&& rhs)
		{
			XTransform::operator=( std::move(rhs) );
			atl::Array< float >::operator=( std::move(rhs) );

			return *this;
		}

#endif

		void Reset(float xOffset_, float xScale_, int newSize = 0, float value = 0.0f)
		{
			xOffset = xOffset_;
			xScale = xScale_;
			atl::Array<float>::Reset( newSize, value );
		}

		void Reset(int newSize = 0, float value = 0.0f)
		{
			atl::Array<float>::Reset( newSize, value );
		}

		void Reset(float xOffset_, float xScale_, const void* data_, int count)	// Creates a copy
		{
			xOffset = xOffset_;
			xScale = xScale_;
			atl::Array<float>::Resize( count );
			std::memcpy( (void*)Begin(), data_, count * sizeof(float) );
		}

		void Reset(float xOffset_, float xScale_, void* data_, int count, bool own)	// Creates a view
		{
			xOffset = xOffset_;
			xScale = xScale_;
			atl::Array<float>::Reset( count, static_cast<float*>(data_), own );
		}

		float			XOffset() const					{ return xOffset; }
		float			XScale() const					{ return xScale; }
		float			X(const int index) const		{ return xOffset + index * xScale; }
		float			X(const float index) const		{ return xOffset + index * xScale; }
		float&			Y(const int index)				{ return (*this)[index]; }
		const float&	Y(const int index) const		{ return (*this)[index]; }

		int				Size() const					{ return atl::Array<float>::Size(); }
		void			Reserve(int newCapacity)		{ return atl::Array<float>::Reserve( newCapacity ); }
		void			Resize(int newSize)				{ return atl::Array<float>::Resize( newSize ); }
		void			Resize(int newSize, float value){ return atl::Array<float>::Resize( newSize, value ); } 
		float*			Begin()							{ return atl::Array<float>::Begin(); }
		float*			End()							{ return atl::Array<float>::End(); }
		const float*	Begin()	const					{ return atl::Array<float>::Begin(); }
		const float*	End()	const					{ return atl::Array<float>::End(); }

		void SetXOffset(float xOffset_)						{ xOffset = xOffset_; }
		void SetXScale(float xScale_)						{ xScale = xScale_; }
		void SetXTransform(float xOffset_, float xScale_)	{ xOffset = xOffset_; xScale = xScale_; }
		void SetXTransform(const XTransform& xTransform)	{ XTransform::operator=( xTransform ); }
		void ResetDomain(const Profile& rhs)				{ XTransform::operator=( rhs ); Resize( rhs.Size() ); }

		bool operator == (const Profile& rhs) const
		{
			return xOffset == rhs.xOffset && xScale == rhs.xScale && this->atl::Array<float>::operator==( rhs );
		}

		bool operator != (const Profile& rhs) const
		{
			return !(operator==( rhs ));
		}
	};

	namespace ProfileProcessingMode
	{
		enum Type
		{
			Bounded,
			Cyclic
		};
	}
}


#endif
