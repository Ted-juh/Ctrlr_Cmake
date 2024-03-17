#pragma once
#include "JuceHeader.h"
#include "../CtrlrComponent.h"
#include "CtrlrPanel/CtrlrPanel.h"

class CtrlrMidiKeyboard  : public CtrlrComponent,
                           public MidiKeyboardStateListener,
						   public CtrlrPanel::Listener
{
public:

    CtrlrMidiKeyboard (CtrlrModulator &owner);
    ~CtrlrMidiKeyboard();

    void setComponentValue (const double newValue, const bool sendChangeMessage=false);
	double getComponentValue();
	int getComponentMidiValue();
	double getComponentMaxValue();
	void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
	void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
	void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
	void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
    void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved, int){}
	void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved, int, int){}
	void handleNoteOn (MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity);
	void handleNoteOff (MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity);
	void midiReceived(MidiMessage &message);
	void customLookAndFeelChanged(LookAndFeelBase *customLookAndFeel = nullptr) {}
    void paint (Graphics& g);
    void resized();
    juce_UseDebuggingNewOperator

private:
	MidiKeyboardState keyboardState;
	CtrlrMidiMessage noteOn, noteOff;
    MidiKeyboardComponent* midiKeyboard;
    CtrlrMidiKeyboard (const CtrlrMidiKeyboard&);
    const CtrlrMidiKeyboard& operator= (const CtrlrMidiKeyboard&);
};