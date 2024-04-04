#pragma once

extern  "C"
{
	#include "lua.h"
}

class LTextButton
{
	public:
		static void wrapForLua (lua_State *L);
};