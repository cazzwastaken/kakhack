#pragma once
#include <array>
#include <map>

namespace v
{
	struct Visuals
	{
		std::pair<bool, std::array<float, 4U>> box{ false, {1.00f, 1.f, 1.f, 1.f} };
		std::pair<bool, std::array<float, 4U>> filled{ false, {0.f, 0.f, 0.f, 0.3f} };
		std::pair<bool, std::array<float, 4U>> outlined{ false, {0.f, 0.f, 0.f, 1.f} };
		std::pair<bool, std::array<float, 4U>> name{ false, {1.00f, 1.f, 1.f, 1.f} };
		std::pair<bool, std::array<float, 4U>> headdot{ false, {1.00f, 1.f, 1.f, 1.f} };

		std::array<float, 4U> world = { 1.f, 1.f, 1.f, 1.f };
		std::array<float, 4U> props = { 1.f, 1.f, 1.f, 1.f };
		std::array<float, 4U> sky = { 1.f, 1.f, 1.f, 1.f };

		std::pair<bool, std::array<float, 4U>> visible{ false, {1.00f, 0.98f, 0.32f, 1.f} };
		std::pair<bool, std::array<float, 4U>> hidden{ false, {0.1f, 1.f, 1.f, 1.f} };
		std::pair<bool, std::array<float, 4U>> item{ false, {1.00f, 1.f, 1.f, 1.f} };
		std::pair<bool, std::array<float, 4U>> arm{ false, {1.f, 0.f, 0.f, 1.f} };
		std::pair<bool, std::array<float, 4U>> sleeve{ false, {0.f, 0.f, 1.f, 1.f} };

		std::pair<bool, std::array<float, 4U>> player{ false, {1.f, 0.f, 1.f, 0.7f} };
		std::pair<bool, std::array<float, 4U>> weapon{ false, {1.f, 1.f, 1.f, 0.7f} };
		std::pair<bool, std::array<float, 4U>> grenade{ false, {1.f, 0.5f, 0.5f, 0.7f} };
		std::pair<bool, std::array<float, 4U>> bomb{ false, {1.f, 0.f, 0.f, 1.f} };
		std::pair<bool, std::array<float, 4U>> chicken{ false, {1.f, 1.f, 0.f, 0.7f} };
	};
	inline auto visuals = Visuals{ };

	struct Misc
	{
		bool bunnyHop = false;

		bool ranks = false;
		bool radar = false;
		bool votes = false;
		bool money = false;

		float viewModelFov = 62.f;
		float worldFov = 90.f;

		std::pair<bool, std::array<float, 4U>> sniperCrosshair = { false, {1.f, 0.f, 0.f, 1.f} };
		std::pair<bool, std::array<float, 4U>> hitEffect = { false, {1.f, 0.f, 1.f, 1.f} };

	};
	inline auto misc = Misc{ };

	struct Skins
	{

	};
	inline auto skins = Skins{ };
}
