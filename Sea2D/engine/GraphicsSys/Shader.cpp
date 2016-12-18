//
//  Shader.cpp
//  Sea2D
//
//  Created by Jibran Syed on 4/10/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "Shader.hpp"
#include "engine/AppSys/DebugGuarantee.hpp"
#include "engine/AppSys/ResourceUtility.hpp"
#include "engine/AppSys/IdGenerator.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

// Shader Macros
#define S2D_VERT_SHDR_FILE_EXT  ".vert.glsl"
#define S2D_FRAG_SHDR_FILE_EXT  ".frag.glsl"


namespace sea2d
{
    //
    // Statics
    //
    
    /// Generates IDs for every shader when the game runs
    static IdGenerator s_idGen;
    
    
    
    //
    // Methods
    //
    
    /// Constructor with shader files (without extension) and name
    Shader::Shader(const char* const filename, const char* const shaderName) :
        shaderProgram(0u),
        id(s_idGen.MakeNewId()),
        name(shaderName)
    {
        guarantee_that(filename != nullptr, "Shader: Filename string is null!");
        guarantee_that(shaderName != nullptr, "Shader: Shader name string is null!");
        
        // Create a new shader program in OpenGL (vert+frag combo)
        this->shaderProgram = glCreateProgram();
        
        // Load the vertex shader code and compile it
        GLuint vertId;
        bool vertSuccess = this->LoadSubShader(vertId, filename, GL_VERTEX_SHADER);
        guarantee_that(vertSuccess == true, "Shader: Vertex shader failed!");
        
        // Load the fragment shader code and compile it
        GLuint fragId;
        bool fragSuccess = this->LoadSubShader(fragId, filename, GL_FRAGMENT_SHADER);
        guarantee_that(fragSuccess == true, "Shader: Fragment shader failed!");
        
        // Link the subshaders together to complete the shader loading
        bool linkingSuccess = this->LinkShader(vertId, fragId);
        guarantee_that(linkingSuccess == true, "Shader: Linking shaders failed!");
        
        // Subshader code can be deleted after linking because the shader logic was already copied into the GPU
        glDeleteShader(vertId);
        glDeleteShader(fragId);
        
        // Done setting up. Don't mess up its state later
        glUseProgram(0);
    }
    
    
    /// Dtor
    Shader::~Shader()
    {
        glUseProgram(0);
        glDeleteProgram(this->shaderProgram);
    }
    
    
    
    /// Make this shader the current shader used for rendering in the draw loop
    void Shader::MakeActive()
    {
        glUseProgram(this->shaderProgram);
    }
    
    
    
    /// Get the unique identifier for this shader
    const unsigned int Shader::GetId() const
    {
        return this->id;
    }
    
    /// Get the read only name of this shader
    const StringFixed& Shader::GetName() const
    {
        return this->name;
    }
    
    
    
