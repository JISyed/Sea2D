//
//  BitmapText.cpp
//  Sea2D
//
//  Created by Jibran Syed on 6/8/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "BitmapText.hpp"
#include "engine/SceneSys/Entities/Transform.hpp"
#include "engine/SceneSys/Entities/Entity.hpp"

#include "engine/MathSys/math3d/Matrix4x4.hpp"

#include "engine/GraphicsSys/RenderUnitRegistry.hpp"
#include "engine/SpriteSys/BitmapFontRegistry.hpp"
#include "engine/GraphicsSys/ShaderRegistry.hpp"


namespace sea2d
{
    //
    // Ctor / Dtor
    //
    
    /// Default Ctor
    BitmapText::BitmapText() :
        renderUnit(nullptr)
    {
        this->renderUnit = new BitmapTextRenderUnit(ShaderRegistry::Find("BitmapFont"), BitmapFontRegistry::Find(1), "Testing");
        RenderUnitRegistry::Add(this->renderUnit);
    }
    
    // VIRTUAL
    /// Destructor
    BitmapText::~BitmapText()
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
    const bool BitmapText::WillDraw() const
    {
        return this->renderUnit->WillDraw();
    }
    
    /// Set whether this render behavior will draw or not
    void BitmapText::SetDrawFlag(const bool willDraw)
    {
        this->renderUnit->SetDrawFlag(willDraw);
    }
    
    /// Get the tint color of this render behavior
    const Color& BitmapText::GetTintColor() const
    {
        return this->renderUnit->GetTintColor();
    }
    
    /// Set the tint color of this render behavior
    void BitmapText::SetTintColor(const Color& newTintColor)
    {
        this->renderUnit->SetTintColor(newTintColor);
    }
    
    
    /// Get the current shader of this render unit
    Shader* const BitmapText::GetShader()
    {
        return this->renderUnit->GetShader();
    }
    
    /// Change the shader of this render unit
    void BitmapText::ChangeShader(Shader* const newShader)
    {
        this->renderUnit->ChangeShader(newShader);
    }
    
    /// Get the BitmapFont used in this renderer
    BitmapFont* const BitmapText::GetBitmapFont() const
    {
        return this->renderUnit->GetFont();
    }
    
    /// Change the BitmapFont used in this renderer
    void BitmapText::ChangeBitmapFont(BitmapFont* const differentFont)
    {
        this->renderUnit->ChangeFont(differentFont);
    }
    
    /// Change text to render
    void BitmapText::ChangeText(const char* const newText)
    {
        this->renderUnit->ChangeText(newText);
    }
    
    
    
    
    //
    // Behavior Identity
    //
    
    // VIRTUAL OVERRIDE
    /// Get the identity unique to this behavior type. Defined in BehaviorIdentity enum
    const BehaviorIdentity BitmapText::GetBehaviorIdentity() const
    {
        return BehaviorIdentity::BitmapText;
    }
    
    
    
    
    //
    // Events
    //
    
    // VIRTUAL OVERRIDE
    /// Called when the Behavior is added to an Entity (called after constructor)
    void BitmapText::OnStart()
    {
        
    }
    
    
    // VIRTUAL OVERRIDE
    /// Called every iteration of the game loop
    void BitmapText::OnUpdate()
    {
        Transform& transform = this->GetEntity()->GetTransform();
        
        
        
        // Construct model matrix
        math3d::Matrix4x4 modelMatrix;
        {
            const Vector2 vT = transform.GetGlobalPosition();
            
            // Get total scale (from Entity and from Sprite)
            const Vector2 entityS = transform.GetGlobalScale();
//            const Rect spriteRect = this->renderUnit->GetSprite()->operator[](this->renderUnit->GetCurrentFrameIndex())->GetPixelDimensions();
//            const Vector2 spriteS = Vector2(spriteRect.width, spriteRect.height);
//            const Vector2 vS = Vector2(entityS.x() * spriteS.x(),
//                                       entityS.y() * spriteS.y());
            const Vector2 vS = entityS;
            
            // Set the scale of the font for the render (aids in rendering properly)
            this->renderUnit->ChangeWidthScale(vS.x());
            //this->renderUnit->ChangeWidthScale(1.0f);
            
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
    /// Called when the Behavior is removed from an Entity (called before destructor)
    void BitmapText::OnDestroy()
    {
        // Intentionally empty
    }
}