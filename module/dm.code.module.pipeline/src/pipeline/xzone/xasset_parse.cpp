#include "xasset_parse.h"

#if USING(DM_SYM_XZONE)
#include "pugixml/pugixml.hpp"

#include "core/hash.h"
#include "core/stl/vector.h"

#include "pipeline/symdb.h"
#include "pipeline/xsrc.h"
#include "pipeline/xzone/xasset.h"
#include "pipeline/fbs_util.h"

namespace dm
{
	static bool zone_parse(flatbuffers::FlatBufferBuilder &builder, const pugi::xml_node &node, const SourceContext &ctx)
	{
		// Name & id
		const char *nameStr = get_xml_attr(node, "name");
		DM_CORE_ASSERT_PTR(nameStr, "xsymbol require a name");
		auto fbName = builder.CreateString(nameStr);

		// auto buildConfig = CreateXBuildConfigAsset(
		// 		builder,
		// 		oId,
		// 		fbName,
		// 		platform,
		// 		fbFeatures);
		// 
		// FinishXBuildConfigAssetBuffer(builder, buildConfig);

		BeginObjectInfo info;
		info.totalPathDep = 1;
		info.totalObjDep = 0;

		Signature<XZoneAssetObject> sig(nameStr);
		const u64 oId = object_get_id(sig);

		bool ok = cache_obj_begin(oId, info);
		if (ok)
		{
			cache_obj_pathdep(oId, ctx.path); // TODO: Once xsym parenting will exist, this logic will get more complex (if we want parent to be in different xsrc)
			cache_obj_payload(oId, builder.GetBufferPointer(), builder.GetSize());
			cache_obj_end(oId);
			cache_obj_save(oId);
		}

		return ok;
	}

	bool xasset_parse_zone(const pugi::xml_node &node, const SourceContext &ctx)
	{
		flatbuffers::FlatBufferBuilder builder(2048);
		return zone_parse(builder, node, ctx);
	}
}
#endif
