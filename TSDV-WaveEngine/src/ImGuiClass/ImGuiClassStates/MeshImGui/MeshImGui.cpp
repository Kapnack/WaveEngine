#include "MeshImGui.h"

#include <ImGui/imgui.h>

namespace WaveEngine
{
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
		for (vector<Drawable*>::iterator it = GetEntityManager()->GetDrawables().begin(); it != GetEntityManager()->GetDrawables().end(); ++it)
		{
			text = "Entity ID: " + to_string((*it)->ID);
			ImGui::Text(text.c_str());

			for (int i = 0; i < (*it)->vertexSize; ++i)
			{
				currentVertex = &(*it)->vertex[i];

				text = to_string(i) + " Vertex Postion of ID: " + to_string((*it)->ID);
				if (ImGui::DragFloat3(text.c_str(), &currentVertex->position.x))
					(*it)->UpdateVertexBuffer();

				text = to_string(i) + "Vertex Color of ID: " + to_string((*it)->ID);
				if (ImGui::ColorEdit4(text.c_str(), &currentVertex->color.x))
					(*it)->UpdateVertexBuffer();


				text = to_string(i) + "Vertex UV: " + to_string((*it)->ID);
				if (ImGui::DragFloat2(text.c_str(), &currentVertex->textureCordinates.x))
					(*it)->UpdateVertexBuffer();

				ImGui::Separator();

			}

			ImGui::Separator();
			ImGui::Separator();

		}
	}
}