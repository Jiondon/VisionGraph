//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _DATACODE_H
#define _DATACODE_H

#include "ATL/Array.h"
#include "ATL/AtlString.h"
#include "ATL/AtlTypes.h"
#include "ATL/Optional.h"
#include "Enums/DataMatrixDetectionMethod.h"
#include "Enums/DataMatrixGapSize.h"
#include "Enums/DataMatrixOutlineStrategy.h"
#include "Enums/DataMatrixPyramidStrategy.h"
#include "Enums/Polarity.h"
#include "Geometry/Geometry.h"
#include "Path/Path.h"

namespace avl
{
	struct DataCode
	{
		Path			outline;
		Polarity::Type	polarity;
		atl::String		text;
		int				rowCount;
		int				columnCount;
		float			minModuleSize;
		float			maxModuleSize;
		Point2D			center;
		atl::Array<Point2D>			grid;

		explicit DataCode
		(
			Path outline_ = Path(),
			Polarity::Type polarity_ = Polarity::Any,
			atl::String text_ = "",
			int rowCount_ = 0,
			int columnCount_ = 0,
			float minModuleSize_ = 0.0f,
			float maxModuleSize_ = 0.0f,
			Point2D center_ = Point2D(),
			const atl::Array<Point2D>& grid_ = atl::Array<Point2D>() 
		) :
			 outline(outline_),
			 polarity(polarity_),
			 text(text_),
			 rowCount(rowCount_),
			 columnCount(columnCount_),
			 minModuleSize(minModuleSize_),
			 maxModuleSize(maxModuleSize_),
			 center(center_),
			 grid(grid_) 
		{}

		Path Outline() const					{ return outline;		};
		Polarity::Type Polarity() const			{ return polarity;		};
		atl::String Text() const				{ return text;			};
		int RowCount() const					{ return rowCount;		};
		int ColumnCount() const					{ return columnCount;	};
		float MinModuleSize() const				{ return minModuleSize;	};
		float MaxModuleSize() const				{ return maxModuleSize;	};
		Point2D Center() const					{ return center;		};
		const atl::Array<Point2D>& Grid() const	{ return grid;			};

		bool operator == ( const avl::DataCode& rhs ) const
		{
			return outline == rhs.outline && 
			polarity == rhs.polarity && 
			text == rhs.text && 
			rowCount == rhs.rowCount && 
			columnCount == rhs.columnCount && 
			minModuleSize == rhs.minModuleSize && 
			maxModuleSize == rhs.maxModuleSize && 
			center == rhs.center && 
			grid == rhs.grid;
		}

