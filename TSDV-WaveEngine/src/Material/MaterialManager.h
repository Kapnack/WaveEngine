#pragma once

#include <map>

#include "Export.h"
#include "Material/Material.h"

using namespace std;

WAVEEXPORT class MaterialManager
{
private:

	static map<string, Material*> materials;
	static unsigned int CompileShader(const string& source, unsigned int type);
	static void SaveMaterial(const string name, Material* material);

public:

	MaterialManager();
	~MaterialManager();

	WAVEEXPORT static Material& CreateMaterial(const string name, const string vertexShader, const string fragmentShader);

	WAVEEXPORT static Material& GetMaterial(string name);

	WAVEEXPORT static void DeleteMaterial(const string name);

	WAVEEXPORT static void DeleteMaterial(Material* material);

};

