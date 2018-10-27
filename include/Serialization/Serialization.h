//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#ifndef AVL_SERIALIZATION_H
#define AVL_SERIALIZATION_H

#include "ATL/AtlString.h"
#include "ATL/Array.hxx"
#include "AVLCommon/Enums/StreamMode.h"
#include "SerializationHelper.h"
#include "AVL_AMR.h"

namespace avs
{
	template<typename T>
	void ReadDataFromMemory( const atl::Array<atl::byte>& data, T& outObject )
	{
		SerializationInternal::AvlSerializationReadHelper helper;
		SerializationInternal::InitAvlSerializationReadHelper(helper, data);

		ReadData( *(helper.pReader), outObject );
	}


	template<typename T>
	void SaveDataToMemory( atl::Array<atl::byte>& buffer, const T& object )
	{
		SerializationInternal::AvlSerializationWriteHelper helper;
		SerializationInternal::InitAvlSerializationWriteHelper(helper, buffer);

		WriteData( *(helper.pWriter), object );
	}


	template<typename T>
	void ReadDataFromFile( const atl::String& filePath, const atl::String& typeName, T& outObject )
	{
		atl::Array<atl::byte> buffer;
		SerializationInternal::AvlSerializationLoadAvData(filePath, typeName, buffer);

		ReadDataFromMemory(buffer, outObject);
	}


	template<typename T>
	void SaveDataToFile( const atl::String& filePath, const atl::String& typeName, const T& object )
	{
		atl::Array<atl::byte> buffer;
		SaveDataToMemory(buffer, object);

		SerializationInternal::AvlSerializationSaveAvData(filePath, typeName, buffer);
	}


	template<typename T>
	void SaveObject
	(
		const T&				inObject,
		const atl::String&		inTypeName,
		const atl::String&		inFile,			//:Input file path.
		avl::StreamMode::Type	inStreamMode,
		bool					inIgnoreErrors

	)
	{
		if (inStreamMode != avl::StreamMode::Binary)
		{
			throw atl::DomainError(L"Not supported stream mode in SaveObject function.");
		}

		try
		{
			if (atl::IsFilePathWithoutExtension(inFile))
			{
				SaveDataToFile<T>(inFile + L".avdata", inTypeName, inObject);
			}
			else
			{
				SaveDataToFile<T>(inFile, inTypeName, inObject);
			}
		}
		catch(...)
		{
			if( inIgnoreErrors == false )
			{
				throw;
			}
		}
	}


	template<typename T>
	void LoadObject
	(
		const atl::String&		inFile,			//:Input file path.
		avl::StreamMode::Type	inStreamMode,
		const atl::String&		inTypeName,
		T&						outObject
	)
	{
		if (inStreamMode != avl::StreamMode::Binary)
		{
			throw atl::DomainError(L"Not supported stream mode in LoadObject function.");
		}

		ReadDataFromFile<T>(inFile, inTypeName, outObject);
	}
}

#endif // AVL_SERIALIZATION_H
