#pragma once

#include "core/core_define.h"

#if USING(DM_SYM_XZONE)
#include "pipeline/generated/zone_generated.h"
#include "pipeline/xasset/util.h"

namespace dm
{
	struct XZoneAssetObject
	{
		static constexpr u64 VERSION = 1;
		using Underlying = XZoneAssetObject;
	};
	XASSET_OBJECT_API(XZoneAssetObject);
}
#endif
