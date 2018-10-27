//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_DATA_WRITER_HELPER_H
#define AVL_DATA_WRITER_HELPER_H

#include "ATL/AtlString.h"
#include "ATL/Array.h"
#include "ATL/AtlIo.h"
#include "AVLCommon/Config.h"


namespace avs {
namespace SerializationInternal {

	struct AvlSerializationWriteHelper;
	struct AvlSerializationReadHelper;

	AVL_FUNCTION void InitAvlSerializationWriteHelper( AvlSerializationWriteHelper& object, atl::Array<atl::byte>& buffer );
	AVL_FUNCTION void DestructAvlSerializationWriteHelper( AvlSerializationWriteHelper& object );
	AVL_FUNCTION void InitAvlSerializationReadHelper( AvlSerializationReadHelper& object, const atl::Array<atl::byte>& buffer );
	AVL_FUNCTION void DestructAvlSerializationReadHelper( AvlSerializationReadHelper& object );

	struct AvlSerializationWriteHelper
	{
		atl::BinaryWriter* pWriter;

		AvlSerializationWriteHelper()
		: pWriter(0)
		{
		}

		~AvlSerializationWriteHelper()
		{
			DestructAvlSerializationWriteHelper(*this);
		}
	};

	struct AvlSerializationReadHelper
	{
		atl::BinaryReader* pReader;

		AvlSerializationReadHelper()
		: pReader(0)
		{
		}

		~AvlSerializationReadHelper()
		{
			DestructAvlSerializationReadHelper(*this);
		}
	};


	AVL_FUNCTION void AvlSerializationLoadAvData( const atl::String& filePath, const atl::String& expectedType, atl::Array<atl::byte>& buffer );
	AVL_FUNCTION void AvlSerializationSaveAvData( const atl::String& filePath, const atl::String& typeName, const atl::Array<atl::byte>& buffer );


} // namespace SerializationInternal
} // namespace avs

#endif // AVL_DATA_WRITER_HELPER_H
