//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_PIXEL_HXX
#define AVL_PIXEL_HXX

#include "ATL/AtlTypes.h"
#include "Image/PlainTypes.h"
#include "Basic/Types.h"

namespace avl
{
	template <class T>
	struct PromotionTraits
	{
		typedef atl::sint32	Addable;
	};

	template <>
	struct PromotionTraits<float>
	{
		typedef float	Addable;
	};

	template <>
	struct PromotionTraits<double>
	{
		typedef double	Addable;
	};

	template <typename T> struct Pixel1;
	template <typename T> struct Pixel2;
	template <typename T> struct Pixel3;
	template <typename T> struct Pixel4;

	template <typename T>
	struct Pixel1
	{
		typedef T TYPE;

		template<typename NewType>
		struct CastType { typedef Pixel1<NewType> P; };

		T x;

		inline Pixel1()
			: x(0) {}

		explicit inline Pixel1( const T& x ) 
			: x(x) {}

		inline Pixel1( const Pixel1& rhs )
			: x( rhs.x ) {}

		explicit inline Pixel1( const Pixel& rhs )
			: x( (T)rhs[0] ) {}

		inline Pixel ToPixel() const
			{ return Pixel((float)x); }

		template <typename R>
		inline static Pixel1<T> Convert( const Pixel1<R>& rhs )
		{
			return Pixel1<T>( (T)rhs.x );
		}

		template <typename R>
		inline static Pixel1<T> Convert( const Pixel2<R>& rhs )
		{
			typedef typename PromotionTraits<R>::Addable A;
			return Pixel1<T>( (T)( ( A(rhs.x) + rhs.y ) / 2 ) );
		}

		template <typename R>
		inline static Pixel1<T> Convert( const Pixel3<R>& rhs )
		{
			typedef typename PromotionTraits<R>::Addable A;
			return Pixel1<T>( (T)( ( A(rhs.x) + rhs.y + rhs.z ) / 3 ) );
		}

		template <typename R>
		inline static Pixel1<T> Convert( const Pixel4<R>& rhs )
		{
			typedef typename PromotionTraits<R>::Addable A;
			return Pixel1<T>( (T)( ( A(rhs.x) + rhs.y + rhs.z + rhs.w ) / 4 ) );
		}

		inline static PlainType::Type Type()	{ return _typeof(T()); }
		inline static int       Size()	{ return 1; }
		
		static const int _SIZE = 1;

		inline T*	Data() const	{ return (T*)this; }

		inline Pixel1 operator + ( const Pixel1& rhs ) const
			{ return Pixel1( x + rhs.x ); }
		inline Pixel1 operator - ( const Pixel1& rhs ) const
			{ return Pixel1( x - rhs.x ); }
		inline Pixel1 operator * ( const Pixel1& rhs ) const
			{ return Pixel1( x * rhs.x ); }
		inline Pixel1 operator / ( const Pixel1& rhs ) const
			{ return Pixel1( x / rhs.x ); }
		inline Pixel1 operator % ( const Pixel1& rhs ) const
			{ return Pixel1( x % rhs.x ); }
		inline Pixel1 operator - () const
			{ return Pixel1( -x ); }

		inline Pixel1& operator = ( const Pixel1& rhs )
			{ x = rhs.x; return (*this); }
		inline Pixel1& operator += ( const Pixel1& rhs )
			{ x += rhs.x; return (*this); }
		inline Pixel1& operator -= ( const Pixel1& rhs )
			{ x -= rhs.x; return (*this); }
		inline Pixel1& operator *= ( const Pixel1& rhs )
			{ x *= rhs.x; return (*this); }
		inline Pixel1& operator /= ( const Pixel1& rhs )
			{ x /= rhs.x; return (*this); }
		inline Pixel1& operator %= ( const Pixel1& rhs )
			{ x %= rhs.x; return (*this); }

		inline Pixel1 operator + ( T rhs ) const
			{ return Pixel1( x + rhs ); }
		inline Pixel1 operator - ( T rhs ) const
			{ return Pixel1( x - rhs ); }
		inline Pixel1 operator * ( T rhs ) const
			{ return Pixel1( x * rhs ); }
		inline Pixel1 operator / ( T rhs ) const
			{ return Pixel1( x / rhs ); }
		inline Pixel1 operator % ( T rhs ) const
			{ return Pixel1( x % rhs ); }
		inline Pixel1 operator >> ( T rhs ) const
			{ return Pixel1( x >> rhs ); }

