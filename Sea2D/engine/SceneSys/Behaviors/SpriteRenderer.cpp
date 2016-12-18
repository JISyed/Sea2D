//
//  SpriteRenderer.cpp
//  Sea2D
//
//  Created by Jibran Syed on 5/10/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "SpriteRenderer.hpp"
#include "engine/SceneSys/Entities/Transform.hpp"
#include "engine/SceneSys/Entities/Entity.hpp"

#include "engine/MathSys/math3d/Matrix4x4.hpp"

#include "engine/GraphicsSys/RenderUnitRegistry.hpp"
#include "engine/GraphicsSys/ShaderRegistry.hpp"
#include "engine/SpriteSys/SpriteRegistry.hpp"

#include "ImageFrame.hpp"

namespace sea2d
{
    //
    // Ctor / Dtor
    //
    
    /// Default Ctor
    SpriteRenderer::SpriteRenderer() :
        renderUnit(nullptr)
    {
        this->renderUnit = new SpriteRenderUnit(ShaderRegistry::Find("Sprite"), SpriteRegistry::Find(1));
        RenderUnitRegistry::Add(this->renderUnit);
    }
    
    // VIRTUAL
    /// Destructor
    SpriteRenderer::~SpriteRenderer()
    {
        if(this->renderUnit != nullptr)
        {
            RenderUnitRegistry::Remove(this->renderUnit->GetId());
            this->renderUnit = nullptr;
        }
    }
    
    
    
    //
    // Additonal Methods
    //
    
    
    /// Will this render behavior draw in the render loop?
    const bool SpriteRenderer::WillDraw() const
    {
        return this->renderUnit->WillDraw();
    }
    
    /// Set whether this render behavior will draw or not
    void SpriteRenderer::SetDrawFlag(const bool willDraw)
    {
        this->renderUnit->SetDrawFlag(willDraw);
    }
    
    /// Get the tint color of this render behavior
    const Color& SpriteRenderer::GetTintColor() const
    {
        return this->renderUnit->GetTintColor();
    }
    
    /// Set the tint color of this render behavior
    void SpriteRenderer::SetTintColor(const Color& newTintColor)
    {
        this->renderUnit->SetTintColor(newTintColor);
    }
    
    
    /// Get the current shader of this render unit
    Shader* const SpriteRenderer::GetShader()
    {
        return this->renderUnit->GetShader();
    }
    
    /// Change the shader of this render unit
    void SpriteRenderer::ChangeShader(Shader* const newShader)
    {
        this->renderUnit->ChangeShader(newShader);
    }
    
    /// Get the Sprite used in this renderer
    Sprite* const SpriteRenderer::GetSprite() const
    {
        return this->renderUnit->GetSprite();
    }
    
    /// Change the Sprite used in this renderer
    void SpriteRenderer::ChangeSprite(Sprite* const differentSprite)
    {
        this->renderUnit->ChangeSprite(differentSprite);
    }
    
    /// Get the current playback speed multiplier if the sprite is animated
    const float SpriteRenderer::GetCurrentPlaybackSpeed() const
    {
        return this->renderUnit->GetCurrentPlaybackSpeed();
    }
    
    /// Change the playback speed multiplier if the sprite is animated
    void SpriteRenderer::ChangePlaybackSpeed(const float newPlaybackSpeed)
    {
        guarantee_that(newPlaybackSpeed != 0.0f, "Sprite animation: Playback speed cannot be 0. Will cause divide-by-zero error!");
        
        this->renderUnit->ChangePlaybackSpeed(newPlaybackSpeed);
    }
    
    
    
    
    //
    // Behavior Identity
    //
    
    // VIRTUAL OVERRIDE
    /// Get the identity unique to this behavior type. Defined in BehaviorIdentity enum
    const BehaviorIdentity SpriteRenderer::GetBehaviorIdentity() const
    {
        return BehaviorIdentity::SpriteRenderer;
    }
    
    
    
    
    //
    // Events
    //
    
    // VIRTUAL OVERRIDE
    /// Called when the Behavior is added to an Entity (called after constructor)
    void SpriteRenderer::OnStart()
    {
        
    }
    
    
    // VIRTUAL OVERRIDE
    /// Called every iteration of the game loop
    void SpriteRenderer::OnUpdate()
    {
        Transform& transform = this->GetEntity()->GetTransform();
        
        // Construct model matrix
        math3d::Matrix4x4 modelMatrix;
        {
            const Vector2 vT = transform.GetGlobalPosition();
            
            // Get total scale (from Entity and from Sprite)
            const Vector2 entityS = transform.GetGlobalScale();
            const Rect spriteRect = this->renderUnit->GetSprite()->operator[](this->renderUnit->GetCurrentFrameIndex())->GetPixelDimensions();
            const Vector2 spriteS = Vector2(spriteRect.width, spriteRect.height);
            const Vector2 vS = Vector2(entityS.x() * spriteS.x(),
                                       entityS.y() * spriteS.y());
            
            
            // The depth is the Z position in this engine
            const float zPosition = transform.GetDepth();
            
            const math3d::Matrix4x4 mT = math3d::Matrix4x4(math3d::TranslationMatrix, vT.x(), vT.y(), zPosition);
            
            const math3d::Matrix4x4 mS = math3d::Matrix4x4(math3d::ScaleMatrix, vS.x(), vS.y(), 1.0f);
            
            const math3d::Matrix4x4 mR = math3d::Matrix4x4(math3d::RotationMatrixZ, transform.GetGlobalRotation());
            
            // Scale * Rotate * Translate
            modelMatrix = mS * mR * mT;
        }
        
        // Send model matrix into render unit. It will use it later to draw
        this->renderUnit->SetModelMatrix(modelMatrix);
    }
    
    
    // VIRTUAL OVERRIDE
    /// Called whene the Behavior is removed from an Entity (called before destructor)
    void SpriteRenderer::OnDestroy()
    {
        // Intentionally empty
    }
}
