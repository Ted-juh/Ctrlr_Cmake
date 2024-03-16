#ifndef __JUCE_HEADER_76E483A2275D56C__
#define __JUCE_HEADER_76E483A2275D56C__

#include "CtrlrMacros.h"

class CtrlrPanel;

class CtrlrMIDISettingsDevices  : public Component,
									public ComboBox::Listener,
									public Label::Listener,
									public Button::Listener
{
public:

    CtrlrMIDISettingsDevices (CtrlrPanel &_owner);
    ~CtrlrMIDISettingsDevices();

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void labelTextChanged (Label* labelThatHasChanged);
    void buttonClicked (Button* buttonThatWasClicked);

private:
    CtrlrPanel &owner;

    ScopedPointer<ComboBox> inputDevices;
    ScopedPointer<ComboBox> controllerDevices;
    ScopedPointer<ComboBox> outputDevices;
    ScopedPointer<Label> label;
    ScopedPointer<Label> label2;
    ScopedPointer<Label> label3;
    ScopedPointer<ComboBox> oscProtocol;
    ScopedPointer<Label> label4;
    ScopedPointer<Label> oscPort;
    ScopedPointer<Label> label5;
    ScopedPointer<Label> label6;
    ScopedPointer<ToggleButton> oscEnabled;
    ScopedPointer<Label> label7;
    ScopedPointer<ComboBox> inputChannel;
    ScopedPointer<ComboBox> controllerChannel;
    ScopedPointer<ComboBox> outputChannel;
    ScopedPointer<Label> label8;
    ScopedPointer<ComboBox> pluginOutputChannel;
    ScopedPointer<ToggleButton> pluginOutput;
    ScopedPointer<Label> label9;
    ScopedPointer<ToggleButton> pluginInput;
    ScopedPointer<ComboBox> pluginInputChannel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrMIDISettingsDevices)
};

#endif