//
//  TexturedMeshRenderer.cpp
//  Sea2D
//
//  Created by Jibran Syed on 5/2/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "TexturedMeshRenderer.hpp"
#include "engine/SceneSys/Entities/Transform.hpp"
#include "engine/SceneSys/Entities/Entity.hpp"

#include "engine/MathSys/math3d/Matrix4x4.hpp"

#include "engine/GraphicsSys/RenderUnitRegistry.hpp"
#include "engine/GraphicsSys/ShaderRegistry.hpp"
#include "engine/GraphicsSys/MeshRegistry.hpp"
#include "engine/GraphicsSys/TextureRegistry.hpp"

namespace sea2d
{
    //
    // Ctor / Dtor
    //
    
    /// Default Ctor
    TexturedMeshRenderer::TexturedMeshRenderer() :
        renderUnit(nullptr)
    {
        this->renderUnit = new TexturedMeshRenderUnit(ShaderRegistry::Find("Standard"), MeshRegistry::Find(1), TextureRegistry::Find(1));
        RenderUnitRegistry::Add(this->renderUnit);
    }
    
    // VIRTUAL
    /// Destructor
    TexturedMeshRenderer::~TexturedMeshRenderer()
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
    const bool TexturedMeshRenderer::WillDraw() const
    {
        return this->renderUnit->WillDraw();
    }
    
    /// Set whether this render behavior will draw or not
    void TexturedMeshRenderer::SetDrawFlag(const bool willDraw)
    {
        this->renderUnit->SetDrawFlag(willDraw);
    }
    
    /// Get the tint color of this render behavior
    const Color& TexturedMeshRenderer::GetTintColor() const
    {
        return this->renderUnit->GetTintColor();
    }
    
    /// Set the tint color of this render behavior
    void TexturedMeshRenderer::SetTintColor(const Color& newTintColor)
    {
        this->renderUnit->SetTintColor(newTintColor);
    }
    
    
    /// Get the current shader of this render unit
    Shader* const TexturedMeshRenderer::GetShader()
    {
        return this->renderUnit->GetShader();
    }
    
    /// Change the shader of this render unit
    void TexturedMeshRenderer::ChangeShader(Shader* const newShader)
    {
        this->renderUnit->ChangeShader(newShader);
    }
    
    /// Get the mesh used for this render behavior
    Mesh* const TexturedMeshRenderer::GetMesh()
    {
        return this->renderUnit->GetMesh();
    }
    
    /// Get the texture used for this render behavior
    Texture* const TexturedMeshRenderer::GetTexture()
    {
        return this->renderUnit->GetTexture();
    }
    
    
    /// Change the mesh used for rendering
    void TexturedMeshRenderer::ChangeMesh(Mesh* const newMesh)
    {
        this->renderUnit->ChangeMesh(newMesh);
    }
    
    /// Change the texture used for rendering
    void TexturedMeshRenderer::ChangeTexture(Texture* const newTexture)
    {
        this->renderUnit->ChangeTexture(newTexture);
    }
    
    
    
    
    //
    // Behavior Identity
    //
    
    // VIRTUAL OVERRIDE
    /// Get the identity unique to this behavior type. Defined in BehaviorIdentity enum
    const BehaviorIdentity TexturedMeshRenderer::GetBehaviorIdentity() const
    {
        return BehaviorIdentity::TexturedMeshRenderer;
    }
    
    
    
    
    //
    // Events
    //
    
    // VIRTUAL OVERRIDE
    /// Called when the Behavior is added to an Entity (called after constructor)
    void TexturedMeshRenderer::OnStart()
    {
        
    }
    
    
    // VIRTUAL OVERRIDE
    /// Called every iteration of the game loop
    void TexturedMeshRenderer::OnUpdate()
    {
        Transform& transform = this->GetEntity()->GetTransform();
        
        // Construct model matrix
        math3d::Matrix4x4 modelMatrix;
        {
            const Vector2 vT = transform.GetGlobalPosition();
            const Vector2 vS = transform.GetGlobalScale();
            
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
    void TexturedMeshRenderer::OnDestroy()
    {
        // Intentionally empty
    }
}
