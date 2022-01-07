#include "config.h"

#include <filesystem>
#include <fstream>

#include "../../external/json/json.hpp"

#include "../core/interfaces.h"

void Config::Setup()
{
	ExistCheck();
	Refresh();
}

void Config::ExistCheck()
{
	if (!std::filesystem::exists(baseDir))
	{
		std::filesystem::create_directory(baseDir);

		if (!std::filesystem::exists(configDir))
			std::filesystem::create_directory(configDir);
	}
}

void Config::Refresh()
{
	ExistCheck();

	// Flush the config list
	configs.clear();

	for (const auto& dir : std::filesystem::recursive_directory_iterator(configDir))
	{
		if (!dir.exists() || !dir.is_regular_file())
			continue;

		const auto& path = dir.path();

		if (!path.has_filename() || !path.has_extension())
			continue;

		if (!path.extension().generic_string().ends_with(".json"))
			continue;

		configs.push_back(path.filename().generic_string());
	}
}

void Config::Create()
{
	ExistCheck();

	// Create a string to use *modern* string functions
	auto name = std::string(nameBuffer);

	if (name.empty())
		return;

	if (!name.ends_with(".json"))
		name += std::string(".json");

	const auto file = std::ofstream(configDir + std::string("/") + name);

	Refresh();
}

void Config::Delete()
{
	ExistCheck();

	if (configs.empty())
		return;

	std::filesystem::remove(configDir + std::string("/") + GetSelectedName());

	Refresh();
}

void Config::Load()
{

}

void Config::Save()
{

}
