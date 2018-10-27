//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef ATL_BLOB_H
#define ATL_BLOB_H

#include "Platform.h"
#include "AtlMemory.h"
#include "Error.h"
#include <cstring>

namespace atl
{

	class Blob
	{
	public:
		Blob();
		Blob( const Blob& rhs );
		~Blob();

		Blob& operator = ( const Blob& rhs );

#ifdef HAS_CPP0X

		Blob( Blob&& rhs );
		Blob& operator = ( Blob&& rhs );

#endif // HAS_CPP0X

		int		Size() const	{ return size; }
		void*	Handle() const	{ return handle; }
		void*	Pointer() const	{ return pointer; }
		bool	Own() const		{ return handle != 0; }

		void	Delete();
		void	Reset( int size );
		void	Reset( int size, void* pointer );

		void	Move( Blob& rhs );
		void*	Release();

	private:
		int		size;		// number of meaningful bytes (starting from 'pointer')
		void*	handle;		// pointer to the beginning of the buffer that has to be deleted (NULL = data are owned elsewhere)
		void*	pointer;	// pointer to where the data start (taking into account a possible alignment)
	};

	inline Blob::Blob()
		: size(0)
		, handle(0)
		, pointer(0)
	{
	}

	inline Blob::Blob(const Blob& rhs)
		: handle(0)
	{
		// deep copy
		Reset(rhs.size);
		std::memcpy(pointer, rhs.pointer, size);
	}

	inline Blob::~Blob()
	{
		Delete();
	}

	inline Blob& Blob::operator = (const Blob& rhs)
	{
		if (&rhs != this)
		{
			Reset(rhs.size);
			std::memcpy(pointer, rhs.pointer, rhs.size);
		}

		return *this;
	}

#ifdef HAS_CPP0X

	inline Blob::Blob( Blob&& rhs )
	{
		size = rhs.size;
		pointer = rhs.pointer;
		handle = rhs.handle;

		rhs.size = 0;
		rhs.pointer = 0;
		rhs.handle = 0;
	}

	inline Blob& Blob::operator = ( Blob&& rhs )
	{
		Move(rhs);

		return *this;
	}

#endif // HAS_CPP0X


	inline void Blob::Delete()
	{
		pointer = 0;
		size = 0;
		AtlFree(handle);
		handle = 0;
	}

	inline void Blob::Reset( int newSize )
	{
		Delete();

		if (newSize > 0)
		{
			pointer = handle = AtlAlloc( (std::size_t)newSize );
			if (!handle)
				throw atl::RuntimeError("Blob memory allocation error.");

			this->size = newSize;
		}
	}

	inline void Blob::Reset( int newSize, void* newPointer )
	{
		Delete();
		this->size    = newSize;
		this->pointer = newPointer;
	}

	inline void Blob::Move( Blob& rhs )
	{
		if (&rhs != this)
		{
			Delete();

			size = rhs.size;
			pointer = rhs.pointer;
			handle = rhs.handle;

			rhs.size = 0;
			rhs.pointer = 0;
			rhs.handle = 0;
		}
	}

	inline void* Blob::Release()
	{
		void* result = handle;
		handle = 0;
		pointer = 0;
		return result;
	}

} // namespace atl


#endif
