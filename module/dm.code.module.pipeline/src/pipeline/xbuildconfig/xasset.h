#pragma once

#include "core/core_define.h"

#if USING(DM_SYM_XBUILDCONFIG)
#include "pipeline/generated/buildconfig_generated.h"
#include "pipeline/xasset/util.h"

namespace dm
{
	struct XBuildConfigAssetObject
	{
		static constexpr u64 VERSION = 1;
		using Underlying = XBuildConfigAsset;
	};
	XASSET_OBJECT_API(XBuildConfigAssetObject)
}
#endif
