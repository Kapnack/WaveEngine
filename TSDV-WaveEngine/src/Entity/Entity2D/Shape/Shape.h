#pragma once

#include "Entity/Entity2D/Entity2D.h"

class Shape : public Entity2D
{
protected:

	vector<float> vertex;
	unsigned int type;

	//virtual void createVertex() = 0;

public:

	Shape();
	~Shape();

	void Draw() override;
};

