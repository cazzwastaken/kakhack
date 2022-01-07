#pragma once
#include <cstring>

namespace fnv
{
	inline constexpr uint32_t base = 0x811C9DC5;
	inline constexpr uint32_t prime = 0x1000193;

	// Compiletime hash
	constexpr uint32_t HashConst(const char* data, const std::uint32_t value = base) noexcept
	{
		return (data[0] == '\0') ? value : HashConst(&data[1], (value ^ std::uint32_t(data[0])) * prime);
	}

	// Runtime hash
	inline uint32_t Hash(const char* data) noexcept
	{
		std::uint32_t hashed = base;

		for (size_t i = 0U; i < strlen(data); ++i)
		{
			hashed ^= data[i];
			hashed *= prime;
		}

		return hashed;
	}
}
