#include "xasset_parse.h"

#if USING(DM_SYM_XZONEALIAS)
#include "pugixml/pugixml.hpp"

#include "core/hash.h"
#include "core/stl/vector.h"

#include "pipeline/symdb.h"
#include "pipeline/xsrc.h"
#include "pipeline/xzonealias/xasset.h"
#include "pipeline/fbs_util.h"

namespace dm
{
	static bool zonealias_parse(flatbuffers::FlatBufferBuilder &builder, const pugi::xml_node &node, const SourceContext &ctx)
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

		Signature<XZoneAliasAssetObject> sig(nameStr);
		const u64 oId = object_get_id(sig);

		bool ok = cache_obj_begin(oId, info);
		if (ok)
		{
			cache_obj_pathdep(oId, ctx.path);
			cache_obj_payload(oId, builder.GetBufferPointer(), builder.GetSize());
			cache_obj_end(oId);
			cache_obj_save(oId);
		}

		return ok;
	}

	bool xasset_parse_zonealias(const pugi::xml_node &node, const SourceContext &ctx)
	{
		flatbuffers::FlatBufferBuilder builder(2048);
		return zonealias_parse(builder, node, ctx);
	}
}
#endif
