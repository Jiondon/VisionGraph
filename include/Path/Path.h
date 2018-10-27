//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_PATH_H
#define AVL_PATH_H

#include "ATL/Utils.h"
#include "ATL/Array.hxx"
#include "Geometry/Geometry.h"

#include <cstring>

namespace avl
{
	struct Path : atl::Array< Point2D >
	{
		bool closed;

		Path()
		: closed(false)
		{}

		explicit Path( bool closed )
		: closed( closed )
		{}

		Path( Segment2D segment )
		: closed(false)
		{ 
			PushBack( segment.Point1() );
			PushBack( segment.Point2() );
		}

		Path( Array<avl::Point2D> points, bool closed ) 
		: Array<avl::Point2D>(points)
		, closed(closed)
		{
		}
		
		Path( const void* data, int count, bool closed )
		{
			Reset(data, count, closed);
		}

#ifdef HAS_CPP0X

		Path( const Path& rhs )
		: atl::Array<Point2D>(rhs), closed (rhs.closed) {}

		Path( Path&& rhs )
		: atl::Array< Point2D >( std::move(rhs) )
		, closed(rhs.closed)
		{
		}

		avl::Path& operator = ( Path&& rhs )
		{
			atl::Array<avl::Point2D>::operator=( std::move(rhs) );
			closed = rhs.closed;

			return *this;
		}

		avl::Path& operator = ( const Path& rhs )
		{
			atl::Array<avl::Point2D>::operator=( rhs );
			closed = rhs.closed;

			return *this;
		}

#endif

#ifdef HAS_CPP11
		Path(std::initializer_list<avl::Point2D> ilist) : Path()
		{
			Insert(Begin(), ilist.begin(), ilist.end());
		}
#endif

		void Reset()
		{
			atl::Array< Point2D >::Reset();
		}

		void Reset( bool newClosed )
		{
			closed = newClosed;
			atl::Array< Point2D >::Reset();
		}

		void Reset( const Array<avl::Point2D>& points, bool newClosed )
		{
			closed = newClosed;
			atl::Array< Point2D >::operator=(points);
		}


		void Reset( const void* newData, int count, bool newClosed )
		{
			this->closed = newClosed;
			atl::Array< Point2D >::Resize( count );
			std::memcpy( Begin(), newData, count * sizeof( Point2D ) );
		}

		bool Closed( void ) const			{ return closed;			}
		void SetClosed( bool newClosed )	{ this->closed = newClosed;	}

		bool operator == ( const Path& rhs ) const 
		{
			return ( closed == rhs.closed && atl::Array<avl::Point2D>::operator==(rhs) );
		}

		bool operator != ( const Path& rhs ) const
		{
			return !(operator == (rhs));
		}
	};
}

#endif
