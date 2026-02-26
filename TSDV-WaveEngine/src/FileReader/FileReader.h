#pragma once

#include <string>
#include "ServiceProvider/Service.h"
#include "Export.h"

class BaseGame;
class ServiceProvider;

using namespace std;

WAVEEXPORT class FileReader : public Service
{
private:

	string GetAbsoluteFilePath(const string_view filePath) const;

	FileReader();
	~FileReader();

	friend class BaseGame;
	friend class ServiceProvider;

public:

	WAVEEXPORT string ReadFileAbsolutePath(const string_view filePath);
	WAVEEXPORT string ReadFile(const string_view filePath);
};

