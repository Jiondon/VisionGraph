//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _DRAWINGSTYLE_H
#define _DRAWINGSTYLE_H

#include "ATL/AtlTypes.h"
#include "ATL/Optional.h"
#include "Enums/DrawingMode.h"
#include "Enums/PointShape.h"

namespace avl
{
	struct DrawingStyle
	{
		DrawingMode::Type				drawingMode;
		float						opacity;
		float						thickness;
		bool							filled;
		atl::Optional<PointShape::Type>	pointShape;
		float						pointSize;

		explicit DrawingStyle
		(
			 DrawingMode::Type drawingMode_ = DrawingMode::HighQuality,
			 float opacity_ = 1.0f,
			 float thickness_ = 3.0f,
			 bool filled_ = false,
			 atl::Optional<PointShape::Type> pointShape_ = atl::NIL,
			 float pointSize_ = 2.0f 
		) :
			 drawingMode(drawingMode_),
			 opacity(opacity_),
			 thickness(thickness_),
			 filled(filled_),
			 pointShape(pointShape_),
			 pointSize(pointSize_) 
		{}

		DrawingMode::Type DrawingMode( void ) const					{ return drawingMode;		};
		float Opacity( void ) const								{ return opacity;			};
		float Thickness( void ) const							{ return thickness;			};
		bool Filled( void ) const									{ return filled;			};
		atl::Optional<PointShape::Type> PointShape( void ) const	{ return pointShape;		};
		float PointSize( void ) const							{ return pointSize;			};

		bool operator == ( const avl::DrawingStyle& rhs ) const
		{
			return drawingMode == rhs.drawingMode && opacity == rhs.opacity && thickness == rhs.thickness && filled == rhs.filled && pointShape == rhs.pointShape && pointSize == rhs.pointSize;
		}

		bool operator != ( const avl::DrawingStyle& rhs ) const
		{
			return !(operator==(rhs));
		}
	};

} //namespace avl


#endif // _DRAWINGSTYLE_H

