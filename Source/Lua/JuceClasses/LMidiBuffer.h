#pragma once

extern  "C"
{
	#include "lua.h"
}

class LMidiBuffer
{
	public:
		static void wrapForLua (lua_State *L);
};