#ifndef CONTROLLER
#define CONTROLLER

#include "Controller.h"

Controller::Controller()
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
void Controller::AddEntityID(const T&... entityIDs)
{
	(entitiesIDs.push_back(entityIDs), ...);
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

#endif