#pragma once

#include "ImGuiClass/ImGuiClassStates/ImGuiClassState.h"
#include "Material/MaterialManager.h"

class MaterialsImGui : public ImGuiClassState
{
private:

	MaterialManager* GetMaterialManager();

	bool deleteByName = false;
	char materialName[255]{};
	int materialID = 0;

public:

	MaterialsImGui();
	~MaterialsImGui();

	void Update() override;
};