		inline Pixel1& operator += ( T rhs )
			{ x += rhs; return (*this); }
		inline Pixel1& operator -= ( T rhs )
			{ x -= rhs; return (*this); }
		inline Pixel1& operator *= ( T rhs )
			{ x *= rhs; return (*this); }
		inline Pixel1& operator /= ( T rhs )
			{ x /= rhs; return (*this); }
		inline Pixel1& operator %= ( T rhs )
			{ x %= rhs; return (*this); }
		inline Pixel1& operator >>= ( T rhs )
			{ x >>= rhs; return (*this); }

		template<typename R>
		inline void AddWeighted( const Pixel1<R>& rhs, T weight )
		{
			x += (T)rhs.x * weight;
		}

		template<typename R>
		inline void Add( const Pixel1<R>& rhs )
		{
			x += (T)rhs.x;
		}

		template<typename R>
		inline void Subtract( const Pixel1<R>& rhs )
		{
			x -= (T)rhs.x;
		}

		inline bool operator == ( const Pixel1& rhs ) const
			{ return x == rhs.x; }
		inline bool operator != ( const Pixel1& rhs ) const
			{ return x != rhs.x; }
		inline bool operator > ( const Pixel1& rhs ) const
			{ return x > rhs.x; }
		inline bool operator < ( const Pixel1& rhs ) const
			{ return x < rhs.x; }

	};

	template <typename T>
	struct Pixel2
	{
		typedef T TYPE;

		template<typename NewType>
		struct CastType { typedef Pixel2<NewType> P; };

		T x;
		T y;
		
		inline Pixel2()
			: x(0), y(0) {}

		inline Pixel2( const T& x, const T& y ) 
			: x(x), y(y) {}

		explicit inline Pixel2( const T& x )
			: x(x), y(x) {}

		inline Pixel2( const Pixel2& rhs )
			: x( rhs.x ), y( rhs.y ) {}

		explicit inline Pixel2( const Pixel& rhs )
			: x( (T)rhs[0] ), y( (T)rhs[1] ) {}

		inline Pixel ToPixel() const
			{ return Pixel((float)x, (float)y); }

		template <typename R>
		inline static Pixel2<T> Convert( const Pixel2<R>& rhs )
			{ return Pixel2<T>( (T)rhs.x, (T)rhs.y ); }

		template <typename R>
		inline static Pixel2<T> Convert( const Pixel1<R>& rhs )
			{ return Pixel2<T>( (T)rhs.x, (T)rhs.x ); }

		inline static PlainType::Type Type() { return _typeof(T()); }
		inline static int       Size() { return 2; }

		static const int _SIZE = 2;

		inline T*	Data() const	{ return (T*)this; }

		inline Pixel2 operator + ( const Pixel2& rhs ) const
			{ return Pixel2( x + rhs.x, y + rhs.y ); }
		inline Pixel2 operator - ( const Pixel2& rhs ) const
			{ return Pixel2( x - rhs.x, y - rhs.y ); }
		inline Pixel2 operator * ( const Pixel2& rhs ) const
			{ return Pixel2( x * rhs.x, y * rhs.y ); }
		inline Pixel2 operator / ( const Pixel2& rhs ) const
			{ return Pixel2( x / rhs.x, y / rhs.y ); }
		inline Pixel2 operator % ( const Pixel2& rhs ) const
			{ return Pixel2( x % rhs.x, y % rhs.y ); }
		inline Pixel2 operator - () const
			{ return Pixel2( -x, -y ); }

		inline Pixel2& operator = ( const Pixel2& rhs )
			{ x = rhs.x; y = rhs.y; return (*this); }
		inline Pixel2& operator += ( const Pixel2& rhs )
			{ x += rhs.x; y += rhs.y; return (*this); }
		inline Pixel2& operator -= ( const Pixel2& rhs )
			{ x -= rhs.x; y -= rhs.y; return (*this); }
		inline Pixel2& operator *= ( const Pixel2& rhs )
			{ x *= rhs.x; y *= rhs.y; return (*this); }
		inline Pixel2& operator /= ( const Pixel2& rhs )
			{ x /= rhs.x; y /= rhs.y; return (*this); }
		inline Pixel2& operator %= ( const Pixel2& rhs )
			{ x %= rhs.x; y %= rhs.y; return (*this); }

