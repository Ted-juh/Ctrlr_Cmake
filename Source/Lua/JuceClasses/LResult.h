#pragma once

extern  "C"
{
	#include "lua.h"
}

class LResult
{
	public:
		static void wrapForLua (lua_State *L);
};