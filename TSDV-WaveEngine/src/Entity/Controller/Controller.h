#pragma once

#include "Entity/EntityManager.h"
#include "Input/Input.h"
#include "Entity/Entity.h"

#include "Export.h"

#include <concepts>

using namespace std;

template<typename T>
concept ControllerStandar = is_same_v<T, unsigned int> || is_integral_v<T>;

class Controller
{
protected:

	vector<unsigned int> entitiesIDs;

	inline Input* GetInput();
	inline EntityManager* GetEntityManager();

public:

	inline Controller();
	inline Controller(const unsigned int& entityID);
	inline ~Controller();

	inline virtual void Update(const float& deltaTime) = 0;

	template<ControllerStandar... T>
	void AddEntityID(const T&... entityIDs);

	template<ControllerStandar... T>
	void RemoveEntityIDs(const T&... entityIDs);

	inline void RemoveEntityID(const unsigned int& entityID);

	inline const std::vector<unsigned int>& GetEntityIDs();
};

#include "Controller.tpp"