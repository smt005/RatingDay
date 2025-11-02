
#include <filesystem>
#include "Help.h"
#include "FileManager.h"

#include <iostream>


bool help::loadJson(const std::string& fileName, Json::Value& value, bool toResource)
{
	std::string mystring = Engine::FileManager::readTextFile(fileName, toResource ? Engine::FileManager ::getResourcesDir() : std::filesystem::current_path());

	Json::CharReaderBuilder readerBuilder;
	Json::CharReader *reader = readerBuilder.newCharReader();
	std::string err;
	if (reader->parse(mystring.c_str(), mystring.c_str() + mystring.length(), &value, &err)) {
		return true;
	}

	return false;
}

bool help::saveJson(const std::string& fileName, const Json::Value& value, const std::string& indentation, bool toResource)
{
	const std::string valueString = stringFroJson(value, indentation);
	return Engine::FileManager::writeTextFile(fileName, valueString, toResource ? Engine::FileManager::getResourcesDir() : std::filesystem::current_path());
}

std::string help::stringFroJson(const Json::Value& value, const std::string& indentation)
{
	Json::StreamWriterBuilder writerBuilder;
	writerBuilder["indentation"] = indentation; // If you want whitespace-less output
	return Json::writeString(writerBuilder, value);
}
