#pragma once

#include "ImGuiClass/ImGuiClassStates/ImGuiClassState.h"
#include "Material/MaterialManager.h"
#include "Material/MaterialFactory.h"
#include "FileReader/FileReader.h"

class MaterialsImGui : public ImGuiClassState
{
private:

	MaterialManager* GetMaterialManager();
	MaterialFactory* GetMaterialFactory();
	FileReader* GetFileReader();

	bool deleteByName = false;

	bool createMaterial = false;
	bool importMaterial = false;

	bool addAbsoluteToVertexPath = false;
	bool addAbsoluteToFragmentPath = false;

	string newMaterialName;
	string vertexShader;
	string fragmentShader;

	string vertexShaderPath;
	string fragmentShaderPath;

	char materialName[255]{};
	int materialID = 0;

	const ImVec2 textBoxSize = ImVec2(500, 120);

public:

	MaterialsImGui();
	~MaterialsImGui();

	void Update() override;
};