		inline Pixel2 operator + ( T rhs ) const
			{ return Pixel2( x + rhs, y + rhs ); }
		inline Pixel2 operator - ( T rhs ) const
			{ return Pixel2( x - rhs, y - rhs ); }
		inline Pixel2 operator * ( T rhs ) const
			{ return Pixel2( x * rhs, y * rhs ); }
		inline Pixel2 operator / ( T rhs ) const
			{ return Pixel2( x / rhs, y / rhs ); }
		inline Pixel2 operator % ( T rhs ) const
			{ return Pixel2( x % rhs, y % rhs ); }
		inline Pixel2 operator >> ( T rhs ) const
			{ return Pixel2( x >> rhs, y >> rhs ); }

		inline Pixel2& operator += ( T rhs )
			{ x += rhs; y += rhs; return (*this); }
		inline Pixel2& operator -= ( T rhs )
			{ x -= rhs; y -= rhs; return (*this); }
		inline Pixel2& operator *= ( T rhs )
			{ x *= rhs; y *= rhs; return (*this); }
		inline Pixel2& operator /= ( T rhs )
			{ x /= rhs; y /= rhs; return (*this); }
		inline Pixel2& operator %= ( T rhs )
			{ x %= rhs; y %= rhs; return (*this); }
		inline Pixel2& operator >>= ( T rhs )
			{ x >>= rhs; y >>= rhs; return (*this); }

		template<typename R>
		inline void AddWeighted( const Pixel2<R>& rhs, T weight )
		{
			x += (T)rhs.x * weight;
			y += (T)rhs.y * weight;
		}

		template<typename R>
		inline void Add( const Pixel2<R>& rhs )
		{
			x += (T)rhs.x;
			y += (T)rhs.y;
		}

		template<typename R>
		inline void Subtract( const Pixel2<R>& rhs )
		{
			x -= (T)rhs.x;
			y -= (T)rhs.y;
		}

		inline bool operator == ( const Pixel2& rhs ) const
			{ return x == rhs.x && y == rhs.y; }
		inline bool operator != ( const Pixel2& rhs ) const
			{ return x != rhs.x || y != rhs.y; }
		inline bool operator > ( const Pixel2& rhs ) const
			{ return x + y > rhs.x + rhs.y; }
		inline bool operator < ( const Pixel2& rhs ) const
			{ return x + y < rhs.x + rhs.y; }

	};

	template <typename T>
	struct Pixel3
	{
		typedef T TYPE;

		template<typename NewType>
		struct CastType { typedef Pixel3<NewType> P; };

		T x;
		T y;
		T z;

		inline Pixel3()
			: x(0), y(0), z(0) {}

		inline Pixel3( const T& x, const T& y, const T& z ) 
			: x(x), y(y), z(z) {}

		explicit inline Pixel3( const T& x )
			: x(x), y(x), z(x) {}

		inline Pixel3( const Pixel3<T>& rhs )
			: x( rhs.x ), y( rhs.y ), z( rhs.z ) {}

		explicit inline Pixel3( const Pixel& rhs )
			: x( (T)rhs[0] ), y( (T)rhs[1] ), z( (T)rhs[2] ) {}

		inline Pixel ToPixel() const
			{ return Pixel((float)x, (float)y, (float)z); }

		template <typename R>
		inline static Pixel3<T> Convert( const Pixel3<R>& rhs )
			{ return Pixel3<T>( (T)rhs.x, (T)rhs.y, (T)rhs.z ); }

		template <typename R>
		inline static Pixel3<T> Convert( const Pixel1<R>& rhs )
			{ return Pixel3<T>( (T)rhs.x, (T)rhs.x, (T)rhs.x ); }

		inline static PlainType::Type Type()	{ return _typeof(T()); }
		inline static int       Size()	{ return 3; }

		static const int _SIZE = 3;

		inline T*	Data() const	{ return (T*)this; }

		inline Pixel3 operator + ( const Pixel3& rhs ) const
			{ return Pixel3( x + rhs.x, y + rhs.y, z + rhs.z ); }
		inline Pixel3 operator - ( const Pixel3& rhs ) const
			{ return Pixel3( x - rhs.x, y - rhs.y, z - rhs.z ); }
		inline Pixel3 operator * ( const Pixel3& rhs ) const
			{ return Pixel3( x * rhs.x, y * rhs.y, z * rhs.z ); }
		inline Pixel3 operator / ( const Pixel3& rhs ) const
			{ return Pixel3( x / rhs.x, y / rhs.y, z / rhs.z ); }
		inline Pixel3 operator % ( const Pixel3& rhs ) const
			{ return Pixel3( x % rhs.x, y % rhs.y, z % rhs.z ); }
		inline Pixel3 operator - () const
			{ return Pixel3( -x, -y, -z ); }

