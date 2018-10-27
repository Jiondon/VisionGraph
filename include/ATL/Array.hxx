//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef ATL_ARRAY_HXX
#define ATL_ARRAY_HXX

#include "Array.h"
#include "Error.h"
#include "AtlMemory.h"
#include <memory>
#include <cstring>
#include <cassert>


#pragma push_macro("new")
#ifdef new
#	undef new
#endif

namespace atl
{
	namespace ArrayInternal
	{
		template<typename T> inline
		typename atl::enable_if_not<atl::has_trivial_destructor<T>::value>::type
		AllocatorDestruct_Impl( T* begin, T* end )
		{
			T* p = begin;
			while (p != end)
			{
				p->~T();
				++p;
			}
		}

		template<typename T> inline
		typename atl::enable_if<atl::has_trivial_destructor<T>::value>::type
		AllocatorDestruct_Impl( T*, T* )
		{
			// Do nothing
		}

		template<typename T> inline
		typename atl::enable_if_not<atl::has_trivial_destructor<T>::value>::type
		AllocatorDestructSingle_Impl(T* element)
		{
			element->~T();
		}

		template<typename T> inline
		typename atl::enable_if<atl::has_trivial_destructor<T>::value>::type
		AllocatorDestructSingle_Impl(T*)
		{
			// Do nothing
		}

		template<typename T> inline
		typename atl::enable_if_not<atl::has_trivial_copy_constructor<T>::value>::type
		AllocatorCopyConstruct_Impl( T* dst, const T* begin, const T* end )
		{
			T* p = dst;
			try
			{
				const T* q = begin;
				while (q != end)
				{
					new (p) T(*q);
					++p;
					++q;
				}
			}
			catch (...)
			{
				AllocatorDestruct_Impl(dst, p);
				throw;
			}
		}

		template<typename T> inline
		typename atl::enable_if<atl::has_trivial_copy_constructor<T>::value>::type
		AllocatorCopyConstruct_Impl( T* dst, const T* begin, const T* end )
		{
			std::memmove(dst, begin, reinterpret_cast<const char*>(end) - reinterpret_cast<const char*>(begin));
		}

		template<typename T> inline
		typename atl::enable_if_not<atl::has_trivial_copy_constructor<T>::value>::type
		AllocatorMoveConstruct_Impl( T* dst, T* begin, T* end )
		{
			T* p = dst;
			try
			{
				T* q = begin;
				while (q != end)
				{
#ifdef HAS_CPP0X
					new (p) T(std::move(*q));
#else
					new (p) T(*q);
#endif
					++p;
					++q;
				}
			}
			catch (...)
			{
				AllocatorDestruct_Impl(dst, p);
				throw;
			}
		}

		template<typename T> inline
		typename atl::enable_if<atl::has_trivial_copy_constructor<T>::value>::type
		AllocatorMoveConstruct_Impl( T* dst, const T* begin, const T* end )
		{
			std::memmove(dst, begin, reinterpret_cast<const char*>(end) - reinterpret_cast<const char*>(begin));
		}

		template<typename T> inline
		typename atl::enable_if_not<atl::has_trivial_copy_assign<T>::value>::type
		AllocatorMoveAssign_Impl(T* dst, T* begin, T* end)
		{
			T* p = dst;
			T* q = begin;
			while (q != end)
			{
#ifdef HAS_CPP0X
				*p = std::move(*q);
#else
				*p = *q;
#endif
				++p;
				++q;
			}
		}

		template<typename T> inline
		typename atl::enable_if<atl::has_trivial_copy_assign<T>::value>::type
		AllocatorMoveAssign_Impl(T* dst, const T* begin, const T* end)
		{
			std::memmove(dst, begin, reinterpret_cast<const char*>(end) - reinterpret_cast<const char*>(begin));
		}

		template<typename T> inline
		typename atl::enable_if_not<atl::has_trivial_copy_assign<T>::value>::type
		AllocatorCopyAssign_Impl( T* dst, const T* begin, const T* end )
		{
			T* p = dst;
			const T* q = begin;

			while (q != end)
				*(p++) = *(q++);
		}

