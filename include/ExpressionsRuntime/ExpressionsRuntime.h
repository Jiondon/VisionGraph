
#ifndef EXPRESSIONS_RUNTIME_H
#define EXPRESSIONS_RUNTIME_H

#include "ATL/Error.h"
#include "ATL/AtlTypes.h"
#include "ATL/Optional.h"
#include "ATL/Array.hxx"

#include <limits>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cwctype>


#ifdef _MSC_VER
	#pragma warning(push)
	#pragma warning(disable: 4996)
#endif


//
// Computation helper functions
//
template<typename T, typename R>
inline atl::Conditional<T> _avfml_cnd_cast( const atl::Conditional<R>& value )
{
	if (value == atl::NIL)
		return atl::NIL;
	else
		return static_cast<T>(value.Get());
}


inline double _avfml_ld_real( float value )
{
	return static_cast<double>(value);
}


inline atl::Conditional<double> _avfml_cnd_ld_real( const atl::Conditional<float>& value )
{
	if (value == atl::NIL)
		return atl::NIL;
	else
		return static_cast<double>(value.Get());
}


inline atl::Conditional<double> _avfml_cnd_ld_real( const atl::Optional<float>& value )
{
	if (value == atl::NIL)
		return atl::NIL;
	else
		return static_cast<double>(value.Get());
}


inline float _avfml_st_real( double value )
{
	return static_cast<float>(value);
}


inline atl::Conditional<float> _avfml_cnd_st_real( const atl::Conditional<double>& value )
{
	if (value == atl::NIL)
		return atl::NIL;
	else
		return static_cast<float>(value.Get());
}


inline atl::Optional<float> _avfml_opt_st_real( const atl::Conditional<double>& value )
{
	if (value == atl::NIL)
		return atl::NIL;
	else
		return static_cast<float>(value.Get());
}


template<typename T> // Specified explicitly
inline atl::Conditional<T> _avfml_ld_opt( const atl::Optional<const T&>& value )
{
	if (value == atl::NIL)
		return atl::NIL;
	else
		return value.Get();
}

template<typename T> // Specified explicitly
inline atl::Optional<T> _avfml_st_opt( const atl::Conditional<const T&>& value )
{
	if (value == atl::NIL)
		return atl::NIL;
	else
		return value.Get();
}

template<typename T> // Specified explicitly
atl::Conditional<int> _avfml_cnd_arrsize( const atl::Conditional<const atl::Array<T>&>& value )
{
	if (value == atl::NIL)
		return atl::NIL;
	else
		return value.Get().Size();
}

template<typename T> // Specified explicitly
const T& _avfml_subscript( const atl::Array<T>& arr, int index )
{
	if (index < 0 || index >= arr.Size())
		throw atl::DomainError("Index out of range in array element read operator.");

	return arr[index];
}

template<typename T> // Specified explicitly
atl::Conditional<T> _avfml_cnd_subscript( atl::Conditional< const atl::Array<T>& > arr, atl::Conditional<int> index )
{
	if (arr == atl::NIL || index == atl::NIL)
		return atl::NIL;

	return _avfml_subscript(arr.Get(), index.Get());
}

template<typename T> // Specified explicitly
atl::Conditional<T> _avfml_cnd_subscript( atl::Conditional< const atl::Array< atl::Conditional<T> >& > arr, atl::Conditional<int> index )
{
	if (arr == atl::NIL || index == atl::NIL)
		return atl::NIL;

	return _avfml_subscript(arr.Get(), index.Get());
}

template<typename T> // Specified explicitly
atl::Conditional<T> _avfml_cnd_subscript( atl::Conditional< const atl::Array< atl::Optional<T> >& > arr, atl::Conditional<int> index )
{
	if (arr == atl::NIL || index == atl::NIL || arr.Get()[index.Get()] == atl::NIL)
		return atl::NIL;

	return _avfml_subscript(arr.Get(), index.Get()).Get();
}

template<typename StructType, typename FieldType> // Specified explicitly
atl::Conditional<FieldType> _avfml_cnd_member( FieldType (StructType::*accptr)() const, atl::Conditional<const StructType&> obj )
{
	if (obj == atl::NIL)
		return atl::NIL;
	else
		return (obj.Get().*accptr)();
}

template<typename StructType, typename FieldType> // Specified explicitly
atl::Conditional<FieldType> _avfml_cnd_member( const FieldType& (StructType::*accptr)() const, atl::Conditional<const StructType&> obj )
{
	if (obj == atl::NIL)
		return atl::NIL;
	else
		return (obj.Get().*accptr)();
}

template<typename StructType, typename FieldType> // Specified explicitly
atl::Conditional<FieldType> _avfml_cnd_member( atl::Conditional<FieldType> (StructType::*accptr)() const, atl::Conditional<const StructType&> obj )
{
	if (obj == atl::NIL)
		return atl::NIL;
	else
		return (obj.Get().*accptr)();
}

template<typename StructType, typename FieldType> // Specified explicitly
atl::Conditional<FieldType> _avfml_cnd_member( const atl::Conditional<FieldType>& (StructType::*accptr)() const, atl::Conditional<const StructType&> obj )
{
	if (obj == atl::NIL)
		return atl::NIL;
	else
		return (obj.Get().*accptr)();
}

template<typename StructType, typename FieldType> // Specified explicitly
atl::Conditional<FieldType> _avfml_cnd_member( atl::Optional<FieldType> (StructType::*accptr)() const, atl::Conditional<const StructType&> obj )
{
	if (obj == atl::NIL)
		return atl::NIL;
	else
		return _avfml_ld_opt( (obj.Get().*accptr)() );
}

template<typename StructType, typename FieldType> // Specified explicitly
atl::Conditional<FieldType> _avfml_cnd_member( const atl::Optional<FieldType>& (StructType::*accptr)() const, atl::Conditional<const StructType&> obj )
{
	if (obj == atl::NIL || (obj.Get().*accptr)() == atl::NIL)
		return atl::NIL;
	else
		return (obj.Get().*accptr)().Get();
}

template<typename T> // Specified explicitly
T _avfml_defval( const atl::Conditional< const T& >& value, const T& def )
{
	return value != atl::NIL ? value.Get() : def;
}

template<typename T> // Specified explicitly
atl::Conditional<T> _avfml_defval( const atl::Conditional< const T& >& value, const atl::Conditional< const T& >& def )
{
	return value != atl::NIL ? value : def;
}

template<typename T> // Specified explicitly
bool _avfml_equal( const atl::Conditional<const T&>& a, const atl::Conditional<const T&>& b )
{
	return a == b;
}

inline bool _avfml_equali( const atl::Conditional<int>& a, const atl::Conditional<int>& b )
{
	return a == b;
}

inline bool _avfml_equall( const atl::Conditional<atl::int64>& a, const atl::Conditional<atl::int64>& b )
{
	return a == b;
}

inline bool _avfml_equalf( const atl::Conditional<double>& a, const atl::Conditional<double>& b )
{
	return a == b;
}

inline bool _avfml_equalb( const atl::Conditional<bool>& a, const atl::Conditional<bool>& b )
{
	return a == b;
}


namespace _avfml_internal
{
	inline double rad_to_deg( double value )
	{
		return value * 180.0 / 3.14159265358979323846;
	}


	inline double deg_to_rad( double value )
	{
		return value * 3.14159265358979323846 / 180.0;
	}


	template<typename T, typename R, typename OP>
	R aggregate_array( const atl::Array<T>& values, OP op = OP() )
	{
		if (values.Empty())
			throw atl::DomainError("Empty array in array aggregation function.");

		R value = static_cast<R>(values[0]);
		for( int i = 1; i < values.Size(); ++i )
			value = op(value, static_cast<R>(values[i]));

		return value;
	}


