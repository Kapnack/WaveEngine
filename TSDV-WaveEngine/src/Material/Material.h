#pragma once

#include <iostream>
#include <string>

using namespace std;

class Material
{
private:

	unsigned int program = 0;

	unsigned int CompileShader(const string& source, unsigned int type);

	string FileReader(const string& filePath);

	int uModel = 0;
	int uView = 0;
	int uProj = 0;

public:

	Material();
	~Material();

	void CreateShader(const string& vertexShader, const string& fragmenteShader);

	void CreateShader(const string& filePath, unsigned int type);

	unsigned int GetProgram();
	unsigned int GetUModel();
	unsigned int GetUView();
	unsigned int GetUProj();

	void Bind();
	void UnBind();

	void Unload();
};

