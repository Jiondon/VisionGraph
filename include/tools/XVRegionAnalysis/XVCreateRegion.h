#ifndef XVCREATEREGION_H
#define XVCREATEREGION_H

#include "xvregionanalysis_global.h"

#include "XVBasic.h"
#include "XVRegionOfInterest.h"
#include "XVEnums/XVAnchor2D.h"
#include "XVString.h"


namespace XVBorderPosition //边模式
{
    enum Type
    {
        Internal,   //边内部
        External,   //边外部
        Centered    //边居中
    };
}

/// <summary>Creates a region corresponding to a given region of interest.</summary>
/// <param name="inFrameWidth">Width of the created region's frame.</param>
/// <param name="inFrameHeight">Height of the created region's frame.</param>
/// <param name="outRegion">Output region.</param>
struct XVCreateRegionOfInterestRegionIn
{
    XVRegionOfInterest              inRegionOfInterest ;
    int								inFrameWidth       ;
    int								inFrameHeight      ;
};
typedef RegionOut XVCreateRegionOfInterestRegionOut;

/// <summary>Creates a rectangular region corresponding to a given box.</summary>
/// <param name="inBox">A box defining pixels that will be converted to white elements.</param>
/// <param name="inFrameWidth">Width of the created region's frame {not to be confused with the width of the box!};.</param>
/// <param name="inFrameHeight">Height of the created region's frame {not to be confused with the height of the box!};.</param>
/// <param name="outRegion">Output region.</param>
struct XVCreateBoxRegionIn
{
    XVBox               inBox         ;
    int					inFrameWidth  ;
    int					inFrameHeight ;
};
typedef RegionOut XVCreateBoxRegionOut;

/// <summary>Creates a frame-shaped region with given parameters.</summary>
/// <param name="inBorderWidth">Default value: 1.</param>
/// <param name="inBorderPosition">Default value: Centered.</param>
/// <param name="inFrameWidth">Width of the created region's frame.</param>
/// <param name="inFrameHeight">Height of the created region's frame.</param>
/// <param name="outRegion">Output region.</param>
struct XVCreateBoxBorderRegionIn
{
    XVBox                       inBox            ;
    int							inBorderWidth    ;
    XVBorderPosition::Type   	inBorderPosition ;
    int							inFrameWidth     ;
    int							inFrameHeight    ;
};
typedef RegionOut XVCreateBoxBorderRegionOut;

/// <summary>Creates an elliptic region of given bounding rectangle.</summary>
/// <param name="inEllipseAlignment">Adjusts the ellipse to the position of the inspected object. Default value: atl::NIL.</param>
/// <param name="inFrameWidth">Width of the created region's frame {not to be confused with the width of the ellipse!};.</param>
/// <param name="inFrameHeight">Height of the created region's frame {not to be confused with the height of the ellipse!};.</param>
/// <param name="outRegion">Output region.</param>
/// <param name="outAlignedEllipse">The input ellipse transformed to the absolute coordinate system.</param>
struct XVCreateEllipseRegionIn
{
    XVRectangle2D                           inEllipse          ;
    XVCoordinateSystem2D                   	inEllipseAlignment ;
    int                                     inFrameWidth       ;
    int                                     inFrameHeight      ;
};
struct XVCreateEllipseRegionOut
{
    XVRegion                                outRegion          ;
    XVRectangle2D                           outAlignedEllipse  ;
};


/// <summary>Creates a ring-shaped region with given parameters.</summary>
/// <param name="inCircle">Input circle.</param>
/// <param name="inCircleAlignment">Adjusts the circle to the position of the inspected object. Default value: atl::NIL.</param>
/// <param name="inRingWidth">Default value: 1.0f.</param>
/// <param name="inBorderPosition">Default value: Centered.</param>
/// <param name="inFrameWidth">Width of the created region's frame.</param>
/// <param name="inFrameHeight">Height of the created region's frame.</param>
/// <param name="outRegion">Output region.</param>
/// <param name="outAlignedCircle">The input circle transformed to the absolute coordinate system.</param>
struct XVCreateRingRegionIn
{
    XVCircle2D    							inCircle          ;
    XVCoordinateSystem2D                   	inCircleAlignment ;
    float									inRingWidth       ;
    XVBorderPosition::Type                  inBorderPosition  ;
    int                                     inFrameWidth      ;
    int                                     inFrameHeight     ;
};
struct XVCreateRingRegionOut
{
    XVRegion                                outRegion         ;
    XVCircle2D                              outAlignedCircle  ;
};


