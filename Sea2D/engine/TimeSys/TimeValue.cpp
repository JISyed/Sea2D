//
//  TimeValue.cpp
//  Sea2D
//
//  Created by Jibran Syed on 4/12/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "TimeValue.hpp"
#include <limits>   // For numeric_limits< Time::Representation >.
#include "engine/AppSys/DebugGuarantee.hpp"


// Time options

/// IMPORTANT: This is private information that is SUBJECT TO CHANGE!
///
/// Currently: 1 second = 30000,
///            1 ms     = 30,
///            1 NTSC   = 500,
///            1 PAL    = 600
///
/// At 32 bits, this gives us a range of roughly -20 to 20 hours.
#define S2D_TIME_VALUE_TO_SECONDS   (30000)


namespace sea2d
{
    //
    // Constructors
    //
    
    // Default Ctor
    TimeValue::TimeValue() :
        internalTime(0)
    {
    }
    
    // Private Representation Ctor
    TimeValue::TimeValue(const TimeValue::Representation newTime) :
        internalTime(newTime)
    {
    }
    
    // TimeBasis Ctor
    TimeValue::TimeValue(const TimeBasis duration) :
        internalTime(0)
    {
        switch (duration)
        {
            case TimeBasis::Zero:
                this->internalTime = 0;
                break;
                
            case TimeBasis::Ntsc60Frame:
                this->internalTime = S2D_TIME_VALUE_TO_SECONDS / 60;
                break;
                
            case TimeBasis::Ntsc30Frame:
                this->internalTime = 2 * S2D_TIME_VALUE_TO_SECONDS / 60;
                break;
                
            case TimeBasis::PalFrame:
                this->internalTime = S2D_TIME_VALUE_TO_SECONDS / 50;
                break;
                
            case TimeBasis::OneSecond:
                this->internalTime = S2D_TIME_VALUE_TO_SECONDS;
                break;
                
            case TimeBasis::OneMillisecond:
                this->internalTime = S2D_TIME_VALUE_TO_SECONDS / 1000;
                break;
                
            case TimeBasis::OneMinute:
                this->internalTime = 60 * S2D_TIME_VALUE_TO_SECONDS;
                break;
                
            case TimeBasis::OneHour:
                this->internalTime = 60 * 60 * S2D_TIME_VALUE_TO_SECONDS;
                break;
                
            case TimeBasis::TimeMin:
                this->internalTime = std::numeric_limits< TimeValue::Representation >::min();
                break;
                
            case TimeBasis::TimeMax:
                this->internalTime = std::numeric_limits< TimeValue::Representation >::max();
                break;
                
            case TimeBasis::InternalTick:
                this->internalTime = 1;
                break;
                
            default:
                guarantee_that(false, "There's a TimeBasis value that needs to be included into the switch statement");
                this->internalTime = 0;
                break;
        }
    }
    
    
    // Copy Ctor
    TimeValue::TimeValue(const TimeValue& rhs) :
        internalTime(rhs.internalTime)
    {
    }
    
    // Copy Assignment
    TimeValue& TimeValue::operator=(const TimeValue& rhs)
    {
        if (this != &rhs)
        {
            this->internalTime = rhs.internalTime;
        }
        
        return *this;
    }
    
    // Dtor
    TimeValue::~TimeValue()
    {
    }
    
    
    
    
    //
    // Friends
    //
    
    // FRIEND
    const TimeValue operator*(const float ratio, const TimeValue& rhs)
    {
        return TimeValue(static_cast<TimeValue::Representation>(ratio * rhs.internalTime));
    }
    
    // FRIEND
    const TimeValue operator*(const int ratio, const TimeValue& rhs)
    {
        return TimeValue(ratio * rhs.internalTime);
    }
    
    // FRIEND
    const TimeValue operator*(const int64_t ratio, const TimeValue& rhs)
    {
        return TimeValue(ratio * rhs.internalTime);
    }
    
    
    
    
    //
    // Comparisons
    //
    
    bool TimeValue::operator==(const TimeValue& rhs) const
    {
        return (this->internalTime == rhs.internalTime);
    }
    
    
    bool TimeValue::operator!=(const TimeValue& rhs) const
    {
        return (this->internalTime != rhs.internalTime);
    }
    
    
    bool TimeValue::operator<(const TimeValue& rhs) const
    {
        return (this->internalTime < rhs.internalTime);
    }
    
    
    bool TimeValue::operator<=(const TimeValue& rhs) const
    {
        return (this->internalTime <= rhs.internalTime);
    }
    
    
    bool TimeValue::operator>(const TimeValue& rhs) const
    {
        return (this->internalTime > rhs.internalTime);
    }
    
    
    bool TimeValue::operator>=(const TimeValue& rhs) const
    {
        return (this->internalTime >= rhs.internalTime);
    }
    
    
    
    
    
    
    
    //
    // Negation / Addition / Subtraction
    //
    
