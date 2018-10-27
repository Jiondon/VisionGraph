//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef EDGE_MODEL_H
#define EDGE_MODEL_H

#include "AVLCommon/Config.h"

namespace avl
{

	class EdgeModel;
	class EdgeModelImpl;

	namespace pImpl_helpers
	{
		/* For internal use only */
		AVL_FUNCTION void DestructEdgeModel(EdgeModel&);
		AVL_FUNCTION void CopyEdgeModel(const EdgeModel&, EdgeModel&);
		AVL_FUNCTION bool TestEdgeModelEqual(const EdgeModel&, const EdgeModel&);
	}

	class EdgeModel
	{
	public:
		EdgeModel() : pImpl(0) {}

		~EdgeModel()
		{
			pImpl_helpers::DestructEdgeModel(*this);
		}

		EdgeModel(const EdgeModel& inEdgeModel) : pImpl(0)
		{
			pImpl_helpers::CopyEdgeModel(inEdgeModel, *this);
		}

		EdgeModel& operator=(const EdgeModel& inEdgeModel)
		{
			pImpl_helpers::CopyEdgeModel(inEdgeModel, *this);
			return *this;
		}

		bool operator == (const EdgeModel& rhs) const
		{
			return pImpl_helpers::TestEdgeModelEqual(*this, rhs);
		}
		
		bool operator != (const EdgeModel& rhs) const
		{
			return !(operator==(rhs));
		}
		
		EdgeModelImpl* pImpl;
	};

}

#endif // EDGE_MODEL_H
