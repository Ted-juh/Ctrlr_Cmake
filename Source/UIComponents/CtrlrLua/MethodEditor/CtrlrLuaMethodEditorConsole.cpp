#include "stdafx.h"
#include "CtrlrLuaMethodEditorConsole.h"

CtrlrLuaMethodEditorConsole::CtrlrLuaMethodEditorConsole (CtrlrLuaMethodEditor &_owner)
    : owner(_owner)
{
    setSize (600, 400);
}

CtrlrLuaMethodEditorConsole::~CtrlrLuaMethodEditorConsole()
{
}

void CtrlrLuaMethodEditorConsole::paint (Graphics& g)
{
    g.fillAll (Colours::white);
}

void CtrlrLuaMethodEditorConsole::resized()
{
}