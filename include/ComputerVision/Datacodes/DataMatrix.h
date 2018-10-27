//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _DATAMATRIX_H
#define _DATAMATRIX_H

#include "ATL/AtlString.h"
#include "Enums/DataMatrixCodeType.h"
#include "Geometry/Geometry.h"

namespace avl
{
	struct DataMatrix
	{
		Rectangle2D				position;
		atl::String				text;
		DataMatrixType::Type	type;

		explicit DataMatrix
		(
			Rectangle2D position_ = Rectangle2D(),
			atl::String text_ = "",
			DataMatrixType::Type type_ = DataMatrixType::ECC_200 
		) :
			 position(position_),
			 text(text_),
			 type(type_) 
		{}

		Rectangle2D Position() const		{ return position;	};
		atl::String Text() const			{ return text;		};
		DataMatrixType::Type Type() const	{ return type;		};

		bool operator == ( const avl::DataMatrix& rhs ) const
		{
			return position == rhs.position && 
			text == rhs.text && 
			type == rhs.type;
		}

		bool operator != ( const avl::DataMatrix& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

} //namespace avl


#endif

