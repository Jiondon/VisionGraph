
#pragma once
#ifndef AVL_QT_H
#define AVL_QT_H

#include "Image/Image.h"
#include "Image/ImageConversions.h"

#include <QImage>

namespace avl
{

	inline void QImageToAvlImage(const QImage& inQImage, avl::Image& outImage)
	{
		bool needConvert = (inQImage.format() != QImage::Format_RGB888) && (inQImage.format() != QImage::Format_ARGB32);
		const QImage& image = needConvert ? inQImage.convertToFormat(QImage::Format_RGB888) : inQImage;
		int depth = image.format() == QImage::Format_RGB888 ? 3 : 4;
		outImage.Reset(image.width(), image.height(), avl::PlainType::UInt8, depth, atl::NIL);

		for (int i = 0; i < outImage.Height(); ++i)
		{
			memcpy(outImage.RowBegin<atl::uint8>(i), image.scanLine(i), outImage.Width() * depth);
		}
	}

	inline void QImageToAvlImage_Linked(QImage& inQImage, avl::Image& outImage)
	{
		if (inQImage.format() == QImage::Format_RGB888 || inQImage.format() == QImage::Format_ARGB32)
		{
			int depth = inQImage.format() == QImage::Format_RGB888 ? 3 : 4;
			outImage.Reset(inQImage.width(), inQImage.height(), inQImage.bytesPerLine(), avl::PlainType::UInt8, depth, inQImage.bits());
		}
		else
		{
			throw atl::DomainError("Unsupported QImage format in function QImageToAvlImage_Linked");
		}
	}

	inline void AvlImageToQImage(const avl::Image& inImage, QImage& outImage)
	{
		if (inImage.Depth() != 1 && inImage.Depth() != 3)
		{
			throw atl::DomainError(L"Unsupported image depth");
		}

		const avl::PlainType::Type originalType = inImage.Format().type;

		avl::Image tmpImage;
		if (originalType != avl::PlainType::UInt8)
		{
			avl::ConvertPixelType(inImage, atl::NIL, avl::PlainType::UInt8, 0, tmpImage);
		}

		const avl::Image& toConvert = originalType == avl::PlainType::UInt8 ? inImage : tmpImage;

		const QImage::Format format = toConvert.Depth() == 3 ? QImage::Format_RGB888 : QImage::Format_Grayscale8;
		outImage = QImage(toConvert.Width(), toConvert.Height(), format);
		const int lineSize = inImage.Width() * inImage.PixelSize();

		for (int i = 0; i < inImage.Height(); ++i)
		{
			memcpy(outImage.scanLine(i), inImage.RowBegin<atl::uint8>(i), lineSize);
		}
	}

	inline void AvlImageToQImage_Linked(const avl::Image& inImage, QImage& outImage)
	{
		if (inImage.Depth() != 1 && inImage.Depth() != 3)
		{
			throw atl::DomainError(L"Unsupported image depth");
		}

		const avl::PlainType::Type imageType = inImage.Format().type;
		if (imageType != avl::PlainType::UInt8)
		{
			throw atl::DomainError(L"Unsupported image format");
		}

		QImage::Format format = inImage.Depth() == 3 ? QImage::Format_RGB888 : QImage::Format_Grayscale8;
		outImage = QImage((const uchar*)inImage.Data(), inImage.Width(), inImage.Height(), inImage.Pitch(), format);
	}

} // namespace avl

#endif // AVL_QT_H
