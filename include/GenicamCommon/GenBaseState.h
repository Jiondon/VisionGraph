//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#ifndef AVL_GEN_BASE_STATE_H
#define AVL_GEN_BASE_STATE_H

namespace avs
{

	struct GenBaseStateImpl
	{
		virtual ~GenBaseStateImpl()
		{
		}
	};


	struct GenBaseState
	{
		GenBaseStateImpl *pImpl;

		GenBaseState()
		: pImpl(0)
		{
		}

		void Release( void )
		{
			delete pImpl;
			pImpl = 0;
		}

		~GenBaseState()
		{
			Release();
		}

	private:
		GenBaseState(const GenBaseState&); //=delete
		GenBaseState& operator=(const GenBaseState&); //=delete
	};
}

#endif // AVL_GEN_BASE_STATE_H
