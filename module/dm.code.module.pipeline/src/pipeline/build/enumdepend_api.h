#pragma once

#include "core/core_define.h"

#if USING(DM_DREAMLIKE_BUILD)
#include "core/stl/map.h"

#include "shared/resource.h"

#include "pipeline/sym.h"
#include "pipeline/request.h"

namespace dm
{
	struct EnumdependContext
	{
		// map<sym_t, ResourceNode> emittedResources;
	};

	struct ResourceNode
	{
		resource_t type;
		u64 objectId;
	};

	void enumdepend_init(EnumdependContext& ctx);
	void enumdepend_shutdown(EnumdependContext& ctx);

	void enumdepend_emit(EnumdependContext& ctx, const ResourceNode& node);
	// We could have multiple enumdepend_emit overloads for different types of inputs

	void enumdepend_xasset(sym_t symbol);
}
#endif