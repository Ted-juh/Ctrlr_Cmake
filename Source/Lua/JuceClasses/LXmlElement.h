#pragma once

extern  "C"
{
	#include "lua.h"
}

class LXmlElement
{
	public:
		static void wrapForLua (lua_State *L);
};