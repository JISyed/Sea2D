//
//  RenderUnit.cpp
//  Sea2D
//
//  Created by Jibran Syed on 5/2/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "RenderUnit.hpp"
#include "engine/AppSys/IdGenerator.hpp"
#include "engine/AppSys/DebugGuarantee.hpp"

namespace sea2d
{
    //
    // Static data
    //
    
    /// Generates IDs for every Entity when the game runs
    static IdGenerator s_idGen;
    
    
    
    //
    // Methods
    //
    
    // Ctor
    RenderUnit::RenderUnit(Shader* const newShader) :
        id(s_idGen.MakeNewId()),
        shouldDraw(true),
        shader(newShader),
        model(new math3d::Matrix4x4(math3d::IdentityMatrix)),
        tintColor(Color::White)
    {
        guarantee_that(newShader != nullptr, "New RenderUnit being given a null shader!");
    }
    
    // VIRTUAL
    // Dtor
    RenderUnit::~RenderUnit()
    {
        delete this->model;
    }
    
    
    
    /// Get the ID of this render unit
    const unsigned int RenderUnit::GetId() const
    {
        return this->id;
    }
    
    
    
    /// Does final draw of this render unit
    void RenderUnit::Draw()
    {
        this->shader->MakeActive();
        
        // Set uniforms
        this->shader->SetUniform("tintColor", this->tintColor);
        this->shader->SetUniform("modelMatrix", *(this->model));
        
        this->OnBeforeDraw();
        
        this->OnDraw();
    }
    
    /// Get the current shader of this render unit
    Shader* const RenderUnit::GetShader()
    {
        return this->shader;
    }
    
    /// Change the shader of this render unit
    void RenderUnit::ChangeShader(Shader* const newShader)
    {
        this->shader = newShader;
        this->shader->MakeActive();
    }
    
    /// Will this render unit draw in the render loop?
    const bool RenderUnit::WillDraw() const
    {
        return this->shouldDraw;
    }
    
    /// Set whether this render unit will draw or not
    void RenderUnit::SetDrawFlag(const bool willDraw)
    {
        this->shouldDraw = willDraw;
    }
    
    /// Get the model matrix set for this render unit
    const math3d::Matrix4x4* const RenderUnit::GetModelMatrix() const
    {
        return this->model;
    }
    
    /// Set the model matrix for this render unit. Should only be called by a renderer Behavior!
    void RenderUnit::SetModelMatrix(const math3d::Matrix4x4& newModel)
    {
        this->model->operator=(newModel);
    }
    
    /// Get the tint color of this render unit
    const Color& RenderUnit::GetTintColor() const
    {
        return this->tintColor;
    }
    
    /// Set the tint color of this render unit
    void RenderUnit::SetTintColor(const Color& newTintColor)
    {
        this->tintColor = newTintColor;
    }
    
    
}
