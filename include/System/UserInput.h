//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_USERINPUT_H
#define AVL_USERINPUT_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.hxx"

namespace avl
{


	/// <summary>Checks if the specified keyboard key is down and if it is toggled.</summary>
	/// <param name="inKeyCode">Virtual key code. See documentation for a complete table.</param>
	/// <param name="outIsDown">Informs if the specified keyboard key is being pressed at the moment.</param>
	/// <param name="outIsToggled">Informs about the state. Important for keys such as CapsLock.</param>
	AVL_FUNCTION void GetKeyboardKeyState
	(
		const int	inKeyCode,		
		bool&		outIsDown,		
		bool&		outIsToggled	
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns virtual key codes of the pressed keys or NULL if no key was pressed.</summary>
	/// <param name="inNumKeypad">Determines whether to analyze keys from numeric keypad. Default value: True.</param>
	/// <param name="inAlpha">Determines whether to analyze keys from alphanumeric keypad. Default value: True.</param>
	/// <param name="inSpecial">Determines whether to analyze special keys.</param>
	/// <param name="inFKeys">Determines whether to analyze functional keys (F1 to F24).</param>
	/// <param name="outKeyCodes">Virtual key codes of the pressed keys. See documentation for a complete table.</param>
	AVL_FUNCTION void GetKeyboardKeys
	(
		const bool	inNumKeypad,	
		const bool	inAlpha,		
		const bool	inSpecial,		
		const bool	inFKeys,		
		atl::Array<int>&	outKeyCodes		
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_USERINPUT_H

