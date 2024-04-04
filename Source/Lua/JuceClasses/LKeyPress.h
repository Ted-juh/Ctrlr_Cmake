#pragma once

#include "JuceHeader.h"
extern  "C"
{
	#include "lua.h"
}

class LKeyPress : public KeyPress
{
	public:
		LKeyPress() {}
		LKeyPress(int keyCode, const ModifierKeys &modifiers, juce_wchar textCharacter) : KeyPress(keyCode, modifiers, textCharacter) {}
		LKeyPress(int keyCode) : KeyPress(keyCode) {}
		static void wrapForLua (lua_State *L);
		int spaceKey;
};