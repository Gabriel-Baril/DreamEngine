#include "read.h"

#if USING(DM_SYM_XZONE)
#include "pipeline/cache.h"

namespace dm
{
	Response<XZoneReadRequest> request_handle(const Request<XZoneReadRequest> &req)
	{
		Response<XZoneReadRequest> res;
		res.data = object_get(req.sig);
		return res;
	}

	const char *requet_get_type_name(const Request<XZoneReadRequest> &req)
	{
		DM_MAYBE_UNUSED(req);
		return DM_NAMEOF(XZoneReadRequest);
	}

	bool request_valid(const Request<XZoneReadRequest> &req)
	{
		DM_MAYBE_UNUSED(req);
		return true;
	}

	u64 request_get_id(const Request<XZoneReadRequest> &req)
	{
		HashBuilder hb;
		hb.add_type<XZoneReadRequest>();
		hb.add(object_get_id(req.sig));
		return hb.get();
	}

	i32 request_get_slug(const Request<XZoneReadRequest> &req, char *buffer, u64 count)
	{
		return request_get_generic_xasset_slug(req, buffer, count);
	}

	ResponseStatus response_success(const Response<XZoneReadRequest> &res)
	{
		return res.data.valid() ? ResponseStatus::SUCCESS : ResponseStatus::FAILED;
	}
}
#endif
