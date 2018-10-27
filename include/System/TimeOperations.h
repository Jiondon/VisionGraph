//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVS_TIMEOPERATIONS_H
#define AVS_TIMEOPERATIONS_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/AtlString.h"
#include "ATL/AtlTypes.h"
#include "ATL/Array.hxx"
#include "ATL/Optional.h"

namespace avl
{


	/// <summary>Returns a string containing the date time information in selected format and all of the date time data separately.</summary>
	/// <param name="inFormat">Date time string format. Default value: \"%x %X\".</param>
	/// <param name="outDateTimeString">Date time string.</param>
	/// <param name="outMilliseconds">Milliseconds [0-999].</param>
	/// <param name="outSeconds">Seconds [0-60].</param>
	/// <param name="outMinutes">Minutes [0-59].</param>
	/// <param name="outHour">Hour in 24h format [0-23].</param>
	/// <param name="outDayOfMonth">Day of the month [1-31].</param>
	/// <param name="outMonth">Month as a decimal number [1-12].</param>
	/// <param name="outYear">Year.</param>
	/// <param name="outDayOfWeek">Day of the week as a decimal number with Sunday as 0 [0-6].</param>
	/// <param name="outDayOfYear">Day of the year [1-366].</param>
	/// <param name="outTimezoneOffset">Offset relative to UTC in seconds (negative value for positive time zone).</param>
	/// <param name="outDaylightSaving">Whether current local time is subject to Daylight Saving.</param>
	AVL_FUNCTION void CurrentDateTime
	(
		const atl::String&	inFormat,			
		atl::String&	outDateTimeString,		
		int&			outMilliseconds,		
		int&			outSeconds,				
		int&			outMinutes,				
		int&			outHour,				
		int&			outDayOfMonth,			
		int&			outMonth,				
		int&			outYear,				
		int&			outDayOfWeek,			
		int&			outDayOfYear,			
		int&			outTimezoneOffset,		
		bool&			outDaylightSaving		
	)
	THROW_AVL_ERRORS;

	/// <summary>Suspends the program workflow for inTime milliseconds.</summary>
	/// <param name="inTime">Target time in milliseconds. Default value: 100.</param>
	AVL_FUNCTION void Delay
	(
		int	inTime 
	)
	THROW_AVL_ERRORS;

	struct DelayByPeriodState : public BaseState
	{
		int value;
		atl::timer_t lastInvokeTime;
	};


	/// <summary>Suspends the program workflow for inTime milliseconds relative to the end of the filter's last invoke time.</summary>
	/// <param name="inTime">Target period in milliseconds. Default value: 100.</param>
	AVL_FUNCTION void DelayByPeriod
	(
		DelayByPeriodState&	ioState,
		int					inTime	
	)
	THROW_AVL_ERRORS;

	struct MeasureState : public BaseState
	{
		atl::timer_t lastInvokeTime;
	};


	/// <summary>Returns elapsed time in milliseconds from last filter call.</summary>
	/// <param name="outTime">Elapsed time in milliseconds.</param>
	/// <param name="outFrequency">The resulting frequency in Hz or FPS.</param>
	AVL_FUNCTION void MeasurePeriod
	(
		MeasureState&			ioState,
		float&				outTime,		
		float&				outFrequency	
	)
	THROW_AVL_ERRORS;

	typedef atl::int64 ClockTime;


	/// <summary>Starts clock to measure performance.</summary>
	/// <param name="outStartTime">Start time.</param>
	AVL_FUNCTION void StartClock
	(
		avl::ClockTime&	outStartTime	
	)
	THROW_AVL_ERRORS;

	/// <summary>Stops clock to measure performance.</summary>
	/// <param name="inStartTime">Start time - use StartClock filter.</param>
	/// <param name="outElapsedTime">Time in milliseconds from last StartClock call.</param>
	AVL_FUNCTION void GetClockTime_Deprecated
	(
		const avl::ClockTime&	inStartTime,		
		float&				outElapsedTime		
	)
	THROW_AVL_ERRORS;

	/// <summary>Stops clock to measure performance.</summary>
	/// <param name="inStartTime">Start time - use StartClock filter.</param>
	/// <param name="outElapsedTime">Time in milliseconds from last StartClock call.</param>
	AVL_FUNCTION void GetClockTime
	(
		const avl::ClockTime&	inStartTime,		
		double&			outElapsedTime		
	)
	THROW_AVL_ERRORS;

} // namespace avl

namespace avs
{

	struct ClockTimeState : public avl::BaseState
	{
		atl::timer_t firstInvokeTime;
	};


	/// <summary>Stops clock to measure performance.</summary>
	/// <param name="inStartTime">Start time - use StartClock filter. Default value: atl::NIL.</param>
	/// <param name="outElapsedTime">Time in milliseconds from last StartClock call.</param>
	AVL_FUNCTION void AvsFilter_GetClockTime_Deprecated
	(
		avs::ClockTimeState&					ioState,
		atl::Optional<const avl::ClockTime&>	inStartTime,		
		float&								outElapsedTime		
	)
	THROW_AVL_ERRORS;

	/// <summary>Stops clock to measure performance.</summary>
	/// <param name="inStartTime">Start time - use StartClock filter. Default value: atl::NIL.</param>
	/// <param name="outElapsedTime">Time in milliseconds from last StartClock call.</param>
	AVL_FUNCTION void AvsFilter_GetClockTime
	(
		avs::ClockTimeState&					ioState,
		atl::Optional<const avl::ClockTime&>	inStartTime,		
		double&							outElapsedTime		
	)
	THROW_AVL_ERRORS;

} // namespace avs

#endif // AVS_TIMEOPERATIONS_H

