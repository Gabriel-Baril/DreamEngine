#pragma once

#include "core/core_define.h"

#if USING(DM_SYM_XBUILDCONFIG)
#include "core/core.h"
#include "pipeline/generated/buildconfig_generated.h"
#include "pipeline/xbuildconfig/xasset.h"
#include "pipeline/request.h"
#include "pipeline/request_read_xasset.h"

namespace dm
{
	struct XBuildConfigReadRequest;

	template <>
	struct Request<XBuildConfigReadRequest>
	{
		DEFINE_XASSET_READ_CONSTRUCTORS(XBuildConfigAssetObject);

		Signature<XBuildConfigAssetObject> sig;
	};

	template <>
	struct Response<XBuildConfigReadRequest>
	{
		Handle<XBuildConfigAssetObject> data;
	};

	u64 request_get_id(const Request<XBuildConfigReadRequest> &req);
	i32 request_get_slug(const Request<XBuildConfigReadRequest> &req, char *buffer, u64 count);
	Response<XBuildConfigReadRequest> request_handle(const Request<XBuildConfigReadRequest> &req);

	const char *requet_get_type_name(const Request<XBuildConfigReadRequest> &req);
	bool request_valid(const Request<XBuildConfigReadRequest> &req);

	ResponseStatus response_success(const Response<XBuildConfigReadRequest> &res);
}
#endif
