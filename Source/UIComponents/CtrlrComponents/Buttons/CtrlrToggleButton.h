#pragma once
#include "CtrlrComponents/CtrlrComponent.h"

class CtrlrValueMap;

class CtrlrToggleButton  : public CtrlrComponent, public Button::Listener
{
public:
 
    CtrlrToggleButton (CtrlrModulator &owner);
    ~CtrlrToggleButton();

	void setComponentValue (const double newValue, const bool sendChangeMessage=false);
	void setComponentMidiValue (const int newValue, const bool sendChangeMessage=false);
	double getComponentValue();
	int getComponentMidiValue();
	double getComponentMaxValue();
	bool getToggleState();
	void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
	void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
	void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
	void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
    void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved, int){}
	void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved, int, int){}
	void click();
	bool isToggleButton();
	void setToggleState(const bool toggleState, const bool sendChangeMessage=false);
	CtrlrValueMap &getValueMap() { return (*valueMap); }
	void customLookAndFeelChanged(LookAndFeelBase *customLookAndFeel = nullptr) {}

	static void wrapForLua(lua_State *L);

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void mouseDown (const MouseEvent& e);

    juce_UseDebuggingNewOperator

private:
	ScopedPointer<CtrlrValueMap> valueMap;
    ToggleButton* ctrlrButton;
    CtrlrToggleButton (const CtrlrToggleButton&);
    const CtrlrToggleButton& operator= (const CtrlrToggleButton&);
};
