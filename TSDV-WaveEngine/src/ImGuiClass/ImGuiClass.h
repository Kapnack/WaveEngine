#pragma once

#include "ServiceProvider/Service.h"

#include "ServiceProvider/ServiceProvider.h"
#include "Window/Window.h"
#include "Vector3.h"

#include<string>

#include <vector>

using namespace std;

class BaseGame;

struct ImGuiClassData
{
	string label;
	Vector3* vector;
	float min;
	float max;
};

class ImGuiClass : public Service
{
private:

	vector<ImGuiClassData> dataToDraw;

	Window* GetWindow();

	void Init();
	void Update();
	void Draw();
	void Unload();

	friend class BaseGame;
	friend class ServiceProvider;

public:

	void CreateVec3Editor(const string& paramName, Vector3& vector, float min, float max);

	ImGuiClass();
	~ImGuiClass();
};