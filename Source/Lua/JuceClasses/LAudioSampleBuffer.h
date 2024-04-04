#pragma once

extern  "C"
{
	#include "lua.h"
}

class LAudioSampleBuffer
{
	public:
		static void wrapForLua (lua_State *L);
};