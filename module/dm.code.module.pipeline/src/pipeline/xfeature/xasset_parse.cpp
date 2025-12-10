#include "xasset_parse.h"

#include "core/core_define.h"

#if USING(DM_SYM_XFEATURE)
#include "core/stl/vector.h"

#include "pipeline/generated/feature_generated.h"
#include "pipeline/xml_util.h"
#include "pipeline/fbs_util.h"
#include "xasset.h"

namespace dm
{
	static constexpr const char *XML_FEATURE_NODE_FEATURES_NAME = "Features";
	static constexpr const char *XML_FEATURE_NODE_FEATURE_NAME = "Feature";
	static constexpr const char *XML_FEATURE_ATTR_FEATURE_NAME = "feature";

	static constexpr const char *XML_FEATURE_NODE_ALIASES_NAME = "Aliases";
	static constexpr const char *XML_FEATURE_NODE_ALIAS_NAME = "Alias";
	static constexpr const char *XML_FEATURE_ATTR_ALIAS_NAME = "alias";

	static constexpr const char *XML_FEATURE_NODE_SYMBOLS_NAME = "Symbol";
	static constexpr const char *XML_FEATURE_ATTR_SYMBOL_NAME = "symbol";

	static bool feature_asset_parse(flatbuffers::FlatBufferBuilder &builder, const pugi::xml_node &node, const SourceContext &ctx)
	{
		// Name & id
		const char *nameStr = get_xml_attr(node, "name");
		auto fbName = builder.CreateString(nameStr);

		// <Features>
		auto fbFeatures = create_string_vector_from_xml(
				builder,
				node.child(XML_FEATURE_NODE_FEATURES_NAME),
				XML_FEATURE_NODE_FEATURE_NAME,
				XML_FEATURE_ATTR_FEATURE_NAME);

		// <Aliases> -> zones conversion
		// std::vector<flatbuffers::Offset<CFeatureZone>> fbZonesVec{};
		// const auto aliasesNode = node.child(XML_FEATURE_NODE_ALIASES_NAME);
		// if (aliasesNode)
		// {
		// 	for (const auto &aliasNode : aliasesNode.children(XML_FEATURE_NODE_ALIAS_NAME))
		// 	{
		// 		const char *aliasStr = get_xml_attr(aliasNode, XML_FEATURE_ATTR_ALIAS_NAME);
		// 		auto fbAliasName = builder.CreateString(aliasStr);
		// 
		// 		// Parse symbols within this alias
		// 		std::vector<flatbuffers::Offset<CFeatureZoneEntry>> fbEntriesVec{};
		// 		for (const auto &symbolNode : aliasNode.children(XML_FEATURE_NODE_SYMBOLS_NAME))
		// 		{
		// 			const char *symbolStr = get_xml_attr(symbolNode, XML_FEATURE_ATTR_SYMBOL_NAME);
		// 			auto fbSymbolName = builder.CreateString(symbolStr);
		// 			auto fbEntry = CreateCFeatureZoneEntry(builder, fbSymbolName, CAssetType_unknown);
		// 			fbEntriesVec.emplace_back(fbEntry);
		// 		}
		// 		auto fbEntries = builder.CreateVector(fbEntriesVec);
		// 		auto fbZone = CreateCFeatureZone(builder, fbAliasName, fbEntries);
		// 
		// 		fbZonesVec.emplace_back(fbZone);
		// 	}
		// }
		// auto fbZones = builder.CreateVector(fbZonesVec, fbZonesVec.size());

		Signature<XFeatureAssetObject> sig(nameStr);
		const u64 oId = object_get_id(sig);
		auto fbFeatureAsset = CreateXFeatureAsset(
				builder,
				oId,
				fbName,
				fbFeatures,
				0);

		FinishXFeatureAssetBuffer(builder, fbFeatureAsset);

		BeginObjectInfo info;
		info.totalPathDep = 1;
		info.totalObjDep = 0;
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

	bool xasset_parse_feature(const pugi::xml_node &node, const SourceContext &ctx)
	{
		flatbuffers::FlatBufferBuilder builder(2048);
		return feature_asset_parse(builder, node, ctx);
	}
}
#endif
