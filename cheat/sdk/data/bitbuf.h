#pragma once
#include <cstdint>
#include <string.h>

class BitBufRead
{
public:
	constexpr BitBufRead(const uintptr_t address, const uintptr_t offset = 0) :
		base(address), offset(offset) { }

public:
	constexpr void SetOffset(const uintptr_t offset)
	{
		this->offset = offset;
	}

	constexpr void Skip(const uintptr_t length)
	{
		this->offset += length;
	}

	constexpr const uintptr_t Position() const
	{
		return base + offset;
	}

public:
	// Reads 1 byte from offset
	inline int ReadByte()
	{
		const auto value = *reinterpret_cast<char*>(Position());
		Skip(1);
		return value;
	}

	// Reads 2 bytes from offset
	inline bool ReadBool()
	{
		const auto value = *reinterpret_cast<bool*>(Position());
		Skip(1);
		return value;
	}

	const char* ReadString()
	{
		char buffer[256];
		const auto length = *reinterpret_cast<char*>(Position());
		Skip(1);

		memcpy(buffer, reinterpret_cast<void*>(Position()), length > 255 ? 255 : length);
		buffer[length > 255 ? 255 : length] = '\0';

		Skip(length + 1);

		return buffer;
	}

private:
	uintptr_t base;
	uintptr_t offset;
};