#include "MeshImGui.h"

#include <ImGui/imgui.h>

MeshImGui::MeshImGui() : ImGuiClassState()
{
}

MeshImGui::~MeshImGui()
{
}

EntityManager* MeshImGui::GetEntityManager()
{
	return ServiceProvider::Instance().Get<EntityManager>();
}

void MeshImGui::Update()
{
	for (map<unsigned int, Drawable*>::iterator it = GetEntityManager()->GetDrawables().begin(); it != GetEntityManager()->GetDrawables().end(); ++it)
	{
		text = "Entity ID: " + to_string(it->first);
		ImGui::Text(text.c_str());

		for (int i = 0; i < it->second->vertexSize; ++i)
		{
			currentVertex = &it->second->vertex[i];

			text = to_string(i) + " Vertex Postion of ID: " + to_string(it->first);
			if (ImGui::DragFloat3(text.c_str(), &currentVertex->position.x))
				it->second->UpdateVertexBuffer();

			text = to_string(i) + "Vertex Color of ID: " + to_string(it->first);
			if (ImGui::ColorEdit4(text.c_str(), &currentVertex->color.x))
				it->second->UpdateVertexBuffer();


			text = to_string(i) + "Vertex UV: " + to_string(it->first);
			if (ImGui::DragFloat2(text.c_str(), &currentVertex->textureCordinates.x))
				it->second->UpdateVertexBuffer();

			ImGui::Separator();

		}

		ImGui::Separator();
		ImGui::Separator();

	}
}
