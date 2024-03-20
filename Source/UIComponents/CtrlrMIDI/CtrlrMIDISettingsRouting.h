#pragma once
#include "JuceHeader.h"

class CtrlrPanel;

class CtrlrMIDISettingsRouting  :   public Component,
								    public Button::Listener
{
public:
 
    CtrlrMIDISettingsRouting (CtrlrPanel &_owner);
    ~CtrlrMIDISettingsRouting();

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);

private:

    CtrlrPanel &owner;

    ScopedPointer<GroupComponent> groupComponent;
    ScopedPointer<ToggleButton> inDev2OutDev;
    ScopedPointer<ToggleButton> ctrlDev2OutDev;
    ScopedPointer<ToggleButton> host2OutDev;
    ScopedPointer<ToggleButton> host2Host;
    ScopedPointer<ToggleButton> inDev2OutDevCh;
    ScopedPointer<ToggleButton> ctrlDev2OutDevCh;
    ScopedPointer<ToggleButton> host2OutDevCh;
    ScopedPointer<ToggleButton> host2HostCh;
    ScopedPointer<Label> label;
    ScopedPointer<ToggleButton> inDev2Host;
    ScopedPointer<ToggleButton> inDev2HostCh;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrMIDISettingsRouting)
};