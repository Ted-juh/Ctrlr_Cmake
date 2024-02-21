#pragma once
#include "CtrlrMacros.h"

class CtrlrLuaMethodEditor;

class CtrlrLuaMethodDebuggerInfo  : public Component
{
public:

    CtrlrLuaMethodDebuggerInfo (CtrlrLuaMethodEditor &_owner);
    ~CtrlrLuaMethodDebuggerInfo();

    void paint (Graphics& g);
    void resized();

private:
    CtrlrLuaMethodEditor &owner;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrLuaMethodDebuggerInfo)
};