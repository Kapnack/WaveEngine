#pragma once

#include "BaseGame/BaseGame.h"

#include "Entity/Controller/EntityController/EntityController.h"

class Game : public BaseGame
{
private:

	EntityController* entityController;

protected:

	void Init(int width, int height) override;
	void Update() override;
	void Draw() override;
	void Unload() override;

public:

	Game(int width, int height);
	~Game();
};

