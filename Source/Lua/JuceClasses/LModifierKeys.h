#pragma once

extern  "C"
{
	#include "lua.h"
}

class LModifierKeys
{
	public:
		static void wrapForLua (lua_State *L);
};