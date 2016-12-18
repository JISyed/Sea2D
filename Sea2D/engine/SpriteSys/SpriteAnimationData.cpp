//
//  SpriteAnimationData.cpp
//  Sea2D
//
//  Created by Jibran Syed on 5/10/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "SpriteAnimationData.hpp"

namespace sea2d
{
    SpriteAnimationData::SpriteAnimationData() :
        frameTime(TimeBasis::Zero),
        numberOfFrames(0),
        isLooping(false)
    {
    }
    
    SpriteAnimationData::SpriteAnimationData(const TimeValue& newFrameTime, const unsigned int numOfFrames, const bool willLoop) :
        frameTime(newFrameTime),
        numberOfFrames(numOfFrames),
        isLooping(willLoop)
    {
    }
    
    
}
