
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

#include "Model.h"
#include "Vertex.h"

#define ION_VERTEX_BUFFER           GL_ARRAY_BUFFER
#define ION_INDEX_BUFFER            GL_ELEMENT_ARRAY_BUFFER


namespace ion
{
    template <GLenum TBufferEnum>
    struct BufferTraits;

    template <GLenum TBufferEnum> requires
     (TBufferEnum == ION_VERTEX_BUFFER || TBufferEnum == ION_INDEX_BUFFER)
     class Buffer;


// Buffer traits specialization to determine buffer value type

    template<>
    struct BufferTraits<ION_VERTEX_BUFFER>
    {
        using ValueType = Vertex;
    };

    template<>
    struct BufferTraits<ION_INDEX_BUFFER>
    {
        using ValueType = GLuint;
    };


    template <GLenum TBufferEnum> requires
    (TBufferEnum == ION_VERTEX_BUFFER || TBufferEnum == ION_INDEX_BUFFER)
    class Buffer
    {
    private:

        using ValueType = BufferTraits<TBufferEnum>::ValueType;

    public:

     inline         Buffer(void);
     inline         ~Buffer(void);


     inline void    SetData(size_t size, ValueType const* data, bool dynamic = false)  const;
     inline void    DeleteData(void);

     inline GLuint  GetID(void)                                                        const;

    private:

     GLuint         m_id = 0;

    };


    template<GLenum TBufferEnum>
    inline Buffer<TBufferEnum>::Buffer(void)
    {
        glCreateBuffers(1, &m_id);
    }

    template<GLenum TBufferEnum>
    inline void Buffer<TBufferEnum>::SetData(size_t size, ValueType const* data, bool dynamic) const
    {
        if (dynamic)
            glNamedBufferData(m_id, size, data, GL_DYNAMIC_DRAW);
        else
            glNamedBufferData(m_id, size, data, GL_STATIC_DRAW);
    }

    template<GLenum TBufferEnum>
    inline void Buffer<TBufferEnum>::DeleteData(void)
    {
        glDeleteBuffers(1, m_id);

        m_id = 0;
    }

    template<GLenum TBufferEnum>
    inline GLuint Buffer<TBufferEnum>::GetID(void) const
    {
        return m_id;
    }

    template<GLenum TBufferEnum>
    inline Buffer<TBufferEnum>::~Buffer(void)
    {
        DeleteData();
    }


// ---- Set data specialization for vertex buffer objects ----

    template<>
    inline void Buffer<ION_VERTEX_BUFFER>::SetData(size_t size, Vertex const* data, bool dynamic) const
    {
        float const*  vertexData = reinterpret_cast<float const*>(data);

        if (dynamic)
            glNamedBufferData(m_id, size, vertexData, GL_DYNAMIC_DRAW);
        else
            glNamedBufferData(m_id, size, vertexData, GL_STATIC_DRAW);
    }


}