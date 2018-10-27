//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef PYLON_INTERFACE_H
#define PYLON_INTERFACE_H

#include "ATL/Optional.h"
#include "Image/PlainTypes.h"
#include "Basic/Types.h"
#include "Image/Image.h"
#include "AVLCommon/CancellationTypes.h"

namespace avl
{
	namespace PylonImageFormat
	{
		enum Type
		{
			Mono8,
			Mono10,
			Mono10packed,
			Mono10p,
			Mono12,
			Mono12packed,
			Mono12p,
			Mono16,
			BayerRG8,
			BayerGR8,
			BayerGB8,
			BayerBG8,		
			BayerGR10,
			BayerRG10,
			BayerGB10,
			BayerBG10,		
			BayerGR10p,
			BayerRG10p,
			BayerGB10p,
			BayerBG10p,		
			BayerGR12,
			BayerRG12,
			BayerGB12,
			BayerBG12,		
			BayerGR12packed,
			BayerRG12packed,
			BayerGB12packed,
			BayerBG12packed,
			BayerGR12p,
			BayerRG12p,
			BayerGB12p,
			BayerBG12p,	
			BayerGR16,
			BayerRG16,
			BayerGB16,
			BayerBG16,
			RGB8Packed,
			RGB10Packed,
			RGB12Packed,
			RGB16Packed,
			YCbCr422_8,
			YUV422Packed,
		};
	}

	namespace PylonTriggerSource
	{
		enum Type
		{
			Software,
			Line1,
			Line2,
			Line3,
			Line4,
			Line5,
			Line6,
			Line7,
			Line8,
			CC1,
			CC2,
			CC3,
			CC4,
			Timer1Start,
			Timer1End,
			Counter1Start,
			Counter1End,
			UserOutput1,
			UserOutput2
		};
	}

	namespace PylonTriggerActivation
	{
		enum Type
		{
			RisingEdge,
			FallingEdge,
			AnyEdge,
			LevelHigh,
			LevelLow
		};
	}

	namespace PylonUserOutput
	{
		enum Type
		{
			UserSettableOutput1,
			UserSettableOutput2,
			UserSettableOutput3,
			UserSettableOutput4,
			UserSettableOutput5,
			UserSettableOutput6,
			UserSettableOutput7,
			UserSettableOutput8
		};
	}

	class PylonInterface
	{
	public:
		virtual ~PylonInterface() {}

		virtual void SetCancellationObject(ICancellationProvider* workCancellation) = 0;

		virtual void BindToFirstCamera() = 0;
		virtual void BindToNamedCamera( const atl::String& inName ) = 0;

		virtual bool GrabImage(const atl::Optional<int>& inTimeout, Image& outImage, atl::int64& outFrameId, atl::int64& outTimeStamp) = 0;
		
		virtual bool AcquisitionStarted() = 0;
		virtual void StartAcquisition(atl::Optional<avl::PylonImageFormat::Type> inPixelFormat, int inOutputQueueSize) = 0;
		virtual void StopAcquisition() = 0;
		virtual void Close() = 0;

		virtual void SetParams(const atl::Optional<float>& inGain,
			const atl::Optional<float>& inBlackLevel, const atl::Optional<float>& inExTime,
			const atl::Optional<float>& inFrameRate, const atl::Optional<const avl::Box&>& inAoi) = 0;
		virtual void SetTriggerParams(const atl::Optional<bool> inTriggerMode, const atl::Optional<avl::PylonTriggerSource::Type> inTriggerSource,
			const atl::Optional<avl::PylonTriggerActivation::Type> inTriggerActivation) = 0;

		virtual void SetUserOutput( PylonUserOutput::Type inOutput, bool value ) = 0;

		virtual void GenerateSoftwareTrigger(const atl::Optional<int> inTimeout, bool inIgnoreWaiting, bool& outExecuted) = 0;

		virtual void SetBoolParameter	( const atl::String& inName, bool		inValue ) = 0;
		virtual void SetRealParameter	( const atl::String& inName, float	inValue ) = 0;
		virtual void SetIntegerParameter( const atl::String& inName, int		inValue ) = 0;
		virtual void SetEnumParameter	( const atl::String& inName, const atl::String& inValue ) = 0;
		virtual void SetStringParameter	( const atl::String& inName, const atl::String& inValue ) = 0;

		virtual void GetBoolParameter	( const atl::String& inName, bool&		outValue ) = 0;
		virtual void GetRealParameter	( const atl::String& inName, float&	outValue ) = 0;
		virtual void GetIntegerParameter( const atl::String& inName, int&		outValue ) = 0;
		virtual void GetEnumParameter	( const atl::String& inName, atl::String& outValue ) = 0;
		virtual void GetStringParameter	( const atl::String& inName, atl::String& outValue ) = 0;

		virtual void ExecuteCommand		( const atl::String& inCommandName ) = 0;

		virtual void GetGigeVisionStatistics(atl::int64& outTotalBufferCount, atl::int64& outFailedBufferCount, atl::int64& outBufferUnderrunCount,
			atl::int64& outTotalPacketCount, atl::int64& outFailedPacketCount, atl::int64& outResendRequestCount, atl::int64& outResendPacketCount,
			atl::int64& outNumEmptyBuffers, atl::int64& outNumQueuedBuffers, atl::int64& outNumReadyBuffers, atl::int64& outOutputQueueSize) = 0;

		virtual void GetUsbVisionStatistics(atl::int64& outTotalBufferCount, atl::int64& outFailedBufferCount, atl::int64& outLastFailedBufferStatus,
			atl::String& outLastFailedBufferStatusText, atl::int64& outMissedFrameCount, atl::int64& outResynchronizationCount, atl::int64& outLastBlockId,
			atl::int64& outNumEmptyBuffers, atl::int64& outNumQueuedBuffers, atl::int64& outNumReadyBuffers, atl::int64& outOutputQueueSize) = 0;
	};
}

#endif
