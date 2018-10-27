#pragma once
#ifndef AVL_OPENCV_H
#define AVL_OPENCV_H

#include <opencv2/core/core.hpp>
#include "Image/Image.h"
#include "Image/Pixel.hxx"

namespace avl
{

	inline int AvlTypeToOpenCVType(int avlDepth, PlainType::Type avlType)
	{
		switch (avlType)
		{
		case PlainType::UInt8:
			return CV_MAKETYPE(CV_8U, avlDepth);
		case PlainType::Int8:
			return CV_MAKETYPE(CV_8S, avlDepth);
		case PlainType::UInt16:
			return CV_MAKETYPE(CV_16U, avlDepth);
		case PlainType::Int16:
			return CV_MAKETYPE(CV_16S, avlDepth);
		case PlainType::Int32:
			return CV_MAKETYPE(CV_32S, avlDepth);
		case PlainType::Real:
			return CV_MAKETYPE(CV_32F, avlDepth);
		default:
			throw atl::DomainError(L"Unsupported image depth in conversion from AVL Image to OpenCV Mat.");
		}
	}

	inline PlainType::Type OpenCVTypeToAvlType(int cvType)
	{
		switch (cvType)
		{
		case CV_8U:
			return PlainType::UInt8;
		case CV_8S:
			return PlainType::Int8;
		case CV_16U:
			return PlainType::UInt16;
		case CV_16S:
			return PlainType::Int16;
		case CV_32S:
			return PlainType::Int32;
		case CV_32F:
			return PlainType::Real;
		case CV_64F:
			return PlainType::Real;
		default:
			throw atl::DomainError(L"Unsupported image depth in conversion from OpenCV Mat to AVL Image.");
		}
	}

	/// This function returns a cv::Mat instance pointing to avl::Image instance's owned memory.
	inline void AvlImageToCVMat_Linked(Image &inImageAvl, cv::Mat &outMatCv)
	{
		outMatCv = cv::Mat(inImageAvl.Height(), inImageAvl.Width(), AvlTypeToOpenCVType(inImageAvl.Depth(), inImageAvl.Type()), 
			inImageAvl.Data(), inImageAvl.Pitch());
	}

	/// This function returns a cv::Mat instance with its own memory and channels switched to BGR to properly display colors.
	inline void AvlImageToCVMat_Switched(const Image &inImageAvl, cv::Mat &outMatCv)
	{
		outMatCv = cv::Mat(inImageAvl.Height(), inImageAvl.Width(), AvlTypeToOpenCVType(inImageAvl.Depth(), inImageAvl.Type()));

		for (int y = 0; y < inImageAvl.Height(); ++y)
		{
			uchar *ptrCv = (uchar *)(outMatCv.data + y * outMatCv.step[0]);
			uchar *ptrAvl = (uchar *)(inImageAvl.RowBegin<Pixel1<atl::uint8> >(y));
			uchar *q = (uchar *)(inImageAvl.RowEnd<Pixel1<atl::uint8> >(y));

			for (; ptrAvl < q; ptrAvl += 3, ptrCv += 3)
			{
				ptrCv[0] = ptrAvl[2];
				ptrCv[1] = ptrAvl[1];
				ptrCv[2] = ptrAvl[0];
			}
		}
	}

	/// This function returns a cv::Mat instance with its own memory and channels left as RGB.
	inline void AvlImageToCVMat(const Image &inImageAvl, cv::Mat &outMatCv)
	{
		outMatCv = cv::Mat(inImageAvl.Height(), inImageAvl.Width(), AvlTypeToOpenCVType(inImageAvl.Depth(), inImageAvl.Type()));

		if ((int)outMatCv.step[0] == inImageAvl.Pitch())
		{
			memcpy(outMatCv.data, inImageAvl.Data(), inImageAvl.Height()*inImageAvl.Pitch());
		}
		else
		{
			for (int y = 0; y < inImageAvl.Height(); ++y)
			{
				uchar *ptrCv = (uchar *)(outMatCv.data + y * outMatCv.step[0]);
				uchar *ptrAvl = (uchar *)(inImageAvl.RowBegin<Pixel1<atl::uint8> >(y));
				uchar *q = (uchar *)(inImageAvl.RowEnd<Pixel1<atl::uint8> >(y));

				memcpy(ptrCv, ptrAvl, q-ptrAvl);
			}
		}
	}

