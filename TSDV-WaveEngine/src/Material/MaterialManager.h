#pragma once

#include "ServiceProvider/Service.h"

#include <unordered_map>
#include <vector>

#include "Export.h"
#include "Entity/Entity.h"
#include "Material/Material.h"

class Renderer;
class MaterialFactory;

using namespace std;

WAVEEXPORT class MaterialManager : public Service
{
private:

	unsigned int currentMaterialID = Material::NULL_MATERIAL;

	unordered_map<unsigned int, Material*> materials;

	void SaveMaterial(const unsigned int id, Material* material);

	vector<Entity*> listeners;

	Material& GetMaterial(const unsigned int id);

	friend class Renderer;
	friend class MaterialFactory;

public:

	MaterialManager();
	~MaterialManager();

	WAVEEXPORT unsigned int GetMaterial(const string name);

	WAVEEXPORT void DeleteMaterial(const string name);

	WAVEEXPORT void DeleteMaterial(const unsigned int id);

	void AddListener(Entity* entity);

	void OnDeleteMaterial(Material& material);

	void RemoveListener(Entity* entity);

};

