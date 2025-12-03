#pragma once

namespace dm
{
	enum class resource_t
	{
#define RESOURCE_TYPE(enumName, strName, className, defaultName) enumName,
#include "resource_definition.h"
#undef RESOURCE_TYPE
		RESOURCE_TYPE_COUNT
	};
}