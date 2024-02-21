#include "stdafx.h"
#include "CtrlrLuaManager.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrLuaConsole.h"

const StringArray joinFileArray (const Array<File> ar)
{
	StringArray s;

	for (int i=0; i<ar.size(); i++)
	{
		s.add (ar[i].getFullPathName());
	}
	return (s);
}

CtrlrLuaConsole::CtrlrLuaConsole (CtrlrPanel &_owner)
    : owner(_owner),
      luaConsoleOutput (0),
      luaConsoleInput (0),
      resizer (0)
{
    addAndMakeVisible (luaConsoleOutput = new CodeEditorComponent (outputDocument, 0));
    luaConsoleOutput->setName (L"luaConsoleOutput");
    luaConsoleOutput->setScrollbarThickness(owner.getOwner().getProperty(Ids::ctrlrScrollbarThickness));

    addAndMakeVisible (luaConsoleInput = new CodeEditorComponent (inputDocument, 0));
    luaConsoleInput->setName (L"luaConsoleInput");
    luaConsoleInput->setScrollbarThickness(owner.getOwner().getProperty(Ids::ctrlrScrollbarThickness));

    addAndMakeVisible (resizer = new StretchableLayoutResizerBar (&layoutManager, 1, false));

	layoutManager.setItemLayout (0, -0.001, -1.0, -0.69);
 	layoutManager.setItemLayout (1, -0.001, -0.01, -0.01);
 	layoutManager.setItemLayout (2, -0.001, -1.0, -0.30);

	luaConsoleInput->setFont (Font(owner.getCtrlrManagerOwner().getFontManager().getDefaultMonoFontName(), 15, Font::plain));
	luaConsoleOutput->setFont (Font(owner.getCtrlrManagerOwner().getFontManager().getDefaultMonoFontName(), 15, Font::plain));
	luaConsoleInput->setColour (CodeEditorComponent::backgroundColourId, Colour(0xffffffff));
	luaConsoleOutput->setColour (CodeEditorComponent::backgroundColourId, Colour(0xffffffff));

	luaConsoleInput->addKeyListener (this);
	owner.getCtrlrManagerOwner().getCtrlrLog().addListener (this);
	nextUpKeyPressWillbeFirst = true;
	lastCommandNumInHistory = -1;
	lastMoveDirection = NONE;
	currentInputString = "";

	setSize (600, 400);
	
	snips.addTokens (owner.getProperty(Ids::uiLuaConsoleSnips).toString(), "$", "\'\"");
}

CtrlrLuaConsole::~CtrlrLuaConsole()
{
	owner.getCtrlrManagerOwner().getCtrlrLog().removeListener (this);
    deleteAndZero (luaConsoleOutput);
    deleteAndZero (luaConsoleInput);
    deleteAndZero (resizer);
}

void CtrlrLuaConsole::paint (Graphics& g)
{
}

void CtrlrLuaConsole::resized()
{
    luaConsoleOutput->setBounds (0, 0, getWidth() - 0, proportionOfHeight (0.6900f));
    luaConsoleInput->setBounds (0, proportionOfHeight (0.7000f), getWidth() - 0, proportionOfHeight (0.3000f));
    resizer->setBounds (0, proportionOfHeight (0.6900f), getWidth() - 0, proportionOfHeight (0.0100f));
	Component* comps[] = { luaConsoleOutput, resizer, luaConsoleInput  };
 	layoutManager.layOutComponents (comps, 3, 0, 0, getWidth(), getHeight(), true, true);
}

bool CtrlrLuaConsole::keyPressed (const KeyPress& key)
{
    return false;  // Return true if your handler uses this key event, or false to allow it to be passed-on.
}

bool CtrlrLuaConsole::keyPressed (const KeyPress& key, Component* originatingComponent)
{
	if (key.getKeyCode() == 13 && originatingComponent == luaConsoleInput && !key.getModifiers().isCtrlDown())
	{
		runCode(inputDocument.getAllContent());

		if ((bool)owner.getProperty(Ids::uiLuaConsoleInputRemoveAfterRun))
		{
			inputDocument.replaceAllContent("");
		}
		return (true);
	}
	else if (key.getKeyCode() == 13 && originatingComponent == luaConsoleInput && key.getModifiers().isCtrlDown())
	{
		luaConsoleInput->insertTextAtCaret ("\n");
		return (true);
	}
	else if (key.getKeyCode() == KeyPress::upKey && key.getModifiers().isCtrlDown() && originatingComponent == luaConsoleInput )
	{
		if(inputHistory.size())
		{
			// Prev command
			if (nextUpKeyPressWillbeFirst) {
				currentInputString = inputDocument.getAllContent();
				nextUpKeyPressWillbeFirst = false;
			}

			luaConsoleInput->loadContent(inputHistory[lastCommandNumInHistory]);  /* Put text at pointer into console */
			lastCommandNumInHistory = ( ((lastCommandNumInHistory - 1) < 0) ? 0 : (lastCommandNumInHistory - 1) );
			lastMoveDirection = UP;
		}
		return (true);
	}
	else if (key.getKeyCode() == KeyPress::downKey && key.getModifiers().isCtrlDown() && originatingComponent == luaConsoleInput)
	{
		if(inputHistory.size())
		{
			// next command
			if (lastCommandNumInHistory == (inputHistory.size() - 1)) // at last command only
			{
				if (!currentInputString.isEmpty()) {
					luaConsoleInput->loadContent(currentInputString);
					nextUpKeyPressWillbeFirst = true;              // if user changes this restored text we need to capture it at up key again
				}
				return true;
			}
			lastCommandNumInHistory += 1;
			luaConsoleInput->loadContent(inputHistory[lastCommandNumInHistory]);  /* Put text at pointer into console */
			lastMoveDirection = DOWN;
		}
		return (true);
	}
	return (false);
}