/// <summary>Creates a cross-shaped region with given parameters.</summary>
/// <param name="inFrameWidth">Width of the created region's frame.</param>
/// <param name="inFrameHeight">Height of the created region's frame.</param>
/// <param name="outRegion">Output region.</param>
struct XVCreateCrossRegionIn
{
    XVBox               inCrossBoundingBox ;
    int					inFrameWidth       ;
    int					inFrameHeight      ;
};
typedef RegionOut XVCreateCrossRegionOut;

/// <summary>Creates a grid-shaped region with given parameters.</summary>
/// <param name="inHorizontalStep">Horizontal distance between vertical grid lines.</param>
/// <param name="inVerticalStep">Vertical distance between horizontal grid lines.</param>
/// <param name="inFrameWidth">Width of the created region's frame.</param>
/// <param name="inFrameHeight">Height of the created region's frame.</param>
/// <param name="outRegion">Output region.</param>
struct XVCreateGridRegionIn
{
    XVBox               inGridBoundingBox ;
    int					inHorizontalStep  ;
    int					inVerticalStep    ;
    int					inFrameWidth      ;
    int					inFrameHeight     ;
};
typedef RegionOut XVCreateGridRegionOut;

/// <summary>Creates a circular region corresponding to a given circle.</summary>
/// <param name="inCircleAlignment">Adjusts the circle to the position of the inspected object. Default value: atl::NIL.</param>
/// <param name="inFrameWidth">Width of the created region's frame {not to be confused with the size of the circle!};.</param>
/// <param name="inFrameHeight">Height of the created region's frame {not to be confused with the size of the circle!};.</param>
/// <param name="outRegion">Output region.</param>
/// <param name="outAlignedCircle">The input circle transformed to the absolute coordinate system.</param>
struct XVCreateCircleRegionIn
{
    XVCircle2D    							inCircle          ;
    XVCoordinateSystem2D                   	inCircleAlignment ;
    int                                     inFrameWidth      ;
    int                                     inFrameHeight     ;
};
typedef XVCreateRingRegionOut XVCreateCircleRegionOut;


/// <summary>Creates a polygonal region corresponding to a given closed path.</summary>
/// <param name="inPolygonAlignment">Adjusts the polygon to the position of the inspected object. Default value: atl::NIL.</param>
/// <param name="inFrameWidth">Width of the created region's frame.</param>
/// <param name="inFrameHeight">Height of the created region's frame.</param>
/// <param name="outRegion">Output region.</param>
/// <param name="outAlignedPolygon">The input polygon transformed to the absolute coordinate system.</param>
struct XVCreatePolygonRegionIn
{
    XVPath    								inPolygon          ;
    XVCoordinateSystem2D                   	inPolygonAlignment ;
    int										inFrameWidth       ;
    int										inFrameHeight      ;
};
struct XVCreatePolygonRegionOut
{
    XVRegion    							outRegion          ;
    XVPath                   				outAlignedPolygon  ;
};

/// <summary>Creates a region from a path with given parameters.</summary>
/// <param name="inPath">Input path.</param>
/// <param name="inPathAlignment">Adjusts the path to the position of the inspected object. Default value: atl::NIL.</param>
/// <param name="inBorderWidth">Default value: 1.0f.</param>
/// <param name="inBorderPosition">Default value: Centered.</param>
/// <param name="inFrameWidth">Width of the created region's frame.</param>
/// <param name="inFrameHeight">Height of the created region's frame.</param>
/// <param name="outRegion">Output region.</param>
/// <param name="outAlignedPath">The input path transformed to the absolute coordinate system.</param>
struct XVCreatePathBorderRegionIn
{
    XVPath                                  inPath           ;
    XVCoordinateSystem2D                   	inPathAlignment  ;
    float                                   inBorderWidth    ;
    XVBorderPosition::Type                  inBorderPosition ;
    int                                     inFrameWidth     ;
    int                                     inFrameHeight    ;
};
struct XVCreatePathBorderRegionOut
{
    XVRegion                                outRegion        ;
    XVPath                                  outAlignedPath   ;
};

