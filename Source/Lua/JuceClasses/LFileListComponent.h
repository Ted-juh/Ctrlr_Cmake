#pragma once

extern  "C"
{
	#include "lua.h"
}

class LFileListComponent
{
	public:
		static void wrapForLua (lua_State *L);
};