#pragma once

extern  "C"
{
	#include "lua.h"
}

class LAudioThumbnail
{
	public:
		static void wrapForLua (lua_State *L);
};