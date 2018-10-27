//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_SURFACE_H
#define AVL_SURFACE_H

#include <climits>
#include "Image/PlainTypes.h"
#include "ATL/Blob.h"
#include "ATL/Error.h"
#include "ATL/AtlTypes.h"
#include "ATL/NumericRange.h"
#include "ATL/Optional.h"
#include "Basic/Types.h"
#include "Region/Region.h"

namespace avl
{

	class Surface
	{
	protected:
		int				width;
		int				height;
		int				pitch;
		PlainType::Type	type;
		int				pointByteSize;

		double			xOffset;
		double			xScale;
		double			yOffset;
		double			yScale;
		double			zOffset;
		double			zScale;

		atl::Blob		blob;

	public:
		Surface();

		Surface(int width_, int height_, PlainType::Type type_, atl::Optional<const avl::Region&> inRoi);

		Surface(int width_, int height_, int pitch_, PlainType::Type type_, void* data, atl::Optional<const avl::Region&> inRoi = atl::NIL);

		~Surface();

		// Deep data copy
		Surface(const Surface& rhs);

		Surface& operator = (const Surface& rhs);

#ifdef HAS_CPP0X

		Surface(Surface&& rhs);
		Surface& operator = (Surface&& rhs);

#endif

		bool operator == (const Surface& rhs) const;
		bool operator != (const Surface& rhs) const;

		/// Iff the format is different then recreates the Surface (point data will be own).
		/// Typically used for (re-)creating output Surface in Surface processing functions.
		void Reset(int newWidth, int newHeight, PlainType::Type newType, atl::Optional<const avl::Region&> inRoi);
		void Reset(const Surface& rhs, atl::Optional<const avl::Region&> inRoi);

		/// Turns the Surface into a wrapper of external data (point data will be NOT own)
		void Reset(int newWidth, int newHeight, int newPitch, PlainType::Type newType, void* data, atl::Optional<const avl::Region&> inRoi = atl::NIL);

		void SetX(double xOffset_, double xScale_);
		void SetY(double yOffset_, double yScale_);
		void SetZ(double zOffset_, double zScale_);
		void SetOffsets(double xOffset_, double yOffset_, double zOffset_);
		void SetScales(double xScale_, double yScale_, double zScale_);
		void SetOffsetAndScales(double xOffset_, double xScale_, double yOffset_, double yScale_, double zOffset_, double zScale_);

		int				Width() const			{ return width;  }
		int				Height() const			{ return height; }
		int				Pitch() const			{ return pitch;  }
		PlainType::Type Type() const			{ return type; }
		int				PointByteSize() const	{ return pointByteSize; }
		bool			Empty() const			{ return width == 0 || height == 0; }
		int				Area() const			{ return width * height; }
		Box				Frame() const			{ return Box(0, 0, width, height); }

		void*			Data()					{ return blob.Pointer(); }
		const void*		Data() const			{ return blob.Pointer(); }

		void*			Release();
		bool			IsDataOwn() const		{ return blob.Own(); }
		bool			MakeDataOwn();

		double			XOffset() const			{ return xOffset; }
		double			XScale() const			{ return xScale; }
		double			YOffset() const			{ return yOffset; }
		double			YScale() const			{ return yScale; }
		double			ZOffset() const			{ return zOffset; }
		double			ZScale() const			{ return zScale; }

		template <typename T>	double		X(T xIndex) const			{ return xOffset + xIndex * xScale;			}
		template <typename T>	double		Y(T yIndex) const			{ return yOffset + yIndex * yScale;			}	
		template <typename T>	double		Z(T value) const			{ return zOffset + value * zScale;			}
		template <typename T>	double		Z(int x, int y) const		{ return zOffset + Value<T>(x, y) * zScale; }
		template <typename T>	double		Z(const Location& l) const	{ return zOffset + Value<T>(l) * zScale;	}

