#pragma once

#include "Entity/Entity2D/Entity2D.h"

WAVEEXPORT class Shape : public Entity2D
{
protected:

	WAVEEXPORT void Draw() override;

public:

	WAVEEXPORT Shape(const unsigned int& ID);
	WAVEEXPORT virtual ~Shape();

};

