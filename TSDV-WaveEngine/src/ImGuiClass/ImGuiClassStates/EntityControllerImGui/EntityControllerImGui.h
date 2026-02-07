#pragma once

#include "../ImGuiClassState.h"
#include "Entity/Controller/EntityController/EntityController.h"

class EntityControllerImGui : public ImGuiClassState
{
private:

	EntityController* GetEntityController();

	int entityToAdd = 0;
	int entityToRemove = 0;

public:

	void Update() override;
};

