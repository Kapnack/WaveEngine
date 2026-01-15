#ifndef SERVICEPROVIDER
#define SERVICEPROVIDER

#include "ServiceProvider.h"

template<ServiceStandard T>
void ServiceProvider::Register(T* service)
{
	services[typeid(T)] = service;
}

template<ServiceStandard T>
T* ServiceProvider::Get()
{
	return static_cast<T*>(services.at(typeid(T)));
}

template<ServiceStandard T>
T* ServiceProvider::TryGet()
{
	unordered_map<type_index, Service*>::iterator it = services.find(typeid(T));

	return (it != services.end()) ? static_cast<T*>(it->second) : nullptr;
}

template<ServiceStandard T>
void ServiceProvider::UnRegister()
{
	services.erase(typeid(T));
}

void ServiceProvider::Clear()
{
	for (auto& [_, service] : services)
	{
		delete service;
	}

	services.clear();
}

#endif