//
//  SpriteAnimationData.hpp
//  Sea2D
//
//  Created by Jibran Syed on 5/10/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//
#ifndef SpriteAnimationData_hpp
#define SpriteAnimationData_hpp

#include "engine/TimeSys/TimeValue.hpp"

namespace sea2d
{
    /// Data about a Sprite animation that doesn't change
    struct SpriteAnimationData
    {
        //
        // Methods
        //
        
        SpriteAnimationData();
        SpriteAnimationData(const TimeValue& newFrameTime, const unsigned int numOfFrames, const bool willLoop);
        
        
        //
        // Data
        //
        
        TimeValue frameTime;            ///< The amount of time for 1 frame to play
        unsigned int numberOfFrames;    ///< The total number of frames in this animation
        bool isLooping;                 ///< Does this animation loop?
    };
}
#endif /* SpriteAnimationData_hpp */
