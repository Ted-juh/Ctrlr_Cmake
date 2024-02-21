#pragma once

#include "CtrlrMacros.h"
#include "CtrlrLog.h"
#include "CtrlrWindowManagers/CtrlrChildWindowContent.h"
#include "CtrlrWindowManagers/CtrlrManagerWindowManager.h"
class CtrlrManager;

class CtrlrMIDICalculator  : public CtrlrChildWindowContent,
                             public TextEditor::Listener,
							 public ComboBox::Listener,
							 public Button::Listener
{
public:

    CtrlrMIDICalculator (CtrlrManager &_owner);
    ~CtrlrMIDICalculator();

    String getContentName()					{ return ("MIDI Calculator"); }
	uint8 getType()							{ return (CtrlrManagerWindowManager::MIDICalculator); }
	void textEditorTextChanged (TextEditor &editor);
	void formatData (const String &data, const bool isHex=false, const bool isDec=false, const bool isBin=false);
	String formatHex(const int d);
	String makeHexPretty(const String &hex);

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void buttonClicked (Button* buttonThatWasClicked);

private:
	CtrlrManager &owner;

    ScopedPointer<TextEditor> hexDisplay;
    ScopedPointer<Label> label;
    ScopedPointer<Label> label2;
    ScopedPointer<TextEditor> binDisplay;
    ScopedPointer<Label> label3;
    ScopedPointer<TextEditor> decDisplay;
    ScopedPointer<ComboBox> hexFormat;
    ScopedPointer<ToggleButton> bit16Switch;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrMIDICalculator)
};