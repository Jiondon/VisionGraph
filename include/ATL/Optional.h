//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef ATL_OPTIONAL_H
#define ATL_OPTIONAL_H

#include "Utils.h"
#include <cassert>

namespace atl
{
	enum NilType { NIL };

	template<typename T>
	class OptionalBase
	{
	public:
		typedef OptionalBase<T> MyType;
		typedef typename std::remove_const<T>::type ValueType;
		typedef ValueType& RefType;
		typedef const ValueType ConstValueType;
		typedef const ValueType& ConstRefType;

		friend class OptionalBase<T&>;
		friend class OptionalBase<const T&>;

	private:
		T _storage;
		T* _pointer;

		MyType& operator = ( const MyType& );

	protected:
		OptionalBase()
			: _storage(), _pointer(0)
		{
		}

		explicit OptionalBase( const NilType& )
			: _storage(), _pointer(0)
		{
		}

		explicit OptionalBase( const OptionalBase<ConstValueType>& other )
			: _storage(other._storage)
		{
			_pointer = other._pointer ? &_storage : 0;
		}

		explicit OptionalBase( const OptionalBase<ValueType>& other )
			: _storage(other._storage)
		{
			_pointer = other._pointer ? &_storage : 0;
		}

#ifdef HAS_CPP0X

		explicit OptionalBase( OptionalBase<ValueType>&& other )
			: _storage( std::move(other._storage) )
		{
			_pointer = other._pointer ? &_storage : 0;
		}

#endif

		explicit OptionalBase( const OptionalBase<ConstRefType>& other )
		{
			_assign(other);
		}

		explicit OptionalBase( const OptionalBase<RefType>& other )
		{
			_assign(other);
		}

		explicit OptionalBase( ConstRefType value )
			: _storage(value)
		{
			_pointer = &_storage;
		}

#ifdef HAS_CPP0X

		explicit OptionalBase( ValueType&& value )
			: _storage(std::move(value))
		{
			_pointer = &_storage;
		}

#endif

		void _assign( const NilType& )
		{
			_pointer = 0;
		}

		void _assign( const OptionalBase<ConstValueType>& other )
		{
			if (other._pointer)
			{
				_storage = other._storage;
				_pointer = &_storage;
			}
			else
			{
				_pointer = 0;
			}
		}

		void _assign( const OptionalBase<ValueType>& other )
		{
			if (other._pointer)
			{
				_storage = other._storage;
				_pointer = &_storage;
			}
			else
			{
				_pointer = 0;
			}
		}

#ifdef HAS_CPP0X

		void _assign( OptionalBase<ValueType>&& other )
		{
			if (other._pointer)
			{
				_storage = std::move(other._storage);
				_pointer = &_storage;
			}
			else
			{
				_pointer = 0;
			}
		}

#endif

		void _assign( const OptionalBase<ConstRefType>& other )
		{
			if (other._pointer)
			{
				_storage = *other._pointer;
				_pointer = &_storage;
			}
			else
			{
				_pointer = 0;
			}
		}

		void _assign( const OptionalBase<RefType>& other )
		{
			if (other._pointer)
			{
				_storage = *other._pointer;
				_pointer = &_storage;
			}
			else
			{
				_pointer = 0;
			}
		}

		void _assign( ConstRefType value )
		{
			_storage = value;
			_pointer = &_storage;
		}

#ifdef HAS_CPP0X

		void _assign( ValueType&& value )
		{
			_storage = std::move(value);
			_pointer = &_storage;
		}

#endif

		bool _equals( const NilType& ) const
		{
			return _pointer == 0;
		}

		bool _equals( const OptionalBase<ValueType>& other ) const
		{
			return (_pointer == 0 && other._pointer == 0) ||
				(_pointer != 0 && other._pointer != 0 && _storage == other._storage);
		}

		bool _equals( const OptionalBase<ConstValueType>& other ) const
		{
			return (_pointer == 0 && other._pointer == 0) ||
				(_pointer != 0 && other._pointer != 0 && _storage == other._storage);
		}

		bool _equals( const OptionalBase<RefType>& other ) const
		{
			return (_pointer == 0 && other._pointer == 0) ||
				(_pointer != 0 && other._pointer != 0 && _storage == *other._pointer);
		}

