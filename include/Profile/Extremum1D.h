//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _EXTREMUM1D_H
#define _EXTREMUM1D_H

#include "ATL/AtlTypes.h"
#include "Enums/ExtremumType.h"

namespace avl
{
	struct Extremum1D
	{
		int					index;
		float				point;
		float				value;
		ExtremumType::Type	type;

		explicit Extremum1D
		(
			int index_ = 0,
			float point_ = 0.0f,
			float value_ = 0.0f,
			ExtremumType::Type type_ = ExtremumType::Any 
		) :
			 index(index_),
			 point(point_),
			 value(value_),
			 type(type_) 
		{}

		int Index() const				{ return index;	};
		float Point() const				{ return point;	};
		float Value() const				{ return value;	};
		ExtremumType::Type Type() const	{ return type;	};

		bool operator == ( const avl::Extremum1D& rhs ) const
		{
			return index == rhs.index && 
			point == rhs.point && 
			value == rhs.value && 
			type == rhs.type;
		}

		bool operator != ( const avl::Extremum1D& rhs ) const
		{
			return !(operator==(rhs));
		}

		
		bool operator < (const Extremum1D& rhs) const
		{
			return value < rhs.value;
		}
		
	};

} //namespace avl


#endif