		bool operator != ( const avl::DataCode& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

	struct DataMatrixCodeParams
	{
		Polarity::Type			polarity;
		int						minRowCount;
		int						maxRowCount;
		int						minColumnCount;
		int						maxColumnCount;
		float					minModuleSize;
		float					maxModuleSize;
		DataMatrixGapSize::Type	expectedGapSize;
		atl::Optional<float>	maxRectangleRatio;
		float					maxSlant;
		bool					allowPerspective;
		bool					allowOversizedModules;

		explicit DataMatrixCodeParams
		(
			Polarity::Type polarity_ = Polarity::Any,
			int minRowCount_ = 8,
			int maxRowCount_ = 32,
			int minColumnCount_ = 8,
			int maxColumnCount_ = 32,
			float minModuleSize_ = 4,
			float maxModuleSize_ = 40,
			DataMatrixGapSize::Type expectedGapSize_ = DataMatrixGapSize::Small,
			atl::Optional<float> maxRectangleRatio_ = 4.0f,
			float maxSlant_ = 20.0f,
			bool allowPerspective_ = true,
			bool allowOversizedModules_ = true 
		) :
			 polarity(polarity_),
			 minRowCount(minRowCount_),
			 maxRowCount(maxRowCount_),
			 minColumnCount(minColumnCount_),
			 maxColumnCount(maxColumnCount_),
			 minModuleSize(minModuleSize_),
			 maxModuleSize(maxModuleSize_),
			 expectedGapSize(expectedGapSize_),
			 maxRectangleRatio(maxRectangleRatio_),
			 maxSlant(maxSlant_),
			 allowPerspective(allowPerspective_),
			 allowOversizedModules(allowOversizedModules_) 
		{}

		Polarity::Type Polarity() const					{ return polarity;				};
		int MinRowCount() const							{ return minRowCount;			};
		int MaxRowCount() const							{ return maxRowCount;			};
		int MinColumnCount() const						{ return minColumnCount;		};
		int MaxColumnCount() const						{ return maxColumnCount;		};
		float MinModuleSize() const						{ return minModuleSize;			};
		float MaxModuleSize() const						{ return maxModuleSize;			};
		DataMatrixGapSize::Type ExpectedGapSize() const	{ return expectedGapSize;		};
		atl::Optional<float> MaxRectangleRatio() const	{ return maxRectangleRatio;		};
		float MaxSlant() const							{ return maxSlant;				};
		bool AllowPerspective() const					{ return allowPerspective;		};
		bool AllowOversizedModules() const				{ return allowOversizedModules;	};

		bool operator == ( const avl::DataMatrixCodeParams& rhs ) const
		{
			return polarity == rhs.polarity && 
			minRowCount == rhs.minRowCount && 
			maxRowCount == rhs.maxRowCount && 
			minColumnCount == rhs.minColumnCount && 
			maxColumnCount == rhs.maxColumnCount && 
			minModuleSize == rhs.minModuleSize && 
			maxModuleSize == rhs.maxModuleSize && 
			expectedGapSize == rhs.expectedGapSize && 
			maxRectangleRatio == rhs.maxRectangleRatio && 
			maxSlant == rhs.maxSlant && 
			allowPerspective == rhs.allowPerspective && 
			allowOversizedModules == rhs.allowOversizedModules;
		}

		bool operator != ( const avl::DataMatrixCodeParams& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

	struct DataMatrixDetectionParams
	{
		int								contrastThreshold;
		int								contrastHysteresis;
		int								contrastPerturbations;
		atl::Optional<int>				dynamicSNRatio;
		bool							nonBinarySegmentation;
		bool							forceIsotropy;
		DataMatrixDetectionMethod::Type	detectionMethod;
		DataMatrixPyramidStrategy::Type	pyramidStrategy;
		DataMatrixOutlineStrategy::Type	outlineStrategy;

		explicit DataMatrixDetectionParams
		(
			int contrastThreshold_ = 10,
			int contrastHysteresis_ = 0,
			int contrastPerturbations_ = 0,
			atl::Optional<int> dynamicSNRatio_ = atl::NIL,
			bool nonBinarySegmentation_ = false,
			bool forceIsotropy_ = false,
			DataMatrixDetectionMethod::Type detectionMethod_ = DataMatrixDetectionMethod::QuietZone,
			DataMatrixPyramidStrategy::Type pyramidStrategy_ = DataMatrixPyramidStrategy::Fast,
			DataMatrixOutlineStrategy::Type outlineStrategy_ = DataMatrixOutlineStrategy::Fast 
		) :
			 contrastThreshold(contrastThreshold_),
			 contrastHysteresis(contrastHysteresis_),
			 contrastPerturbations(contrastPerturbations_),
			 dynamicSNRatio(dynamicSNRatio_),
			 nonBinarySegmentation(nonBinarySegmentation_),
			 forceIsotropy(forceIsotropy_),
			 detectionMethod(detectionMethod_),
			 pyramidStrategy(pyramidStrategy_),
			 outlineStrategy(outlineStrategy_) 
		{}

		int ContrastThreshold() const							{ return contrastThreshold;		};
		int ContrastHysteresis() const							{ return contrastHysteresis;	};
		int ContrastPerturbations() const						{ return contrastPerturbations;	};
		atl::Optional<int> DynamicSNRatio() const				{ return dynamicSNRatio;		};
		bool NonBinarySegmentation() const						{ return nonBinarySegmentation;	};
		bool ForceIsotropy() const								{ return forceIsotropy;			};
		DataMatrixDetectionMethod::Type DetectionMethod() const	{ return detectionMethod;		};
		DataMatrixPyramidStrategy::Type PyramidStrategy() const	{ return pyramidStrategy;		};
		DataMatrixOutlineStrategy::Type OutlineStrategy() const	{ return outlineStrategy;		};

		bool operator == ( const avl::DataMatrixDetectionParams& rhs ) const
		{
			return contrastThreshold == rhs.contrastThreshold && 
			contrastHysteresis == rhs.contrastHysteresis && 
			contrastPerturbations == rhs.contrastPerturbations && 
			dynamicSNRatio == rhs.dynamicSNRatio && 
			nonBinarySegmentation == rhs.nonBinarySegmentation && 
			forceIsotropy == rhs.forceIsotropy && 
			detectionMethod == rhs.detectionMethod && 
			pyramidStrategy == rhs.pyramidStrategy && 
			outlineStrategy == rhs.outlineStrategy;
		}

		bool operator != ( const avl::DataMatrixDetectionParams& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

} //namespace avl


#endif

