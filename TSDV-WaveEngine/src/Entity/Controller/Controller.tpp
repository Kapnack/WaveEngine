#ifndef CONTROLLER
#define CONTROLLER

#include "Controller.h"

Controller::Controller() : Service()
{
}

Controller::~Controller()
{
}

Input* Controller::GetInput()
{
	return ServiceProvider::Instance().Get<Input>();
}

EntityManager* Controller::GetEntityManager()
{
	return ServiceProvider::Instance().Get<EntityManager>();
}

Controller::Controller(const unsigned int& entityID)
{
	entitiesIDs.push_back(entityID);
}

template<ControllerStandar... T>
void Controller::AddEntityIDs(const T&... entityIDs)
{
	(AddEntityID(entityIDs), ...);
}

template<ControllerStandar... T>
void Controller::RemoveEntityIDs(const T&... entityIDs)
{
	(RemoveEntityID(entityIDs), ...);
}

void Controller::RemoveEntityID(const unsigned int& entityID)
{
	entitiesIDs.erase(remove(entitiesIDs.begin(), entitiesIDs.end(), entityID), entitiesIDs.end());
}

const std::vector<unsigned int>& Controller::GetEntityIDs()
{
	return entitiesIDs;
}

void Controller::AddEntityID(const unsigned int& entityID)
{
	for (vector<unsigned int>::iterator it = entitiesIDs.begin(); it != entitiesIDs.end(); ++it)
		if (*it == entityID)
			return;

	entitiesIDs.push_back(entityID);
}

#endif