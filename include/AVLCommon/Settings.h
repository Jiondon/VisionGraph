//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef SETTINGS_H
#define SETTINGS_H

#include "Config.h"
#include "ATL/AtlString.h"

namespace avl
{

	AVL_FUNCTION
	void EnableSSEAcceleration( bool enable );


	AVL_FUNCTION
	bool GetSSEAccelerationEnabled( void );


	AVL_FUNCTION
	void SetParallelComputing( bool enabled, int num_threads );


	AVL_FUNCTION
	int GetParallelComputingThreadsCount( void );


	AVL_FUNCTION
	void EnableAvlDiagnosticOutputs( bool enable );


	AVL_FUNCTION
	bool GetAvlDiagnosticOutputsEnabled( void );


	AVL_FUNCTION
	void InitGPUProcessing( const atl::String& platformName = "", const atl::String& deviceName = "" );


	AVL_FUNCTION
	void GetGPUProcessingDiagInfo( atl::String& outDiagInfo );


	AVL_FUNCTION
	void CloseGPUProcessing( void );


	AVL_FUNCTION
	bool EnableGPUProcessing( bool inEnabled );

#ifdef ENABLE_NEON

	AVL_FUNCTION
	void EnableNEONAcceleration(bool enable);

	AVL_FUNCTION
	bool  GetNEONEnabled();

#endif

} // namespace avl

#endif // SETTINGS_H
