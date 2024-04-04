#pragma once

extern  "C"
{
	#include "lua.h"
}

class LMidiKeyboardComponent
{
	public:
		static void wrapForLua (lua_State *L);
};