#pragma once

#include "Entity/Controller/Controller.h"
#include "Entity/Entity.h"

#include "Export.h"

WAVEEXPORT class EntityController : public Controller
{
private:

public:

	WAVEEXPORT EntityController();
	WAVEEXPORT EntityController(const unsigned int entityID);
	WAVEEXPORT ~EntityController();

	WAVEEXPORT void Update(const float& deltaTime) override;

};

