#pragma once

extern  "C"
{
	#include "lua.h"
}

class LValue
{
	public:
		static void wrapForLua (lua_State *L);
};