	template<typename T, typename R, typename OP>
	R aggregate_array( const atl::Array<T>& values, R initialValue, OP op = OP() )
	{
		R value = initialValue;
		for( int i = 0; i < values.Size(); ++i )
			value = op(value, static_cast<R>(values[i]));

		return value;
	}


	template<typename T> struct min_aggregator
	{
		T operator() ( const T& a, const T& b ) { return a < b ? a : b; }
	};

	template<typename T> struct max_aggregator
	{
		T operator() ( const T& a, const T& b ) { return a > b ? a : b; }
	};

	template<typename T> struct sum_aggregator
	{
		T operator() ( const T& a, const T& b ) { return a + b; }
	};

	template<typename T> struct product_aggregator
	{
		T operator() ( const T& a, const T& b ) { return a * b; }
	};

	struct and_aggregator
	{
		bool operator() ( bool a, bool b ) { return a && b; }
	};

	struct or_aggregator
	{
		bool operator() ( bool a, bool b ) { return a || b; }
	};

	template<typename T>
	double variance_impl( const atl::Array<T>& values )
	{
		if (values.Empty())
			throw atl::DomainError("Empty array in variance function.");

		double average = 0;
		for( int i = 0; i < values.Size(); ++i )
			average += values[i];

		average /= values.Size();

		double variance = 0;
		for( int i = 0; i < values.Size(); ++i )
		{
			double d = values[i] - average;
			variance += d * d;
		}

		return variance / values.Size();
	}

	template<typename T, typename R>
	R median_impl( const atl::Array<T>& values )
	{
		if (values.Empty())
			throw atl::DomainError("Empty array in median function.");

		int p = values.Size() / 2;

		atl::Array<T> tmpArray(values);
		std::nth_element(tmpArray.Begin(), tmpArray.Begin() + p, tmpArray.End());

		if (values.Size() % 2)
		{
			return tmpArray[p];
		}
		else
		{
			T* m = std::max_element(tmpArray.Begin(), tmpArray.Begin() + p);
			return (static_cast<R>(*m) + static_cast<R>(tmpArray[p])) / 2;
		}
	}

	template<typename T, typename R>
	R nth_value_impl( const atl::Array<T>& values, int n )
	{
		if (n < 0 || n >= values.Size())
			throw atl::DomainError("Selected position exceed the array range in nthValue function.");

		atl::Array<T> tmpArray(values);
		std::nth_element(tmpArray.Begin(), tmpArray.Begin() + n, tmpArray.End());

		return tmpArray[n];
	}

	template<typename T, typename R>
	R quantile_impl( const atl::Array<T>& values, double point )
	{
		if (point < 0.0 || point > 1.0)
			throw atl::DomainError("Point value is outside of valid range in quantile function.");

		if (values.Empty())
			throw atl::DomainError("Empty array on input in quantile function.");

		int index = std::max(0, std::min(values.Size() - 1, static_cast<int>(values.Size() * point)));
		return nth_value_impl<T, R>(values, index);
	}
}


inline double _avfml_inf( void )
{
	return std::numeric_limits<double>::infinity();
}


inline int _avfml_divi( int left, int right )
{
	if (right == 0)
		throw atl::DomainError("Division by zero.");

	return left / right;
}


inline atl::int64 _avfml_divl( atl::int64 left, atl::int64 right )
{
	if (right == 0)
		throw atl::DomainError("Division by zero.");

	return left / right;
}


inline int _avfml_mod( int left, int right )
{
	if (right == 0)
		throw atl::DomainError("Modulo by zero.");

	return left % right;
}


inline atl::int64 _avfml_modl( atl::int64 left, atl::int64 right )
{
	if (right == 0)
		throw atl::DomainError("Modulo by zero.");

	return left % right;
}


inline bool _avfml_logic_xor( bool left, bool right )
{
	return (left && !right) || (!left && right);
}


inline int _avfml_safe_lshift( int value, int shift )
{
	if (shift < 0)
		throw atl::DomainError("Negative bitwise shift value.");
	else if (shift > 31)
		return 0;
	else
		return value << shift;
}


inline atl::int64 _avfml_safe_lshiftl( atl::int64 value, atl::int64 shift )
{
	if (shift < 0)
		throw atl::DomainError("Negative bitwise shift value.");
	else if (shift > 63)
		return 0;
	else
		return value << shift;
}


inline int _avfml_safe_rshift( int value, int shift )
{
	if (shift < 0)
		throw atl::DomainError("Negative bitwise shift value.");
	else if (shift > 31)
		return 0;
	else
		return static_cast<int>( static_cast<unsigned int>(value) >> static_cast<unsigned int>(shift) );
}


inline atl::int64 _avfml_safe_rshiftl( atl::int64 value, atl::int64 shift )
{
	if (shift < 0)
		throw atl::DomainError("Negative bitwise shift value.");
	else if (shift > 63)
		return 0;
	else
		return static_cast<atl::int64>( static_cast<atl::uint64>(value) >> static_cast<atl::uint64>(shift) );
}


inline atl::Conditional<bool> _avfml_cnd_logic_xor( const atl::Conditional<bool>& left, const atl::Conditional<bool>& right )
{
	if (left == atl::NIL || right == atl::NIL)
		return atl::NIL;
	else
		return (left.Get() && !right.Get()) || (!left.Get() && right.Get());
}


inline atl::Conditional<int> _avfml_cnd_safe_lshift( const atl::Conditional<int>& left, const atl::Conditional<int>& right )
{
	if (left == atl::NIL || right == atl::NIL)
		return atl::NIL;
	else
		return _avfml_safe_lshift(left.Get(), right.Get());
}


inline atl::Conditional<atl::int64> _avfml_cnd_safe_lshiftl( const atl::Conditional<atl::int64>& left, const atl::Conditional<atl::int64>& right )
{
	if (left == atl::NIL || right == atl::NIL)
		return atl::NIL;
	else
		return _avfml_safe_lshiftl(left.Get(), right.Get());
}


inline atl::Conditional<int> _avfml_cnd_safe_rshift( const atl::Conditional<int>& left, const atl::Conditional<int>& right )
{
	if (left == atl::NIL || right == atl::NIL)
		return atl::NIL;
	else
		return _avfml_safe_rshift(left.Get(), right.Get());
}


inline atl::Conditional<atl::int64> _avfml_cnd_safe_rshiftl( const atl::Conditional<atl::int64>& left, const atl::Conditional<atl::int64>& right )
{
	if (left == atl::NIL || right == atl::NIL)
		return atl::NIL;
	else
		return _avfml_safe_rshiftl(left.Get(), right.Get());
}


//
// Conditional versions of standard operators
//


inline atl::Conditional< int > _avfml_cnd_addi( const atl::Conditional< int >& left, const atl::Conditional< int >& right )
{
	if (left != atl::NIL && right != atl::NIL)
		return left.Get() + right.Get();
	else
		return atl::NIL;
}


inline atl::Conditional< atl::int64 > _avfml_cnd_addl( const atl::Conditional< atl::int64 >& left, const atl::Conditional< atl::int64 >& right )
{
	if (left != atl::NIL && right != atl::NIL)
		return left.Get() + right.Get();
	else
		return atl::NIL;
}


inline atl::Conditional< double > _avfml_cnd_addf( const atl::Conditional< double >& left, const atl::Conditional< double >& right )
{
	if (left != atl::NIL && right != atl::NIL)
		return left.Get() + right.Get();
	else
		return atl::NIL;
}


inline atl::Conditional< int > _avfml_cnd_subi( const atl::Conditional< int >& left, const atl::Conditional< int >& right )
{
	if (left != atl::NIL && right != atl::NIL)
		return left.Get() - right.Get();
	else
		return atl::NIL;
}


