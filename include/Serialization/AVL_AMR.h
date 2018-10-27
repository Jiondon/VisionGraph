//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_AMR_H
#define AVL_AMR_H

#include "ATL/Utils.h"
#include "ATL/AtlTypes.h"
#include "ATL/Array.hxx"
#include "ATL/Optional.h"
#include "ATL/AtlIo.h"
#include "ATL/BinaryWriter.hxx"
#include "AVL_AMR_Common.h"
#include "AVL_AMR_BasicTypes.h"
#include "AVL_AMR_Generated.h"
#include "AMRSharedLibrary.h"

namespace avl
{
	class RegionOfInterest;
}

namespace avs
{
	AMR_PUBLIC void ReadData(atl::BinaryReader& reader, avl::RegionOfInterest& outRegionOfInterest);
	AMR_PUBLIC void WriteData(atl::BinaryWriter& writer, const avl::RegionOfInterest& inRegionOfInterest);

	//
	// Enum trivial serialization
	//
	template <typename T>
	typename atl::enable_if<std::is_enum<T>::value>::type
	ReadData( atl::BinaryReader& reader, T& outValue)
	{
		outValue = static_cast<T>(reader.ReadI32());
	}

	template <typename T>
	typename atl::enable_if<std::is_enum<T>::value>::type
	WriteData( atl::BinaryWriter& writer, T inValue)
	{
		writer.WriteI32( static_cast<int>(inValue) );
	}

	template <typename T>
	void ReadDataDirect( atl::BinaryReader& reader, T& outValue )
	{
		outValue = *static_cast<T*>(reader.ReadBinary( sizeof(T) ));
	}

	template <typename T>
	void WriteDataDirect( atl::BinaryWriter& writer, const T& inValue )
	{
		writer.WriteBinary( &inValue, sizeof(T) );
	}

	template <typename T>
	typename atl::enable_if<has_trivial_serialization<T>::value>::type
	ReadData( atl::BinaryReader& reader, T& outValue )
	{
		ReadDataDirect( reader, outValue );
	}

	template <typename T>
	typename atl::enable_if<has_trivial_serialization<T>::value>::type
	WriteData( atl::BinaryWriter& writer, const T& inValue )
	{
		WriteDataDirect( writer, inValue );
	}


	//
	// Explicit serializations
	//
	AMR_PUBLIC void ReadData ( atl::BinaryReader& reader, atl::Array<int>& outInts );
	AMR_PUBLIC void WriteData( atl::BinaryWriter& writer, const atl::Array<int>& inInts );

	AMR_PUBLIC void ReadData ( atl::BinaryReader& reader, atl::Array<float>& outFloats );
	AMR_PUBLIC void WriteData( atl::BinaryWriter& writer, const atl::Array<float>& inFloats );

	AMR_PUBLIC void ReadData ( atl::BinaryReader& reader, atl::String& outValue );
	AMR_PUBLIC void WriteData( atl::BinaryWriter& writer, const atl::String& inValue );

	//
	// Arrays serialization
	//

	// Specific ReadArrayData[Direct] forward declarations
	// for example atl::Array<atl::Array<T>> needs this at instantiation

	template <typename T>
	void ReadArrayData( atl::BinaryReader& reader, atl::Array< T >& outArray );
	template <typename T>
	void WriteArrayData( atl::BinaryWriter& writer, const atl::Array< T >& inArray );
	template <typename T>
	void ReadArrayDataDirect( atl::BinaryReader& reader, atl::Array<T>& outArray );
	template <typename T>
	void WriteArrayDataDirect( atl::BinaryWriter& writer, const atl::Array<T>& inArray );

	// ReadData templates, can be used internally by ReadArrayData[Direct]

	template<typename T>
	typename atl::enable_if_not<has_trivial_serialization<T>::value>::type
	ReadData( atl::BinaryReader& reader, atl::Array<T>& outValue )
	{
		ReadArrayData( reader, outValue );
	}

	template<typename T>
	typename atl::enable_if_not<has_trivial_serialization<T>::value>::type
	WriteData( atl::BinaryWriter& writer, const atl::Array<T>& inValue)
	{
		WriteArrayData( writer, inValue);
	}

	template <typename T>
	typename atl::enable_if<has_trivial_serialization<T>::value>::type
	ReadData( atl::BinaryReader& reader, atl::Array<T>& outValue )
	{
		ReadArrayDataDirect( reader, outValue );
	}

	template <typename T>
	typename atl::enable_if<has_trivial_serialization<T>::value>::type
	WriteData( atl::BinaryWriter& writer, const atl::Array<T>& inValue )
	{
		WriteArrayDataDirect( writer, inValue );
	}

	// Specific ReadArrayData[Direct] definitions

	template <typename T>
	void ReadArrayData( atl::BinaryReader& reader, atl::Array< T >& outArray )
	{
		int count = reader.ReadI32();
		outArray.Reset(count);

		for (int i = 0; i < count; ++i)
			ReadData( reader, outArray[i] );
	}

	template <typename T>
	void WriteArrayData( atl::BinaryWriter& writer, const atl::Array< T >& inArray )
	{
		int count = inArray.Size();
		writer.WriteI32( count );

		for (int i = 0; i < count; ++i)
			WriteData( writer, inArray[i] );
	}

	template <typename T>
	void ReadArrayDataDirect( atl::BinaryReader& reader, atl::Array<T>& outArray )
	{
		int	count = reader.ReadI32();
		T* data = static_cast<T*>(reader.ReadBinary(count * sizeof(T)));

		bool isExternal = reader.GetMode() == atl::EXTERNAL;
		if (isExternal)
		{
			outArray.Reset();
			outArray.Insert( data, data + count );
		}
		else
		{
			outArray.Reset( count, data, false );
		}
	}

	template <typename T>
	void WriteArrayDataDirect( atl::BinaryWriter& writer, const atl::Array<T>& inArray )
	{
		int count = inArray.Size();

		writer.WriteI32( count );
		writer.WriteBinary( inArray.Begin(), count * sizeof(T) );
	}


	//
	// Optional and Conditional data serialization
	//
	template <typename T>
	void ReadData( atl::BinaryReader& reader, atl::Optional<T>& outValue )
	{
		int flag = reader.ReadI32();
		if (flag != 0)
		{
			if (outValue == atl::NIL)
				outValue = T();

			ReadData( reader, outValue.Get() );
		}
		else
		{
			outValue = atl::NIL;
		}
	}

	template <typename T>
	void WriteData( atl::BinaryWriter& writer, const atl::Optional<T>& inValue )
	{
		if (inValue != atl::NIL)
		{
			writer.WriteBool(true);
			WriteData( writer, inValue.Get() );
		}
		else
		{
			writer.WriteBool(false);
		}
	}

	template <typename T>
	void ReadData( atl::BinaryReader& reader, atl::Conditional<T>& outValue )
	{
		int flag = reader.ReadI32();
		if (flag != 0)
		{
			if (outValue == atl::NIL)
				outValue = T();

			ReadData( reader, outValue.Get() );
		}
		else
		{
			outValue = atl::NIL;
		}
	}

	template <typename T>
	void WriteData( atl::BinaryWriter& writer, const atl::Conditional<T>& inValue )
	{
		if (inValue != atl::NIL)
		{
			writer.WriteBool(true);
			WriteData( writer, inValue.Get() );
		}
		else
		{
			writer.WriteBool(false);
		}
	}

}

#endif
