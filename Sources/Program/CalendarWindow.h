#include <MainWindow.h>
#include <string>
#include <vector>
#include <unordered_map>

class Data;

class CalendarWindow final : public Window {
private:
	struct TextData {
		inline static const size_t size = 128;
		char chars[size];
	};

public:
	CalendarWindow(Data& data);	
	void Render() override;
	void MakeUi();

private:
	Data& _data;
	std::unordered_map<std::string_view, TextData> _texts;

private:
	static std::vector<std::string> _days;
};