		inline Pixel3& operator = ( const Pixel3& rhs )
			{ x = rhs.x; y = rhs.y; z = rhs.z; return (*this); }
		inline Pixel3& operator += ( const Pixel3& rhs )
			{ x += rhs.x; y += rhs.y; z += rhs.z; return (*this); }
		inline Pixel3& operator -= ( const Pixel3& rhs )
			{ x -= rhs.x; y -= rhs.y; z -= rhs.z; return (*this); }
		inline Pixel3& operator *= ( const Pixel3& rhs )
			{ x *= rhs.x; y *= rhs.y; z *= rhs.z; return (*this); }
		inline Pixel3& operator /= ( const Pixel3& rhs )
			{ x /= rhs.x; y /= rhs.y; z /= rhs.z; return (*this); }
		inline Pixel3& operator %= ( const Pixel3& rhs )
			{ x %= rhs.x; y %= rhs.y; z %= rhs.z; return (*this); }

		inline Pixel3 operator + ( T rhs ) const
			{ return Pixel3( x + rhs, y + rhs, z + rhs ); }
		inline Pixel3 operator - ( T rhs ) const
			{ return Pixel3( x - rhs, y - rhs, z - rhs ); }
		inline Pixel3 operator * ( T rhs ) const
			{ return Pixel3( x * rhs, y * rhs, z * rhs ); }
		inline Pixel3 operator / ( T rhs ) const
			{ return Pixel3( x / rhs, y / rhs, z / rhs ); }
		inline Pixel3 operator % ( T rhs ) const
			{ return Pixel3( x % rhs, y % rhs, z % rhs ); }
		inline Pixel3 operator >> ( T rhs ) const
			{ return Pixel3( x >> rhs, y >> rhs, z >> rhs ); }

		inline Pixel3& operator += ( T rhs )
			{ x += rhs; y += rhs; z += rhs; return (*this); }
		inline Pixel3& operator -= ( T rhs )
			{ x -= rhs; y -= rhs; z -= rhs; return (*this); }
		inline Pixel3& operator *= ( T rhs )
			{ x *= rhs; y *= rhs; z *= rhs; return (*this); }
		inline Pixel3& operator /= ( T rhs )
			{ x /= rhs; y /= rhs; z /= rhs; return (*this); }
		inline Pixel3& operator %= ( T rhs )
			{ x %= rhs; y %= rhs; z %= rhs; return (*this); }
		inline Pixel3& operator >>= ( T rhs )
			{ x >>= rhs; y >>= rhs; z >>= rhs; return (*this); }

		template<typename R>
		inline void AddWeighted( const Pixel3<R>& rhs, T weight )
		{
			x += (T)rhs.x * weight;
			y += (T)rhs.y * weight;
			z += (T)rhs.z * weight;
		}

		template<typename R>
		inline void Add( const Pixel3<R>& rhs )
		{
			x += (T)rhs.x;
			y += (T)rhs.y;
			z += (T)rhs.z;
		}

		template<typename R>
		inline void Subtract( const Pixel3<R>& rhs )
		{
			x -= (T)rhs.x;
			y -= (T)rhs.y;
			z -= (T)rhs.z;
		}

		inline bool operator == ( const Pixel3& rhs ) const
			{ return x == rhs.x && y == rhs.y && z == rhs.z; }
		inline bool operator != ( const Pixel3& rhs ) const
			{ return x != rhs.x || y != rhs.y || z != rhs.z; }
		inline bool operator > ( const Pixel3& rhs ) const
			{ return x + y + z > rhs.x + rhs.y + rhs.z; }
		inline bool operator < ( const Pixel3& rhs ) const
			{ return x + y + z < rhs.x + rhs.y + rhs.z; }

	};

	template <typename T>
	struct Pixel4
	{
		typedef T TYPE;

		template<typename NewType>
		struct CastType { typedef Pixel4<NewType> P; };

		T x;
		T y;
		T z;
		T w;

