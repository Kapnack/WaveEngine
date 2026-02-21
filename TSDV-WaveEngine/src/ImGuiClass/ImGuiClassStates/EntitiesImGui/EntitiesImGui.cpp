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
	EntityCreator();

	EntityDeleter();

	EntityDisplayer();
}

void EntitiesImGui::EntityCreator()
{
	ImGui::Combo("Entity Factory", &currentCreationOption, creationOptions, IM_ARRAYSIZE(creationOptions));

	if (currentCreationOption > 0)
	{
		text = "Spawn Entity";
		if (ImGui::Button(text.c_str()))
			switch (currentCreationOption)
			{
			case 1: GetEntityFactory()->Create<Sprite>(); break;
			case 2: GetEntityFactory()->Create<Square>(); break;
			case 3: GetEntityFactory()->Create<Triangle>(); break;

			default:
				break;
			}
	}

	ImGui::Separator();
}

void EntitiesImGui::EntityDeleter()
{
	ImGui::Combo("Choose Delete form", &currentDeletionFilter, delitionFilters, IM_ARRAYSIZE(delitionFilters));


	if (currentDeletionFilter == 0)
	{
		ImGui::Text("Delete Entity by ID");
		ImGui::InputInt("Input Entity ID", &entityToDelete);
	}


	if (ImGui::Button("Delete"))
		switch (currentDeletionFilter)
		{
		case 0: GetEntityManager()->DeleteEntity(entityToDelete); break;

		case 1: GetEntityManager()->DeleteAll(); break;
		case 2: GetEntityManager()->DeleteAllOfType<Sprite>(); break;
		case 3: GetEntityManager()->DeleteAllOfType<Square>(); break;
		case 4: GetEntityManager()->DeleteAllOfType<Triangle>(); break;
		case 5: GetEntityManager()->DeleteAllOfType<Tile>(); break;
		case 6: GetEntityManager()->DeleteAllOfType<Drawable>(); break;
		case 7: GetEntityManager()->DeleteAllOfType<TileMap>(); break;

		default:
			break;
		}

	ImGui::Separator();
}

void EntitiesImGui::EntityDisplayer()
{
	ImGui::Combo("Filter", &currentFilter, filters, IM_ARRAYSIZE(filters));

	text = "Display in Reverse";
	ImGui::Checkbox(text.c_str(), &showInReverseOrder);

	text = "Show Entities Materials";
	ImGui::Checkbox(text.c_str(), &showMaterials);

	text = "Show Entities Textures";
	ImGui::Checkbox(text.c_str(), &showTextures);

	switch (currentFilter)
	{
	case 0:
		if (!showInReverseOrder)
			for (map<unsigned int, Entity*>::iterator it = GetEntityManager()->GetEntities().begin(); it != GetEntityManager()->GetEntities().end(); ++it)
				ShowEntity(it->second);
		else
			for (map<unsigned int, Entity*>::reverse_iterator it = GetEntityManager()->GetEntities().rbegin(); it != GetEntityManager()->GetEntities().rend(); ++it)
				ShowEntity(it->second);
		break;

	case 1: ShowAllOfType<Sprite>();   break;
	case 2: ShowAllOfType<Square>();   break;
	case 3: ShowAllOfType<Triangle>(); break;
	case 4: ShowAllOfType<Tile>();     break;
	case 5: ShowAllOfType<Drawable>();     break;
	case 6: ShowAllOfType<TileMap>();     break;
	}
}

void EntitiesImGui::ShowEntity(Entity* entity)
{
	ShowEntityData(entity);

	drawableIT = GetEntityManager()->GetDrawables().find(entity->GetID());

	if (drawableIT != GetEntityManager()->GetDrawables().end() && drawableIT->second)
	{
		text = "Current Layer : " + to_string(drawableIT->second->GetLayer()) + "##xx ID: " + to_string(drawableIT->first);
		ImGui::InputInt(text.c_str(), &layer);

		text = "Change Layer ##xx ID: " + to_string(drawableIT->first);
		if (ImGui::Button(text.c_str()))
			drawableIT->second->SetLayer(layer);

		if (showMaterials)
			ShowMaterial(drawableIT->first, drawableIT->second);

		if (showTextures)
			if (Sprite* sprite = dynamic_cast<Sprite*>(entity))
				ShowTexture(sprite);
	}

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
		it->CalculateTRS();

	text = "ID: " + to_string(it->ID) + ". Rotation.";
	if (ImGui::DragFloat3(text.c_str(), &it->rotation.x))
		it->CalculateTRS();

	text = "ID: " + to_string(it->ID) + ". Scale.";
	if (ImGui::DragFloat3(text.c_str(), &it->scale.x))
		it->CalculateTRS();

	text = "ID: " + to_string(it->ID) + ". IsActive.";
	if (ImGui::Checkbox(text.c_str(), &it->isActive))
		it->SetIsActive(it->isActive);
}

void EntitiesImGui::ShowMaterial(const unsigned int& ID, Drawable* drawable)
{
	text = "ID: " + to_string(ID) + ". Input Material ID. ";
	ImGui::InputInt(text.c_str(), &materialID);

	text = "Set Material ##xx ID: " + to_string(ID);

	drawableIT = GetEntityManager()->GetDrawables().find(ID);

	if (ImGui::Button(text.c_str()))
		drawable->SetMaterial(materialID);

	Material* material = GetMaterialManager()->GetMaterial(drawable->GetMaterial());

	if (material != nullptr)
	{
		text = "##xx Name: " + material->GetName() + ". Program ID: " + to_string(material->GetProgram()) + "." + "ID: " + to_string(ID);

		ImGui::ColorEdit4(text.c_str(), &material->color.x);
	}
}

void EntitiesImGui::ShowTexture(Sprite* sprite)
{
	text = "ID: " + to_string(sprite->GetID()) + ". Position. ";
	ImGui::InputInt(text.c_str(), &textureID);

	text = "Set Texture ##xx ID: " + to_string(sprite->GetID());

	if (ImGui::Button(text.c_str()))
		sprite->SetTexture(textureID);

	Texture* texture = GetTextureManager()->GetTexture(sprite->GetTexture());

	if (texture != nullptr)
		ImGui::Image(texture->GetTextureID(), ImVec2(texture->GetWidth() / 3, texture->GetHeight() / 3), ImVec2(0, 1), ImVec2(1, 0));
}
