//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVLImage_H
#define AVLImage_H

#include "Image/PlainTypes.h"
#include "Basic/Types.h"
#include "ATL/Utils.h"
#include "ATL/Optional.h"
#include "ATL/Error.h"
#include "ATL/Blob.h"
#include "ATL/AtlTypes.h"
#include "Region/Region.h"

#include <cstring>
#include <climits>

#include <assert.h>


namespace avl
{
	struct PixelFormat
	{
		PixelFormat(PlainType::Type type, int depth)
			: type(type), depth(depth)
		{}
		avl::PlainType::Type	type;
		int						depth;

		bool operator==(const PixelFormat& rhs) const
		{
			return type == rhs.type && depth == rhs.depth;
		}

		bool operator!=(const PixelFormat& rhs) const
		{
			return type != rhs.type || depth != rhs.depth;
		}
	};

	typedef void* (*FAlloc)(std::size_t size);
	typedef void  (*FFree)(void* ptr, std::size_t size);

	inline
	FAlloc& GetPoolAllocFuncPtr()
	{
		static FAlloc f = NULL;
		return f;
	}

	inline
	FFree& GetPoolFreeFuncPtr()
	{
		static FFree f = NULL;
		return f;
	}

	const atl::uint32 IMAGE_DIRTY_BACKGROUND = 0x01;
	const atl::uint32 IMAGE_MEMORY_POOLING = 0x02;
	const atl::uint32 IMAGE_NO_MEMORY_REDUCTION = 0x04;

	/*
	*	Universal (portable) image type with explicit run-time information
	*	about its format. Designed for optimum balance between simplicity
	*	and genericity.
	*	Supports monochromatic and multichannel images based on one
	*	of the 6 plain data types (UINT8, SINT8, UINT16, SINT16, SINT32, REAL).
	*	Image performs automatic memory management.
	*/
	class Image
	{
	protected:
		int				width;			// number of pixel columns
		int				height;			// number of pixel rows
		int				pitch;			// byte-distance between consecutive rows
		PlainType::Type	type;			// type of channels
		int				depth;			// number of channels
		atl::Blob		blob;			// the pixel data
		int				pixelSize;		// byte-size of a pixel (computed from 'type' and 'depth')

	private:
		atl::uint32		flags;			// object-specific optimization flags

	protected:
		// Constructor used by generic constructors to set the format only
		Image( PlainType::Type type, int depth );

	private:
		void Init( atl::Optional<const avl::Region&> inRoi );

	public:
		// Constructor used for images, which will be created later, e.g. by 'LoadImage' function
		Image();

		// Constructor used for creating new images. Parameter inRoi defines which pixels should not be set
		// with zero values. If value atl::NIL is provided all image pixels will not set.
		Image( int width, int height, PlainType::Type type, int depth, atl::Optional<const avl::Region&> inRoi );

		// Constructor used for creating wrappers on existing data.
		Image( int width, int height, int pitch, PlainType::Type type, int depth, void* data, atl::Optional<const avl::Region&> inRoi = atl::NIL );

		// Copying constructor. Performs deep data copy.
		Image( const Image& rhs );

		~Image();

		// Performs deep data copy.
		avl::Image& operator = ( const Image& rhs );

#ifdef HAS_CPP0X

		Image( Image&& rhs );
		avl::Image& operator = ( Image&& rhs );

#endif

		bool operator == ( const Image& rhs ) const;
		bool operator != ( const Image& rhs ) const;


		// If the format is different then recreates the image (pixel data will be own).
		// Typically used for (re-)creating output images in image processing functions.
		void		Reset( int width, int height, PlainType::Type type, int depth, atl::Optional<const avl::Region&> inRoi );
		void		Reset( const Image& rhs, atl::Optional<const avl::Region&> inRoi );

		// Turns the image into a wrapper of external data (pixel data will be NOT own).
		void		Reset( int width, int height, int pitch, PlainType::Type type, int depth, void* data, atl::Optional<const avl::Region&> inRoi = atl::NIL );

