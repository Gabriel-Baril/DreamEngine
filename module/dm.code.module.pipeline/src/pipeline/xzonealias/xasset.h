#pragma once

#include "core/core_define.h"

#if USING(DM_SYM_XZONEALIAS)
#include "pipeline/generated/zonealias_generated.h"
#include "pipeline/xasset/util.h"

namespace dm
{
	struct XZoneAliasAssetObject
	{
		static constexpr u64 VERSION = 1;
		using Underlying = XZoneAliasAsset;
	};
	XASSET_OBJECT_API(XZoneAliasAssetObject);
}
#endif

