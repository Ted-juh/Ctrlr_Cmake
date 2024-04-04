#pragma once

extern  "C"
{
	#include "lua.h"
}

class LJustification
{
	public:
		static void wrapForLua (lua_State *L);
};