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

	ImGui::Combo("Filter", &currentFilter, filters, IM_ARRAYSIZE(filters));

	text = "Show Entities Materials";
	ImGui::Checkbox(text.c_str(), &showMaterials);

	text = "Show Entities Textures";
	ImGui::Checkbox(text.c_str(), &showTextures);

	switch (currentFilter)
	{
	case 0:

		for (auto it : GetEntityManager()->GetEntities())
			ShowEntity(it.second);

		break;

	case 1:

		for (auto it : GetEntityManager()->GetAllOfType<Sprite>())
			ShowEntity(it);

		break;

	case 2:

		for (auto it : GetEntityManager()->GetAllOfType<Square>())
			ShowEntity(it);

		break;

	case 3:

		for (auto it : GetEntityManager()->GetAllOfType<Triangle>())
			ShowEntity(it);

		break;

	case 4:

		for (auto it : GetEntityManager()->GetAllOfType<Tile>())
			ShowEntity(it);

		break;

	default:
		break;
	}
}

void EntitiesImGui::ShowEntity(Entity* entity)
{
	ShowEntityData(entity);

	if (showMaterials)
		ShowMaterial(entity);

	if (showTextures && (currentFilter == 4 || currentFilter == 2))
		if (Sprite* sprite = dynamic_cast<Sprite*>(entity))
			ShowTexture(sprite);

	ImGui::Separator();
}

void EntitiesImGui::ShowEntityData(Entity* it)
{
	if (it == nullptr)
		return;

	text = "EntityID: " + to_string(it->ID);

	ImGui::Text(text.c_str());

	text = "ID: " + to_string(it->ID) + ". Position. ";
	if (ImGui::DragFloat3(text.c_str(), &it->position.x))
		it->SetTRS();

	text = "ID: " + to_string(it->ID) + ". Rotation.";
	if (ImGui::DragFloat3(text.c_str(), &it->rotation.x))
		it->SetTRS();

	text = "ID: " + to_string(it->ID) + ". Scale.";
	if (ImGui::DragFloat3(text.c_str(), &it->scale.x))
		it->SetTRS();

	text = "ID: " + to_string(it->ID) + ". IsActive.";
	ImGui::Checkbox(text.c_str(), &it->isActive);
}

void EntitiesImGui::ShowMaterial(Entity* entity)
{
	text = "ID: " + to_string(entity->ID) + ". Input Material ID. ";
	ImGui::InputInt(text.c_str(), &materialID);

	text = "Set Material ##xx ID: " + to_string(entity->ID);

	if (ImGui::Button(text.c_str()))
		entity->SetMaterial(materialID);

	Material* material = GetMaterialManager()->GetMaterial(entity->GetMaterial());

	if (material != nullptr)
	{
		text = "##xx Name: " + material->GetName() + ". Program ID: " + to_string(material->GetProgram()) + "." + "ID: " + to_string(entity->ID);

		ImGui::ColorEdit4(text.c_str(), &material->color.x);
	}
}

void EntitiesImGui::ShowTexture(Sprite* sprite)
{
	text = "ID: " + to_string(sprite->ID) + ". Position. ";
	ImGui::InputInt(text.c_str(), &textureID);

	text = "Set Texture ##xx ID: " + to_string(sprite->ID);

	if (ImGui::Button(text.c_str()))
		sprite->SetTexture(textureID);

	Texture* texture = GetTextureManager()->GetTexture(sprite->GetTexture());

	if (texture != nullptr)
		ImGui::Image(texture->GetTextureID(), ImVec2(texture->GetWidth() / 3, texture->GetHeight() / 3), ImVec2(0, 1), ImVec2(1, 0));
}
