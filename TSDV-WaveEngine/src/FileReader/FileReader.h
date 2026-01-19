#pragma once

#include <string>
#include "Export.h"

using namespace std;

WAVEEXPORT class FileReader
{
private:

	string GetAbsoluteFilePath(const string& filePath) const;

public:

	WAVEEXPORT string ReadFile(string filePath);
};

