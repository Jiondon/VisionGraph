//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#ifndef CANCELLATION_TYPES_H
#define CANCELLATION_TYPES_H


namespace avl
{

	struct ICancellationProvider
	{
		virtual bool IsAVLWorkCancelled( void ) = 0;
	};

}


#endif // CANCELLATION_TYPES_H
