#pragma once

#include "Entity/EntityManager.h"
#include "Input/Input.h"
#include "Entity/Entity.h"

#include "Export.h"

WAVEEXPORT class Controller
{
private:

	unsigned int entityID = Entity::NULL_ENTITY;

protected:

	Input* GetInput();
	EntityManager* GetEntityManager();

public:

	WAVEEXPORT	Controller();
	WAVEEXPORT Controller(const unsigned int& entityID);
	WAVEEXPORT ~Controller();

	WAVEEXPORT virtual void Update(const float& deltaTime) = 0;

	WAVEEXPORT void SetEntityID(const unsigned int& entityID);
	WAVEEXPORT const unsigned int GetEntityID();
};

