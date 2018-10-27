//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_AMR_BASIC_TYPES_H
#define AVL_AMR_BASIC_TYPES_H

#include "ATL/AtlTypes.h"
#include "ATL/AtlIo.h"
#include "AMRSharedLibrary.h"


// Forward declarations
namespace avl
{
	class Image;
}


namespace avs
{
	AMR_PUBLIC void ReadData ( atl::BinaryReader& reader, avl::Image& outImage );
	AMR_PUBLIC void WriteData( atl::BinaryWriter& writer, const avl::Image& inImage );

	// ----------------------------------------------------------------------------
	// Integer

	AMR_PUBLIC inline void ReadData(atl::BinaryReader& reader, int& outValue)
	{
		outValue = reader.ReadI32();
	}

	AMR_PUBLIC inline void WriteData(atl::BinaryWriter& writer, int inValue)
	{
		writer.WriteI32(inValue);
	}

	// ----------------------------------------------------------------------------
	// Uint64

	AMR_PUBLIC inline void ReadData(atl::BinaryReader& reader, atl::uint64& outValue)
	{
		outValue = reader.ReadI64();
	}

	AMR_PUBLIC inline void WriteData(atl::BinaryWriter& writer, atl::uint64 inValue)
	{
		writer.WriteI64(inValue);
	}

	// ----------------------------------------------------------------------------
	// Int64

	AMR_PUBLIC inline void ReadData(atl::BinaryReader& reader, atl::int64& outValue)
	{
		outValue = reader.ReadI64();
	}

	AMR_PUBLIC inline void WriteData(atl::BinaryWriter& writer, atl::int64 inValue)
	{
		writer.WriteI64(inValue);
	}

	// ----------------------------------------------------------------------------
	// Bool

	AMR_PUBLIC inline void WriteData(atl::BinaryWriter& writer, bool inValue)
	{
		writer.WriteBool(inValue);
	}

	AMR_PUBLIC inline void ReadData(atl::BinaryReader& reader, bool& outValue)
	{
		outValue = reader.ReadBool();
	}

	// ----------------------------------------------------------------------------
	// Real

	AMR_PUBLIC inline void ReadData(atl::BinaryReader& reader, float& outValue)
	{
		outValue = reader.ReadF32();
	}

	AMR_PUBLIC inline void WriteData(atl::BinaryWriter& writer, float inValue)
	{
		writer.WriteF32(inValue);
	}

	// ----------------------------------------------------------------------------
	// Double

	AMR_PUBLIC inline void ReadData(atl::BinaryReader& reader, double& outValue)
	{
		outValue = reader.ReadF64();
	}

	AMR_PUBLIC inline void WriteData(atl::BinaryWriter& writer, double inValue)
	{
		writer.WriteF64(inValue);
	}
}

#endif
