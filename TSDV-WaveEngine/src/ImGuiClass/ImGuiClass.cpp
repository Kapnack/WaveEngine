#include "ImGuiClass.h"

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_opengl3.h>
#include <ImGui/imgui_impl_glfw.h>

#include "Material/Material.h"

ImGuiClass::ImGuiClass() : Service()
{
	Init();
}

ImGuiClass::~ImGuiClass()
{
	Unload();
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

void ImGuiClass::Unload()
{
	for (vector<ImGuiClassData*>::iterator it = dataToDraw.begin(); it != dataToDraw.end(); ++it)
		delete* it;

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiClass::GoToPreviousState()
{
	if ((static_cast<ImGuiClassStates>(currentState - 1)) == ImGuiClassStates::Begin)
		return;

	--currentState;
}

void ImGuiClass::GoToNextState()
{
	if ((static_cast<ImGuiClassStates>(currentState + 1)) == ImGuiClassStates::End)
		return;

	++currentState;
}

Window* ImGuiClass::GetWindow()
{
	return ServiceProvider::Instance().Get<Window>();
}

TextureManager* ImGuiClass::GetTextureManager()
{
	return ServiceProvider::Instance().Get<TextureManager>();
}

EntityManager* ImGuiClass::GetEntityManager()
{
	return ServiceProvider::Instance().Get<EntityManager>();
}

MaterialManager* ImGuiClass::GetMaterialManager()
{
	return ServiceProvider::Instance().Get<MaterialManager>();
}

void ImGuiClass::Update()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("WaveEngine Debug Window");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	if (ImGui::Button("Previous Page", ImVec2(100, 25)))
		GoToPreviousState();

	ImGui::SameLine();

	if (ImGui::Button("Next Page", ImVec2(100, 25)))
		GoToNextState();

	string text;
	Material* material;

	switch (static_cast<ImGuiClassStates>(currentState))
	{
	case ImGuiClassStates::ShowEntities:

		for (auto it : GetEntityManager()->GetEntities())
		{
			if (it.second == nullptr)
				continue;

			text = "EntityID: " + to_string(it.second->ID);

			ImGui::Text(text.c_str());

			text = "ID: " + to_string(it.second->ID) + ". Position. ";
			if (ImGui::InputFloat3(text.c_str(), &it.second->position.x))
				it.second->SetTRS();


			text = "ID: " + to_string(it.second->ID) + ". Rotation.";
			if (ImGui::InputFloat3(text.c_str(), &it.second->rotation.x))
				it.second->SetTRS();

			text = "ID: " + to_string(it.second->ID) + ". Scale.";
			if (ImGui::InputFloat3(text.c_str(), &it.second->scale.x))
				it.second->SetTRS();
		}

		break;

	case ImGuiClassStates::ShowTextures:

		for (auto it : GetTextureManager()->GetTextures())
		{
			if (it.second == nullptr)
				continue;

			ImGui::Image(it.second->GetTextureID(), ImVec2(it.second->GetWidth() / 3, it.second->GetHeight() / 3), ImVec2(0, 1), ImVec2(1, 0));
		}

		break;

	case ImGuiClassStates::ShowMaterials:

		for (auto it : GetMaterialManager()->GetMaterials())
		{
			if (it.second == nullptr)
				continue;

			text = "Name: " + it.second->GetName() + ". Material ID: " + to_string(it.second->GetProgram()) + ".";

			ImGui::SliderFloat4(text.c_str(), &it.second->color.x, 0, 1);
		}

		break;

	default:
		break;
	}

	ImGui::End();
}

void ImGuiClass::Draw()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiClass::CreateEditor(const unsigned int& ID, Vector3& position, Vector3& rotation, unsigned int* textureID)
{
	ImGuiClassData* newData = new ImGuiClassData();

	newData->id = ID;
	newData->position = &position;
	newData->rotation = &rotation;
	newData->textureID = textureID;

	dataToDraw.push_back(newData);
}