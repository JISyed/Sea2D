//
//  SpriteAnimationPlayback.hpp
//  Sea2D
//
//  Created by Jibran Syed on 5/10/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//
#ifndef SpriteAnimationPlayback_hpp
#define SpriteAnimationPlayback_hpp

#include "SpriteAnimationData.hpp"
#include "engine/TimeSys/TimeMeasurer.hpp"

namespace sea2d
{
    /// Represents instanced animation of a Sprite
    class SpriteAnimationPlayback
    {
    public:
        
        //
        // Essentials
        //
        
        // Default Ctor
        SpriteAnimationPlayback();
        
        // Destructor
        ~SpriteAnimationPlayback();
        
        
        //
        // Methods
        //
        
        /// Update the animation of a sprite given its animation data
        void UpdateAnimation(const SpriteAnimationData* const animData);
        
        /// Get the current index of the Sprite
        const unsigned int GetCurrentFrameIndex() const;
        
        /// Get the current playback speed multiplier of this sprite
        const float GetPlaybackSpeed() const;
        
        /// Change the playback speed multiplier for this sprite. 1.0 is normal speed. Cannot be negative
        void ChangePlaybackSpeed(const float newPlaybackSpeed);
        
        /// Reset the current frame to zero
        void ResetFrameIndex();
        
    private:
        
        //
        // Data
        //
        
        TimeMeasurer frameTimer;        ///< The timer that determines when to go to next frame
        unsigned int currentFrameIdx;   ///< The index of the current ImageFrame
        float playbackSpeed;            ///< The speed multiplier for playback
        TimeValue exceededTime;         ///< The amount of elapsed time exceeded from the frame time
        
        
        
        //
        // Private Methods
        //
        
        /// Proceed to the next frame in the animation. Corrects for last frame
        void GoToNextFrame(const SpriteAnimationData* const animData);
        
        
        
        //
        // Deleted Methods
        //
        
        // Copy Ctor
        SpriteAnimationPlayback(const SpriteAnimationPlayback& other) = delete;
        
        // Copy Assignment
        SpriteAnimationPlayback& operator=(const SpriteAnimationPlayback& rhs) = delete;
        
    };
}
#endif /* SpriteAnimationPlayback_hpp */
