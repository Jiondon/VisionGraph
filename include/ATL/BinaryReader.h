//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef ATL_BINARY_READER_H
#define ATL_BINARY_READER_H

#include "AtlTypes.h"
#include "AtlString.h"
#include "NumericRange.h"

namespace atl
{
	template<typename TX> class BaseBinaryReaderType;

	template<>
	class BaseBinaryReaderType<void*>
	{
	public:
		typedef void* PtrType;
		typedef atl::byte* BytePtrType;
	};

	template<>
	class BaseBinaryReaderType<const void*>
	{
	public:
		typedef const void* PtrType;
		typedef const atl::byte* BytePtrType;
	};

	template<typename TX>
	class BaseBinaryReader : public BaseBinaryReaderType<TX>
	{
	public:
		typedef BaseBinaryReaderType<TX> MyBase;
		typedef typename MyBase::PtrType PtrType;
		typedef typename MyBase::BytePtrType BytePtrType;

		int ReadI32()
		{
			const int new_capacity = capacity - (int)sizeof(int);
			if (new_capacity < 0)
				DataStreamError();
			capacity = new_capacity;

			int value = *reinterpret_cast<const int*>(ptr);
			ptr += sizeof(int);
			return value;
		}

		long long ReadI64()
		{
			const int new_capacity = capacity - (int)sizeof(long long);
			if (new_capacity < 0)
				DataStreamError();
			capacity = new_capacity;

			long long value = 0;
			const size_t size = sizeof(long long);
			memcpy(&value, ptr, size);
			ptr += size;
			return value;
		}

		float ReadF32()
		{
			const int new_capacity = capacity - (int)sizeof(float);
			if (new_capacity < 0)
				DataStreamError();
			capacity = new_capacity;

			float value = *reinterpret_cast<const float*>(ptr);
			ptr += sizeof(float);
			return value;
		}

		double ReadF64()
		{
			const int new_capacity = capacity - (int)sizeof(double);
			if (new_capacity < 0)
				DataStreamError();
			capacity = new_capacity;

			double value = 0.0;
			const size_t size = sizeof(double);
			memcpy(&value, ptr, size);
			ptr += size;
			return value;
		}

		bool ReadBool()
		{
			return ReadI32() != 0;
		}

		atl::String ReadString()
		{
			// Warning: If you change this, change also StringType::MeasureStream
			const int count = (ReadI32() + 1) * sizeof(atl::wchar16);

			const int new_capacity = capacity - count;
			if (new_capacity < 0 || count < 0)
				DataStreamError();
			capacity = new_capacity;

			atl::String value( reinterpret_cast<const atl::wchar16*>(ptr) );
			ptr += count;
			Align(4);

			return value;
		}

		void SkipString()
		{
			// Warning: If you change this, change also StringType::MeasureStream
			const int count = (ReadI32() + 1) * sizeof(atl::wchar16);

			const int new_capacity = capacity - count;
			if (new_capacity < 0 || count < 0)
				DataStreamError();
			capacity = new_capacity;

			ptr += count;
			Align(4);
		}

		PtrType ReadPtr()
		{
			return reinterpret_cast<PtrType>(ReadI64());
		}

		PtrType ReadBinary(int size)
		{
			const int new_capacity = capacity - size;
			if (new_capacity < 0 || size < 0)
				DataStreamError();
			capacity = new_capacity;

			PtrType result = ptr;
			ptr += size;
			Align(4);
			return result;
		}

	protected:
		BaseBinaryReader(PtrType buffer, int bufferSize)
			: ptr(reinterpret_cast<BytePtrType>(buffer))
			, capacity(bufferSize)
		{
		}

		void DataStreamError()
		{
			throw atl::IoError("Error in serialized data stream.");
		}

		int Align(int wordSize)
		{
			int n = (wordSize - (int)(((long long)ptr) % (long long)wordSize)) % wordSize;
			ptr += n;
			capacity -= n;
			return n;
		}

		BytePtrType ptr;
		int capacity;
	};

	class BinaryReader : public BaseBinaryReader<void*>
	{
	public:
		explicit BinaryReader(void* buffer, BinaryMode mode = INTERNAL, int bufferSize = atl::NumericRange<int>::Max());

		bool		ReadBlob(void*& data, int& size);
		BinaryMode	GetMode( void );

	protected:
		BinaryMode binaryMode;
	};

	class ConstBinaryReader : public BaseBinaryReader<const void*>
	{
	public:
		explicit ConstBinaryReader(const void* buffer, int bufferSize = atl::NumericRange<int>::Max());
	};
}

#endif
