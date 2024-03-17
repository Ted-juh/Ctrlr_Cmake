#pragma once
#include "CtrlrComponents/CtrlrComponent.h"
#include "CtrlrSliderInternal.h"

class CtrlrImageSliderLF;

class CtrlrImageSlider  : public CtrlrComponent,
                          public SettableTooltipClient,
						  public Slider::Listener
{
public:
    CtrlrImageSlider (CtrlrModulator &owner);
    ~CtrlrImageSlider();

	void setComponentValue (const double newValue, const bool sendChangeMessage=false);
	double getComponentValue();
	int getComponentMidiValue();
	double getComponentMaxValue();
	const String getComponentText();
	void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
	void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
	void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
	void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
    void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved, int){}
	void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved, int, int){}
	Image &getFilmStripImage() { return (filmStripImage); }
	Slider *getOwnedSlider() { return (ctrlrSlider); }
	void reloadResources(Array <CtrlrPanelResource*> resourcesThatChanged);
	void setResource();
	static void wrapForLua(lua_State *L);
	void customLookAndFeelChanged(LookAndFeelBase *customLookAndFeel = nullptr) {}
    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void mouseUp (const MouseEvent& e);

    juce_UseDebuggingNewOperator

private:
	ScopedPointer<CtrlrImageSliderLF> lf;
	Image filmStripImage;
    CtrlrSliderInternal* ctrlrSlider;
    CtrlrImageSlider (const CtrlrImageSlider&);
    const CtrlrImageSlider& operator= (const CtrlrImageSlider&);
};