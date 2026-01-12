#include "FileReader.h"

#include <iostream>

#include <filesystem>
#include <sstream>
#include <fstream>

string FileReader::GetAbsoluteFilePath(const string filePath)
{
	return filesystem::absolute(filePath).lexically_normal().string();
}

string FileReader::ReadFile(string filePath)
{
	filePath = GetAbsoluteFilePath(filePath);

	ifstream inStream;

	stringstream buffer;

	try
	{
		inStream.open(filePath, ios::in);

		if (!inStream.is_open())
			throw runtime_error("FilePath; " + filePath + " wasn't found.");

		buffer << inStream.rdbuf();

	}
	catch (runtime_error& e)
	{
		cerr << e.what();
	}
	catch (...)
	{
		cerr << "Uknow error detected while trying to read file";
	}

	if (inStream.is_open())
		inStream.close();

	return buffer.str();
}

