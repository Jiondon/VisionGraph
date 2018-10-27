//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef ATL_BINARY_WRITER_HXX
#define ATL_BINARY_WRITER_HXX

#include "BinaryWriter.h"
#include "Array.hxx"

namespace atl
{
	inline
	BinaryWriter::BinaryWriter(BinaryMode binaryMode)
		: buffer( internalBuffer ), binaryMode(binaryMode)
	{
	}

	inline
	BinaryWriter::BinaryWriter(int size,BinaryMode binaryMode)
		: buffer( internalBuffer ), binaryMode(binaryMode)
	{
		Reserve(size);
	}

	inline
	BinaryWriter::BinaryWriter(atl::Array<byte>& externalBuffer, BinaryMode binaryMode)
		: buffer( externalBuffer ), binaryMode(binaryMode)
	{
	}

	inline
	void BinaryWriter::Reserve(int size)
	{
		buffer.Reserve(size);
	}

	inline
	int BinaryWriter::Align(int wordSize)
	{
		int bufferSize = buffer.Size();
		int alignedBufferSize = ((bufferSize + wordSize - 1) / wordSize) * wordSize;
		int n = alignedBufferSize - bufferSize;
#ifdef _DEBUG
		int nOld = (wordSize - (int)(((long long)buffer.End()) % (long long)wordSize)) % wordSize;
		if (n != nOld)
			throw atl::RuntimeError("BinaryWriter::Align error!PK403339");
#endif
		for (int i = 0; i < n; ++i)
		{
			buffer.PushBack(0);
		}
		return n;
	}

	inline
	void BinaryWriter::Write(const void* ptr, int size)
	{
		buffer.Insert( (byte*)ptr, (byte*)ptr + size );
	}

	inline
	void BinaryWriter::WriteI32(int value)
	{
		Write(&value, 4);
	}

	inline
	void BinaryWriter::WriteI64(long long value)
	{
		Write(&value, 8);
	}

	inline
	void BinaryWriter::WriteF32(float value)
	{
		Write(&value, 4);
	}

	inline
	void BinaryWriter::WriteF64(double value)
	{
		Write(&value, 8);
	}

	inline
	void BinaryWriter::WriteBool(bool value)
	{
		WriteI32(value ? 1 : 0);
	}

	inline
	void BinaryWriter::WriteBlob(const void* data, int size)
	{
		if (binaryMode == INTERNAL)
		{
			WriteI32(size);
			WritePtr(size != 0 ? data : NULL);	// Note: the pointer may originate from Begin() of an empty Array
		}
		else
		{
			WriteI32(size);
			WritePtr(0);
			Write(data, size);
			Align(4);
		}
	}

	inline
	void BinaryWriter::WriteString( const atl::String& value )
	{
		int count = (int)value.Length();
		WriteI32( count );
		Write(value.CStr16(), (count + 1) * sizeof(atl::wchar16));
		Align(4);
	}

	inline
	void BinaryWriter::WritePtr(const void* ptr)
	{
		WriteI64((long long)ptr);
	}

	inline
	void BinaryWriter::WriteBinary(const void* data, int size)
	{
		Write(data, size);
		Align(4);
	}

	inline
	void* BinaryWriter::ExportData()
	{
		// TODO: Use avl::Array or a hack on std::vector to extract
		//       the data buffer without memcpy
		byte* data = new byte[ buffer.Size() ];
		memcpy( data, buffer.Begin(), buffer.Size() );
		return data;
	}

	inline
	const void* BinaryWriter::GetData() const
	{
		return buffer.Begin();
	}

	inline
	int BinaryWriter::Size() const
	{
		return buffer.Size();
	}
}

#endif