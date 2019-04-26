#ifndef XVREGIONFEATURETYPE_H
#define XVREGIONFEATURETYPE_H

namespace XVRegionFeature
{
enum Type
{
    Area,
    BoundingBoxBottom,
    BoundingBoxHeight,
    BoundingBoxLeft,
    BoundingBoxRight,
    BoundingBoxTop,
    BoundingBoxWidth,
    Circularity_BoundingCirclePreserving,
    Circularity_PerimeterPreserving,
    Circularity_RadiusPreserving,
    Convexity,
    DiameterLength,
    Elongation,
    MassCenterX,
    MassCenterY,
    MajorAxisLength,
    MinorAxisLength,
    NumberOfHoles_EightDirections,
    NumberOfHoles_FourDirections,
    PerimeterLength,
    Rectangularity
};
}

#endif // XVREGIONFEATURETYPE_H
