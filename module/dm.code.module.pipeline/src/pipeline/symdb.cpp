#include "symdb.h"

#include "core/stl/unordered_map.h"
#include "core/hash.h"

#include "xsrc.h"
#include "nxsrc.h"
#include "strdb.h"

namespace dm
{
	struct SymDBGlob
	{
		unordered_map<sym_t, SymbolMetadata> symmap{};
	};

	static SymDBGlob s_SymDBGlob{};

	static constexpr const char *s_SymTypeStr[underlying(ESymbolType::COUNT)] = {
#define SYMBOL_TYPE(symbolTypeEnum, symbolTypeString, parseFunc, assetParseFunc, enumdependFunc) symbolTypeString,
#include "pipeline/symbol_definition.h"
#undef SYMBOL_TYPE
	};

	static constexpr SourceParseCallback s_SourceParseCallbacks[underlying(ESymbolType::COUNT)] = {
#define SYMBOL_TYPE(symbolTypeEnum, symbolTypeString, parseFunc, assetParseFunc, enumdependFunc) parseFunc,
#include "pipeline/symbol_definition.h"
#undef SYMBOL_TYPE
	};

	static void explore_source(const fspath &path)
	{
		if (!filesystem_is_directory(path))
		{
			ESymbolType type = symdb_get_source_file_type(path);
			if (type != ESymbolType::UNKNOWN)
			{
				DM_TRACE_LOG("Source '{0}'", path.string().c_str());
				SourceParseCallback parseCallback = symdb_get_parse_callback(type);
				if (parseCallback)
				{
					parseCallback(path);
				}
			}
		}
	}

	const char *symdb_sym_to_str(ESymbolType type)
	{
		return s_SymTypeStr[underlying(type)];
	}

	ESymbolType symdb_str_to_sym_type(const char *type)
	{
		char lowerCaseBuffer[SYMBOL_TYPE_MAX_LENGTH];
		str_copy(lowerCaseBuffer, type);
		str_to_lowercase(lowerCaseBuffer, strlen(lowerCaseBuffer));

		for (int i = 0; i < underlying(ESymbolType::COUNT); i++)
		{
			if (str_equals(lowerCaseBuffer, s_SymTypeStr[i]))
			{
				return static_cast<ESymbolType>(i);
			}
		}
		return ESymbolType::UNKNOWN;
	}

	ESymbolType symdb_sym_type_from_sym_name(const char* symName)
	{
		const char* dotPosition = str_find_first_of(symName, '.');
		if (dotPosition == nullptr)
		{
			return ESymbolType::UNKNOWN;
		}
		return symdb_str_to_sym_type(dotPosition + 1);
	}

	SourceParseCallback symdb_get_parse_callback(ESymbolType type)
	{
		return s_SourceParseCallbacks[underlying(type)];
	}

	bool symdb_is_xsymbol(ESymbolType type)
	{
		return type >= ESymbolType::XSYMBOL_BEGIN && type <= ESymbolType::XSYMBOL_END;
	}

	bool symdb_is_nxsymbol(ESymbolType type)
	{
		return type >= ESymbolType::NXSYMBOL_BEGIN && type <= ESymbolType::NXSYMBOL_END;
	}

	ESymbolType symdb_get_source_file_type(const fspath &path)
	{
		for (int i = 0; i < underlying(ESymbolType::COUNT); i++)
		{
			char extBuffer[SYMBOL_TYPE_MAX_LENGTH + 1];
			sprintf(extBuffer, ".%s", s_SymTypeStr[i]);
			if (filesystem_has_extension(path, extBuffer))
			{
				return static_cast<ESymbolType>(i);
			}
		}
		return ESymbolType::UNKNOWN;
	}

	void symdb_explore_sources(const fspath &path)
	{
		filesystem_iterate(path, explore_source, true);
	}

	const SymbolMetadata *symdb_get_meta(sym_t symbol)
	{
		if (s_SymDBGlob.symmap.contains(symbol))
		{
			return &s_SymDBGlob.symmap[symbol];
		}
		return nullptr;
	}

	ESymbolType symdb_get_type(sym_t symbol)
	{
		const SymbolMetadata *meta = symdb_get_meta(symbol);
		if (meta)
		{
			return meta->type;
		}
		return ESymbolType::UNKNOWN;
	}

	void symdb_register(sym_t symbol, const char *name, ESymbolType type, const fspath &path)
	{
		if (symdb_get_meta(symbol))
		{
			return;
		}

		SymbolMetadata &meta = s_SymDBGlob.symmap[symbol];
		meta.name = strdb_allocate(name);
		meta.type = type;
		meta.path = path;
	}
}
