//
//  SpriteRenderer.hpp
//  Sea2D
//
//  Created by Jibran Syed on 5/10/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//
#ifndef SpriteRenderer_hpp
#define SpriteRenderer_hpp

#include "Behavior.hpp"
#include "engine/GraphicsSys/SpriteRenderUnit.hpp"

namespace sea2d
{
    /// Behavior that draws Entity with TexturedMeshRenderUnit
    class SpriteRenderer final : public Behavior
    {
    public:
        
        //
        // Essentials
        //
        
        /// Default Ctor
        SpriteRenderer();
        
        /// Destructor
        virtual ~SpriteRenderer();
        
        /// Get the identity unique to this behavior type. Defined in BehaviorIdentity enum
        virtual const BehaviorIdentity GetBehaviorIdentity() const override;
        
        
        
        //
        // Additonal Methods
        //
        
        
        /// Will this render behavior draw in the render loop?
        const bool WillDraw() const;
        
        /// Set whether this render behavior will draw or not
        void SetDrawFlag(const bool willDraw);
        
        /// Get the tint color of this render behavior
        const Color& GetTintColor() const;
        
        /// Set the tint color of this render behavior
        void SetTintColor(const Color& newTintColor);
        
        
        /// Get the current shader of this render unit
        Shader* const GetShader();
        
        /// Change the shader of this render unit
        void ChangeShader(Shader* const newShader);
        
        
        /// Get the Sprite used in this renderer
        Sprite* const GetSprite() const;
        
        /// Change the Sprite used in this renderer
        void ChangeSprite(Sprite* const differentSprite);
        
        /// Get the current playback speed multiplier if the sprite is animated
        const float GetCurrentPlaybackSpeed() const;
        
        /// Change the playback speed of an animated sprite. 1.0 is normal speed. If negative, will force value as positive.
        void ChangePlaybackSpeed(const float newPlaybackSpeed);
        
        
        
    protected:
        
        
        //
        // Events
        //
        
        /// Called when the Behavior is added to an Entity (called after constructor)
        virtual void OnStart() override;
        
        /// Called every iteration of the game loop
        virtual void OnUpdate() override;
        
        /// Called whene the Behavior is removed from an Entity (called before destructor)
        virtual void OnDestroy() override;
        
        
    private:
        
        //
        // Data
        //
        
        SpriteRenderUnit* renderUnit;
        
        
        
    };
}
#endif /* SpriteRenderer_hpp */
