//
//  RenderUnitRegistry.cpp
//  Sea2D
//
//  Created by Jibran Syed on 5/2/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "RenderUnitRegistry.hpp"
#include "engine/AppSys/DebugGuarantee.hpp"
#include "engine/CameraSys/Camera.hpp"
#include "engine/MathSys/math3d/Matrix4x4.hpp"
#include "engine/GraphicsSys/ShaderRegistry.hpp"


// Sea2D Render Options

#define S2D_CAMERA_Z_POS (-102.0f)


namespace sea2d
{
    //
    // Static Data
    //
    
    RenderUnitRegistry* RenderUnitRegistry::s_instance = nullptr;
    
    
    
    //
    // Methods
    //
    
    // Default Ctor
    RenderUnitRegistry::RenderUnitRegistry() :
        resourceList()
    {
        guarantee_that(RenderUnitRegistry::s_instance == nullptr, "RenderUnitRegistry singleton already exists!");
        RenderUnitRegistry::s_instance = this;
    }
    
    // VIRTUAL
    // Dtor
    RenderUnitRegistry::~RenderUnitRegistry()
    {
        guarantee_that(this->resourceList.GetNumberOfElements() == 0, "RenderUnitRegistry list must be empty before destruction");
        guarantee_that(RenderUnitRegistry::s_instance != nullptr, "RenderUnitRegistry singeton instance must exist before destruction!");
        RenderUnitRegistry::s_instance = nullptr;
    }
    
    
    
    
    
    
    // VIRTUAL OVERRIDE
    /// Decide what resources to load at the start of the App
    void RenderUnitRegistry::Load()
    {
        // Intentionally empty. Renderer Behaviors add RenderUnits to this registry
    }
    
    
    
    
    
    // VIRTUAL OVERRIDE
    /// Release any resources remaining that are managed by this registry
    void RenderUnitRegistry::Unload()
    {
        while(this->resourceList.GetNumberOfElements() != 0)
        {
            RenderUnit* oldResource = this->resourceList.RemoveFront();
            delete oldResource;
        }
    }
    
    /// Draw every render unit currently being managed
    void RenderUnitRegistry::Draw(const Camera* const currentCamera)
    {
        // Create view matrix from data
        math3d::Matrix4x4 viewMatrix;
        {
            const Vector2 cameraPosition = currentCamera->GetTransformData().position;
            const math3d::Vector4 cameraPosition3d(cameraPosition.x(), cameraPosition.y(), S2D_CAMERA_Z_POS, 1.0f);
            
            const math3d::Matrix4x4 matT = math3d::Matrix4x4(math3d::TranslationMatrix, cameraPosition3d);
            
            const math3d::Matrix4x4 matR = math3d::Matrix4x4(math3d::RotationMatrixZ, currentCamera->GetTransformData().rotation);
            
            viewMatrix = matT * matR;
        }
        
        // Create projection matrix from data
        math3d::Matrix4x4 projMatrix(math3d::IdentityMatrix);
        {
            // http://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/orthographic-projection-matrix
            const CameraProjection& projData = currentCamera->GetProjectionData();
            projMatrix.m0() = 2.0f / (projData.rightEdge - projData.leftEdge);
            projMatrix.m5() = 2.0f / (projData.topEdge - projData.bottomEdge);
            projMatrix.m10() = -2.0f / (projData.farClip - projData.nearClip);
            projMatrix.m12() = (-1.0f * (projData.rightEdge + projData.leftEdge)) / (projData.rightEdge - projData.leftEdge);
            projMatrix.m13() = (-1.0f * (projData.topEdge + projData.bottomEdge)) / (projData.topEdge - projData.bottomEdge);
            projMatrix.m14() = (-1.0f * (projData.farClip + projData.nearClip)) / (projData.farClip - projData.nearClip);
            projMatrix.m15() = 1.0f;
        }
        
        
        // For every shader, set the camera matrices, since they won't change with these draw calls
        for(auto itr = ShaderRegistry::GetIterator(); itr.IsDone() == false; itr.Next())
        {
            Shader* const currentShader = itr.CurrentItem();
            currentShader->SetUniform("viewMatrix", viewMatrix);
            currentShader->SetUniform("projectionMatrix", projMatrix);
        }
        
        
        // Actually draw the RenderUnits
        for(auto itr = this->resourceList.GetIterator(); itr.IsDone() == false; itr.Next())
        {
            RenderUnit* const currentRenderUnit = itr.CurrentItem();
            if(currentRenderUnit->WillDraw())
            {
                currentRenderUnit->Draw();
            }
        }
    }
    
    
    
    
    // STATIC
    /// Find any resource by ID
    RenderUnit* const RenderUnitRegistry::Find(const unsigned int id)
    {
        return RenderUnitRegistry::s_instance->resourceList.FindById((int) id);
    }
    
    
    // STATIC
    /// Deletes any RenderUnit, given its ID. Should only be called by a Renderer Behavior!
    const bool RenderUnitRegistry::Remove(const unsigned int id)
    {
        bool removedSucessfully = false;
        
        // Finds unit by ID and removes it from list, but doesn't delete it
        RenderUnit* oldRenderUnit = RenderUnitRegistry::s_instance->resourceList.RemoveById((int) id);
        
        if(oldRenderUnit != nullptr)
        {
            removedSucessfully = true;
            
            // Delete unit if found
            delete oldRenderUnit;
        }
        
        return removedSucessfully;
    }
    
    
    
    // STATIC
    /// Resource must be dynaically allocated, but it will be deleted by this registry later
    void RenderUnitRegistry::Add(RenderUnit* newResource)
    {
        guarantee_that(newResource != nullptr, "Registry adding a null resource!");
        RenderUnitRegistry::s_instance->resourceList.AddFront(newResource, (int)newResource->GetId());
    }

}
