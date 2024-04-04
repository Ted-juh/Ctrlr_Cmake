#pragma once

extern  "C"
{
	#include "lua.h"
}

class LRandom
{
	public:
		static void wrapForLua (lua_State *L);
};