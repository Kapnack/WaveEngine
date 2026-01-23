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
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(GetWindow()->GetGLFWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330");
	IMGUI_CHECKVERSION();
	ImGui::StyleColorsDark();
}

void ImGuiClass::Update()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Epic Window");

	for (vector<ImGuiClassData>::iterator it = dataToDraw.begin(); it != dataToDraw.end(); ++it)
	{
		ImGui::SliderFloat(it->label.c_str(), &it->vector->x, it->min, it->max);
	}

	ImGui::Text("Application avarag Frame rate", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}

void ImGuiClass::Draw()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiClass::Unload()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiClass::CreateVec3Editor(const string& paramName, Vector3& vector, float min, float max)
{
	ImGuiClassData newData;

	newData.label = paramName;
	newData.vector = &vector;
	newData.min = min;
	newData.max = min;

	dataToDraw.push_back(newData);
}

ImGuiClass::ImGuiClass() : Service()
{
	Init();
}

ImGuiClass::~ImGuiClass()
{
	Unload();
}
