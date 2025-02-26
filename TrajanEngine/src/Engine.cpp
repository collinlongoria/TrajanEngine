#include "Engine.hpp"

#include <chrono>

#include "Log.hpp"

void Engine::Init() {
	windowManager.Init("Trajan Engine", 1024, 760, 0, 0);
}

int Engine::Update(float dt) {
	if (windowManager.Quit()) return 1;


	windowManager.ProcessInput();

	// Update stuff here...

	windowManager.Update();


	return 0;
}

int Engine::Shutdown() {
	Output("Shutting down...");
	windowManager.Shutdown();

	Output("Goodbye!", Severity::GOOD);
	return EXIT_SUCCESS;
}