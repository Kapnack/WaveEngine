#include "EntitiesImGui.h"

#include <ImGui/imgui.h>

#include "ServiceProvider/ServiceProvider.h"
#include <Entity/Entity2D/Shape/Square/Square.h>
#include <Entity/Entity2D/Shape/Triangle/Triangle.h>

EntitiesImGui::EntitiesImGui() : ImGuiClassState()
{
}

EntitiesImGui::~EntitiesImGui()
{
}

EntityManager* EntitiesImGui::GetEntityManager()
{
	return ServiceProvider::Instance().Get<EntityManager>();
}

EntityFactory* EntitiesImGui::GetEntityFactory()
{
	return ServiceProvider::Instance().Get<EntityFactory>();
}

MaterialManager* EntitiesImGui::GetMaterialManager()
{
	return ServiceProvider::Instance().Get<MaterialManager>();
}

TextureManager* EntitiesImGui::GetTextureManager()
{
	return ServiceProvider::Instance().Get<TextureManager>();
}

void EntitiesImGui::Update()
{

	ImGui::Combo("Entity Factory", &currentCreationOption, creationOptions, IM_ARRAYSIZE(creationOptions));

	if (currentCreationOption > 0)
	{
		text = "Spawn Entity";
		if (ImGui::Button(text.c_str()))
			switch (currentCreationOption)
			{
			case 1:

				GetEntityFactory()->Create<Sprite>();
				break;

			case 2:

				GetEntityFactory()->Create<Square>();
				break;

			case 3:

				GetEntityFactory()->Create<Triangle>();
				break;

			default:
				break;
			}
	}

	ImGui::Separator();

	ImGui::Text("Delete Entity by ID");
	ImGui::InputInt("Input Entity ID", &entityToDelete);

	if (ImGui::Button("Delete Entity"))
		GetEntityManager()->DeleteEntity(entityToDelete);

	ImGui::Separator();

	text = "Show Entities Materials";
	ImGui::Checkbox(text.c_str(), &showMaterials);

	text = "Show Entities Textures";
	ImGui::Checkbox(text.c_str(), &showTextures);

	for (auto it : GetEntityManager()->GetEntities())
	{
		if (it.second == nullptr)
			continue;

		text = "EntityID: " + to_string(it.second->ID);

		ImGui::Text(text.c_str());

		text = "ID: " + to_string(it.second->ID) + ". Position. ";
		if (ImGui::DragFloat3(text.c_str(), &it.second->position.x))
			it.second->SetTRS();

		text = "ID: " + to_string(it.second->ID) + ". Rotation.";
		if (ImGui::DragFloat3(text.c_str(), &it.second->rotation.x))
			it.second->SetTRS();

		text = "ID: " + to_string(it.second->ID) + ". Scale.";
		if (ImGui::DragFloat3(text.c_str(), &it.second->scale.x))
			it.second->SetTRS();

		text = "ID: " + to_string(it.second->ID) + ". IsActive.";
		ImGui::Checkbox(text.c_str(), &it.second->isActive);

		if (showMaterials)
		{
			text = "ID: " + to_string(it.second->ID) + ". Input Material ID. ";
			ImGui::InputInt(text.c_str(), &materialID);

			text = "Set Material ##xx ID: " + to_string(it.second->ID);

			if (ImGui::Button(text.c_str()))
				it.second->SetMaterial(materialID);

			Material* material = GetMaterialManager()->GetMaterial(it.second->GetMaterial());

			if (material != nullptr)
			{
				text = "##xx Name: " + material->GetName() + ". Program ID: " + to_string(material->GetProgram()) + "." + "ID: " + to_string(it.second->ID);

				ImGui::ColorEdit4(text.c_str(), &material->color.x);
			}
		}

		if (showTextures)
		{
			if (Sprite* sprite = dynamic_cast<Sprite*>(it.second))
			{
				text = "ID: " + to_string(it.second->ID) + ". Position. ";
				ImGui::InputInt(text.c_str(), &textureID);

				text = "Set Texture ##xx ID: " + to_string(it.second->ID);

				if (ImGui::Button(text.c_str()))
					sprite->SetTexture(textureID);

				Texture* texture = GetTextureManager()->GetTexture(sprite->GetTexture());

				if (texture != nullptr)
					ImGui::Image(texture->GetTextureID(), ImVec2(texture->GetWidth() / 3, texture->GetHeight() / 3), ImVec2(0, 1), ImVec2(1, 0));
			}
		}

		ImGui::Separator();
	}
}