/// <summary>Creates a region corresponding to a given rectangle.</summary>
/// <param name="inRectangleAlignment">Adjusts the rectangle to the position of the inspected object. Default value: atl::NIL.</param>
/// <param name="inFrameWidth">Width of the created region's frame {not to be confused with the width of the rectangle!};.</param>
/// <param name="inFrameHeight">Height of the created region's frame {not to be confused with the height of the rectangle!};.</param>
/// <param name="outRegion">Output region.</param>
/// <param name="outAlignedRectangle">The input rectangle transformed to the absolute coordinate system.</param>
struct XVCreateRectangleRegionIn
{
    XVRectangle2D    						inRectangle          ;
    XVCoordinateSystem2D                   	inRectangleAlignment ;
    int                                     inFrameWidth         ;
    int                                     inFrameHeight        ;
};
struct XVCreateRectangleRegionOut
{
    XVRegion                                outRegion            ;
    XVRectangle2D                           outAlignedRectangle  ;
};

/// <summary>Creates a frame-shaped region with given parameters.</summary>
/// <param name="inRectangleAlignment">Adjusts the rectangle to the position of the inspected object. Default value: atl::NIL.</param>
/// <param name="inBorderWidth">Default value: 1.0f.</param>
/// <param name="inBorderPosition">Default value: Centered.</param>
/// <param name="inFrameWidth">Width of the created region's frame.</param>
/// <param name="inFrameHeight">Height of the created region's frame.</param>
/// <param name="outRegion">Output region.</param>
/// <param name="outAlignedRectangle">The input rectangle transformed to the absolute coordinate system.</param>
struct XVCreateRectangleBorderRegionIn
{
    XVRectangle2D                           inRectangle          ;
    XVCoordinateSystem2D                   	inRectangleAlignment ;
    float                                   inBorderWidth        ;
    XVBorderPosition::Type                  inBorderPosition     ;
    int                                     inFrameWidth         ;
    int                                     inFrameHeight        ;
};
typedef XVCreateRectangleRegionOut XVCreateRectangleBorderRegionOut;


/// <summary>Creates a segment region.</summary>
/// <param name="inWidth">Segment width.</param>
/// <param name="inRound">Make ends of segment round.</param>
/// <param name="outRegion">Output region.</param>
struct XVCreateSegmentRegionIn
{
    XVSegment2D                                     inSegment          ;
    XVCoordinateSystem2D                            inSegmentAlignment ;
    int												inWidth            ;
    int												inFrameWidth       ;
    int												inFrameHeight      ;
    bool											inRound            ;
};
struct XVCreateSegmentRegionOut
{
    XVRegion    									outRegion          ;
    XVSegment2D                   					outAlignedSegment  ;
};

/// <summary>Creates a line region.</summary>
/// <param name="inWidth">Width of output region line.</param>
/// <param name="outRegion">Output region.</param>
struct XVCreateLineRegionIn
{
    XVLine2D                                        inLine          ;
    XVCoordinateSystem2D                            inLineAlignment ;
    int												inWidth         ;
    int												inFrameWidth    ;
    int												inFrameHeight   ;
};
struct XVCreateLineRegionOut
{
    XVRegion    									outRegion       ;
    XVLine2D                   						outAlignedLine  ;
};

/// <summary>Changes the width and the height of a region's frame {but does not rescale the content};.</summary>
/// <param name="inWidth">New frame width.</param>
/// <param name="inHeight">New frame height.</param>
struct XVSetRegionFrameIn
{
    XVRegion    		inRegion ;
    int					inWidth  ;
    int					inHeight ;
};
typedef RegionOut XVSetRegionFrameOut;

/// <summary>Returns the width and height of the entire region's frame {not to be confused with RegionBoundingBox!};</summary>
/// <param name="inRegion">Input region.</param>
typedef RegionIn XVGetRegionFrameIn;
struct XVGetRegionFrameOut
{
    int 				outFrameWidth  ;
    int 				outFrameHeight ;
};

/// <summary>Converts a closed path to region of interest.</summary>
/// <param name="inPath">Input path.</param>
struct XVPathToRegionOfInterestIn
{
    XVPath    				inPath              ;
};
struct XVPathToRegionOfInterestOut
{
    XVRegionOfInterest    	outRegionOfInterest ;
};

/// <summary>Converts a region of interest to a region with automatically computed frame.</summary>
/// <param name="outRegion">Output region.</param>
struct XVRegionOfInterestToRegionIn
{
    XVRegionOfInterest    	inRegionOfInterest ;
};
typedef RegionOut XVRegionOfInterestToRegionOut;

/// <summary>Returns a characteristic point of the input's region bounding box.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inPointAnchor">Default value: TopLeft.</param>
struct XVRegionCharacteristicPointIn
{
    XVRegion    			inRegion      ;
    XVAnchor2D::Type        inPointAnchor ;
};
struct XVRegionCharacteristicPointOut
{
    XVPoint2D    			outPoint      ;
};

