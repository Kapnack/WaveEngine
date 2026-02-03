#include "TextureManager.h"

#include <GL/glew.h>

TextureManager::TextureManager() : Service()
{
}

TextureManager::~TextureManager()
{
	for (unordered_map<unsigned int, Texture*>::iterator it = textures.begin(); it != textures.end(); ++it)
		delete it->second;
}

void TextureManager::Save(const unsigned int& ID, Texture* texture)
{
	textures[ID] = texture;
}

Texture* TextureManager::GetTexture(const unsigned int& ID)
{
	return textures[ID];
}

unordered_map<unsigned int, Texture*>& TextureManager::GetTextures()
{
	return textures;
}

void TextureManager::DeleteTexture(const unsigned int& ID)
{
	if (textures[ID] == nullptr)
		return;

	glDeleteTextures(textures[ID]->textureID, &textures[ID]->textureID);
	delete textures[ID];
	textures.erase(ID);
}

void TextureManager::DeleteTexture(const string& name)
{
	unordered_map<unsigned int, Texture*>::iterator it = find_if(textures.begin(), textures.end(),
		[&name](const pair<const unsigned int, Texture*>& it)
		{
			return it.second && it.second->GetName() == name;
		});

	if (it == textures.end())
		return;

	glDeleteTextures(it->second->textureID, &it->second->textureID);
	delete it->second;
	textures.erase(it);
}