    const TimeValue TimeValue::operator-() const
    {
        return TimeValue(-this->internalTime);
    }
    
    
    const TimeValue TimeValue::operator+(const TimeValue& rhs) const
    {
        // Overflow possible, but not likely on an int64
        return TimeValue(this->internalTime + rhs.internalTime);
    }
    
    
    const TimeValue TimeValue::operator-(const TimeValue& rhs) const
    {
        // Overflow possible, but not likely on an int64
        return TimeValue(this->internalTime - rhs.internalTime);
    }
    
    
    TimeValue& TimeValue::operator+=(const TimeValue& rhs)
    {
        // Overflow possible, but not likely on an int64
        this->internalTime += rhs.internalTime;
        return *this;
    }
    
    
    TimeValue& TimeValue::operator-=(const TimeValue& rhs)
    {
        // Overflow possible, but not likely on an int64
        this->internalTime -= rhs.internalTime;
        return *this;
    }
    
    
    
    
    
    
    
    
    //
    // Multiplication
    //
    
    const TimeValue TimeValue::operator*(const float ratio) const
    {
        // Overflow possible, but not likely on an int64
        return TimeValue(static_cast<Representation>(ratio * this->internalTime));
    }
    
    
    const TimeValue TimeValue::operator*(const int ratio) const
    {
        // Overflow possible, but not likely on an int64
        return TimeValue(this->internalTime * ratio);
    }
    
    
    TimeValue& TimeValue::operator*=(const float ratio)
    {
        // Overflow possible, but not likely on an int64
        this->internalTime = static_cast<Representation>(ratio * this->internalTime);
        return *this;
    }
    
    
    TimeValue& TimeValue::operator*=(const int ratio)
    {
        // Overflow possible, but not likely on an int64
        this->internalTime *= ratio;
        return *this;
    }
    
    
    
    
    
    
    
    //
    // Division
    //
    
    float TimeValue::operator/(const TimeValue& denominator) const
    {
        guarantee_that(denominator.internalTime != 0, "TimeValue division: Divide by zero detected");
        return static_cast<float>(this->internalTime) / static_cast<float>(denominator.internalTime);
    }
    
    
    const TimeValue TimeValue::operator/(const float denominator) const
    {
        guarantee_that(denominator != 0, "TimeValue division: Divide by zero detected");
        return TimeValue(static_cast<Representation>(this->internalTime / denominator));
    }
    
    
    const TimeValue TimeValue::operator/(const int denominator) const
    {
        guarantee_that(denominator != 0, "TimeValue division: Divide by zero detected");
        return TimeValue(this->internalTime / denominator);
    }
    
    
    TimeValue& TimeValue::operator/=(const float denominator)
    {
        guarantee_that(denominator != 0, "TimeValue division: Divide by zero detected");
        this->internalTime = static_cast<Representation>(this->internalTime / denominator);
        return *this;
    }
    
    
    TimeValue& TimeValue::operator/=(const int denominator)
    {
        guarantee_that(denominator != 0, "TimeValue division: Divide by zero detected");
        this->internalTime /= denominator;
        return *this;
    }
    
    
    
    
    
    
    //
    // Quotient / Remainder
    //
    
    int TimeValue::quotient(const TimeValue& numerator, const TimeValue& denominator)
    {
        guarantee_that(denominator.internalTime != 0, "TimeValue quotient: Divide by zero detected");
        // !!! FIXME: Check range
        return static_cast<int> (numerator.internalTime / denominator.internalTime);
    }
    
    const TimeValue TimeValue::remainder(const TimeValue& numerator, const TimeValue& denominator)
    {
        guarantee_that(denominator.internalTime != 0, "TimeValue remainder: Divide by zero detected");
        return TimeValue(numerator.internalTime % denominator.internalTime);
    }
    
    
    
    //
    // Other Operators
    //
    
    /// Get the time in a readable format given a time basis. (Zero, TimeMin, and TimeMax are invalid parameters)
    const float TimeValue::GetReadableTime(const TimeBasis timeBasis) const
    {
        return this->operator/(TimeValue(timeBasis));
    }
    
    /// Get the time in a readable format given a time basis. (Zero, TimeMin, and TimeMax are invalid parameters) (Need to pass in an int to get the remaining time in a smaller format)
    const int TimeValue::GetReadableTime(const TimeBasis timeBasis, int& inOutRemainderTime) const
    {
        if(timeBasis == TimeBasis::Zero || timeBasis == TimeBasis::TimeMin || timeBasis == TimeBasis::TimeMax)
        {
            return 0;
        }
    
        int resultTime = 0;
        inOutRemainderTime = 0;
        const TimeValue BaseTime(timeBasis);
        TimeValue remainder;
        TimeBasis smallerBasis = TimeBasis::InternalTick;
        
        resultTime = TimeValue::quotient(*this, BaseTime);
        remainder = TimeValue::remainder(*this, BaseTime);
        
        switch (timeBasis)
        {
            case TimeBasis::OneSecond:
            {
                smallerBasis = TimeBasis::OneMillisecond;
                break;
            }
            case TimeBasis::OneMinute:
            {
                smallerBasis = TimeBasis::OneSecond;
                break;
            }
            case TimeBasis::OneHour:
            {
                smallerBasis = TimeBasis::OneMinute;
                break;
            }
            case TimeBasis::Ntsc60Frame:
            {
                smallerBasis = TimeBasis::OneMillisecond;
                break;
            }
            case TimeBasis::Ntsc30Frame:
            {
                smallerBasis = TimeBasis::OneMillisecond;
                break;
            }
            case TimeBasis::PalFrame:
            {
                smallerBasis = TimeBasis::OneMillisecond;
                break;
            }
            default:
            {
                break;
            }
        }
        
        inOutRemainderTime = TimeValue::quotient(remainder, TimeValue(smallerBasis));
            
        return resultTime;
    }
    
}
