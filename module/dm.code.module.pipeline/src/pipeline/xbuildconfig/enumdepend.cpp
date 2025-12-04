#include "enumdepend.h"
#include "read.h"

namespace dm
{
	bool enumdepend_xbuildconfig(sym_t symbol, Response<XEnumDependTask>& res)
	{
		Request<XBuildConfigReadTask> buildconfigReq;
		buildconfigReq.set_symbol(symbol);
		Response<XBuildConfigReadTask> buildconfigRes;
		request_send(buildconfigReq, buildconfigRes);

		if (!buildconfigRes.data.valid())
		{
			return false;
		}

		return true;
	}
}
