#pragma once

#include "core/core_define.h"

#if USING(DM_SYM_XFEATURE)
#include "pipeline/generated/feature_generated.h"
#include "pipeline/xasset/util.h"

namespace dm
{
	struct XFeatureAssetObject
	{
		static constexpr u64 VERSION = 1;
		using Underlying = XFeatureAsset;
	};
	XASSET_OBJECT_API(XFeatureAssetObject);
}
#endif
