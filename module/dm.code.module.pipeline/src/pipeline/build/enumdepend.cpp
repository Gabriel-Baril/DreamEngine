#include "pipeline/build/enumdepend.h"
#include "pipeline/symdb.h"

#if USING(DM_DREAMLIKE_BUILD)

#include "pipeline/xbuildconfig/enumdepend.h"

namespace dm
{
	using EnumdependCallback = bool (*)(sym_t sym, Response<XEnumDependTask>& res);
	static constexpr EnumdependCallback s_EnumdependCallbacks[underlying(ESymbolType::COUNT)] =
	{
#define SYMBOL_TYPE(symbolTypeEnum, symbolTypeString, parseFunc, assetParseFunc, enumdependFunc) enumdependFunc,
#include "pipeline/symbol_definition.h"
#undef SYMBOL_TYPE
	};

	void request_handle(const Request<XEnumDependTask>& req, Response<XEnumDependTask>& res)
	{
		DM_CORE_ASSERT(req.symbols, "Symbol cannot be null");
		for (int i = 0; i < req.get_symbol_count(); i++)
		{
			const sym_t symbol = req.symbols[i];
			ESymbolType symType = symdb_get_type(req.symbols[i]);
			if (symType != ESymbolType::UNKNOWN)
			{
				auto callback = s_EnumdependCallbacks[underlying(symType)];
				if (callback)
				{
					callback(symbol, res);
				}
			}
		}
	}

	const char* requet_get_type_name(const Request<XEnumDependTask>& req)
	{
		DM_MAYBE_UNUSED(req);
		return DM_NAMEOF(XEnumDependTask);
	}

	bool request_valid(const Request<XEnumDependTask>& req)
	{
		return req.symbols != nullptr;
	}

	u64 request_get_id(const Request<XEnumDependTask>& req)
	{
		HashBuilder hb;
		hb.add_type<XEnumDependTask>();
		// TODO: In theory we should sort the symbols to get a consistent hash regardless of order
		for (int i = 0; i < req.get_symbol_count(); i++)
		{
			hb.add(static_cast<u64>(req.symbols[i]));
		}
		return hb.get();
	}

	i32 request_get_slug(const Request<XEnumDependTask>& req, char* buffer, u64 count)
	{
		DM_MAYBE_UNUSED(req);
		DM_MAYBE_UNUSED(buffer);
		DM_MAYBE_UNUSED(count);
		DM_CORE_UNIMPLEMENTED();
		return 0;
	}

	ResponseStatus response_success(const Response<XEnumDependTask>& res)
	{
		return ResponseStatus::SUCCESS;
	}
}
#endif