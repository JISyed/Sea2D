//
//  TexturedMeshRenderer.hpp
//  Sea2D
//
//  Created by Jibran Syed on 5/2/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#ifndef TexturedMeshRenderer_hpp
#define TexturedMeshRenderer_hpp

#include "Behavior.hpp"
#include "engine/GraphicsSys/TexturedMeshRenderUnit.hpp"

namespace sea2d
{
    /// Behavior that draws Entity with TexturedMeshRenderUnit
    class TexturedMeshRenderer : public Behavior
    {
    public:
        
        //
        // Essentials
        //
        
        /// Default Ctor
        TexturedMeshRenderer();
        
        /// Destructor
        virtual ~TexturedMeshRenderer();
        
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
        
        /// Get the mesh used for this render behavior
        Mesh* const GetMesh();
        
        /// Get the texture used for this render behavior
        Texture* const GetTexture();
        
        
        /// Change the mesh used for rendering
        void ChangeMesh(Mesh* const newMesh);
        
        /// Change the texture used for rendering
        void ChangeTexture(Texture* const newTexture);
        
        
        
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
        
        TexturedMeshRenderUnit* renderUnit;
        
        
        
    };

}
#endif /* TexturedMeshRenderer_hpp */