		template<typename T> inline
		typename atl::enable_if<atl::has_trivial_copy_assign<T>::value>::type
		AllocatorCopyAssign_Impl( T* dst, const T* begin, const T* end )
		{
			std::memmove(dst, begin, reinterpret_cast<const char*>(end) - reinterpret_cast<const char*>(begin));
		}

		template<typename T> inline
		typename atl::enable_if_not<atl::has_trivial_copy_assign<T>::value>::type
		AllocatorMoveAssignBackwards_Impl(T* dst, T* begin, T* end)
		{
			T* p = dst + (end - begin);
			T* q = end;
			while (begin != q)
			{
				--p;
				--q;

#ifdef HAS_CPP0X
				*p = std::move(*q);
#else
				*p = *q;
#endif
			}
		}

		template<typename T> inline
		typename atl::enable_if<atl::has_trivial_copy_assign<T>::value>::type
		AllocatorMoveAssignBackwards_Impl(T* dst, const T* begin, const T* end)
		{
			std::memmove(dst, begin, reinterpret_cast<const char*>(end) - reinterpret_cast<const char*>(begin));
		}

		template <typename T> inline
		typename atl::enable_if_not<atl::has_trivial_default_constructor<T>::value>::type
		AllocatorConstruct_Impl( T* begin, T* end )
		{
			T* p = begin;
			try
			{
				while (p != end)
				{
					new (p) T();
					++p;
				}
			}
			catch (...)
			{
				AllocatorDestruct_Impl(begin, p);
				throw;
			}
		}

		template <typename T> inline
		typename atl::enable_if<atl::has_trivial_default_constructor<T>::value>::type
		AllocatorConstruct_Impl( T* begin, T* end )
		{
			T* p = begin;
			while (p != end)
				new (p++) T();
		}

		template <typename T> inline
		typename atl::enable_if_not<atl::has_trivial_copy_constructor<T>::value>::type
		AllocatorConstruct_Impl( T* begin, T* end, const T& value )
		{
			T* p = begin;
			try
			{
				while (p != end)
				{
					new (p) T(value);
					++p;
				}
			}
			catch (...)
			{
				AllocatorDestruct_Impl(begin, p);
				throw;
			}
		}

		template <typename T> inline
		typename atl::enable_if<atl::has_trivial_copy_constructor<T>::value>::type
		AllocatorConstruct_Impl( T* begin, T* end, const T& value )
		{
			T* p = begin;
			while (p != end)
				new (p++) T(value);
		}

	} // namespace ArrayInternal

	template <typename T>
	T& Array<T>::Front()
	{
		assert(size);
		return *data;
	}

	template <typename T>
	const T& Array<T>::Front() const
	{
		assert(size);
		return *data;
	}

	template <typename T>
	T& Array<T>::Back()
	{
		assert(size);
		return *(data + size -1);
	}

	template <typename T>
	const T& Array<T>::Back() const
	{
		assert(size);
		return *(data + size -1);
	}

	template <typename T>
	Array<T>::Array()
		: data(nullptr)
		, size(0)
		, capacity(0)
	{
	}


	template <typename T>
	Array<T>::Array( int size )
		: data(nullptr)
		, size(0)
		, capacity(0)
	{
		Reset(size);
	}


	template <typename T>
	Array<T>::Array( int size, const T& value )
		: data(nullptr)
		, size(0)
		, capacity(0)
	{
		Reset( size, value );
	}


	template <typename T>
	Array<T>::Array( int size, T* data, bool own )
		: data(data)
		, size(size)
		, capacity(own ? size : 0)
	{
		static_assert(atl::has_trivial_copy_constructor<T>::value && atl::has_trivial_destructor<T>::value,
			"Types with no trivial copy constructor are not supported in this constructor.");
	}


	template <typename T>
	Array<T>::Array( const T* begin, const T* end )
		: data(nullptr)
		, size(0)
		, capacity(0)
	{
		Insert( begin, end );
	}


