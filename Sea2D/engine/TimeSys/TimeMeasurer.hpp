//
//  TimeMeasurer.hpp
//  Sea2D
//
//  Created by Jibran Syed on 4/12/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#ifndef TimeMeasurer_hpp
#define TimeMeasurer_hpp

#include "engine/TimeSys/TimeValue.hpp"

namespace sea2d
{
    /// Timer class that measures durations of time using TimeValue
    class TimeMeasurer
    {
    public:
        
        //
        // Essentials
        //
        
        /// Default Ctor
        TimeMeasurer();
        
        
        
        /// Destructor
        ~TimeMeasurer();
        
        
        
        
        //
        // Methods
        //
        
        /// Start the timer. Can also be used to reset the timer
        void Start();
        
        /// Get the elapsed time since the timer started
        /// @remark  Does not reset the timer
        /// @remark  If the timer never started, returns TimeValue(TimeBasis::Zero)
        /// @return  The time from when the timer started to when this method was called
        const TimeValue GetElapsedTime() const;
        
        
        
        
    private:
        
        //
        // Data
        //
        
        TimeValue startingTime;     ///< The starting time of the timer
        
        
        
        //
        // Private Routines
        //
        
        /// Use OS's internal clock to get the current time since app launch
        static const TimeValue GetSystemTime();
        
        
        
        //
        // Deleted Methods
        //
        
        /// No Copy Ctor
        TimeMeasurer(const TimeMeasurer& other) = delete;
        
        /// No Copy Assignment
        TimeMeasurer& operator=(const TimeMeasurer& rhs) = delete;
        
    };
}

#endif /* TimeMeasurer_hpp */
