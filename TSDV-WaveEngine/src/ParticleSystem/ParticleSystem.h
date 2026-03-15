#pragma once

#include <WaveMath/Vector2/Vector2.h>
#include <WaveMath/Vector4/Vector4.h>
#include <Entity/Entity2D/Entity2D.h>
#include <Entity/Entity2D/Shape/Square/Square.h>
#include <Entity/EntityManager.h>
#include <Entity/EntityFactory.h>

#include <vector>

using namespace std;

namespace WaveEngine
{
	struct ParticleProps
	{
		Vector2 position;
		Vector2 velocity{ 1.0f,1.0f };
		Vector2 velocityVariation = velocity;
		Vector4 beginColor = { 1.0f, 0.5f, 1.0f, 1.0f };
		Vector4 endColor;
		float beginingSize = 10.0f;
		float endSize;
		float sizeVariation;
		float rotation = 0.0f;
		float lifeTime = 1.0f;

		ParticleProps()
		{

		}

	};

	class Particle : public Square
	{
	public:

		Particle(const unsigned int& ID) : Square(ID)
		{
		}

		~Particle()
		{
		}

		Vector2 velocity;
		Vector4 endColor;
		float endSize;
		float lifeTime = 1.0f;
		float lifeTimeRemaining = 0.0f;
	};

	class ParticleSystem
	{
	private:

		vector<unsigned int> particlePool;
		int maxPoolIndex = 999;
		int poolIndex = 0;

		EntityManager* GetEntityManager();
		EntityFactory* GetEntityFactory();

	public:

		ParticleSystem();
		~ParticleSystem();

		void Update(const float& deltaTime);
		void Emit(const ParticleProps& particleProps);
	};
}