	template <typename T>
	Array<T>::Array( const Array& rhs )
		: data(nullptr)
		, size(0)
		, capacity(0)
	{
		Insert( rhs.Begin(), rhs.End() );
	}


	template <typename T>
	Array<T>& Array<T>::operator = ( const Array& rhs )
	{
		if ( this == &rhs )
			return *this;

		Reset();
		Insert( rhs.Begin(), rhs.End() );

		return *this;
	}


	template <typename T>
	bool Array<T>::operator == ( const Array& rhs ) const
	{
		if ( Size() != rhs.Size() )
		{
			return false;
		}
		else
		{
			for ( int i = 0; i < Size(); i++ )
			{
				if ( !((*this)[i] == rhs[i]) )
					return false;
			}

			return true;
		}
	}


	template <typename T>
	bool Array<T>::operator != ( const Array& rhs ) const
	{
		return !(operator==(rhs));
	}


	template <typename T>
	void Array<T>::Enlarge(int requestedCapacity)
	{
		int currentSize = IsDataOwn() ? Capacity() : Size();
		int newCapacity = currentSize > 0 ? currentSize * 2 : 8;

		if (requestedCapacity > newCapacity)
			newCapacity = requestedCapacity;

		T* newData = Alloc(newCapacity);

		if (data)
		{
			try
			{
				ArrayInternal::AllocatorMoveConstruct_Impl(newData, data, data + size);
			}
			catch (...)
			{
				Free(newData);
				throw;
			}

			if (IsDataOwn())
			{
				ArrayInternal::AllocatorDestruct_Impl(data, data + size);
				Free(data);
			}
		}

		this->data = newData;
		this->capacity = newCapacity;
	}


	template <typename T>
	void Array<T>::Delete( void )
	{
		if (IsDataOwn())
		{
			ArrayInternal::AllocatorDestruct_Impl(data, data + size);
			Free(data);
		}
		data = nullptr;
		size = 0;
		capacity = 0;
	}


	template <typename T>
	bool Array<T>::IsDataOwn( void ) const
	{
		return Capacity() > 0;
	}

	// Memory allocation without construction
	template <typename T>
	T* Array<T>::Alloc( int n )
	{
		if (static_cast<std::size_t>(n) > (2000000000 / sizeof(T)))
			throw atl::OutOfMemoryError("Allocation error - array size too big.");

		void* ptr = AtlAlloc(static_cast<std::size_t>(n) * sizeof(T));
		if (!ptr)
			throw atl::OutOfMemoryError("Allocation error - array size too big.");

		return static_cast<T*>(ptr);
	}


	// Memory freeing without destruction
	template <typename T>
	void Array<T>::Free( T* ptr )
	{
		AtlFree( static_cast<void*>(ptr) );
	}


	template<typename T>
	void Array<T>::Clear()
	{
		ArrayInternal::AllocatorDestruct_Impl(data, data + size);
		this->size = 0;
	}


	template <typename T>
	T* Array<T>::Release()
	{
		if (capacity == 0)
			return nullptr;

		T* result = data;

		data = nullptr;
		size = 0;
		capacity = 0;

		return result;
	}


	// Recreate the array
	template <typename T>
	void Array<T>::Reset( int newSize )
	{
		if (newSize <= 0)
		{
			ArrayInternal::AllocatorDestruct_Impl(data, data + size);
			this->size = 0;
		}
		else if (this->capacity < newSize || !this->data)
		{
			// memory reallocation
			Delete();
			this->data = Alloc(newSize);
			this->capacity = newSize;
			ArrayInternal::AllocatorConstruct_Impl(data, data + newSize);
			this->size = newSize;
		}
		else
		{
			// memory reuse with explicit recreation
			ArrayInternal::AllocatorDestruct_Impl(data, data + size);
			this->size = 0;
			ArrayInternal::AllocatorConstruct_Impl(data, data + newSize);
			this->size = newSize;
		}
	}