inline atl::Conditional< atl::int64 > _avfml_cnd_subl( const atl::Conditional< atl::int64 >& left, const atl::Conditional< atl::int64 >& right )
{
	if (left != atl::NIL && right != atl::NIL)
		return left.Get() - right.Get();
	else
		return atl::NIL;
}


inline atl::Conditional< double > _avfml_cnd_subf( const atl::Conditional< double >& left, const atl::Conditional< double >& right )
{
	if (left != atl::NIL && right != atl::NIL)
		return left.Get() - right.Get();
	else
		return atl::NIL;
}


inline atl::Conditional< int > _avfml_cnd_muli( const atl::Conditional< int >& left, const atl::Conditional< int >& right )
{
	if (left != atl::NIL && right != atl::NIL)
		return left.Get() * right.Get();
	else
		return atl::NIL;
}


inline atl::Conditional< atl::int64 > _avfml_cnd_mull( const atl::Conditional< atl::int64 >& left, const atl::Conditional< atl::int64 >& right )
{
	if (left != atl::NIL && right != atl::NIL)
		return left.Get() * right.Get();
	else
		return atl::NIL;
}


inline atl::Conditional< double > _avfml_cnd_mulf( const atl::Conditional< double >& left, const atl::Conditional< double >& right )
{
	if (left != atl::NIL && right != atl::NIL)
		return left.Get() * right.Get();
	else
		return atl::NIL;
}


inline atl::Conditional< int > _avfml_cnd_divi( const atl::Conditional< int >& left, const atl::Conditional< int >& right )
{
	if (left != atl::NIL && right != atl::NIL)
		return _avfml_divi(left.Get(), right.Get());
	else
		return atl::NIL;
}


inline atl::Conditional< atl::int64 > _avfml_cnd_divl( const atl::Conditional< atl::int64 >& left, const atl::Conditional< atl::int64 >& right )
{
	if (left != atl::NIL && right != atl::NIL)
		return _avfml_divl(left.Get(), right.Get());
	else
		return atl::NIL;
}


inline atl::Conditional< double > _avfml_cnd_divf( const atl::Conditional< double >& left, const atl::Conditional< double >& right )
{
	if (left != atl::NIL && right != atl::NIL)
		return left.Get() / right.Get();
	else
		return atl::NIL;
}


inline atl::Conditional< int > _avfml_cnd_mod( const atl::Conditional< int >& left, const atl::Conditional< int >& right )
{
	if (left != atl::NIL && right != atl::NIL)
		return _avfml_mod(left.Get(), right.Get());
	else
		return atl::NIL;
}


inline atl::Conditional< atl::int64 > _avfml_cnd_modl( const atl::Conditional< atl::int64 >& left, const atl::Conditional< atl::int64 >& right )
{
	if (left != atl::NIL && right != atl::NIL)
		return _avfml_modl(left.Get(), right.Get());
	else
		return atl::NIL;
}


inline atl::Conditional< int > _avfml_cnd_bitand( const atl::Conditional< int >& left, const atl::Conditional< int >& right )
{
	if (left != atl::NIL && right != atl::NIL)
		return left.Get() & right.Get();
	else
		return atl::NIL;
}


inline atl::Conditional< atl::int64 > _avfml_cnd_bitandl( const atl::Conditional< atl::int64 >& left, const atl::Conditional< atl::int64 >& right )
{
	if (left != atl::NIL && right != atl::NIL)
		return left.Get() & right.Get();
	else
		return atl::NIL;
}


inline atl::Conditional< int > _avfml_cnd_bitor( const atl::Conditional< int >& left, const atl::Conditional< int >& right )
{
	if (left != atl::NIL && right != atl::NIL)
		return left.Get() | right.Get();
	else
		return atl::NIL;
}


inline atl::Conditional< atl::int64 > _avfml_cnd_bitorl( const atl::Conditional< atl::int64 >& left, const atl::Conditional< atl::int64 >& right )
{
	if (left != atl::NIL && right != atl::NIL)
		return left.Get() | right.Get();
	else
		return atl::NIL;
}


inline atl::Conditional< int > _avfml_cnd_bitxor( const atl::Conditional< int >& left, const atl::Conditional< int >& right )
{
	if (left != atl::NIL && right != atl::NIL)
		return left.Get() ^ right.Get();
	else
		return atl::NIL;
}


inline atl::Conditional< atl::int64 > _avfml_cnd_bitxorl( const atl::Conditional< atl::int64 >& left, const atl::Conditional< atl::int64 >& right )
{
	if (left != atl::NIL && right != atl::NIL)
		return left.Get() ^ right.Get();
	else
		return atl::NIL;
}


inline atl::Conditional< bool > _avfml_cnd_logic_and( const atl::Conditional< bool >& left, const atl::Conditional< bool >& right )
{
	if (left != atl::NIL && right != atl::NIL)
		return left.Get() && right.Get();
	else
		return atl::NIL;
}


inline atl::Conditional< bool > _avfml_cnd_logic_or( const atl::Conditional< bool >& left, const atl::Conditional< bool >& right )
{
	if (left != atl::NIL && right != atl::NIL)
		return left.Get() || right.Get();
	else
		return atl::NIL;
}


inline atl::Conditional<bool> _avfml_cnd_lessi( const atl::Conditional< int >& left, const atl::Conditional< int >& right )
{
	if (left != atl::NIL && right != atl::NIL)
		return left.Get() < right.Get();
	else
		return atl::NIL;
}


inline atl::Conditional<bool> _avfml_cnd_lessl( const atl::Conditional< atl::int64 >& left, const atl::Conditional< atl::int64 >& right )
{
	if (left != atl::NIL && right != atl::NIL)
		return left.Get() < right.Get();
	else
		return atl::NIL;
}


inline atl::Conditional<bool> _avfml_cnd_lessf( const atl::Conditional< double >& left, const atl::Conditional< double >& right )
{
	if (left != atl::NIL && right != atl::NIL)
		return left.Get() < right.Get();
	else
		return atl::NIL;
}


inline atl::Conditional<bool> _avfml_cnd_lesseqi( const atl::Conditional< int >& left, const atl::Conditional< int >& right )
{
	if (left != atl::NIL && right != atl::NIL)
		return left.Get() <= right.Get();
	else
		return atl::NIL;
}


inline atl::Conditional<bool> _avfml_cnd_lesseql( const atl::Conditional< atl::int64 >& left, const atl::Conditional< atl::int64 >& right )
{
	if (left != atl::NIL && right != atl::NIL)
		return left.Get() <= right.Get();
	else
		return atl::NIL;
}


inline atl::Conditional<bool> _avfml_cnd_lesseqf( const atl::Conditional< double >& left, const atl::Conditional< double >& right )
{
	if (left != atl::NIL && right != atl::NIL)
		return left.Get() <= right.Get();
	else
		return atl::NIL;
}


inline atl::Conditional<bool> _avfml_cnd_greathi( const atl::Conditional< int >& left, const atl::Conditional< int >& right )
{
	if (left != atl::NIL && right != atl::NIL)
		return left.Get() > right.Get();
	else
		return atl::NIL;
}


inline atl::Conditional<bool> _avfml_cnd_greathl( const atl::Conditional< atl::int64 >& left, const atl::Conditional< atl::int64 >& right )
{
	if (left != atl::NIL && right != atl::NIL)
		return left.Get() > right.Get();
	else
		return atl::NIL;
}


inline atl::Conditional<bool> _avfml_cnd_greathf( const atl::Conditional< double >& left, const atl::Conditional< double >& right )
{
	if (left != atl::NIL && right != atl::NIL)
		return left.Get() > right.Get();
	else
		return atl::NIL;
}


