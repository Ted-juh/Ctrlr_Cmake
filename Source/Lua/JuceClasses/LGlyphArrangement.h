#pragma once

extern  "C"
{
	#include "lua.h"
}

class LGlyphArrangement
{
	public:
		static void wrapForLua (lua_State *L);
};