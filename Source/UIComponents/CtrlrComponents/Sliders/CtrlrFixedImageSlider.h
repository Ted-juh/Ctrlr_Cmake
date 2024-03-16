#ifndef __JUCER_HEADER_CTRLRFIXEDIMAGESLIDER_CTRLRFIXEDIMAGESLIDER_73B20E68__
#define __JUCER_HEADER_CTRLRFIXEDIMAGESLIDER_CTRLRFIXEDIMAGESLIDER_73B20E68__

#include "CtrlrComponents/CtrlrComponent.h"

class CtrlrValueMap;
class CtrlrImageSliderLF;
class CtrlrSliderInternal;

class CtrlrFixedImageSlider  : public CtrlrComponent,
                               public Slider::Listener
{
public:
    
    CtrlrFixedImageSlider (CtrlrModulator &owner);
    ~CtrlrFixedImageSlider();

	void sliderValueChanged (Slider* sliderThatWasMoved);
	void setComponentValue (const double newValue, const bool sendChangeMessage=false);
	double getComponentValue();
	int getComponentMidiValue();
	double getComponentMaxValue();
	const String getComponentText();
	void sliderContentChanged();
	void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
	void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
	void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
	void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
    void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved, int){}
	void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved, int, int){}
	Image &getFilmStripImage() { return (filmStripImage); }
	const String getTextForValue(const double value);
	void reloadResources(Array <CtrlrPanelResource*> resourcesThatChanged);
	void setResource();
	Slider *getOwnedSlider();
	CtrlrValueMap &getValueMap() { return (*valueMap); }
	void customLookAndFeelChanged(LookAndFeelBase *customLookAndFeel = nullptr) {}

	static void wrapForLua(lua_State *L);

    void paint (Graphics& g);
    void resized();
    void mouseUp (const MouseEvent& e);

	juce_UseDebuggingNewOperator

private:
 	ScopedPointer<CtrlrValueMap> valueMap;
	ScopedPointer<CtrlrImageSliderLF> lf;
	Image filmStripImage;
     CtrlrSliderInternal* ctrlrSlider;
    CtrlrFixedImageSlider (const CtrlrFixedImageSlider&);
    const CtrlrFixedImageSlider& operator= (const CtrlrFixedImageSlider&);
};


#endif   // __JUCER_HEADER_CTRLRFIXEDIMAGESLIDER_CTRLRFIXEDIMAGESLIDER_73B20E68__
