#include "stdafx.h"
#include "CtrlrInlineUtilitiesGUI.h"
#include "CtrlrLuaMethodDebuggerVars.h"

CtrlrLuaMethodDebuggerVars::CtrlrLuaMethodDebuggerVars (CtrlrLuaMethodEditor &_owner)
    : owner(_owner)
{
    addAndMakeVisible (valueList = new TableListBox());
    setName ("Variables");
    valueList->setModel (this);
    valueList->getHeader().addColumn ("Name", 1, 120, 120, -1);
    valueList->getHeader().addColumn ("Type", 2, 120, 120, -1);
    valueList->getHeader().addColumn ("Value", 3, 140, 140, -1);

    setSize (600, 400);
}

CtrlrLuaMethodDebuggerVars::~CtrlrLuaMethodDebuggerVars()
{
    valueList = nullptr;
}

void CtrlrLuaMethodDebuggerVars::paint (Graphics& g)
{
    g.fillAll (Colours::white);
}

void CtrlrLuaMethodDebuggerVars::resized()
{
    valueList->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
}

void CtrlrLuaMethodDebuggerVars::setData (const String &data)
{
    var result;
    JSON::parse ("{" + data + "}", result);

    if (result.isObject())
    {
        currentVars.clear();

        DynamicObject *o = result.getDynamicObject();

        if (o)
        {
            if (o->getProperty(o->getProperties().getName(0)).isObject())
            {
                DynamicObject *variables = o->getProperty(o->getProperties().getName(0)).getDynamicObject();
                if (variables)
                {
                    for (int i=0; i<variables->getProperties().size(); i++)
                    {
                        Variable v;
                        if (variables->getProperties().getName(i).toString() == "table")
                            continue;

                        v.varName   = variables->getProperties().getName(i).toString();
                        if (variables->getProperties().getValueAt(i).isObject())
                        {
                            DynamicObject *varDesc = variables->getProperties().getValueAt(i).getDynamicObject();

                            if (varDesc->getProperties().getName(0).toString() == "userdata")
                            {
                                if (isupper (varDesc->getProperties().getValueAt(0).toString()[0]))
                                {
                                    v.varType = _STR ("(" + varDesc->getProperties().getValueAt(0).toString() + ")");
                                }
                                else
                                {
                                    v.varType = varDesc->getProperties().getValueAt(0);
                                }
                            }
                            else if (varDesc->getProperties().getName(0).toString() == "table")
                            {
                                v.varType   = varDesc->getProperties().getName(0).toString();
                                v.varValue  = _STR("["+varDesc->getProperties().getValueAt(0).toString()+"]");
                            }
                            else
                            {
                                v.varType   = varDesc->getProperties().getName(0).toString();
                                v.varValue  = varDesc->getProperties().getValueAt(0);
                            }
                        }
                        else
                        {
                            v.varValue = variables->getProperties().getValueAt(i);
                        }

                        currentVars.add (v);
                    }
                }

                valueList->updateContent();
            }
        }
    }
}

void CtrlrLuaMethodDebuggerVars::paintRowBackground (Graphics &g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected)
    {
        gui::drawSelectionRectangle(g, width, height);
    }
    else
    {
        g.fillAll (Colours::white);
    }
}

void CtrlrLuaMethodDebuggerVars::paintCell (Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    if (columnId == 1)
        g.drawText (currentVars[rowNumber].varName, 0, 0, width, height, Justification::left, true);

    if (columnId == 2)
        g.drawText (currentVars[rowNumber].varType, 0, 0, width, height, Justification::left, true);

    if (columnId == 3)
        g.drawText (currentVars[rowNumber].varValue.toString(), 0, 0, width, height, Justification::left, true);
}

void CtrlrLuaMethodDebuggerVars::cellDoubleClicked (int rowNumber, int columnId, const MouseEvent &e)
{
}

int CtrlrLuaMethodDebuggerVars::getNumRows()
{
    return (currentVars.size());
}