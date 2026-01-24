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

void ImGuiClass::Update()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("WaveEngine Debug Window");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	string text;

	for (vector<ImGuiClassData*>::iterator it = dataToDraw.begin(); it != dataToDraw.end(); ++it)
	{
		text = "EntityID: " + to_string((*it)->id);

		ImGui::Text(text.c_str());

		Entity* entity = GetEntityManager()->Get((*it)->id);

		if ((*it)->position != nullptr)
		{
			text = "ID: " + to_string((*it)->id) + ". Position. ";
			if (ImGui::InputFloat3(text.c_str(), &(*it)->position->x))
				entity->SetTRS();
		}

		if ((*it)->rotation != nullptr)
		{
			text = "ID: " + to_string((*it)->id) + ". Rotation.";
			if (ImGui::InputFloat3(text.c_str(), &(*it)->rotation->x))
				entity->SetTRS();
		}


		if ((*it)->textureID != nullptr)
		{
			Texture* texture = GetTextureManager()->GetTexture(*(*it)->textureID);

			ImGui::Image(*(*it)->textureID, ImVec2(texture->GetWidth() / 3, texture->GetHeight() / 3), ImVec2(0, 1), ImVec2(1, 0));
		}
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