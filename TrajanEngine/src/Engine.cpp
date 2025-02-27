#include "Engine.hpp"

#include <chrono>
#include "glfw3.h"

#include "Log.hpp"

#include "ECSCoordinator.hpp"
#include "Window.hpp"

static ECSCoordinator gECSCoordinator;
static std::shared_ptr<Window> gWindow;

namespace Engine{

	void Initialize() {
		// Does nothing currently, maybe make it manage GLFW and other library initialization?
	}

	void Update(float dt) {

	}

	void Shutdown() {
		Output("Shutting down...");

		glfwTerminate();

		Output("Goodbye!", Severity::GOOD);
	}

	 std::shared_ptr<Window> CreateWindow(std::string const& windowName,
		unsigned int windowWidth, unsigned int windowHeight,
		unsigned int windowPosX, unsigned int windowPosY) {

		// Ignore position for now
		(void)windowPosX;
		(void)windowPosY;

		gWindow = std::make_shared<Window>(windowWidth, windowHeight, windowName);

		// Error check if Window was created successfully
		if (!gWindow) {
			Output("Window could not be created!", Severity::ERROR);
			return nullptr;
		}

		return gWindow;
	}

}

