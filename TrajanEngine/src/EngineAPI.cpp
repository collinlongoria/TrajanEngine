#include "EngineAPI.hpp"

#include "Engine.hpp"

static Engine g_engine;

void EngineInit() {
	g_engine.Init();
}

int EngineUpdate(float dt) {
	return g_engine.Update(dt);
}

int EngineShutdown() {
	return g_engine.Shutdown();
}