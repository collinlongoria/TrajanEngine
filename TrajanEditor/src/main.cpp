#include <chrono>
#include <print>

#include "Engine.hpp"
#include "Window.hpp"

int main(void) {
	// Initialize Engine
	Engine::Initialize();

	// Create window
	auto window = Engine::CreateWindow("Trajan", 640, 480, 0, 0);

	// Engine Loop
	float dt = 0.0f;
	while (!window->ShouldClose()) {
		auto start = std::chrono::high_resolution_clock::now();

		window->PollEvents();

		Engine::Update(dt);

		window->SwapBuffers();

		auto stop = std::chrono::high_resolution_clock::now();

		// Calculate delta
		dt = std::chrono::duration<float, std::chrono::seconds::period>(stop - start).count();
	}

	// Shutdown Engine
	Engine::Shutdown();

	return EXIT_SUCCESS;
}