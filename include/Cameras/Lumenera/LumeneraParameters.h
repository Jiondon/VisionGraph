//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#pragma once
#include "ATL/AtlTypes.h"
#include "ATL/Optional.h"
#include "Basic/Types.h"

namespace avl {

namespace LumeneraPixelFormat
{
	enum Type
	{
		MONO8,
		MONO16,
		RGB8,
		RGB16,
	};
}

namespace LumeneraProperties
{
	enum Type
	{
		EXPOSURE = 50,
		GAIN = 51,
		GAIN_RED = 52,
		GAIN_GREEN1 = 53,
		GAIN_GREEN2 = 54,
		GAIN_BLUE = 55,
	};
}

struct LumeneraImageFormatParams
{
	LumeneraImageFormatParams()
		: pixelFormat(atl::NIL)
		, aoi(atl::NIL)
		, binningX(false)
		, sSBinX(atl::NIL)
		, binningY(false)
		, sSBinY(atl::NIL)
	{}

	LumeneraImageFormatParams(
		atl::Optional<avl::LumeneraPixelFormat::Type> _pixelFormat,
		atl::Optional<avl::Box> _aoi,
		bool _binningX,
		atl::Optional<int> _SSBinX,
		bool _binningY,
		atl::Optional<int> _SSBinY
	)
		: pixelFormat(_pixelFormat)
		, aoi(_aoi)
		, binningX(_binningX)
		, sSBinX(_SSBinX)
		, binningY(_binningY)
		, sSBinY(_SSBinY)
	{
	}

	atl::Optional<avl::LumeneraPixelFormat::Type> PixelFormat(void)	const { return pixelFormat; }
	atl::Optional<avl::Box> Aoi(void)								const { return aoi; }
	bool BinningX(void)												const { return binningX; }
	atl::Optional<int> SSBinX(void)									const { return sSBinX; }
	bool BinningY(void)												const { return binningY; }
	atl::Optional<int> SSBinY(void)									const { return sSBinY; }


	bool operator == (const avl::LumeneraImageFormatParams& rhs) const
	{
		return pixelFormat == rhs.pixelFormat && aoi == rhs.aoi && binningX == rhs.binningX && sSBinX == rhs.sSBinX && binningY == rhs.binningY && sSBinY == rhs.sSBinY;
	}

	bool operator != (const avl::LumeneraImageFormatParams& rhs) const
	{
		return !(operator==(rhs));
	}

	atl::Optional<avl::LumeneraPixelFormat::Type> pixelFormat;
	atl::Optional<avl::Box> aoi;
	bool binningX;
	atl::Optional<int> sSBinX;
	bool binningY;
	atl::Optional<int> sSBinY;
};

struct LumeneraAcquisitionControlParams
{
	LumeneraAcquisitionControlParams()
		: hWTrigger(false)
		, gain(atl::NIL)
		, exposure(atl::NIL)
	{}

	LumeneraAcquisitionControlParams(
		bool _hWTrigger,
		atl::Optional<float> _gain,
		atl::Optional<float> _exposure,
		atl::Optional<int> _bufferSize
	)
		: hWTrigger(_hWTrigger)
		, gain(_gain)
		, exposure(_exposure)
		, bufferSize(_bufferSize)
	{}

	bool HWTrigger(void)									const { return hWTrigger; }
	atl::Optional<float> Gain(void)							const { return gain; }
	atl::Optional<float> Exposure(void)						const { return exposure; }
	atl::Optional<int> BufferSize(void)						const { return bufferSize; }

	bool operator == (const avl::LumeneraAcquisitionControlParams& rhs) const
	{
		return hWTrigger == rhs.hWTrigger && gain == rhs.gain && exposure == rhs.exposure && bufferSize == rhs.bufferSize;
	}

	bool operator != (const avl::LumeneraAcquisitionControlParams& rhs) const
	{
		return !(operator==(rhs));
	}

	bool	hWTrigger;
	atl::Optional<float> gain;
	atl::Optional<float> exposure;
	atl::Optional<int> bufferSize;
};

}
