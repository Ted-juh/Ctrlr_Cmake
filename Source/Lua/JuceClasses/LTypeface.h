#pragma once

extern  "C"
{
	#include "lua.h"
}

class LTypeface
{
	public:
		static void wrapForLua (lua_State *L);
};