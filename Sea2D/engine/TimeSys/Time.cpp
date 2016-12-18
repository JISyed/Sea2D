//
//  Time.cpp
//  Sea2D
//
//  Created by Jibran Syed on 4/23/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "Time.hpp"
#include "engine/AppSys/DebugGuarantee.hpp"

namespace sea2d
{
    //
    // Static data
    //
    
    static const TimeValue ONE_SECOND(TimeBasis::OneSecond);
    Time* Time::singletonInstance = nullptr;
    
    
    //
    // Methods
    //
    
    Time::Time() :
        deltaTime(TimeBasis::Ntsc60Frame),
        frameTimer(),
        startupTimer(),
        frameCount(0)
    {
        // Singeton must not exist yet
        guarantee_that(Time::singletonInstance == nullptr, "Time class ctor: There can only be one instance");
        Time::singletonInstance = this;
        
        frameTimer.Start();
        startupTimer.Start();
    }
    
    Time::~Time()
    {
        guarantee_that(Time::singletonInstance != nullptr, "Time class dtor: singeton instance does not exist!");
        Time::singletonInstance = nullptr;
    }
    
    
    
    // Only to be called by App class!
    void Time::Update()
    {
        // Get current delta time
        this->deltaTime = this->frameTimer.GetElapsedTime();
        guarantee_that(this->deltaTime != TimeValue(TimeBasis::Zero), "Delta time should not be zero!");
        
        // Update frame count
        ++(this->frameCount);
        
        #if DEBUG
            this->debugCurrentTime = this->startupTimer.GetElapsedTime();
        #endif
        
        // Reset frame timer
        this->frameTimer.Start();
    }
    
    
    
    
    // STATIC
    // Get the time since the game started
    const float Time::GetTimeFromStartInSeconds()
    {
        return Time::singletonInstance->startupTimer.GetElapsedTime() / ONE_SECOND;
    }
    
    
    // STATIC
    // Get the time between frames
    const float Time::GetDeltaTimeInSeconds()
    {
        return Time::singletonInstance->deltaTime / ONE_SECOND;
    }
    
    
    // STATIC
    // Get the time since the game started
    const TimeValue Time::GetTimeFromStart()
    {
        return Time::singletonInstance->startupTimer.GetElapsedTime();
    }
    
    // STATIC
    // Get the time between frames
    const TimeValue Time::GetDeltaTime()
    {
        return Time::singletonInstance->deltaTime;
    }
    
    // STATIC
    /// Get the number of frames that passed in the program run time so far
    const uint64_t Time::GetFrameCount()
    {
        return Time::singletonInstance->frameCount;
    }
    
}