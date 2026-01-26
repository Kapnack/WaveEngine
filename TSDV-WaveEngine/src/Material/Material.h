#pragma once

#include <iostream>
#include <string>

#include "Vector4.h"

class MaterialManager;
class MaterialFactory;
class EntitiesImGui;
class MaterialsImGui;

using namespace std;

class Material final
{
private:

	string name;

	Vector4 color = Vector4(1, 1, 1, 1);

	unsigned int ID = 0;

	unsigned int program = 0;

	int uColor = 0;
	int uModel = 0;
	int uView = 0;
	int uProj = 0;
	int ourTexture = 0;

	Material(const unsigned int& ID);
	~Material();

	void SetName(const string& name);
	void SetProgram(const unsigned int& program);
	void SetUColor(const unsigned int& color);
	void SetUModel(const unsigned int& model);
	void SetUView(const unsigned int& view);
	void SetUProj(const unsigned int& projection);
	void SetOurTexture(const unsigned int& ourTexture);
	void Unload();

	friend class MaterialManager;
	friend class MaterialFactory;
	friend class EntitiesImGui;
	friend class MaterialsImGui;

public:

	const static unsigned int NULL_MATERIAL;

	const string GetName();

	Vector4 GetColor();
	unsigned int GetID();
	unsigned int GetProgram();
	unsigned int GetUColor();
	unsigned int GetUModel();
	unsigned int GetUView();
	unsigned int GetUProj();

	unsigned int GetOurTexture();

	void SetColor(const Vector4& color);

	void Bind();
	void UnBind();
};