	// Recreate the array
	template <typename T>
	void Array<T>::Reset( int newSize, const T& value )
	{
		if (newSize <= 0)
		{
			ArrayInternal::AllocatorDestruct_Impl(data, data + size);
			this->size = 0;
		}
		else if (this->capacity < newSize || !this->data)
		{
			// memory reallocation
			Delete();
			this->data = Alloc(newSize);
			this->capacity = newSize;
			ArrayInternal::AllocatorConstruct_Impl(data, data + newSize, value);
			this->size = newSize;
		}
		else
		{
			// memory reuse with explicit recreation
			ArrayInternal::AllocatorDestruct_Impl(data, data + size);
			this->size = 0;
			ArrayInternal::AllocatorConstruct_Impl(data, data + newSize, value);
			this->size = newSize;
		}
	}

	template <typename T>
	void Array<T>::Reset( int newSize, T* _data, bool own )
	{
		static_assert(atl::has_trivial_copy_constructor<T>::value && atl::has_trivial_destructor<T>::value,
			"Types with no trivial copy constructor are not supported in this constructor.");

		Delete();
		this->data = _data;
		this->size = newSize;
		if (own)
		{
			this->capacity = newSize;
		}
		else
		{
			this->capacity = 0;
		}
	}


	template <typename T>
	Array<T>::~Array()
	{
		Delete();
	}


	template <typename T>
	void Array<T>::Resize( int newSize )
	{
		if (!data || newSize <= 0)
		{
			Reset(newSize);
		}
		else if (newSize < size)
		{
			ArrayInternal::AllocatorDestruct_Impl(data + newSize, data + size);
			size = newSize;
		}
		else if (newSize > size)
		{
			Reserve(newSize);
			ArrayInternal::AllocatorConstruct_Impl(data + size, data + newSize);
			size = newSize;
		}
	}


	template <typename T>
	void Array<T>::Resize( int newSize, const T& value )
	{
		if (!data || newSize <= 0)
		{
			Reset(newSize, value);
		}
		else if (newSize < size)
		{
			ArrayInternal::AllocatorDestruct_Impl(data + newSize, data + size);
			size = newSize;
		}
		else if (newSize > size)
		{
			Reserve(newSize);
			ArrayInternal::AllocatorConstruct_Impl(data + size, data + newSize, value);
			size = newSize;
		}
	}


	template <typename T>
	void Array<T>::Reserve( int requestedCapacity )
	{
		if (requestedCapacity > 0 && (Capacity() < requestedCapacity || !data))
		{
			Enlarge(requestedCapacity);
		}
	}

	template <typename T>
	T& Array<T>::operator[] (int k)
	{
		assert(0 <= k && k < size);
		return *(data + k);
	}

	template <typename T>
	const T& Array<T>::operator[] (int k) const
	{
		assert(0 <= k && k < size);
		return *(data + k);
	}

	template <typename T>
	void Array<T>::PushBack( const T& value )
	{
		if ( size >= capacity )
		{
			Enlarge();
		}

		new (data + size) T(value);
		size++;
	}


	template <typename T>
	void Array<T>::PopBack()
	{
		assert(size > 0);
		size--;
		ArrayInternal::AllocatorDestructSingle_Impl(data + size);
	}


	template <typename T>
	void Array<T>::Insert( int index, const T& value )
	{
		Insert(data + index, value);
	}


	template <typename T>
	void Array<T>::Insert( const T *target, const T& value )
	{
		const T* ptr = &value;
		Insert(target, ptr, ptr + 1);
	}


	template <typename T>
	void Array<T>::Insert( const T* begin, const T* end )
	{
		int n = (int)(end - begin);

		assert(n >= 0);

		Reserve(size + n);
		ArrayInternal::AllocatorCopyConstruct_Impl(data + size, begin, end);
		size += n;
	}


