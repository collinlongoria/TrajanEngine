#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "EngineAPI.hpp"

#include "WindowManager.hpp"

class ENGINE_API Engine {
public:
	void Init();
	int Update(float dt);
	int Shutdown();

private:
	WindowManager windowManager;
};

#endif