		inline int			Width () const		{ return width;  }
		inline int			Height() const		{ return height; }
		inline avl::Size	Size() const		{ return avl::Size(width, height); }
		inline bool			Empty () const		{ return width == 0 || height == 0; }
		inline int			Pitch () const		{ return pitch;  }
		inline int			Area  () const		{ return width * height; }
		inline Box			Frame() const		{ return Box( 0, 0, width, height ); }

		// Number of channels (standard RGB images have 3).
		inline int			Depth() const 		{ return depth; }

		// Type of channels (standard RGB images have UINT8).
		inline PlainType::Type	Type()  const	{ return type; } 

		inline PixelFormat	Format() const		{ return PixelFormat( type, depth ); }

		// Size of pixels in bytes.
		inline int			PixelSize() const	{ return pixelSize; }

		// Direct access to pixel data
		void*		Data();
		const void* Data() const;

		// Returns pointer to pixels memory which since that point will
		// be owned externally (this image will not delete it in the destructor).
		void*		Release();

		bool		IsDataOwn() const			{ return blob.Own(); }
		bool		MakeDataOwn();

		// Direct access to pixel data
		template <typename P>	P*			RowBegin( int i );
		template <typename P>	const P*	RowBegin( int i ) const;
		template <typename P>	P*			RowEnd  ( int i );
		template <typename P>	const P*	RowEnd  ( int i ) const;

		template <typename P>	P*			Ptr( int x, int y );
		template <typename P>	const P*	Ptr( int x, int y ) const;
		template <typename P>	P*			Ptr( const Location& p );
		template <typename P>	const P*	Ptr( const Location& p ) const;

		template <typename P>	P&			Value( int x, int y );
		template <typename P>	const P&	Value( int x, int y ) const;
		template <typename P>	P&			Value( const Location& p );
		template <typename P>	const P&	Value( const Location& p ) const;


		// Helper method for range checking
		bool		HasLocation( int x, int y ) const;
		bool		HasLocation( Location p ) const;
		bool		HasPoint( float x, float y ) const;

		int			PtrToX( const void* ptr ) const;
		int			PtrToY( const void* ptr ) const;

		//FIXME: rename SetFlags to AddFlags, as it adds flags really, you cannot remove a flag once it has been set
		void		SetFlags(atl::uint32 flags);
		atl::uint32	GetFlags() const;
	};

	// --- Inline implementations ------------------------------------------------------

	template <typename P>
	inline
	P* Image::Ptr( int x, int y )
	{
		return (P*)( (atl::uint8*)blob.Pointer() + y * pitch + x * pixelSize );
	}

	template <typename P>
	inline
	const P* Image::Ptr( int x, int y ) const
	{
		return (P*)( (atl::uint8*)blob.Pointer() + y * pitch + x * pixelSize );
	}

	template <typename P>
	inline
	P* Image::Ptr( const Location& p )
	{
		return (P*)( (atl::uint8*)blob.Pointer() + p.y * pitch + p.x * pixelSize );
	}

	template <typename P>
	inline
	const P* Image::Ptr( const Location& p ) const
	{
		return (P*)( (atl::uint8*)blob.Pointer() + p.y * pitch + p.x * pixelSize );
	}

	template <typename P>
	inline
	P& Image::Value( int x, int y )
	{
		return *Ptr<P>( x, y );
	}

	template <typename P>
	inline
	const P& Image::Value( int x, int y ) const
	{
		return *Ptr<P>( x, y );
	}

	template <typename P>
	inline
	P& Image::Value( const Location& p )
	{
		return *Ptr<P>( p.x, p.y );
	}

	template <typename P>
	inline
	const P& Image::Value( const Location& p ) const
	{
		return *Ptr<P>( p.x, p.y );
	}

	inline
	bool Image::HasLocation( int x, int y ) const
	{
		return ( 0 <= x && x < Width() ) && ( 0 <= y && y < Height() );
	}

	inline
	bool Image::HasLocation( Location p ) const
	{
		return HasLocation(p.x, p.y);
	}

