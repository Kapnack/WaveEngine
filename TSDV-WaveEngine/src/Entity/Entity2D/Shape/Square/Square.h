#pragma once

#include "../Shape.h"

class EntityFactory;
class EntityManager;

WAVEEXPORT class Square : public Shape
{
private:

	WAVEEXPORT Square(const unsigned int& ID);
	WAVEEXPORT ~Square();

	friend class EntityFactory;
	friend class EntityManager;
};

