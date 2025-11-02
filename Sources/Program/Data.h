
#include <string>
#include <json/json.h>

class Data final {
public:
	Data(std::string_view name);
	void Save();

public: //private:
	std::string _fileNamePath;
	Json::Value _value;
};
