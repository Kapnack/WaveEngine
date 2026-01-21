#include "MaterialManager.h"

#include <GL/glew.h>
#include <algorithm>

#include "FileReader/FileReader.h"

MaterialManager::MaterialManager() : Service()
{

	Init();
}

MaterialManager::~MaterialManager()
{
	for (unordered_map<unsigned int, Material*>::iterator it = materials.begin(); it != materials.end(); ++it)
		delete it->second;

	materials.clear();
}

void MaterialManager::Init()
{
	FileReader fileReader;

	string vertexShader = fileReader.ReadFile("Shaders/Shapes/basicVertexShader.shader");

	string fragmentShader = fileReader.ReadFile("Shaders/Shapes/basicFragmentShader.shader");

	CreateMaterial("basicShapeMaterial", vertexShader, fragmentShader);

	vertexShader = fileReader.ReadFile("Shaders/Sprites/basicVertexShader.shader");

	fragmentShader = fileReader.ReadFile("Shaders/Sprites/basicFragmentShader.shader");

	CreateMaterial("basicSpriteMaterial", vertexShader, fragmentShader);
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

unsigned int MaterialManager::CreateMaterial(const string name, const string vertexShader, const string fragmentShader)
{
	unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
	unsigned int fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

	unsigned int program = glCreateProgram();

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	Material* newMaterial = new Material();

	newMaterial->SetProgram(program);

	newMaterial->SetUModel(glGetUniformLocation(program, "uModel"));

	newMaterial->SetUView(glGetUniformLocation(program, "uView"));

	newMaterial->SetUProj(glGetUniformLocation(program, "uProj"));

	newMaterial->SetOurTexture(glGetUniformLocation(program, "ourTexture"));

	newMaterial->SetName(name);

	++currentMaterialID;

	SaveMaterial(currentMaterialID, newMaterial);

	return currentMaterialID;
}

unsigned int MaterialManager::GetMaterial(const string name)
{
	unordered_map<unsigned int, Material*>::iterator it = find_if(materials.begin(), materials.end(),
		[&name](const auto& pair)
		{
			return pair.second && pair.second->GetName() == name;
		});

	if (it == materials.end())
		return 0;

	return it->first;
}

void MaterialManager::SaveMaterial(const unsigned int id, Material* material)
{
	materials[id] = material;
}

Material& MaterialManager::GetMaterial(const unsigned int id)
{
	return *materials[id];
}

void MaterialManager::DeleteMaterial(const string name)
{
	unordered_map<unsigned int, Material*>::iterator it = find_if(materials.begin(), materials.end(),
		[&name](const auto& pair)
		{
			return pair.second && pair.second->GetName() == name;
		});

	if (it == materials.end())
		return;

	OnDeleteMaterial(*it->second);

	delete it->second;
	materials.erase(it);
}

void MaterialManager::DeleteMaterial(const unsigned int id)
{
	unordered_map<unsigned, Material*>::iterator it = materials.find(id);

	if (it == materials.end())
		return;

	OnDeleteMaterial(*it->second);

	delete it->second;
	materials.erase(it);
}

void MaterialManager::AddListener(Entity* entity)
{
	listeners.push_back(entity);
}

void MaterialManager::OnDeleteMaterial(Material& material)
{
	for (Entity* entity : listeners)
		if (entity->GetMaterial() == material.GetProgram())
			entity->SetMaterial(Material::NULL_MATERIAL);
}

void MaterialManager::RemoveListener(Entity* entity)
{
	for (vector<Entity*>::iterator it = listeners.begin(); it != listeners.end(); ++it)
		if (*it == entity)
		{
			listeners.erase(it);
			break;
		}
}