inline atl::Conditional<bool> _avfml_cnd_greatheqi( const atl::Conditional< int >& left, const atl::Conditional< int >& right )
{
	if (left != atl::NIL && right != atl::NIL)
		return left.Get() >= right.Get();
	else
		return atl::NIL;
}


inline atl::Conditional<bool> _avfml_cnd_greatheql( const atl::Conditional< atl::int64 >& left, const atl::Conditional< atl::int64 >& right )
{
	if (left != atl::NIL && right != atl::NIL)
		return left.Get() >= right.Get();
	else
		return atl::NIL;
}


inline atl::Conditional<bool> _avfml_cnd_greatheqf( const atl::Conditional< double >& left, const atl::Conditional< double >& right )
{
	if (left != atl::NIL && right != atl::NIL)
		return left.Get() >= right.Get();
	else
		return atl::NIL;
}


inline atl::Conditional<int> _avfml_cnd_negi( const atl::Conditional<int>& arg )
{
	if (arg == atl::NIL)
		return atl::NIL;
	else
		return -arg.Get();
}


inline atl::Conditional<atl::int64> _avfml_cnd_negl( const atl::Conditional<atl::int64>& arg )
{
	if (arg == atl::NIL)
		return atl::NIL;
	else
		return -arg.Get();
}


inline atl::Conditional<double> _avfml_cnd_negf( const atl::Conditional<double>& arg )
{
	if (arg == atl::NIL)
		return atl::NIL;
	else
		return -arg.Get();
}


inline atl::Conditional<int> _avfml_cnd_bitnot( const atl::Conditional<int>& arg )
{
	if (arg == atl::NIL)
		return atl::NIL;
	else
		return ~arg.Get();
}


inline atl::Conditional<atl::int64> _avfml_cnd_bitnotl( const atl::Conditional<atl::int64>& arg )
{
	if (arg == atl::NIL)
		return atl::NIL;
	else
		return ~arg.Get();
}


inline atl::Conditional<bool> _avfml_cnd_logic_not( const atl::Conditional<bool>& arg )
{
	if (arg == atl::NIL)
		return atl::NIL;
	else
		return !arg.Get();
}


//
// Basic functions
//


inline double _avfml_sin( double value )
{
	return std::sin(_avfml_internal::deg_to_rad(value));
}


inline atl::Conditional<double> _avfml_cnd_sin( const atl::Conditional<double>& value )
{
	if (value == atl::NIL)
		return atl::NIL;
	else
		return _avfml_sin(value.Get());
}


inline double _avfml_cos( double value )
{
	return std::cos(_avfml_internal::deg_to_rad(value));
}


inline atl::Conditional<double> _avfml_cnd_cos( const atl::Conditional<double>& value )
{
	if (value == atl::NIL)
		return atl::NIL;
	else
		return _avfml_cos(value.Get());
}


inline double _avfml_tan( double value )
{
	return std::tan(_avfml_internal::deg_to_rad(value));
}


inline atl::Conditional<double> _avfml_cnd_tan( const atl::Conditional<double>& value )
{
	if (value == atl::NIL)
		return atl::NIL;
	else
		return _avfml_tan(value.Get());
}


inline double _avfml_asin( double value )
{
	return _avfml_internal::rad_to_deg(std::asin(value));
}


inline atl::Conditional<double> _avfml_cnd_asin( const atl::Conditional<double>& value )
{
	if (value == atl::NIL)
		return atl::NIL;
	else
		return _avfml_asin(value.Get());
}


inline double _avfml_acos( double value )
{
	return _avfml_internal::rad_to_deg(std::acos(value));
}


inline atl::Conditional<double> _avfml_cnd_acos( const atl::Conditional<double>& value )
{
	if (value == atl::NIL)
		return atl::NIL;
	else
		return _avfml_acos(value.Get());
}


inline double _avfml_atan( double value )
{
	return _avfml_internal::rad_to_deg(std::atan(value));
}


inline atl::Conditional<double> _avfml_cnd_atan( const atl::Conditional<double>& value )
{
	if (value == atl::NIL)
		return atl::NIL;
	else
		return _avfml_atan(value.Get());
}


inline double _avfml_exp( double value )
{
	return std::exp(value);
}


inline atl::Conditional<double> _avfml_cnd_exp( const atl::Conditional<double>& value )
{
	if (value == atl::NIL)
		return atl::NIL;
	else
		return _avfml_exp(value.Get());
}


inline double _avfml_ln( double value )
{
	return std::log(value);
}


inline atl::Conditional<double> _avfml_cnd_ln( const atl::Conditional<double>& value )
{
	if (value == atl::NIL)
		return atl::NIL;
	else
		return _avfml_ln(value.Get());
}


inline double _avfml_log( double value )
{
	return std::log10(value);
}


inline atl::Conditional<double> _avfml_cnd_log( const atl::Conditional<double>& value )
{
	if (value == atl::NIL)
		return atl::NIL;
	else
		return _avfml_log(value.Get());
}


inline double _avfml_sqrt( double value )
{
	return std::sqrt(value);
}


inline atl::Conditional<double> _avfml_cnd_sqrt( const atl::Conditional<double>& value )
{
	if (value == atl::NIL)
		return atl::NIL;
	else
		return _avfml_sqrt(value.Get());
}


inline double _avfml_floor( double value )
{
	return std::floor(value);
}


inline atl::Conditional<double> _avfml_cnd_floor( const atl::Conditional<double>& value )
{
	if (value == atl::NIL)
		return atl::NIL;
	else
		return _avfml_floor(value.Get());
}


inline double _avfml_ceil( double value )
{
	return std::ceil(value);
}


inline atl::Conditional<double> _avfml_cnd_ceil( const atl::Conditional<double>& value )
{
	if (value == atl::NIL)
		return atl::NIL;
	else
		return _avfml_ceil(value.Get());
}


inline int _avfml_absi( int value )
{
	return std::abs(value);
}


inline atl::int64 _avfml_absl( atl::int64 value )
{
	return std::abs(value);
}


inline double _avfml_absf( double value )
{
	return std::abs(value);
}


inline atl::Conditional<int> _avfml_cnd_absi( const atl::Conditional<int>& value )
{
	if (value == atl::NIL)
		return atl::NIL;
	else
		return _avfml_absi(value.Get());
}


inline atl::Conditional<atl::int64> _avfml_cnd_absl( const atl::Conditional<atl::int64>& value )
{
	if (value == atl::NIL)
		return atl::NIL;
	else
		return _avfml_absl(value.Get());
}


inline atl::Conditional<double> _avfml_cnd_absf( const atl::Conditional<double>& value )
{
	if (value == atl::NIL)
		return atl::NIL;
	else
		return _avfml_absf(value.Get());
}


inline double _avfml_powi( double a, int b )
{
	return std::pow(a, b);
}


inline double _avfml_powf( double a, double b )
{
	return std::pow(a, b);
}


inline atl::Conditional<double> _avfml_cnd_powi( const atl::Conditional<double>& a, const atl::Conditional<int>& b )
{
	if (a == atl::NIL || b == atl::NIL)
		return atl::NIL;
	else
		return _avfml_powi(a.Get(), b.Get());
}


inline atl::Conditional<double> _avfml_cnd_powf( const atl::Conditional<double>& a, const atl::Conditional<double>& b )
{
	if (a == atl::NIL || b == atl::NIL)
		return atl::NIL;
	else
		return _avfml_powf(a.Get(), b.Get());
}


inline double _avfml_round( double value )
{
	return std::floor(value + 0.5);
}


inline double _avfml_round( double value, int p )
{
	double multipler = std::pow(10.0, p);
	return std::floor(value * multipler + 0.5) / multipler;
}


inline atl::Conditional<double> _avfml_cnd_round( const atl::Conditional<double>& value )
{
	if (value == atl::NIL)
		return atl::NIL;
	else
		return _avfml_round(value.Get());
}