		template <typename T>	T*			RowBegin(int y);
		template <typename T>	const T*	RowBegin(int y) const;
		template <typename T>	T*			RowEnd  (int y);
		template <typename T>	const T*	RowEnd  (int y) const;

		template <typename T>	T*			Ptr(int x, int y);
		template <typename T>	const T*	Ptr(int x, int y) const;
		template <typename T>	T*			Ptr(const Location& l);
		template <typename T>	const T*	Ptr(const Location& l) const;

		template <typename T>	T&			Value(int x, int y);
		template <typename T>	const T&	Value(int x, int y) const;
		template <typename T>	T&			Value(const Location& l);
		template <typename T>	const T&	Value(const Location& l) const;

		bool			HasLocation(int x, int y) const;
		bool			HasLocation(const Location& l) const;

		template <typename T>
		static CONSTEXPR T Infinity(void) NOEXCEPT;

		template <typename T>
		void Init(atl::Optional<const avl::Region&> inRoi, const T& value);

	private:
		void SetBasicOffsetAndScales();
		void InitWithZero(atl::Optional<const avl::Region&> inRoi);
	};

	// Inline implementations

	template <typename T>
	inline T* Surface::RowBegin( int y )
	{
		return (T*)( (atl::uint8*)blob.Pointer() + y * pitch );
	}

	template <typename T>
	inline const T* Surface::RowBegin( int y ) const
	{
		return (T*)( (atl::uint8*)blob.Pointer() + y * pitch );
	}

	template <typename T>
	inline T* Surface::RowEnd( int y )
	{
		return (T*)( (atl::uint8*)blob.Pointer() + y * pitch + pointByteSize * width );
	}

	template <typename T>
	inline const T* Surface::RowEnd( int y ) const
	{
		return (T*)( (atl::uint8*)blob.Pointer() + y * pitch + pointByteSize * width );
	}

	template <typename T>
	inline T* Surface::Ptr( int x, int y )
	{
		return (T*)( (atl::uint8*)blob.Pointer() + y * pitch + x * pointByteSize );
	}

	template <typename T>
	inline const T* Surface::Ptr( int x, int y ) const
	{
		return (T*)( (atl::uint8*)blob.Pointer() + y * pitch + x * pointByteSize );
	}

	template <typename T>
	inline T* Surface::Ptr( const Location& l )
	{
		return (T*)( (atl::uint8*)blob.Pointer() + l.y * pitch + l.x * pointByteSize );
	}

	template <typename T>
	inline const T* Surface::Ptr( const Location& l ) const
	{
		return (T*)( (atl::uint8*)blob.Pointer() + l.y * pitch + l.x * pointByteSize );
	}

	template <typename T>
	inline T& Surface::Value( int x, int y )
	{
		return *Ptr<T>( x, y );
	}

	template <typename T>
	inline const T& Surface::Value( int x, int y ) const
	{
		return *Ptr<T>( x, y );
	}

	template <typename T>
	inline T& Surface::Value( const Location& l )
	{
		return *Ptr<T>( l.x, l.y );
	}

	template <typename T>
	inline const T& Surface::Value( const Location& l ) const
	{
		return *Ptr<T>( l.x, l.y );
	}

	inline
	bool Surface::HasLocation( int x, int y ) const
	{
		return (0 <= x && x < Width()) && (0 <= y && y < Height());
	}

	inline
	bool Surface::HasLocation( const Location& l ) const
	{
		return HasLocation( l.x, l.y );
	}

	inline
	Surface::Surface()
		: width(0)
		, height(0)
		, pitch(0)
		, type(PlainType::Int8)
		, pointByteSize(1)
	{
		SetBasicOffsetAndScales();
	}

	inline
	Surface::Surface( int width_, int height_, PlainType::Type type_, atl::Optional<const avl::Region&> inRoi )
		: width(0)
		, height(0)
	{
		Reset( width_, height_, type_, inRoi );
		SetBasicOffsetAndScales();
	}

