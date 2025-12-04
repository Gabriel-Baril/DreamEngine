#pragma once

#include "core/core_define.h"

#if USING(DM_SYM_XZONEALIAS)
#include "pipeline/xzonealias/xasset.h"
#include "pipeline/xasset/util.h"

namespace dm
{
	struct XZoneAliasReadTask
	{
		static constexpr u64 VERSION = 1;
		using UnderlyingObject = XZoneAliasAssetObject;
	};
	XASSET_OBJECT_API(XZoneAliasReadTask);
}
#endif
