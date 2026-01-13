#include "MaterialManager.h"
#include <GL/glew.h>

std::map<std::string, Material*> MaterialManager::materials;

MaterialManager::MaterialManager()
{
}

MaterialManager::~MaterialManager()
{
	for (map<string, Material*>::iterator it = materials.begin(); it != materials.end(); ++it)
	{
		delete it->second;
	}

	materials.clear();
}

unsigned int MaterialManager::CompileShader(const string& source, unsigned int type)
{
	unsigned int id = glCreateShader(type);

	const char* src = source.c_str();

	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		cout << message << "\n\n";

		glDeleteShader(id);

		return 0;
	}

	return id;
}

Material& MaterialManager::CreateMaterial(const string name, const string vertexShader, const string fragmentShader)
{
	Material* newMaterial = new Material();

	unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
	unsigned int fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

	unsigned int program = glCreateProgram();

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	newMaterial->SetProgram(program);

	newMaterial->SetUModel(glGetUniformLocation(program, "uModel"));

	newMaterial->SetUView(glGetUniformLocation(program, "uView"));

	newMaterial->SetUProj(glGetUniformLocation(program, "uProj"));

	newMaterial->SetOurTexture(glGetUniformLocation(program, "ourTexture"));

	newMaterial->SetName(name);

	MaterialManager::SaveMaterial(name, newMaterial);

	return *newMaterial;
}

void MaterialManager::SaveMaterial(const string name, Material* material)
{
	string nameToSearch = name;
	int numberToAdd = 1;

	while (materials.find(nameToSearch) != materials.end())
	{
		nameToSearch = name + "_(" + to_string(numberToAdd) + ")";
		++numberToAdd;
	}

	materials[nameToSearch] = material;
	material->SetName(nameToSearch);
}

Material& MaterialManager::GetMaterial(string name)
{
	return *materials[name];
}

void MaterialManager::DeleteMaterial(const string name)
{
	delete materials[name];
	materials.erase(name);
}

void MaterialManager::DeleteMaterial(Material* material)
{
	for (map<string, Material*>::iterator it = materials.begin(); it != materials.end(); ++it)
	{
		if (it->second == material)
			it = materials.erase(it);
	}

	delete material;
}
