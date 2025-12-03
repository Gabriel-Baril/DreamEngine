#pragma once

#include "core/core.h"
#include "core/core_filesystem.h"

#include "sym.h"

namespace dm
{
	// The symbol types supported by the pipeline
	enum class ESymbolType
	{
#define SYMBOL_TYPE(symbolTypeEnum, symbolTypeString, parseFunc, assetParseFunc, enumdependFunc) symbolTypeEnum,
#include "pipeline/symbol_definition.h"
#undef SYMBOL_TYPE

		COUNT,
		NXSYMBOL_BEGIN = SYMBOL_VERT_SHADER, // non xsymbol
		NXSYMBOL_END = SYMBOL_OBJ,
		XSYMBOL_BEGIN = SYMBOL_STRINGTABLE, // engine-specific xml-like symbol
		XSYMBOL_END = SYMBOL_FEATURE,
		UNKNOWN
	};

	static_assert(
		underlying(ESymbolType::COUNT) ==
		[]() {
			int count = 0;
#define SYMBOL_TYPE(...) ++count;
#include "pipeline/symbol_definition.h"
#undef SYMBOL_TYPE
			return count;
		}(),
		"ESymbolType::COUNT does not match number of entries in symbol_definition.h"
	);

	struct SymbolMetadata
	{
		const char *name;
		ESymbolType type;
		fspath path;
	};

	using SourceParseCallback = bool (*)(const fspath &path);

	const char *symdb_sym_to_str(ESymbolType type);
	ESymbolType symdb_str_to_sym(const char *type);

	SourceParseCallback symdb_get_parse_callback(ESymbolType type);

	bool symdb_is_xsymbol(ESymbolType type);
	bool symdb_is_nxsymbol(ESymbolType type);
	ESymbolType symdb_get_source_file_type(const fspath &path);
	void symdb_explore_sources(const fspath &path);

	const SymbolMetadata *symdb_get_meta(sym_t symbol);
	ESymbolType symdb_get_type(sym_t symbol);
	void symdb_register(sym_t symbol, const char *name, ESymbolType type, const fspath &path);
}