inline atl::Conditional<double> _avfml_cnd_round( const atl::Conditional<double>& value, const atl::Conditional<int>& p )
{
	if (value == atl::NIL || p == atl::NIL)
		return atl::NIL;
	else
		return _avfml_round(value.Get(), p.Get());
}


//
// Array aggregating functions
//


inline int _avfml_mini( const atl::Array<int>& values )
{
	return _avfml_internal::aggregate_array< int, int, _avfml_internal::min_aggregator<int> >(values);
}


inline atl::int64 _avfml_minl( const atl::Array<atl::int64>& values )
{
	return _avfml_internal::aggregate_array< atl::int64, atl::int64, _avfml_internal::min_aggregator<atl::int64> >(values);
}


inline double _avfml_minf( const atl::Array<float>& values )
{
	return _avfml_internal::aggregate_array< float, double, _avfml_internal::min_aggregator<double> >(values);
}


inline double _avfml_mind( const atl::Array<double>& values )
{
	return _avfml_internal::aggregate_array< double, double, _avfml_internal::min_aggregator<double> >(values);
}


inline int _avfml_maxi( const atl::Array<int>& values )
{
	return _avfml_internal::aggregate_array< int, int, _avfml_internal::max_aggregator<int> >(values);
}


inline atl::int64 _avfml_maxl( const atl::Array<atl::int64>& values )
{
	return _avfml_internal::aggregate_array< atl::int64, atl::int64, _avfml_internal::max_aggregator<atl::int64> >(values);
}


inline double _avfml_maxf( const atl::Array<float>& values )
{
	return _avfml_internal::aggregate_array< float, double, _avfml_internal::max_aggregator<double> >(values);
}


inline double _avfml_maxd( const atl::Array<double>& values )
{
	return _avfml_internal::aggregate_array< double, double, _avfml_internal::max_aggregator<double> >(values);
}


inline int _avfml_sumi( const atl::Array<int>& values )
{
	return _avfml_internal::aggregate_array< int, int, _avfml_internal::sum_aggregator<int> >(values, 0);
}


inline atl::int64 _avfml_suml( const atl::Array<atl::int64>& values )
{
	return _avfml_internal::aggregate_array< atl::int64, atl::int64, _avfml_internal::sum_aggregator<atl::int64> >(values, 0);
}


inline double _avfml_sumf( const atl::Array<float>& values )
{
	return _avfml_internal::aggregate_array< float, double, _avfml_internal::sum_aggregator<double> >(values, 0.0);
}


inline double _avfml_sumd( const atl::Array<double>& values )
{
	return _avfml_internal::aggregate_array< double, double, _avfml_internal::sum_aggregator<double> >(values, 0.0);
}


inline int _avfml_producti( const atl::Array<int>& values )
{
	return _avfml_internal::aggregate_array< int, int, _avfml_internal::product_aggregator<int> >(values, 1);
}


inline atl::int64 _avfml_productl( const atl::Array<atl::int64>& values )
{
	return _avfml_internal::aggregate_array< atl::int64, atl::int64, _avfml_internal::product_aggregator<atl::int64> >(values, 1);
}


inline double _avfml_productf( const atl::Array<float>& values )
{
	return _avfml_internal::aggregate_array< float, double, _avfml_internal::product_aggregator<double> >(values, 1.0);
}


inline double _avfml_productd( const atl::Array<double>& values )
{
	return _avfml_internal::aggregate_array< double, double, _avfml_internal::product_aggregator<double> >(values, 1.0);
}


inline int _avfml_avgi( const atl::Array<int>& values )
{
	atl::int64 sum = _avfml_internal::aggregate_array< int, atl::int64, _avfml_internal::sum_aggregator<atl::int64> >(values);
	
	return static_cast<int>(sum / values.Size());
}


inline atl::int64 _avfml_avgl( const atl::Array<atl::int64>& values )
{
	atl::int64 sum = _avfml_internal::aggregate_array< atl::int64, atl::int64, _avfml_internal::sum_aggregator<atl::int64> >(values);
	
	return sum / values.Size();
}


inline double _avfml_avgf( const atl::Array<float>& values )
{
	long double sum = _avfml_internal::aggregate_array< float, long double, _avfml_internal::sum_aggregator<long double> >(values);

	return static_cast<double>(sum / values.Size());
}


inline double _avfml_avgd( const atl::Array<double>& values )
{
	long double sum = _avfml_internal::aggregate_array< double, long double, _avfml_internal::sum_aggregator<long double> >(values);

	return static_cast<double>(sum / values.Size());
}


inline int _avfml_mediani( const atl::Array<int>& values )
{
	return _avfml_internal::median_impl<int, int>(values);
}


inline atl::int64 _avfml_medianl( const atl::Array<atl::int64>& values )
{
	return _avfml_internal::median_impl<atl::int64, atl::int64>(values);
}


inline double _avfml_medianf( const atl::Array<float>& values )
{
	return _avfml_internal::median_impl<float, double>(values);
}


inline double _avfml_mediand( const atl::Array<double>& values )
{
	return _avfml_internal::median_impl<double, double>(values);
}


inline int _avfml_nth_valuei( const atl::Array<int>& values, int n )
{
	return _avfml_internal::nth_value_impl<int, int>(values, n);
}


inline atl::int64 _avfml_nth_valuel( const atl::Array<atl::int64>& values, int n )
{
	return _avfml_internal::nth_value_impl<atl::int64, atl::int64>(values, n);
}


inline double _avfml_nth_valuef( const atl::Array<float>& values, int n )
{
	return _avfml_internal::nth_value_impl<float, double>(values, n);
}


inline double _avfml_nth_valued( const atl::Array<double>& values, int n )
{
	return _avfml_internal::nth_value_impl<double, double>(values, n);
}


inline int _avfml_quantilei( const atl::Array<int>& values, double point )
{
	return _avfml_internal::quantile_impl<int, int>(values, point);
}


inline atl::int64 _avfml_quantilel( const atl::Array<atl::int64>& values, double point )
{
	return _avfml_internal::quantile_impl<atl::int64, atl::int64>(values, point);
}


inline double _avfml_quantilef( const atl::Array<float>& values, double point )
{
	return _avfml_internal::quantile_impl<float, double>(values, point);
}


inline double _avfml_quantiled( const atl::Array<double>& values, double point )
{
	return _avfml_internal::quantile_impl<double, double>(values, point);
}


inline double _avfml_variancef( const atl::Array<float>& values )
{
	return _avfml_internal::variance_impl<float>(values);
}


inline double _avfml_varianced( const atl::Array<double>& values )
{
	return _avfml_internal::variance_impl<double>(values);
}


inline double _avfml_std_devf( const atl::Array<float>& values )
{
	return std::sqrt(_avfml_variancef(values));
}


inline double _avfml_std_devd( const atl::Array<double>& values )
{
	return std::sqrt(_avfml_varianced(values));
}


inline bool _avfml_all( const atl::Array<bool>& values )
{
	return _avfml_internal::aggregate_array< bool, bool, _avfml_internal::and_aggregator >(values, true);
}


inline bool _avfml_any( const atl::Array<bool>& values )
{
	return _avfml_internal::aggregate_array< bool, bool, _avfml_internal::or_aggregator >(values, false);
}


inline atl::Conditional<int> _avfml_cnd_mini( atl::Conditional<const atl::Array<int>&> values )
{
	if (values == atl::NIL)
		return atl::NIL;
	else
		return _avfml_mini(values.Get());
}


inline atl::Conditional<atl::int64> _avfml_cnd_minl( atl::Conditional<const atl::Array<atl::int64>&> values )
{
	if (values == atl::NIL)
		return atl::NIL;
	else
		return _avfml_minl(values.Get());
}