    //
    // Private Routines
    //
    
    
    /// Loads either the vertex or fragment shader
    const bool Shader::LoadSubShader(GLuint& subshader, const char* const filename, GLenum subshaderType)
    {
        guarantee_that(filename != nullptr, "Subshader: Filename is null!");
        guarantee_that(subshaderType == GL_VERTEX_SHADER || subshaderType == GL_FRAGMENT_SHADER, "Subshader: GLenum parameter can only be GL_VERTEX_SHADER or GL_FRAGMENT_SHADER");
        
        /// Figure out the actual file name with extension of the subshader
        std::string filenameWithExt(filename);
        if(subshaderType == GL_VERTEX_SHADER)
        {
            filenameWithExt += S2D_VERT_SHDR_FILE_EXT;
        }
        else if(subshaderType == GL_FRAGMENT_SHADER)
        {
            filenameWithExt += S2D_FRAG_SHDR_FILE_EXT;
        }
        
        /// Get the full file path of this subshader
        std::string fullPath = ResouceUtility::GetFullPathForFileName(filenameWithExt.c_str());
        
        /// Open the file from the path
        std::ifstream fileReader;
        fileReader.open(fullPath.c_str(), std::ios::in | std::ios::binary);
        bool openSuccess = fileReader.is_open();
        if(!openSuccess)
        {
            guarantee_that(openSuccess, "Subshader: Failed to open the shader file");
        }
        
        // Read the file into a buffer
        std::stringstream strBufStream;
        strBufStream << fileReader.rdbuf();
        
        // Compile the shader source
        return this->CompileSubShader(subshader, strBufStream.str().c_str(), subshaderType);
    }
    
    
    
    
    /// Compiles with the vertex or fragment shader
    const bool Shader::CompileSubShader(GLuint& subshader, const char* const shaderSourceBuffer, GLenum subshaderType)
    {
        guarantee_that(shaderSourceBuffer != nullptr, "Shader: loaded code is null!");
        guarantee_that(subshaderType == GL_VERTEX_SHADER || subshaderType == GL_FRAGMENT_SHADER, "Shader: GLenum parameter can only be GL_VERTEX_SHADER or GL_FRAGMENT_SHADER");
        
        // Create the subshader
        subshader = glCreateShader(subshaderType);
        
        // Upload the shader code into OpenGL's runtime compiler
        glShaderSource(subshader, 1, &shaderSourceBuffer, NULL);
        
        // Actually compile the shader
        glCompileShader(subshader);
        
        // Check the compile status for any errors
        GLint errorCode = 0;
        glGetShaderiv(subshader, GL_COMPILE_STATUS, &errorCode);
        
        // Report errors, if any
        if(!errorCode)
        {
            // Get the error message from OpenGL
            GLint errorMessageLen;
            glGetShaderiv(subshader, GL_INFO_LOG_LENGTH, &errorMessageLen);
            char* errorMessage = new char[errorMessageLen];
            glGetShaderInfoLog(subshader, errorMessageLen, NULL, errorMessage);
            std::string subshaderTypeName;
            if(subshaderType == GL_VERTEX_SHADER)
            {
                subshaderTypeName = "Vertex";
            }
            else if(subshaderType == GL_FRAGMENT_SHADER)
            {
                subshaderTypeName = "Fragment";
            }
            
            // Print message
            std::cout << "    Error Compiling " << subshaderTypeName << " Shader " << "\"" << std::string(this->name.GetCString()) << "\": " << std::string(errorMessage) << std::endl;
            
            // Subshader failed
            guarantee_that(false, "Subshader: Compile failed! Read the error message above");
            delete [] errorMessage;
            return false;
        }
        
        // Success
        return true;
    }
    
    
    
    
    
    /// Link the subshaders together to complete the shader program
    const bool Shader::LinkShader(GLuint& vertexShaderId, GLuint& fragmentShaderId)
    {
        // Attach the vertex and fragment logic to the shader program
        glAttachShader(this->shaderProgram, vertexShaderId);
        glAttachShader(this->shaderProgram, fragmentShaderId);
        
        // Link the vertex and fragment shader together. Make sure they are compatable
        glLinkProgram(this->shaderProgram);
        
        // Check the linking status for any errors
        GLint linkingSuccess = GL_FALSE;
        glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &linkingSuccess);
        
        // Report errors if any
        if(linkingSuccess == GL_FALSE)
        {
            // Get error message from OpenGL
            GLchar errorMessage[4096] = {0};
            glGetProgramInfoLog(this->shaderProgram, 4096, NULL, errorMessage);
            
            std::cout << "Error Linking Shader " << "\"" << std::string(this->name.GetCString()) << "\": " << std::string(errorMessage) << std::endl;
            
            // Whole shader failed
            guarantee_that(false, "Shader: Linking failed! Read the error message above");
            return false;
        }
        
