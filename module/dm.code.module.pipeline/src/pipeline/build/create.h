#pragma once

#include "core/core_define.h"

#if USING(DM_DREAMLIKE_BUILD)
#include "core/core.h"
#include "pipeline/generated/buildconfig_generated.h"
#include "pipeline/xbuildconfig/xasset.h"
#include "pipeline/request.h"

namespace dm
{
	enum class BuildStatus
	{
		UNKNOWN,
		SUCCESS,
		FAILED
	};

	struct DreamlikeBuildCreateRequest
	{
		static constexpr u64 VERSION = 1;
	};

	template <>
	struct Request<DreamlikeBuildCreateRequest>
	{
		Request() = default;

		DM_INLINE void set_buildconfig(sym_t sym) { builconfigSym = sym; }
		
		sym_t builconfigSym = SYMNULL;
	};

	template <>
	struct Response<DreamlikeBuildCreateRequest>
	{
		DM_INLINE BuildStatus get_build_status() const { return buildStatus; }
		DM_INLINE void set_build_status(BuildStatus status) { buildStatus = status; }

		BuildStatus buildStatus = BuildStatus::UNKNOWN;
	};

	u64 request_get_id(const Request<DreamlikeBuildCreateRequest> &req);
	i32 request_get_slug(const Request<DreamlikeBuildCreateRequest> &req, char *buffer, u64 count);
	void request_handle(const Request<DreamlikeBuildCreateRequest> &req, Response<DreamlikeBuildCreateRequest>& response);
	const char *requet_get_type_name(const Request<DreamlikeBuildCreateRequest> &req);
	bool request_valid(const Request<DreamlikeBuildCreateRequest> &req);
	ResponseStatus response_success(const Response<DreamlikeBuildCreateRequest> &res);
}
#endif
