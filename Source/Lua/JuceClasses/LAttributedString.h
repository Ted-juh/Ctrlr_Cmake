#pragma once

extern  "C"
{
	#include "lua.h"
}

class LAttributedString
{
	public:
		static void wrapForLua (lua_State *L);
};