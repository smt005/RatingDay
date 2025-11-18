#pragma once

#include <memory>

class ContentWindow {
public:
	using Ptr = std::shared_ptr<ContentWindow>;
	using Wptr = std::weak_ptr<ContentWindow>;

public:
	~ContentWindow() = default;
	virtual void Render() {};
	virtual void Save() {};
};
