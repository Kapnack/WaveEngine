#pragma once

#include "Export.h"

class ServiceProvider;

class Service
{
protected:

	Service();
	virtual ~Service();

	friend class ServiceProvider;
};

