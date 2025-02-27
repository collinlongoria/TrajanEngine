#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "EngineAPI.hpp"

#include <cstdint>

#include "Log.hpp"

#include "glad.h"
#include "glfw3.h"

class ENGINE_API Window {
public:
	// unique_ptr deletion
	using GLFWwindowDeleter = void(*)(GLFWwindow*);

	// Constructor
	Window(uint32_t width, uint32_t height, const std::string& name);

	// Destructor
	~Window() = default;

	// Poll and Process GLFW events
	void PollEvents();

	// Swap front and back buffers
	void SwapBuffers();

	// Returns if window should close
	bool ShouldClose() const;

	// Provides access to underlying GLFWwindow pointer
	GLFWwindow* NativeWindow() const {
		return mWindow.get();
	}

	// Getters for window properties
	uint32_t Width() const { return mWidth; }
	uint32_t Height() const { return mHeight; }
	const std::string& Name() const { return mName; }

	// Sets key/input callback for the window
	void SetKeyCallback(GLFWkeyfun callback) {
		if (mWindow)
			glfwSetKeyCallback(mWindow.get(), callback);
	}

private:
	uint32_t mWidth, mHeight;
	std::string mName;
	std::unique_ptr<GLFWwindow, GLFWwindowDeleter> mWindow;

	// TODO: GLFWManager that handles initializing and shutting down GLFW
	static bool sGLFWInitialized;
};


#endif