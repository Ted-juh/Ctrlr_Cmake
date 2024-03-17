#pragma once
#ifdef _WIN32
#pragma warning(disable:4100)
#endif // _WIN32
#include "luabind/object_fwd.hpp"
extern "C"
{
#include "lua.h"
}

struct LuaTimerCallback
{
	bool isValid;
	luabind::object o;
};

class CtrlrLuaMultiTimer : public MultiTimer
{
	public:
		CtrlrLuaMultiTimer();
		~CtrlrLuaMultiTimer();

		static void wrapForLua(lua_State *L);
		void timerCallback(int timerId);
		void setCallback (const int timerId, luabind::object callback);
		void startTimer (const int timerId, const int interval);
		const bool isRegistered(const int timerId);
		void stopTimer (const int timerId);
		const bool isTimerRunning (const int timerId);
		const int getTimerInterval(const int timerId);

	private:
		HashMap <int, LuaTimerCallback> callbacks;
};