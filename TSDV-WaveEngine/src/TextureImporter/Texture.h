#pragma once

#include "Vector2.h"
#include "Export.h"

#include <string>

class TextureManager;
class TextureImporter;

using namespace std;

class Texture final
{
private:

	string name;
	unsigned int ID = 0;
	unsigned int textureID = 0;

	int width;
	int height;

	Texture(const unsigned int& ID, const unsigned int& textureID, const int& width, const int& height);
	~Texture();

	friend class TextureManager;
	friend class TextureImporter;

public:

	static const int NULL_TEXTURE = 0;

	int GetWidth();
	int GetHeight();
	string GetName();

	Vector2 GetRes();

	unsigned int GetTextureID();
	unsigned int GetID();
};