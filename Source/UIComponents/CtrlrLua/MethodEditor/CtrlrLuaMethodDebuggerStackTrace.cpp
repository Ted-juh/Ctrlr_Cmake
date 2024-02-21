#include "stdafx.h"
#include "CtrlrInlineUtilitiesGUI.h"
#include "CtrlrLuaMethodEditor.h"
#include "CtrlrLuaMethodDebuggerStackTrace.h"

CtrlrLuaMethodDebuggerStackTrace::CtrlrLuaMethodDebuggerStackTrace (CtrlrLuaMethodEditor &_owner)
    : owner(_owner)
{
    addAndMakeVisible (stackTraceList = new TableListBox());

    stackTraceList->setModel (this);
    stackTraceList->getHeader().addColumn ("No", 1, 30, 30, -1, TableHeaderComponent::notSortable);
    stackTraceList->getHeader().addColumn ("Script", 2, 120, 120, -1, TableHeaderComponent::notSortable);
    stackTraceList->getHeader().addColumn ("Method", 3, 150, 150, -1, TableHeaderComponent::notSortable);
    stackTraceList->getHeader().addColumn ("Line", 4, 40, 40, -1, TableHeaderComponent::notSortable);
    setName ("Stack trace");

    setSize (600, 400);
}

CtrlrLuaMethodDebuggerStackTrace::~CtrlrLuaMethodDebuggerStackTrace()
{
    stackTraceList = nullptr;
}

//==============================================================================
void CtrlrLuaMethodDebuggerStackTrace::paint (Graphics& g)
{
    g.fillAll (Colours::white);
}

void CtrlrLuaMethodDebuggerStackTrace::resized()
{
    stackTraceList->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
}

void CtrlrLuaMethodDebuggerStackTrace::setData(const String &data)
{
    traceLines = StringArray::fromLines (data);
    currentFrames.clear();

    for (int i=0; i<traceLines.size(); i++)
    {
        if (!traceLines[i].trim().isEmpty())
            currentFrames.add (getStackFrame(traceLines[i]));
    }

    stackTraceList->updateContent ();
}

CtrlrLuaMethodDebuggerStackTrace::StackFrame CtrlrLuaMethodDebuggerStackTrace::getStackFrame(const String &stackTraceInfoAsString)
{
    CtrlrLuaMethodDebuggerStackTrace::StackFrame frame;
    StringArray tokens = StringArray::fromTokens (stackTraceInfoAsString, " \t", "\"'");

    frame.positionOnTheStack    = tokens[0].fromFirstOccurrenceOf("[", false, true).getIntValue();
    frame.methodName            = tokens[1].trim();
    frame.scriptName            = tokens[4].upToFirstOccurrenceOf("]", false, true).unquoted();
    frame.lineNumber            = tokens[4].fromFirstOccurrenceOf(":", false, true).getIntValue();
    frame.isCurrent             = tokens[0].contains("*");

    return (frame);
}

int CtrlrLuaMethodDebuggerStackTrace::getNumRows()
{
    return (currentFrames.size());
}

void CtrlrLuaMethodDebuggerStackTrace::paintRowBackground (Graphics &g, int rowNumber, int width, int height, bool rowIsSelected)
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

void CtrlrLuaMethodDebuggerStackTrace::paintCell (Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    g.setColour (Colours::black);

    if (currentFrames[rowNumber].isCurrent)
        g.setFont (Font (12.0f, Font::bold));
    else
        g.setFont (Font (12.0f, Font::plain));

    if (columnId == 1)
        g.drawText (_STR(currentFrames[rowNumber].positionOnTheStack), 0, 0, width, height, Justification::left, true);

    if (columnId == 2)
        g.drawText (currentFrames[rowNumber].scriptName, 0, 0, width, height, Justification::left, true);

    if (columnId == 3)
        g.drawText (currentFrames[rowNumber].methodName, 0, 0, width, height, Justification::left, true);

    if (columnId == 4)
        g.drawText (_STR(currentFrames[rowNumber].lineNumber), 0, 0, width, height, Justification::left, true);
}

void CtrlrLuaMethodDebuggerStackTrace::cellDoubleClicked (int rowNumber, int columnId, const MouseEvent &e)
{
    // int Ctrlr a script == a method, but there can be any functions/methods withing scripts
    // we can go only as far as a METHOD in ctrlr, that is those defined as internal methods
    // we can't really search for individual functions in all METHODS of Ctrlr
    owner.highlightCode (currentFrames[rowNumber].scriptName, currentFrames[rowNumber].lineNumber);
}