#include "stdafx.h"
#include "CtrlrIDs.h"
#include "CtrlrLuaMethodEditor.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrLuaMethodEditArea.h"

CtrlrLuaMethodEditArea::CtrlrLuaMethodEditArea (CtrlrLuaMethodEditor &_owner)
    : owner(_owner)
{
    addAndMakeVisible (lowerTabs = new TabbedComponent (TabbedButtonBar::TabsAtBottom));
    lowerTabs->setCurrentTabIndex (-1);

    addAndMakeVisible (upperTabs = new CtrlrLuaMethodEditorTabs (owner));


    //[UserPreSize]
	owner.getOwner().getCtrlrManagerOwner().getCtrlrLog().addListener (this);
	output						= new CtrlrTextEditor("Output");
	output->setFont (Font (owner.getOwner().getCtrlrManagerOwner().getFontManager().getDefaultMonoFontName(), 16.0f, Font::plain));
	output->setMultiLine(true, true);
	output->setReadOnly (true);
	output->addMouseListener (this, false);
	output->setColour (TextEditor::outlineColourId, Colours::transparentBlack);
	output->setColour (TextEditor::shadowColourId, Colours::transparentBlack);

	find						= new CtrlrLuaMethodFind(owner);
	addAndMakeVisible (resizer	= new StretchableLayoutResizerBar (&layoutManager, 1, false));
    debuggerPrompt              = new CtrlrLuaMethodDebuggerPrompt(owner);
	luaConsole                  = new CtrlrLuaConsole (owner.getOwner());

	lowerTabs->addTab ("Output", Colours::lightgrey, output, true);
	lowerTabs->addTab ("Find and replace", Colours::lightgrey, find, true);
    lowerTabs->addTab ("Debugger output", Colours::lightgrey, debuggerPrompt, true);
    lowerTabs->addTab ("Console", Colours::lightgrey, luaConsole, true);
	lowerTabs->setTabBarDepth(owner.getOwner().getOwner().getProperty(Ids::ctrlrTabBarDepth));

	layoutManager.setItemLayout (0, -0.001, -1.0, -0.79);
 	layoutManager.setItemLayout (1, -0.001, -0.01, -0.01);
 	layoutManager.setItemLayout (2, -0.001, -1.0, -0.19);

    setSize (600, 400);
}

CtrlrLuaMethodEditArea::~CtrlrLuaMethodEditArea()
{
	owner.getOwner().getCtrlrManagerOwner().getCtrlrLog().removeListener (this);
	deleteAndZero (resizer);

    lowerTabs = nullptr;
    upperTabs = nullptr;
}

void CtrlrLuaMethodEditArea::paint (Graphics& g)
{
}

void CtrlrLuaMethodEditArea::resized()
{
    lowerTabs->setBounds (0, proportionOfHeight (0.6995f), getWidth() - 0, proportionOfHeight (0.3005f));
    upperTabs->setBounds (0, 0, getWidth() - 0, proportionOfHeight (0.6995f));
	Component* comps[] = { upperTabs, resizer, lowerTabs  };
	layoutManager.layOutComponents (comps, 3, 0, 0, getWidth(), getHeight(), true, true);
}

void CtrlrLuaMethodEditArea::mouseDoubleClick (const MouseEvent &e)
{
	const String line = output->getLineAtPosition (output->getTextIndexAt (e.x, e.y)).trim();

	if (line.startsWithIgnoreCase("ERROR"))
	{
		const int errorInLine = line.fromFirstOccurrenceOf ("]:", false, true).getIntValue();

		if (errorInLine > 0 && owner.getCurrentEditor())
		{
			owner.getCurrentEditor()->setErrorLine(errorInLine);
		}
	}
	else if (line.startsWithIgnoreCase("Method: "))
	{
		const String methodName	= line.fromFirstOccurrenceOf ("Method: ", false, false).upToFirstOccurrenceOf("line: ", false, true).trim();
		const int errorInLine	= line.fromFirstOccurrenceOf ("line: ", false, true).getIntValue();
		const int positionStart	= line.fromFirstOccurrenceOf ("start: ", false,true).getIntValue();
		const int positionEnd	= line.fromFirstOccurrenceOf ("end: ", false,true).getIntValue();

		owner.searchResultClicked (methodName, errorInLine, positionStart, positionEnd);
	}
}

