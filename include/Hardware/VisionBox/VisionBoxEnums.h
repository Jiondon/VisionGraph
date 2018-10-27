//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef VISION_BOX_ENUMS_H
#define VISION_BOX_ENUMS_H

namespace avl
{

	namespace VisionBoxStrobeMode
	{
		enum Type
		{
			StrobeModeSoftwareEdge = 0,
			StrobeModeSoftwareCopy = 1,
			StrobeModeHardwareEdge = 2,
			StrobeModeHardwareCopy = 3
		};
	}

	namespace VisionBoxStrobeSource
	{
		enum Type
		{
			StrobeSourceDigIn0 = 0,
			StrobeSourceDigIn1 = 1,
			StrobeSourceDigIn2 = 2,
			StrobeSourceDigIn3 = 3,
			StrobeSourceDigIn4 = 4,
			StrobeSourceDigIn5 = 5,
			StrobeSourceDigIn6 = 6,
			StrobeSourceDigIn7 = 7,
			StrobeSourceRs422In0 = 8,
			StrobeSourceRs422In1 = 9,
			StrobeSourceRs422In2 = 10,
			StrobeSourceTriggenOut0 =13,
			StrobeSourceTriggenOut1 =14,
			StrobeSourceTriggenOut2 =15,
			StrobeSourceTriggenOut3 = 16,
			StrobeSourceMuxOut0 = 0x100,
			StrobeSourceMuxOut1 = 0x101,
			StrobeSourceMuxOut2,
			StrobeSourceMuxOut3,
			StrobeSourceMuxOut4,
			StrobeSourceMuxOut5,
			StrobeSourceMuxOut6,
			StrobeSourceMuxOut7,
			StrobeSourceMuxOut8,
			StrobeSourceMuxOut9,
			StrobeSourceMuxOut10,
			StrobeSourceMuxOut11,
			StrobeSourceMuxOut12,
			StrobeSourceMuxOut13,
			StrobeSourceMuxOut14,
			StrobeSourceMuxOut15 = 0x10F
		};
	}

	namespace VisionBoxTriggerSource
	{
		enum Type
		{
			CamTrgOff = 0,
			CamTrgOn,
			CamTrgDigIn0,
			CamTrgDigIn1,
			CamTrgDigIn2,
			CamTrgDigIn3,
			CamTrgDigIn4,
			CamTrgDigIn5,
			CamTrgDigIn6,
			CamTrgDigIn7,
			CamTrgRs422In0,
			CamTrgRs422In1,
			CamTrgRs422In2,
			CamTrgTriggenOut0,
			CamTrgTriggenOut1,
			CamTrgTriggenOut2 = 15,
			CamTrgMuxOut0 = 0x020,
			CamTrgMuxOut1 = 0x030,
			CamTrgMuxOut2 = 0x040,
			CamTrgMuxOut3 = 0x050,
			CamTrgMuxOut4 = 0x060,
			CamTrgMuxOut5 = 0x070,
			CamTrgMuxOut6 = 0x080,
			CamTrgMuxOut7 = 0x090,
			CamTrgMuxOut8 = 0x0A0,
			CamTrgMuxOut9 = 0x0B0,
			CamTrgMuxOut10 = 0x0C0,
			CamTrgMuxOut11 = 0x0D0,
			CamTrgMuxOut12 = 0x0E0,
			CamTrgMuxOut13 = 0x0F0,
			CamTrgMuxOut14 = 0x100,
			CamTrgMuxOut15 = 0x110
		};
	}

	namespace VisionBoxMuxSource
	{
		enum Type
		{
			MuxSrcOff = 0,
			MuxSrcOn,
			MuxSrcDigIn0,
			MuxSrcDigIn1,
			MuxSrcDigIn2,
			MuxSrcDigIn3,
			MuxSrcDigIn4,
			MuxSrcDigIn5,
			MuxSrcDigIn6,
			MuxSrcDigIn7,
			MuxSrcStrobe0,
			MuxSrcStrobe1,
			MuxSrcStrobe2,
			MuxSrcStrobe3,
			MuxSrcSync0,
			MuxSrcSync1,
			MuxSrcSync2,
			MuxSrcSync3,
			MuxSrcTriggenOut0,
			MuxSrcTriggenOut1,
			MuxSrcTriggenOut2,
			MuxSrcTriggenOut3,
			MuxSrcIoscheduler0Out0,
			MuxSrcIoscheduler0Out1,
			MuxSrcIoscheduler1Out0,
			MuxSrcIoscheduler1Out1,
			MuxSrcIoscheduler2Out0,
			MuxSrcIoscheduler2Out1,
			MuxSrcIoscheduler3Out0,
			MuxSrcIoscheduler3Out1
		};
	}

	namespace VisionBoxLedMode
	{
		enum Type
		{
			LedOff = 0,
			LedOn,
			LedGen0,
			LedGen1,
			LedReset,
			LedSata,
			LedCf,
			LedSataCf,
			LedPci,
			LedSun,
			LedRs232,
			LesRs422
		};
	}

	namespace VisionBoxDigitalOutSource
	{
		enum Type
		{
			DigOutSrcRegister = 0x00,
			DigOutSrcMuxOut0,
			DigOutSrcMuxOut1,
			DigOutSrcMuxOut2,
			DigOutSrcMuxOut3,
			DigOutSrcMuxOut4,
			DigOutSrcMuxOut5,
			DigOutSrcMuxOut6,
			DigOutSrcMuxOut7,
			DigOutSrcMuxOut8,
			DigOutSrcMuxOut9,
			DigOutSrcMuxOut10,
			DigOutSrcMuxOut11,
			DigOutSrcMuxOut12,
			DigOutSrcMuxOut13,
			DigOutSrcMuxOut14,
			DigOutSrcMuxOut15 = 0x10
		};
	}

	namespace VisionBoxRS422OutSource
	{
		enum Type
		{
			RS422SrcRegister = 0x00,
			RS422SrcMuxOut0 ,
			RS422SrcMuxOut1 ,
			RS422SrcMuxOut2 ,
			RS422SrcMuxOut3 ,
			RS422SrcMuxOut4 ,
			RS422SrcMuxOut5 ,
			RS422SrcMuxOut6 ,
			RS422SrcMuxOut7 ,
			RS422SrcMuxOut8 ,
			RS422SrcMuxOut9 ,
			RS422SrcMuxOut10,
			RS422SrcMuxOut11,
			RS422SrcMuxOut12,
			RS422SrcMuxOut13,
			RS422SrcMuxOut14,
			RS422SrcMuxOut15 = 0x10
		};
	}

	namespace VisionBoxIOSchedulerCounter
	{
		enum Type
		{
			IOSchedulerCounterTrigger = 0x1,
			IOSchedulerCounterEncoder = 0x2,
			IOSchedulerCounterTimer = 0x3,
			IOSchedulerCounterEncoderCopy = 0x4,
			IOSchedulerCounterTimerCopy = 0x5
		};
	}

	namespace VisionBoxIOSchedulerCmpSrc
	{
		enum Type
		{
			IOSchedulerCmpSrcTrigger = 0x0,
			IOSchedulerCmpSrcEncoder = 0x1,
			IOSchedulerCmpSrcTimer = 0x2
		};
	}

	namespace VisionBoxIOSchedulerEncoderDir
	{
		enum Type
		{
			IOSchedulerEncoderDirNormal = 0x0,
			IOSchedulerEncoderDirReverse = 0x1
		};
	}

}//avl
#endif //VISION_BOX_ENUMS_H