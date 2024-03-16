#pragma once

#include "JuceHeader.h"
#include "CtrlrWindowManagers/CtrlrChildWindowContent.h"

class CtrlrPanel;

class CtrlrMIDISettingsDialog  : public CtrlrChildWindowContent
{

public:

    CtrlrMIDISettingsDialog (CtrlrPanel &_owner);
    ~CtrlrMIDISettingsDialog();

    static void showDialog(CtrlrPanel &_owner);

    uint8 getType() { return (CtrlrPanelWindowManager::MIDISettings);}

    void resized();



private:
    CtrlrPanel &owner;
    ScopedPointer<TabbedComponent> midiTabs;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrMIDISettingsDialog)
};
