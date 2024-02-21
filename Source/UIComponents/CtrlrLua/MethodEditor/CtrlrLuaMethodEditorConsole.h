#pragma once
#include "CtrlrMacros.h"

class CtrlrLuaMethodEditor;

class CtrlrLuaMethodEditorConsole  : public Component
{
public:
    CtrlrLuaMethodEditorConsole (CtrlrLuaMethodEditor &_owner);
    ~CtrlrLuaMethodEditorConsole();

    void paint (Graphics& g);
    void resized();

private:
    CtrlrLuaMethodEditor &owner;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrLuaMethodEditorConsole)
};