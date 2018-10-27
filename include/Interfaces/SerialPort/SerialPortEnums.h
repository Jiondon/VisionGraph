//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef SERIALPORTENUMS_H
#define SERIALPORTENUMS_H

namespace avl
{
	namespace SerialPortParity
	{
		enum Type
		{
			None,
			Odd,
			Even
		};
	}

	namespace SerialPortStopBits
	{
		enum Type
		{
			One,
			OnePointFive,
			Two
		};
	}

	namespace SerialPortFlowControl
	{
		enum Type
		{
			NoFlowControl,
			SoftwareFlowControl,
			HardwareFlowControl
		};
	}
}

#endif
