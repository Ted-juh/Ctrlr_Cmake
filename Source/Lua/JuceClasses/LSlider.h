#pragma once

extern  "C"
{
	#include "lua.h"
}

class LSlider
{
	public:
		static void wrapForLua (lua_State *L);
};