	/// This function returns a avl::Image instance pointing to cv::Mat instance's owned memory.
	inline void CVMatToAvlImage_Linked(cv::Mat &inMatCv, Image &outImageAvl)
	{
		const PlainType::Type pixelType = OpenCVTypeToAvlType(inMatCv.depth());

		if (inMatCv.depth() == CV_64F)
			throw atl::DomainError(L"Unsupported image depth in linked conversion from OpenCV Mat to AVL Image.");

		outImageAvl.Reset(inMatCv.cols, inMatCv.rows, inMatCv.step[0] ,pixelType, inMatCv.channels(), inMatCv.data);
	}

	/// This function returns a avl::Image instance with its own memory and channels switched to RGB to properly display colors.
	inline void CVMatToAvlImage_Switched(const cv::Mat &inMatCv, avl::Image& outImageAvl)
	{
		const avl::PlainType::Type pixelType = OpenCVTypeToAvlType(inMatCv.depth());

		outImageAvl.Reset(inMatCv.cols, inMatCv.rows, pixelType, inMatCv.channels(), atl::NIL);

		if (inMatCv.depth() == CV_64F)
		{
			for (int y = 0; y < outImageAvl.Height(); ++y)
			{
				double *ptrCv = (double *)(inMatCv.data + y * inMatCv.step[0]);
				float *ptrAvl = (float *)(outImageAvl.RowBegin<avl::Pixel1<atl::uint8> >(y));
				float *q = (float *)(outImageAvl.RowEnd<avl::Pixel1<atl::uint8> >(y));

				for (; ptrAvl < q; ptrAvl += 3, ptrCv += 3)
				{
					ptrAvl[0] = (float)ptrCv[2];
					ptrAvl[1] = (float)ptrCv[1];
					ptrAvl[2] = (float)ptrCv[0];
				}
			}
		}
		else
		{
			for (int y = 0; y < outImageAvl.Height(); ++y)
			{
				uchar *ptrCv = (uchar *)(inMatCv.data + y * inMatCv.step[0]);
				uchar *ptrAvl = (uchar *)(outImageAvl.RowBegin<avl::Pixel1<atl::uint8> >(y));
				uchar *q = (uchar *)(outImageAvl.RowEnd<avl::Pixel1<atl::uint8> >(y));

				for (; ptrAvl < q; ptrAvl += 3, ptrCv += 3)
				{
					ptrAvl[0] = ptrCv[2];
					ptrAvl[1] = ptrCv[1];
					ptrAvl[2] = ptrCv[0];
				}
			}
		}
	}

	/// This function returns a avl::Image instance with its own memory and channels left as BGR.
	inline void CVMatToAvlImage(const cv::Mat &inMatCv, Image &outImageAvl)
	{
		const PlainType::Type pixelType = OpenCVTypeToAvlType(inMatCv.depth());

		outImageAvl.Reset(inMatCv.cols, inMatCv.rows, pixelType, inMatCv.channels(), atl::NIL);

		if (inMatCv.depth() == CV_64F)
		{
			for (int y = 0; y < outImageAvl.Height(); ++y)
			{
				double *ptrCv = (double *)(inMatCv.data + y * inMatCv.step[0]);
				float *ptrAvl = (float *)(outImageAvl.RowBegin<Pixel1<atl::uint8> >(y));
				float *q = (float *)(outImageAvl.RowEnd<Pixel1<atl::uint8> >(y));

				while (ptrAvl < q)
					*ptrAvl++ = (float)(*ptrCv++);
			}
		}
		else
		{
			if ((int)inMatCv.step[0] == outImageAvl.Pitch())
			{
				memcpy(outImageAvl.Data(), inMatCv.data, outImageAvl.Height() * outImageAvl.Pitch());
			}
			else
			{
				for (int y = 0; y < outImageAvl.Height(); ++y)
				{
					uchar *ptrCv = (uchar *)(inMatCv.data + y * inMatCv.step[0]);
					uchar *ptrAvl = (uchar *)(outImageAvl.RowBegin<Pixel1<atl::uint8> >(y));
					uchar *q = (uchar *)(outImageAvl.RowEnd<Pixel1<atl::uint8> >(y));

					memcpy(ptrAvl, ptrCv, q - ptrAvl);
				}
			}
		}
	}

} // namespace avl

#endif // AVL_OPENCV_H
