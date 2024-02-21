#include "stdafx.h"
#include "CtrlrLuaMethodEditor.h"
#include "CtrlrLuaMethodCodeEditor.h"
#include "Methods/CtrlrLuaMethodManager.h"
#include "CtrlrInlineUtilitiesGUI.h"
#include "CtrlrLuaMethodFind.h"

CtrlrLuaMethodFind::CtrlrLuaMethodFind (CtrlrLuaMethodEditor &_owner)
    : owner(_owner)
{
    setName ("Search and Replace");
    addAndMakeVisible (findInput = new TextEditor (""));
    findInput->setMultiLine (true);
    findInput->setReturnKeyStartsNewLine (false);
    findInput->setReadOnly (false);
    findInput->setScrollbarsShown (true);
    findInput->setCaretVisible (true);
    findInput->setPopupMenuEnabled (true);
    findInput->setColour (TextEditor::backgroundColourId, Colours::white);
    findInput->setColour (TextEditor::outlineColourId, Colour (0x00000000));
    findInput->setColour (TextEditor::shadowColourId, Colour (0x00000000));
    findInput->setText ("");

    addAndMakeVisible (replaceInput = new TextEditor (""));
    replaceInput->setMultiLine (true);
    replaceInput->setReturnKeyStartsNewLine (false);
    replaceInput->setReadOnly (false);
    replaceInput->setScrollbarsShown (true);
    replaceInput->setCaretVisible (true);
    replaceInput->setPopupMenuEnabled (true);
    replaceInput->setColour (TextEditor::backgroundColourId, Colours::white);
    replaceInput->setColour (TextEditor::outlineColourId, Colour (0x00000000));
    replaceInput->setColour (TextEditor::shadowColourId, Colour (0x00000000));
    replaceInput->setText ("");

    addAndMakeVisible (findNext = new TextButton (""));
    findNext->setButtonText (TRANS("Find"));
    findNext->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    findNext->addListener (this);
    findNext->setColour (TextButton::buttonColourId, Colour (0xffbababa));

    addAndMakeVisible (replaceNextButton = new TextButton (""));
    replaceNextButton->setButtonText (TRANS("Next"));
    replaceNextButton->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    replaceNextButton->addListener (this);
    replaceNextButton->setColour (TextButton::buttonColourId, Colour (0xffcbf2aa));

    addAndMakeVisible (replaceAllButton = new TextButton (""));
    replaceAllButton->setButtonText (TRANS("All"));
    replaceAllButton->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    replaceAllButton->addListener (this);
    replaceAllButton->setColour (TextButton::buttonColourId, Colour (0xffa9cfff));

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Find")));
    label->setFont (Font (16.00f, Font::bold | Font::italic));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (matchCase = new ToggleButton (""));
    matchCase->setButtonText (TRANS("Match Case"));
    matchCase->addListener (this);

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("Replace")));
    label2->setFont (Font (16.00f, Font::bold | Font::italic));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (whereToFindCombo = new ComboBox (""));
    whereToFindCombo->setEditableText (false);
    whereToFindCombo->setJustificationType (Justification::centredLeft);
    whereToFindCombo->setTextWhenNothingSelected (TRANS("Current"));
    whereToFindCombo->setTextWhenNoChoicesAvailable ("");
    whereToFindCombo->addItem (TRANS("Current"), 1);
    whereToFindCombo->addItem (TRANS("All Open"), 2);
    whereToFindCombo->addItem (TRANS("All"), 3);
    whereToFindCombo->addListener (this);

	replaceInput->addListener (this);
	findInput->addListener (this);

	lastFoundPosition = -1;
	findInput->setFont (Font(16));
	replaceInput->setFont (Font(16));

    setSize (424, 64);
}

CtrlrLuaMethodFind::~CtrlrLuaMethodFind()
{
    findInput = nullptr;
    replaceInput = nullptr;
    findNext = nullptr;
    replaceNextButton = nullptr;
    replaceAllButton = nullptr;
    label = nullptr;
    matchCase = nullptr;
    label2 = nullptr;
    whereToFindCombo = nullptr;
}


