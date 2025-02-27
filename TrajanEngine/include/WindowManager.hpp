#ifndef WINDOWMANAGER_HPP
#define WINDOWMANAGER_HPP

#include <string>

#include "EngineAPI.hpp"

struct GLFWwindow;

class WindowManager {
public:
	GLFWwindow& Init(std::string const& windowName,
		unsigned int windowWidth, unsigned int windowHeight,
		unsigned int windowPosX, unsigned int windowPosY);

	void Update();

	void ProcessInput();

	void Shutdown();

	// Poll WindowManager for shutdown
	bool Quit() const { return toQuit; }

private:
	GLFWwindow* window = nullptr;

	bool toQuit = false;
};

#endif