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
	this->entityID = entityID;
}

void Controller::SetEntityID(const unsigned int& entityID)
{
	this->entityID = entityID;
}

const unsigned int Controller::GetEntityID()
{
	return entityID;
}