		bool _equals( const OptionalBase<ConstRefType>& other ) const
		{
			return (_pointer == 0 && other._pointer == 0) ||
				(_pointer != 0 && other._pointer != 0 && _storage == *other._pointer);
		}

		bool _equals( ConstRefType value ) const
		{
			return _pointer != 0 && _storage == value;
		}

	public:
		T& Get( void )
		{
			assert(_pointer != 0);
			return *_pointer;
		}

		ConstRefType Get( void ) const
		{
			assert(_pointer != 0);
			return *_pointer;
		}

		void AssignNonNil( void )
		{
			_pointer = &_storage;
		}

		bool HasValue( void ) const
		{
			return _pointer != 0;
		}

		bool operator!( void ) const
		{
			return !HasValue();
		}

		ATL_EXPLICIT_OPERATOR_BOOL()
	};


	template<typename T>
	class OptionalBase<T&>
	{
	public:
		typedef OptionalBase<T&> MyType;
		typedef T ValueType;
		typedef T& RefType;
		typedef const T ConstValueType;
		typedef const T& ConstRefType;

		friend class OptionalBase<T>;
		friend class OptionalBase<const T>;
		friend class OptionalBase<const T&>;

	private:
		T* _pointer;

		MyType& operator = ( const MyType& );

	protected:
		OptionalBase()
			: _pointer(0)
		{
		}

		explicit OptionalBase( const NilType& )
			: _pointer(0)
		{
		}

		explicit OptionalBase( const OptionalBase<RefType>& other )
			: _pointer(other._pointer)
		{
		}

		explicit OptionalBase( const OptionalBase<ValueType>& other )
			: _pointer(other._pointer)
		{
		}

		explicit OptionalBase( RefType value )
			: _pointer(&value)
		{
		}

		void _assign( const NilType& )
		{
			_pointer = 0;
		}

		void _assign( const OptionalBase<RefType>& other )
		{
			_pointer = other._pointer;
		}

		void _assign( const OptionalBase<ValueType>& other )
		{
			_pointer = other._pointer;
		}

		void _assign( RefType value )
		{
			_pointer = &value;
		}

		bool _equals( const NilType& ) const
		{
			return _pointer == 0;
		}

		bool _equals( const OptionalBase<ValueType>& other ) const
		{
			return (_pointer == 0 && other._pointer == 0) ||
				(_pointer != 0 && other._pointer != 0 && *_pointer == other._storage);
		}

		bool _equals( const OptionalBase<ConstValueType>& other ) const
		{
			return (_pointer == 0 && other._pointer == 0) ||
				(_pointer != 0 && other._pointer != 0 && *_pointer == other._storage);
		}

		bool _equals( const OptionalBase<RefType>& other ) const
		{
			return (_pointer == other._pointer) ||
				(_pointer != 0 && other._pointer != 0 && *_pointer == *other._pointer);
		}

		bool _equals( const OptionalBase<ConstRefType>& other ) const
		{
			return (_pointer == other._pointer) ||
				(_pointer != 0 && other._pointer != 0 && *_pointer == *other._pointer);
		}

		bool _equals( ConstRefType value ) const
		{
			return _pointer != 0 && *_pointer == value;
		}

	public:
		RefType Get( void ) const
		{
			assert(_pointer != 0);
			return *_pointer;
		}

		bool HasValue( void ) const
		{
			return _pointer != 0;
		}

		bool operator!( void ) const
		{
			return !HasValue();
		}

		ATL_EXPLICIT_OPERATOR_BOOL()
	};


	template<typename T>
	class OptionalBase<const T&>
	{
	public:
		typedef OptionalBase<const T&> MyType;
		typedef T ValueType;
		typedef T& RefType;
		typedef const T ConstValueType;
		typedef const T& ConstRefType;

		friend class OptionalBase<T>;
		friend class OptionalBase<const T>;
		friend class OptionalBase<T&>;

	private:
		const T* _pointer;

		MyType& operator = ( const MyType& );

	protected:
		OptionalBase()
			: _pointer(0)
		{
		}

		explicit OptionalBase( const NilType& )
			: _pointer(0)
		{
		}

		explicit OptionalBase( const OptionalBase<RefType>& other )
			: _pointer(other._pointer)
		{
		}

		explicit OptionalBase( const OptionalBase<ConstRefType>& other )
			: _pointer(other._pointer)
		{
		}

