//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVS_CONFIGURATION_H
#define AVS_CONFIGURATION_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/Optional.h"
#include "ATL/AtlString.h"
#include "ATL/Array.hxx"
#include "AVLCommon/Settings.h"

namespace avl
{


	/// <summary>Enables or disables SSE cpu extension usage by other filters.</summary>
	/// <param name="inIsEnabled">When 'true' SSE instructions are used. Default value: True.</param>
	AVL_FUNCTION void ControlSSE
	(
		bool	inIsEnabled,	
		bool&	outIsAvailable
	)
	THROW_AVL_ERRORS;

	/// <summary>Enables or disables filters multithreading parallelization.</summary>
	/// <param name="inIsEnabled">When 'true' parallel computing is used. Default value: True.</param>
	/// <param name="inThreadCount">Requested number of threads. Default value: atl::NIL.</param>
	/// <param name="outThreadCount">Actually available number of threads.</param>
	AVL_FUNCTION void ControlParallelComputing
	(
		bool				inIsEnabled,	
		atl::Optional<int>	inThreadCount,	
		int&				outThreadCount	
	)
	THROW_AVL_ERRORS;

	/// <summary>Enables or disables deterministic image memory allocator.</summary>
	/// <param name="inIsEnabled">Specifies whether memory pools should be used or not. Default value: True.</param>
	AVL_FUNCTION void ControlImageMemoryPools
	(
		bool inIsEnabled						
	)
	THROW_AVL_ERRORS;

	/// <summary>Returns information about allocated image memory buffers. This information can be used for preallocation.</summary>
	/// <param name="outIsEnabled">Specifies whether memory pools are used or not.</param>
	/// <param name="outPoolSizes">Count of blocks in consecutive pools.</param>
	/// <param name="outBlockLengths">Length of blocks in consecutive pools.</param>
	/// <param name="outTotalUsage">Total image memory allocated [B].</param>
	AVL_FUNCTION void InspectImageMemoryPools
	(
		bool&				outIsEnabled,		
		atl::Array<int>&	outPoolSizes,		
		atl::Array<int>&	outBlockLengths,	
		int&				outTotalUsage		
	)
	THROW_AVL_ERRORS;

	/// <summary>Preallocates memory buffers for images.</summary>
	/// <param name="inRequestedPoolSizes">Copy a value from InspectImageMemoryPools.outPoolSizes.</param>
	/// <param name="inTouch">Forces getting the new memory pools to the cache memory.</param>
	AVL_FUNCTION void ChargeImageMemoryPools
	(
		const atl::Array<int>&	inRequestedPoolSizes,	
		bool inTouch									
	)
	THROW_AVL_ERRORS;

	/// <summary>Releases preallocated image memory buffers.</summary>
	AVL_FUNCTION void DischargeImageMemoryPools
	(
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets current Computer ID</summary>
	AVL_FUNCTION void GetComputerID
	(
		atl::String& outComputerID
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets current dongle serial number</summary>
	AVL_FUNCTION void GetDongleSerialNumber
	(
		atl::String& outDongleSerialNumber
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets current library version</summary>
	AVL_FUNCTION void GetLibraryVersion
	(
		int& outMajor,
		int& outMinor,
		int& outBuild,
		int& outRevision
	)
	THROW_AVL_ERRORS;

	/// <summary></summary>
	AVL_FUNCTION void ThrowOnProgramStop
	(
	)
	THROW_AVL_ERRORS;

	/// <summary>Initializes library internals. Should be called before any other function from AVL.</summary>
	AVL_FUNCTION void InitLibrary
	()
	THROW_AVL_ERRORS;

} // namespace avl

namespace avs
{

	struct InitGPUProcessingState
	{
		atl::String diagInfo;
		bool isInitialized;

		InitGPUProcessingState()
		: isInitialized(false)
		{
		}

		~InitGPUProcessingState()
		{
			if (isInitialized)
			{
				avl::CloseGPUProcessing();
				isInitialized = false;
			}
		}
	};


	/// <summary>Initializes GPU OpenCL processing.</summary>
	/// <param name="inPlatformName">Name or fragment of a name of OpenCL provider platform. Default value: atl::NIL.</param>
	/// <param name="inDeviceName">Name or fragment of a name of OpenCL device. Default value: atl::NIL.</param>
	/// <param name="diagDeviceInfo">Provides human readable diagnostic information about OpenCL device selected for processing.</param>
	AVL_FUNCTION void AvsFilter_InitGPUProcessing
	(
		InitGPUProcessingState&							ioState,
		const atl::Optional<const atl::String&>&		inPlatformName,		
		const atl::Optional<const atl::String&>&		inDeviceName,		
		atl::Optional<atl::String&>						diagDeviceInfo = atl::NIL		
	)
	THROW_AVL_ERRORS;

	/// <summary>Resumes or suspends GPU OpenCL processing in filters.</summary>
	/// <param name="inEnable">True to resume, False to suspend GPU processing. Default value: True.</param>
	AVL_FUNCTION void AvsFilter_EnableGPUProcessing
	(
		bool	inEnable		
	)
	THROW_AVL_ERRORS;

} // namespace avs

#endif // AVS_CONFIGURATION_H

