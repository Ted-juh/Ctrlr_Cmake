#pragma once

extern  "C"
{
	#include "lua.h"
}

class LMidiMessage
{
	public:
		static void wrapForLua (lua_State *L);
};