#include "Editor.hpp"

#include "Window.hpp"
#include "Log.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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

	static bool show = false;

	ImGui::Begin("Hello World!");

	ImGui::Checkbox("Demo", &show);

	ImGui::End();

	// Rendering ImGui
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void Editor::Shutdown() {
	// ImGui Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	Output("Editor Shutdown!", Severity::MESSAGE);
}