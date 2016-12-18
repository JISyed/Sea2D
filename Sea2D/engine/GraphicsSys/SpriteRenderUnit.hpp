//
//  SpriteRenderUnit.hpp
//  Sea2D
//
//  Created by Jibran Syed on 5/10/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#ifndef SpriteRenderUnit_hpp
#define SpriteRenderUnit_hpp

#include "RenderUnit.hpp"
#include "engine/SpriteSys/Sprite.hpp"
#include "engine/SpriteSys/SpriteAnimationPlayback.hpp"

namespace sea2d
{
    // Foward declare Mehs
    class Mesh;
    
    /// A RenderUnit that draws a textured mesh
    class SpriteRenderUnit final : public RenderUnit
    {
    public:
        
        //
        // Essentials
        //
        
        /// Ctor
        SpriteRenderUnit(Shader* const newShader, Sprite* const newSprite);
        
        /// Destructor
        virtual ~SpriteRenderUnit();
        
        
        //
        // Methods
        //
        
        /// Get the sprite used for this render unit
        Sprite* const GetSprite();
        
        
        /// Change the Sprite used for rendering. Do not call while in render loop!
        void ChangeSprite(Sprite* const newSprite);
        
        /// Get the current frame index for this sprite render unit
        const unsigned int GetCurrentFrameIndex() const;
        
        /// Get the current playback speed multiplier of this sprite render unit
        const float GetCurrentPlaybackSpeed() const;
        
        /// Change the playback speed of an animated sprite. 1.0 is normal speed. Should not be negative
        void ChangePlaybackSpeed(const float newPlaybackSpeed);
        
        
    protected:
        
        
        /// Setup render state, such as binding data or setting uniforms (called before OnDraw())
        virtual void OnBeforeDraw() override;
        
        /// Perform actual draw call (or multiple if needed)
        virtual void OnDraw() override;
        
        
        
    private:
        
        //
        // Data
        //
        
        Mesh* mesh;                         ///< Should be Quad
        Sprite* sprite;                     ///< The sprite used by this render unit
        SpriteAnimationPlayback* animator;  ///< Sprite animator
        
        
        //
        // Deleted Methods
        //
        
        /// No Default Ctor
        SpriteRenderUnit() = delete;
        
    };

}
#endif /* SpriteRenderUnit_hpp */