	template <typename T>
	void Array<T>::Insert( const T* target, const T* begin, const T* end )
	{
		assert(target >= data && target <= (data + size) && begin <= end);

		if (begin >= end)
			return;

		if (target >= (data + size))
		{
			Insert(begin, end);
		}
		else
		{
			int n = (int)(end - begin);
			int index = (int)(target - data);
			int newSize = size + n;
			int sizeAfter = size - index;

			assert(n >= 0);

			if (newSize > capacity || (begin >= data && begin < (data + size)))
			{
				int newCapacity = capacity;
				if (newSize > newCapacity)
				{
					newCapacity = capacity * 2;
					if (newSize > newCapacity)
						newCapacity = newSize;
				}

				T* newData = Alloc(newCapacity);
				T* newDataEnd = newData;

				try
				{
					ArrayInternal::AllocatorMoveConstruct_Impl(newDataEnd, data, data + index);
					newDataEnd += index;
					ArrayInternal::AllocatorCopyConstruct_Impl(newDataEnd, begin, end);
					newDataEnd += n;
					ArrayInternal::AllocatorMoveConstruct_Impl(newDataEnd, data + index, data + size);
				}
				catch (...)
				{
					ArrayInternal::AllocatorDestruct_Impl(newData, newDataEnd);
					Free(newData);
					throw;
				}

				Delete();

				this->data = newData;
				this->size = newSize;
				this->capacity = newCapacity;
			}
			else if (sizeAfter < n)
			{
				int m = n - sizeAfter;

				T* dataEnd = data + size;
				try
				{
					ArrayInternal::AllocatorCopyConstruct_Impl(dataEnd, end - m, end);
					dataEnd += m;
					ArrayInternal::AllocatorMoveConstruct_Impl(dataEnd, data + index, data + size);
				}
				catch (...)
				{
					ArrayInternal::AllocatorDestruct_Impl(data + size, dataEnd);
					throw;
				}

				size = newSize;

				ArrayInternal::AllocatorCopyAssign_Impl(data + index, begin, begin + sizeAfter);
			}
			else // sizeAfter >= n
			{
				T* dataEnd = data + size;
				ArrayInternal::AllocatorMoveConstruct_Impl(dataEnd, dataEnd - n, dataEnd);
				size = newSize;

				ArrayInternal::AllocatorMoveAssignBackwards_Impl(data + index + n, data + index, dataEnd - n);
				ArrayInternal::AllocatorCopyAssign_Impl(data + index, begin, end);
			}
		}
	}

	template <typename T>
	T* Array<T>::Erase( T *target )
	{
		assert(target >= Begin() && target <= End());

		ArrayInternal::AllocatorMoveAssign_Impl(target, target + 1, data + size);
		--size;
		ArrayInternal::AllocatorDestructSingle_Impl(data + size);

		return target;
	}


	template <typename T>
	T* Array<T>::Erase( T* begin, T* end )
	{
		assert(begin >= Begin() && begin <= End() && end >= begin && end <= End());

		int n = (int)(end - begin);
		if (n > 0)
		{
			T* prevDataEnd = data + size;

			ArrayInternal::AllocatorMoveAssign_Impl(begin, end, prevDataEnd);
			size -= n;
			ArrayInternal::AllocatorDestruct_Impl(data + size, prevDataEnd);
		}

		return begin;
	}


	template <typename T>
	void Array<T>::Swap( Array& rhs )
	{
		if (!IsDataOwn())
		{
			MakeDataOwn();
		}

		if (!rhs.IsDataOwn())
		{
			rhs.MakeDataOwn();
		}

		std::swap( this->data, rhs.data );
		std::swap( this->size, rhs.size );
		std::swap( this->capacity, rhs.capacity );
	}

	template <typename T>
	void Array<T>::MakeDataOwn()
	{
		if (IsDataOwn() || !data)
			return;

		T* newData = Alloc(size);
		try
		{
			ArrayInternal::AllocatorMoveConstruct_Impl(newData, data, data + size);
		}
		catch (...)
		{
			Free(newData);
			throw;
		}

		data = newData;
		capacity = size;
	}


#ifdef HAS_CPP0X

