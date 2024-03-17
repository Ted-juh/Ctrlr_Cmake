#pragma once
#include "../CtrlrComponent.h"

class CtrlrImage  : public CtrlrComponent
{
public:

    CtrlrImage (CtrlrModulator &owner);
    ~CtrlrImage();

	void setComponentValue (const double newValue, const bool sendChangeMessage=false);
	double getComponentValue();
	int getComponentMidiValue();
	double getComponentMaxValue();

	const Array<int> getResourceList();
	void resetSize();
	void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
	void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
	void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
	void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
    void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved, int){}
	void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved, int, int){}
	void restoreState (const ValueTree &savedState);
	void reloadResources(Array <CtrlrPanelResource*> resourcesThatChanged);
	void setResource();
	void customLookAndFeelChanged(LookAndFeelBase *customLookAndFeel = nullptr) {}

    void paint (Graphics& g);
    void resized();

    juce_UseDebuggingNewOperator

private:
	Array <int> values;
	Image currentImage;
	String resourceName;
    CtrlrImage (const CtrlrImage&);
    const CtrlrImage& operator= (const CtrlrImage&);
};