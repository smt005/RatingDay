// ◦ Xyz ◦

#pragma once

#include <WindowsManager.h>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "ContentView.h"

class Statistics final : public ContentView {
public:
	using Ptr = std::shared_ptr<Statistics>;
	using Wptr = std::weak_ptr<Statistics>;

private:
	struct TextData {
		inline static const size_t size = 128;
		char chars[size];
	};

	struct Element {
		TextData id;
		TextData rate;
		TextData description;
	};

public:
	Statistics();
	void Render() override;
	void MakeUi();

private:
	std::string _dayTimeStr;
	Element* _editElement = nullptr;
	std::vector<Element> _texts;
};
