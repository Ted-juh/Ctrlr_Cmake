#pragma once
#include "CtrlrMacros.h"

class CtrlrLuaMethodEditor;

class CtrlrLuaMethodDebuggerStackTrace  : public Component,
                                          public TableListBoxModel
{
public:

    CtrlrLuaMethodDebuggerStackTrace (CtrlrLuaMethodEditor &_owner);
    ~CtrlrLuaMethodDebuggerStackTrace();

    struct StackFrame
    {
        int lineNumber;
        int positionOnTheStack;
        String methodName;
        String scriptName;
        bool isCurrent;
    };
    void setData (const String &data);
    int getNumRows();
    void paintRowBackground (Graphics &g, int rowNumber, int width, int height, bool rowIsSelected);
    void paintCell (Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected);
    void cellDoubleClicked (int rowNumber, int columnId, const MouseEvent &e);
    StackFrame getStackFrame(const String &stackTraceInfoAsString);
    void paint (Graphics& g);
    void resized();

private:
    CtrlrLuaMethodEditor &owner;
    StringArray traceLines;
    Array<StackFrame> currentFrames;
    ScopedPointer<TableListBox> stackTraceList;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrLuaMethodDebuggerStackTrace)
};