// Copyright (C) 2014 The Android Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef EMUGL_COMMON_SHARED_LIBRARY_H
#define EMUGL_COMMON_SHARED_LIBRARY_H

#ifdef _WIN32
#include <windows.h>
#endif

namespace emugl {

// A class used to open a platform-specific shared library, and probe
// it for symbols. Usage is the following:
//
//    // Open the library.
//    SharedLibrary* library = SharedLibrary::open("libFoo");
//    if (!library) {
//        ... could not find / open library!
//    }
//
//    //Probe for function symbol.
//    FunctionPtr my_func = library->findSymbol("my_func");
//
//    // Closes library/
//    delete library;
//
class SharedLibrary {
public:
    // Open a given library. |libraryName| can be either a full library
    // path, or a simple name without an extension. On success, returns
    // a new SharedLibrary instance that must be deleted by the caller.
    static SharedLibrary* open(const char* libraryName);

    // Closes an existing SharedLibrary instance.
    ~SharedLibrary();

    // Generic function pointer type, for values returned by the
    // findSymbol() method.
    typedef void (*FunctionPtr)(void);

    // Probe a given SharedLibrary instance to find a symbol named
    // |symbolName| in it. Return its address as a FunctionPtr, or
    // NULL if the symbol is not found.
    FunctionPtr findSymbol(const char* symbolName);

private:
#ifdef _WIN32
    typedef HMODULE HandleType;
#else
    typedef void* HandleType;
#endif

    // Constructor intentionally hidden.
    SharedLibrary(HandleType);

    HandleType mLib;
};

// Macro to compose emugl shared library name under various OS and bitness
// eg.
//     on x86_64, EMUGL_LIBNAME("foo") --> "lib64foo"

#if defined(__x86_64__)
#  define EMUGL_LIBNAME(name) "lib64" name
#elif defined(__i386__)
#  define EMUGL_LIBNAME(name) "lib" name
#else
/* This header is included by target w/o using EMUGL_LIBNAME().  Don't #error, leave it undefined */
#endif

}  // namespace emugl

#endif  // EMUGL_COMMON_SHARED_LIBRARY_H
