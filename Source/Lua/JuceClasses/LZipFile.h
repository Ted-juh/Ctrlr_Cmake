#pragma once
extern  "C"
{
	#include "lua.h"
}

class LZipEntry
{
	public:
		static void wrapForLua (lua_State *L);
};

class LZipFile
{
	public:
		static void wrapForLua (lua_State *L);
};