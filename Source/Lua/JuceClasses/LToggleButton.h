#pragma once

extern  "C"
{
	#include "lua.h"
}

class LToggleButton
{
	public:
		static void wrapForLua (lua_State *L);
};