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

	struct BuildCreateTask
	{
		static constexpr u64 VERSION = 1;
	};

	template <>
	struct Request<BuildCreateTask>
	{
		Request() = default;

		DM_INLINE void set_buildconfig(sym_t sym) { builconfigSym = sym; }
		
		sym_t builconfigSym = SYMNULL;
	};

	template <>
	struct Response<BuildCreateTask>
	{
		DM_INLINE BuildStatus get_build_status() const { return buildStatus; }
		DM_INLINE void set_build_status(BuildStatus status) { buildStatus = status; }

		BuildStatus buildStatus = BuildStatus::UNKNOWN;
	};

	u64 request_get_id(const Request<BuildCreateTask> &req);
	i32 request_get_slug(const Request<BuildCreateTask> &req, char *buffer, u64 count);
	void request_handle(const Request<BuildCreateTask> &req, Response<BuildCreateTask>& response);
	const char *requet_get_type_name(const Request<BuildCreateTask> &req);
	bool request_valid(const Request<BuildCreateTask> &req);
	ResponseStatus response_success(const Response<BuildCreateTask> &res);
}
#endif
