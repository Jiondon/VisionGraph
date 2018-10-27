//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_KNEARESTNEIGHBORS_H
#define AVL_KNEARESTNEIGHBORS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.hxx"
#include "Geometry/Geometry.h"
#include "Enums/Metric.h"

namespace avl
{


	class KNNModel;
	class KNNModelImpl;

	namespace pImpl_helpers
	{
		/* For internal use only */
		AVL_FUNCTION void DestructKNNModel(KNNModel&);
		AVL_FUNCTION void CopyKNNModel(const KNNModel&, KNNModel&);
		AVL_FUNCTION bool TestKNNModelEqual(const KNNModel&, const KNNModel&);
	}

	class KNNModel
	{
	public:
		KNNModel() : pImpl(0) {}

		~KNNModel()
		{
			pImpl_helpers::DestructKNNModel(*this);
		}

		KNNModel(const KNNModel& inKNNModel) : pImpl(0)
		{
			pImpl_helpers::CopyKNNModel(inKNNModel, *this);
		}

		KNNModel& operator=(const KNNModel& inKNNModel)
		{
			pImpl_helpers::CopyKNNModel(inKNNModel, *this);
			return *this;
		}

		bool operator == (const KNNModel& rhs) const
		{
			return pImpl_helpers::TestKNNModelEqual(*this, rhs);
		}
		
		bool operator != (const KNNModel& rhs) const
		{
			return !(operator==(rhs));
		}
		
		KNNModelImpl* pImpl;
	};



	/// <summary>Initializes the KNN classifier.</summary>
	/// <param name="inClassCount">Number of classes.</param>
	/// <param name="inDimensionCount">Length of feature vector.</param>
	/// <param name="outKNNModel">Initialized KNN model.</param>
	AVL_FUNCTION void KNN_Init
	(
		const int				inClassCount,		
		const int				inDimensionCount,	
		avl::KNNModel&			outKNNModel			
	)
	THROW_AVL_ERRORS;

	/// <summary>Trains KNN classifier using sample data.</summary>
	/// <param name="inKNNModel">Initialized KNN model.</param>
	/// <param name="inFeatures">Array of features array.</param>
	/// <param name="inClasses">Array of classes corresponding to feature array elements.</param>
	/// <param name="outKNNModel">Trained KNN model.</param>
	AVL_FUNCTION void KNN_Train
	(
		const avl::KNNModel&						inKNNModel,		
		const atl::Array<atl::Array<float> >&	inFeatures,		
		const atl::Array< int >&					inClasses,		
		avl::KNNModel&								outKNNModel		
	)
	THROW_AVL_ERRORS;

	/// <summary>Classify data using the KNN classifier.</summary>
	/// <param name="inKNNModel">Trained KNN model.</param>
	/// <param name="inFeature">Vector of features.</param>
	/// <param name="inK">Numbers of neighbors.</param>
	/// <param name="inDistanceType">Geometry distance type used to calculate neighbors.</param>
	AVL_FUNCTION void KNN_Classify
	(	
		const avl::KNNModel&			inKNNModel,			
		const atl::Array<float>&	inFeature,			
		const int						inK,				
		const avl::Metric::Type			inDistanceType,		
		int&							outClass
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_KNEARESTNEIGHBORS_H

