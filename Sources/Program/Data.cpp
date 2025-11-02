
#include "Data.h"
#include <Help.h>
#include <Log.h>

Data::Data(std::string_view name)
{
	_fileNamePath = TO_STRING("{}.json", name);
	help::loadJson(_fileNamePath, _value);
}

void Data::Save()
{
	help::saveJson(_fileNamePath, _value);
}
