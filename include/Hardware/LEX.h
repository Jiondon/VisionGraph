//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_LEX_H
#define AVL_LEX_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "Hardware/LEX/LexInterface.h"

namespace avl
{


	
	struct Lex_BaseStructState : public BaseState
	{
		LexInterface* lex;

		Lex_BaseStructState()
			: lex(nullptr)
		{
		}

		~Lex_BaseStructState()
		{
			delete lex;
		}

	private:
		Lex_BaseStructState(const Lex_BaseStructState&); //=delete
		Lex_BaseStructState& operator=(const Lex_BaseStructState&); //=delete
	};

	typedef Lex_BaseStructState Lex_SetDigitalOutputState;
	typedef Lex_BaseStructState Lex_GetDigitalInputState;



	/// <summary>Sets a digital output state of LEX computers.</summary>
	/// <param name="inOutput">Number of output to change.</param>
	/// <param name="inState">State of pin output to set.</param>
	AVL_FUNCTION void Lex_SetDigitalOutput
	(
		Lex_SetDigitalOutputState&	ioState,
		const int					inOutput,	
		bool						inState		
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets a digital input state of LEX computers.</summary>
	/// <param name="inInput">Number of pin to read.</param>
	/// <param name="outState">Read state of chosen pin.</param>
	AVL_FUNCTION void Lex_GetDigitalInput
	(
		Lex_GetDigitalInputState&	ioState,
		const int					inInput, 
		bool&						outState 
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_LEX_H

