#pragma once

#include "ServiceProvider/Service.h"

#include <unordered_map>
#include <vector>

#include "Export.h"
#include "Entity/Entity.h"
#include "Material/Material.h"

class Renderer;

using namespace std;

WAVEEXPORT class MaterialManager : public Service
{
private:

	unsigned int currentMaterialID = Material::NULL_MATERIAL;

	unordered_map<unsigned int, Material*> materials;
	unsigned int CompileShader(const string& source, unsigned int type);
	void SaveMaterial(const unsigned int id, Material* material);

	vector<Entity*> listeners;

	Material& GetMaterial(const unsigned int id);

	friend class Renderer;

public:

	MaterialManager();
	~MaterialManager();

	void Init();

	WAVEEXPORT unsigned int CreateMaterial(const string name, const string vertexShader, const string fragmentShader);

	WAVEEXPORT unsigned int GetMaterial(const string name);

	WAVEEXPORT void DeleteMaterial(const string name);

	WAVEEXPORT void DeleteMaterial(const unsigned int id);

	void AddListener(Entity* entity);

	void OnDeleteMaterial(Material& material);

	void RemoveListener(Entity* entity);

};

