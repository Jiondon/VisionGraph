//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef GRAY_MODEL_H
#define GRAY_MODEL_H

#include "AVLCommon/Config.h"

namespace avl
{

	class GrayModel;
	class GrayModelImpl;

	namespace pImpl_helpers
	{
		/* For internal use only */
		AVL_FUNCTION void DestructGrayModel(GrayModel&);
		AVL_FUNCTION void CopyGrayModel(const GrayModel&, GrayModel&);
		AVL_FUNCTION bool TestGrayModelEqual(const GrayModel&, const GrayModel&);
	}

	class GrayModel
	{
	public:
		GrayModel() : pImpl(0) {}

		~GrayModel()
		{
			pImpl_helpers::DestructGrayModel(*this);
		}

		GrayModel(const GrayModel& inGrayModel) : pImpl(0)
		{
			pImpl_helpers::CopyGrayModel(inGrayModel, *this);
		}

		GrayModel& operator=(const GrayModel& inGrayModel)
		{
			pImpl_helpers::CopyGrayModel(inGrayModel, *this);
			return *this;
		}

		bool operator == (const GrayModel& rhs) const
		{
			return pImpl_helpers::TestGrayModelEqual(*this, rhs);
		}
		
		bool operator != (const GrayModel& rhs) const
		{
			return !(operator==(rhs));
		}
		
		GrayModelImpl* pImpl;
	};

}

#endif // GRAY_MODEL_H