void CtrlrLuaConsole::runCode(const String &code)
{
	luaConsoleOutput->moveCaretToEnd(false);
	luaConsoleOutput->insertTextAtCaret ("\n");
	luaConsoleOutput->insertTextAtCaret (">>> " + code + "\n");
	// add running code into history
	if (code.isNotEmpty()){
		inputHistory.addIfNotAlreadyThere(code);
		nextUpKeyPressWillbeFirst = true;
		lastCommandNumInHistory = inputHistory.size() - 1;
		lastMoveDirection = NONE;
		currentInputString = "";
	}
	owner.getCtrlrLuaManager().runCode(code);
	// luaConsoleInput->clear();
}

void CtrlrLuaConsole::messageLogged (CtrlrLog::CtrlrLogMessage message)
{
	if (message.level == CtrlrLog::Lua)
	{
		// luaConsoleOutput->setCaretPosition (luaConsoleOutput->getText().length());
		luaConsoleOutput->insertTextAtCaret (message.message + "\n");
	}
	if (message.level == CtrlrLog::LuaError)
	{
		// luaConsoleOutput->setCaretPosition (luaConsoleOutput->getText().length());
		luaConsoleOutput->insertTextAtCaret (message.message + "\n");
	}
}

const PopupMenu CtrlrLuaConsole::getSnipsMenu(const int mask)
{
	PopupMenu m;

	for (int i=0; i<snips.size(); i++)
	{
		m.addItem (mask+i, snips[i]);
	}

	return (m);
}

void CtrlrLuaConsole::snipsItemClicked(Button *b)
{
	PopupMenu m;
	m.addItem (1, "Add input to snips");
	m.addSubMenu ("Run snip", getSnipsMenu(1024));
	m.addSubMenu ("Remove snip", getSnipsMenu(4096));
	m.addItem (2, "Toggle input removal after run", true, (bool)owner.getProperty(Ids::uiLuaConsoleInputRemoveAfterRun));
	const int ret = m.showAt(b);

	if (ret == 1)
	{
		snips.add (inputDocument.getAllContent());
	}
	if (ret >= 1024 && ret < 4096)
	{
		runCode (snips[ret-1024]);
	}
	if (ret >= 4096)
	{
		snips.remove (ret-4096);
	}
	if (ret == 2)
	{
		owner.setProperty (Ids::uiLuaConsoleInputRemoveAfterRun, !owner.getProperty(Ids::uiLuaConsoleInputRemoveAfterRun));
	}
	owner.setProperty (Ids::uiLuaConsoleSnips, snips.joinIntoString("$"));
}

StringArray CtrlrLuaConsole::getMenuBarNames()
{
	const char* const names[] = { "File", "View", nullptr };
	return StringArray (names);
}

PopupMenu CtrlrLuaConsole::getMenuForIndex(int topLevelMenuIndex, const String &menuName)
{
	PopupMenu menu;
	if (topLevelMenuIndex == 0)
	{
		menu.addItem (2, "Add input to snips");
		menu.addSubMenu ("Run snip", getSnipsMenu(1024));
		menu.addSubMenu ("Remove snip", getSnipsMenu(4096));
		menu.addSeparator();
		menu.addItem (1, "Close");
	}
	else if(topLevelMenuIndex == 1)
	{
		menu.addItem (3, "Toggle input removal after run", true, (bool)owner.getProperty(Ids::uiLuaConsoleInputRemoveAfterRun));
	}

	return (menu);
}

void CtrlrLuaConsole::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
	if (topLevelMenuIndex == 0 && menuItemID==1)
	{
		owner.getWindowManager().toggle (CtrlrPanelWindowManager::LuaConsole, false);
	}
	if (menuItemID == 2)
	{
		snips.add (inputDocument.getAllContent());
	}
	if (menuItemID >= 1024 && menuItemID < 4096)
	{
		runCode (snips[menuItemID-1024]);
	}
	if (menuItemID >= 4096)
	{
		snips.remove (menuItemID-4096);
	}
	if (menuItemID == 3)
	{
		owner.setProperty (Ids::uiLuaConsoleInputRemoveAfterRun, !owner.getProperty(Ids::uiLuaConsoleInputRemoveAfterRun));
	}
	owner.setProperty (Ids::uiLuaConsoleSnips, snips.joinIntoString("$"));
}

void CtrlrLuaConsole::focusGained(FocusChangeType cause)
{
	luaConsoleInput->grabKeyboardFocus();
}