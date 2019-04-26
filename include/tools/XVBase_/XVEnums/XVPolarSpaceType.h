#ifndef XVPOLARSPACETYPE_H
#define XVPOLARSPACETYPE_H



namespace XVPolarSpaceType
{
///<summary>Decides which formula use to transform image. Parameters \(m\) and \(k\) are set to values which allow to fit source image in output image.</summary>
enum Type
{
    ///<summary>Polar space</summary>
    Polar,
    ///<summary>Log-Polar space</summary>
    LogPolar
};
}

#endif // XVPOLARSPACETYPE_H
