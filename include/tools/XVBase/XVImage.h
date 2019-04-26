#ifndef XVIMAGE_H
#define XVIMAGE_H

#include "XVGlobal.h"
#include "XVBaseType.h"
#include "XVEnums/XVPolarity.h"

enum XVPlainType
{
    Int8,
    UInt8,
    Int16,
    UInt16,
    Int32,
    Real
};

struct XVImage;
///函数
static void CopyXVImage(const XVImage& src, XVImage &dest);
static int sizeof_PlainType( XVPlainType type );


struct XVImage
{
    XVOptionalType  optional = NUL;
    int             width   = 0;                    // number of pixel columns
    int             height  = 0;                    // number of pixel rows
    XVPlainType	    type    = XVPlainType::UInt8;   // type of channels (默认UInt8)
    int             depth   = 1;                    // number of channels(灰度图1)
    BYTE*           data    = nullptr;
};


struct XVImageFormat
{
    int             width   = 0;                    // Image width in pixels
    int             height  = 0;                    // Image height in pixels
    XVPlainType     type    = XVPlainType::UInt8;   // Type of pixel components
    int             depth   = 1;                    // Number of pixel components
    int             pitchAlignment = 16;
};

struct XVExtremum2D
{
    XVOptionalType  optional = NUL;
    XVPoint2D       point;
    float           value;
    XVPolarityType  polarity;
};

struct XVImageLocalExtremaVerification
{
    XVOptionalType  optional      = NUL;
    int             pointCount    = 8;
    float           radius        = 3.0f;
    float           minDifference = 0.0f;
};


void CopyXVImage(const XVImage &src, XVImage &dest)
{
    dest.optional = src.optional;
    dest.width  = src.width ;
    dest.height = src.height;
    dest.type   = src.type  ;
    dest.depth  = src.depth ;
    if(dest.data != nullptr){
        free(dest.data);
        dest.data = nullptr;
    }
    if(src.data != nullptr){
        int size = src.width*src.height*sizeof(BYTE)*src.depth;
        dest.data = (BYTE*)malloc(size);
        memcpy(dest.data,src.data,size);
    }
}
int sizeof_PlainType( XVPlainType type )
{
    switch (type)
    {
    case XVPlainType::Int8:     return sizeof( signed   char );
    case XVPlainType::UInt8:	return sizeof( unsigned char );
    case XVPlainType::Int16:	return sizeof( signed   short );
    case XVPlainType::UInt16:	return sizeof( unsigned short );
    case XVPlainType::Int32:	return sizeof( signed   int );
    case XVPlainType::Real:     return sizeof( float );
    default:		return 0;
    }
}

#endif // XVIMAGE_H
