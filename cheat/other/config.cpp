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

#define READ(j, var) v::var = j[#var];
#define READ_ARR(j, var) std::copy(j[#var].begin(), j[#var].end(), v::space::var);
#define WRITE(j, var) j[#var] = v::var;

void Config::Load() {

	if (GetSelectedName() == NULL)
		return;
	nlohmann::json j;
	std::fstream read(configDir + std::string("/") + GetSelectedName());
	read >> j;
	read.close();

	READ(j, visuals.visible.first)
	READ(j, visuals.visible.second)
	READ(j, visuals.hidden.first)

	READ(j, visuals.hidden.second)
	READ(j, misc.sniperCrosshair.first)
	READ(j, misc.sniperCrosshair.second)

	// etc, etc etc

}

void Config::Save() {
	if (GetSelectedName() == NULL)
		return;
	nlohmann::json j;

	WRITE(j, visuals.visible.first)
	WRITE(j, visuals.visible.second)
	WRITE(j, visuals.hidden.first)

	WRITE(j, visuals.hidden.second)
	WRITE(j, misc.sniperCrosshair.first)
	WRITE(j, misc.sniperCrosshair.second)
	// etc, etc etc

	std::ofstream write(configDir + std::string("/") + GetSelectedName());
	write << j << std::endl;
	write.close();
}
