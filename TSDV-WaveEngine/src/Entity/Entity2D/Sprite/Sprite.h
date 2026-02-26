#pragma once

#include "Entity/Entity2D/Entity2D.h"
#include "Entity/Drawable/Drawable.h"
#include "Entity/Entity2D/Animation/Animation.h"

class EntityFactory;
class EntitiesImGui;

class Sprite : public Entity2D, public Drawable
{
private:

	unsigned int textureID = 0;
	Animation* animation = nullptr;

	void Init(const Vector4& color);

	friend class EntityFactory;
	friend class EntitiesImGui;

protected:

	WAVEEXPORT void Draw() override;

public:

	WAVEEXPORT Sprite(const unsigned int& ID);
	WAVEEXPORT virtual ~Sprite();

	WAVEEXPORT void SetUVCordinates(const Vector2& cord1, const Vector2& cord2);
	WAVEEXPORT void SetAnimation(Animation* animation);
	WAVEEXPORT void Update();
	WAVEEXPORT void SetTexture(const unsigned int& textureID);
	WAVEEXPORT Animation* GetAnimation();
	WAVEEXPORT unsigned int GetTexture();
};

