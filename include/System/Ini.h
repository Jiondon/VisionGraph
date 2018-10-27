//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_INI_H
#define AVL_INI_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/AtlString.h"
#include "ATL/Optional.h"
#include "ATL/Array.h"

namespace avl
{


	/// <summary>Loads an INI file.</summary>
	/// <param name="inFile">Path to the source file.</param>
	AVL_FUNCTION void INI_LoadFile
	(
		const atl::File&	inFile,		
		atl::String&		outINI
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets all section names in the INI.</summary>
	/// <param name="inINI">INI.</param>
	AVL_FUNCTION void INI_GetAllSections
	(
		const atl::String&			inINI,		
		atl::Array<atl::String>&	outSections
	)
	THROW_AVL_ERRORS;

	/// <summary>Get all key names within a section.</summary>
	/// <param name="inINI">INI.</param>
	/// <param name="inSectionName">Section name.</param>
	AVL_FUNCTION void INI_GetAllSectionKeys
	(
		const atl::String&			inINI,			
		const atl::String&			inSectionName,	
		atl::Array<atl::String>&	outKeys
	)
	THROW_AVL_ERRORS;

	/// <summary>Get all values within a section & key</summary>
	/// <param name="inINI">INI.</param>
	/// <param name="inSection">Section name.</param>
	/// <param name="inKey">Key name.</param>
	AVL_FUNCTION void INI_GetAllValues
	(
		const atl::String&			inINI,		
		const atl::String&			inSection,	
		const atl::String&			inKey,		
		atl::Array<atl::String>&	outValues
	)
	THROW_AVL_ERRORS;

	/// <summary>Get value from section & key.</summary>
	/// <param name="inINI">INI.</param>
	/// <param name="inSection">Section name.</param>
	/// <param name="inKey">Key name.</param>
	/// <param name="inDefault">Value to return if the key is not found.</param>
	AVL_FUNCTION void INI_GetStringValue
	(
		const atl::String&			inINI,		
		const atl::String&			inSection,	
		const atl::String&			inKey,		
		const atl::String&			inDefault,	
		atl::String&				outValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Get value from section & key.</summary>
	/// <param name="inINI">INI.</param>
	/// <param name="inSection">Section name.</param>
	/// <param name="inKey">Key name.</param>
	/// <param name="inDefault">Value to return if the key is not found.</param>
	AVL_FUNCTION void INI_GetBoolValue
	(
		const atl::String&		inINI,		
		const atl::String&		inSection,	
		const atl::String&		inKey,		
		const bool				inDefault,  
		bool&					outValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Get value from section & key.</summary>
	/// <param name="inINI">INI.</param>
	/// <param name="inSection">Section name.</param>
	/// <param name="inKey">Key name.</param>
	/// <param name="inDefault">Value to return if the key is not found.</param>
	AVL_FUNCTION void INI_GetIntegerValue
	(
		const atl::String&		inINI,		
		const atl::String&		inSection,	
		const atl::String&		inKey,		
		const int				inDefault,  
		int&					outValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Get value from section & key.</summary>
	/// <param name="inINI">INI.</param>
	/// <param name="inSection">Section name.</param>
	/// <param name="inKey">Key name.</param>
	/// <param name="inDefault">Value to return if the key is not found.</param>
	AVL_FUNCTION void INI_GetRealValue
	(
		const atl::String&		inINI,		
		const atl::String&		inSection,	
		const atl::String&		inKey,		
		const float			inDefault,  
		float&				outValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Save INI into file</summary>
	/// <param name="inINI">INI.</param>
	/// <param name="inFile">Path to a file.</param>
	AVL_FUNCTION void INI_SaveFile
	(
		const atl::String&		inINI,	
		const atl::File&		inFile	
	)
	THROW_AVL_ERRORS;

	/// <summary>Add new section</summary>
	/// <param name="inINI">INI.</param>
	/// <param name="inSection">Section name.</param>
	/// <param name="inComment">Optional comment. Default value: atl::NIL.</param>
	AVL_FUNCTION void INI_AddSection
	(
		const atl::String&					inINI,		
		const atl::String&					inSection,	
		atl::Optional<const atl::String&>	inComment,	
		atl::String&						outINI
	)
	THROW_AVL_ERRORS;

	/// <summary>Add or update INI value in specified section & key</summary>
	/// <param name="inINI">INI.</param>
	/// <param name="inSection">Section name.</param>
	/// <param name="inKey">Key name.</param>
	/// <param name="inValue">Key value.</param>
	/// <param name="inComment">Optional comment. Default value: atl::NIL.</param>
	AVL_FUNCTION void INI_AddStringValue
	(
		const atl::String&					inINI,		
		const atl::String&					inSection,	
		const atl::String&					inKey,		
		const atl::String&					inValue,	
		atl::Optional<const atl::String&>	inComment,	
		atl::String&						outINI
	)
	THROW_AVL_ERRORS;

	/// <summary>Add or update INI value in specified section & key</summary>
	/// <param name="inINI">INI.</param>
	/// <param name="inSection">Section name.</param>
	/// <param name="inKey">Key name.</param>
	/// <param name="inValue">Key value.</param>
	/// <param name="inComment">Optional comment. Default value: atl::NIL.</param>
	AVL_FUNCTION void INI_AddBoolValue
	(
		const atl::String&					inINI,		
		const atl::String&					inSection,	
		const atl::String&					inKey,		
		const bool							inValue,	
		atl::Optional<const atl::String&>	inComment,	
		atl::String&						outINI
	)
	THROW_AVL_ERRORS;

	/// <summary>Add or update INI value in specified section & key</summary>
	/// <param name="inINI">INI.</param>
	/// <param name="inSection">Section name.</param>
	/// <param name="inKey">Key name.</param>
	/// <param name="inValue">Key value.</param>
	/// <param name="inComment">Optional comment. Default value: atl::NIL.</param>
	AVL_FUNCTION void INI_AddRealValue
	(
		const atl::String&					inINI,		
		const atl::String&					inSection,	
		const atl::String&					inKey,		
		const float						inValue,	
		atl::Optional<const atl::String&>	inComment,	
		atl::String&						outINI
	)
	THROW_AVL_ERRORS;

	/// <summary>Add or update INI value in specified section & key</summary>
	/// <param name="inINI">INI.</param>
	/// <param name="inSection">Section name.</param>
	/// <param name="inKey">Key name.</param>
	/// <param name="inValue">Key value.</param>
	/// <param name="inComment">Optional comment. Default value: atl::NIL.</param>
	AVL_FUNCTION void INI_AddIntegerValue
	(
		const atl::String&					inINI,		
		const atl::String&					inSection,	
		const atl::String&					inKey,		
		const int							inValue,	
		atl::Optional<const atl::String&>	inComment,	
		atl::String&						outINI
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_INI_H