inline atl::Conditional<double> _avfml_cnd_minf( atl::Conditional<const atl::Array<float>&> values )
{
	if (values == atl::NIL)
		return atl::NIL;
	else
		return _avfml_minf(values.Get());
}


inline atl::Conditional<double> _avfml_cnd_mind( atl::Conditional<const atl::Array<double>&> values )
{
	if (values == atl::NIL)
		return atl::NIL;
	else
		return _avfml_mind(values.Get());
}


inline atl::Conditional<int> _avfml_cnd_maxi( atl::Conditional<const atl::Array<int>&> values )
{
	if (values == atl::NIL)
		return atl::NIL;
	else
		return _avfml_maxi(values.Get());
}


inline atl::Conditional<atl::int64> _avfml_cnd_maxl( atl::Conditional<const atl::Array<atl::int64>&> values )
{
	if (values == atl::NIL)
		return atl::NIL;
	else
		return _avfml_maxl(values.Get());
}


inline atl::Conditional<double> _avfml_cnd_maxf( atl::Conditional<const atl::Array<float>&> values )
{
	if (values == atl::NIL)
		return atl::NIL;
	else
		return _avfml_maxf(values.Get());
}


inline atl::Conditional<double> _avfml_cnd_maxd( atl::Conditional<const atl::Array<double>&> values )
{
	if (values == atl::NIL)
		return atl::NIL;
	else
		return _avfml_maxd(values.Get());
}


inline atl::Conditional<int> _avfml_cnd_sumi( atl::Conditional<const atl::Array<int>&> values )
{
	if (values == atl::NIL)
		return atl::NIL;
	else
		return _avfml_sumi(values.Get());
}


inline atl::Conditional<atl::int64> _avfml_cnd_suml( atl::Conditional<const atl::Array<atl::int64>&> values )
{
	if (values == atl::NIL)
		return atl::NIL;
	else
		return _avfml_suml(values.Get());
}


inline atl::Conditional<double> _avfml_cnd_sumf( atl::Conditional<const atl::Array<float>&> values )
{
	if (values == atl::NIL)
		return atl::NIL;
	else
		return _avfml_sumf(values.Get());
}


inline atl::Conditional<double> _avfml_cnd_sumd( atl::Conditional<const atl::Array<double>&> values )
{
	if (values == atl::NIL)
		return atl::NIL;
	else
		return _avfml_sumd(values.Get());
}


inline atl::Conditional<int> _avfml_cnd_producti( atl::Conditional<const atl::Array<int>&> values )
{
	if (values == atl::NIL)
		return atl::NIL;
	else
		return _avfml_producti(values.Get());
}


inline atl::Conditional<atl::int64> _avfml_cnd_productl( atl::Conditional<const atl::Array<atl::int64>&> values )
{
	if (values == atl::NIL)
		return atl::NIL;
	else
		return _avfml_productl(values.Get());
}


inline atl::Conditional<double> _avfml_cnd_productf( atl::Conditional<const atl::Array<float>&> values )
{
	if (values == atl::NIL)
		return atl::NIL;
	else
		return _avfml_productf(values.Get());
}


inline atl::Conditional<double> _avfml_cnd_productd( atl::Conditional<const atl::Array<double>&> values )
{
	if (values == atl::NIL)
		return atl::NIL;
	else
		return _avfml_productd(values.Get());
}


inline atl::Conditional<int> _avfml_cnd_avgi( atl::Conditional<const atl::Array<int>&> values )
{
	if (values == atl::NIL)
		return atl::NIL;
	else
		return _avfml_avgi(values.Get());
}


inline atl::Conditional<atl::int64> _avfml_cnd_avgl( atl::Conditional<const atl::Array<atl::int64>&> values )
{
	if (values == atl::NIL)
		return atl::NIL;
	else
		return _avfml_avgl(values.Get());
}


inline atl::Conditional<double> _avfml_cnd_avgf( atl::Conditional<const atl::Array<float>&> values )
{
	if (values == atl::NIL)
		return atl::NIL;
	else
		return _avfml_avgf(values.Get());
}


inline atl::Conditional<double> _avfml_cnd_avgd( atl::Conditional<const atl::Array<double>&> values )
{
	if (values == atl::NIL)
		return atl::NIL;
	else
		return _avfml_avgd(values.Get());
}


inline atl::Conditional<int> _avfml_cnd_mediani( atl::Conditional<const atl::Array<int>&> values )
{
	if (values == atl::NIL)
		return atl::NIL;
	else
		return _avfml_mediani(values.Get());
}


inline atl::Conditional<atl::int64> _avfml_cnd_medianl( atl::Conditional<const atl::Array<atl::int64>&> values )
{
	if (values == atl::NIL)
		return atl::NIL;
	else
		return _avfml_medianl(values.Get());
}


inline atl::Conditional<double> _avfml_cnd_medianf( atl::Conditional<const atl::Array<float>&> values )
{
	if (values == atl::NIL)
		return atl::NIL;
	else
		return _avfml_medianf(values.Get());
}


inline atl::Conditional<double> _avfml_cnd_mediand( atl::Conditional<const atl::Array<double>&> values )
{
	if (values == atl::NIL)
		return atl::NIL;
	else
		return _avfml_mediand(values.Get());
}


inline atl::Conditional<int> _avfml_cnd_nth_valuei( atl::Conditional<const atl::Array<int>&> values, const atl::Conditional<int>& n )
{
	if (values == atl::NIL || n == atl::NIL)
		return atl::NIL;
	else
		return _avfml_nth_valuei(values.Get(), n.Get());
}


inline atl::Conditional<atl::int64> _avfml_cnd_nth_valuel( atl::Conditional<const atl::Array<atl::int64>&> values, const atl::Conditional<int>& n )
{
	if (values == atl::NIL || n == atl::NIL)
		return atl::NIL;
	else
		return _avfml_nth_valuel(values.Get(), n.Get());
}


inline atl::Conditional<double> _avfml_cnd_nth_valuef( atl::Conditional<const atl::Array<float>&> values, const atl::Conditional<int>& n )
{
	if (values == atl::NIL || n == atl::NIL)
		return atl::NIL;
	else
		return _avfml_nth_valuef(values.Get(), n.Get());
}


inline atl::Conditional<double> _avfml_cnd_nth_valued( atl::Conditional<const atl::Array<double>&> values, const atl::Conditional<int>& n )
{
	if (values == atl::NIL || n == atl::NIL)
		return atl::NIL;
	else
		return _avfml_nth_valued(values.Get(), n.Get());
}


inline atl::Conditional<int> _avfml_cnd_quantilei( atl::Conditional<const atl::Array<int>&> values, const atl::Conditional<double>& point )
{
	if (values == atl::NIL || point == atl::NIL)
		return atl::NIL;
	else
		return _avfml_quantilei(values.Get(), point.Get());
}


inline atl::Conditional<atl::int64> _avfml_cnd_quantilel( atl::Conditional<const atl::Array<atl::int64>&> values, const atl::Conditional<double>& point )
{
	if (values == atl::NIL || point == atl::NIL)
		return atl::NIL;
	else
		return _avfml_quantilel(values.Get(), point.Get());
}


inline atl::Conditional<double> _avfml_cnd_quantilef( atl::Conditional<const atl::Array<float>&> values, const atl::Conditional<double>& point )
{
	if (values == atl::NIL || point == atl::NIL)
		return atl::NIL;
	else
		return _avfml_quantilef(values.Get(), point.Get());
}


inline atl::Conditional<double> _avfml_cnd_quantiled( atl::Conditional<const atl::Array<double>&> values, const atl::Conditional<double>& point )
{
	if (values == atl::NIL || point == atl::NIL)
		return atl::NIL;
	else
		return _avfml_quantiled(values.Get(), point.Get());
}




