#pragma once
#include <vector>
#include <string>

class Config
{
public:
	void Setup();

	void ExistCheck();
	void Refresh();

	void Create();
	void Delete();

	void Load();
	void Save();

	constexpr size_t Size() const
	{
		return configs.size();
	}

	constexpr size_t& Selected()
	{
		return selected;
	}

	constexpr const char* GetSelectedName() const
	{
		if (configs.empty())
			return "None";
		else
			return configs[selected].c_str();
	}

	const char* operator[](const std::size_t index) const
	{
		return configs[index].c_str();
	}

public:
	char nameBuffer[36];

private:
	const char* baseDir = "kakhack/";
	const char* configDir = "kakhack/configs";

	size_t selected = 0;
	std::vector<std::string> configs{ };
};
