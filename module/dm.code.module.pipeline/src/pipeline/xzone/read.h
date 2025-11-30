#pragma once

#include "core/core_define.h"

#if USING(DM_SYM_XZONE)
#include "core/core.h"
#include "pipeline/generated/buildconfig_generated.h"
#include "pipeline/xbuildconfig/xasset.h"
#include "pipeline/request.h"
#include "pipeline/request_read_xasset.h"

namespace dm
{
	struct XZoneReadRequest;

	template <>
	struct Request<XZoneReadRequest>
	{
		DEFINE_XASSET_READ_CONSTRUCTORS(XBuildConfigAssetObject);

		Signature<XBuildConfigAssetObject> sig;
	};

	template <>
	struct Response<XZoneReadRequest>
	{
		Handle<XBuildConfigAssetObject> data;
	};

	u64 request_get_id(const Request<XZoneReadRequest> &req);
	i32 request_get_slug(const Request<XZoneReadRequest> &req, char *buffer, u64 count);
	Response<XZoneReadRequest> request_handle(const Request<XZoneReadRequest> &req);

	const char *requet_get_type_name(const Request<XZoneReadRequest> &req);
	bool request_valid(const Request<XZoneReadRequest> &req);

	ResponseStatus response_success(const Response<XZoneReadRequest> &res);
}
#endif
