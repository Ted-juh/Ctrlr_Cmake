#pragma once
#include "CtrlrMacros.h"

class CtrlrLuaMethodEditor;

class CtrlrLuaMethodFind  : public Component,
                            public TextEditor::Listener,
							public Button::Listener,
							public ComboBox::Listener
{
public:

    CtrlrLuaMethodFind (CtrlrLuaMethodEditor &_owner);
    ~CtrlrLuaMethodFind();

    void textEditorReturnKeyPressed (TextEditor &editor);
	void textEditorTextChanged (TextEditor &editor);
	void findNextMatch();
	void findInOpened();
	void findInAll();
	void replaceNextMatch();
	void replaceAllMatches();
	void setFocusOnFindInput();
	const Array<Range<int> > searchForMatchesInDocument(CodeDocument &doc);
	void reportFoundMatch (CodeDocument &document, const String &methodName, const Range<int> range);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void visibilityChanged();
    bool keyPressed (const KeyPress& key);

private:
	CtrlrLuaMethodEditor &owner;
	int lastFoundPosition;
    ScopedPointer<TextEditor> findInput;
    ScopedPointer<TextEditor> replaceInput;
    ScopedPointer<TextButton> findNext;
    ScopedPointer<TextButton> replaceNextButton;
    ScopedPointer<TextButton> replaceAllButton;
    ScopedPointer<Label> label;
    ScopedPointer<ToggleButton> matchCase;
    ScopedPointer<Label> label2;
    ScopedPointer<ComboBox> whereToFindCombo;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrLuaMethodFind)
};