//
//  Mesh.hpp
//  Sea2D
//
//  Created by Jibran Syed on 4/10/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <GL/gl3w.h>
#include "engine/DataTypes/StringFixed.hpp"

namespace sea2d
{
    /// Represents a renderable collection of vertices and faces
    class Mesh
    {
    public:
        
        //
        // Essentials
        //
        
        /// New constructor given mesh data and a name
        Mesh(const GLfloat* const vertexData, const size_t elementsInVertexData, const GLuint* const triangeData, const size_t elementsInTriangleData,
             const char* const newName);
        
        /// Destructor
        ~Mesh();
        
        
        
        
        //
        // Methods
        //
        
        
        /// Get the number of triangles in this mesh
        const int GetNumberOfTriangles() const;
        
        /// Make the active mesh to render in the draw loop
        void MakeActive();
        
        /// Get the read only name of this mesh
        const StringFixed& GetName() const;
        
        /// Get the instance ID of this mesh (unique for every mesh) (not OpenGL handle!)
        const unsigned int GetId() const;
        
        
    private:
        
        //
        // Data
        //
        
        GLuint vao;         ///< Vertex Array Object, which is a group of multiple VBOs
        GLuint vbo[2];      ///< Vertex Buffer Object, which contains vertex data of various types
        int numOfTriangles; ///< The number of triangles in this mesh
        unsigned int id;    ///< The engine id of this mesh (not OpenGL id)
        StringFixed name;      ///< The name of this mesh
        
        
        //
        // Deleted Methods
        //
        
        // No Default Ctor
        Mesh() = delete;
        
        // No Copy Ctor
        Mesh(const Mesh& other) = delete;
        
        // No Copy Assignment
        Mesh& operator=(const Mesh& rhs) = delete;
        
        
    };
}

#endif /* Mesh_hpp */
