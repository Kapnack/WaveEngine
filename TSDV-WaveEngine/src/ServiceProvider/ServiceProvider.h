#pragma once

#include "Service.h"

#include <unordered_map>
#include <typeindex>
#include <type_traits>

using namespace std;

template<typename T>
concept ServiceStandard = is_base_of_v<Service, T>;

class ServiceProvider
{
private:
    static inline unordered_map<type_index, Service*> services;

public:
    template<ServiceStandard T>
    static void Register(T* service);

    template<ServiceStandard T>
    static T* Get();

    template<ServiceStandard T>
    static T* TryGet();

    template<ServiceStandard T>
    static void UnRegister();

    static inline void Clear();
};

#include "ServiceProvider.tpp"