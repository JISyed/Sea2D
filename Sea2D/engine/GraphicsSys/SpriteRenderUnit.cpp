//
//  SpriteRenderUnit.cpp
//  Sea2D
//
//  Created by Jibran Syed on 5/10/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "SpriteRenderUnit.hpp"
#include "MeshRegistry.hpp"
#include "Texture.hpp"
#include "engine/SpriteSys/ImageFrame.hpp"
#include "Shader.hpp"

namespace sea2d
{
    // Default Ctor
    SpriteRenderUnit::SpriteRenderUnit(Shader* const newShader, Sprite* const newSprite) :
        RenderUnit(newShader),
        mesh(nullptr),
        sprite(newSprite),
        animator(new SpriteAnimationPlayback())
    {
        static const unsigned int QuadMeshId = MeshRegistry::Find("Quad")->GetId();
        this->mesh = MeshRegistry::Find(QuadMeshId);
        
        guarantee_that(newShader != nullptr, "New RenderUnit cannot take in null shader!");
        guarantee_that(newSprite != nullptr, "New RenderUnit cannot take in null sprite!");
    }
    
    // VIRTUAL
    // Dtor
    SpriteRenderUnit::~SpriteRenderUnit()
    {
        delete this->animator;
    }
    
    
    
    /// Get the sprite used for this render unit
    Sprite* const SpriteRenderUnit::GetSprite()
    {
        return this->sprite;
    }
    
    
    /// Change the texture used for rendering. Do not call while in render loop!
    void SpriteRenderUnit::ChangeSprite(Sprite *const newSprite)
    {
        guarantee_that(newSprite != nullptr, "Changing sprite, but being given a null sprite!");
        
        this->sprite = newSprite;
        this->animator->ResetFrameIndex();
    }
    
    /// Get the current frame index for this sprite render unit
    const unsigned int SpriteRenderUnit::GetCurrentFrameIndex() const
    {
        return this->animator->GetCurrentFrameIndex();
    }
    
    /// Get the current playback speed multiplier of this sprite render unit
    const float SpriteRenderUnit::GetCurrentPlaybackSpeed() const
    {
        return this->animator->GetPlaybackSpeed();
    }
    
    /// Change the playback speed of an animated sprite
    void SpriteRenderUnit::ChangePlaybackSpeed(const float newPlaybackSpeed)
    {
        this->animator->ChangePlaybackSpeed(newPlaybackSpeed);
    }
    
    
    
    // VIRTUAL OVERRIDE
    /// Setup render state, such as binding data or setting uniforms (called before OnDraw())
    void SpriteRenderUnit::OnBeforeDraw()
    {
        this->mesh->MakeActive();
        this->sprite->GetOriginatingTexture()->MakeActive();
        
        // Update animation, if one exist (animator will exist regardless)
        this->animator->UpdateAnimation(this->sprite->GetAnimationData());
        
        Rect normalizedDimensions = this->sprite->operator[](this->animator->GetCurrentFrameIndex())->GetNormalizedDimensions();
        
        // This weird calculation is needed to translate the texture's origin to OpenGL's origin (top-left vs. bottom-left)
        normalizedDimensions.origin.y() = 1.0f - normalizedDimensions.origin.y() - normalizedDimensions.height;
        
        this->GetShader()->SetUniform("spriteRectUV", normalizedDimensions);
    }
    
    // VIRTUAL OVERRIDE
    /// Perform actual draw call (or multiple if needed)
    void SpriteRenderUnit::OnDraw()
    {
        glDrawElements(GL_TRIANGLES, this->mesh->GetNumberOfTriangles() * 3, GL_UNSIGNED_INT, 0);
    }
}
