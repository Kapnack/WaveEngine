#pragma once

#include "Export.h"
#include <string>

using namespace std;

class TextureImporter final
{
private:

	unsigned int texture;

public:

	WAVEEXPORT void LoadTexture(string filePath);
	WAVEEXPORT unsigned int GetLoadedTexture();
};