	template <typename T>
	Array<T>::Array( Array&& rhs )
	{
		data = rhs.data;
		size = rhs.size;
		capacity = rhs.capacity;

		rhs.data = nullptr;
		rhs.size = 0;
		rhs.capacity = 0;

		if (!IsDataOwn())
		{
			MakeDataOwn();
		}
	}


	template <typename T>
	Array<T>& Array<T>::operator = ( Array&& rhs )
	{
		if ( this == &rhs )
			return *this;

		Delete();

		data = rhs.data;
		size = rhs.size;
		capacity = rhs.capacity;

		rhs.data = nullptr;
		rhs.size = 0;
		rhs.capacity = 0;

		if (!IsDataOwn())
		{
			MakeDataOwn();
		}

		return *this;
	}


	template <typename T>
	void Array<T>::PushBack( T&& value )
	{
		if ( size >= capacity )
		{
			Enlarge();
		}

		new (data + size) T(std::move(value));
		size++;
	}

	template <typename T>
	void Array<T>::Insert(int index, T&& value)
	{
		assert(index >= 0 && index <= size);

		if (index >= size)
		{
			PushBack(std::move(value));
		}
		else
		{
			if ( size >= capacity )
				Enlarge();

			T* target = data + index;
			T* dataEnd = data + size;

			new (dataEnd) T(std::move(*(dataEnd - 1)));
			++size;
			ArrayInternal::AllocatorMoveAssignBackwards_Impl(target + 1, target, dataEnd - 1);
			*target = std::move(value);
		}
	}

	template <typename T>
	void Array<T>::Insert(const T *target, T&& value)
	{
		Insert((int)(target - data), std::move(value));
	}

#ifndef HAS_CPP11
	template<typename T> template<typename A0>
	void Array<T>::EmplaceBack( A0&& arg0 )
	{
		if ( size >= capacity )
			Enlarge();

		new (data + size) T( std::forward<A0>(arg0) );
		size++;
	}

	template<typename T> template <typename A0, typename A1>
	void Array<T>::EmplaceBack( A0&& arg0, A1&& arg1 )
	{
		if ( size >= capacity )
			Enlarge();

		new (data + size) T( std::forward<A0>(arg0), std::forward<A1>(arg1) );
		size++;
	}

	template<typename T> template <typename A0, typename A1, typename A2>
	void Array<T>::EmplaceBack( A0&& arg0, A1&& arg1, A2&& arg2 )
	{
		if ( size >= capacity )
			Enlarge();

		new (data + size) T( std::forward<A0>(arg0), std::forward<A1>(arg1), std::forward<A2>(arg2) );
		size++;
	}

	template<typename T> template <typename A0, typename A1, typename A2, typename A3>
	void Array<T>::EmplaceBack( A0&& arg0, A1&& arg1, A2&& arg2, A3&& arg3 )
	{
		if ( size >= capacity )
			Enlarge();

		new (data + size) T( std::forward<A0>(arg0), std::forward<A1>(arg1), std::forward<A2>(arg2), std::forward<A3>(arg3) );
		size++;
	}
#endif

#endif // HAS_CPP0X

#ifdef HAS_CPP11
	template <typename T>
	Array<T>::Array(std::initializer_list<T> ilist) : Array()
	{
		Insert(Begin(), ilist.begin(), ilist.end());
	}

	template <typename T>
	Array<T>& Array<T>::operator=(std::initializer_list<T> ilist)
	{
		return operator=(Array<T>(ilist));
	}

	template <typename T>
	void Array<T>::Insert(const T* target, std::initializer_list<T> ilist)
	{
		Insert(target, ilist.begin(), ilist.end());
	}

	template <typename T>
	template <typename... Args>
	T& Array<T>::EmplaceBack(Args&&... args)
	{
		if ( size >= capacity )
		{
			Enlarge();
		}
		new (data+size) T(std::forward<Args>(args)...);
		size++;
		return Back();
	}
#endif


} // namespace atl

#pragma pop_macro("new")

#endif // ATL_ARRAY_HXX
