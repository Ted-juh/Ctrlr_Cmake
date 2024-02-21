#include "stdafx.h"
#include "CtrlrLuaMethodDebuggerPrompt.h"
#include "CtrlrLuaMethodEditor.h"

CtrlrLuaMethodDebuggerPrompt::CtrlrLuaMethodDebuggerPrompt(CtrlrLuaMethodEditor& _owner)
    : owner(_owner)
{
    addAndMakeVisible(debuggerOutput = new TextEditor("Debugger output"));
    debuggerOutput->setMultiLine(true);
    debuggerOutput->setReturnKeyStartsNewLine(false);
    debuggerOutput->setReadOnly(true);
    debuggerOutput->setScrollbarsShown(true);
    debuggerOutput->setCaretVisible(false);
    debuggerOutput->setPopupMenuEnabled(true);
    debuggerOutput->setColour(TextEditor::textColourId, Colour(0xff5c5c5c));
    debuggerOutput->setColour(TextEditor::outlineColourId, Colour(0x00000000));
    debuggerOutput->setColour(TextEditor::shadowColourId, Colour(0x00000000));
    debuggerOutput->setText("");

    addAndMakeVisible(debuggerInput = new TextEditor("Debugger input"));
    debuggerInput->setMultiLine(false);
    debuggerInput->setReturnKeyStartsNewLine(false);
    debuggerInput->setReadOnly(false);
    debuggerInput->setScrollbarsShown(false);
    debuggerInput->setCaretVisible(true);
    debuggerInput->setPopupMenuEnabled(true);
    debuggerInput->setColour(TextEditor::highlightColourId, Colour(0x5b247c8d));
    debuggerInput->setColour(TextEditor::outlineColourId, Colour(0x8a000000));
    debuggerInput->setColour(TextEditor::shadowColourId, Colour(0x00000000));
    debuggerInput->setText("");

    addAndMakeVisible(debugContinue = new ImageButton("Continue"));
    debugContinue->setTooltip(TRANS("Continue"));
    debugContinue->addListener(this);

    debugContinue->setImages(false, true, true,
        Image(), 0.550f, Colour(0x00000000),
        Image(), 0.850f, Colour(0x00000000),
        Image(), 1.000f, Colour(0x00000000));
    addAndMakeVisible(debugStepOver = new ImageButton("Step Over"));
    debugStepOver->setTooltip(TRANS("Step Over"));
    debugStepOver->addListener(this);

    debugStepOver->setImages(false, true, true,
        Image(), 0.550f, Colour(0x00000000),
        Image(), 0.850f, Colour(0x00000000),
        Image(), 1.000f, Colour(0x00000000));
    addAndMakeVisible(debugStepInto = new ImageButton("Step Into"));
    debugStepInto->setTooltip(TRANS("Step Into"));
    debugStepInto->addListener(this);

    debugStepInto->setImages(false, true, true,
        Image(), 0.550f, Colour(0x00000000),
        Image(), 0.850f, Colour(0x00000000),
        Image(), 1.000f, Colour(0x00000000));
    addAndMakeVisible(debuggerInfo = new ConcertinaPanel());
    debuggerInfo->setExplicitFocusOrder(50);
    debuggerInfo->setName("Realtime information");

    addAndMakeVisible(debugStepOut = new ImageButton("Step Out"));
    debugStepOut->setTooltip(TRANS("Step Out"));
    debugStepOut->addListener(this);

    debugStepOut->setImages(false, true, true,
        Image(), 0.550f, Colour(0x00000000),
        Image(), 0.850f, Colour(0x00000000),
        Image(), 1.000f, Colour(0x00000000));
    addAndMakeVisible(debugRestart = new ImageButton("Restart"));
    debugRestart->setTooltip(TRANS("Restart"));
    debugRestart->addListener(this);

    debugRestart->setImages(false, true, true,
        Image(), 0.550f, Colour(0x00000000),
        Image(), 0.850f, Colour(0x00000000),
        Image(), 1.000f, Colour(0x00000000));
    addAndMakeVisible(debugStop = new ImageButton("Stop"));
    debugStop->setTooltip(TRANS("Stop"));
    debugStop->addListener(this);

    debugStop->setImages(false, true, true,
        Image(), 0.550f, Colour(0x00000000),
        Image(), 0.850f, Colour(0x00000000),
        Image(), 1.000f, Colour(0x00000000));

    addAndMakeVisible(clearOutput = new ImageButton("Clear"));
    clearOutput->setTooltip(TRANS("Clear"));
    clearOutput->addListener(this);

    clearOutput->setImages(false, true, true,
        Image(), 0.550f, Colour(0x00000000),
        Image(), 0.850f, Colour(0x00000000),
        Image(), 1.000f, Colour(0x00000000));

    collectionState = Ended;

    addAndMakeVisible(resizer = new StretchableLayoutResizerBar(&layoutManager, 1, true));

    layoutManager.setItemLayout(0, -0.001, -1.0, -0.59);
    layoutManager.setItemLayout(1, 8, 8, 8);
    layoutManager.setItemLayout(2, -0.001, -1.0, -0.39);

    debuggerInfo->addPanel(0, stackTracePanel = new CtrlrLuaMethodDebuggerStackTrace(owner), true);
    debuggerInfo->addPanel(1, varsPanel = new CtrlrLuaMethodDebuggerVars(owner), true);

    debuggerOutput->setFont(Font(Font::getDefaultMonospacedFontName(), 14.0f, Font::plain));
    debuggerInput->setFont(Font(Font::getDefaultMonospacedFontName(), 14.0f, Font::plain));
    debuggerInput->addListener(this);

    debugContinue->setImages(false, true, true,
        ImageCache::getFromMemory(BinaryData::play_svg, BinaryData::play_svgSize), 0.550f, Colour(0x00000000),
        ImageCache::getFromMemory(BinaryData::play_svg, BinaryData::play_svgSize), 0.850f, Colour(0x00000000),
        ImageCache::getFromMemory(BinaryData::play_svg, BinaryData::play_svgSize), 1.000f, Colour(0x00000000));
    debugContinue->setMouseCursor(MouseCursor::PointingHandCursor);

    debugStepInto->setImages(false, true, true,
        ImageCache::getFromMemory(BinaryData::appbar_debug_step_into_png, BinaryData::appbar_debug_step_into_pngSize), 0.550f, Colour(0x00000000),
        ImageCache::getFromMemory(BinaryData::appbar_debug_step_into_png, BinaryData::appbar_debug_step_into_pngSize), 0.850f, Colour(0x00000000),
        ImageCache::getFromMemory(BinaryData::appbar_debug_step_into_png, BinaryData::appbar_debug_step_into_pngSize), 1.000f, Colour(0x00000000));
    debugStepInto->setMouseCursor(MouseCursor::PointingHandCursor);

    debugStepOver->setImages(false, true, true,
        ImageCache::getFromMemory(BinaryData::appbar_debug_step_over_png, BinaryData::appbar_debug_step_over_pngSize), 0.550f, Colour(0x00000000),
        ImageCache::getFromMemory(BinaryData::appbar_debug_step_over_png, BinaryData::appbar_debug_step_over_pngSize), 0.850f, Colour(0x00000000),
        ImageCache::getFromMemory(BinaryData::appbar_debug_step_over_png, BinaryData::appbar_debug_step_over_pngSize), 1.000f, Colour(0x00000000));
    debugStepOver->setMouseCursor(MouseCursor::PointingHandCursor);

    debugRestart->setImages(false, true, true,
        ImageCache::getFromMemory(BinaryData::appbar_debug_restart_png, BinaryData::appbar_debug_restart_pngSize), 0.550f, Colour(0x00000000),
        ImageCache::getFromMemory(BinaryData::appbar_debug_restart_png, BinaryData::appbar_debug_restart_pngSize), 0.850f, Colour(0x00000000),
        ImageCache::getFromMemory(BinaryData::appbar_debug_restart_png, BinaryData::appbar_debug_restart_pngSize), 1.000f, Colour(0x00000000));
    debugRestart->setMouseCursor(MouseCursor::PointingHandCursor);

    debugStepOut->setImages(false, true, true,
        ImageCache::getFromMemory(BinaryData::appbar_debug_step_out_png, BinaryData::appbar_debug_step_out_pngSize), 0.550f, Colour(0x00000000),
        ImageCache::getFromMemory(BinaryData::appbar_debug_step_out_png, BinaryData::appbar_debug_step_out_pngSize), 0.850f, Colour(0x00000000),
        ImageCache::getFromMemory(BinaryData::appbar_debug_step_out_png, BinaryData::appbar_debug_step_out_pngSize), 1.000f, Colour(0x00000000));
    debugStepOut->setMouseCursor(MouseCursor::PointingHandCursor);

    debugStop->setImages(false, true, true,
        ImageCache::getFromMemory(BinaryData::stop_svg, BinaryData::stop_svgSize), 0.550f, Colour(0x00000000),
        ImageCache::getFromMemory(BinaryData::stop_svg, BinaryData::stop_svgSize), 0.850f, Colour(0x00000000),
        ImageCache::getFromMemory(BinaryData::stop_svg, BinaryData::stop_svgSize), 1.000f, Colour(0x00000000));
    debugStop->setMouseCursor(MouseCursor::PointingHandCursor);

    clearOutput->setImages(false, true, true,
        ImageCache::getFromMemory(BinaryData::cleanup_svg, BinaryData::cleanup_svgSize), 0.550f, Colour(0x00000000),
        ImageCache::getFromMemory(BinaryData::cleanup_svg, BinaryData::cleanup_svgSize), 0.850f, Colour(0x00000000),
        ImageCache::getFromMemory(BinaryData::cleanup_svg, BinaryData::cleanup_svgSize), 1.000f, Colour(0x00000000));
    clearOutput->setMouseCursor(MouseCursor::PointingHandCursor);

    setSize(600, 400);
}

