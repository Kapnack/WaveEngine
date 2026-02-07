#pragma once

#include "Export.h"

class ServiceProvider;

WAVEEXPORT class Service
{
protected:

	WAVEEXPORT Service();
	WAVEEXPORT virtual ~Service();

	friend class ServiceProvider;
};

