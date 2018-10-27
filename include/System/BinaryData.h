//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_BINARYDATA_H
#define AVL_BINARYDATA_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Optional.h"
#include "ATL/AtlString.h"
#include "ATL/Array.h"
#include "System/ByteBuffer.h"
#include "System/FileAccessMode.h"

namespace avl
{



	namespace IntegerBinaryFormat
	{
		enum Type
		{
			Signed_8Bit,
			Signed_16Bit_LittleEndian,
			Signed_32Bit_LittleEndian,
			Signed_64Bit_LittleEndian,
			Unsigned_8Bit,
			Unsigned_16Bit_LittleEndian,
			Unsigned_32Bit_LittleEndian,
			Unsigned_64Bit_LittleEndian,
			Signed_16Bit_BigEndian,
			Signed_32Bit_BigEndian,
			Signed_64Bit_BigEndian,
			Unsigned_16Bit_BigEndian,
			Unsigned_32Bit_BigEndian,
			Unsigned_64Bit_BigEndian,
		};
	}

	namespace RealBinaryFormat
	{
		enum Type
		{
			SinglePrecision_32Bit_LittleEndian,
			DoublePrecision_64Bit_LittleEndian,
			SinglePrecision_32Bit_BigEndian,
			DoublePrecision_64Bit_BigEndian,
		};
	}

	namespace StringBinaryFormat
	{
		enum Type
		{
			VariableLength_Raw,
			VariableLength_NullTerminated,
			VariableLength_8BitPrefix,
			VariableLength_16BitLEPrefix,
			VariableLength_32BitLEPrefix,
			VariableLength_16BitBEPrefix,
			VariableLength_32BitBEPrefix,
			VariableLength_LEB128Prefix,
			FixedLength_Raw,
			FixedLength_NullTerminated,
		};
	}

	namespace StringEncodingFormat
	{
		enum Type
		{
			ASCII,
			UTF8,
			UTF16LE,
			UTF16BE,
			ANSI,
			OEM,
		};
	}



