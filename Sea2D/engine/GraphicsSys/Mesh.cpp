//
//  Mesh.cpp
//  Sea2D
//
//  Created by Jibran Syed on 4/10/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "Mesh.hpp"
#include "engine/AppSys/DebugGuarantee.hpp"
#include "engine/AppSys/IdGenerator.hpp"

namespace sea2d
{
    //
    // Statics
    //
    
    /// Generates IDs for every mesh when the game runs
    static IdGenerator s_idGen;
    
    
    
    //
    // Methods
    //
    
    /// New constructor given mesh data and a name
    Mesh::Mesh(const GLfloat* const vertexData, const size_t elementsInVertexData, const GLuint* const triangeData, const size_t elementsInTriangleData,
               const char* const newName) :
        vao(0),
        vbo{0,0},
        numOfTriangles(-1),
        id(s_idGen.MakeNewId()),
        name(newName)
    {
        guarantee_that(vertexData != nullptr, "Mesh: Vertex buffer is null!");
        guarantee_that(triangeData != nullptr, "Mesh: Triange buffer is null!");
        guarantee_that(newName != nullptr, "Mesh: Name string is null!");
        
        // Determine the number of triangles
        this->numOfTriangles = (int) (elementsInTriangleData / 3);
        
        // Create the vertex array object
        glGenVertexArrays(1, &this->vao);
        guarantee_that(this->vao != 0, "Mesh: VAO creation failed!");
        glBindVertexArray(this->vao);
        
        // Create the 2 Vertex Buffer Objects (Vertex Attributes & Triangle Indices)
        glGenBuffers(2, this->vbo);
        guarantee_that(this->vbo[0] != 0, "Mesh: Vertex VBO creation failed!");
        guarantee_that(this->vbo[1] != 0, "Mesh: Triangle VBO creation failed");
        
        
        // Setup Vertex Attributes VBO
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, (int)(elementsInVertexData * sizeof(GLfloat)), vertexData, GL_STATIC_DRAW);
        
        // Format vertex position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (GLvoid*)0);
        glEnableVertexAttribArray(0);
        
        // Format texture coodinates
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        
        
        // Setup Triange Indices VBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vbo[1]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (int)(elementsInTriangleData * sizeof(GLuint)), triangeData, GL_STATIC_DRAW);
        
        
        // Unbind the VAO so we don't mess it up on accident later
        glBindVertexArray(0);
    }
    
    
    /// Dtor
    Mesh::~Mesh()
    {
        glBindVertexArray(this->vao);
        
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        
        glDeleteBuffers(2, this->vbo);
        glDeleteVertexArrays(1, &this->vao);
    }
    
    
    
    
    /// Get the number of triangles in this mesh
    const int Mesh::GetNumberOfTriangles() const
    {
        return this->numOfTriangles;
    }
    
    /// Make the active mesh to render in the draw loop
    void Mesh::MakeActive()
    {
        glBindVertexArray(this->vao);
    }
    
    /// Get the read only name of this mesh
    const StringFixed& Mesh::GetName() const
    {
        return this->name;
    }
    
    /// Get the instance ID of this mesh (unique for every mesh)
    const unsigned int Mesh::GetId() const
    {
        return this->id;
    }
    
}