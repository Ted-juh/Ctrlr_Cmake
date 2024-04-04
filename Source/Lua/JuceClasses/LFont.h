#pragma once

extern  "C"
{
	#include "lua.h"
}

class LFont : public Font
{
	public:
		static void wrapForLua (lua_State *L);
};