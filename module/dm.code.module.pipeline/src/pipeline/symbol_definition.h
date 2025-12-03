#ifndef SYMBOL_TYPE
#error Must define SYMBOL_TYPE before including symbol_definition.h
#endif // !SYMBOL_TYPE

SYMBOL_TYPE(SYMBOL_VERT_SHADER, "vert", nxsrc_agnostic_parse, nullptr, nullptr)
SYMBOL_TYPE(SYMBOL_FRAG_SHADER, "frag", nxsrc_agnostic_parse, nullptr, nullptr)
SYMBOL_TYPE(SYMBOL_FBX, "fbx", nxsrc_agnostic_parse, nullptr, nullptr)
SYMBOL_TYPE(SYMBOL_OBJ, "obj", nxsrc_agnostic_parse, nullptr, nullptr)

SYMBOL_TYPE(SYMBOL_STRINGTABLE, "stringtable", xsrc_agnostic_parse, nullptr					, nullptr)
SYMBOL_TYPE(SYMBOL_TEXT		  , "text"		 , xsrc_agnostic_parse, nullptr					, nullptr)
SYMBOL_TYPE(SYMBOL_PREFAB	  , "prefab"	 , xsrc_agnostic_parse, xasset_parse_prefab		, nullptr)
SYMBOL_TYPE(SYMBOL_BUILDCONFIG, "buildconfig", xsrc_agnostic_parse, xasset_parse_buildconfig, enumdepend_xbuildconfig)
SYMBOL_TYPE(SYMBOL_FEATURE	  , "feature"	 , xsrc_agnostic_parse, xasset_parse_feature	, nullptr)
