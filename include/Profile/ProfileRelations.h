//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_PROFILERELATIONS_H
#define AVL_PROFILERELATIONS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Profile/Profile.h"

namespace avl
{


	/// <summary>Checks whether values in the first profile are greater or equal than corresponding values in the second profile</summary>
	/// <param name="inProfile1">Input profile1.</param>
	/// <param name="inProfile2">Input profile2.</param>
	AVL_FUNCTION void TestProfileDominatesProfile
	(
		const avl::Profile&	inProfile1,
		const avl::Profile&	inProfile2,
		bool&				outDominates
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_PROFILERELATIONS_H

