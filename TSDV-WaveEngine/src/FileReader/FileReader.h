#pragma once

#include <string>
#include "Export.h"

using namespace std;

WAVEEXPORT static class FileReader
{
private:

	static string GetAbsoluteFilePath(const string filePath);

public:

	WAVEEXPORT static string ReadFile(string filePath);
};

