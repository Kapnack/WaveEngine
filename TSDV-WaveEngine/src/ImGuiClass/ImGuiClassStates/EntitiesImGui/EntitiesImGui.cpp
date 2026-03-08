#include "EntitiesImGui.h"

#include <ImGui/imgui.h>

#include "ServiceProvider/ServiceProvider.h"
#include <Entity/Entity2D/Shape/Square/Square.h>
#include <Entity/Entity2D/Shape/Triangle/Triangle.h>

namespace WaveEngine
{
	EntitiesImGui::EntitiesImGui() : ImGuiClassState()
	{
		creation = ComoboStruct
		(
			{
				{ "None", []() {} },
				{ "Sprites", [this]() {GetEntityFactory()->Create<Sprite>(); } },
				{ "Square", [this]() {GetEntityFactory()->Create<Square>(); } },
				{ "Triangle", [this]() {GetEntityFactory()->Create<Triangle>(); } }
			}
		);

		filters = ComoboStruct
		(
			{
				{ "Entities", [this]() {ShowAllEntities(); } },
				{ "Sprites", [this]() {ShowAllOfType<Sprite>(); } },
				{ "Squares", [this]() {ShowAllOfType<Square>(); } },
				{ "Triangles", [this]() {ShowAllOfType<Triangle>(); } },
				{ "Tiles", [this]() {ShowAllOfType<Tile>(); } },
				{ "Drawables", [this]() {ShowAllOfType<Drawable>(); } },
				{ "TileMaps", [this]() {ShowAllOfType<TileMap>(); } }
			}
		);

		deletionOptions = ComoboStruct
		(
			{
		{ "By ID", [this]() {GetEntityManager()->DeleteEntity(entityToDelete); }},
		{ "All Entities", [this]() {GetEntityManager()->DeleteAll(); }},
		{ "All Sprites", [this]() {GetEntityManager()->DeleteAllOfType<Sprite>(); }},
		{ "All Squares", [this]() {GetEntityManager()->DeleteAllOfType<Square>(); }},
		{ "All Triangles", [this]() {GetEntityManager()->DeleteAllOfType<Triangle>(); }},
		{ "All Tiles", [this]() {GetEntityManager()->DeleteAllOfType<Tile>(); }},
		{ "All Drawables", [this]() {GetEntityManager()->DeleteAllOfType<Drawable>(); }},
		{ "All TileMaps", [this]() {GetEntityManager()->DeleteAllOfType<TileMap>(); }},
			}
			);
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
		ImGui::Combo("Entity Factory", &creation.selected, creation.labels.data(), creation.labels.size());

		if (creation.selected > 0)
		{
			text = "Spawn Entity";
			if (ImGui::Button(text.c_str()))
				creation.options.at(creation.selected).action();
		}

		ImGui::Separator();
	}

	void EntitiesImGui::EntityDeleter()
	{
		ImGui::Combo("Choose Delete Form", &deletionOptions.selected, deletionOptions.labels.data(), deletionOptions.labels.size());

		if (deletionOptions.selected == 0)
		{
			ImGui::Text("Delete Entity by ID");
			ImGui::InputInt("Input Entity ID", &entityToDelete);
		}

		if (ImGui::Button("Delete"))
		{
			deletionOptions.options.at(deletionOptions.selected).action();
		}

		ImGui::Separator();
	}

	void EntitiesImGui::EntityDisplayer()
	{
		ImGui::Combo("Filter", &filters.selected, filters.labels.data(), filters.labels.size());

		ImGui::Checkbox("Display in Reverse", &showInReverseOrder);

		ImGui::Checkbox("Show Entities Materials", &showMaterials);

		ImGui::Checkbox("Show Entities Textures", &showTextures);

		filters.options.at(filters.selected).action();
	}

	void EntitiesImGui::ShowEntity(Entity& entity)
	{
		ShowEntityData(entity);

		drawableIT = GetEntityManager()->GetDrawables().find(entity.ID);

		if (drawableIT != GetEntityManager()->GetDrawables().end() && drawableIT->second)
		{
			text = "Current Layer : " + to_string(drawableIT->second->GetLayer()) + "##xx ID: " + to_string(drawableIT->first);
			ImGui::InputInt(text.c_str(), &layer);

			text = "Change Layer ##xx ID: " + to_string(drawableIT->first);
			if (ImGui::Button(text.c_str()))
				drawableIT->second->SetLayer(layer);

			if (showMaterials)
				ShowMaterial(drawableIT->first, *drawableIT->second);

			if (showTextures)
				if (Sprite* sprite = GetEntityManager()->TryGet<Sprite>(entity.ID))
					ShowTexture(*sprite);
		}

		ImGui::Separator();
	}

	void EntitiesImGui::ShowEntityData(Entity& entity)
	{
		text = "EntityID: " + to_string(entity.ID);
		ImGui::Text(text.c_str());

		changedEntityTRS = false;

		text = "ID: " + to_string(entity.ID) + ". Position. ";
		changedEntityTRS |= ImGui::DragFloat3(text.c_str(), &entity.position.x);

		text = "ID: " + to_string(entity.ID) + ". Rotation.";
		changedEntityTRS |= ImGui::DragFloat3(text.c_str(), &entity.rotation.x);

		text = "ID: " + to_string(entity.ID) + ". Scale.";
		changedEntityTRS |= ImGui::DragFloat3(text.c_str(), &entity.scale.x);

		if (changedEntityTRS)
			entity.CalculateTRS();

		text = "ID: " + to_string(entity.ID) + ". IsActive.";
		if (ImGui::Checkbox(text.c_str(), &entity.isActive))
			entity.SetIsActive(entity.isActive);
	}

	void EntitiesImGui::ShowMaterial(const unsigned int& ID, Drawable& drawable)
	{
		text = "ID: " + to_string(ID) + ". Input Material ID. ";
		ImGui::InputInt(text.c_str(), &materialID);

		text = "Set Material ##xx ID: " + to_string(ID);

		drawableIT = GetEntityManager()->GetDrawables().find(ID);

		if (ImGui::Button(text.c_str()))
			drawable.SetMaterial(materialID);

		Material* material = GetMaterialManager()->GetMaterial(drawable.GetMaterial());

		if (material != nullptr)
		{
			text = "##xx Name: " + material->GetName() + ". Program ID: " + to_string(material->GetProgram()) + "." + "ID: " + to_string(ID);

			ImGui::ColorEdit4(text.c_str(), &material->color.x);
		}
	}

	void EntitiesImGui::ShowTexture(Sprite& sprite)
	{
		text = "ID: " + to_string(sprite.GetID()) + ". Position. ";
		ImGui::InputInt(text.c_str(), &textureID);

		text = "Set Texture ##xx ID: " + to_string(sprite.GetID());

		if (ImGui::Button(text.c_str()))
			sprite.SetTexture(textureID);

		Texture* texture = GetTextureManager()->GetTexture(sprite.GetTexture());

		if (texture != nullptr)
			ImGui::Image(texture->GetTextureID(), ImVec2(texture->GetWidth() / 3, texture->GetHeight() / 3), ImVec2(0, 1), ImVec2(1, 0));
	}
}
