#pragma once

extern  "C"
{
	#include "lua.h"
}

class LAudioPlayHead
{
	public:
		static void wrapForLua (lua_State *L);
};