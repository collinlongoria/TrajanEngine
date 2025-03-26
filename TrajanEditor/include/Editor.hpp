#ifndef EDITOR_HPP
#define EDITOR_HPP

class Window;

namespace Editor {
	static bool showFPS = false;

	void Initialize(Window& window);

	void Update(float dt);

	/*
		Helper functions (that go in Update)
	*/
	void RenderMenu();
	void RenderFPSCounter();
	//void RenderGameScreen(ImTextureID gameTexture, const ImVec2& gameTextureSize);

	void Shutdown();

};

#endif