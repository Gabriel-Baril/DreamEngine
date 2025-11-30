#include "read.h"

#include "core/core_define.h"

#if USING(DM_SYM_XFEATURE)
#include "pipeline/cache.h"

namespace dm
{
	Response<XFeatureReadRequest> request_handle(const Request<XFeatureReadRequest> &req)
	{
		Response<XFeatureReadRequest> res;
		res.data = object_get(req.sig);
		return res;
	}

	const char *requet_get_type_name(const Request<XFeatureReadRequest> &req)
	{
		DM_MAYBE_UNUSED(req);
		return DM_NAMEOF(XFeatureReadRequest);
	}

	bool request_valid(const Request<XFeatureReadRequest> &req)
	{
		return true;
	}

	u64 request_get_id(const Request<XFeatureReadRequest> &req)
	{
		HashBuilder hb;
		hb.add_type<XFeatureReadRequest>();
		hb.add(object_get_id(req.sig));
		return hb.get();
	}

	i32 request_get_slug(const Request<XFeatureReadRequest> &req, char *buffer, u64 count)
	{
		return request_get_generic_xasset_slug(req, buffer, count);
	}

	ResponseStatus response_success(const Response<XFeatureReadRequest> &res)
	{
		return res.data.valid() ? ResponseStatus::SUCCESS : ResponseStatus::FAILED;
	}
}
#endif