		explicit OptionalBase( const OptionalBase<ValueType>& other )
			: _pointer(other._pointer)
		{
		}

		explicit OptionalBase( const OptionalBase<ConstValueType>& other )
			: _pointer(other._pointer)
		{
		}

		explicit OptionalBase( ConstRefType value )
			: _pointer(&value)
		{
		}

		void _assign( const NilType& )
		{
			_pointer = 0;
		}

		void _assign( const OptionalBase<RefType>& other )
		{
			_pointer = other._pointer;
		}

		void _assign( const OptionalBase<ConstRefType>& other )
		{
			_pointer = other._pointer;
		}

		void _assign( const OptionalBase<ValueType>& other )
		{
			_pointer = other._pointer;
		}

		void _assign( const OptionalBase<ConstValueType>& other )
		{
			_pointer = other._pointer;
		}

		void _assign( ConstRefType value )
		{
			_pointer = &value;
		}

		bool _equals( const NilType& ) const
		{
			return _pointer == 0;
		}

		bool _equals( const OptionalBase<ValueType>& other ) const
		{
			return (_pointer == 0 && other._pointer == 0) ||
				(_pointer != 0 && other._pointer != 0 && *_pointer == other._storage);
		}

		bool _equals( const OptionalBase<ConstValueType>& other ) const
		{
			return (_pointer == 0 && other._pointer == 0) ||
				(_pointer != 0 && other._pointer != 0 && *_pointer == other._storage);
		}

		bool _equals( const OptionalBase<RefType>& other ) const
		{
			return (_pointer == other._pointer) ||
				(_pointer != 0 && other._pointer != 0 && *_pointer == *other._pointer);
		}

		bool _equals( const OptionalBase<ConstRefType>& other ) const
		{
			return (_pointer == other._pointer) ||
				(_pointer != 0 && other._pointer != 0 && *_pointer == *other._pointer);
		}

		bool _equals( ConstRefType value ) const
		{
			return _pointer != 0 && *_pointer == value;
		}

	public:
		ConstRefType Get( void ) const
		{
			assert(_pointer != 0);
			return *_pointer;
		}

		bool HasValue( void ) const
		{
			return _pointer != 0;
		}

		bool operator!( void ) const
		{
			return !HasValue();
		}

		ATL_EXPLICIT_OPERATOR_BOOL()
	};


	template<typename T>
	class Optional : public OptionalBase<T>
	{
	public:
		typedef Optional<T> MyType;
		typedef OptionalBase<T> MyBase;
		typedef typename MyBase::ValueType ValueType;
		typedef typename MyBase::RefType RefType;
		typedef typename MyBase::ConstValueType ConstValueType;
		typedef typename MyBase::ConstRefType ConstRefType;

		Optional() : MyBase() { }
		Optional( const Optional<ValueType>& other ) : MyBase(other) { }
		Optional( const Optional<RefType>& other ) : MyBase(other) { }
		Optional( const Optional<ConstValueType>& other ) : MyBase(other) { }
		Optional( const Optional<ConstRefType>& other ) : MyBase(other) { }
		Optional( const NilType& ) : MyBase(NIL) { }
		Optional( ConstRefType value ) : MyBase(value) { }

		const MyType& operator = ( const Optional<ValueType>& other ) { MyBase::_assign(other); return *this; }
		const MyType& operator = ( const Optional<RefType>& other ) { MyBase::_assign(other); return *this; }
		const MyType& operator = ( const Optional<ConstValueType>& other ) { MyBase::_assign(other); return *this; }
		const MyType& operator = ( const Optional<ConstRefType>& other ) { MyBase::_assign(other); return *this; }
		const MyType& operator = ( const NilType& ) { MyBase::_assign(NIL); return *this; }
		const MyType& operator = ( ConstRefType value ) { MyBase::_assign(value); return *this; }

#ifdef HAS_CPP0X

		Optional( Optional<ValueType>&& other ) : MyBase( std::move(other) ) { }
		Optional( ValueType&& value ) : MyBase( std::move(value) ) { }
		const MyType& operator = ( Optional<ValueType>&& other ) { MyBase::_assign( std::move(other) ); return *this; }
		const MyType& operator = ( ValueType&& value ) { MyBase::_assign( std::move(value) ); return *this; }

#endif

