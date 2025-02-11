#include "stdafx.hpp"

#include "WindowManager.hpp"
#include "Log.hpp"

WindowManager windowManager;

int main(void) {

	windowManager.Init("Trajan Engine", 1024, 760, 0, 0);

	float dt = 0.0f;
	while (!windowManager.Quit()) {
		auto start = std::chrono::high_resolution_clock::now();

		windowManager.ProcessInput();
		
		// Update stuff here...
		
		windowManager.Update();

		auto stop = std::chrono::high_resolution_clock::now();

		// Calculate delta
		dt = std::chrono::duration<float, std::chrono::seconds::period>(stop - start).count();
	}

	Output("Shutting down...");
	windowManager.Shutdown();

	Output("Goodbye!", Severity::GOOD);
	return EXIT_SUCCESS;
}