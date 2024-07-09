/*

 _____                               _
|_   _|                             (_)
  | |  ___  _ __     ___ _ __   __ _ _ _ __   ___
  | | / _ \| '_ \   / _ \ '_ \ / _` | | '_ \ / _ \
 _| || (_) | | | | |  __/ | | | (_| | | | | |  __/
 \___/\___/|_| |_|  \___|_| |_|\__, |_|_| |_|\___|
								__/ |
							   |___/


NAME: IonOpenGL.hpp

DESCTIPTION: OpenGL debug functions and macros

AUTHOR: Noah de Pischof | @torrra on GitHub

*/


#ifndef __ION_OPENGL_H__
#define __ION_OPENGL_H__

#ifndef glGetError
#include "glad/glad.h"
#endif // !glGetError

#include "IonDebug.hpp"

namespace internal::opengl
{
	inline const char* TranslateErrorCode(GLenum _code)
	{
		// Some error codes may not be present in every version of OpenGL,
		// so use numeric values instead of macro
		switch (_code)
		{
		case 0x0500: return "OpenGL error: Invalid enum";
		case 0x0501: return "OpenGL error: Invalid value";
		case 0x0502: return "OpenGL error: Invalid operation";
		case 0x0503: return "OpenGL error: Stack overflow";
		case 0x0504: return "OpenGL error: Stack underflow";
		case 0x0505: return "OpenGL error: Out of memory";
		case 0x0506: return "OpenGL error: Invalid framebuffer operation";
		case 0x0507: return "OpenGL error: Context lost";

		default: return "OpenGL error: Unknown error";
		}
	}


	inline const char* VerboseErrorDescription(GLenum _code)
	{
		// Add onto error message previously obtained from TranslateErrorCode
		switch (_code)
		{
		case 0x0500: return "\nA parameter passed as an enum was not accepted by the callee function.";
		case 0x0501: return "\nAn illegal parameter was passed to a function.";
		case 0x0502: return "\nThe current OpenGL state does not allow for a given operation to be performed.";
		case 0x0503: return "\nStack upper limit reached. Pushing any more data to the stack would overflow it.";
		case 0x0504: return "\nStack lower limit reached. Popping any more data off the stack is impossible.";
		case 0x0505: return "\nUnable to allocate more memory.\nWARNING: This error's behavior is undefined. Partial execution may occur.";
		case 0x0506: return "\nAttempt to read from or write to an incomplete framebuffer.";
		case 0x0507: return "\nGraphics card was reset. OpenGL context lost.";

		default: return "Unable to find cause due to unknown error code";
		}
	}


	inline void ClearErrors(void)
	{
		// glGetError resets flags as they are returned
		// to the user
		while (glGetError());
	}


	inline bool CheckError(const char* _file, uint32_t _line, const char* _exprString, bool verbose = false)
	{
		// Check if last instruction did not raise any OpenGL error flags

		GLuint error = glGetError();

		if (!error)
			return true;

		std::stringstream	errorMsg;

		errorMsg << TranslateErrorCode(error);

		if (verbose)
			errorMsg << VerboseErrorDescription(error);

		errorMsg << "\nExpression: " << _exprString;
		Log(true, _file, _line, errorMsg.str());

		return false;
	}
}

#ifndef NDEBUG

// Debug mode

// Check if an expression causes an OpenGL error. Logs error if one is found
#define ION_GL_CHECK(_expression)			internal::opengl::ClearErrors(); _expression; internal::opengl::CheckError(__FILE__, __LINE__, #_expression, false)

// Check if an expression causes an OpenGL error. Logs a verbose description if an error occurs
#define ION_GL_CHECK_VERBOSE(_expression)	internal::opengl::ClearErrors(); _expression; internal::opengl::CheckError(__FILE__, __LINE__, #_expression, true)


#ifdef ION_MSVC_COMPILER

// Calls an MSVC debug break instruction if an OpenGL error is found
#define ION_GL_BREAK(_expression)			internal::opengl::ClearErrors(); _expression; if(!internal::opengl::CheckError(__FILE__, __LINE__, #_expression, true)) __debugbreak();
#define ION_GL_ASSERT(_expression)			internal::opengl::ClearErrors(); _expression; ION_ASSERT(internal::opengl::CheckError(__FILE__, __LINE__, #_expression, true))

#else

// This macro is equivalent to ION_CHECK outside of microsoft's compiler
#define ION_GL_BREAK(_expression)			ION_CHECK(_expression)

#endif // !ION_MSVC_COMPILER

#else

// Release mode

#define ION_GL_CHECK(_expression)				(void) _expression
#define ION_GL_CHECK_VERBOSE(_expression)		(void) _expression

#define ION_GL_BREAK(_expression)				(void) _expression

#define ION_GL_ASSERT(_expression)				(void) _expression

#endif // !NDebug




#endif // !__ION_OPENGL_H__