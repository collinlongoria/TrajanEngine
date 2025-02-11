#include "stdafx.hpp"

#include "glad.h"
#include "glfw3.h"

#include "Log.hpp"

#include "WindowManager.hpp"

void WindowManager::Init(std::string const& windowName, unsigned int windowWidth, unsigned int windowHeight, unsigned int windowPosX, unsigned int windowPosY) {
	// Init GLFW
	Output("Initializing GLFW...");
	if (!glfwInit()) {
		Output("Failed to initialize GLFW!", Severity::ERROR);
		toQuit = true;
		return;
	}

	// Specify version
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window
	Output("Creating GLFW window...");
	window = glfwCreateWindow(windowWidth, windowHeight, windowName.c_str(), NULL, NULL);
	if (!window) {
		Output("Failed to create GLFW window!", Severity::ERROR);
		toQuit = true;
		return;
	}

	// Make context current
	glfwMakeContextCurrent(window);

	// Init glad
	Output("Initializing glad...");
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		Output("Failed to initialize glad!", Severity::ERROR);
		toQuit = true;
		return;
	}
	glfwSwapInterval(2);

	// Configure OpenGL
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Output("Window initialized!", Severity::GOOD);
}

void WindowManager::Update() {
	if (glfwWindowShouldClose(window)) {
		toQuit = true;
	}

	glfwSwapBuffers(window);
}

void WindowManager::ProcessInput() {
	glfwPollEvents();
}

void WindowManager::Shutdown() {
	Output("Shutting down GLFW...");
	glfwDestroyWindow(window);
	glfwTerminate();
}