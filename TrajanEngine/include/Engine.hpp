#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "EngineAPI.hpp"

#include "Window.hpp"

namespace Engine {
	
	ENGINE_API void Initialize();
	//ENGINE_API void Initialize(GLFWwindow& window);

	ENGINE_API void Update(float dt);

	ENGINE_API void Shutdown();

	ENGINE_API std::shared_ptr<Window> CreateWindow(std::string const& windowName,
		unsigned int windowWidth, unsigned int windowHeight,
		unsigned int windowPosX, unsigned int windowPosY);

}; 

#endif