#pragma once
#include "../CtrlrComponent.h"

class CtrlrXYSurface;

class CtrlrXYModulator  : public Component
{
public:

    CtrlrXYModulator (CtrlrXYSurface &_owner);
    ~CtrlrXYModulator();

    void customLookAndFeelChanged(LookAndFeelBase *customLookAndFeel = nullptr) {}
    void paint (Graphics& g);
    void resized();
    void moved();
    void mouseEnter (const MouseEvent& e);
    void mouseExit (const MouseEvent& e);
    void mouseDown (const MouseEvent& e);
    void mouseDrag (const MouseEvent& e);

private:
	CtrlrXYSurface &owner;
	ComponentDragger dragger;
    CtrlrXYModulator (const CtrlrXYModulator&);
    const CtrlrXYModulator& operator= (const CtrlrXYModulator&);

    JUCE_LEAK_DETECTOR (CtrlrXYModulator)
};