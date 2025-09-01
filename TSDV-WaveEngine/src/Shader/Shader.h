#pragma once

#include <iostream>
#include <string>

using namespace std;

class Shader
{
private:


public:

	Shader();
	~Shader();

	unsigned int CompileShader(const string& source, unsigned int type);
	unsigned int CreateShader(const string& vertexShader, const string& fragmenteShader);
};

