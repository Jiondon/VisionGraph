//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef LEX_INTERFACE_H
#define LEX_INTERFACE_H

typedef unsigned char BYTE;

class LexInterface
{
public:
	virtual ~LexInterface() {}

	virtual bool Init() = 0;
	virtual BYTE& Address() = 0;

	virtual void SetDigitalOutput(int inOutput, bool value) = 0;
	virtual bool GetDigitalInput(int inInput) = 0;
};


#endif //LEX_INTERFACE_H