	inline
	Surface::Surface( int width_, int height_, int pitch_, PlainType::Type type_, void* data, atl::Optional<const avl::Region&> inRoi )
		: width(0)
		, height(0)
	{
		Reset( width_, height_, pitch_, type_, data, inRoi );
	}

	inline
	Surface::~Surface()
	{
	}

	inline
	Surface::Surface( const Surface& rhs )
		: width(0)
		, height(0)
		, pitch(0)
		, type(PlainType::Int8)
		, pointByteSize(1)
	{
		operator=( rhs );
	}

	inline
	Surface& Surface::operator=(const Surface& rhs)
	{
		if (this != &rhs)
		{
			// Create a deep copy
			Reset( rhs.width, rhs.height, rhs.type, atl::NIL );

			if (pitch == rhs.pitch)
			{
				std::memcpy( (atl::byte*)blob.Pointer(), (const atl::byte*)rhs.blob.Pointer(), pitch * height );
			}
			else
			{
				const int minPitch = (pitch < rhs.pitch) ? pitch : rhs.pitch;
				for (int i = 0; i < height; ++i)
				{
					std::memcpy( (atl::byte*)blob.Pointer() + i * pitch, (const atl::byte*)rhs.blob.Pointer() + i * rhs.pitch, minPitch );
				}
			}

			SetOffsetAndScales( rhs.xOffset, rhs.xScale, rhs.yOffset, rhs.yScale, rhs.zOffset, rhs.zScale );
		}

		return (*this);
	}

#ifdef HAS_CPP0X

	inline
	Surface::Surface( Surface&& rhs )
	{
		operator=( std::move(rhs) );
	}

	inline
	Surface& Surface::operator=( Surface&& rhs )
	{
		if (this != &rhs)
		{
			if (rhs.blob.Own() == false)
			{
				// Data not own by source Surface - operator = is expected to create a copy with own Surface data
				operator=( static_cast<const Surface&>(rhs) );
			}
			else
			{
				// Data own by r-value Surface - steal it
				width = rhs.width;
				height = rhs.height;
				pitch = rhs.pitch;
				type = rhs.type;
				blob = std::move(rhs.blob);
				pointByteSize = rhs.pointByteSize;
				SetOffsetAndScales( rhs.xOffset, rhs.xScale, rhs.yOffset, rhs.yScale, rhs.zOffset, rhs.zScale );

				rhs.Reset( 0, 0, 0, PlainType::Int8, (void*)0);
				rhs.SetBasicOffsetAndScales();
			}
		}

		return (*this);
	}

#endif

	inline
	bool Surface::operator == ( const Surface& rhs ) const
	{
		if (this != &rhs)
		{
			if (width != rhs.width || height != rhs.height || type != rhs.type)
			{
				return false;
			}
			if (xOffset != rhs.xOffset || xScale != rhs.xScale ||
				yOffset != rhs.yOffset || yScale != rhs.yScale ||
				zOffset != rhs.zOffset || zScale != rhs.zScale)
			{
				return false;
			}

			for (int i = 0; i < height; ++i)
			{
				const void* p = RowBegin<void>(i);
				const void* rhsP = rhs.RowBegin<void>(i);

				if (0 != std::memcmp( p, rhsP, width * pointByteSize))
				{
					return false;
				}
			}
		}

		return true;
	}

	inline
	bool Surface::operator != ( const Surface& rhs ) const
	{
		return !(operator==(rhs));
	}

