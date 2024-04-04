#pragma once

extern  "C"
{
	#include "lua.h"
}

class LAffineTransform
{
	public:
		static void wrapForLua (lua_State *L);
};