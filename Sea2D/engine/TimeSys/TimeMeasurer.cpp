//
//  TimeMeasurer.cpp
//  Sea2D
//
//  Created by Jibran Syed on 4/12/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "TimeMeasurer.hpp"
#include "engine/AppSys/DebugGuarantee.hpp"
#include <mach/mach_time.h>

namespace sea2d
{
    // Default Ctor
    TimeMeasurer::TimeMeasurer() :
        startingTime(TimeBasis::TimeMax)
    {
    }
    
    // Dtor
    TimeMeasurer::~TimeMeasurer()
    {
    }
    
    
    
    /// Start the timer. Can also be used to reset the timer
    void TimeMeasurer::Start()
    {
        this->startingTime = TimeMeasurer::GetSystemTime();
    }
    
    
    
    /// Get the elapsed time since the timer started
    /// @remark  Does not reset the timer
    /// @remark  If the timer never started, returns TimeValue(TimeBasis::Zero)
    /// @return  The time from when the timer started to when this method was called
    const TimeValue TimeMeasurer::GetElapsedTime() const
    {
        /// The time since the timer started.
        /// If timer didn't start, zero time will be returned
        TimeValue elapsedTime(TimeBasis::Zero);
        
        // Check if the timer started (timer not at TimeMax)
        if(this->startingTime != TimeValue(TimeBasis::TimeMax))
        {
            const TimeValue currentTime = TimeMeasurer::GetSystemTime();
            elapsedTime = currentTime - this->startingTime;
        }
        
        
        
        return elapsedTime;
    }
    
    
    // STATIC
    // This helped: https://developer.apple.com/library/mac/qa/qa1398/_index.html
    /// Use OS's internal clock to get the current time since app launch
    const TimeValue TimeMeasurer::GetSystemTime()
    {
        /// One Millisecond in TimeValue terms
        //static const TimeValue ONE_MILLISECOND(TimeBasis::OneMillisecond);
        static const TimeValue INTERNAL_TICK(TimeBasis::InternalTick);
        
        /// The time base information, local to this Apple computer
        static mach_timebase_info_data_t s_timebaseInfo;
        static bool s_timeInfoIsSetup = false;
        if(s_timeInfoIsSetup == false)
        {
            mach_timebase_info(&s_timebaseInfo);
            s_timeInfoIsSetup = true;
        }
        
        /// The current time from the computer's perspective
        uint64_t currentTimeMach = mach_absolute_time();
        
        #define S2D_MS_TO_TICKS 30
        // First factor in milliseconds and ticks, then factor in Apple's time to nanoseconds. May help prevent interger overflow
        // 1 ms = 1,000,000 ns = 30 internal TimeValue ticks
        uint64_t currentTimeMS = currentTimeMach / (1000000/S2D_MS_TO_TICKS);
        currentTimeMS *= s_timebaseInfo.numer;
        currentTimeMS /= s_timebaseInfo.denom;
        
        /// The current time in milliseconds
        //uint64_t currentTimeMS = 0;
        
        // Get the time in nanoseconds
        //currentTimeMS = (uint64_t) (currentTimeMach * (s_timebaseInfo.numer / (double)s_timebaseInfo.denom));
        
        // Get the time in milliseconds
        //currentTimeMS /= 1000000;
        
        // Convert to TimeValue
        //TimeValue systemTime = (int64_t)currentTimeMS * ONE_MILLISECOND;
        TimeValue systemTime = (int64_t)currentTimeMS * INTERNAL_TICK;
        return systemTime;
    }
    
    
    
}