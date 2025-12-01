#pragma once

#include "core/core_define.h"

#if USING(DM_SYM_XBUILDCONFIG)
#include "pipeline/xbuildconfig/xasset.h"
#include "pipeline/xasset/util.h"

namespace dm
{
	struct XBuildConfigReadRequest
	{
		static constexpr u64 VERSION = 1;
		using UnderlyingObject = XBuildConfigAssetObject;
	};
	XASSET_READ_API(XBuildConfigReadRequest);
}
#endif
