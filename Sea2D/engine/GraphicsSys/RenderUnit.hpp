//
//  RenderUnit.hpp
//  Sea2D
//
//  Created by Jibran Syed on 5/2/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//
#ifndef RenderUnit_hpp
#define RenderUnit_hpp

#include "Shader.hpp"
#include "engine/DataTypes/Color.hpp"
#include "engine/MathSys/math3d/Matrix4x4.hpp"

namespace sea2d
{
    /// Base class that represents a single renderable unit. Used to draw into OpenGL
    class RenderUnit
    {
    public:
        
        //
        // Essentials
        //
        
        /// Ctor
        RenderUnit(Shader* const newShader);
        
        /// Destructor
        virtual ~RenderUnit();
        
        
        //
        // Methods
        //
        
        
        /// Get the ID of this render unit
        const unsigned int GetId() const;
        
        /// Does final draw of this render unit. Should only be called by RenderUnitRegistry!
        void Draw();
        
        /// Get the current shader of this render unit
        Shader* const GetShader();
        
        /// Change the shader of this render unit. Don't change shaders while drawing with current unit!
        void ChangeShader(Shader* const newShader);
        
        /// Will this render unit draw in the render loop?
        const bool WillDraw() const;
        
        /// Set whether this render unit will draw or not
        void SetDrawFlag(const bool willDraw);
        
        /// Get the model matrix set for this render unit
        const math3d::Matrix4x4* const GetModelMatrix() const;
        
        /// Set the model matrix for this render unit. Should only be called by a renderer Behavior in the update loop!
        void SetModelMatrix(const math3d::Matrix4x4& newModel);
        
        /// Get the tint color of this render unit
        const Color& GetTintColor() const;
        
        /// Set the tint color of this render unit
        void SetTintColor(const Color& newTintColor);
        
        
    protected:
        
        
        /// Setup render state, such as binding data or setting uniforms (called before OnDraw())
        virtual void OnBeforeDraw() = 0;
        
        /// Perform actual draw call (or multiple if needed)
        virtual void OnDraw() = 0;
        
        
        
    private:
        
        //
        // Data
        //
        
        unsigned int id;            ///< The unique ID of this render unit
        bool shouldDraw;            ///< Flag to enable or disable drawing
        Shader* shader;             ///< The shader used by this render unit
        math3d::Matrix4x4* model;   ///< The final model matrix of this unit
        Color tintColor;            ///< The tint color for this render unit
        
        
        
        //
        // Deleted Methods
        //
        
        /// No Default Ctor
        RenderUnit() = delete;
        
        /// No Copy Ctor
        RenderUnit(const RenderUnit& other) = delete;
        
        /// No Copy Assignment
        RenderUnit& operator=(const RenderUnit& rhs) = delete;
    };
}
#endif /* RenderUnit_hpp */
