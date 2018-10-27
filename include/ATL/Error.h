//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//


#ifndef ATL_ERROR_H
#define ATL_ERROR_H

#include "Platform.h"

#define NO_ATL_STRING_HXX
#include "AtlString.h"
#undef NO_ATL_STRING_HXX

namespace atl
{
	enum ErrorType
	{
		ANY_ERROR,
		IO_ERROR,
		SYSTEM_ERROR,
		DOMAIN_ERROR,
		LICENSE_ERROR,
		RUNTIME_ERROR,
		ASSERTION_ERROR,
		UNHANDLED_ERROR,
		OUT_OF_MEMORY_ERROR,
		NONE
	};

	// Base class for all exceptions
	class Error
	{
	public:
		const char*		Message()	const { return msg.CStr8(); }
		const wchar16*	Message16()	const { return msg.CStr16(); }
		virtual const char* Kind()	const { return "Error"; }
		virtual ErrorType	Type()	const { return ANY_ERROR; }

	protected:
		explicit Error( const String& msg )
			: msg( msg )
		{}

		// Copy constructor is needed
		Error( const Error& rhs )
			: msg( rhs.msg )
		{}

		virtual ~Error()
		{}

		void SetMessage( const String& _msg )
		{
			this->msg = _msg;
		}

	private:
		String msg;
	};

	// Exception occurring when a function cannot be completed
	class RuntimeError : public Error
	{
	public:
		RuntimeError( const String& msg )
			: Error( msg )
		{}

		const char* Kind() const { return "Runtime Error"; }
		ErrorType	Type() const { return RUNTIME_ERROR; }
	};

	// Exception occurring when allocationg memory is not possible
	class OutOfMemoryError : public RuntimeError
	{
	public:
		OutOfMemoryError(const String& msg)
		: RuntimeError(msg)
		{}

		const char* Kind() const { return "Out of Memory Error"; }
		ErrorType	Type() const { return OUT_OF_MEMORY_ERROR; }
	};

	// Exception specific to communication with external devices (disks, network etc.)
	class IoError : public Error
	{
	public:
		IoError(const String& msg)
			: Error( msg )
		{}

		const char* Kind() const { return "IO Error"; }
		ErrorType	Type() const { return IO_ERROR; }
	};

	// Exception specific to operating system (memory, libraries, services)
	class SystemError : public Error
	{
	public:
		SystemError(const String& msg)
			: Error( msg )
		{}

		const char* Kind() const { return "System Error"; }
		ErrorType	Type() const { return SYSTEM_ERROR; }
	};

	// Exception specific to incorrect data-entry or programming by the user
	class DomainError : public Error
	{
	public:
		DomainError(const String& msg)
			: Error( msg )
		{}

		const char* Kind() const { return "Domain Error"; }
		ErrorType	Type() const { return DOMAIN_ERROR; }
	};

	// Exception occurring due to unknown reasons
	class FatalError : public Error
	{
	public:
		FatalError(const String& msg)
			: Error(msg)
		{}

		const char* Kind() const { return "Fatal Error"; }
		ErrorType	Type() const { return ANY_ERROR; }
	};

	// Exception thrown in case of problems with license
	class LicenseError : public Error
	{
	public:
		LicenseError(const String& msg)
			: Error(msg)
		{}

		const char* Kind() const { return "License Error"; }
		ErrorType	Type() const { return LICENSE_ERROR; }
	};

	// Exception thrown by assert filters
	class AssertionError : public Error
	{
	public:
		AssertionError(const String& msg)
		: Error(msg)
		{}

		const char* Kind() const { return "Assertion Error"; }
		ErrorType	Type() const { return ASSERTION_ERROR; }
	};

} // namespace atl


#include "AtlString.hxx"

#endif // ATL_ERROR_H