	inline
	bool Image::HasPoint( float x, float y ) const
	{
		return ( 0.0f <= x && x < (float)Width() ) && ( 0.0f <= y && y < (float)Height() );
	}

	inline
	Image::Image()
		: width(0)
		, height(0)
		, pitch(0)
		, type( PlainType::Int8 )
		, depth(1)
		, pixelSize(1)
		, flags(0)
	{
	}

	inline
	Image::Image( PlainType::Type type, int depth )
		: width(0)
		, height(0)
		, pitch(0)
		, type( PlainType::Int8 )
		, depth(1)
		, pixelSize(1)
		, flags(0)
	{
		Reset( 0, 0, type, depth, atl::NIL );
	}

	inline
	Image::Image( int width, int height, PlainType::Type type, int depth, atl::Optional<const avl::Region&> inRoi )
		: width(0)
		, height(0)
		, pitch(0)
		, type( PlainType::Int8 )
		, depth(1)
		, pixelSize(1)
		, flags(0)
	{
		Reset( width, height, type, depth, inRoi );
	}

	inline
	Image::Image( int width, int height, int pitch, PlainType::Type type, int depth, void* data, atl::Optional<const avl::Region&> inRoi )
		: flags(0)
	{
		Reset( width, height, pitch, type, depth, data, inRoi );
	}

	inline
	Image::~Image()
	{
		if ((flags & IMAGE_MEMORY_POOLING) != 0)
		{
			assert(blob.Handle() == NULL/*, "Non-null handle detected in a pooled image."*/);

			FFree& fFree = GetPoolFreeFuncPtr();

			assert(fFree != NULL/*, "Cannot use image memory pooling because PoolFree function is NULL."*/);

			fFree(blob.Pointer(), blob.Size());
			blob.Reset(0, 0);

		}
	}

	inline
	Image::Image( const Image& rhs )
		: width		( 0	)
		, height	( 0	)
		, pitch		( 0 )
		, type		( PlainType::Int8 )
		, depth		( 1	)
		, pixelSize	( 1	)
		, flags		( 0 )
	{
		operator=(rhs);
	}

	inline Image& Image::operator=(const Image& rhs)
	{
		if (this != &rhs)
		{
			// Create a deep copy
			Reset( rhs.width, rhs.height, rhs.type, rhs.depth, atl::NIL );

			if( pitch == rhs.pitch )
			{
				std::memcpy((atl::byte*)blob.Pointer(), (const atl::byte*)rhs.blob.Pointer(), pitch * height);
			}
			else
			{
				int minPitch = ( pitch < rhs.pitch ) ? pitch : rhs.pitch;
				for (int i = 0; i < height; ++i)
				{
					std::memcpy((atl::byte*)blob.Pointer() + i * pitch, (const atl::byte*)rhs.blob.Pointer() + i * rhs.pitch, minPitch);
				}
			}

			// do not copy flags as they are object-specific
		}

		return (*this);
	}

#ifdef HAS_CPP0X

	inline Image::Image( Image&& rhs )
		: flags(0)
	{
		operator=(std::move(rhs));
	}

	inline Image& Image::operator=( Image&& rhs )
	{
		if (this == &rhs)
			return *this;

		bool lhsIsPooled = (this->flags & IMAGE_MEMORY_POOLING) != 0;
		bool rhsIsPooled = (rhs.flags   & IMAGE_MEMORY_POOLING) != 0;
		if ((lhsIsPooled == true && rhsIsPooled == false) ||
			(lhsIsPooled == false && rhsIsPooled == true))
		{
			// Move semantics is not possible, when copying PooledImage -> Image or Image -> PooledImage
			operator=( static_cast<const Image&>(rhs) );
		}
		else if (rhs.blob.Own() == false)
		{
			// Data not own by source image - operator = is expected to create a copy with own image data
			operator=( static_cast<const Image&>(rhs) );
		}
		else if (rhs.blob.Own())
		{
			// Data own by r-value image - steal it
			width = rhs.width;
			height = rhs.height;
			pitch = rhs.pitch;
			type = rhs.type;
			depth = rhs.depth;
			blob = std::move(rhs.blob);
			pixelSize = rhs.pixelSize;

			rhs.Reset(0, 0, 0, PlainType::Int8, 0, (void*)0);

			// do not copy flags as they are object-specific
		}

		return (*this);
	}

#endif

