#pragma once

extern  "C"
{
	#include "lua.h"
}

class LTextEditor
{
	public:
		static void wrapForLua (lua_State *L);
};