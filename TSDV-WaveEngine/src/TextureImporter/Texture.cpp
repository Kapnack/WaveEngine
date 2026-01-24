#include "Texture.h"

Texture::Texture(const unsigned int& ID, const unsigned int& textureID, const int& width, const int& height)
{
	this->ID = ID;
	this->textureID = textureID;
	this->width = width;
	this->height = height;
}

Texture::~Texture()
{
}

int Texture::GetWidth()
{
	return width;
}

int Texture::GetHeight()
{
	return height;
}

Vector2 Texture::GetRes()
{
	return Vector2(width, height);
}

unsigned int Texture::GetTextureID()
{
	return textureID;
}

unsigned int Texture::GetID()
{
	return ID;
}