void CtrlrLuaMethodFind::resized()
{
    findInput->setBounds (4, 4, proportionOfWidth (0.3302f), 32);
    replaceInput->setBounds (proportionOfWidth (0.4505f), 4, proportionOfWidth (0.3302f), 32);
    findNext->setBounds (4 + proportionOfWidth (0.3302f), 4, proportionOfWidth (0.0991f), 32);
    replaceNextButton->setBounds (proportionOfWidth (0.4505f) + proportionOfWidth (0.3302f), 4, proportionOfWidth (0.0991f), 32);
    replaceAllButton->setBounds ((proportionOfWidth (0.4505f) + proportionOfWidth (0.3302f)) + proportionOfWidth (0.0991f), 4, proportionOfWidth (0.0991f), 32);
    label->setBounds (4 + 0, 40, 64, 24);
    matchCase->setBounds (4 + 68, 40, 96, 24);
    label2->setBounds (proportionOfWidth (0.4505f) + 121, 40, 64, 24);
    whereToFindCombo->setBounds (176, 40, 128, 24);
}

void CtrlrLuaMethodFind::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == findNext)
    {
		if (whereToFindCombo->getSelectedId() == 1 || whereToFindCombo->getSelectedId() == 0)
		{
			findNextMatch();
		}
		else if (whereToFindCombo->getSelectedId() == 2)
		{
			findInOpened();
		}
		else if (whereToFindCombo->getSelectedId() == 3)
		{
			findInAll();
		}
    }
    else if (buttonThatWasClicked == replaceNextButton)
    {
		replaceNextMatch();
    }
    else if (buttonThatWasClicked == replaceAllButton)
    {
		replaceAllMatches();
    }
    else if (buttonThatWasClicked == matchCase)
    {
    }
}

void CtrlrLuaMethodFind::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == whereToFindCombo)
    {
    }
}

void CtrlrLuaMethodFind::visibilityChanged()
{
	if (isVisible())
	{
		findInput->grabKeyboardFocus();
		findInput->selectAll();
	}
}

bool CtrlrLuaMethodFind::keyPressed (const KeyPress& key)
{
	if (key.getKeyCode() == 65650) // F3
	{
	}
    return false;  // Return true if your handler uses this key event, or false to allow it to be passed-on.
}

void CtrlrLuaMethodFind::textEditorReturnKeyPressed (TextEditor &editor)
{
	if (&editor == findInput)
	{
		if (whereToFindCombo->getSelectedId() <= 1)
		{
			findNextMatch();
		}
		else if (whereToFindCombo->getSelectedId() == 2)
		{
			findInOpened();
		}
		else if (whereToFindCombo->getSelectedId() == 3)
		{
			findInAll();
		}
	}

	if (&editor == replaceInput)
	{
		replaceNextMatch();
	}
}

void CtrlrLuaMethodFind::textEditorTextChanged (TextEditor &editor)
{
}

void CtrlrLuaMethodFind::replaceNextMatch()
{
	if (owner.getCurrentEditor() == nullptr)
	{
		return;
	}

	CodeDocument &doc		= owner.getCurrentEditor()->getCodeDocument();
	const String search		= findInput->getText();
	const String replace	= replaceInput->getText();

	findNextMatch(); // correction to find and replace on first time also
	if (lastFoundPosition >= 0)
	{
		doc.newTransaction();
		doc.deleteSection (lastFoundPosition, lastFoundPosition+search.length());
		doc.insertText (lastFoundPosition, replace);
	}
}

void CtrlrLuaMethodFind::replaceAllMatches()
{
	lastFoundPosition = -1;

	do
	{
		replaceNextMatch();
	}
	while (lastFoundPosition >= 0);
}

void CtrlrLuaMethodFind::setFocusOnFindInput()
{
	findInput->grabKeyboardFocus();
}

