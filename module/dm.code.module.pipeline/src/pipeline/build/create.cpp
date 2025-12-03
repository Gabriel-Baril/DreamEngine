#include "create.h"

#if USING(DM_DREAMLIKE_BUILD)
#include "pipeline/cache.h"
#include "pipeline/xasset/util.h"
#include "pipeline/xbuildconfig/read.h"
#include "pipeline/xfeature/read.h"

namespace dm
{
	void request_handle(const Request<DreamlikeBuildCreateRequest> &req, Response<DreamlikeBuildCreateRequest>& res)
	{
		Request<XBuildConfigReadRequest> buildconfigReq;
		buildconfigReq.set_symbol(req.builconfigSym);
		Response<XBuildConfigReadRequest> buildconfigRes;
		request_send(buildconfigReq, buildconfigRes);

		if (!buildconfigRes.data.valid())
		{
			res.set_build_status(BuildStatus::FAILED);
			return;
		}

		const auto* vec = buildconfigRes.data->features();
		if (!vec)
		{
			res.set_build_status(BuildStatus::FAILED);
			return;
		}

		for (flatbuffers::uoffset_t i = 0; i < vec->size(); ++i)
		{
			const char* featureName = vec->Get(i)->c_str();
			if (!featureName)
			{
				continue;
			}

			sym_t featureSym = featureName;
			Request<XFeatureReadRequest> featureReq;
			featureReq.set_symbol(featureSym);
			Response<XFeatureReadRequest> featureRes;
			request_send(featureReq, featureRes);

			if (featureRes.data.valid())
			{
				DM_INFO_LOG("Failed to find feature '{0}'", featureName);
				continue;
			}
		}
		res.set_build_status(BuildStatus::SUCCESS);
	}									   

	const char *requet_get_type_name(const Request<DreamlikeBuildCreateRequest> &req)
	{
		DM_MAYBE_UNUSED(req);
		return DM_NAMEOF(XBuildConfigReadRequest);
	}

	bool request_valid(const Request<DreamlikeBuildCreateRequest> &req)
	{
		DM_MAYBE_UNUSED(req);
		return true;
	}

	u64 request_get_id(const Request<DreamlikeBuildCreateRequest> &req)
	{
		HashBuilder hb;
		hb.add_type<DreamlikeBuildCreateRequest>();
		hb.add(static_cast<u64>(req.builconfigSym));
		return hb.get();
	}

	i32 request_get_slug(const Request<DreamlikeBuildCreateRequest> &req, char *buffer, u64 count)
	{
		DM_MAYBE_UNUSED(req);
		DM_MAYBE_UNUSED(buffer);
		DM_MAYBE_UNUSED(count);
		DM_CORE_UNIMPLEMENTED();
		return 0;
	}

	ResponseStatus response_success(const Response<DreamlikeBuildCreateRequest> &res)
	{
		return res.buildStatus == BuildStatus::SUCCESS ? ResponseStatus::SUCCESS : ResponseStatus::FAILED;
	}
}
#endif
