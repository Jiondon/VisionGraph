#ifndef XVTHRESHOLDMETHOD_H
#define XVTHRESHOLDMETHOD_H


namespace XVThresholdSelectionMethod
{
    enum Type
    {
        ClusteringKittler,
        ClusteringKMeans, 			// KMeans clustering
        ClusteringOtsu,   			// Otsu clustering
        Entropy,
        HistogramIntermodes
    };
}
namespace XVThresholdDynamicReferenceMethod
{
    enum Type
    {
        Mean,
        Median,
        Middle
    };
}

#endif // XVTHRESHOLDMETHOD_H
