#include "Material.h"

#include <GL/glew.h>

#define GLM_FORCE_ALIGNED_GENTYPES
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>

#include "MaterialManager.h"

using namespace std;

const unsigned int Material::NULL_MATERIAL = 0;

Material::Material(const unsigned int& ID)
{
	this->ID = ID;
}

Material::~Material()
{
	Unload();
}

const string Material::GetName()
{
	return name;
}

Vector4 Material::GetColor() const
{
	return color;
}

unsigned int Material::GetID() const
{
	return ID;
}

unsigned int Material::GetProgram() const
{
	return program;
}

unsigned int Material::GetUColor() const
{
	return uColor;
}

unsigned int Material::GetUModel() const
{
	return uModel;
}

unsigned int Material::GetUView() const
{
	return uView;
}

unsigned int Material::GetUProj() const
{
	return uProj;
}

void Material::SetName(const string_view name)
{
	this->name = name;
}

void Material::SetProgram(const unsigned int& program)
{
	this->program = program;
}

void Material::SetUColor(const unsigned int& color)
{
	this->uColor = color;
}

void Material::SetUModel(const unsigned int& model)
{
	uModel = model;
}

void Material::SetUView(const unsigned int& view)
{
	uView = view;
}

void Material::SetUProj(const unsigned int& projection)
{
	uProj = projection;
}

void Material::SetOurTexture(const unsigned int& ourTexture)
{
	this->ourTexture = ourTexture;
}

unsigned int Material::GetOurTexture() const
{
	return ourTexture;
}

void Material::SetColor(const Vector4& color)
{
	this->color = color;
}

void Material::Bind() const
{
	glUseProgram(program);
}

void Material::UnBind() const
{
	glUseProgram(0);
}

void Material::Unload() const
{
	glDeleteProgram(program);
}
