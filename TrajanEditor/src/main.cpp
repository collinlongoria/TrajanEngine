#include <chrono>
#include <print>
#include <Windows.h>

typedef void (*EngineInitFunc)    ();
typedef int  (*EngineUpdateFunc)  (float);
typedef int  (*EngineShutdownFunc)();

int main(void) {
	// Load Engine Module
	HMODULE engineModule = LoadLibraryA("TrajanEngine.dll");

	if (!engineModule) return EXIT_FAILURE;

	// Inject Engine Functions
	EngineInitFunc EngineInit = (EngineInitFunc)GetProcAddress(engineModule, "EngineInit");
	EngineUpdateFunc EngineUpdate = (EngineUpdateFunc)GetProcAddress(engineModule, "EngineUpdate");
	EngineShutdownFunc EngineShutdown = (EngineShutdownFunc)GetProcAddress(engineModule, "EngineShutdown");

	if (EngineInit && EngineUpdate && EngineShutdown) {
		
		EngineInit();

		// Engine Loop
		float dt = 0.0f; int quitCode = 0;
		while (quitCode != 1) {
			auto start = std::chrono::high_resolution_clock::now();

			quitCode = EngineUpdate(dt);

			auto stop = std::chrono::high_resolution_clock::now();

			// Calculate delta
			dt = std::chrono::duration<float, std::chrono::seconds::period>(stop - start).count();
		}

		EngineShutdown();
	}
	else {
		return EXIT_FAILURE;
	}

	FreeLibrary(engineModule);
	return EXIT_SUCCESS;
}