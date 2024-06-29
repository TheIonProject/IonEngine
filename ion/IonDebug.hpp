/*

 _____                               _
|_   _|                             (_)
  | |  ___  _ __     ___ _ __   __ _ _ _ __   ___
  | | / _ \| '_ \   / _ \ '_ \ / _` | | '_ \ / _ \
 _| || (_) | | | | |  __/ | | | (_| | | | | |  __/
 \___/\___/|_| |_|  \___|_| |_|\__, |_|_| |_|\___|
                                __/ |
                               |___/


NAME: IonDebug.hpp

DESCTIPTION: Macros to help with internal debugging

AUTHOR: Noah de Pischof | @torrra on GitHub

STYLE:

ION_ prefix helps identify macros specific to the project

()  empty parentheses are added after macros that represent an action, to
    differentiate them from macros that extend to simple values

*/


#ifndef __ION_ASSERT_H__
#define __ION_ASSERT_H__

#include "IonCompiler.hpp"

#if (WIN32)


// Windows API headers cause truncation warnings.
// Disable them as they are irrelevant and there
// is nothing we can do about it :(
ION_PUSH_WARNINGS()
ION_DISABLE_WARNING(ION_VALUE_TRUNCATION)

#include <windows.h>
#include <winuser.h>

ION_POP_WARNINGS()

#include <string>

#else

#include <iostream>

#endif // Win32

namespace internal
{
    inline void Assert(bool _expression, const char* _file, uint32_t _line, const char* _exprString)
    {
        if (_expression)
            return;

#if (WIN32)

        // Create a popup window on windows

        std::string   errorMessage("Assertion failed!\r\nIn file: ");

        errorMessage += _file;
        errorMessage += "\r\nOn line: ";
        errorMessage += std::to_string(_line);
        errorMessage += "\r\nThe following assertion failed:\r\n\r\n";
        errorMessage += _exprString;


        int boxStatus = MessageBox
        (
            // No window owns this popup
            NULL,

            // Popup message
            errorMessage.c_str(),

            // Popup title
            "Ion Engine error",

            // OK button | big red icon| user must interact with window to resume execution
            MB_OK | MB_ICONSTOP | MB_TASKMODAL);

        // OK button (or escape key was pressed)
        if (IDOK == boxStatus)
            exit(-1);


#else

        // Show an erroe message on other platforms

        std::cerr << "[Ion Engine] Assertion failed!\nIn file: " << _file << ":" << _line <<
            "On line:" << _line << "\nThe following assertion failed:\n" << _exprString << std::endl;

        exit(-1);


#endif // WIN32
    }
}

#if !defined(NDEBUG)

// Compiling in debug mode

#define ION_ASSERT(_expression)\
internal::Assert(static_cast<bool>(_expression), __FILE__, __LINE__, #_expression);


#else // NDEBUG

// Compiling in release mode

// Disable assert in release
#define ION_ASSERT(expression)

# endif // !NDEBUG

#endif // !__ION_ASSERT_H__