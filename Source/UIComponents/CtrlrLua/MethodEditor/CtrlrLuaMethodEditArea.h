#pragma once
#include "CtrlrLuaMethodEditorTabs.h"
#include "CtrlrLuaMethodFind.h"
#include "CtrlrTextEditor.h"
#include "CtrlrLuaMethodCodeEditor.h"
#include "CtrlrLuaMethodDebuggerPrompt.h"
#include "../CtrlrLuaConsole.h"

class CtrlrLuaMethodEditor;

class CtrlrLuaMethodEditArea  : public Component,
                                public CtrlrLog::Listener
{
public:

    CtrlrLuaMethodEditArea (CtrlrLuaMethodEditor &_owner);
    ~CtrlrLuaMethodEditArea();

	CtrlrLuaMethodEditorTabs *getTabs();
	TabbedComponent *getLowerTabs();
	void insertOutput(const String &textToInsert, const Colour what);
	void insertOutput(const AttributedString stringToInsert);
	void showFindDialog();
	void showDebuggerTab();
	void showConsoleTab();
	void findNextMatch();
	void replaceNextMatch();
	void closeTabWithMethod(const ValueTree &item);
	void messageLogged (CtrlrLog::CtrlrLogMessage message);
	void mouseDoubleClick (const MouseEvent &e);
	bool keyPressed (const KeyPress &key, Component *event);
	void setActiveOutputTab();
	CtrlrLuaMethodDebuggerPrompt *getLuaDebuggerPrompt(const bool activateDebuggerNow=false);
    void clearOutputText();
    void paint (Graphics& g);
    void resized();

private:

	CtrlrLuaMethodEditor &owner;
	StretchableLayoutManager layoutManager;
	StretchableLayoutResizerBar *resizer;
	CtrlrTextEditor *output;
	CtrlrLuaMethodFind *find;
	CtrlrLuaMethodDebuggerPrompt *debuggerPrompt;
	CtrlrLuaConsole *luaConsole;
    ScopedPointer<TabbedComponent> lowerTabs;
    ScopedPointer<CtrlrLuaMethodEditorTabs> upperTabs;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrLuaMethodEditArea)
};