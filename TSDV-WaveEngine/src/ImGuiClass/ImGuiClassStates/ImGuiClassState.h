#pragma once

#include <string>

using namespace std;

class ImGuiClassState
{
protected:

	string text;

public:

	ImGuiClassState();
	~ImGuiClassState();

	virtual void Update() = 0;
};

