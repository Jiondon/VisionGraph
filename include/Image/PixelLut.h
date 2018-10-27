//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef PIXEL_LUT_H
#define PIXEL_LUT_H

#include "AVLCommon/Config.h"
#include "PlainTypes.h"

namespace avl
{
	class PixelLut;
	class PixelLutImpl;

	namespace pImpl_helpers
	{
		AVL_FUNCTION void DestructPixelLut(PixelLut&);
		AVL_FUNCTION void CopyPixelLut(const PixelLut&, PixelLut&);
	} // namespace pImpl_helpers

	class PixelLut
	{
	public:
		PixelLut()
			: pImpl(0)
		{

		}

		~PixelLut()
		{
			pImpl_helpers::DestructPixelLut(*this);
		}

		PixelLut(const PixelLut& rhs)
			: pImpl(0)
		{
			pImpl_helpers::CopyPixelLut(rhs, *this);
		}

		PixelLut& operator=(const PixelLut& rhs)
		{
			pImpl_helpers::CopyPixelLut(rhs, *this);
			return *this;
		}

		PixelLutImpl* pImpl;
	};

} // namespace avl

#endif //LOOK_UP_TABLE_H