	inline
	bool Image::operator == ( const Image& rhs ) const
	{
		if (this == &rhs)
			return true;

		if (width != rhs.width || height != rhs.height || type != rhs.type || depth != rhs.depth)
			return false;

		for( int i = 0; i < height; ++i )
		{
			const void* t = RowBegin<void>(i);
			const void* r = rhs.RowBegin<void>(i);

			if (0 != std::memcmp(t, r, width * pixelSize))
				return false;
		}

		return true;
	}

	inline
	bool Image::operator != ( const Image& rhs ) const
	{
		return !(operator==(rhs));
	}

	inline
	void Image::Reset( int newWidth, int newHeight, PlainType::Type newType, int newDepth, atl::Optional<const avl::Region&> inRoi )
	{
		if ( this->blob.Own() == false  ||
			 this->Width()    != newWidth  ||
			 this->Height()   != newHeight ||
			 this->Type()     != newType   ||
			 this->Depth()    != newDepth )
		{
			// a) memory is not compliant

			if (newWidth < 0 || newHeight < 0)
				throw atl::DomainError("Negative value of image dimension in Image::Reset().");

			if (newDepth < 1 || newDepth > 4)
				throw atl::DomainError("Invalid value of image depth in Image::Reset().");

			if (newWidth == 0 || newHeight == 0)
			{
				// Prevents dimensions like (0, 492)
				newWidth = 0;
				newHeight = 0;
			}

			const int typeSize = _sizeof(newType);

			if (typeSize <= 0)
				throw atl::DomainError("Invalid pixel type in Image::Reset().");

			if ((INT_MAX - 16) / newDepth / typeSize < newWidth)
				throw atl::RuntimeError( "Image dimensions too big in Image::Reset()." );

			int newPitch = (newDepth * typeSize * newWidth + 15) / 16 * 16;	// round up to 16B / 128b

			if (newPitch > 0 && INT_MAX / newPitch < newHeight)
				throw atl::RuntimeError( "Image dimensions too big in Image::Reset()." );

			this->width			= newWidth;
			this->height		= newHeight;
			this->pitch			= newPitch;
			this->type			= newType;
			this->depth			= newDepth;
			this->pixelSize		= newDepth * typeSize;

			try
			{
				int size = newPitch * newHeight;
				if ((flags & IMAGE_MEMORY_POOLING) != 0)
				{
					FAlloc& fAlloc = GetPoolAllocFuncPtr();
					FFree&  fFree  = GetPoolFreeFuncPtr();
					if (fAlloc == NULL || fFree == NULL)
					{
						throw atl::RuntimeError("Cannot use image memory pooling because pool allocation functions are NULL.");
					}
					else
					{
						fFree(blob.Pointer(), blob.Size());
						void* buf = fAlloc(size);
						blob.Reset(size, buf);
					}
				}
				else
				{
					blob.Reset(size);
				}
			}
			catch ( const atl::Error& )
			{
				throw atl::OutOfMemoryError("Allocation error - image dimensions too big in Image::Reset().");
			}
		}

		Init( inRoi );
	}

	inline
	void Image::Reset( const Image& rhs, atl::Optional<const avl::Region&> inRoi )
	{
		if (this == &rhs)
			return;

		Reset( rhs.Width(), rhs.Height(), rhs.Type(), rhs.Depth(), inRoi );
	}

