#pragma once

extern  "C"
{
	#include "lua.h"
}

class LURL
{
	public:
		static void wrapForLua (lua_State *L);
};