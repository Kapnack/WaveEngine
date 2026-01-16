#pragma once

#include <iostream>
#include <string>

using namespace std;

class Material
{
private:

	string name;

	unsigned int program = 0;

	int uModel = 0;
	int uView = 0;
	int uProj = 0;
	int ourTexture = 0;

public:

	Material();
	~Material();

	const string GetName();
	unsigned int GetProgram();
	unsigned int GetUModel();
	unsigned int GetUView();
	unsigned int GetUProj();

	void SetName(const string name);
	void SetProgram(unsigned int program);
	void SetUModel(unsigned int model);
	void SetUView(unsigned int view);
	void SetUProj(unsigned int projection);
	void SetOurTexture(unsigned int ourTexture);

	unsigned int GetOurTexture();

	void Bind();
	void UnBind();

	void Unload();
};

