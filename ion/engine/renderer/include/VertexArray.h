/*

 _____                               _
|_   _|                             (_)
  | |  ___  _ __     ___ _ __   __ _ _ _ __   ___
  | | / _ \| '_ \   / _ \ '_ \ / _` | | '_ \ / _ \
 _| || (_) | | | | |  __/ | | | (_| | | | | |  __/
 \___/\___/|_| |_|  \___|_| |_|\__, |_|_| |_|\___|
                                __/ |
                               |___/


NAME: VertexArray.h

DESCTIPTION: Abstraction of OpenGL 4.5 vertex array objects

AUTHOR: Noah de Pischof | @torrra on GitHub

*/



#pragma once

#include "Buffer.h"
#include "Model.h"

namespace ion
{
    class VertexArray
    {
    public:

        // Create an empty vertex array along with an empty vertex buffer
        // and an empty index buffer
                VertexArray(void);

        // Directly set up all necessary buffers from a model
                VertexArray(const Model& model);

        // Create VBO from c-style array or Vertex objects.
        // size refers to the buffer's total size in bytes
        void    CreateVertexBuffer(const Vertex* vertices, int64_t bufferSize);

        // Create VBO from vector of Vertex objects
        void    CreateVertexBuffer(const std::vector<Vertex>& vertices);

        // Create EBO from c-style array of unsigned integers.
        // size refers to the buffer's total size in bytes
        void    CreateIndexBuffer(const uint32_t* indices, int64_t bufferSize);

        // Create EBO from vector of unsigned integers
        void    CreateIndexBuffer(const std::vector<uint32_t>& indices);

        // Draw vertices from this objects vertex and index buffers
        void    Draw(void);

        // Delete this vertex array.
        // This does not delete its vertex and index buffers.
        void    Delete(void);

                ~VertexArray(void);


    private:

        // Set position, normal and texture coordinate attributes within the index buffer
        void    SetAllAttributes(void);

        // Set a single vertrex attribute
        void    SetAttribute(uint32_t position, int32_t size, uint32_t offset);

        // Bind this object's VBO to the OpenGL VAO's binding point
        // at index 0
        void    BindVBO(void);

        // Bind this object's VBO to the OpenGL VAO's binding point
        void    BindEBO(void);

        Buffer<ION_VERTEX_BUFFER>   m_vbo;
        Buffer<ION_INDEX_BUFFER>    m_ebo;

        uint32_t                    m_id;
        int32_t                     m_vertexCount = 0;
    };
}
