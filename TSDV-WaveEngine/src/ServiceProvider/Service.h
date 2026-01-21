#pragma once

#include "Export.h"

class ServiceProvider;

class Service
{
	friend class ServiceProvider;

protected:

	Service();
	virtual ~Service();
};

