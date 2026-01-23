#include "TextureImporter.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <GL/glew.h>
#include <iostream>
#include <filesystem>

void TextureImporter::LoadTexture(string filePath)
{
	string absolutePath = std::filesystem::absolute(filePath).lexically_normal().string();

	int width;
	int height;
	int nrChannels;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(absolutePath.c_str(), &width, &height, &nrChannels, 0);

	GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;

	if (!data)
	{
		std::cout << "Failed to load texture: " << absolutePath << std::endl;
		return;
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	std::cout << "Loaded texture: " << absolutePath << " (" << width << "x" << height << ")" << std::endl;
}

unsigned int TextureImporter::GetLoadedTexture()
{
	return texture;
}