		bool operator == ( const Optional<ValueType>& other ) const { return MyBase::_equals(other); }
		bool operator == ( const Optional<RefType>& other ) const { return MyBase::_equals(other); }
		bool operator == ( const Optional<ConstValueType>& other ) const { return MyBase::_equals(other); }
		bool operator == ( const Optional<ConstRefType>& other ) const { return MyBase::_equals(other); }
		bool operator == ( const NilType& ) const { return MyBase::_equals(NIL); }
		bool operator == ( ConstRefType value ) const { return MyBase::_equals(value); }

		bool operator != ( const Optional<ValueType>& other ) const { return !MyBase::_equals(other); }
		bool operator != ( const Optional<RefType>& other ) const { return !MyBase::_equals(other); }
		bool operator != ( const Optional<ConstValueType>& other ) const { return !MyBase::_equals(other); }
		bool operator != ( const Optional<ConstRefType>& other ) const { return !MyBase::_equals(other); }
		bool operator != ( const NilType& ) const { return !MyBase::_equals(NIL); }
		bool operator != ( ConstRefType value ) const { return !MyBase::_equals(value); }
	};

	template<typename T>
	class Conditional : public OptionalBase<T>
	{
	public:
		typedef Conditional<T> MyType;
		typedef OptionalBase<T> MyBase;
		typedef typename MyBase::ValueType ValueType;
		typedef typename MyBase::RefType RefType;
		typedef typename MyBase::ConstValueType ConstValueType;
		typedef typename MyBase::ConstRefType ConstRefType;

		Conditional() : MyBase() { }
		Conditional( const Conditional<ValueType>& other ) : MyBase(other) { }
		Conditional( const Conditional<RefType>& other ) : MyBase(other) { }
		Conditional( const Conditional<ConstValueType>& other ) : MyBase(other) { }
		Conditional( const Conditional<ConstRefType>& other ) : MyBase(other) { }
		Conditional( const NilType& ) : MyBase(NIL) { }
		Conditional( ConstRefType value ) : MyBase(value) { }

		const MyType& operator = ( const Conditional<ValueType>& other ) { MyBase::_assign(other); return *this; }
		const MyType& operator = ( const Conditional<RefType>& other ) { MyBase::_assign(other); return *this; }
		const MyType& operator = ( const Conditional<ConstValueType>& other ) { MyBase::_assign(other); return *this; }
		const MyType& operator = ( const Conditional<ConstRefType>& other ) { MyBase::_assign(other); return *this; }
		const MyType& operator = ( const NilType& ) { MyBase::_assign(NIL); return *this; }
		const MyType& operator = ( ConstRefType value ) { MyBase::_assign(value); return *this; }

#ifdef HAS_CPP0X

		Conditional( Conditional<ValueType>&& other ) : MyBase( std::move(other) ) { }
		Conditional( ValueType&& value ) : MyBase( std::move(value) ) { }
		const MyType& operator = ( Conditional<ValueType>&& other ) { MyBase::_assign( std::move(other) ); return *this; }
		const MyType& operator = ( ValueType&& value ) { MyBase::_assign( std::move(value) ); return *this; }

#endif

		bool operator == ( const Conditional<ValueType>& other ) const { return MyBase::_equals(other); }
		bool operator == ( const Conditional<RefType>& other ) const { return MyBase::_equals(other); }
		bool operator == ( const Conditional<ConstValueType>& other ) const { return MyBase::_equals(other); }
		bool operator == ( const Conditional<ConstRefType>& other ) const { return MyBase::_equals(other); }
		bool operator == ( const NilType& ) const { return MyBase::_equals(NIL); }
		bool operator == ( ConstRefType value ) const { return MyBase::_equals(value); }

		bool operator != ( const Conditional<ValueType>& other ) const { return !MyBase::_equals(other); }
		bool operator != ( const Conditional<RefType>& other ) const { return !MyBase::_equals(other); }
		bool operator != ( const Conditional<ConstValueType>& other ) const { return !MyBase::_equals(other); }
		bool operator != ( const Conditional<ConstRefType>& other ) const { return !MyBase::_equals(other); }
		bool operator != ( const NilType& ) const { return !MyBase::_equals(NIL); }
		bool operator != ( ConstRefType value ) const { return !MyBase::_equals(value); }
	};


