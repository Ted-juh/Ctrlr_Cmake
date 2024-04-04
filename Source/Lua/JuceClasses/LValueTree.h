#pragma once

extern  "C"
{
	#include "lua.h"
}

class LValueTree
{
	public:
		static void wrapForLua (lua_State *L);
};