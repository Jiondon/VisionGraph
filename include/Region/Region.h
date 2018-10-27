//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_REGION_H
#define AVL_REGION_H

#include "ATL/Utils.h"
#include "ATL/AtlTypes.h"
#include "ATL/Array.hxx"
#include "Basic/Types.h"
#include <cstring>

namespace avl
{

	/*
	*	Compressed sequence of horizontally consecutive locations.
	*
	*	Fixed binary representation in 6 bytes (for interoperability):
	*		0x00: atl::uint16 x;
	*		0x02: atl::uint16 y;
	*		0x04: atl::uint16 length;
	*/
	class PointRun
	{
	public:
		atl::uint16 x, y; // PointRun begin location
		atl::uint16	length;

		PointRun() 
			: x(0)
			, y(0)
			, length(0) 
		{}

		PointRun( const Location& begin, int length )
			: x( (atl::uint16)begin.x )
			, y( (atl::uint16)begin.y )
			, length( (atl::uint16)length )
		{}

		PointRun( int x, int y, int length )
			: x( (atl::uint16)x )
			, y( (atl::uint16)y )
			, length( (atl::uint16)length )
		{}

		Location	Begin()  const	{ return Location( x, y ); }
		Location	End()    const	{ return Location( x + length, y ); }
		int			Length() const	{ return length; }

		int			X()		 const	{ return x; }
		int			Y()		 const	{ return y; }

		bool operator == ( const PointRun& rhs ) const { return x == rhs.x && y == rhs.y && length == rhs.length; }
		bool operator != ( const PointRun& rhs ) const { return x != rhs.x || y != rhs.y || length != rhs.length; }

		// for sorting pointRuns according to Region order
		bool operator< ( const PointRun& rhs ) const
		{ 
			if (y != rhs.Y())
				return y < rhs.Y();
			else
				return x < rhs.Begin().x;
		} 
		
	};

	// A separate class to force field order in class Region
	class RegionFrame
	{
	protected:
		RegionFrame(int frameWidth_, int frameHeight_) : frameWidth(frameWidth_), frameHeight(frameHeight_) {}

		int frameWidth;
		int	frameHeight;
	};

	// Compressed binary mask.
	class Region : public RegionFrame, public atl::Array< PointRun >
	{
	public:
		Region() : RegionFrame(0, 0)
		{}

		Region(int frameWidth_, int frameHeight_) : RegionFrame(frameWidth_, frameHeight_)
		{}

		Region(int frameWidth_, int frameHeight_, void* data, int count, bool own)
			: RegionFrame(frameWidth_, frameHeight_)
			, atl::Array<PointRun>(count, static_cast<PointRun*>(data), own)
		{}

		Region(int frameWidth_, int frameHeight_, void* data, int count)
			: RegionFrame(frameWidth_, frameHeight_)
		{
			const avl::PointRun* newData = (const avl::PointRun*)data;
			atl::Array<PointRun>::Insert(newData, newData + count);
		}

#ifdef HAS_CPP0X

		Region( const Region& rhs )
			: RegionFrame( rhs )
			, atl::Array< PointRun >( rhs )
		{}

		Region( Region&& rhs )
			: RegionFrame( std::move(rhs) )
			, atl::Array< PointRun >( std::move(rhs) )
		{}

		Region(int frameWidth_, int frameHeight_, atl::Array<PointRun> pointRuns)
			: RegionFrame(frameWidth_, frameHeight_)
			, atl::Array< PointRun >( std::move(pointRuns) )
		{}

		avl::Region& operator = ( Region&& rhs )
		{
			RegionFrame::operator=( std::move(rhs) );
			atl::Array< PointRun >::operator=( std::move(rhs) );

			return *this;
		}	

		avl::Region& operator = ( const Region& rhs )
		{
			RegionFrame::operator=(rhs);
			atl::Array< PointRun >::operator=( rhs );

			return *this;
		}	

#endif

		void Reset()
		{
			atl::Array<PointRun>::Reset();
		}

		void Reset( int frameWidth_, int frameHeight_ )
		{
			frameWidth = frameWidth_;
			frameHeight = frameHeight_;
			atl::Array<PointRun>::Reset();
		}

		void Reset( int frameWidth_, int frameHeight_, const void* data_, int count )	// Creates copy
		{
			frameWidth = frameWidth_;
			frameHeight = frameHeight_;
			atl::Array<PointRun>::Clear();
			Insert((const avl::PointRun*)data_, (const avl::PointRun*)data_ + count);
		}

		void Reset( int frameWidth_, int frameHeight_, void* data_, int count, bool own )	// Creates a view
		{
			frameWidth = frameWidth_;
			frameHeight = frameHeight_;
			atl::Array<PointRun>::Reset(count, static_cast<avl::PointRun*>(data_), own);
		}

		int			FrameWidth() const			{ return frameWidth; }
		int			FrameHeight() const			{ return frameHeight; }
		Box			Frame() const				{ return Box( 0, 0, frameWidth, frameHeight ); }
		int			Size() const				{ return atl::Array<PointRun>::Size(); }
		void		Reserve( int newCapacity )	{ return atl::Array<PointRun>::Reserve(newCapacity); }
		PointRun*	Begin()						{ return atl::Array<PointRun>::Begin(); }
		PointRun*	End()						{ return atl::Array<PointRun>::End(); }
		const PointRun*	Begin()	const			{ return atl::Array<PointRun>::Begin(); }
		const PointRun*	End()	const			{ return atl::Array<PointRun>::End(); }

		PointRun	Run   ( int k ) const		{ return (*this)[k];          }
		Location	Begin ( int k ) const		{ return (*this)[k].Begin();  }
		Location	End   ( int k ) const		{ return (*this)[k].End();    }
		int			Length( int k ) const		{ return (*this)[k].Length(); }

		void		SetFrameWidth ( int frameWidth_ )	{ frameWidth = frameWidth_;  }
		void		SetFrameHeight( int frameHeight_ )	{ frameHeight = frameHeight_; }
		void		SetFrame( int frameWidth_, int frameHeight_ )	{ frameWidth = frameWidth_; frameHeight = frameHeight_; }
				
		void		Add( const PointRun& pr )				{ PushBack(pr);		}

#ifdef HAS_CPP0X

		void		Add( int x, int y, int len )			{ EmplaceBack( x, y, len );			}
		void		Add( const Location& begin, int len )	{ EmplaceBack( begin, len );		}

#else // HAS_CPP0X

		void		Add( int x, int y, int len )			{ PushBack( PointRun( x, y, len ) );		}
		void		Add( const Location& begin, int len )	{ PushBack( PointRun( begin, len ) );		}

#endif // HAS_CPP0X

		bool operator== ( const Region& rhs ) const 
		{
			if ( Size() != rhs.Size() ) 
				return false;
			
			if ( FrameWidth() != rhs.FrameWidth() ) 
				return false;
			
			if ( FrameHeight() != rhs.FrameHeight() ) 
				return false;
			
			for ( int i = 0; i < Size(); ++i )
			{
				if ( !( (*this)[i] == rhs[i] ) )
				{
					return false;
				}
			}
			return true;
		}

		bool operator!= (const Region& rhs) const { return !(operator==(rhs)); }
	};

}


#endif
