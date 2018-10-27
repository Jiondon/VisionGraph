//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _BARCODEGRADES_H
#define _BARCODEGRADES_H

#include "ATL/AtlString.h"
#include "ATL/AtlTypes.h"
#include "ATL/Optional.h"

namespace avl
{
	struct BarcodeGrades
	{
		atl::Conditional<float>	overallGrade;
		atl::Conditional<float>	decode;
		atl::String				decodedText;
		atl::Conditional<float>	rmax;
		int						rmin;
		atl::Conditional<float>	globalThreshold;
		float					symbolContrast;
		atl::Conditional<float>	minEdgeContrast;
		atl::Conditional<float>	modulation;
		atl::Conditional<float>	defects;
		atl::Conditional<float>	decodability;

		explicit BarcodeGrades
		(
			atl::Conditional<float> overallGrade_ = atl::NIL,
			atl::Conditional<float> decode_ = atl::NIL,
			atl::String decodedText_ = "",
			atl::Conditional<float> rmax_ = atl::NIL,
			int rmin_ = 0,
			atl::Conditional<float> globalThreshold_ = atl::NIL,
			float symbolContrast_ = 0.0f,
			atl::Conditional<float> minEdgeContrast_ = atl::NIL,
			atl::Conditional<float> modulation_ = atl::NIL,
			atl::Conditional<float> defects_ = atl::NIL,
			atl::Conditional<float> decodability_ = atl::NIL 
		) :
			 overallGrade(overallGrade_),
			 decode(decode_),
			 decodedText(decodedText_),
			 rmax(rmax_),
			 rmin(rmin_),
			 globalThreshold(globalThreshold_),
			 symbolContrast(symbolContrast_),
			 minEdgeContrast(minEdgeContrast_),
			 modulation(modulation_),
			 defects(defects_),
			 decodability(decodability_) 
		{}

		atl::Conditional<float> OverallGrade() const	{ return overallGrade;		};
		atl::Conditional<float> Decode() const			{ return decode;			};
		atl::String DecodedText() const					{ return decodedText;		};
		atl::Conditional<float> Rmax() const			{ return rmax;				};
		int Rmin() const								{ return rmin;				};
		atl::Conditional<float> GlobalThreshold() const	{ return globalThreshold;	};
		float SymbolContrast() const					{ return symbolContrast;	};
		atl::Conditional<float> MinEdgeContrast() const	{ return minEdgeContrast;	};
		atl::Conditional<float> Modulation() const		{ return modulation;		};
		atl::Conditional<float> Defects() const			{ return defects;			};
		atl::Conditional<float> Decodability() const	{ return decodability;		};

		bool operator == ( const avl::BarcodeGrades& rhs ) const
		{
			return overallGrade == rhs.overallGrade && 
			decode == rhs.decode && 
			decodedText == rhs.decodedText && 
			rmax == rhs.rmax && 
			rmin == rhs.rmin && 
			globalThreshold == rhs.globalThreshold && 
			symbolContrast == rhs.symbolContrast && 
			minEdgeContrast == rhs.minEdgeContrast && 
			modulation == rhs.modulation && 
			defects == rhs.defects && 
			decodability == rhs.decodability;
		}

		bool operator != ( const avl::BarcodeGrades& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

} //namespace avl


#endif

