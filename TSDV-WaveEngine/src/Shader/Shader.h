#pragma once

#include <iostream>
#include <string>

using namespace std;

class Shader
{
private:

	unsigned int program;

	unsigned int CompileShader(const string& source, unsigned int type);

public:

	Shader();
	~Shader();

	void CreateShader(const string& vertexShader, const string& fragmenteShader);

	unsigned int GetProgram();

	void Unload();
};

