#pragma once
#include "pipeline/sym.h"
#include "pipeline/build/enumdepend.h"

namespace dm
{
	bool enumdepend_xbuildconfig(sym_t symbol, Response<XEnumDependRequest>& res);
}