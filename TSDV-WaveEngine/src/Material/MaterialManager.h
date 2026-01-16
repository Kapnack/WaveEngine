#pragma once

#include "ServiceProvider/Service.h"

#include <unordered_map>
#include <vector>

#include "Export.h"
#include "Entity/Entity.h"
#include "Material/Material.h"

using namespace std;

WAVEEXPORT class MaterialManager : public Service
{
private:

	unordered_map<string, Material*> materials;
	unsigned int CompileShader(const string& source, unsigned int type);
	void SaveMaterial(const string name, Material* material);

	vector<Entity*> listeners;

public:

	MaterialManager();
	~MaterialManager();

	void Init();

	WAVEEXPORT  Material& CreateMaterial(const string name, const string vertexShader, const string fragmentShader);

	WAVEEXPORT  Material& GetMaterial(string name);

	WAVEEXPORT  void DeleteMaterial(const string name);

	WAVEEXPORT  void DeleteMaterial(Material* material);

	void AddListener(Entity* entity);

	void OnDeleteMaterial(Material* material);

	void RemoveListener(Entity* entity);

};

