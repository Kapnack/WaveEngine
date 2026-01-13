#include "Material.h"

#include <GL/glew.h>

#define GLM_FORCE_ALIGNED_GENTYPES
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>

#include "MaterialManager.h"

using namespace std;

Material::Material()
{
}

Material::~Material()
{
	Unload();
}

const string Material::GetName()
{
	return name;
}

unsigned int Material::GetProgram()
{
	return program;
}

unsigned int Material::GetUModel()
{
	return uModel;
}

unsigned int Material::GetUView()
{
	return uView;
}

unsigned int Material::GetUProj()
{
	return uProj;
}

void Material::SetName(const string name)
{
	this->name = name;
}

void Material::SetProgram(unsigned int program)
{
	this->program = program;
}

void Material::SetUModel(unsigned int model)
{
	uModel = model;
}

void Material::SetUView(unsigned int view)
{
	uView = view;
}

void Material::SetUProj(unsigned int projection)
{
	uProj = projection;
}

void Material::SetOurTexture(unsigned int ourTexture)
{
	this->ourTexture = ourTexture;
}

unsigned int Material::GetOurTexture()
{
	return ourTexture;
}

void Material::Bind()
{
	glUseProgram(program);
}

void Material::UnBind()
{
	glUseProgram(0);
}

void Material::Unload()
{
	glDeleteShader(program);
}
