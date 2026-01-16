#include "MaterialManager.h"

#include <GL/glew.h>

#include "FileReader/FileReader.h"

MaterialManager::MaterialManager() : Service()
{
}

MaterialManager::~MaterialManager()
{
	for (unordered_map<string, Material*>::iterator it = materials.begin(); it != materials.end(); ++it)
		delete it->second;

	materials.clear();
}

void MaterialManager::Init()
{
	string vertexShader = FileReader::ReadFile("Shaders/Shapes/basicVertexShader.shader");

	string fragmentShader = FileReader::ReadFile("Shaders/Shapes/basicFragmentShader.shader");

	CreateMaterial("basicShapeMaterial", vertexShader, fragmentShader);

	vertexShader = FileReader::ReadFile("Shaders/Sprites/basicVertexShader.shader");

	fragmentShader = FileReader::ReadFile("Shaders/Sprites/basicFragmentShader.shader");

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

	SaveMaterial(name, newMaterial);

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
	unordered_map<string, Material*>::iterator it = materials.find(name);

	if (it == materials.end())
		return;

	OnDeleteMaterial(it->second);

	delete it->second;
	materials.erase(it);
}

void MaterialManager::DeleteMaterial(Material* material)
{
	unordered_map<string, Material*>::iterator it = materials.find(material->GetName());

	if (it == materials.end())
		return;

	OnDeleteMaterial(it->second);

	delete it->second;
	materials.erase(it);
}

void MaterialManager::AddListener(Entity* entity)
{
	listeners.push_back(entity);
}

void MaterialManager::OnDeleteMaterial(Material* material)
{
	for (Entity* entity : listeners)
		if (&entity->GetMaterial() == material)
			entity->SetMaterial(nullptr);
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
