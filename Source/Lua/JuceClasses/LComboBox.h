#pragma once

extern  "C"
{
	#include "lua.h"
}

class LComboBox
{
	public:
		static void wrapForLua (lua_State *L);
};