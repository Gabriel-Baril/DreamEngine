#pragma once

#include "core/core_define.h"

#if USING(DM_SYM_XZONE)
#include "pipeline/xzone/xasset.h"
#include "pipeline/xasset/util.h"

namespace dm
{
	struct XZoneReadRequest
	{
		static constexpr u64 VERSION = 1;
		using UnderlyingObject = XZoneAssetObject;
	};
	XASSET_READ_API(XZoneReadRequest);
}
#endif
