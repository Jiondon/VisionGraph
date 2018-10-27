//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef ATL_BINARY_WRITER_H
#define ATL_BINARY_WRITER_H

#include "AtlTypes.h"
#include "AtlString.h"
#include "Array.hxx"


namespace atl
{
	class BinaryWriter
	{
	public:
		explicit BinaryWriter( BinaryMode binaryMode );
		BinaryWriter( int size, BinaryMode binaryMode );
		BinaryWriter( atl::Array<atl::byte>& externalArray, BinaryMode binaryMode );

		void Reserve(int size);
		void WriteI32(int value);
		void WriteI64(long long value);
		void WriteF32(float value);
		void WriteF64(double value);
		void WriteBool(bool value);
		void WriteBlob(const void* buffer, int size);
		void WriteString(const atl::String& value);
		void WritePtr(const void* ptr);
		void WriteBinary(const void* data, int size);

		int Size() const;
		void* ExportData();
		const void* GetData() const;

		~BinaryWriter()
		{}

	private:
		BinaryWriter& operator = ( const BinaryWriter& );

	private:
		Array<byte>		internalBuffer;
		Array<byte>&	buffer;			// internal or external
		BinaryMode		binaryMode;

	private:
		int Align(int wordSize);
		void Write(const void* ptr, int size);
	};
}

#endif
