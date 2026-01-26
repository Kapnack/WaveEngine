#pragma once

#include "../ImGuiClassState.h"
#include "TextureImporter/TextureManager.h"
#include "TextureImporter/TextureImporter.h"
#include "TextureImporter/Texture.h"

#include <string>

using namespace std;

class TexturesImGui : public ImGuiClassState
{
private:

	TextureManager* GetTextureManager();
	TextureImporter* GetTextureImporter();

	string fileTexurePath;
	string textureName;

	bool withAbsolutePath = false;
	bool deleteByName = false;
	int textureID = 0;

public:

	TexturesImGui();
	~TexturesImGui();

	void Update() override;
};