	template<typename T>
	class Optional<T&> : public OptionalBase<T&>
	{
	public:
		typedef Optional<T&> MyType;
		typedef OptionalBase<T&> MyBase;
		typedef typename MyBase::ValueType ValueType;
		typedef typename MyBase::RefType RefType;
		typedef typename MyBase::ConstValueType ConstValueType;
		typedef typename MyBase::ConstRefType ConstRefType;

		Optional() : MyBase() { }
		Optional( const Optional<ValueType>& other ) : MyBase(other) { }
		Optional( const Optional<RefType>& other ) : MyBase(other) { }
		Optional( const Optional<ConstValueType>& other ) : MyBase(other) { }
		Optional( const Optional<ConstRefType>& other ) : MyBase(other) { }
		Optional( const NilType& ) : MyBase(NIL) { }
		Optional( ConstRefType value ) : MyBase(value) { }
		Optional( RefType value ) : MyBase(value) { }

		const MyType& operator = ( const Optional<ValueType>& other ) { MyBase::_assign(other); return *this; }
		const MyType& operator = ( const Optional<RefType>& other ) { MyBase::_assign(other); return *this; }
		const MyType& operator = ( const Optional<ConstValueType>& other ) { MyBase::_assign(other); return *this; }
		const MyType& operator = ( const Optional<ConstRefType>& other ) { MyBase::_assign(other); return *this; }
		const MyType& operator = ( const NilType& ) { MyBase::_assign(NIL); return *this; }
		const MyType& operator = ( ConstRefType value ) { MyBase::_assign(value); return *this; }
		const MyType& operator = ( RefType value ) { MyBase::_assign(value); return *this; }

		bool operator == ( const Optional<ValueType>& other ) const { return MyBase::_equals(other); }
		bool operator == ( const Optional<RefType>& other ) const { return MyBase::_equals(other); }
		bool operator == ( const Optional<ConstValueType>& other ) const { return MyBase::_equals(other); }
		bool operator == ( const Optional<ConstRefType>& other ) const { return MyBase::_equals(other); }
		bool operator == ( const NilType& ) const { return MyBase::_equals(NIL); }
		bool operator == ( ConstRefType value ) const { return MyBase::_equals(value); }

		bool operator != ( const Optional<ValueType>& other ) const { return !MyBase::_equals(other); }
		bool operator != ( const Optional<RefType>& other ) const { return !MyBase::_equals(other); }
		bool operator != ( const Optional<ConstValueType>& other ) const { return !MyBase::_equals(other); }
		bool operator != ( const Optional<ConstRefType>& other ) const { return !MyBase::_equals(other); }
		bool operator != ( const NilType& ) const { return !MyBase::_equals(NIL); }
		bool operator != ( ConstRefType value ) const { return !MyBase::_equals(value); }
	};

	template<typename T>
	class Conditional<T&> : public OptionalBase<T&>
	{
	public:
		typedef Conditional<T&> MyType;
		typedef OptionalBase<T&> MyBase;
		typedef typename MyBase::ValueType ValueType;
		typedef typename MyBase::RefType RefType;
		typedef typename MyBase::ConstValueType ConstValueType;
		typedef typename MyBase::ConstRefType ConstRefType;

		Conditional() : MyBase() { }
		Conditional( const Conditional<ValueType>& other ) : MyBase(other) { }
		Conditional( const Conditional<RefType>& other ) : MyBase(other) { }
		Conditional( const Conditional<ConstValueType>& other ) : MyBase(other) { }
		Conditional( const Conditional<ConstRefType>& other ) : MyBase(other) { }
		Conditional( const NilType& ) : MyBase(NIL) { }
		Conditional( ConstRefType value ) : MyBase(value) { }
		Conditional( RefType value ) : MyBase(value) { }

		const MyType& operator = ( const Conditional<ValueType>& other ) { MyBase::_assign(other); return *this; }
		const MyType& operator = ( const Conditional<RefType>& other ) { MyBase::_assign(other); return *this; }
		const MyType& operator = ( const Conditional<ConstValueType>& other ) { MyBase::_assign(other); return *this; }
		const MyType& operator = ( const Conditional<ConstRefType>& other ) { MyBase::_assign(other); return *this; }
		const MyType& operator = ( const NilType& ) { MyBase::_assign(NIL); return *this; }
		const MyType& operator = ( ConstRefType value ) { MyBase::_assign(value); return *this; }
		const MyType& operator = ( RefType value ) { MyBase::_assign(value); return *this; }

