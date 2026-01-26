#pragma once

#include "../ImGuiClassState.h"
#include "TextureImporter/TextureManager.h"
#include "TextureImporter/TextureImporter.h"
#include "TextureImporter/Texture.h"

class TexturesImGui : public ImGuiClassState
{
private:

	TextureManager* GetTextureManager();
	TextureImporter* GetTextureImporter();

	char buf[255]{' '};

	bool withAbsolutePath = false;

public:

	TexturesImGui();
	~TexturesImGui();

	void Update() override;
};

