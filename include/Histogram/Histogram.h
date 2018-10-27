//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_HISTOGRAM_H
#define AVL_HISTOGRAM_H

#include "ATL/Utils.h"
#include "ATL/AtlTypes.h"
#include "ATL/Array.hxx"
#include <cstring>
#include <cmath>

namespace avl
{

	class Histogram : public atl::Array< int >
	{
	private:
		float domainBegin;
		float domainEnd;
		float binSize;

	public:
		Histogram()
			: domainBegin(0.0f), domainEnd(0.0f), binSize(0.0f)
		{
		}

		Histogram( float l, float r, float i)
		: domainBegin(l), domainEnd(r), binSize(i)
		{
			float newSizeReal = (domainEnd-domainBegin)/binSize;
			atl::Array<int>::Resize((int)std::ceil(newSizeReal), 0);
		}

		Histogram( float l, float r, float i, int bins)
		: domainBegin(l), domainEnd(r), binSize(i)
		{
			atl::Array<int>::Resize(bins, 0);
		}

		Histogram( float l, float r, float i, const void* data, int count )
		{
			Reset(l, r, i, data, count);
		}

#ifdef HAS_CPP0X

		Histogram( const Histogram& rhs )
		: atl::Array< int >( rhs )
		, domainBegin(rhs.domainBegin)
		, domainEnd(rhs.domainEnd)
		, binSize(rhs.binSize)
		{
		}

		avl::Histogram& operator = ( const Histogram& rhs )
		{
			domainBegin = rhs.domainBegin;
			domainEnd = rhs.domainEnd;
			binSize = rhs.binSize;
			atl::Array<int>::operator=( rhs );

			return *this;
		}

		Histogram( Histogram&& rhs )
		: atl::Array< int >( std::move(rhs) )
		, domainBegin(rhs.domainBegin)
		, domainEnd(rhs.domainEnd)
		, binSize(rhs.binSize)
		{
		}

		avl::Histogram& operator = ( Histogram&& rhs )
		{
			domainBegin = rhs.domainBegin;
			domainEnd = rhs.domainEnd;
			binSize = rhs.binSize;
			atl::Array<int>::operator=( std::move(rhs) );

			return *this;
		}

#endif

		void Reset( float l, float r, float i, const void* newData, int count)
		{
			domainBegin = l;
			domainEnd = r;
			binSize = i;
			atl::Array<int>::Resize(count);
			std::memcpy((void*)Begin(), newData, count * sizeof(int));
		}


		int			Size() const				{ return atl::Array<int>::Size(); }
		void		Reserve( int newCapacity )	{ return atl::Array<int>::Reserve(newCapacity); }
		int*		Begin()						{ return atl::Array<int>::Begin(); }
		int*		End()						{ return atl::Array<int>::End(); }
		const int*	Begin()	const				{ return atl::Array<int>::Begin(); }
		const int*	End()	const				{ return atl::Array<int>::End(); }
		float		DomainBegin()	const		{ return domainBegin; }
		float		DomainEnd()	const			{ return domainEnd; }
		float		BinSize()	const           { return binSize; }
		void		SetDomainBegin( float l )	{ domainBegin = l;  }
		void		SetDomainEnd( float r )		{ domainEnd = r; }
		void		SetBinSize( float i)			{ binSize = i; }
		
		bool operator == ( const Histogram& rhs ) const
		{
			if ( Size() != rhs.Size() ) return false;
			if ( DomainBegin() != rhs.DomainBegin() ) return false;
			if ( DomainEnd() != rhs.DomainEnd() ) return false;
			if ( BinSize() != rhs.BinSize() ) return false;

			for ( int i = 0; i < Size(); ++i )
			{
				if ( !( (*this)[i] == rhs[i] ) )
				{
					return false;
				}
			}
			return true;
		}

		bool operator != ( const Histogram& rhs ) const
		{
			return !(operator == (rhs));
		}
	};

}


#endif
