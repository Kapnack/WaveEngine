#pragma once

#include "ServiceProvider/Service.h"

#include "ServiceProvider/ServiceProvider.h"
#include "Window/Window.h"
#include "Vector3.h"
#include "Vector4.h"

#include <string>

#include <vector>

using namespace std;

class BaseGame;

struct ImGuiClassData
{
	unsigned int id;
	Vector3* position = nullptr;
	Vector3* rotation = nullptr;
	unsigned int* textureID = nullptr;
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

	ImGuiClass();
	~ImGuiClass();

	friend class BaseGame;
	friend class ServiceProvider;

public:

	WAVEEXPORT void CreateEditor(const unsigned int& ID, Vector3& position, Vector3& rotation, unsigned int* textureID = nullptr);
};