#include "stdafx.h"
#include "CtrlrLuaMethodDebuggerInfo.h"

CtrlrLuaMethodDebuggerInfo::CtrlrLuaMethodDebuggerInfo (CtrlrLuaMethodEditor &_owner)
    : owner(_owner)
{
    setName ("Debug info");
    setSize (600, 400);
}

CtrlrLuaMethodDebuggerInfo::~CtrlrLuaMethodDebuggerInfo()
{
}

void CtrlrLuaMethodDebuggerInfo::paint (Graphics& g)
{
    g.fillAll (Colours::white);
}

void CtrlrLuaMethodDebuggerInfo::resized()
{
}