#pragma once
#include "CtrlrMacros.h"
#include "CtrlrLuaMethodDebuggerStackTrace.h"
#include "CtrlrLuaMethodDebuggerVars.h"

class CtrlrLuaMethodEditor;

class CtrlrLuaMethodDebuggerPrompt  : public Component,
                                      public TextEditor::Listener,
									  public Button::Listener
{
public:

    CtrlrLuaMethodDebuggerPrompt (CtrlrLuaMethodEditor &_owner);
    ~CtrlrLuaMethodDebuggerPrompt();

    enum CollectionState
    {
        Ended,
        Trace,
        Values
    };
    void insertRawDebuggerOutput(const String &debuggerOutput);
    void sendCommand (const String &text);
    void textEditorReturnKeyPressed (TextEditor &editor);
    StringArray &getCommandQueue();
    const String getCurrentDebuggerCommand(const bool clearTheReturnedCommand=true);
    void visibilityChanged();
    void insertToOutput(const String &what, const Colour textColour=Colour (0xff5c5c5c));
    void finishDataCollection();
    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);

private:

    CtrlrLuaMethodEditor &owner;
    StringArray commandQueue;
    StretchableLayoutManager layoutManager;
	ScopedPointer <StretchableLayoutResizerBar> resizer;
	CollectionState collectionState;
	String collectedData;
	CtrlrLuaMethodDebuggerStackTrace *stackTracePanel;
    CtrlrLuaMethodDebuggerVars *varsPanel;
    ScopedPointer<TextEditor> debuggerOutput;
    ScopedPointer<TextEditor> debuggerInput;
    ScopedPointer<ImageButton> debugContinue;
    ScopedPointer<ImageButton> debugStepOver;
    ScopedPointer<ImageButton> debugStepInto;
    ScopedPointer<ConcertinaPanel> debuggerInfo;
    ScopedPointer<ImageButton> debugStepOut;
    ScopedPointer<ImageButton> debugRestart;
    ScopedPointer<ImageButton> debugStop;
	ScopedPointer<ImageButton> clearOutput;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrLuaMethodDebuggerPrompt)
};