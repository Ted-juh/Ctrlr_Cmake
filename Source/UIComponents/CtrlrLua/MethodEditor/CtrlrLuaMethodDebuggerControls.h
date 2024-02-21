#pragma once
#include "JuceHeader.h"

class CtrlrLuaMethodDebuggerControls  : public Component
{
public:
    //==============================================================================
    CtrlrLuaMethodDebuggerControls ();
    ~CtrlrLuaMethodDebuggerControls();

    void paint (Graphics& g);
    void resized();

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrLuaMethodDebuggerControls)
};