		inline Pixel4()
			: x(0), y(0), z(0), w(0) {}

		inline Pixel4( const T& x, const T& y, const T& z, const T& w ) 
			: x(x), y(y), z(z), w(w) {}

		explicit inline Pixel4( const T& x )
			: x(x), y(x), z(x), w(x) {}

		inline Pixel4( const Pixel4& rhs )
			: x( rhs.x ), y( rhs.y ), z( rhs.z ), w( rhs.w ) {}

		explicit inline Pixel4( const Pixel& rhs )
			: x( (T)rhs[0] ), y( (T)rhs[1] ), z( (T)rhs[2] ), w( (T)rhs[3] ) {}

		inline Pixel ToPixel() const
			{ return Pixel((float)x, (float)y, (float)z, (float)w); }

		template <typename R>
		inline static Pixel4<T> Convert( const Pixel4<R>& rhs )
			{ return Pixel4<T>( (T)rhs.x, (T)rhs.y, (T)rhs.z, (T)rhs.w ); }

		template <typename R>
		inline static Pixel4<T> Convert( const Pixel1<R>& rhs )
			{ return Pixel4<T>( (T)rhs.x, (T)rhs.x, (T)rhs.x, (T)rhs.x ); }

		inline static PlainType::Type Type()	{ return _typeof(T()); }
		inline static int       Size()	{ return 4; }

		static const int _SIZE = 4;

		inline T*	Data() const	{ return (T*)this; }

		inline Pixel4 operator + ( const Pixel4& rhs ) const
			{ return Pixel4( x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w ); }
		inline Pixel4 operator - ( const Pixel4& rhs ) const
			{ return Pixel4( x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w ); }
		inline Pixel4 operator * ( const Pixel4& rhs ) const
			{ return Pixel4( x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w ); }
		inline Pixel4 operator / ( const Pixel4& rhs ) const
			{ return Pixel4( x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w ); }
		inline Pixel4 operator % ( const Pixel4& rhs ) const
			{ return Pixel4( x % rhs.x, y % rhs.y, z % rhs.z, w % rhs.w ); }
		inline Pixel4 operator - () const
			{ return Pixel4( -x, -y, -z, -w ); }

		inline Pixel4& operator = ( const Pixel4& rhs )
			{ x = rhs.x; y = rhs.y; z = rhs.z; w = rhs.w; return (*this); }
		inline Pixel4& operator += ( const Pixel4& rhs )
			{ x += rhs.x; y += rhs.y; z += rhs.z; w += rhs.w; return (*this); }
		inline Pixel4& operator -= ( const Pixel4& rhs )
			{ x -= rhs.x; y -= rhs.y; z -= rhs.z; w -= rhs.w; return (*this); }
		inline Pixel4& operator *= ( const Pixel4& rhs )
			{ x *= rhs.x; y *= rhs.y; z *= rhs.z; w *= rhs.w; return (*this); }
		inline Pixel4& operator /= ( const Pixel4& rhs )
			{ x /= rhs.x; y /= rhs.y; z /= rhs.z; w /= rhs.w; return (*this); }
		inline Pixel4& operator %= ( const Pixel4& rhs )
			{ x %= rhs.x; y %= rhs.y; z %= rhs.z; w %= rhs.w; return (*this); }

		inline Pixel4 operator + ( T rhs ) const
			{ return Pixel4( x + rhs, y + rhs, z + rhs, w + rhs ); }
		inline Pixel4 operator - ( T rhs ) const
			{ return Pixel4( x - rhs, y - rhs, z - rhs, w - rhs ); }
		inline Pixel4 operator * ( T rhs ) const
			{ return Pixel4( x * rhs, y * rhs, z * rhs, w * rhs ); }
		inline Pixel4 operator / ( T rhs ) const
			{ return Pixel4( x / rhs, y / rhs, z / rhs, w / rhs ); }
		inline Pixel4 operator % ( T rhs ) const
			{ return Pixel4( x % rhs, y % rhs, z % rhs, w % rhs ); }
		inline Pixel4 operator >> ( T rhs ) const
			{ return Pixel4( x >> rhs, y >> rhs, z >> rhs, w >> rhs ); }

