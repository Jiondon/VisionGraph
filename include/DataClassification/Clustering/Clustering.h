//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_CLUSTERING_H
#define AVL_CLUSTERING_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.hxx"
#include "AVLCommon/MatrixTypes.h"
#include "Geometry/Geometry.h"
#include "Geometry3D/Geometry3D.h"
#include "ATL/Optional.h"

namespace avl
{


	namespace KMeansClusteringMethod
	{
		enum Type
		{
			KMeans = 0,
			KMeansPlusPlus = 1
		};
	}


	/// <summary>Clusters 3D points using K Means Clustering method.</summary>
	/// <param name="inPoints">Array of points to cluster.</param>
	/// <param name="inClusters">Number of clusters to extract. Default value: 2.</param>
	/// <param name="inMaxIterations">Maximal number of KMeans iterations. Default value: 200.</param>
	/// <param name="outClusters">Resulting Point3D clusters.</param>
	/// <param name="outCentroids">Center of found clusters.</param>
	/// <param name="outDistanceSum">Sum of distance squares from points in array to its respective cluster center.</param>
	AVL_FUNCTION void ClusterPoints3D
	(
		const atl::Array<avl::Point3D>&				inPoints,			
		const int									inClusters,			
		const int									inMaxIterations,	
		atl::Array<atl::Conditional<atl::Array<avl::Point3D>>>&		outClusters,		
		atl::Array<atl::Conditional<avl::Point3D>>&	outCentroids,		
		float&									outDistanceSum		
	)
	THROW_AVL_ERRORS;

	/// <summary>Clusters 2D points using K Means Clustering method.</summary>
	/// <param name="inPoints">Array of points to cluster.</param>
	/// <param name="inClusters">Number of clusters to extract. Default value: 2.</param>
	/// <param name="inMaxIterations">Maximal number of KMeans iterations. Default value: 200.</param>
	/// <param name="outClusters">Resulting Point2D clusters.</param>
	/// <param name="outCentroids">Center of found clusters.</param>
	/// <param name="outDistanceSum">Sum of distance squares from points in array to its respective cluster center.</param>
	AVL_FUNCTION void ClusterPoints2D
	(
		const atl::Array<avl::Point2D>&				inPoints,			
		const int									inClusters, 		
		const int									inMaxIterations,	
		atl::Array<atl::Conditional<atl::Array<avl::Point2D>>>&		outClusters,		
		atl::Array<atl::Conditional<avl::Point2D>>&	outCentroids,		
		float&									outDistanceSum		
	)
	THROW_AVL_ERRORS;

	/// <summary>Clusters data using KMeans algorithm.</summary>
	/// <param name="inData">Data set, array of examples.</param>
	/// <param name="inClusters">Number of clusters to extract. Default value: 2.</param>
	/// <param name="inMaxIterations">Maximal number of procedure iterations. Default value: 200.</param>
	/// <param name="inSeed">Seed to init random engine. Default value: 5489.</param>
	/// <param name="inTerminationFactor">Additional factor of procedure stop. Default value: 1.5f.</param>
	/// <param name="inClusteringMethod">KMeans variant to use. Default value: KMeansPlusPlus.</param>
	/// <param name="outCentroids">Resulting centroid points in feature space.</param>
	/// <param name="outPointToClusterAssignment">Array of input point assignments to generated clusters.</param>
	/// <param name="outDistanceSum">Sum of squared distances from points to its respective cluster centroids.</param>
	AVL_FUNCTION void ClusterData_KMeans
	(
		const atl::Array<atl::Array<float> >&	inData,				
		const int			inClusters,								
		const int			inMaxIterations,						
		const int			inSeed,									
		const float			inTerminationFactor,					
		const avl::KMeansClusteringMethod::Type inClusteringMethod, 
		avl::Matrix&		outCentroids,							
		atl::Array<int>&	outPointToClusterAssignment,			
		float&				outDistanceSum							
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds connected components in a graph given as set of bidirectional connections.</summary>
	/// <param name="inConnections">List of connections for each element.</param>
	/// <param name="outComponents">List of input element indices for each connected component.</param>
	/// <param name="outElementLabels">Index of a component for each input element.</param>
	AVL_FUNCTION void FindConnectedComponents
	(
		const atl::Array<atl::Array<int> >& inConnections, 
		atl::Array<atl::Array<int> >&		outComponents, 
		atl::Array<int>&					outElementLabels, 
		bool&								outFound
	)
	THROW_AVL_ERRORS;

	/// <summary>Clusters data using hierarchical single-link algorithm.</summary>
	/// <param name="inPoints">Array of points to cluster.</param>
	/// <param name="inClusters">Number of clusters to extract. Default value: atl::NIL.</param>
	/// <param name="inMaxDistance">Maximum distance between two closest points in a cluster. Default value: atl::NIL.</param>
	/// <param name="outClusters">Resulting Point2D clusters.</param>
	AVL_FUNCTION void ClusterPoints2D_SingleLink
	(
		const atl::Array<avl::Point2D>&				inPoints,			
		const atl::Optional<int>					inClusters,			
		const atl::Optional<float>					inMaxDistance,		
		atl::Array<atl::Array<avl::Point2D>>&		outClusters			
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_CLUSTERING_H

