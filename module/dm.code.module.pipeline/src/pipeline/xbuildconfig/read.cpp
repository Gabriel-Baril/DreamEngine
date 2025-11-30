#include "read.h"

#if USING(DM_SYM_XBUILDCONFIG)
#include "pipeline/cache.h"

namespace dm
{
	Response<XBuildConfigReadRequest> request_handle(const Request<XBuildConfigReadRequest> &req)
	{
		Response<XBuildConfigReadRequest> res;
		res.data = object_get(req.sig);
		return res;
	}

	const char *requet_get_type_name(const Request<XBuildConfigReadRequest> &req)
	{
		DM_MAYBE_UNUSED(req);
		return DM_NAMEOF(XBuildConfigReadRequest);
	}

	bool request_valid(const Request<XBuildConfigReadRequest> &req)
	{
		DM_MAYBE_UNUSED(req);
		return true;
	}

	u64 request_get_id(const Request<XBuildConfigReadRequest> &req)
	{
		HashBuilder hb;
		hb.add_type<XBuildConfigReadRequest>();
		hb.add(object_get_id(req.sig));
		return hb.get();
	}

	i32 request_get_slug(const Request<XBuildConfigReadRequest> &req, char *buffer, u64 count)
	{
		return request_get_generic_xasset_slug(req, buffer, count);
	}

	ResponseStatus response_success(const Response<XBuildConfigReadRequest> &res)
	{
		return res.data.valid() ? ResponseStatus::SUCCESS : ResponseStatus::FAILED;
	}
}
#endif