		inline Pixel4& operator += ( T rhs )
			{ x += rhs; y += rhs; z += rhs; w += rhs; return (*this); }
		inline Pixel4& operator -= ( T rhs )
			{ x -= rhs; y -= rhs; z -= rhs; w -= rhs; return (*this); }
		inline Pixel4& operator *= ( T rhs )
			{ x *= rhs; y *= rhs; z *= rhs; w *= rhs; return (*this); }
		inline Pixel4& operator /= ( T rhs )
			{ x /= rhs; y /= rhs; z /= rhs; w /= rhs; return (*this); }
		inline Pixel4& operator %= ( T rhs )
			{ x %= rhs; y %= rhs; z %= rhs; w %= rhs; return (*this); }
		inline Pixel4& operator >>= ( T rhs )
			{ x >>= rhs; y >>= rhs; z >>= rhs; w >>= rhs; return (*this); }

		template<typename R>
		inline void AddWeighted( const Pixel4<R>& rhs, T weight )
		{
			x += (T)rhs.x * weight;
			y += (T)rhs.y * weight;
			z += (T)rhs.z * weight;
			w += (T)rhs.w * weight;
		}

		template<typename R>
		inline void Add( const Pixel4<R>& rhs )
		{
			x += (T)rhs.x;
			y += (T)rhs.y;
			z += (T)rhs.z;
			w += (T)rhs.w;
		}

		template<typename R>
		inline void Subtract( const Pixel4<R>& rhs )
		{
			x -= (T)rhs.x;
			y -= (T)rhs.y;
			z -= (T)rhs.z;
			w -= (T)rhs.w;
		}

		inline bool operator == ( const Pixel4& rhs ) const
			{ return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w; }
		inline bool operator != ( const Pixel4& rhs ) const
			{ return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w; }
		inline bool operator > ( const Pixel4& rhs ) const
			{ return x + y + z + w > rhs.x + rhs.y + rhs.z + rhs.w; }
		inline bool operator < ( const Pixel4& rhs ) const
			{ return x + y + z + w < rhs.x + rhs.y + rhs.z + rhs.w; }

	};

	typedef Pixel1<atl::uint8>  Pixel1_u8;
	typedef Pixel1<atl::sint8>  Pixel1_i8;
	typedef Pixel1<atl::uint16> Pixel1_u16;
	typedef Pixel1<atl::sint16> Pixel1_i16;
	typedef Pixel1<atl::sint32> Pixel1_i32;
	typedef Pixel1<float>   Pixel1_r;

	typedef Pixel2<atl::uint8>  Pixel2_u8;
	typedef Pixel2<atl::sint8>  Pixel2_i8;
	typedef Pixel2<atl::uint16> Pixel2_u16;
	typedef Pixel2<atl::sint16> Pixel2_i16;
	typedef Pixel2<atl::sint32> Pixel2_i32;
	typedef Pixel2<float>   Pixel2_r;

	typedef Pixel3<atl::uint8>  Pixel3_u8;
	typedef Pixel3<atl::sint8>  Pixel3_i8;
	typedef Pixel3<atl::uint16> Pixel3_u16;
	typedef Pixel3<atl::sint16> Pixel3_i16;
	typedef Pixel3<atl::sint32> Pixel3_i32;
	typedef Pixel3<float>   Pixel3_r;

	typedef Pixel4<atl::uint8>  Pixel4_u8;
	typedef Pixel4<atl::sint8>  Pixel4_i8;
	typedef Pixel4<atl::uint16> Pixel4_u16;
	typedef Pixel4<atl::sint16> Pixel4_i16;
	typedef Pixel4<atl::sint32> Pixel4_i32;
	typedef Pixel4<float>   Pixel4_r;

	// ----------------------------------------------------------------------------

	template <typename T>
	struct PromotionTraits< Pixel1<T> >
	{
		typedef Pixel1< typename PromotionTraits<T>::Addable > Addable;
		typedef Pixel1< float > Floating;
	};

	template <typename T>
	struct PromotionTraits< Pixel2<T> >
	{
		typedef Pixel2< typename PromotionTraits<T>::Addable > Addable;
		typedef Pixel2< float > Floating;
	};

	template <typename T>
	struct PromotionTraits< Pixel3<T> >
	{
		typedef Pixel3< typename PromotionTraits<T>::Addable > Addable;
		typedef Pixel3< float > Floating;
	};

	template <typename T>
	struct PromotionTraits< Pixel4<T> >
	{
		typedef Pixel4< typename PromotionTraits<T>::Addable > Addable;
		typedef Pixel4< float > Floating;
	};

} // namespace avl

#endif
