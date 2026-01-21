#pragma once

#include "ServiceProvider/Service.h"
#include "Material/MaterialManager.h"

#include <string>

using namespace std;

class MaterialFactory final : public Service
{
private:

	unsigned int currentMaterialID = Material::NULL_MATERIAL;

	MaterialManager* GetMaterialManager();

	unsigned int CompileShader(const string& source, const unsigned int type);

public:

	MaterialFactory();
	~MaterialFactory();

	unsigned int CreateMaterial(const string name, const string vertexShader, const string fragmentShader);
};

