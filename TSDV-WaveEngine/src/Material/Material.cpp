#include "Material.h"

#include <GL/glew.h>

#include <fstream>

using namespace std;

Material::Material()
{
}

Material::~Material()
{
	Unload();
}

unsigned int Material::CompileShader(const string& source, unsigned int type)
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

string Material::FileReader(const string& filePath)
{
	ifstream inputFile;
	string script;

	try
	{
		inputFile.open(filePath.c_str(), ios::in);

		if (!inputFile.is_open())
			throw runtime_error("Shader Path: " + filePath + " couldn't be openned.\n\n");

		while (!inputFile.eof())
		{
			string newText;
			inputFile >> newText;

			script += newText + " ";
		}
	}
	catch (runtime_error& error)
	{
		cout << error.what();
	}
	catch (...)
	{
		cout << "An unexpected error happened while working with Shader file: " << filePath << "\n\n";
	}

	if (inputFile.is_open())
		inputFile.close();

	return script;
}

void Material::CreateShader(const string& vertexShader, const string& fragmenteShader)
{
	if (program != 0)
		Unload();

	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
	unsigned int fs = CompileShader(fragmenteShader, GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	this->program = program;
}

void Material::CreateShader(const string& filePath, unsigned int type)
{
	if (program != 0)
		Unload();

	string script = FileReader(filePath);

	unsigned int program = glCreateProgram();
	unsigned int shader = CompileShader(script, type);

	glAttachShader(program, shader);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(shader);

	this->program = program;
}

unsigned int Material::GetProgram()
{
	return program;
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
