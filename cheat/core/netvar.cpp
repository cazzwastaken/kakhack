#include "netvar.h"

#include "interfaces.h"

#include <cctype>
#include <string>
#include <format>

void n::Setup() noexcept
{
	for (auto clientClass = i::client->GetAllClasses(); clientClass; clientClass = clientClass->next)
		if (clientClass->recvTable)
			Dump(clientClass->networkName, clientClass->recvTable, 0);
}

void n::Dump(const char* baseClass, RecvTable* table, const std::uint32_t offset)
{
	for (auto i = 0; i < table->propsCount; ++i)
	{
		const auto prop = &table->props[i];

		if (!prop || isdigit(prop->varName[0]))
			continue;

		if (fnv::Hash(prop->varName) == fnv::HashConst("baseclass"))
			continue;

		if (prop->recvType == SendPropType::DATATABLE &&
			prop->dataTable &&
			prop->dataTable->tableName[0] == 'D')
			Dump(baseClass, prop->dataTable, std::uint32_t(offset + prop->offset));

		data[fnv::Hash(std::format("{}->{}", baseClass, prop->varName).data())] =
		{
			prop,
			std::uint32_t(offset + prop->offset)
		};
	}
}

std::uint32_t n::GetOffset(const std::uint32_t hash)
{
	return data.at(hash).offset;
}

RecvProp* n::GetProp(const std::uint32_t hash)
{
	return data.at(hash).prop;
}
