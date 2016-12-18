//
//  Time.hpp
//  Sea2D
//
//  Created by Jibran Syed on 4/23/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//
#ifndef Time_S2D_hpp
#define Time_S2D_hpp

#include "TimeValue.hpp"
#include "TimeMeasurer.hpp"

namespace sea2d
{
    /// Keeps track of time data for the engine
    class Time
    {
    public:
        
        //
        // Ctor / Dtor
        //
        
        /// Default Ctor
        Time();
        
        /// Dtor
        ~Time();
        
        
        
        //
        // Methods
        //
        
        /// Only to be called by App class!
        void Update();
        
        
        //
        // Static Methods
        //
        
        /// Get the time since the game started (in seconds)
        static const float GetTimeFromStartInSeconds();
        
        /// Get the time between frames (in seconds)
        static const float GetDeltaTimeInSeconds();
        
        /// Get the time since the game started
        static const TimeValue GetTimeFromStart();
        
        /// Get the time between frames
        static const TimeValue GetDeltaTime();
        
        /// Get the number of frames that passed in the program run time so far
        static const uint64_t GetFrameCount();
        
        
    private:
        
        //
        // Data
        //
        
        TimeValue deltaTime;		///< The time between frames
        TimeMeasurer frameTimer;	///< The timer for a frame's duration
        TimeMeasurer startupTimer;	///< The timer for the program's duration
        uint64_t frameCount;        ///< The number of loop iterations of the program
        
        #if DEBUG
            TimeValue debugCurrentTime; ///< DEBUG: Read the current time. Do not use!
        #endif
        
        
        //
        // Static Data
        //
        
        static Time* singletonInstance; ///< Only one time data source
        
        
        //
        // Deleted Methods
        //
        
        /// No Copy ctor
        Time(const Time& other) = delete;
        
        /// No copy assignment
        Time& operator=(const Time& other) = delete;
        
        /// No move ctor
        Time(Time&& other) = delete;
        
        /// No move assignment
        Time& operator=(Time&& other) = delete;
    };
}
#endif /* Time_S2D_hpp */
