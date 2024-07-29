
/*

 _____                               _
|_   _|                             (_)
  | |  ___  _ __     ___ _ __   __ _ _ _ __   ___
  | | / _ \| '_ \   / _ \ '_ \ / _` | | '_ \ / _ \
 _| || (_) | | | | |  __/ | | | (_| | | | | |  __/
 \___/\___/|_| |_|  \___|_| |_|\__, |_|_| |_|\___|
                                __/ |
                               |___/


NAME: Buffer.h

DESCTIPTION: Buffer class for OpenGL 4.5

AUTHOR: Noah de Pischof | @torrra on GitHub

NOTE: Model objects already store vertex and index data, so these buffers only contain OpenGL stuff

*/

#pragma once

#include "glad/glad.h"
#include "Vertex.h"

#define ION_VERTEX_BUFFER           GL_ARRAY_BUFFER
#define ION_INDEX_BUFFER            GL_ELEMENT_ARRAY_BUFFER


namespace ion
{
    // This struct only defines the buffer's ValueType if
    // its template parameter is of a valid buffer type
    // (ION_VERTEX_BUFFER or ION_INDEX_BUFFER)
    template <GLenum TBufferEnum>
    struct BufferTraits;


// Buffer traits specialization to determine buffer value type

    template<>
    struct BufferTraits<ION_VERTEX_BUFFER>
    {
        using ValueType = Vertex;
    };

    template<>
    struct BufferTraits<ION_INDEX_BUFFER>
    {
        using ValueType = uint32_t;
    };


// ---- Buffer class for VBOs and EBOs ----

    template <GLenum TBufferEnum>
    class RES_API Buffer
    {
    private:

        // Value type, vertex or index (unsigned int)
        using ValueType = BufferTraits<TBufferEnum>::ValueType;

    public:

     inline             Buffer(void);
     inline             ~Buffer(void);

     // Feed buffer data to OpenGL
     inline void        SetData(int64_t size, ValueType const* data)  const;

     // Delete buffer and reset index
     inline void        DeleteData(void);

     // Get buffer index
     inline uint32_t    GetID(void)                                   const;

    private:

     uint32_t           m_id = 0;

    };


    using VertexBuffer = Buffer<ION_VERTEX_BUFFER>;
    using IndexBuffer = Buffer<ION_INDEX_BUFFER>;



// ---- Implementations ----

    template <GLenum TBufferEnum>
    inline Buffer<TBufferEnum>::Buffer(void)
    {
        glCreateBuffers(1, &m_id);
    }

    template <GLenum TBufferEnum>
    inline void Buffer<TBufferEnum>::SetData(int64_t size, ValueType const* data) const
    {
        glNamedBufferData(m_id, size, data, GL_STATIC_DRAW);
    }

    template <GLenum TBufferEnum>
    inline void Buffer<TBufferEnum>::DeleteData(void)
    {
        glDeleteBuffers(1, &m_id);

        m_id = 0;
    }

    template <GLenum TBufferEnum>
    inline uint32_t Buffer<TBufferEnum>::GetID(void) const
    {
        return m_id;
    }

    template <GLenum TBufferEnum>
    inline Buffer<TBufferEnum>::~Buffer(void)
    {
        DeleteData();
    }


// ---- SetData specialization for vertex buffer objects ----

    template<>
    inline void Buffer<ION_VERTEX_BUFFER>::SetData(int64_t size, Vertex const* vertices) const
    {
        // First literal value inside a vertex is its position vector's x value,
        // which is a float
        float const*  vertexData = reinterpret_cast<float const*>(vertices);

        glNamedBufferData(m_id, size, vertexData, GL_STATIC_DRAW);
    }

}