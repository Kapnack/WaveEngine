#pragma once

#include "ImGuiClass/ImGuiClassStates/ImGuiClassState.h"
#include "Material/MaterialManager.h"
#include "Material/MaterialFactory.h"

class MaterialsImGui : public ImGuiClassState
{
private:

	MaterialManager* GetMaterialManager();
	MaterialFactory* GetMaterialFactory();

	bool deleteByName = false;

	bool createMaterial = false;

	string newMaterialName;
	string vertexShader;
	string fragmentShader;
	char materialName[255]{};
	int materialID = 0;

	const ImVec2 textBoxSize = ImVec2(500, 120);

public:

	MaterialsImGui();
	~MaterialsImGui();

	void Update() override;
};

