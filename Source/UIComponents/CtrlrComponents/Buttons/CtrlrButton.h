#pragma once
#include "CtrlrComponents/CtrlrComponent.h"

class CtrlrValueMap;

class CtrlrButton  : public CtrlrComponent,
					 public Button::Listener,
					 public Timer
{
public:
    CtrlrButton (CtrlrModulator &owner);
    ~CtrlrButton();

	void setComponentValue (const double newValue, const bool sendChangeMessage=false);
	double getComponentValue();
	int getComponentMidiValue();
	double getComponentMaxValue();
	const String getComponentText();
	bool getToggleState();
	void setComponentText (const String &componentText);
	void buttonContentChanged();
	void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
	void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
	void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
	void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
	void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved, int){}
	void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved, int, int){}
	void click();
	bool isToggleButton();
	void setToggleState(const bool toggleState, const bool sendChangeMessage=false);
	void timerCallback();
	void customLookAndFeelChanged(LookAndFeelBase *customLookAndFeel = nullptr) {}
	CtrlrValueMap &getValueMap() { return (*valueMap); }

	static void wrapForLua(lua_State *L);

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void mouseDown (const MouseEvent& e);

    juce_UseDebuggingNewOperator

private:
	ScopedPointer <CtrlrValueMap> valueMap;
    TextButton* ctrlrButton;
    CtrlrButton (const CtrlrButton&);
    const CtrlrButton& operator= (const CtrlrButton&);
};
