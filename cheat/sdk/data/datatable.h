#pragma once
#include "../definitions.h"

#include <cstdint>

enum class SendPropType : int
{
	INT = 0,
	FLOAT,
	VECTOR,
	VECTOR2D,
	STRING,
	ARRAY,
	DATATABLE,
	INT64,
	SENDPROPTYPEMAX
};

struct DataVariant
{
	union
	{
		float Float;
		long Int;
		char* String;
		void* Data;
		float Vector[3];
		int64_t Int64;
	};

	SendPropType type;
};

struct RecvProxyData
{
	const RecvProp* pRecvProp;
	DataVariant	value;
	int element;
	int objectId;
};

struct RecvTable
{
	RecvProp* props;
	int	propsCount;
	void* decoder;
	char* tableName;
	bool initialized;
	bool inMainList;
};

struct RecvProp
{
	char* varName;
	SendPropType recvType;
	int flags;
	int stringBufferSize;
	bool insideArray;
	const void* extraData;
	RecvProp* arrayProp;
	ArrayLengthProxyFn* arrayLengthProxyFn;
	RecvVarProxyFn proxyFn;
	DataTableProxyFn* dataTableProxyFn;
	RecvTable* dataTable;
	int offset;
	int elementStride;
	int elements;
	const char* parentArrayPropName;
};
