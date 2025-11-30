#pragma once

#include "core/core_define.h"

#if USING(DM_SYM_XFEATURE)
#include "core/core.h"

#include "pipeline/xfeature/xasset.h"
#include "pipeline/request.h"
#include "pipeline/request_read_xasset.h"

namespace dm
{
	struct XFeatureReadRequest;

	template <>
	struct Request<XFeatureReadRequest>
	{
		DEFINE_XASSET_READ_CONSTRUCTORS(XFeatureAssetObject);

		Signature<XFeatureAssetObject> sig;
	};

	template <>
	struct Response<XFeatureReadRequest>
	{
		Handle<XFeatureAssetObject> data;
	};

	u64 request_get_id(const Request<XFeatureReadRequest> &req);
	i32 request_get_slug(const Request<XFeatureReadRequest> &, char *buffer, u64 count);
	Response<XFeatureReadRequest> request_handle(const Request<XFeatureReadRequest> &req);
	const char *requet_get_type_name(const Request<XFeatureReadRequest> &req);
	bool request_valid(const Request<XFeatureReadRequest> &req);
	ResponseStatus response_success(const Response<XFeatureReadRequest> &res);
}
#endif