CtrlrLuaMethodDebuggerPrompt::~CtrlrLuaMethodDebuggerPrompt()
{

    debuggerOutput = nullptr;
    debuggerInput = nullptr;
    debugContinue = nullptr;
    debugStepOver = nullptr;
    debugStepInto = nullptr;
    debuggerInfo = nullptr;
    debugStepOut = nullptr;
    debugRestart = nullptr;
    debugStop = nullptr;
	clearOutput = nullptr;
}

void CtrlrLuaMethodDebuggerPrompt::paint (Graphics& g)
{
}

void CtrlrLuaMethodDebuggerPrompt::resized()
{
    debuggerOutput->setBounds (0, 32, proportionOfWidth (0.7000f), getHeight() - 50);
    debuggerInput->setBounds (0, getHeight() - 18, getWidth() - 0, 18);
    debugContinue->setBounds (0, 0, 32, 32);
    debugStepOver->setBounds (40, 0, 32, 32);
    debugStepInto->setBounds (80, 0, 32, 32);
    debuggerInfo->setBounds (proportionOfWidth (0.7000f), 32, proportionOfWidth (0.3000f), getHeight() - 50);
    debugStepOut->setBounds (120, 0, 32, 32);
    debugRestart->setBounds (160, 0, 32, 32);
    debugStop->setBounds (200, 0, 32, 32);
	clearOutput->setBounds (240, 0, 32, 32);
    Component* comps[] = { debuggerOutput, resizer, debuggerInfo  };
	layoutManager.layOutComponents (comps, 3, 0, 32, getWidth(), getHeight() - 50, false, true);
}

