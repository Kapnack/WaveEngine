#pragma once

#include "ServiceProvider/Service.h"
#include "ServiceProvider/ServiceProvider.h"

#include "TextureImporter/Texture.h"

#include <unordered_map>
#include "Export.h"

class TextureImporter;
class BaseGame;
class ImGuiClass;
class TileMap;

using namespace std;

WAVEEXPORT class TextureManager final : public Service
{
private:

	unordered_map<unsigned int, Texture*> textures;

	TextureManager();
	~TextureManager();

	void Save(const unsigned int& ID, Texture* texture);

	Texture* GetTexture(const unsigned int& ID);

	friend class BaseGame;
	friend class TextureImporter;
	friend class ServiceProvider;
	friend class ImGuiClass;
	friend class TileMap;

public:

	WAVEEXPORT void DeleteTexture(const unsigned int& ID);
};