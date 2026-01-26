#include "FileReader.h"

#include <iostream>

#include <filesystem>
#include <sstream>
#include <fstream>

FileReader::FileReader() : Service()
{
}

FileReader::~FileReader()
{
}

string FileReader::GetAbsoluteFilePath(const string& filePath) const
{
	return filesystem::absolute(filePath).lexically_normal().string();
}

string FileReader::ReadFileAbsolutePath(const string& filePath)
{
	string absoluteFilePath = GetAbsoluteFilePath(filePath);

	return ReadFile(absoluteFilePath);
}

string FileReader::ReadFile(const string& filePath)
{
	ifstream inStream;

	stringstream buffer;

	try
	{
		inStream.open(filePath, ios::in);

		if (!inStream.is_open())
			throw runtime_error("FilePath; " + filePath + " wasn't found.\n");

		buffer << inStream.rdbuf();

	}
	catch (runtime_error& e)
	{
		cerr << e.what() << "\n";
	}
	catch (...)
	{
		cerr << "Unknow error detected while trying to read file.\n";
	}

	if (inStream.is_open())
		inStream.close();

	return buffer.str();
}

