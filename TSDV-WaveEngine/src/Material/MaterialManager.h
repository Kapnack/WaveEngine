#pragma once

#include "ServiceProvider/Service.h"

#include <unordered_map>
#include <vector>

#include "Export.h"
#include "Entity/Drawable/Drawable.h"
#include "Material/Material.h"
#include "ServiceProvider/ServiceProvider.h"

class Renderer;
class MaterialFactory;
class EntityFactory;
class EntityManager;
class BaseGame;
class EntitiesImGui;
class MaterialsImGui;

using namespace std;

WAVEEXPORT class MaterialManager final : public Service
{
private:

	unsigned int currentMaterialID = Material::NULL_MATERIAL;

	unordered_map<unsigned int, Material*> materials;

	void SaveMaterial(const unsigned int id, Material* material);

	vector<Drawable*> listeners;

	Material* GetMaterial(const unsigned int id);

	unordered_map<unsigned int, Material*>& GetMaterials();

	friend class Renderer;
	friend class MaterialFactory;
	friend class EntityFactory;
	friend class EntityManager;
	friend class BaseGame;
	friend class ServiceProvider;
	friend class EntitiesImGui;
	friend class MaterialsImGui;

	void OnDeleteMaterial(Material& material);

	MaterialManager();
	~MaterialManager();

public:

	WAVEEXPORT unsigned int GetMaterial(const string name);

	WAVEEXPORT void DeleteMaterial(const string name);

	WAVEEXPORT void DeleteMaterial(const unsigned int id);

	WAVEEXPORT void AddListener(Drawable* entity);

	WAVEEXPORT void RemoveListener(Drawable* entity);
};

