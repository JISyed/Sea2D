//
//  SpriteAnimationPlayback.cpp
//  Sea2D
//
//  Created by Jibran Syed on 5/10/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "SpriteAnimationPlayback.hpp"
#include "engine/AppSys/DebugGuarantee.hpp"
#include <iostream>
using namespace std;

namespace sea2d
{
    // Default Ctor
    SpriteAnimationPlayback::SpriteAnimationPlayback() :
        frameTimer(),
        currentFrameIdx(0),
        playbackSpeed(1.0f),
        exceededTime(TimeBasis::Zero)
    {
        this->frameTimer.Start();
    }
    
    // Dtor
    SpriteAnimationPlayback::~SpriteAnimationPlayback()
    {
    }
    
    
    
    /// Update the animation of a sprite given its animation data
    void SpriteAnimationPlayback::UpdateAnimation(const SpriteAnimationData* const animData)
    {
        // Only update anything if there is an animation for this sprite
        if(animData != nullptr)
        {
            // One frame plays for a certain time ...
            const TimeValue scaledframeTime = (1.0f / this->playbackSpeed) * animData->frameTime;
            const TimeValue elapsedInterval = this->frameTimer.GetElapsedTime() + this->exceededTime;
            
            // ... is that time up?
            if(elapsedInterval > scaledframeTime)
            {
                // Calculate the extra time elapsed after the regular frame time
                TimeValue extraTime = elapsedInterval - scaledframeTime;
                
                // If elasped time is too big, multiple frames may have to be skipped
                do
                {
                    // Next frame
                    this->GoToNextFrame(animData);
                    
                    // Reduce the frame's time from the extra time
                    extraTime -= scaledframeTime;
                    //tally++;
                } while(extraTime > scaledframeTime);
                
                guarantee_that(extraTime <= scaledframeTime, "Sprite animation: there is still more extra frame time than the current frame that was not processed!");
                
                // The remaining extra time is less than the frame time and will be factored next animation loop as "exceeded time"
                this->exceededTime = extraTime;
                
                // Reset frame timer
                this->frameTimer.Start();
            }
        }
    }
    
    
    /// Get the current index of the Sprite
    const unsigned int SpriteAnimationPlayback::GetCurrentFrameIndex() const
    {
        return this->currentFrameIdx;
    }
    
    /// Get the current playback speed multiplier of this sprite
    const float SpriteAnimationPlayback::GetPlaybackSpeed() const
    {
        return this->playbackSpeed;
    }
    
    /// Change the playback speed multiplier for this sprite. 1.0 is normal speed. Cannot be negative
    void SpriteAnimationPlayback::ChangePlaybackSpeed(const float newPlaybackSpeed)
    {
        if(newPlaybackSpeed < 0)
        {
            this->playbackSpeed = -newPlaybackSpeed;
        }
        else
        {
            this->playbackSpeed = newPlaybackSpeed;
        }
    }
    
    /// Reset the current frame to zero
    void SpriteAnimationPlayback::ResetFrameIndex()
    {
        this->currentFrameIdx = 0;
    }
    
    
    
    
    /// Proceed to the next frame in the animation. Corrects for last frame
    void SpriteAnimationPlayback::GoToNextFrame(const SpriteAnimationData* const animData)
    {
        // Next frame
        this->currentFrameIdx++;
        
        // Last frame?
        if(this->currentFrameIdx >= animData->numberOfFrames)
        {
            if(animData->isLooping)
            {
                // Loop to beginning
                this->currentFrameIdx = 0;
            }
            else
            {
                // Stay at last frame
                this->currentFrameIdx = animData->numberOfFrames - 1;
            }
        }
    }
    
    
}
