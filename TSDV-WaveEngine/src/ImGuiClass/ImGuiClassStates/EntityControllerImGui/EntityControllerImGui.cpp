#include "EntityControllerImGui.h"

#include "ServiceProvider/ServiceProvider.h"

#include <ImGui/imgui.h>

#include <vector>

EntityController* EntityControllerImGui::GetEntityController()
{
	return ServiceProvider::Instance().TryGet<EntityController>();
}

void EntityControllerImGui::Update()
{
	if (!GetEntityController())
	{
		if (ImGui::Button("Create Controller"))
			ServiceProvider::Instance().Register<EntityController>(new EntityController());
	}
	else
	{
		if (ImGui::Button("Delete Controller"))
		{
			ServiceProvider::Instance().UnRegister<EntityController>();
			return;
		}

		ImGui::InputInt("Entity ID to Add", &entityToAdd);

		if (ImGui::Button("Confirm Addition"))
			GetEntityController()->AddEntityIDs(entityToAdd);

		ImGui::InputInt("Entity ID to Remove", &entityToRemove);

		if (ImGui::Button("Confirm Deletion"))
			GetEntityController()->RemoveEntityID(entityToRemove);

		ImGui::Text("Entities in Controller");
		for (vector<unsigned int>::const_iterator it = GetEntityController()->GetEntityIDs().begin(); it != GetEntityController()->GetEntityIDs().end(); ++it)
		{
			text = "ID: " + to_string(*it);
			ImGui::Text(text.c_str());

			ImGui::Separator();
		}
	}
}
