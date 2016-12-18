//
//  TexturedMeshRenderUnit.cpp
//  Sea2D
//
//  Created by Jibran Syed on 5/2/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "TexturedMeshRenderUnit.hpp"
#include "engine/AppSys/DebugGuarantee.hpp"

namespace sea2d
{
    // Default Ctor
    TexturedMeshRenderUnit::TexturedMeshRenderUnit(Shader* const newShader, Mesh* const newMesh, Texture* const newTexture) :
        RenderUnit(newShader),
        mesh(newMesh),
        texture(newTexture)
    {
        guarantee_that(newShader != nullptr, "New RenderUnit cannot take in null shader!");
        guarantee_that(newMesh != nullptr, "New RenderUnit cannot take in null mesh!");
        guarantee_that(newTexture != nullptr, "New RenderUnit cannot take in null texture!");
    }
    
    // VIRTUAL
    // Dtor
    TexturedMeshRenderUnit::~TexturedMeshRenderUnit()
    {
    }
    
    
    
    /// Get the mesh used for this render unit
    Mesh* const TexturedMeshRenderUnit::GetMesh()
    {
        return this->mesh;
    }
    
    /// Get the texture used for this render unit
    Texture* const TexturedMeshRenderUnit::GetTexture()
    {
        return this->texture;
    }
    
    
    /// Change the mesh used for rendering. Do not call while in render loop!
    void TexturedMeshRenderUnit::ChangeMesh(Mesh* const newMesh)
    {
        this->mesh = newMesh;
        this->mesh->MakeActive();
    }
    
    /// Change the texture used for rendering. Do not call while in render loop!
    void TexturedMeshRenderUnit::ChangeTexture(Texture* const newTexture)
    {
        this->texture = newTexture;
        this->texture->MakeActive();
    }
    
    
    // VIRTUAL OVERRIDE
    /// Setup render state, such as binding data or setting uniforms (called before OnDraw())
    void TexturedMeshRenderUnit::OnBeforeDraw()
    {
        this->mesh->MakeActive();
        this->texture->MakeActive();
    }
    
    // VIRTUAL OVERRIDE
    /// Perform actual draw call (or multiple if needed)
    void TexturedMeshRenderUnit::OnDraw()
    {
        glDrawElements(GL_TRIANGLES, this->mesh->GetNumberOfTriangles() * 3, GL_UNSIGNED_INT, 0);
    }
    
    
}
