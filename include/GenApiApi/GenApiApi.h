//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_GENAPIAPI_H
#define AVL_GENAPIAPI_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Array.hxx"
#include "ATL/AtlString.h"

namespace avl
{



	typedef int GenApiHandle;

	namespace GenApi_InterfaceType
	{
		enum Type
		{
			Invalid = 0,
			Integer,
			Float,
			String,
			Enumeration,
			Command,
			Boolean,
			Category,
		};
	}
	
	struct GenApi_ParameterDescriptor
	{
		atl::String DisplayName;
		atl::String Description;
		avl::GenApi_InterfaceType::Type InterfaceType;
		bool IsImplemented;
		bool IsAvailable;
		bool IsReadable;
		bool IsWriteable;
	};

	struct GenApi_IntegerDescriptor
	{
		atl::sint64 Min;
		atl::sint64 Max;
		atl::sint64 Inc;
		atl::String Unit;
	};

	struct GenApi_FloatDescriptor
	{
		double Min;
		double Max;
		bool HasInc;
		double Inc;
		atl::String Unit;
	};

	struct GenApi_EnumEntryDescriptor
	{
		atl::String Id;
		atl::String DisplayName;
		atl::String Description;
		bool IsImplemented;
		bool IsAvailable;
		double NumericValue;
	};

	struct GenApi_EnumDescriptor
	{
		atl::Array<GenApi_EnumEntryDescriptor> Entries;
	};

	struct GenApi_CategoryDescriptor
	{
		atl::Array< atl::String > Features;
	};



	/// <summary>Writes named parameter value using GenICam IInteger interface.</summary>
	/// <param name="inHandle">Handle to object providing GenApi interface.</param>
	/// <param name="inParameterName">Textual name of the parameter that should be accessed in GenICam naming convention or device specific name. Parameter name is case sensitive.</param>
	/// <param name="inValue">New value that should be written to parameter.</param>
	/// <param name="inVerify">True to verify parameter access and value range and alignment.</param>
	AVL_FUNCTION void GenApi_SetIntegerParam
	(
		GenApiHandle	inHandle,			
		const char*		inParameterName,	
		atl::sint64		inValue,			
		bool			inVerify = true		
	)
	THROW_AVL_ERRORS;

	/// <summary>Writes named parameter value using GenICam IFloat interface.</summary>
	/// <param name="inHandle">Handle to object providing GenApi interface.</param>
	/// <param name="inParameterName">Textual name of the parameter that should be accessed in GenICam naming convention or device specific name. Parameter name is case sensitive.</param>
	/// <param name="inValue">New value that should be written to parameter.</param>
	/// <param name="inVerify">True to verify parameter access and value range.</param>
	AVL_FUNCTION void GenApi_SetFloatParam
	(
		GenApiHandle	inHandle,			
		const char*		inParameterName,	
		double			inValue,			
		bool			inVerify = true		
	)
	THROW_AVL_ERRORS;

	/// <summary>Writes named parameter value using GenICam IBoolean interface.</summary>
	/// <param name="inHandle">Handle to object providing GenApi interface.</param>
	/// <param name="inParameterName">Textual name of the parameter that should be accessed in GenICam naming convention or device specific name. Parameter name is case sensitive.</param>
	/// <param name="inValue">New value that should be written to parameter.</param>
	/// <param name="inVerify">True to verify parameter access.</param>
	AVL_FUNCTION void GenApi_SetBooleanParam
	(
		GenApiHandle	inHandle,			
		const char*		inParameterName,	
		bool			inValue,			
		bool			inVerify = true		
	)
	THROW_AVL_ERRORS;