	/// <summary>Converts integer value into specified binary representation and writes it to a byte buffer.</summary>
	/// <param name="inBuffer">Initial buffer to be expanded.</param>
	/// <param name="inOffset">Write destination position. Default value: atl::NIL.</param>
	/// <param name="inValue">Value to be written.</param>
	/// <param name="inFormat">Binary serialization format of integer data. Default value: Signed_32Bit_LittleEndian.</param>
	/// <param name="outBuffer">Resulting data.</param>
	AVL_FUNCTION void WriteIntegerToBuffer
	(
		const avl::ByteBuffer&			inBuffer,		
		atl::Optional<int>				inOffset,		
		int								inValue,		
		avl::IntegerBinaryFormat::Type	inFormat,		
		avl::ByteBuffer&				outBuffer		
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads integer value in specified binary format from a byte buffer.</summary>
	/// <param name="inBuffer">Source data.</param>
	/// <param name="inOffset">Read start position. Default value: 0.</param>
	/// <param name="inFormat">Binary serialization format of integer data. Default value: Signed_32Bit_LittleEndian.</param>
	/// <param name="inCheckRange">Verify if read data can be stored in resulting Integer type. Default value: True.</param>
	/// <param name="outValue">Read value.</param>
	/// <param name="outOffset">Resulting position behind read data.</param>
	AVL_FUNCTION void ReadIntegerFromBuffer
	(
		const avl::ByteBuffer&			inBuffer,		
		int								inOffset,		
		avl::IntegerBinaryFormat::Type	inFormat,		
		bool							inCheckRange,	
		int&							outValue,		
		int&							outOffset		
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts boolean value into specified integer binary representation and writes it to a byte buffer.</summary>
	/// <param name="inBuffer">Initial buffer to be expanded.</param>
	/// <param name="inOffset">Write destination position. Default value: atl::NIL.</param>
	/// <param name="inValue">Value to be written.</param>
	/// <param name="inFormat">Binary serialization format of integer data. Default value: Signed_32Bit_LittleEndian.</param>
	/// <param name="inTrueValue">Integer value representing True. Default value: 1.</param>
	/// <param name="inFalseValue">Integer value representing False. Default value: 0.</param>
	/// <param name="outBuffer">Resulting data.</param>
	AVL_FUNCTION void WriteBoolToBuffer
	(
		const avl::ByteBuffer&			inBuffer,		
		atl::Optional<int>				inOffset,		
		bool							inValue,		
		avl::IntegerBinaryFormat::Type	inFormat,		
		int								inTrueValue,	
		int								inFalseValue,	
		avl::ByteBuffer&				outBuffer		
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads boolean value in specified binary format from byte buffer.</summary>
	/// <param name="inBuffer">Source data.</param>
	/// <param name="inOffset">Read start position. Default value: 0.</param>
	/// <param name="inFormat">Binary serialization format of integer data. Default value: Signed_32Bit_LittleEndian.</param>
	/// <param name="outValue">Read value.</param>
	/// <param name="outOffset">Resulting position behind read data.</param>
	AVL_FUNCTION void ReadBoolFromBuffer
	(
		const avl::ByteBuffer&			inBuffer,		
		int								inOffset,		
		avl::IntegerBinaryFormat::Type	inFormat,		
		bool&							outValue,		
		int&							outOffset		
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts real value into specified binary representation and writes it to a byte buffer.</summary>
	/// <param name="inBuffer">Initial buffer to be expanded.</param>
	/// <param name="inOffset">Write destination position. Default value: atl::NIL.</param>
	/// <param name="inValue">Value to be written.</param>
	/// <param name="inFormat">Binary serialization format of floating point data. Default value: SinglePrecision_32Bit_LittleEndian.0f.</param>
	/// <param name="outBuffer">Resulting data.</param>
	AVL_FUNCTION void WriteRealToBuffer
	(
		const avl::ByteBuffer&		inBuffer,		
		atl::Optional<int>			inOffset,		
		float						inValue,		
		avl::RealBinaryFormat::Type	inFormat,		
		avl::ByteBuffer&			outBuffer		
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts double value into specified binary representation and writes it to a byte buffer.</summary>
	/// <param name="inBuffer">Initial buffer to be expanded.</param>
	/// <param name="inOffset">Write destination position. Default value: atl::NIL.</param>
	/// <param name="inValue">Value to be written.</param>
	/// <param name="inFormat">Binary serialization format of floating point data. Default value: DoublePrecision_64Bit_LittleEndian.0f.</param>
	/// <param name="outBuffer">Resulting data.</param>
	AVL_FUNCTION void WriteDoubleToBuffer
	(
		const avl::ByteBuffer&		inBuffer,		
		atl::Optional<int>			inOffset,		
		double						inValue,		
		avl::RealBinaryFormat::Type	inFormat,		
		avl::ByteBuffer&			outBuffer		
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads real value in specified binary format from a byte buffer.</summary>
	/// <param name="inBuffer">Source data.</param>
	/// <param name="inOffset">Read start position. Default value: 0.</param>
	/// <param name="inFormat">Binary serialization format of floating point data. Default value: SinglePrecision_32Bit_LittleEndian.0f.</param>
	/// <param name="outValue">Read value.</param>
	/// <param name="outOffset">Resulting position behind read data.</param>
	AVL_FUNCTION void ReadRealFromBuffer
	(
		const avl::ByteBuffer&		inBuffer,		
		int							inOffset,		
		avl::RealBinaryFormat::Type	inFormat,		
		float&						outValue,		
		int&						outOffset		
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads double value in specified binary format from a byte buffer.</summary>
	/// <param name="inBuffer">Source data.</param>
	/// <param name="inOffset">Read start position. Default value: 0.</param>
	/// <param name="inFormat">Binary serialization format of floating point data. Default value: DoublePrecision_64Bit_LittleEndian.0f.</param>
	/// <param name="outValue">Read value.</param>
	/// <param name="outOffset">Resulting position behind read data.</param>
	AVL_FUNCTION void ReadDoubleFromBuffer
	(
		const avl::ByteBuffer&		inBuffer,		
		int							inOffset,		
		avl::RealBinaryFormat::Type	inFormat,		
		double&						outValue,		
		int&						outOffset		
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts string value into specified binary representation and writes it to a byte buffer.</summary>
	/// <param name="inBuffer">Initial buffer to be expanded.</param>
	/// <param name="inOffset">Write destination position. Default value: atl::NIL.</param>
	/// <param name="inValue">Value to be written.</param>
	/// <param name="inFormat">Binary serialization format responsible for handling string length. Default value: VariableLength_NullTerminated.</param>
	/// <param name="inTextEncoding">Binary character encoding format. Default value: UTF8.</param>
	/// <param name="inMaxLength">Maximum length of resulting string in code units. Default value: 32000.</param>
	/// <param name="outBuffer">Resulting data.</param>
	AVL_FUNCTION void WriteStringToBuffer
	(
		const avl::ByteBuffer&			inBuffer,			
		atl::Optional<int>				inOffset,			
		const atl::String&				inValue,			
		avl::StringBinaryFormat::Type	inFormat,			
		avl::StringEncodingFormat::Type inTextEncoding,		
		int								inMaxLength,		
		avl::ByteBuffer&				outBuffer			
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads string value in specified binary format from a byte buffer.</summary>
	/// <param name="inBuffer">Source data.</param>
	/// <param name="inOffset">Read start position.</param>
	/// <param name="inFormat">Binary serialization format responsible for handling string length. Default value: VariableLength_NullTerminated.</param>
	/// <param name="inTextEncoding">Binary character encoding format. Default value: UTF8.</param>
	/// <param name="inMaxLength">Maximum length of resulting string in code units. Default value: 32000.</param>
	/// <param name="outValue">Read value.</param>
	/// <param name="outOffset">Resulting position behind read data.</param>
	AVL_FUNCTION void ReadStringFromBuffer
	(
		const avl::ByteBuffer&			inBuffer,			
		int								inOffset,			
		avl::StringBinaryFormat::Type	inFormat,			
		avl::StringEncodingFormat::Type inTextEncoding,		
		int								inMaxLength,		
		atl::String&					outValue,			
		int&							outOffset			
	)
	THROW_AVL_ERRORS;

	/// <summary>Writes content of a source byte buffer into other byte buffer.</summary>
	/// <param name="inBuffer">Initial buffer to be expanded.</param>
	/// <param name="inOffset">Write destination position. Default value: atl::NIL.</param>
	/// <param name="inSourceBuffer">Buffer containing source data to be copied.</param>
	/// <param name="inSourceOffset">Copy start position in source data. Default value: 0.</param>
	/// <param name="inSourceLength">Length of data to be copied in bytes. Default value: atl::NIL.</param>
	/// <param name="outBuffer">Resulting data.</param>
	AVL_FUNCTION void WriteBufferToBuffer
	(
		const avl::ByteBuffer&	inBuffer,			
		atl::Optional<int>		inOffset,			
		const avl::ByteBuffer&	inSourceBuffer,		
		int						inSourceOffset,		
		atl::Optional<int>		inSourceLength,		
		avl::ByteBuffer&		outBuffer			
	)
	THROW_AVL_ERRORS;

	/// <summary>Writes connected content of all source buffer array items into other byte buffer.</summary>
	/// <param name="inBuffer">Initial buffer to be expanded.</param>
	/// <param name="inOffset">Write destination position. Default value: 0.</param>
	/// <param name="inSourceBuffers">Buffers with source data to be copied.</param>
	/// <param name="outBuffer">Resulting data.</param>
	AVL_FUNCTION void WriteBufferArrayToBuffer
	(
		const avl::ByteBuffer&				inBuffer,			
		atl::Optional<int>					inOffset,			
		const atl::Array<avl::ByteBuffer>&	inSourceBuffers,	
		avl::ByteBuffer&					outBuffer			
	)
	THROW_AVL_ERRORS;

	/// <summary>Splits chunk of data from byte buffer into array of buffers of equal sizes.</summary>
	/// <param name="inBuffer">Source data.</param>
	/// <param name="inOffset">Read start position. Default value: 0.</param>
	/// <param name="inElementSize">Length in bytes of single array element. Default value: 4.</param>
	/// <param name="inElementsCount">Amount of array elements to read. Default value: 0.</param>
	/// <param name="outArray">Buffers array with copied data.</param>
	/// <param name="outOffset">Resulting position behind read data.</param>
	AVL_FUNCTION void ReadBufferArrayFromBuffer
	(
		const avl::ByteBuffer&			inBuffer,			
		int								inOffset,			
		int								inElementSize,		
		int								inElementsCount,	
		atl::Array<avl::ByteBuffer>&	outArray,			
		int&							outOffset			
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts an array of integer values into specified binary representation and writes it to a byte buffer.</summary>
	/// <param name="inBuffer">Initial buffer to be expanded.</param>
	/// <param name="inOffset">Write destination position. Default value: atl::NIL.</param>
	/// <param name="inArray">Values array to be written.</param>
	/// <param name="inFormat">Binary serialization format of integer data. Default value: Signed_32Bit_LittleEndian.</param>
	/// <param name="outBuffer">Resulting data.</param>
	AVL_FUNCTION void WriteIntegerArrayToBuffer
	(
		const avl::ByteBuffer&			inBuffer,		
		atl::Optional<int>				inOffset,		
		const atl::Array<int>&			inArray,		
		avl::IntegerBinaryFormat::Type	inFormat,		
		avl::ByteBuffer&				outBuffer		
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads an array of integer values in specified binary format from a byte buffer.</summary>
	/// <param name="inBuffer">Source data.</param>
	/// <param name="inOffset">Read start position. Default value: 0.</param>
	/// <param name="inArraySize">Number of elements to read into array. Default value: 1.</param>
	/// <param name="inFormat">Binary serialization format of integer data. Default value: Signed_32Bit_LittleEndian.</param>
	/// <param name="inCheckRange">Verify if read data can be stored in resulting Integer type. Default value: True.</param>
	/// <param name="outArray">Array of read values.</param>
	/// <param name="outOffset">Resulting position behind read data.</param>
	AVL_FUNCTION void ReadIntegerArrayFromBuffer
	(
		const avl::ByteBuffer&			inBuffer,		
		int								inOffset,		
		int								inArraySize,	
		avl::IntegerBinaryFormat::Type	inFormat,		
		bool							inCheckRange,	
		atl::Array<int>&				outArray,		
		int&							outOffset		
	)
	THROW_AVL_ERRORS;

	/// <summary>Writes bytes from a byte buffer to a file.</summary>
	/// <param name="inFileAccessMode">Default value: CreateOrErase.</param>
	AVL_FUNCTION void SaveBuffer
	(
		const avl::ByteBuffer&		inBuffer,
		avl::FileAccessMode::Type	inFileAccessMode,
		const atl::File&			inFile,
		bool						inIgnoreErrors
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads bytes from a file and returns them as a bytes buffer.</summary>
	AVL_FUNCTION void LoadBuffer
	(
		const atl::File&	inFile,
		avl::ByteBuffer&	outBuffer
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_BINARYDATA_H

