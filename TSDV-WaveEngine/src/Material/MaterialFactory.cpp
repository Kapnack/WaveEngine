#include "MaterialFactory.h"

#include <GL/glew.h>
#include <iostream>

#include "Material.h"
#include "FileReader/FileReader.h"

MaterialFactory::MaterialFactory()
{
	FileReader fileReader;

	string vertexShader = fileReader.ReadFile("Shaders/Shapes/basicVertexShader.shader");

	string fragmentShader = fileReader.ReadFile("Shaders/Shapes/basicFragmentShader.shader");

	CreateMaterial("basicShapeMaterial", vertexShader, fragmentShader);

	vertexShader = fileReader.ReadFile("Shaders/Sprites/basicVertexShader.shader");

	fragmentShader = fileReader.ReadFile("Shaders/Sprites/basicFragmentShader.shader");

	CreateMaterial("basicSpriteMaterial", vertexShader, fragmentShader);
}

MaterialFactory::~MaterialFactory()
{
}

MaterialManager* MaterialFactory::GetMaterialManager()
{
	return ServiceProvider::Instance().Get<MaterialManager>();
}

unsigned int MaterialFactory::CreateMaterial(const string name, const string vertexShader, const string fragmentShader)
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

	GetMaterialManager()->SaveMaterial(currentMaterialID, newMaterial);

	return currentMaterialID;
}

unsigned int MaterialFactory::CompileShader(const string& source, unsigned int type)
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
