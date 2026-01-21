#pragma once

#include <iostream>
#include <string>

class MaterialManager;
class MaterialFactory;

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

	Material();
	~Material();

	void SetName(const string name);
	void SetProgram(const unsigned int program);
	void SetUModel(const unsigned int model);
	void SetUView(const unsigned int view);
	void SetUProj(const unsigned int projection);
	void SetOurTexture(const unsigned int ourTexture);
	void Unload();

	friend class MaterialManager;
	friend class MaterialFactory;

public:

	const static unsigned int NULL_MATERIAL;

	const string GetName();
	unsigned int GetProgram();
	unsigned int GetUModel();
	unsigned int GetUView();
	unsigned int GetUProj();

	unsigned int GetOurTexture();

	void Bind();
	void UnBind();
};

