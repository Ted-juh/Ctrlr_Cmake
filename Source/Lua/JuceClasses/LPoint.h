#pragma once

extern  "C"
{
	#include "lua.h"
}

class LPoint
{
	public:
		static void wrapForLua (lua_State *L);
};