void CtrlrLuaMethodDebuggerPrompt::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == debugContinue)
    {
        sendCommand ("run");
    }
    else if (buttonThatWasClicked == debugStepOver)
    {
         sendCommand ("over");
     }
    else if (buttonThatWasClicked == debugStepInto)
    {
         sendCommand ("step");
     }
    else if (buttonThatWasClicked == debugStepOut)
    {
         sendCommand ("out");
     }
    else if (buttonThatWasClicked == debugRestart)
    {
         sendCommand ("exit");
     }
    else if (buttonThatWasClicked == debugStop)
    {
    }
	else if (buttonThatWasClicked == clearOutput)
	{
		debuggerOutput->setText("");
	}
}

void CtrlrLuaMethodDebuggerPrompt::insertRawDebuggerOutput(const String &output)
{
    insertToOutput (output);

    if (output.contains("Paused at file"))
    {
        /* Debugger tells us we paused at some location in the code
            get the method name, and highlight the relevant code in
            the editor
        */
        const String file = output.fromFirstOccurrenceOf("Paused at file ", false, true).upToFirstOccurrenceOf(" ", false, true);
        const int line = output.fromFirstOccurrenceOf(" line ", false, true).getIntValue();

        owner.highlightCode (file, line);
    }

    if (output.contains ("::start trace"))
    {
        collectedData = "";
        collectionState = Trace;
        return;
    }

    if (output.contains ("::start dumpvar"))
    {
        collectedData = "";
        collectionState = Values;
        return;
    }

    if (output.contains("::end"))
    {
        finishDataCollection();
    }

    if (collectionState != Ended)
        collectedData << output;
}