        return true;
    }
    
    
    
    
    
    //
    // Unifrom Setting
    //
    
    /// Set a matrix uniform into this shader given the uniform's name, as declared in the shader
    void Shader::SetUniform(const char* const uniformNameInShader, const math3d::Matrix4x4& uniformValue)
    {
        guarantee_that(uniformNameInShader != nullptr, "Shader Uniform Name is null!");
        
        this->MakeActive();
        
        const GLint uniformHandle = glGetUniformLocation(this->shaderProgram, uniformNameInShader);
        guarantee_that(uniformHandle >= 0, "Shader Uniform location not found! It either does not exist or it's spelled wrong");
        
        glUniformMatrix4fv(uniformHandle, 1, GL_FALSE, uniformValue.getFloatPointer());
    }
    
    /// Set a 4D vector uniform into this shader given the uniform's name, as declared in the shader
    void Shader::SetUniform(const char* const uniformNameInShader, const math3d::Vector4& uniformValue)
    {
        guarantee_that(uniformNameInShader != nullptr, "Shader Uniform Name is null!");
        
        this->MakeActive();
        
        const GLint uniformHandle = glGetUniformLocation(this->shaderProgram, uniformNameInShader);
        guarantee_that(uniformHandle >= 0, "Shader Uniform location not found! It either does not exist or it's spelled wrong");
        
        glUniform4fv(uniformHandle, 1, uniformValue.getFloatPointer());
    }
    
    /// Set a 2D vector uniform into this shader given the uniform's name, as declared in the shader
    void Shader::SetUniform(const char* const uniformNameInShader, const Vector2& uniformValue)
    {
        guarantee_that(uniformNameInShader != nullptr, "Shader Uniform Name is null!");
        
        this->MakeActive();
        
        const GLint uniformHandle = glGetUniformLocation(this->shaderProgram, uniformNameInShader);
        guarantee_that(uniformHandle >= 0, "Shader Uniform location not found! It either does not exist or it's spelled wrong");
        
        glUniform2f(uniformHandle, uniformValue.x(), uniformValue.y());
    }
    
    /// Set a color uniform into this shader given the uniform's name, as declared in the shader. In shader, color is of type vec4
    void Shader::SetUniform(const char* const uniformNameInShader, const Color& uniformValue)
    {
        guarantee_that(uniformNameInShader != nullptr, "Shader Uniform Name is null!");
        
        this->MakeActive();
        
        const GLint uniformHandle = glGetUniformLocation(this->shaderProgram, uniformNameInShader);
        guarantee_that(uniformHandle >= 0, "Shader Uniform location not found! It either does not exist or it's spelled wrong");
        
        glUniform4fv(uniformHandle, 1, uniformValue.GetRawData());
    }
    
    /// Set a signed integer uniform into this shader given the uniform's name, as declared in the shader. Will assert if uniform is spelled wrong
    void Shader::SetUniform(const char* const uniformNameInShader, const int uniformValue)
    {
        guarantee_that(uniformNameInShader != nullptr, "Shader Uniform Name is null!");
        
        this->MakeActive();
        
        const GLint uniformHandle = glGetUniformLocation(this->shaderProgram, uniformNameInShader);
        guarantee_that(uniformHandle >= 0, "Shader Uniform location not found! It either does not exist or it's spelled wrong");
        
        glUniform1i(uniformHandle, uniformValue);
    }
    
    /// Set an unsigned integer uniform into this shader given the uniform's name, as declared in the shader. Will assert if uniform is spelled wrong
    void Shader::SetUniform(const char* const uniformNameInShader, const unsigned int uniformValue)
    {
        guarantee_that(uniformNameInShader != nullptr, "Shader Uniform Name is null!");
        
        this->MakeActive();
        
        const GLint uniformHandle = glGetUniformLocation(this->shaderProgram, uniformNameInShader);
        guarantee_that(uniformHandle >= 0, "Shader Uniform location not found! It either does not exist or it's spelled wrong");
        
        glUniform1ui(uniformHandle, uniformValue);
    }
    
    /// Set a floating point number uniform into this shader given the uniform's name, as declared in the shader. Will assert if uniform is spelled wrong
    void Shader::SetUniform(const char* const uniformNameInShader, const float uniformValue)
    {
        guarantee_that(uniformNameInShader != nullptr, "Shader Uniform Name is null!");
        
        this->MakeActive();
        
        const GLint uniformHandle = glGetUniformLocation(this->shaderProgram, uniformNameInShader);
        guarantee_that(uniformHandle >= 0, "Shader Uniform location not found! It either does not exist or it's spelled wrong");
        
        glUniform1f(uniformHandle, uniformValue);
    }
    
    
    /// Set a Rect uniform into the shader given the uniform's name, as declared in the shader. In the shader, Rect is of type vec4
    void Shader::SetUniform(const char* const uniformNameInShader, const Rect& uniformValue)
    {
        guarantee_that(uniformNameInShader != nullptr, "Shader Uniform Name is null!");
        
        this->MakeActive();
        
        const GLint uniformHandle = glGetUniformLocation(this->shaderProgram, uniformNameInShader);
        guarantee_that(uniformHandle >= 0, "Shader Uniform location not found! It either does not exist or it's spelled wrong");
        
        glUniform4f(uniformHandle, uniformValue.origin.x(), uniformValue.origin.y(), uniformValue.width, uniformValue.height);
    }
    
    
}