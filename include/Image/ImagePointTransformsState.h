//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef IMAGE_POINT_TRANSFORMS_STATE_H
#define IMAGE_POINT_TRANSFORMS_STATE_H

#include "ATL/AtlTypes.h"
#include "ATL/Array.h"
#include "Basic/Types.h"
#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "Image/PlainTypes.h"

namespace avl
{

	class ImagePointTransformsState;
	class ImagePointTransformsStateImpl;

	namespace pImpl_helpers
	{
		AVL_FUNCTION void DestructImagePointTransformsState( ImagePointTransformsState& state );
	}

	class ImagePointTransformsState : public BaseState
	{
	public:
		ImagePointTransformsStateImpl* pImpl;

		ImagePointTransformsState()
		: pImpl(0)
		{
		}

		~ImagePointTransformsState()
		{
			pImpl_helpers::DestructImagePointTransformsState(*this);
		}

	private:
		ImagePointTransformsState( const ImagePointTransformsState& );				// = delete
		ImagePointTransformsState& operator = ( const ImagePointTransformsState& );	// = delete
	};

	struct ColorizeImageState : public BaseState
	{
		atl::Array<atl::uint8> indices;

		int maxValue, minValue;
		bool negate;

		ColorizeImageState()
			: indices(65536), maxValue(0), minValue(0), negate(false)
		{}
	};

	struct LUTTransformImageState : public BaseState
	{
		avl::Pixel indices[65536];
		bool gradient;
		atl::Array<int> points;
		atl::Array<avl::Pixel> colors;
		avl::PlainType::Type type;

		LUTTransformImageState() : gradient(false), type(avl::PlainType::UInt8)
		{}
	};

} // namespace avl

#endif // IMAGE_POINT_TRANSFORMS_STATE_H
