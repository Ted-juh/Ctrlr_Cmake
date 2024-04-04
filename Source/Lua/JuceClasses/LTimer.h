#pragma once

#include "stdafx_luabind.h"

class LTimer : public Timer
{
	public:
		LTimer()
		{}
		void timerCallback();
		void setCallback (luabind::object _callback);
		static void wrapForLua (lua_State *L);
	private:
		luabind::object callback;
};