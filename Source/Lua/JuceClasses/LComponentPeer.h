#pragma once

extern  "C"
{
	#include "lua.h"
}

class LComponentPeer
{
	public:
		static void wrapForLua (lua_State *L);
};