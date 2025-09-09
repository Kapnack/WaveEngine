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

public:

	Material();
	~Material();

	void CreateShader(const string& vertexShader, const string& fragmenteShader);

	void CreateShader(const string& filePath, unsigned int type);

	unsigned int GetProgram();

	void Bind();
	void UnBind();

	void Unload();
};

