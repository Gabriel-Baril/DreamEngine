#pragma once

#include "core/core_define.h"

#if USING(DM_SYM_XZONE)
#include "pipeline/object_get.h"
#include "pipeline/symdb.h"
#include "pipeline/generated/zone_generated.h"

namespace dm
{
	static constexpr u64 XASSET_CODE_VERSION_BUILDCONFIG = 1;

	struct XZoneAssetObject
	{
		using Underlying = XZoneAsset;
	};

	template <>
	struct Signature<XZoneAssetObject>
	{
		Signature(sym_t _symbol)
				: symbol{_symbol}
		{
		}

		sym_t symbol;
	};

	u64 object_get_id(const Signature<XZoneAssetObject> &sig);
	i32 object_get_slug(const Signature<XZoneAssetObject> &sig, char *buffer, u64 count);
	ObjectRequestResult object_request(const Signature<XZoneAssetObject> &sig);
	void object_request_failure(const Signature<XZoneAssetObject> &sig, ObjectRequestResult result);
	void object_load_failure(const Signature<XZoneAssetObject> &sig);
}
#endif
