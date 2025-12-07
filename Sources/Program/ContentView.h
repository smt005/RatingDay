// ◦ Xyz ◦

#pragma once

#include <memory>

class ContentView {
public:
	using Ptr = std::shared_ptr<ContentView>;
	using Wptr = std::weak_ptr<ContentView>;

public:
	~ContentView() = default;
	virtual void Render() {};
	virtual void Save() {};
};
