#pragma once

#include "../lib/ImGui/imgui.h"
#include <string>

using namespace std;

class ImGuiClassState
{
protected:

	string text;

	static int ResizeCallback(ImGuiInputTextCallbackData* data);

public:

	ImGuiClassState();
	~ImGuiClassState();

	virtual void Update() = 0;
};

