#pragma once

extern  "C"
{
	#include "lua.h"
}

class LBorderSize
{
	public:
		static void wrapForLua (lua_State *L);
};