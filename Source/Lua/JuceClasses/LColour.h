#pragma once

extern  "C"
{
	#include "lua.h"
}

class LColour
{
	public:
		static void wrapForLua (lua_State *L);
};