inline double _avfml_cnd_variancef( atl::Conditional<const atl::Array<float>&> values )
{
	if (values == atl::NIL)
		return atl::NIL;
	else
		return _avfml_variancef(values.Get());
}


inline double _avfml_cnd_varianced( atl::Conditional<const atl::Array<double>&> values )
{
	if (values == atl::NIL)
		return atl::NIL;
	else
		return _avfml_varianced(values.Get());
}


inline double _avfml_cnd_std_devf( atl::Conditional<const atl::Array<float>&> values )
{
	if (values == atl::NIL)
		return atl::NIL;
	else
		return _avfml_std_devf(values.Get());
}


inline double _avfml_cnd_std_devd( atl::Conditional<const atl::Array<double>&> values )
{
	if (values == atl::NIL)
		return atl::NIL;
	else
		return _avfml_std_devd(values.Get());
}


inline atl::Conditional<bool> _avfml_cnd_all( atl::Conditional<const atl::Array<bool>&> values )
{
	if (values == atl::NIL)
		return atl::NIL;
	else
		return _avfml_all(values.Get());
}


inline atl::Conditional<bool> _avfml_cnd_any( atl::Conditional<const atl::Array<bool>&> values )
{
	if (values == atl::NIL)
		return atl::NIL;
	else
		return _avfml_any(values.Get());
}


inline int _avfml_mini( int a, int b )
{
	return a < b ? a : b;
}


inline atl::int64 _avfml_minl( atl::int64 a, atl::int64 b )
{
	return a < b ? a : b;
}


inline double _avfml_minf( double a, double b )
{
	return a < b ? a : b;
}


inline atl::Conditional<int> _avfml_cnd_mini( atl::Conditional<int> a, atl::Conditional<int> b )
{
	if (a == atl::NIL || b == atl::NIL)
		return atl::NIL;
	else
		return _avfml_mini(a.Get(), b.Get());
}


inline atl::Conditional<atl::int64> _avfml_cnd_minl( atl::Conditional<atl::int64> a, atl::Conditional<atl::int64> b )
{
	if (a == atl::NIL || b == atl::NIL)
		return atl::NIL;
	else
		return _avfml_minl(a.Get(), b.Get());
}


inline atl::Conditional<double> _avfml_cnd_minf( atl::Conditional<double> a, atl::Conditional<double> b )
{
	if (a == atl::NIL || b == atl::NIL)
		return atl::NIL;
	else
		return _avfml_minf(a.Get(), b.Get());
}


inline int _avfml_maxi( int a, int b )
{
	return a > b ? a : b;
}


inline atl::int64 _avfml_maxl( atl::int64 a, atl::int64 b )
{
	return a > b ? a : b;
}


inline double _avfml_maxf( double a, double b )
{
	return a > b ? a : b;
}


inline atl::Conditional<int> _avfml_cnd_maxi( atl::Conditional<int> a, atl::Conditional<int> b )
{
	if (a == atl::NIL || b == atl::NIL)
		return atl::NIL;
	else
		return _avfml_maxi(a.Get(), b.Get());
}


inline atl::Conditional<atl::int64> _avfml_cnd_maxl( atl::Conditional<atl::int64> a, atl::Conditional<atl::int64> b )
{
	if (a == atl::NIL || b == atl::NIL)
		return atl::NIL;
	else
		return _avfml_maxl(a.Get(), b.Get());
}


inline atl::Conditional<double> _avfml_cnd_maxf( atl::Conditional<double> a, atl::Conditional<double> b )
{
	if (a == atl::NIL || b == atl::NIL)
		return atl::NIL;
	else
		return _avfml_maxf(a.Get(), b.Get());
}


inline int _avfml_avgi( int a, int b )
{
	return static_cast<int>( (static_cast<atl::int64>(a) + static_cast<atl::int64>(b)) / 2 );
}


inline atl::int64 _avfml_avgl( atl::int64 a, atl::int64 b )
{
	atl::int64 av = a / 2;
	atl::int64 ar = a % 2;
	atl::int64 bv = b / 2;
	atl::int64 br = b % 2;

	return av + bv + (ar + br) / 2;
}


inline double _avfml_avgf( double a, double b )
{
	return static_cast<double>( (static_cast<long double>(a) + static_cast<long double>(b)) / 2.0 );
}


inline atl::Conditional<int> _avfml_cnd_avgi( atl::Conditional<int> a, atl::Conditional<int> b )
{
	if (a == atl::NIL || b == atl::NIL)
		return atl::NIL;
	else
		return _avfml_avgi(a.Get(), b.Get());
}


inline atl::Conditional<atl::int64> _avfml_cnd_avgl( atl::Conditional<atl::int64> a, atl::Conditional<atl::int64> b )
{
	if (a == atl::NIL || b == atl::NIL)
		return atl::NIL;
	else
		return _avfml_avgl(a.Get(), b.Get());
}


inline atl::Conditional<double> _avfml_cnd_avgf( atl::Conditional<double> a, atl::Conditional<double> b )
{
	if (a == atl::NIL || b == atl::NIL)
		return atl::NIL;
	else
		return _avfml_avgf(a.Get(), b.Get());
}


inline int _avfml_lerpi( int a, int b, double p )
{
	if (b < a)
	{
		std::swap(a, b);
		p = 1.0 - p;
	}
		
	return a + static_cast<int>(std::floor(static_cast<double>(b - a) * p + 0.5));
}


inline atl::int64 _avfml_lerpl( atl::int64 a, atl::int64 b, double p )
{
	if (b < a)
	{
		std::swap(a, b);
		p = 1.0 - p;
	}
		
	return a + static_cast<atl::int64>(std::floor(static_cast<double>(b - a) * p + 0.5));
}


inline double _avfml_lerpf( double a, double b, double p )
{
	return a + (b - a) * p;
}


inline atl::Conditional<int> _avfml_cnd_lerpi( const atl::Conditional<int>& a, const atl::Conditional<int>& b, const atl::Conditional<double>& p )
{
	if (a == atl::NIL || b == atl::NIL || p == atl::NIL)
		return atl::NIL;
	else
		return _avfml_lerpi(a.Get(), b.Get(), p.Get());
}


inline atl::Conditional<atl::int64> _avfml_cnd_lerpl( const atl::Conditional<atl::int64>& a, const atl::Conditional<atl::int64>& b, const atl::Conditional<double>& p )
{
	if (a == atl::NIL || b == atl::NIL || p == atl::NIL)
		return atl::NIL;
	else
		return _avfml_lerpl(a.Get(), b.Get(), p.Get());
}


inline atl::Conditional<double> _avfml_cnd_lerpf( const atl::Conditional<double>& a, const atl::Conditional<double>& b, const atl::Conditional<double>& p )
{
	if (a == atl::NIL || b == atl::NIL || p == atl::NIL)
		return atl::NIL;
	else
		return _avfml_lerpf(a.Get(), b.Get(), p.Get());
}


inline atl::String _avfml_to_stringb( bool value )
{
	return value ? "True" : "False";
}


inline atl::String _avfml_to_stringi( int value )
{
	char text[16];
	std::sprintf(text, "%d", value);
	
	return text;
}

inline atl::String _avfml_to_stringl( atl::int64 value )
{
	char text[32];
	std::sprintf(text, "%lld", value);
	
	return text;
}

inline atl::String _avfml_to_stringf( double value )
{
	char text[128];
	std::sprintf(text, "%g", value);

	return text;
}


inline atl::Conditional<atl::String> _avfml_cnd_to_stringb( atl::Conditional<bool> value )
{
	if (value == atl::NIL)
		return atl::NIL;
	else
		return _avfml_to_stringb(value.Get());
}


