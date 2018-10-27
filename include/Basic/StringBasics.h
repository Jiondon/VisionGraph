//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVS_STRINGBASICS_H
#define AVS_STRINGBASICS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/AtlString.h"
#include "ATL/AtlTypes.h"
#include "ATL/Array.hxx"
#include "System/FileAccessMode.h"

namespace avl
{


	/// <summary>Returns the number of characters in a string.</summary>
	AVL_FUNCTION void StringLength
	(
		const atl::String&	inString,
		int&				outLength
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a string from a fragment of the input string.</summary>
	AVL_FUNCTION void Substring
	(
		const atl::String&			inString,
		const int					inStart,
		const atl::Optional<int>&	inLength,
		atl::String&				outSubstring
	)
	THROW_AVL_ERRORS;

	/// <summary>Removes a part of a string.</summary>
	/// <param name="inString">Input string.</param>
	/// <param name="inPosition">Index of first character to erase.</param>
	/// <param name="inLength">Length of erased substring.</param>
	/// <param name="outString">Output string.</param>
	AVL_FUNCTION void EraseString
	(
		const atl::String&	inString,	
		const int&			inPosition,	
		const int&			inLength,	
		atl::String&		outString	
	)
	THROW_AVL_ERRORS;

	/// <summary>Inserts a string into another one at the given position.</summary>
	AVL_FUNCTION void InsertToString
	(
		const atl::String&	inString,
		const atl::String&	inInsertedString,
		const int			inIndex,
		atl::String&		outString
	)
	THROW_AVL_ERRORS;

	/// <summary>Joins multiple strings into a single one.</summary>
	/// <param name="inPadString">String inserted between concatenated elements.</param>
	/// <param name="inPadAtBegin">Determines if inPadString will be inserted also before first element.</param>
	/// <param name="inPadAtEnd">Determines if inPadString will be inserted also after last element.</param>
	AVL_FUNCTION void ConcatenateStrings_OfArray
	(
		const atl::Array<atl::String>&	inStringArray,
		const atl::String&				inPadString,	
		const bool						inPadAtBegin,	
		const bool						inPadAtEnd,		
		atl::String&					outString
	)
	THROW_AVL_ERRORS;

	/// <summary>Checks whether the input string is earlier alphabetically than a reference string.</summary>
	AVL_FUNCTION void TestStringEarlierThan
	(
		const atl::String&	inString,
		const atl::String&	inReferenceString,
		const bool			inIgnoreCase,
		const bool			inTrimWhitespace,
		bool&				outIsEarlier
	)
	THROW_AVL_ERRORS;

	/// <summary>Compares two strings character by character.</summary>
	AVL_FUNCTION void TestStringEqualTo
	(
		const atl::String&	inString,
		const atl::String&	inReferenceString,
		const bool			inIgnoreCase,
		const bool			inTrimWhitespace,
		bool&				outIsEqual
	)
	THROW_AVL_ERRORS;

	/// <summary>Compares two strings character by character.</summary>
	AVL_FUNCTION void TestStringUnequalTo
	(
		const atl::String&	inString,
		const atl::String&	inReferenceString,
		const bool			inIgnoreCase,
		const bool			inTrimWhitespace,
		bool&				outIsUnequal
	)
	THROW_AVL_ERRORS;

	/// <summary>Replaces all occurrences of the searched string with a replacement string.</summary>
	/// <param name="inString">Input string.</param>
	/// <param name="inFind">Searched string.</param>
	/// <param name="inReplacement">Replacement string.</param>
	/// <param name="outString">Output string.</param>
	AVL_FUNCTION void ReplaceInString
	(
		const atl::String&	inString,			
		const atl::String&	inFind,				
		const atl::String&	inReplacement,		
		atl::String&		outString			
	)
	THROW_AVL_ERRORS;

	/// <summary>Divides the input string into an array of strings using the specified delimiters.</summary>
	/// <param name="inString">Input string.</param>
	/// <param name="inSplitters">Array of delimiters.</param>
	/// <param name="inRemoveEmptyEntries">Removes or leaves zero length strings. Default value: False.</param>
	/// <param name="outStrings">Array of a split elements.</param>
	AVL_FUNCTION void SplitString
	(
		const atl::String&				inString,				
		const atl::Array<atl::String>&	inSplitters,			
		const bool						inRemoveEmptyEntries,	
		atl::Array<atl::String>&		outStrings				
	)
	THROW_AVL_ERRORS;

	/// <summary>Splits the input string into individual characters.</summary>
	/// <param name="inString">Input string.</param>
	/// <param name="outStrings">Array of characters.</param>
	AVL_FUNCTION void SplitStringIntoCharacters
	(
		const atl::String&			inString,				
		atl::Array<atl::String>&	outStrings				
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds first occurrence of a substring in the input string.</summary>
	/// <param name="inString">Input string.</param>
	/// <param name="inFind">Searched string.</param>
	/// <param name="inStartPosition">Minimum index of a searched substring in string. Default value: atl::NIL.</param>
	/// <param name="inIgnoreCase">Default value: False.</param>
	/// <param name="outPosition">Position of searched string, -1 if not found.</param>
	AVL_FUNCTION void FindInString
	(
		const atl::String&			inString,			
		const atl::String&			inFind,				
		const atl::Optional<int>&	inStartPosition,	
		bool						inIgnoreCase,		
		int&						outPosition,		
		bool&						outStringFound		
	)
	THROW_AVL_ERRORS;

	/// <summary>Finds last occurrence of a substring in the input string.</summary>
	/// <param name="inString">Input string.</param>
	/// <param name="inFind">Searched string.</param>
	/// <param name="inEndPosition">Maximum index of a searched substring in string. Default value: atl::NIL.</param>
	/// <param name="inIgnoreCase">Default value: False.</param>
	/// <param name="outPosition">Position of searched string.</param>
	AVL_FUNCTION void FindLastInString
	(
		const atl::String&			inString,			
		const atl::String&			inFind,				
		const atl::Optional<int>&	inEndPosition,		
		bool						inIgnoreCase,		
		int&						outPosition,		
		bool&						outStringFound		
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a string according to the given format and data.</summary>
	/// <param name="inFormat">Format string.</param>
	/// <param name="inData">Values used in format.</param>
	/// <param name="outFormattedString">Output formatted string.</param>
	AVL_FUNCTION void FormatString
	(
		const atl::String&				inFormat,				
		const atl::Array<atl::String>&	inData,					
		atl::String&					outFormattedString		
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a string from an integer number using a proper format.</summary>
	/// <param name="inInteger">Input integer.</param>
	/// <param name="inDigitCount">How many characters the output string should have at least.</param>
	/// <param name="inTrailingCharacter">Defines the trailing character. Default value: \"0\".</param>
	/// <param name="inForceSignPrinting">Forces printing the sign of the number even if the number is positive. Default value: False.</param>
	/// <param name="inSuffix">Defines a suffix. Generally it is an unit of value (eg. mm). Default value: \"\".</param>
	/// <param name="inSystemBase">The base of the numeral system. Default value: 10.</param>
	/// <param name="outString">Output string.</param>
	AVL_FUNCTION void FormatIntegerToString
	(
		const int			inInteger,		
		const int			inDigitCount,	
		const atl::String&	inTrailingCharacter,
		const bool			inForceSignPrinting,
		const atl::String&	inSuffix,			
		const int			inSystemBase,		
		atl::String&		outString		
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a string from a real number using a proper format.</summary>
	/// <param name="inReal">Input real.</param>
	/// <param name="inIntegerDigitCount">How many characters the integer part of the input real should have at least.</param>
	/// <param name="inFractionalDigitCount">How many characters the fractional part of the input real should have. Default value: 3.</param>
	/// <param name="inDecimalMark">The symbol used to separate the integer part from the fractional part of the number. Default value: \".\".</param>
	/// <param name="inTrailingCharacter">Defines the trailing character. Default value: \"0\".</param>
	/// <param name="inForceSignPrinting">Forces printing the sign of the number even if the number is positive. Default value: False.</param>
	/// <param name="inSuffix">Defines a suffix. Generally it is an unit of value (eg. mm). Default value: \"\".</param>
	/// <param name="outString">Output string.</param>
	AVL_FUNCTION void FormatRealToString
	(
		const float			inReal,			
		const int				inIntegerDigitCount,	
		const int				inFractionalDigitCount,	
		const atl::String&		inDecimalMark,		
		const atl::String&		inTrailingCharacter,
		const bool				inForceSignPrinting,
		const atl::String&		inSuffix,			
		atl::String&			outString		
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a string from a double number using a proper format.</summary>
	/// <param name="inDouble">Input real.</param>
	/// <param name="inIntegerDigitCount">How many characters the integer part of the input real should have at least.</param>
	/// <param name="inFractionalDigitCount">How many characters the fractional part of the input real should have. Default value: 3.</param>
	/// <param name="inDecimalMark">The symbol used to separate the integer part from the fractional part of the number. Default value: \".\".</param>
	/// <param name="inTrailingCharacter">Defines the trailing character. Default value: \"0\".</param>
	/// <param name="inForceSignPrinting">Forces printing the sign of the number even if the number is positive. Default value: False.</param>
	/// <param name="inSuffix">Defines a suffix. Generally it is an unit of value (eg. mm). Default value: \"\".</param>
	/// <param name="outString">Output string.</param>
	AVL_FUNCTION void FormatDoubleToString
	(
		const double&		inDouble,			
		const int				inIntegerDigitCount,	
		const int				inFractionalDigitCount,	
		const atl::String&		inDecimalMark,		
		const atl::String&		inTrailingCharacter,
		const bool				inForceSignPrinting,
		const atl::String&		inSuffix,			
		atl::String&			outString		
	)
	THROW_AVL_ERRORS;

	/// <summary>Makes a string uppercase.</summary>
	/// <param name="inString">Input string.</param>
	/// <param name="outString">Converted string.</param>
	AVL_FUNCTION void StringToUpperCase
	(
		const atl::String&		inString,	
		atl::String&			outString	
	)
	THROW_AVL_ERRORS;

	/// <summary>Makes a string lowercase.</summary>
	/// <param name="inString">Input string.</param>
	/// <param name="outString">Converted string.</param>
	AVL_FUNCTION void StringToLowerCase
	(
		const atl::String&		inString,	
		atl::String&			outString	
	)
	THROW_AVL_ERRORS;

	/// <summary>Tests whether the length of a string equals zero.</summary>
	/// <param name="inString">Input string.</param>
	AVL_FUNCTION void TestStringEmpty
	(
		const atl::String&		inString,	
		bool&					outIsEmpty	
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts string to an integer array of character codes (UTF-16).</summary>
	/// <param name="inString">Input string.</param>
	AVL_FUNCTION void StringToNumericCodes
	(
		const atl::String&		inString,		
		atl::Array<int>&		outCodes
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts an integer array of character codes (UTF-16) into a string.</summary>
	/// <param name="inCodes">Input array.</param>
	/// <param name="outString">Output string.</param>
	AVL_FUNCTION void NumericCodesToString
	(
		const atl::Array<int>&	inCodes,		
		atl::String&			outString		
	)
	THROW_AVL_ERRORS;

	/// <summary>Saves a text to a file.</summary>
	AVL_FUNCTION void SaveText
	(
		const atl::String&			inText,
		avl::FileAccessMode::Type	inFileAccessMode,
		const atl::File&			inFile,
		bool						inIgnoreErrors
	)
	THROW_AVL_ERRORS;

	/// <summary>Loads a text from a file.</summary>
	AVL_FUNCTION void LoadText
	(
		const atl::File&	inFile,
		atl::String&		outText
	)
	THROW_AVL_ERRORS;

	/// <summary>Saves text lines to a file.</summary>
	/// <param name="inLineDelimiter">End of line character sequence, escaped. Default value: \"\\\\r\\\\n\".</param>
	AVL_FUNCTION void SaveTextLines
	(
		const atl::Array<atl::String>&	inTextLines,
		avl::FileAccessMode::Type		inFileAccessMode,
		const atl::File&				inFile,
		const atl::String&				inLineDelimiter,	
		bool							inIgnoreErrors
	)
	THROW_AVL_ERRORS;

	/// <summary>Loads text lines from a file.</summary>
	/// <param name="inLineDelimiter">End of line character sequence, escaped. Default value: \"\\\\r\\\\n\".</param>
	AVL_FUNCTION void LoadTextLines
	(
		const atl::File&			inFile,
		const atl::String&			inLineDelimiter,	
		bool						inSkipEmptyLines,
		atl::Array<atl::String>&	outTextLines
	)
	THROW_AVL_ERRORS;

	/// <summary>If the input string has at least one character, it is copied to the output; otherwise NIL is returned.</summary>
	AVL_FUNCTION void SkipEmptyString
	(
		const atl::String&				inString,
		atl::Conditional<atl::String>&	outNotEmptyString,
		bool&							outIsNotEmpty
	)
	THROW_AVL_ERRORS;

} // namespace avl

namespace avs
{

	/// <summary>Sort an array of strings</summary>
	/// <param name="inNaturalSort">Default value: False.</param>
	AVL_FUNCTION void AvsFilter_SortStrings
	(
		atl::Array<atl::String>&	ioStrings,
		bool					inDescending,
		bool					inNaturalSort
	)
	THROW_AVL_ERRORS;

	/// <summary>Joins two or more strings into a single one.</summary>
	/// <param name="inString1">Default value: "".</param>
	/// <param name="inString2">Default value: "".</param>
	/// <param name="inString3">Default value: "".</param>
	/// <param name="inString4">Default value: "".</param>
	/// <param name="inString5">Default value: "".</param>
	/// <param name="inString6">Default value: "".</param>
	/// <param name="inString7">Default value: "".</param>
	/// <param name="inString8">Default value: "".</param>
	AVL_FUNCTION void AvsFilter_ConcatenateStrings
	(
		const atl::String&	inString1,
		const atl::String&	inString2,
		const atl::String&	inString3,
		const atl::String&	inString4,
		const atl::String&	inString5,
		const atl::String&	inString6,
		const atl::String&	inString7,
		const atl::String&	inString8,
		atl::String&		outString
	)
	THROW_AVL_ERRORS;

	struct AvsFilter_ConcatenateStrings_OfLoopState
	{
		atl::String stateVariable;
	};


	/// <summary>Joins strings appearing in consecutive iterations.</summary>
	AVL_FUNCTION void AvsFilter_ConcatenateStrings_OfLoop
	(
		AvsFilter_ConcatenateStrings_OfLoopState& ioState,
		const atl::String&	inString,
		atl::String&		outString
	)
	THROW_AVL_ERRORS;

} // namespace avs

#endif // AVS_STRINGBASICS_H

