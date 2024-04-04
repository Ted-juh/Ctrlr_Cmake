#pragma once

extern  "C"
{
	#include "lua.h"
}

class LLabel
{
	public:
		static void wrapForLua (lua_State *L);
};