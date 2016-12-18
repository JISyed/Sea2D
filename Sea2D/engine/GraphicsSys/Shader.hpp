//
//  Shader.hpp
//  Sea2D
//
//  Created by Jibran Syed on 4/10/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <GL/gl3w.h>
#include "engine/DataTypes/StringFixed.hpp"
#include "engine/MathSys/Vector2.hpp"
#include "engine/MathSys/math3d/Vector4.hpp"
#include "engine/MathSys/math3d/Matrix4x4.hpp"
#include "engine/DataTypes/Color.hpp"
#include "engine/DataTypes/Rect.hpp"

namespace sea2d
{
    /// Represents a complete programable rendering pipeline for GPUs
    class Shader
    {
    public:
        
        //
        // Essentials
        //
        
        /// Constructor with shader files (without extension) and name
        Shader(const char* const filename, const char* const shaderName);
        
        /// Destructor
        ~Shader();
        
        
        
        //
        // Methods
        //
        
        /// Make this shader the current shader used for rendering in the draw loop
        void MakeActive();
        
        /// Get the read only name of this shader
        const StringFixed& GetName() const;
        
        /// Get the instance ID of this shader (unique for every shader) (not OpenGL handle!)
        const unsigned int GetId() const;
        
        
        //
        // Uniform Setting
        //
        
        /// Set a matrix uniform into this shader given the uniform's name, as declared in the shader
        void SetUniform(const char* const uniformNameInShader, const math3d::Matrix4x4& uniformValue);
        
        /// Set a 4D vector uniform into this shader given the uniform's name, as declared in the shader
        void SetUniform(const char* const uniformNameInShader, const math3d::Vector4& uniformValue);
        
        /// Set a 2D vector uniform into this shader given the uniform's name, as declared in the shader
        void SetUniform(const char* const uniformNameInShader, const Vector2& uniformValue);
        
        /// Set a color uniform into this shader given the uniform's name, as declared in the shader. In the shader, color is of type vec4
        void SetUniform(const char* const uniformNameInShader, const Color& uniformValue);
        
        /// Set a signed integer uniform into this shader given the uniform's name, as declared in the shader. Will assert if uniform is spelled wrong
        void SetUniform(const char* const uniformNameInShader, const int uniformValue);
        
        /// Set an unsigned integer uniform into this shader given the uniform's name, as declared in the shader. Will assert if uniform is spelled wrong
        void SetUniform(const char* const uniformNameInShader, const unsigned int uniformValue);
        
        /// Set a floating point number uniform into this shader given the uniform's name, as declared in the shader. Will assert if uniform is spelled wrong
        void SetUniform(const char* const uniformNameInShader, const float uniformValue);
        
        /// Set a Rect uniform into the shader given the uniform's name, as declared in the shader. In the shader, Rect is of type vec4
        void SetUniform(const char* const uniformNameInShader, const Rect& uniformValue);
        
        
    private:
        
        //
        // Data
        //
        
        GLuint shaderProgram;   ///< Internal OpenGL ID
        unsigned int id;        ///< Engine ID for shader (not OpenGL ID)
        StringFixed name;       ///< Name of the shader
        
        
        
        
        //
        // Private Routines
        //
        
        /// Loads either the vertex or fragment shader
        const bool LoadSubShader(GLuint& subshader, const char* const filename, GLenum subshaderType);
        
        /// Compiles with the vertex or fragment shader
        const bool CompileSubShader(GLuint& subshader, const char* const shaderSourceBuffer, GLenum subshaderType);
        
        /// Link the subshaders together to complete the shader program
        const bool LinkShader(GLuint& vertexShaderId, GLuint& fragmentShaderId);
        
        
        //
        // Deleted Methods
        //
        
        /// No Default Ctor
        Shader() = delete;
        
        /// No Copy Ctor
        Shader(const Shader& other) = delete;
        
        /// No Copy Assignment
        Shader& operator=(const Shader& rhs) = delete;
        
        
    };
}

#endif /* Shader_hpp */
