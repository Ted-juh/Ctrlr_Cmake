#pragma once

extern  "C"
{
	#include "lua.h"
}

class LButton
{
	public:
		static void wrapForLua (lua_State *L);
};