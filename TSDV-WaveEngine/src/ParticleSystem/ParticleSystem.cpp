#include "ParticleSystem.h"

#include "Random/Random.h"

namespace WaveEngine
{
	ParticleSystem::ParticleSystem()
	{
		particlePool.resize(maxPoolIndex);

		for (vector<unsigned int>::iterator it = particlePool.begin(); it != particlePool.end(); ++it)
		{
			*it = GetEntityFactory()->Create<Particle>();

			GetEntityManager()->Get(*it)->SetIsActive(false);
		}
	}

	ParticleSystem::~ParticleSystem()
	{
		for (vector<unsigned int>::iterator it = particlePool.begin(); it != particlePool.end(); ++it)
			GetEntityManager()->DeleteEntity(*it);
	}

	EntityManager* ParticleSystem::GetEntityManager()
	{
		return ServiceProvider::Instance().Get<EntityManager>();
	}

	EntityFactory* ParticleSystem::GetEntityFactory()
	{
		return ServiceProvider::Instance().Get<EntityFactory>();
	}

	void ParticleSystem::Update(const float& deltaTime)
	{
		for (vector<unsigned int>::iterator it = particlePool.begin(); it != particlePool.end(); ++it)
		{
			Particle* particle = GetEntityManager()->TryGet<Particle>(*it);

			if (!particle)
				continue;

			if (!particle->GetIsActive())
				continue;

			if (particle->lifeTimeRemaining <= 0.0f)
			{
				particle->SetIsActive(false);
				continue;
			}

			particle->lifeTimeRemaining -= deltaTime;

			particle->Translate(particle->velocity * deltaTime);
			particle->Rotate(Vector3::Up() * (0.01f * deltaTime));
		}
	}

	void ParticleSystem::Emit(const ParticleProps& particleProps)
	{
		Particle* particle = GetEntityManager()->Get<Particle>(particlePool[poolIndex]);

		if (!particle)
			return;

		particle->SetIsActive(true);
		particle->SetPosition(particleProps.position);
		particle->SetRotation(Vector3::Up() * particleProps.rotation); //* Random::Float());
				
		particle->velocity = particleProps.velocity;
		particle->velocity.x += particleProps.velocityVariation.x; //* (Random::Float() - 0.5f);
		particle->velocity.y += particleProps.velocityVariation.y; //* (Random::Float() - 0.5f);
			
		particle->SetColor(particleProps.beginColor);
		particle->endColor = particleProps.endColor;
				
		particle->lifeTime = particleProps.lifeTime;
		particle->lifeTimeRemaining = particleProps.lifeTime;
				
		particle->SetScale(Vector3::One() * particleProps.beginingSize);
		particle->endSize = particleProps.endSize;

		poolIndex = --poolIndex % particlePool.size();
	}
}
