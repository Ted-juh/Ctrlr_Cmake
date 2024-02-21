#pragma once
#include "CtrlrComponents/CtrlrComponent.h"

class CtrlrValueMap;
class CtrlrCustomButtonInternal;

class CtrlrImageButton  : public CtrlrComponent,
                          public SettableTooltipClient,
                          public Button::Listener,
						  public Timer
{
public:
 
    CtrlrImageButton (CtrlrModulator &owner);
    ~CtrlrImageButton();

 	enum ImageButtonMode
	{
		Normal,
		Momentary,
		NormalMouseOver,
		MomentaryMouseOver
	};

	void mouseDown (const MouseEvent &e);
	void setComponentValue (const double newValue, const bool sendChangeMessage=false);
	void setComponentMidiValue (const int newValue, const bool sendChangeMessage=false);
	int getComponentMidiValue();
	double getComponentValue();
	double getComponentMaxValue();
	const String getComponentText();
	void buttonContentChanged();
	const Array<int> getResourceList();
	const Array<Font> getFontList();
	bool getToggleState();
	void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
	void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
	void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
	void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
    void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved, int){}
	void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved, int, int){}
	void buttonClicked (Button* button);
	void buttonModeChanged(const ImageButtonMode newMode);
	const ImageButtonMode getButtonMode();
	void click();
	bool isToggleButton();
	void setToggleState(const bool toggleState, const bool sendChangeMessage=false);
	void timerCallback();
	void reloadResources(Array <CtrlrPanelResource*> resourcesThatChanged);
	void setResource();
	void customLookAndFeelChanged(LookAndFeelBase *customLookAndFeel = nullptr) {}
	CtrlrValueMap &getValueMap() { return (*valueMap); }
	static void wrapForLua(lua_State *L);
    void paint (Graphics& g);
    void resized();

private:
	Image filmStripImage;
	ScopedPointer<CtrlrValueMap> valueMap;
    CtrlrCustomButtonInternal* ctrlrButton;
    CtrlrImageButton (const CtrlrImageButton&);
    const CtrlrImageButton& operator= (const CtrlrImageButton&);

	JUCE_LEAK_DETECTOR(CtrlrImageButton)
};