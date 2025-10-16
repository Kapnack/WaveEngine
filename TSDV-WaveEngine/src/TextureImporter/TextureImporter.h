#pragma once

#include "Export.h"
#include <string>

class TextureImporter
{
private:

	unsigned int texture;

public:

	WAVEEXPORT void LoadTexture(std::string filePath);
	WAVEEXPORT unsigned int GetLoadedTexture();
};