#pragma once

extern  "C"
{
	#include "lua.h"
}

class LColourGradient
{
	public:
		static void wrapForLua (lua_State *L);
};