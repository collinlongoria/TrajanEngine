#include "Editor.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Window.hpp"
#include "Log.hpp"

void Editor::Initialize(Window& window) {
	// Define GLSL version
	const char* glsl_version = "#version 460";
	
	// Setup ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable keyboard controls

	// Setup ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup ImGui backends
	ImGui_ImplGlfw_InitForOpenGL(window.NativeWindow(), true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	Output("Editor Initialized!", Severity::GOOD);
}

void Editor::Update(float dt) {

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	RenderMenu();
	if(showFPS) RenderFPSCounter();

	// Rendering ImGui
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void Editor::RenderMenu() {
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("Options")) {
			// FPS
			ImGui::MenuItem("Show FPS", nullptr, &showFPS);
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}
void Editor::RenderFPSCounter() {
	ImVec2 windowPos(0, ImGui::GetFrameHeight());
	ImGui::SetNextWindowPos(windowPos);
	ImGui::SetNextWindowBgAlpha(0.35f); //optional, may remove

	// remove decorations
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoInputs;
	ImGui::Begin("FPS Counter", nullptr, window_flags);
	ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate); // change with my calculated framerate
	ImGui::End();
}
/*
void RenderGameScreen(ImTextureID gameTexture, const ImVec2& gameTextureSize) {
	ImGui::Begin("Game View");
	ImGui::Image(gameTexture, gameTextureSize);
	ImGui::End();
}
*/

void Editor::Shutdown() {
	// ImGui Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	Output("Editor Shutdown!", Severity::MESSAGE);
}