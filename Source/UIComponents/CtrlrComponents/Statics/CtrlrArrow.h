#pragma once
#include "../CtrlrComponent.h"
#include "CtrlrIDs.h"

class CtrlrArrow  : public CtrlrComponent
{
public:
    CtrlrArrow (CtrlrModulator &owner);
    ~CtrlrArrow();

    void setComponentValue (const double newValue, const bool sendChangeMessage=false);
	double getComponentValue();
	int getComponentMidiValue();
	double getComponentMaxValue();
	void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
	void restoreState (const ValueTree &savedState);
	void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
	void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
	void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
    void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved, int){}
	void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved, int, int){}
	void customLookAndFeelChanged(LookAndFeelBase *customLookAndFeel = nullptr) {}
    void paint (Graphics& g);
    void resized();

private:

	CtrlrArrow (const CtrlrArrow&);
    const CtrlrArrow& operator= (const CtrlrArrow&);

	JUCE_LEAK_DETECTOR(CtrlrArrow)
};