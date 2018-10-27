//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVS_PROCESS_H
#define AVS_PROCESS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/AtlString.h"

namespace avs
{


	/// <summary>Executes a command using the system console.</summary>
	/// <param name="inCommand">System command to be executed.</param>
	/// <param name="inWorkingDirectory">Working directory in which the command will be executed. Default value: \".\".</param>
	/// <param name="outReturnCode">Return code of the executed command.</param>
	/// <param name="outResult">Captured text data.</param>
	AVL_FUNCTION void AvsFilter_Execute
	(
		const atl::File&			inCommand,			
		const atl::Directory&		inWorkingDirectory,	
		int&						outReturnCode,		
		atl::String&				outResult			
	)
	THROW_AVL_ERRORS;

} // namespace avs

#endif // AVS_PROCESS_H

