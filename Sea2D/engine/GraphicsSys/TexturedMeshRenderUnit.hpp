//
//  TexturedMeshRenderUnit.hpp
//  Sea2D
//
//  Created by Jibran Syed on 5/2/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//
#ifndef TexturedMeshRenderUnit_hpp
#define TexturedMeshRenderUnit_hpp

#include "RenderUnit.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"

namespace sea2d
{
    /// A RenderUnit that draws a textured mesh
    class TexturedMeshRenderUnit final : public RenderUnit
    {
    public:
        
        //
        // Essentials
        //
        
        /// Ctor
        TexturedMeshRenderUnit(Shader* const newShader, Mesh* const newMesh, Texture* const newTexture);
        
        /// Destructor
        virtual ~TexturedMeshRenderUnit();
        
        
        //
        // Methods
        //
        
        
        /// Get the mesh used for this render unit
        Mesh* const GetMesh();
        
        /// Get the texture used for this render unit
        Texture* const GetTexture();
        
        
        /// Change the mesh used for rendering. Do not call while in render loop!
        void ChangeMesh(Mesh* const newMesh);
        
        /// Change the texture used for rendering. Do not call while in render loop!
        void ChangeTexture(Texture* const newTexture);
        
        
        
    protected:
        
        
        /// Setup render state, such as binding data or setting uniforms (called before OnDraw())
        virtual void OnBeforeDraw() override;
        
        /// Perform actual draw call (or multiple if needed)
        virtual void OnDraw() override;
        
        
        
    private:
        
        //
        // Data
        //
        
        Mesh* mesh;         ///< The mesh used by this render unit
        Texture* texture;   ///< The texture used by this render unit
        
        
        
        //
        // Deleted Methods
        //
        
        /// No Default Ctor
        TexturedMeshRenderUnit() = delete;
        
    };
}
#endif /* TexturedMeshRenderUnit_hpp */
