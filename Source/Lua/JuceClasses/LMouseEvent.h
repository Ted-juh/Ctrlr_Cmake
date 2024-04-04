#pragma once

extern  "C"
{
	#include "lua.h"
}

class LMouseEvent
{
	public:
		static void wrapForLua (lua_State *L);
};