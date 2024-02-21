#pragma once
#include "CtrlrMacros.h"

class CtrlrLuaMethodEditor;

class CtrlrLuaMethodDebuggerVars  : public Component,
                                    public TableListBoxModel
{
public:

    CtrlrLuaMethodDebuggerVars (CtrlrLuaMethodEditor &_owner);
    ~CtrlrLuaMethodDebuggerVars();

    struct Variable
    {
        String varName;
        String varType;
        var varValue;
    };

    int getNumRows();
    void paintRowBackground (Graphics &g, int rowNumber, int width, int height, bool rowIsSelected);
    void paintCell (Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected);
    void cellDoubleClicked (int rowNumber, int columnId, const MouseEvent &e);
    void setData (const String &data);
    void paint (Graphics& g);
    void resized();

private:

    CtrlrLuaMethodEditor &owner;
    Array <Variable> currentVars;
    ScopedPointer<TableListBox> valueList;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrLuaMethodDebuggerVars)
};