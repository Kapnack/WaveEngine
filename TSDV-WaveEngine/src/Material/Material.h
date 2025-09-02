#pragma once

#include <iostream>
#include <string>

using namespace std;

class Material
{
private:

	unsigned int program;

	unsigned int CompileShader(const string& source, unsigned int type);

public:

	Material();
	~Material();

	void CreateShader(const string& vertexShader, const string& fragmenteShader);

	unsigned int GetProgram();

	void Unload();
};

