
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


*/

#pragma once

#include "glad/glad.h"

#define ION_VERTEX_BUFFER           GL_ARRAY_BUFFER
#define ION_INDEX_BUFFER            GL_ELEMENT_ARRAY_BUFFER

namespace ion
{

    template <GLenum TBufferEnum> requires
    (TBufferEnum == ION_VERTEX_BUFFER || TBufferEnum == ION_INDEX_BUFFER)
    class Buffer
    {

    };

}
