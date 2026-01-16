#pragma once

#include "Entity/Entity2D/Entity2D.h"

WAVEEXPORT class Shape : public Entity2D
{
protected:

public:

	WAVEEXPORT Shape();
	WAVEEXPORT virtual ~Shape();

	WAVEEXPORT void Draw() override;
};