void CtrlrLuaMethodFind::findNextMatch()
{
	if (owner.getCurrentEditor() == nullptr)
	{
		return;
	}

	CodeDocument &doc		= owner.getCurrentEditor()->getCodeDocument();
	CodeEditorComponent *ed	= owner.getCurrentEditor()->getCodeComponent();
	const String search		= findInput->getText();
	int position			= -1;

	if (!matchCase->getToggleState())
	{
		position = doc.getAllContent().indexOfIgnoreCase (lastFoundPosition+1, search);
	}
	else
	{
		position = doc.getAllContent().indexOf (lastFoundPosition+1, search);
	}

	if (position >= 0)
	{
		lastFoundPosition = position;
		if (ed)
		{
			ed->selectRegion (CodeDocument::Position(doc,lastFoundPosition), CodeDocument::Position(doc, lastFoundPosition+search.length()));
		}
	}
	else
	{
		lastFoundPosition = -1;
	}
}

void CtrlrLuaMethodFind::findInOpened()
{
	if (owner.getTabs() == nullptr)
		return;

	StringArray names = owner.getTabs()->getTabNames();

	owner.getMethodEditArea()->insertOutput("\n\nSearching for: \""+findInput->getText()+"\" in all opened methods (double click line to jump)\n", Colours::darkblue);

	for (int i=0; i<owner.getTabs()->getNumTabs(); i++)
	{
		CtrlrLuaMethodCodeEditor *codeEditor = dynamic_cast<CtrlrLuaMethodCodeEditor*>(owner.getTabs()->getTabContentComponent(i));

		if (codeEditor != nullptr)
		{
			CodeDocument &doc		= codeEditor->getCodeDocument();

			Array<Range<int> > results = searchForMatchesInDocument (doc);

			for (int j=0; j<results.size(); j++)
			{
				reportFoundMatch (doc, names[i], results[j]);
			}
		}
	}

	owner.getMethodEditArea()->getLowerTabs()->setCurrentTabIndex(0,true);
}

void CtrlrLuaMethodFind::findInAll()
{
	owner.getMethodEditArea()->insertOutput("\n\nSearching for: \""+findInput->getText()+"\" in all methods (double click line to jump)\n", Colours::darkblue);
	StringArray names;

	for (int i=0; i<owner.getMethodManager().getNumMethods(); i++)
	{
		CtrlrLuaMethod *m = owner.getMethodManager().getMethodByIndex (i);

		if (m)
		{
			names.add (m->getName());

			if (m->getCodeEditor())
			{
				/* it has an editor so it's open */
				CodeDocument &doc		= m->getCodeEditor()->getCodeDocument();

				Array<Range<int> > results = searchForMatchesInDocument (doc);

				for (int j=0; j<results.size(); j++)
				{
					reportFoundMatch (doc, names[i], results[j]);
				}
			}
		}
	}

	owner.getMethodEditArea()->getLowerTabs()->setCurrentTabIndex(0,true);
}

const Array<Range<int> > CtrlrLuaMethodFind::searchForMatchesInDocument(CodeDocument &doc)
{
	Array<Range<int> > results;
	const String search		= findInput->getText();
	int position			= -1;
	lastFoundPosition		= -1;

	do
	{
		if (!matchCase->getToggleState())
		{
			position = doc.getAllContent().indexOfIgnoreCase (lastFoundPosition+1, search);
		}
		else
		{
			position = doc.getAllContent().indexOf (lastFoundPosition+1, search);
		}

		if (position >= 0)
		{
			lastFoundPosition		= position;
			results.add (Range<int> (lastFoundPosition, lastFoundPosition+search.length()));
		}
		else
		{
			lastFoundPosition = -1;
		}
	}
	while (lastFoundPosition >= 0);

	return (results);
}

void CtrlrLuaMethodFind::reportFoundMatch (CodeDocument &document, const String &methodName, const Range<int> range)
{
	CodeDocument::Position pos (document, range.getStart());
	AttributedString as;
	as.append ("Method: ", Colours::black);
	as.append (methodName, Colours::blue);

	as.append ("\tline: ", Colours::black);
	as.append (String(pos.getLineNumber()+1), Colours::darkgreen);

	as.append ("\tstart: ", Colours::black);
	as.append (String(range.getStart()), Colours::darkgreen);

	as.append ("\tend: ", Colours::black);
	as.append (String(range.getEnd()), Colours::darkgreen);

	owner.getMethodEditArea()->insertOutput (as);
}
