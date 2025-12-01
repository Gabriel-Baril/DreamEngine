#pragma once

#include "core/core_define.h"

#if USING(DM_SYM_XFEATURE)
#include "pipeline/xfeature/xasset.h"
#include "pipeline/xasset/util.h"

namespace dm
{
	struct XFeatureReadRequest
	{
		static constexpr u64 VERSION = 1;
		using UnderlyingObject = XFeatureAssetObject;
	};
	XASSET_READ_API(XFeatureReadRequest);
}
#endif
