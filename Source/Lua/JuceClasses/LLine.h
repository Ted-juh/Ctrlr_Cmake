#pragma once

extern  "C"
{
	#include "lua.h"
}

class LLine
{
	public:
		static void wrapForLua (lua_State *L);
};