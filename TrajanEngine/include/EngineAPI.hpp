#ifndef ENGINEAPI_HPP
#define ENGINEAPI_HPP

#ifdef _WIN32
    #ifdef ENGINE_EXPORTS
        #define ENGINE_API __declspec(dllexport)
    #else
        #define ENGINE_API __declspec(dllimport)
    #endif
#else
    #define ENGINE_API
#endif

#ifdef _MSC_VER
#pragma warning(disable:4251)
#endif

#endif