#ifndef __JUCER_HEADER_CTRLRFIXEDSLIDER_CTRLRFIXEDSLIDER_AD4513E7__
#define __JUCER_HEADER_CTRLRFIXEDSLIDER_CTRLRFIXEDSLIDER_AD4513E7__

#include "CtrlrComponents/CtrlrComponent.h"
#include "CtrlrSliderInternal.h"

class CtrlrValueMap;
class CtrlrSliderLookAndFeel;

class CtrlrFixedSlider  : public CtrlrComponent,
                          public SettableTooltipClient,
                          public Slider::Listener
{
public:

    CtrlrFixedSlider (CtrlrModulator &owner);
    ~CtrlrFixedSlider();

	void sliderValueChanged (Slider* sliderThatWasMoved);
	void setComponentValue (const double newValue, const bool sendChangeMessage=false);
	double getComponentValue();
	int getComponentMidiValue();
	double getComponentMaxValue();
	const String getComponentText();
	void sliderContentChanged();
	const String getTextForValue(const double value);
	void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
	void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
	void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
	void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
    void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved, int){}
	void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved, int, int){}
	Slider *getOwnedSlider() { return (ctrlrSlider); }
	CtrlrValueMap &getValueMap() { return (*valueMap); }
	void customLookAndFeelChanged(LookAndFeelBase *customLookAndFeel = nullptr) {}
	static void wrapForLua(lua_State *L);
    void paint (Graphics& g);
    void resized();
    void mouseUp (const MouseEvent& e);

    juce_UseDebuggingNewOperator

private:
	ScopedPointer<CtrlrSliderLookAndFeel_V2> lf;
	ScopedPointer<CtrlrValueMap> valueMap;
    CtrlrSliderInternal* ctrlrSlider;
    CtrlrFixedSlider (const CtrlrFixedSlider&);
    const CtrlrFixedSlider& operator= (const CtrlrFixedSlider&);
};


#endif   // __JUCER_HEADER_CTRLRFIXEDSLIDER_CTRLRFIXEDSLIDER_AD4513E7__
