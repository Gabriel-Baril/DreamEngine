#include "create.h"

#if USING(DM_DREAMLIKE_BUILD)
#include "pipeline/cache.h"
#include "pipeline/xasset/util.h"

#include "pipeline/xbuildconfig/read.h"
#include "pipeline/xfeature/read.h"

namespace dm
{
	void request_handle(const Request<BuildCreateTask> &req, Response<BuildCreateTask>& res)
	{
		Request<XBuildConfigReadTask> buildconfigReq;
		buildconfigReq.set_symbol(req.builconfigSym);
		Response<XBuildConfigReadTask> buildconfigRes;
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
			Request<XFeatureReadTask> featureReq;
			featureReq.set_symbol(featureSym);
			Response<XFeatureReadTask> featureRes;
			request_send(featureReq, featureRes);

			if (featureRes.data.valid())
			{
				DM_INFO_LOG("Failed to find feature '{0}'", featureName);
				continue;
			}
		}
		res.set_build_status(BuildStatus::SUCCESS);
	}									   

	const char *requet_get_type_name(const Request<BuildCreateTask> &req)
	{
		DM_MAYBE_UNUSED(req);
		return DM_NAMEOF(BuildCreateTask);
	}

	bool request_valid(const Request<BuildCreateTask> &req)
	{
		DM_MAYBE_UNUSED(req);
		return true;
	}

	u64 request_get_id(const Request<BuildCreateTask> &req)
	{
		HashBuilder hb;
		hb.add_type<BuildCreateTask>();
		hb.add(static_cast<u64>(req.builconfigSym));
		return hb.get();
	}

	i32 request_get_slug(const Request<BuildCreateTask> &req, char *buffer, u64 count)
	{
		DM_MAYBE_UNUSED(req);
		DM_MAYBE_UNUSED(buffer);
		DM_MAYBE_UNUSED(count);
		DM_CORE_UNIMPLEMENTED();
		return 0;
	}

	ResponseStatus response_success(const Response<BuildCreateTask> &res)
	{
		return res.buildStatus == BuildStatus::SUCCESS ? ResponseStatus::SUCCESS : ResponseStatus::FAILED;
	}
}
#endif