		bool operator == ( const Conditional<ValueType>& other ) const { return MyBase::_equals(other); }
		bool operator == ( const Conditional<RefType>& other ) const { return MyBase::_equals(other); }
		bool operator == ( const Conditional<ConstValueType>& other ) const { return MyBase::_equals(other); }
		bool operator == ( const Conditional<ConstRefType>& other ) const { return MyBase::_equals(other); }
		bool operator == ( const NilType& ) const { return MyBase::_equals(NIL); }
		bool operator == ( ConstRefType value ) const { return MyBase::_equals(value); }

		bool operator != ( const Conditional<ValueType>& other ) const { return !MyBase::_equals(other); }
		bool operator != ( const Conditional<RefType>& other ) const { return !MyBase::_equals(other); }
		bool operator != ( const Conditional<ConstValueType>& other ) const { return !MyBase::_equals(other); }
		bool operator != ( const Conditional<ConstRefType>& other ) const { return !MyBase::_equals(other); }
		bool operator != ( const NilType& ) const { return !MyBase::_equals(NIL); }
		bool operator != ( ConstRefType value ) const { return !MyBase::_equals(value); }
	};


	template<typename T>
	struct ToOptionalType
	{
		typedef Optional<T> Type;
	};

	template<typename T>
	struct ToOptionalType< Optional<T> >
	{
		typedef typename std::remove_const< typename std::remove_reference<T>::type >::type ItemType;
		typedef Optional<ItemType> Type;
	};

	template<typename T>
	struct ToOptionalType< Optional<T>& >
	{
		typedef typename std::remove_const< typename std::remove_reference<T>::type >::type ItemType;
		typedef Optional<ItemType&> Type;
	};

	template<typename T>
	struct ToOptionalType< const Optional<T>& >
	{
		typedef typename std::remove_const< typename std::remove_reference<T>::type >::type ItemType;
		typedef Optional<const ItemType&> Type;
	};

	template<typename T>
	struct ToOptionalType< Conditional<T> >
	{
		typedef typename std::remove_const< typename std::remove_reference<T>::type >::type ItemType;
		typedef Optional<ItemType> Type;
	};

	template<typename T>
	struct ToOptionalType< Conditional<T>& >
	{
		typedef typename std::remove_const< typename std::remove_reference<T>::type >::type ItemType;
		typedef Optional<ItemType&> Type;
	};

	template<typename T>
	struct ToOptionalType< const Conditional<T>& >
	{
		typedef typename std::remove_const< typename std::remove_reference<T>::type >::type ItemType;
		typedef Optional<const ItemType&> Type;
	};

	template<typename T>
	struct ToConditionalType
	{
		typedef Conditional<T> Type;
	};

	template<typename T>
	struct ToConditionalType< Conditional<T> >
	{
		typedef typename std::remove_const< typename std::remove_reference<T>::type >::type ItemType;
		typedef Conditional<ItemType> Type;
	};

	template<typename T>
	struct ToConditionalType< Conditional<T>& >
	{
		typedef typename std::remove_const< typename std::remove_reference<T>::type >::type ItemType;
		typedef Conditional<ItemType&> Type;
	};

	template<typename T>
	struct ToConditionalType< const Conditional<T>& >
	{
		typedef typename std::remove_const< typename std::remove_reference<T>::type >::type ItemType;
		typedef Conditional<const ItemType&> Type;
	};

	template<typename T>
	struct ToConditionalType< Optional<T> >
	{
		typedef typename std::remove_const< typename std::remove_reference<T>::type >::type ItemType;
		typedef Conditional<ItemType> Type;
	};

	template<typename T>
	struct ToConditionalType< Optional<T>& >
	{
		typedef typename std::remove_const< typename std::remove_reference<T>::type >::type ItemType;
		typedef Conditional<ItemType&> Type;
	};

	template<typename T>
	struct ToConditionalType< const Optional<T>& >
	{
		typedef typename std::remove_const< typename std::remove_reference<T>::type >::type ItemType;
		typedef Conditional<const ItemType&> Type;
	};


} // namespace atl

#endif // ATL_OPTIONAL_H
