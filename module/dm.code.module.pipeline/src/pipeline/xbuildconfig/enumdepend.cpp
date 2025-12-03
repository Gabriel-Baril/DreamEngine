#include "enumdepend.h"
#include "read.h"

namespace dm
{
	bool enumdepend_xbuildconfig(sym_t symbol, Response<XEnumDependRequest>& res)
	{
		Request<XBuildConfigReadRequest> buildconfigReq;
		buildconfigReq.set_symbol(symbol);
		Response<XBuildConfigReadRequest> buildconfigRes;
		request_send(buildconfigReq, buildconfigRes);

		if (!buildconfigRes.data.valid())
		{
			return false;
		}

		return true;
	}
}
