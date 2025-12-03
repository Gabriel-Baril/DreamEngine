#pragma once
#include "core/core_define.h"

#if USING(DM_DREAMLIKE_BUILD)
#include "pipeline/sym.h"
#include "pipeline/request.h"
#include "core/stl/vector.h"

namespace dm
{
	struct XEnumDependRequest
	{
		static constexpr u64 VERSION = 1;
	};
	
	template <>
	struct Request<XEnumDependRequest>
	{
		Request() = default;

		DM_INLINE void set_symbols(sym_t* _symbols, u64 count)
		{ 
			symbols = _symbols;
			symbolCount = count;
		}

		DM_INLINE u64 get_symbol_count() const { return symbolCount; }

		sym_t* symbols = nullptr;
		u64 symbolCount = 0;
	};

	template <>
	struct Response<XEnumDependRequest>
	{

	};

	u64 request_get_id(const Request<XEnumDependRequest>& req);
	i32 request_get_slug(const Request<XEnumDependRequest>& req, char* buffer, u64 count);
	void request_handle(const Request<XEnumDependRequest>& req, Response<XEnumDependRequest>& response);
	const char* requet_get_type_name(const Request<XEnumDependRequest>& req);
	bool request_valid(const Request<XEnumDependRequest>& req);
	ResponseStatus response_success(const Response<XEnumDependRequest>& res);
}
#endif