inline atl::Conditional<atl::String> _avfml_cnd_to_stringi( atl::Conditional<int> value )
{
	if (value == atl::NIL)
		return atl::NIL;
	else
		return _avfml_to_stringi(value.Get());
}


inline atl::Conditional<atl::String> _avfml_cnd_to_stringl( atl::Conditional<atl::int64> value )
{
	if (value == atl::NIL)
		return atl::NIL;
	else
		return _avfml_to_stringl(value.Get());
}


inline atl::Conditional<atl::String> _avfml_cnd_to_stringf( atl::Conditional<double> value )
{
	if (value == atl::NIL)
		return atl::NIL;
	else
		return _avfml_to_stringf(value.Get());
}


inline atl::Conditional<int> _avfml_cnd_string_size( const atl::Conditional<const atl::String&> value )
{
	if (value == atl::NIL)
		return atl::NIL;
	else
		return value.Get().Size();
}


inline atl::Conditional<atl::String> _avfml_cnd_concat( const atl::Conditional<const atl::String&> a, const atl::Conditional<const atl::String&> b )
{
	if (a == atl::NIL || b == atl::NIL)
		return atl::NIL;
	else
		return a.Get() + b.Get();
}


inline atl::Conditional<bool> _avfml_cnd_lesss( const atl::Conditional<const atl::String&> a, const atl::Conditional<const atl::String&> b )
{
	if (a == atl::NIL || b == atl::NIL)
		return atl::NIL;
	else
		return a.Get() < b.Get();
}


inline atl::Conditional<bool> _avfml_cnd_lesseqs( const atl::Conditional<const atl::String&> a, const atl::Conditional<const atl::String&> b )
{
	if (a == atl::NIL || b == atl::NIL)
		return atl::NIL;
	else
		return a.Get() <= b.Get();
}


inline atl::String _avfml_substring( const atl::String& str, int pos )
{
	if (pos < 0 || pos > str.Size())
		throw atl::DomainError("Substring portion is out of valid range.");

	return str.Substr(pos);
}


inline atl::String _avfml_substring( const atl::String& str, int pos, int len )
{
	if (pos < 0 || pos > str.Size() || len < 0)
		throw atl::DomainError("Substring portion is out of valid range.");

	return str.Substr(pos, len);
}


inline atl::Conditional<atl::String> _avfml_cnd_substring( const atl::Conditional<const atl::String&>& str, const atl::Conditional<int> pos )
{
	if (str == atl::NIL || pos == atl::NIL)
		return atl::NIL;
	else
		return _avfml_substring(str.Get(), pos.Get());
}


inline atl::Conditional<atl::String> _avfml_cnd_substring( const atl::Conditional<const atl::String&>& str, const atl::Conditional<int> pos, const atl::Conditional<int> len )
{
	if (str == atl::NIL || pos == atl::NIL || len == atl::NIL)
		return atl::NIL;
	else
		return _avfml_substring(str.Get(), pos.Get(), len.Get());
}


inline atl::String _avfml_replace( const atl::String& str, const atl::String& find, const atl::String& replace )
{
	return str.Replace(find, replace);
}


inline atl::Conditional<atl::String> _avfml_cnd_replace( const atl::Conditional<const atl::String&>& str, const atl::Conditional<const atl::String&>& find, const atl::Conditional<const atl::String&>& replace )
{
	if (str == atl::NIL || find == atl::NIL || replace == atl::NIL)
		return atl::NIL;
	else
		return _avfml_replace(str.Get(), find.Get(), replace.Get());
}


inline atl::Conditional<bool> _avfml_cnd_starts_with( const atl::Conditional<const atl::String&>& str, const atl::Conditional<const atl::String&>& value )
{
	if (str == atl::NIL || value == atl::NIL)
		return atl::NIL;
	else
		return str.Get().StartsWith(value.Get());
}


inline atl::Conditional<bool> _avfml_cnd_ends_with( const atl::Conditional<const atl::String&>& str, const atl::Conditional<const atl::String&>& value )
{
	if (str == atl::NIL || value == atl::NIL)
		return atl::NIL;
	else
		return str.Get().EndsWith(value.Get());
}


inline bool _avfml_contains( const atl::String& str, const atl::String& value )
{
	return str.Find(value) != atl::String::NPos;
}


inline atl::Conditional<bool> _avfml_cnd_contains( const atl::Conditional<const atl::String&>& str, const atl::Conditional<const atl::String&>& value )
{
	if (str == atl::NIL || value == atl::NIL)
		return atl::NIL;
	else
		return _avfml_contains(str.Get(), value.Get());
}


inline int _avfml_find( const atl::String& str, const atl::String& value )
{
	return str.Find(value);
}


inline int _avfml_find( const atl::String& str, const atl::String& value, int pos )
{
	if (pos < 0)
		throw atl::DomainError("Start position of string find function is out of valid range.");

	return str.Find(value, pos);
}


inline atl::Conditional<int> _avfml_cnd_find( const atl::Conditional<const atl::String&>& str, const atl::Conditional<const atl::String&>& value )
{
	if (str == atl::NIL || value == atl::NIL)
		return atl::NIL;
	else
		return _avfml_find(str.Get(), value.Get());
}


inline atl::Conditional<int> _avfml_cnd_find( const atl::Conditional<const atl::String&>& str, const atl::Conditional<const atl::String&>& value, const atl::Conditional<int>& pos )
{
	if (str == atl::NIL || value == atl::NIL || pos == atl::NIL)
		return atl::NIL;
	else
		return _avfml_find(str.Get(), value.Get(), pos.Get());
}


inline atl::Conditional<int> _avfml_cnd_rfind( const atl::Conditional<const atl::String&>& str, const atl::Conditional<const atl::String&>& value )
{
	if (str == atl::NIL || value == atl::NIL)
		return atl::NIL;
	else
		return str.Get().RFind(value.Get());
}


inline atl::Conditional<int> _avfml_cnd_rfind( const atl::Conditional<const atl::String&>& str, const atl::Conditional<const atl::String&>& value, const atl::Conditional<int>& pos )
{
	if (str == atl::NIL || value == atl::NIL || pos == atl::NIL)
		return atl::NIL;
	else
		return str.Get().RFind(value.Get(), pos.Get());
}


inline atl::Conditional<bool> _avfml_cnd_empty( const atl::Conditional<const atl::String&>& str )
{
	if (str == atl::NIL)
		return atl::NIL;
	else
		return str.Get().Empty();
}


inline atl::Conditional<atl::String> _avfml_cnd_trim( const atl::Conditional<const atl::String&>& str )
{
	if (str == atl::NIL)
		return atl::NIL;
	else
		return str.Get().Strip();
}


inline atl::String _avfml_to_lower( const atl::String& str )
{
	atl::String out;
	out.Resize(str.Size());

	for( int i = 0; i < str.Size(); ++i )
		out[i] = std::towlower(str[i]);

	return out;
}


inline atl::Conditional<atl::String> _avfml_cnd_to_lower( const atl::Conditional<const atl::String&>& str )
{
	if (str == atl::NIL)
		return atl::NIL;
	else
		return _avfml_to_lower(str.Get());
}


inline atl::String _avfml_to_upper( const atl::String& str )
{
	atl::String out;
	out.Resize(str.Size());

	for( int i = 0; i < str.Size(); ++i )
		out[i] = std::towupper(str[i]);

	return out;
}


inline atl::Conditional<atl::String> _avfml_cnd_to_upper( const atl::Conditional<const atl::String&>& str )
{
	if (str == atl::NIL)
		return atl::NIL;
	else
		return _avfml_to_upper(str.Get());
}


#ifdef _MSC_VER
	#pragma warning(pop)
#endif

#endif // EXPRESSIONS_RUNTIME_H
