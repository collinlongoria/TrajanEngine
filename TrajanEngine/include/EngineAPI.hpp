#ifndef ENGINEAPI_HPP
#define ENGINEAPI_HPP

#ifdef __cplusplus
extern "C" {
#endif

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

	ENGINE_API void EngineInit();
	ENGINE_API int  EngineUpdate(float dt);
	ENGINE_API int  EngineShutdown();

#ifdef __cplusplus
}
#endif

/*
	To avoid error generated from STL libraries included as private variables inside of classes
	@TODO: Refactor classes where this is the case to follow pimpl pattern
	Current known classes:
		Log
		WindowManager
*/
#ifdef _MSC_VER
#pragma warning(disable:4251)
#endif

/*
	I might want to do this another way
*/
void EngineInit();
int EngineUpdate(float dt);
int EngineShutdown();

#endif