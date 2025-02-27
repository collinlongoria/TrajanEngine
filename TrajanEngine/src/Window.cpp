#include "Window.hpp"

bool Window::sGLFWInitialized = false;

Window::Window(uint32_t width, uint32_t height, const std::string& name)
	: mWidth(width), mHeight(height), mName(name), mWindow(nullptr, glfwDestroyWindow)
{
	// Initialize GLFW
	if (!sGLFWInitialized) {
		Output("Initializing GLFW...");
		if (!glfwInit()) {
			Output("Failed to initialize GLFW!", Severity::ERROR);
			return;
		}
	}

	// Set GLFW Window Hints
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create GLFW Window
	Output("Creating GLFW window...");
	GLFWwindow* rawWindow = (glfwCreateWindow(mWidth, mHeight, mName.c_str(), NULL, NULL));
	if (!rawWindow) {
		Output("Failed to create GLFW window!", Severity::ERROR);
		return;
	}

	mWindow = std::unique_ptr<GLFWwindow, GLFWwindowDeleter>(rawWindow, glfwDestroyWindow);

	// Make Context Current
	glfwMakeContextCurrent(mWindow.get());

	// Initialize glad
	Output("Initializing glad...");
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		Output("Failed to initialize glad!", Severity::ERROR);
		return;
	}
	glfwSwapInterval(2);

	// Configure OpenGL
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Set User Pointer
	glfwSetWindowUserPointer(mWindow.get(), this);

	Output("Window initialized!", Severity::GOOD);
}

void Window::PollEvents() {
	glfwPollEvents();
}

void Window::SwapBuffers() {
	if (mWindow)
		glfwSwapBuffers(mWindow.get());
}

bool Window::ShouldClose() const {
	return mWindow ? glfwWindowShouldClose(mWindow.get()) : true;
}