/// <summary>If the input region contains at least one pixel then it is copied to the output; otherwise Nil is returned.</summary>
/// <param name="inRegion">Input region.</param>
typedef RegionIn XVSkipEmptyRegionIn;
struct XVSkipEmptyRegionOut
{
    XVRegion                      	outNotEmptyRegion ;
    bool 							outIsNotEmpty     ;
};


/// <summary>Saves serialized Region object as avdata file.</summary>
/// <param name="inRegion">Region to be serialized.</param>
/// <param name="inFilename">Name of the target file.</param>
struct XVSaveRegionIn
{
    XVRegion            inRegion   ;
    XVFile              inFilename ;
};


/// <summary>Loads serialized Region object from avdata file.</summary>
/// <param name="inFilename">Name of the source file.</param>
/// <param name="outRegion">Deserialized output Region.</param>
struct XVLoadRegionIn
{
    XVFile              inFilename ;
};
typedef RegionOut XVLoadRegionOut;



MAKEDLL_API void XVCreateRegionOfInterestRegion(XVCreateRegionOfInterestRegionIn &in, XVCreateRegionOfInterestRegionOut &out)throw(...);
MAKEDLL_API void XVCreateBoxRegion             (XVCreateBoxRegionIn              &in, XVCreateBoxRegionOut              &out)throw(...);
MAKEDLL_API void XVCreateBoxBorderRegion       (XVCreateBoxBorderRegionIn        &in, XVCreateBoxBorderRegionOut        &out)throw(...);
MAKEDLL_API void XVCreateEllipseRegion         (XVCreateEllipseRegionIn          &in, XVCreateEllipseRegionOut          &out)throw(...);
MAKEDLL_API void XVCreateRingRegion            (XVCreateRingRegionIn             &in, XVCreateRingRegionOut             &out)throw(...);
MAKEDLL_API void XVCreateCrossRegion           (XVCreateCrossRegionIn            &in, XVCreateCrossRegionOut            &out)throw(...);
MAKEDLL_API void XVCreateGridRegion            (XVCreateGridRegionIn             &in, XVCreateGridRegionOut             &out)throw(...);
MAKEDLL_API void XVCreateCircleRegion          (XVCreateCircleRegionIn           &in, XVCreateCircleRegionOut           &out)throw(...);
MAKEDLL_API void XVCreatePolygonRegion         (XVCreatePolygonRegionIn          &in, XVCreatePolygonRegionOut          &out)throw(...);
MAKEDLL_API void XVCreatePathBorderRegion      (XVCreatePathBorderRegionIn       &in, XVCreatePathBorderRegionOut       &out)throw(...);
MAKEDLL_API void XVCreateRectangleRegion       (XVCreateRectangleRegionIn        &in, XVCreateRectangleRegionOut        &out)throw(...);
MAKEDLL_API void XVCreateRectangleBorderRegion (XVCreateRectangleBorderRegionIn  &in, XVCreateRectangleBorderRegionOut  &out)throw(...);
MAKEDLL_API void XVCreateSegmentRegion         (XVCreateSegmentRegionIn          &in, XVCreateSegmentRegionOut          &out)throw(...);
MAKEDLL_API void XVCreateLineRegion            (XVCreateLineRegionIn             &in, XVCreateLineRegionOut             &out)throw(...);
MAKEDLL_API void XVSetRegionFrame              (XVSetRegionFrameIn               &in, XVSetRegionFrameOut               &out)throw(...);
MAKEDLL_API void XVGetRegionFrame              (XVGetRegionFrameIn               &in, XVGetRegionFrameOut               &out)throw(...);
MAKEDLL_API void XVPathToRegionOfInterest      (XVPathToRegionOfInterestIn       &in, XVPathToRegionOfInterestOut       &out)throw(...);
MAKEDLL_API void XVRegionOfInterestToRegion    (XVRegionOfInterestToRegionIn     &in, XVRegionOfInterestToRegionOut     &out)throw(...);
MAKEDLL_API void XVRegionCharacteristicPoint   (XVRegionCharacteristicPointIn    &in, XVRegionCharacteristicPointOut    &out)throw(...);
MAKEDLL_API void XVSkipEmptyRegion             (XVSkipEmptyRegionIn              &in, XVSkipEmptyRegionOut              &out)throw(...);
MAKEDLL_API void XVSaveRegion                  (XVSaveRegionIn                   &in                                        )throw(...);
MAKEDLL_API void XVLoadRegion                  (XVLoadRegionIn                   &in, XVLoadRegionOut                   &out)throw(...);

#endif // XVCREATEREGION_H
