//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef BYTE_BUFEFR_H
#define BYTE_BUFEFR_H

#include "ATL/Blob.h"
#include <algorithm>
#include <cstring>

namespace avl
{

	class ByteBuffer
	{
	private:
		atl::Blob data;

	public:
		static const int MaxBufferSize = 512 * 1024 * 1024;	// 512 MB

		ByteBuffer()
		{
		}

		ByteBuffer( const ByteBuffer& rhs )
		: data(rhs.data)
		{
		}

		explicit ByteBuffer( int size )
		{
			Set(size);
		}

		ByteBuffer& operator = ( const ByteBuffer& rhs )
		{
			data = rhs.data;

			return *this;
		}

#ifdef HAS_CPP0X

		ByteBuffer( ByteBuffer&& rhs )
		: data( std::move(rhs.data) )
		{
		}

		ByteBuffer& operator = ( ByteBuffer&& rhs )
		{
			data = std::move(rhs.data);

			return *this;
		}

#endif // HAS_CPP0X

		bool operator == ( const ByteBuffer& rhs ) const
		{
			return data.Size() == rhs.data.Size() && 0 == std::memcmp(data.Pointer(), rhs.data.Pointer(), data.Size());
		}

		bool operator != ( const ByteBuffer& rhs ) const
		{
			return data.Size() != rhs.data.Size() || 0 != std::memcmp(data.Pointer(), rhs.data.Pointer(), data.Size());
		}

		void Resize( int newSize )
		{
			if (newSize < 0 || newSize > MaxBufferSize)
				throw atl::RuntimeError(L"Invalid size for ByteBuffer.");

			if (data.Size() != newSize || (!data.Own() && newSize > 0))
			{
				atl::Blob newData;

				newData.Reset(newSize);
				std::memcpy(newData.Pointer(), data.Pointer(), std::min<int>(newData.Size(), data.Size()));

				if (newData.Size() > data.Size())
					std::memset(reinterpret_cast<char*>(newData.Pointer()) + data.Size(), 0, newData.Size() - data.Size());

				data.Move(newData);
			}
		}

		void Set( int size )
		{
			if (size < 0 || size > MaxBufferSize)
				throw atl::RuntimeError(L"Invalid size for ByteBuffer.");

			data.Reset(size);

			if (data.Size() > 0)
				std::memset(data.Pointer(), 0, data.Size());
		}

		void Set( int size, const ByteBuffer& sourceData )
		{
			if (size < 0 || size > MaxBufferSize)
				throw atl::RuntimeError(L"Invalid size for ByteBuffer.");

			if (sourceData.data.Pointer() == data.Pointer())
			{
				Resize(size);
			}
			else
			{
				data.Reset(size);
				std::memcpy(data.Pointer(), sourceData.data.Pointer(), std::min<int>(data.Size(), sourceData.data.Size()));

				if (data.Size() > sourceData.Size())
					std::memset(reinterpret_cast<char*>(data.Pointer()) + sourceData.Size(), 0, data.Size() - sourceData.Size());
			}
		}

		void Set( const void* newData, int dataSize )
		{
			if (dataSize < 0 || dataSize > MaxBufferSize)
				throw atl::RuntimeError(L"Invalid size for ByteBuffer.");

			this->data.Reset(dataSize);
			std::memcpy(this->data.Pointer(), newData, dataSize);
		}

		void Set( const void* newData, std::size_t dataSize )
		{
			if (dataSize > static_cast<std::size_t>(MaxBufferSize))
				throw atl::RuntimeError(L"Requested ByteBuffer size is too large.");

			this->data.Reset(static_cast<int>(dataSize));
			std::memcpy(this->data.Pointer(), newData, dataSize);
		}

		void SetNotOwn( int size, void* pointer )
		{
			data.Reset(size, pointer);
		}

		int Size( void ) const
		{
			return data.Size();
		}

		bool Empty( void ) const
		{
			return data.Size() == 0;
		}

		void* Data( void )
		{
			if (!data.Own() && data.Size() > 0)
				throw atl::RuntimeError(L"Accessing data of modifiable ByteBuffer that not owns its data.");

			return data.Pointer();
		}

		void* Data( int offset )
		{
			if (!data.Own() && data.Size() > 0)
				throw atl::RuntimeError(L"Accessing data of modifiable ByteBuffer that not owns its data.");

			if (offset < 0 || offset > data.Size())
				throw atl::RuntimeError(L"Invalid offset in ByteBuffer.");

			return reinterpret_cast<atl::byte*>(data.Pointer()) + offset;
		}

		const void* Data( void ) const
		{
			return data.Pointer();
		}

		const void* Data( int offset ) const
		{
			if (offset < 0 || offset > data.Size())
				throw atl::RuntimeError(L"Invalid offset in ByteBuffer.");

			return reinterpret_cast<const atl::byte*>(data.Pointer()) + offset;
		}

		const void* DataEnd( void ) const
		{
			return reinterpret_cast<const atl::byte*>(data.Pointer()) + data.Size();
		}
	};


} // namespace avl

#endif // BYTE_BUFEFR_H
