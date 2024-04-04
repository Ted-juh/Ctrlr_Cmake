#pragma once

extern  "C"
{
	#include "lua.h"
}

class LFileTreeComponent
{
	public:
		static void wrapForLua (lua_State *L);
};