	inline
	void Image::Reset( int newWidth, int newHeight, int newPitch, PlainType::Type newType, int newDepth, void* data, atl::Optional<const avl::Region&> inRoi )
	{
		if (newWidth < 0 || newHeight < 0 || newPitch < 0)
			throw atl::DomainError("Negative value of image dimension in Image::Reset().");

		if (newWidth == 0 || newHeight == 0)
		{
			// Prevents dimensions like (0, 492)
			newWidth = 0;
			newHeight = 0;
			newPitch = 0;
		}

		if (newPitch > 0 && INT_MAX / newPitch < newHeight)
			throw atl::RuntimeError("Image dimensions too big in Image::Reset().");

		if ((flags & IMAGE_MEMORY_POOLING) != 0)
		{
			throw atl::RuntimeError("Cannot set external data to an image with pooled memory.");
		}

		this->width		= newWidth;
		this->height	= newHeight;
		this->pitch		= newPitch;
		this->type		= newType;
		this->depth		= newDepth;
		this->blob.Reset( newPitch * newHeight, data );
		this->pixelSize	= newDepth * _sizeof(newType);

		Init(inRoi);
	}

	inline
	void Image::Init( atl::Optional<const avl::Region&> inRoi )
	{
		// Initialize pixels that will NOT be set
		if (inRoi != atl::NIL && (flags & IMAGE_DIRTY_BACKGROUND) == 0)
		{
			// Note: this is similar to RegionComplement
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
				// between the last point-run and the end of the image
				atl::uint8* p1 = this->Ptr<atl::uint8>( loc );
				atl::uint8* p2 = this->Ptr<atl::uint8>( width, height - 1 );
				std::memset(p1, 0, p2 - p1);
			}
		}
	}

	inline
	void* Image::Release()
	{
		void* data = blob.Release();
		if ( data )
		{
			this->width = 0;
			this->height = 0;
		}
		return data;
	}

	inline bool Image::MakeDataOwn()
	{
		if( blob.Own() == false && Data() != 0 )
		{
			const atl::uint8*	oldData  = (atl::uint8*)Data();
			const int			oldPitch = pitch;

			Reset( width, height, type, depth, atl::NIL );

			if( pitch == oldPitch )
			{
				std::memcpy( (atl::byte*)blob.Pointer(), oldData, pitch * height );
			}
			else
			{
				for(int i = 0; i < height; ++i)
				{
					memcpy( Ptr<atl::uint8>(0, i), oldData + oldPitch * i, width * pixelSize );
				}
			}

			return true;
		}

		return false;
	}

	inline void*       Image::Data()				{ return blob.Pointer(); }
	inline const void* Image::Data() const			{ return blob.Pointer(); }

	template <typename P>
	inline P* Image::RowBegin( int i )
	{
		return (P*)( (atl::uint8*)blob.Pointer() + i * pitch );
	}

	template <typename P>
	inline const P* Image::RowBegin( int i ) const
	{
		return (P*)( (atl::uint8*)blob.Pointer() + i * pitch );
	}

	template <typename P>
	inline P*       Image::RowEnd( int i )
	{
		return (P*)( (atl::uint8*)blob.Pointer() + i * pitch + PixelSize() * width );
	}

	template <typename P>
	inline const P* Image::RowEnd( int i ) const
	{
		return (P*)( (atl::uint8*)blob.Pointer() + i * pitch + PixelSize() * width );
	}

	inline
	int Image::PtrToX( const void* ptr ) const
	{
		return ( ( (const atl::uint8*)ptr - (const atl::uint8*)blob.Pointer() ) % pitch ) / pixelSize ;
	}

	inline
	int	Image::PtrToY( const void* ptr ) const
	{
		return (int)( ( (const atl::uint8*)ptr - (const atl::uint8*)blob.Pointer() ) / pitch );
	}

	// ---------------------------------------------------------------------------------

	inline
	void Image::SetFlags(atl::uint32 newFlags)
	{
		if ((newFlags & IMAGE_MEMORY_POOLING) != (flags & IMAGE_MEMORY_POOLING))	// change of IMAGE_MEMORY_POOLING
		{
			if (blob.Pointer() != NULL)
			{
				throw atl::RuntimeError("Cannot change IMAGE_MEMORY_POOLING flag while memory has already been allocated.");
			}
		}
		flags |= newFlags;
	}

	inline
	atl::uint32 Image::GetFlags() const
	{
		return flags;
	}
}

#endif