	/// <summary>Writes named parameter value using GenICam IString interface.</summary>
	/// <param name="inHandle">Handle to object providing GenApi interface.</param>
	/// <param name="inParameterName">Textual name of the parameter that should be accessed in GenICam naming convention or device specific name. Parameter name is case sensitive.</param>
	/// <param name="inValue">New value that should be written to parameter.</param>
	/// <param name="inVerify">True to verify parameter access and value range and alignment.</param>
	AVL_FUNCTION void GenApi_SetStringParam
	(
		GenApiHandle	inHandle,			
		const char*		inParameterName,	
		const char*		inValue,			
		bool			inVerify = true		
	)
	THROW_AVL_ERRORS;

	/// <summary>Writes named parameter value using GenICam IEnumeration interface.</summary>
	/// <param name="inHandle">Handle to object providing GenApi interface.</param>
	/// <param name="inParameterName">Textual name of the parameter that should be accessed in GenICam naming convention or device specific name. Parameter name is case sensitive.</param>
	/// <param name="inValue">New enumeration entry id that should be written to parameter.</param>
	/// <param name="inVerify">True to verify parameter access and value range and alignment.</param>
	AVL_FUNCTION void GenApi_SetEnumParam
	(
		GenApiHandle	inHandle,			
		const char*		inParameterName,	
		const char*		inValue,			
		bool			inVerify = true		
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads named parameter value using GenICam IInteger interface.</summary>
	/// <param name="inHandle">Handle to object providing GenApi interface.</param>
	/// <param name="inParameterName">Textual name of the parameter that should be accessed in GenICam naming convention or device specific name. Parameter name is case sensitive.</param>
	/// <param name="inVerifyAccess">True to verify parameter access.</param>
	AVL_FUNCTION atl::sint64 GenApi_GetIntegerParam
	(
		GenApiHandle	inHandle,					
		const char*		inParameterName,			
		bool			inVerifyAccess = true		
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads named parameter value using GenICam IFloat interface.</summary>
	/// <param name="inHandle">Handle to object providing GenApi interface.</param>
	/// <param name="inParameterName">Textual name of the parameter that should be accessed in GenICam naming convention or device specific name. Parameter name is case sensitive.</param>
	/// <param name="inVerifyAccess">True to verify parameter access.</param>
	AVL_FUNCTION double GenApi_GetFloatParam
	(
		GenApiHandle	inHandle,					
		const char*		inParameterName,			
		bool			inVerifyAccess = true		
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads named parameter value using GenICam IBoolean interface.</summary>
	/// <param name="inHandle">Handle to object providing GenApi interface.</param>
	/// <param name="inParameterName">Textual name of the parameter that should be accessed in GenICam naming convention or device specific name. Parameter name is case sensitive.</param>
	/// <param name="inVerifyAccess">True to verify parameter access.</param>
	AVL_FUNCTION bool GenApi_GetBooleanParam
	(
		GenApiHandle	inHandle,					
		const char*		inParameterName,			
		bool			inVerifyAccess = true		
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads named parameter value using GenICam IInteger interface.</summary>
	/// <param name="inHandle">Handle to object providing GenApi interface.</param>
	/// <param name="inParameterName">Textual name of the parameter that should be accessed in GenICam naming convention or device specific name. Parameter name is case sensitive.</param>
	/// <param name="inVerifyAccess">True to verify parameter access.</param>
	AVL_FUNCTION void GenApi_GetStringParam
	(
		GenApiHandle	inHandle,			
		const char*		inParameterName,	
		bool			inVerifyAccess,		
		atl::String&	outValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads named parameter value using GenICam IEnumeration interface.</summary>
	/// <param name="inHandle">Handle to object providing GenApi interface.</param>
	/// <param name="inParameterName">Textual name of the parameter that should be accessed in GenICam naming convention or device specific name. Parameter name is case sensitive.</param>
	/// <param name="inVerifyAccess">True to verify parameter access.</param>
	AVL_FUNCTION void GenApi_GetEnumParam
	(
		GenApiHandle	inHandle,				
		const char*		inParameterName,		
		bool			inVerifyAccess,			
		atl::String&	outValue
	)
	THROW_AVL_ERRORS;

	/// <summary>Executes named command parameter using GenICam ICommand interface.</summary>
	/// <param name="inHandle">Handle to object providing GenApi interface.</param>
	/// <param name="inCommandName">Textual name of the command parameter that should be executed in GenICam naming convention or device specific name. Command name is case sensitive.</param>
	/// <param name="inVerifyAccess">True to verify parameter access.</param>
	AVL_FUNCTION void GenApi_ExecuteCommand
	(
		GenApiHandle	inHandle,				
		const char*		inCommandName,			
		bool			inVerifyAccess = true	
	)
	THROW_AVL_ERRORS;

	/// <summary>Checks if parameter, category or command with specified name exists in GenApi set.</summary>
	/// <param name="inHandle">Handle to object providing GenApi interface.</param>
	/// <param name="inParameterName">Textual name of the parameter, category or command that should be checked in GenICam naming convention or device specific name. Name is case sensitive.</param>
	AVL_FUNCTION bool GenApi_GetParamExists
	(
		GenApiHandle				inHandle,			
		const char*					inParameterName		
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads named parameter description and attributes from GenICam interface.</summary>
	/// <param name="inHandle">Handle to object providing GenApi interface.</param>
	/// <param name="inParameterName">Textual name of the parameter that should be accessed in GenICam naming convention or device specific name. Parameter name is case sensitive.</param>
	AVL_FUNCTION void GenApi_GetParamDescriptor
	(
		GenApiHandle				inHandle,			
		const char*					inParameterName,	
		GenApi_ParameterDescriptor&	outDescriptor
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads named integer parameter attributes from GenICam IInteger interface.</summary>
	/// <param name="inHandle">Handle to object providing GenApi interface.</param>
	/// <param name="inParameterName">Textual name of the parameter that should be accessed in GenICam naming convention or device specific name. Parameter name is case sensitive.</param>
	AVL_FUNCTION void GenApi_GetIntegerDescriptor
	(
		GenApiHandle				inHandle,			
		const char*					inParameterName,	
		GenApi_IntegerDescriptor&	outDescriptor
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads named float parameter attributes from GenICam IFloat interface.</summary>
	/// <param name="inHandle">Handle to object providing GenApi interface.</param>
	/// <param name="inParameterName">Textual name of the parameter that should be accessed in GenICam naming convention or device specific name. Parameter name is case sensitive.</param>
	AVL_FUNCTION void GenApi_GetFloatDescriptor
	(
		GenApiHandle			inHandle,			
		const char*				inParameterName,	
		GenApi_FloatDescriptor&	outDescriptor
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads named enum parameter description from GenICam IEnumeration interface.</summary>
	/// <param name="inHandle">Handle to object providing GenApi interface.</param>
	/// <param name="inParameterName">Textual name of the parameter that should be accessed in GenICam naming convention or device specific name. Parameter name is case sensitive.</param>
	/// <param name="inAvailableEntriesOnly">True to include in returned description only implemented and available enumeration entries.</param>
	AVL_FUNCTION void GenApi_GetEnumDescriptor
	(
		GenApiHandle			inHandle,					
		const char*				inParameterName,			
		bool					inAvailableEntriesOnly,		
		GenApi_EnumDescriptor&	outDescriptor
	)
	THROW_AVL_ERRORS;

	/// <summary>Reads named category description from GenICam interface.</summary>
	/// <param name="inHandle">Handle to object providing GenApi interface.</param>
	/// <param name="inCategoryName">Textual name of the category that should be accessed in GenICam naming convention or device specific name. Category name is case sensitive.</param>
	AVL_FUNCTION void GenApi_GetCategoryDescriptor
	(
		GenApiHandle				inHandle,			
		const char*					inCategoryName,		
		GenApi_CategoryDescriptor&	outDescriptor
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_GENAPIAPI_H

