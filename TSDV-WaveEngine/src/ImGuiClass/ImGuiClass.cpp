#include "ImGuiClass.h"

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_opengl3.h>
#include <ImGui/imgui_impl_glfw.h>

ImGuiClass::ImGuiClass() : Service()
{
	Init();
}

ImGuiClass::~ImGuiClass()
{
	Unload();
}

Window* ImGuiClass::GetWindow()
{
	return ServiceProvider::Instance().Get<Window>();
}

Input* ImGuiClass::GetInput()
{
	return ServiceProvider::Instance().Get<Input>();
}
 
void ImGuiClass::Init()
{
	showEntitiesState = new EntitiesImGui();
	showTexturesState = new TexturesImGui();
	showMaterialsState = new MaterialsImGui();
	showMeshState = new MeshImGui();

	state = showEntitiesState;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(GetWindow()->GetGLFWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGui::StyleColorsDark();
}

void ImGuiClass::Unload()
{
	delete showTexturesState;
	delete showMaterialsState;
	delete showEntitiesState;
	delete showMeshState;

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiClass::Update()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("WaveEngine Debug Window");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	if (ImGui::Button("Entities", ImVec2(100, 25)))
		state = showEntitiesState;

	ImGui::SameLine();

	if (ImGui::Button("Textures", ImVec2(100, 25)))
		state = showTexturesState;

	ImGui::SameLine();

	if (ImGui::Button("Materials", ImVec2(100, 25)))
		state = showMaterialsState;

	ImGui::SameLine();

	if (ImGui::Button("Meshes", ImVec2(100, 25)))
		state = showMeshState;

	ImGui::Separator();

	if (state)
		state->Update();

	ImGui::End();
}

void ImGuiClass::Draw()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}