#pragma once

template <typename T>
class Singlitone {
public:
	static T& Instance()
	{
		if (!instance) {
			instance = new T();
		}
		return *instance;
	}

	static void Destroy()
	{
		delete instance;
		instance = nullptr;
	}

private:
	inline static T* instance = nullptr;
};