	inline
	void Surface::Reset( int newWidth, int newHeight, PlainType::Type newType, atl::Optional<const avl::Region&> inRoi )
	{
		if (this->blob.Own() == false ||
			this->Width() != newWidth ||
			this->Height() != newHeight ||
			this->Type() != newType)
		{
			// memory is not compliant

			if (newWidth < 0 || newHeight < 0)
				throw atl::DomainError("Negative value of Surface dimension in Surface::Reset().");

			if (newWidth == 0 || newHeight == 0)
			{
				// Prevents dimensions like (0, 492)
				newWidth = 0;
				newHeight = 0;
			}

			const int typeSize = _sizeof(newType);

			if (typeSize <= 0)
				throw atl::DomainError("Invalid pixel type in Surface::Reset().");

			if ((INT_MAX - 16) / typeSize < newWidth)
				throw atl::RuntimeError( "Surface dimensions too big in Surface::Reset()." );

			const int newPitch = (typeSize * newWidth + 15) / 16 * 16;	// round up to 16B / 128b

			if (newPitch > 0 && INT_MAX / newPitch < newHeight)
				throw atl::RuntimeError( "Surface dimensions too big in Surface::Reset()." );

			this->width			= newWidth;
			this->height		= newHeight;
			this->pitch			= newPitch;
			this->type			= newType;
			this->pointByteSize	= typeSize;

			try
			{
				const int size = newPitch * newHeight;
				blob.Reset(size);
			}
			catch (const atl::Error&)
			{
				throw atl::OutOfMemoryError("Allocation error - surface dimensions too big in Surface::Reset().");
			}
		}

		InitWithZero( inRoi );
	}

	inline
	void Surface::Reset( const Surface& rhs, atl::Optional<const avl::Region&> inRoi )
	{
		if (this != &rhs)
		{
			Reset( rhs.Width(), rhs.Height(), rhs.Type(), inRoi );
		}
	}

	inline
	void Surface::Reset( int newWidth, int newHeight, int newPitch, PlainType::Type newType, void* data, atl::Optional<const avl::Region&> inRoi )
	{
		if (newWidth < 0 || newHeight < 0 || newPitch < 0)
			throw atl::DomainError("Negative value of Surface dimension in Surface::Reset().");

		if (newWidth == 0 || newHeight == 0)
		{
			// Prevents dimensions like (0, 492)
			newWidth = 0;
			newHeight = 0;
			newPitch = 0;
		}

		if (newPitch > 0 && INT_MAX / newPitch < newHeight)
			throw atl::RuntimeError("Surface dimensions too big in Surface::Reset().");

		this->width			= newWidth;
		this->height		= newHeight;
		this->pitch			= newPitch;
		this->type			= newType;
		this->blob.Reset( newPitch * newHeight, data );
		this->pointByteSize	= _sizeof(newType);

		InitWithZero(inRoi);
	}

	inline
	void Surface::SetX(double xOffset_, double xScale_)
	{
		if (xScale_ < 0.0)
		{
			throw atl::DomainError("Negative X scale in Surface.");
		}

		xOffset = xOffset_;
		xScale = xScale_;
	}

	inline
	void Surface::SetY(double yOffset_, double yScale_)
	{
		if (yScale_ < 0.0)
		{
			throw atl::DomainError("Negative Y scale in Surface.");
		}

		yOffset = yOffset_;
		yScale = yScale_;
	}

	inline
	void Surface::SetZ(double zOffset_, double zScale_)
	{
		if (zScale_ < 0.0)
		{
			throw atl::DomainError("Negative Z scale in Surface.");
		}

		zOffset = zOffset_;
		zScale = zScale_;
	}

	inline
	void Surface::SetOffsets(double xOffset_, double yOffset_, double zOffset_)
	{
		xOffset = xOffset_;
		yOffset = yOffset_;
		zOffset = zOffset_;
	}

	inline
	void Surface::SetScales(double xScale_, double yScale_, double zScale_)
	{
		if (xScale_ < 0.0 || yScale_ < 0.0 || zScale_ < 0.0)
		{
			throw atl::DomainError("Negative scale in Surface.");
		}

		xScale = xScale_;
		yScale = yScale_;
		zScale = zScale_;
	}

	inline
	void Surface::SetOffsetAndScales(double xOffset_, double xScale_, double yOffset_, double yScale_, double zOffset_, double zScale_)
	{
		SetX( xOffset_, xScale_ );
		SetY( yOffset_, yScale_ );
		SetZ( zOffset_, zScale_ );
	}