void CtrlrLuaMethodDebuggerPrompt::finishDataCollection()
{
    switch (collectionState)
    {
        case Trace:
            stackTracePanel->setData(collectedData);
            break;
        case Values:
            varsPanel->setData(collectedData);
            break;
        default:
            break;
    }

    collectionState = Ended;
}

void CtrlrLuaMethodDebuggerPrompt::sendCommand (const String &command)
{
    if (owner.getParentComponent()->isCurrentlyModal())
    {
        commandQueue.add (command);

        insertToOutput (command.trim() + "\n", Colours::black);

        if (owner.getParentComponent()->isCurrentlyModal())
        {
            owner.getParentComponent()->exitModalState(1);
        }
    }
    else
    {
        _WRN("CtrlrLuaMethodDebuggerPrompt::sendCommand debugger is not active");
    }
}

void CtrlrLuaMethodDebuggerPrompt::textEditorReturnKeyPressed (TextEditor &editor)
{
    if (&editor == debuggerInput)
    {
        sendCommand (debuggerInput->getText());
        debuggerInput->clear();
    }
}

StringArray &CtrlrLuaMethodDebuggerPrompt::getCommandQueue()
{
    return (commandQueue);
}

const String CtrlrLuaMethodDebuggerPrompt::getCurrentDebuggerCommand(const bool clearTheReturnedCommand)
{
    if (commandQueue.size() <= 0)
        return ("");

    const String ret = commandQueue[commandQueue.size() - 1];
    commandQueue.remove (commandQueue.size() - 1);
    return (ret);
}

void CtrlrLuaMethodDebuggerPrompt::visibilityChanged()
{
    if (isVisible())
    {
        debuggerInput->grabKeyboardFocus ();
    }
}

void CtrlrLuaMethodDebuggerPrompt::insertToOutput(const String &what, Colour textColour)
{
    const Colour lastColourUsed = debuggerOutput->findColour(TextEditor::textColourId);

    debuggerOutput->setColour (TextEditor::textColourId, textColour);
    debuggerOutput->setCaretPosition (debuggerOutput->getText().length());
    debuggerOutput->insertTextAtCaret (what);
    debuggerOutput->setColour (TextEditor::textColourId, lastColourUsed);
}