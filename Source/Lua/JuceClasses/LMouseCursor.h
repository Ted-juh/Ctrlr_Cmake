#pragma once

extern  "C"
{
	#include "lua.h"
}

class LMouseCursor
{
	public:
		static void wrapForLua (lua_State *L);
};