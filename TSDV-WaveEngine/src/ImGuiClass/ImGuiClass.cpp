#include "ImGuiClass.h"

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_opengl3.h>
#include <ImGui/imgui_impl_glfw.h>

Window* ImGuiClass::GetWindow()
{
	return ServiceProvider::Instance().Get<Window>();
}

void ImGuiClass::Init()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(GetWindow()->GetGLFWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGui::StyleColorsDark();
}

void ImGuiClass::Update()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Epic Window");

	string label;

	for (vector<ImGuiClassData>::iterator it = dataToDraw.begin(); it != dataToDraw.end(); ++it)
	{
		if (it->position != nullptr)
		{
			label = to_string(it->id) + ": Pos. ";
			ImGui::InputFloat3(label.c_str(), &it->position->x);
		}

		if (it->rotation != nullptr)
		{
			label = to_string(it->id) + ": Rot. ";
			ImGui::InputFloat3(label.c_str(), &it->rotation->x);
		}

		if (it->textureID != nullptr)
		{
			ImGui::Image((ImTextureID)(intptr_t)it->textureID, ImVec2(256, 256));
		}
	}

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}

void ImGuiClass::Draw()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

ImGuiClass::ImGuiClass() : Service()
{
	Init();
}

ImGuiClass::~ImGuiClass()
{
	Unload();
}

void ImGuiClass::CreateEditor(const unsigned int& ID, Vector3& position, Vector3& rotation, unsigned int* textureID)
{
	ImGuiClassData newData;

	newData.id = ID;
	newData.position = &position;
	newData.rotation = &rotation;
	newData.textureID = textureID;

	dataToDraw.push_back(newData);
}

void ImGuiClass::Unload()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}