#pragma once

extern  "C"
{
	#include "lua.h"
}

class LAudioFile
{
	public:
		static void wrapForLua(lua_State *L);
};