	inline
	void* Surface::Release()
	{
		void* data = blob.Release();
		if (data)
		{
			this->width = 0;
			this->height = 0;
		}
		return data;
	}

	inline
	bool Surface::MakeDataOwn()
	{
		if (blob.Own() == false && Data() != 0)
		{
			const atl::uint8*	oldData  = (atl::uint8*)Data();
			const int			oldPitch = pitch;

			Reset( width, height, type, atl::NIL );

			if (pitch == oldPitch)
			{
				std::memcpy( (atl::byte*)blob.Pointer(), oldData, pitch * height );
			}
			else
			{
				for (int i = 0; i < height; ++i)
				{
					std::memcpy( RowBegin<atl::uint8>(i), oldData + oldPitch * i, width * pointByteSize );
				}
			}

			return true;
		}

		return false;
	}

	inline
	void Surface::SetBasicOffsetAndScales()
	{
		xOffset = 0.0f;
		xScale = 1.0f;
		yOffset = 0.0f;
		yScale = 1.0f;
		zOffset = 0.0f;
		zScale = 1.0f;
	}

	inline
	void Surface::InitWithZero(atl::Optional<const avl::Region&> inRoi)
	{
		if (inRoi != atl::NIL)
		{
			const Region& region = inRoi.Get();
			Location loc(0, 0);
			for (int i = 0; i < region.Size(); ++i)
			{
				atl::uint8* p1 = this->Ptr<atl::uint8>( loc );
				atl::uint8* p2 = this->Ptr<atl::uint8>( region.Begin(i) );
				std::memset(p1, 0, p2 - p1);
				loc = region.End(i);
			}
			{
				// between the last point-run and the end of the Surface
				atl::uint8* p1 = this->Ptr<atl::uint8>( loc );
				atl::uint8* p2 = this->Ptr<atl::uint8>( width, height - 1 );
				std::memset(p1, 0, p2 - p1);
			}
		}
	}

	template <typename T>
	inline CONSTEXPR T SurfaceInfinityValue() NOEXCEPT
	{
		return atl::NumericRange<T>::Max();
	}
	template <>
	inline CONSTEXPR atl::sint8 SurfaceInfinityValue<atl::sint8>() NOEXCEPT
	{
		return atl::NumericRange<atl::sint8>::Min();
	}
	template <>
	inline CONSTEXPR atl::sint16 SurfaceInfinityValue<atl::sint16>() NOEXCEPT
	{
		return atl::NumericRange<atl::sint16>::Min();
	}
	template <>
	inline CONSTEXPR atl::sint32 SurfaceInfinityValue<atl::sint32>() NOEXCEPT
	{
		return atl::NumericRange<atl::sint32>::Min();
	}
	template <>
	inline CONSTEXPR float SurfaceInfinityValue<float>() NOEXCEPT
	{
		return atl::NumericRange<float>::Min();
	}
	template <>
	inline CONSTEXPR double SurfaceInfinityValue<double>() NOEXCEPT
	{
		return atl::NumericRange<double>::Min();
	}

	template <typename T>
	inline CONSTEXPR T Surface::Infinity(void) NOEXCEPT
	{
		return SurfaceInfinityValue<T>();
	}

	template <typename T>
	inline void Surface::Init(atl::Optional<const avl::Region&> inRoi, const T& value)
	{
		if (inRoi == atl::NIL)
		{
			for (int y = 0; y < height; ++y)
			{
				T* p = RowBegin<T>(y);
				const T* const e = RowEnd<T>(y);
				while (p < e)
				{
					*p++ = value;
				}
			}
		}
		else
		{
			const Region& roi = inRoi.Get();
			for (int i = 0; i < roi.Size(); ++i)
			{
				T* p = Ptr<T>( roi[i].Begin() );
				const T* const e = p + roi[i].Length();
				while (p < e)
				{
					*p++ = value;
				}
			}
		}
	}

}

#endif
