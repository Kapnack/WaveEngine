#pragma once

#include <string>

using namespace std;

static class FileReader
{
private:

	string GetAbsoluteFilePath(const string filePath);

public:

	string ReadFile(string filePath);
};

