#pragma once
#include "CtrlrComponents/CtrlrComponent.h"

class CtrlrHyperlink  : public CtrlrComponent,
						public Button::Listener
{
public:

    CtrlrHyperlink (CtrlrModulator &owner);
    ~CtrlrHyperlink();

	void setComponentValue (const double newValue, const bool sendChangeMessage=false);
	double getComponentValue();
	int getComponentMidiValue();
	double getComponentMaxValue();
	const String getComponentText();
	void setComponentText(const String &componentText);
	void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
	void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
	void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
	void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
    void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved, int){}
	void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved, int, int){}
	void customLookAndFeelChanged(LookAndFeelBase *customLookAndFeel = nullptr) {}
	void buttonContentChanged();
	bool hyperlinkOpensUrl();
	void setHyperlinkUrl(const String &newURL);
    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);

    juce_UseDebuggingNewOperator

private:
    CtrlrValueMap valueMap;
    HyperlinkButton* hyperlinkButton;
    CtrlrHyperlink (const CtrlrHyperlink&);
    const CtrlrHyperlink& operator= (const CtrlrHyperlink&);
};