#pragma once

extern  "C"
{
	#include "lua.h"
}

class LExpression
{
	public:
		static void wrapForLua (lua_State *L);
};