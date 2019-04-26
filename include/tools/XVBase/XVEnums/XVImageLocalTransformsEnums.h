#ifndef XVIMAGELOCALTRANSFORMSENUMS_H
#define XVIMAGELOCALTRANSFORMSENUMS_H

namespace XVMorphologyKernel
{
    enum Type
    {
        Box3x3,
        Box5x5,
        Cross3x3,
        Cross5x5,
        Disc5x5,
        Disc7x7,
        Disc9x9
    };
}
namespace XVMeanKernel
{
    enum Type
    {
        Box3x3,
        Box5x5
    };
}
namespace XVGaussKernel
{
    enum Type
    {
        _3x3,
        _5x5,
        _7x7,
        _9x9,
        _11x11
    };
}
namespace XVGradientMaskOperator
{
    enum Type
    {
        Sobel,						// Sobel operator
        Prewitt,  					// Prewitt operator
        Central,
        Forward
    };
}
namespace XVGradientOperator
{
    enum Type
    {
        Gauss,
        Deriche,
        Lanser
    };
}
namespace XVMagnitudeMeasure
{
    enum Type
    {
        Horizontal,   				// Horizontal estimation
        Vertical, 					// Vertical estimation
        Average,  					// Average estimation
        Sum,  						// Sum estimation
        Maximum,  					// Maximum estimation
        Hypot 						// Hypot estimation
    };
}
namespace XVSmoothImageMedianKernel
{
    enum Type
    {
        Box
    };
}


#endif // XVIMAGELOCALTRANSFORMSENUMS_H