CtrlrLuaMethodEditorTabs *CtrlrLuaMethodEditArea::getTabs()
{
	return (upperTabs);
}

void CtrlrLuaMethodEditArea::insertOutput(const String &textToInsert, const Colour what)
{
	output->setCaretPosition(output->getText().length());
	output->insertText (textToInsert, Font (owner.getOwner().getCtrlrManagerOwner().getFontManager().getDefaultMonoFontName(), 16.0f, Font::plain), what);
}

void CtrlrLuaMethodEditArea::insertOutput(const AttributedString stringToInsert)
{
	output->setCaretPosition (output->getText().length() + 1);
	output->insertAttributedText(stringToInsert);
}

void CtrlrLuaMethodEditArea::showFindDialog()
{
	lowerTabs->setCurrentTabIndex (1, true);
	find->setFocusOnFindInput();
}

void CtrlrLuaMethodEditArea::showDebuggerTab()
{
	lowerTabs->setCurrentTabIndex (2, true);
}

void CtrlrLuaMethodEditArea::showConsoleTab()
{
	lowerTabs->setCurrentTabIndex (3, true);
}

void CtrlrLuaMethodEditArea::findNextMatch()
{
	find->findNextMatch();
}

void CtrlrLuaMethodEditArea::replaceNextMatch()
{
	find->replaceNextMatch();
}

void CtrlrLuaMethodEditArea::closeTabWithMethod(const ValueTree &item)
{
	for (int i=0; i<upperTabs->getNumTabs(); i++)
	{
		CtrlrLuaMethodCodeEditor *ed = dynamic_cast<CtrlrLuaMethodCodeEditor*>(upperTabs->getTabContentComponent(i));
		if (ed != nullptr)
		{
			if (ed->getMethod()->getUuid() == item.getProperty(Ids::uuid).toString())
			{
				upperTabs->removeTab (i);
				upperTabs->setCurrentTabIndex(i == 0 ? i+1 : i-1 , true);
				break;
			}
		}
	}
}

void CtrlrLuaMethodEditArea::messageLogged (CtrlrLog::CtrlrLogMessage message)
{
	if (message.level == CtrlrLog::Lua)
	{
		output->insertText ("LUA>> "+message.message+"\n", Font (owner.getOwner().getCtrlrManagerOwner().getFontManager().getDefaultMonoFontName(), 16.0f, Font::plain), Colours::black);
	}

	if (message.level == CtrlrLog::LuaRuntimeError)
	{
		output->insertText ("RUNTIME ERROR>> "+message.message+"\n", Font (owner.getOwner().getCtrlrManagerOwner().getFontManager().getDefaultMonoFontName(), 16.0f, Font::bold), Colours::red);
		owner.updateTabs();
	}
}

TabbedComponent *CtrlrLuaMethodEditArea::getLowerTabs()
{
	return (lowerTabs);
}

bool CtrlrLuaMethodEditArea::keyPressed (const KeyPress &key, Component *event)
{
    if (getTabs())
    {
        if (getTabs()->getCurrentTabIndex() < (getTabs()->getNumTabs()-1) && getTabs()->getCurrentTabIndex() >= 0)
        {
            getTabs()->setCurrentTabIndex(getTabs()->getCurrentTabIndex() + 1);
            return (true);
        }

        if (getTabs()->getCurrentTabIndex() >= getTabs()->getNumTabs() - 1)
        {
            getTabs()->setCurrentTabIndex(0);
            return (true);
        }
    }
    return (false);
}

void CtrlrLuaMethodEditArea::setActiveOutputTab()
{
	if (getLowerTabs())
	{
		getLowerTabs()->setCurrentTabIndex (0);
	}
}

CtrlrLuaMethodDebuggerPrompt *CtrlrLuaMethodEditArea::getLuaDebuggerPrompt(const bool activateDebuggerNow)
{
    if (activateDebuggerNow)
        lowerTabs->setCurrentTabIndex (2, true);

    return (debuggerPrompt);
}

void CtrlrLuaMethodEditArea::clearOutputText()
{
	output->setText("");
}