#include "stdafx.h"
#include "CtrlrMIDISettingsDevices.h"
#include "MIDI/CtrlrMIDIDeviceManager.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrMacros.h"

CtrlrMIDISettingsDevices::CtrlrMIDISettingsDevices (CtrlrPanel &_owner)
    : owner(_owner)
{
    addAndMakeVisible (inputDevices = new ComboBox (String()));
    inputDevices->setEditableText (false);
    inputDevices->setJustificationType (Justification::centredLeft);
    inputDevices->setTextWhenNothingSelected (TRANS("No device selected"));
    inputDevices->setTextWhenNoChoicesAvailable (TRANS("No devices available"));
    inputDevices->addListener (this);

    addAndMakeVisible (controllerDevices = new ComboBox (String()));
    controllerDevices->setEditableText (false);
    controllerDevices->setJustificationType (Justification::centredLeft);
    controllerDevices->setTextWhenNothingSelected (TRANS("No device selected"));
    controllerDevices->setTextWhenNoChoicesAvailable (TRANS("No devices available"));
    controllerDevices->addListener (this);

    addAndMakeVisible (outputDevices = new ComboBox (String()));
    outputDevices->setEditableText (false);
    outputDevices->setJustificationType (Justification::centredLeft);
    outputDevices->setTextWhenNothingSelected (TRANS("No device selected"));
    outputDevices->setTextWhenNoChoicesAvailable (TRANS("No devices available"));
    outputDevices->addListener (this);

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Input device")));
    label->setFont (Font (16.00f, Font::bold));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("Controller device")));
    label2->setFont (Font (16.00f, Font::bold));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("Output device")));
    label3->setFont (Font (16.00f, Font::bold));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (oscProtocol = new ComboBox ("OSC Protocol"));
    oscProtocol->setEditableText (false);
    oscProtocol->setJustificationType (Justification::centredLeft);
    oscProtocol->setTextWhenNothingSelected (TRANS("TCP"));
    oscProtocol->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    oscProtocol->addItem (TRANS("Default"), 1);
    oscProtocol->addItem (TRANS("UDP"), 2);
    oscProtocol->addItem (TRANS("Local/UNIX"), 3);
    oscProtocol->addItem (TRANS("TCP"), 4);
    oscProtocol->addListener (this);

    addAndMakeVisible (label4 = new Label ("new label",
                                           TRANS("OSC Server settings")));
    label4->setFont (Font (16.00f, Font::bold));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (oscPort = new Label ("OSC Port",
                                            TRANS("7770")));
    oscPort->setTooltip (TRANS("OSC Port"));
    oscPort->setFont (Font (24.00f, Font::plain));
    oscPort->setJustificationType (Justification::centred);
    oscPort->setEditable (true, true, false);
    oscPort->setColour (Label::backgroundColourId, Colours::white);
    oscPort->setColour (Label::outlineColourId, Colour (0x84000000));
    oscPort->setColour (TextEditor::textColourId, Colours::black);
    oscPort->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    oscPort->addListener (this);

    addAndMakeVisible (label5 = new Label ("new label",
                                           TRANS("Protocol")));
    label5->setFont (Font (14.00f, Font::plain));
    label5->setJustificationType (Justification::centredLeft);
    label5->setEditable (false, false, false);
    label5->setColour (TextEditor::textColourId, Colours::black);
    label5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label6 = new Label ("new label",
                                           TRANS("Port/Socket path")));
    label6->setFont (Font (14.00f, Font::plain));
    label6->setJustificationType (Justification::centredLeft);
    label6->setEditable (false, false, false);
    label6->setColour (TextEditor::textColourId, Colours::black);
    label6->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (oscEnabled = new ToggleButton ("OSC Enabled"));
    oscEnabled->setButtonText (String());
    oscEnabled->addListener (this);

    addAndMakeVisible (label7 = new Label ("new label",
                                           TRANS("Enable")));
    label7->setFont (Font (14.00f, Font::plain));
    label7->setJustificationType (Justification::centredLeft);
    label7->setEditable (false, false, false);
    label7->setColour (TextEditor::textColourId, Colours::black);
    label7->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (inputChannel = new ComboBox (String()));
    inputChannel->setEditableText (false);
    inputChannel->setJustificationType (Justification::centredLeft);
    inputChannel->setTextWhenNothingSelected (TRANS("All"));
    inputChannel->setTextWhenNoChoicesAvailable (String());
    inputChannel->addItem (TRANS("All"), 1);
    inputChannel->addItem (TRANS("1"), 2);
    inputChannel->addItem (TRANS("2"), 3);
    inputChannel->addItem (TRANS("3"), 4);
    inputChannel->addItem (TRANS("4"), 5);
    inputChannel->addItem (TRANS("6"), 6);
    inputChannel->addItem (TRANS("7"), 7);
    inputChannel->addItem (TRANS("8"), 8);
    inputChannel->addItem (TRANS("9"), 9);
    inputChannel->addItem (TRANS("10"), 10);
    inputChannel->addItem (TRANS("11"), 11);
    inputChannel->addItem (TRANS("12"), 12);
    inputChannel->addItem (TRANS("13"), 13);
    inputChannel->addItem (TRANS("14"), 14);
    inputChannel->addItem (TRANS("15"), 15);
    inputChannel->addItem (TRANS("16"), 16);
    inputChannel->addListener (this);

    addAndMakeVisible (controllerChannel = new ComboBox (String()));
    controllerChannel->setEditableText (false);
    controllerChannel->setJustificationType (Justification::centredLeft);
    controllerChannel->setTextWhenNothingSelected (TRANS("All"));
    controllerChannel->setTextWhenNoChoicesAvailable (String());
    controllerChannel->addItem (TRANS("All"), 1);
    controllerChannel->addItem (TRANS("1"), 2);
    controllerChannel->addItem (TRANS("2"), 3);
    controllerChannel->addItem (TRANS("3"), 4);
    controllerChannel->addItem (TRANS("4"), 5);
    controllerChannel->addItem (TRANS("6"), 6);
    controllerChannel->addItem (TRANS("7"), 7);
    controllerChannel->addItem (TRANS("8"), 8);
    controllerChannel->addItem (TRANS("9"), 9);
    controllerChannel->addItem (TRANS("10"), 10);
    controllerChannel->addItem (TRANS("11"), 11);
    controllerChannel->addItem (TRANS("12"), 12);
    controllerChannel->addItem (TRANS("13"), 13);
    controllerChannel->addItem (TRANS("14"), 14);
    controllerChannel->addItem (TRANS("15"), 15);
    controllerChannel->addItem (TRANS("16"), 16);
    controllerChannel->addListener (this);

    addAndMakeVisible (outputChannel = new ComboBox (String()));
    outputChannel->setEditableText (false);
    outputChannel->setJustificationType (Justification::centredLeft);
    outputChannel->setTextWhenNothingSelected (TRANS("All"));
    outputChannel->setTextWhenNoChoicesAvailable (String());
    outputChannel->addItem (TRANS("All"), 1);
    outputChannel->addItem (TRANS("1"), 2);
    outputChannel->addItem (TRANS("2"), 3);
    outputChannel->addItem (TRANS("3"), 4);
    outputChannel->addItem (TRANS("4"), 5);
    outputChannel->addItem (TRANS("6"), 6);
    outputChannel->addItem (TRANS("7"), 7);
    outputChannel->addItem (TRANS("8"), 8);
    outputChannel->addItem (TRANS("9"), 9);
    outputChannel->addItem (TRANS("10"), 10);
    outputChannel->addItem (TRANS("11"), 11);
    outputChannel->addItem (TRANS("12"), 12);
    outputChannel->addItem (TRANS("13"), 13);
    outputChannel->addItem (TRANS("14"), 14);
    outputChannel->addItem (TRANS("15"), 15);
    outputChannel->addItem (TRANS("16"), 16);
    outputChannel->addListener (this);

    addAndMakeVisible (label8 = new Label ("new label",
                                           TRANS("Plugin")));
    label8->setFont (Font (16.00f, Font::bold));
    label8->setJustificationType (Justification::centredLeft);
    label8->setEditable (false, false, false);
    label8->setColour (TextEditor::textColourId, Colours::black);
    label8->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (pluginOutputChannel = new ComboBox (String()));
    pluginOutputChannel->setEditableText (false);
    pluginOutputChannel->setJustificationType (Justification::centredLeft);
    pluginOutputChannel->setTextWhenNothingSelected (TRANS("All"));
    pluginOutputChannel->setTextWhenNoChoicesAvailable (String());
    pluginOutputChannel->addItem (TRANS("All"), 1);
    pluginOutputChannel->addItem (TRANS("1"), 2);
    pluginOutputChannel->addItem (TRANS("2"), 3);
    pluginOutputChannel->addItem (TRANS("3"), 4);
    pluginOutputChannel->addItem (TRANS("4"), 5);
    pluginOutputChannel->addItem (TRANS("6"), 6);
    pluginOutputChannel->addItem (TRANS("7"), 7);
    pluginOutputChannel->addItem (TRANS("8"), 8);
    pluginOutputChannel->addItem (TRANS("9"), 9);
    pluginOutputChannel->addItem (TRANS("10"), 10);
    pluginOutputChannel->addItem (TRANS("11"), 11);
    pluginOutputChannel->addItem (TRANS("12"), 12);
    pluginOutputChannel->addItem (TRANS("13"), 13);
    pluginOutputChannel->addItem (TRANS("14"), 14);
    pluginOutputChannel->addItem (TRANS("15"), 15);
    pluginOutputChannel->addItem (TRANS("16"), 16);
    pluginOutputChannel->addListener (this);

    addAndMakeVisible (pluginOutput = new ToggleButton ("new toggle button"));
    pluginOutput->setButtonText (TRANS("Enable output to plugin host"));
    pluginOutput->addListener (this);

    addAndMakeVisible (label9 = new Label ("new label",
                                           TRANS("MIDI Channel")));
    label9->setFont (Font (16.00f, Font::bold));
    label9->setJustificationType (Justification::centredLeft);
    label9->setEditable (false, false, false);
    label9->setColour (TextEditor::textColourId, Colours::black);
    label9->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (pluginInput = new ToggleButton ("new toggle button"));
    pluginInput->setButtonText (TRANS("Enable input from plugin host"));
    pluginInput->addListener (this);

    addAndMakeVisible (pluginInputChannel = new ComboBox (String()));
    pluginInputChannel->setEditableText (false);
    pluginInputChannel->setJustificationType (Justification::centredLeft);
    pluginInputChannel->setTextWhenNothingSelected (TRANS("All"));
    pluginInputChannel->setTextWhenNoChoicesAvailable (String());
    pluginInputChannel->addItem (TRANS("All"), 1);
    pluginInputChannel->addItem (TRANS("1"), 2);
    pluginInputChannel->addItem (TRANS("2"), 3);
    pluginInputChannel->addItem (TRANS("3"), 4);
    pluginInputChannel->addItem (TRANS("4"), 5);
    pluginInputChannel->addItem (TRANS("6"), 6);
    pluginInputChannel->addItem (TRANS("7"), 7);
    pluginInputChannel->addItem (TRANS("8"), 8);
    pluginInputChannel->addItem (TRANS("9"), 9);
    pluginInputChannel->addItem (TRANS("10"), 10);
    pluginInputChannel->addItem (TRANS("11"), 11);
    pluginInputChannel->addItem (TRANS("12"), 12);
    pluginInputChannel->addItem (TRANS("13"), 13);
    pluginInputChannel->addItem (TRANS("14"), 14);
    pluginInputChannel->addItem (TRANS("15"), 15);
    pluginInputChannel->addItem (TRANS("16"), 16);
    pluginInputChannel->addListener (this);


    //[UserPreSize]
    oscProtocol->clear();
    oscProtocol->addItem (TRANS("Default"), 1);
    oscProtocol->addItem (TRANS("UDP"), 2);
    oscProtocol->addItem (TRANS("Local/UNIX"), 3);
    oscProtocol->addItem (TRANS("TCP"), 5);
    //[/UserPreSize]

    setSize (400, 500);


    //[Constructor] You can add your own custom stuff here..
    owner.getCtrlrManagerOwner().getCtrlrMidiDeviceManager().reloadComboContents (*inputDevices, inputDevice, &owner);
    owner.getCtrlrManagerOwner().getCtrlrMidiDeviceManager().reloadComboContents (*controllerDevices, controllerDevice, &owner);
    owner.getCtrlrManagerOwner().getCtrlrMidiDeviceManager().reloadComboContents (*outputDevices, outputDevice, &owner);
    oscEnabled->setToggleState (owner.getProperty(Ids::panelOSCEnabled), dontSendNotification);
    oscPort->setText (owner.getProperty(Ids::panelOSCPort), dontSendNotification);
    oscProtocol->setSelectedItemIndex(owner.getProperty(Ids::panelOSCProtocol), dontSendNotification);
    inputChannel->setText (owner.getProperty(Ids::panelMidiInputChannelDevice), dontSendNotification);
    outputChannel->setText (owner.getProperty(Ids::panelMidiOutputChannelDevice), dontSendNotification);
    controllerChannel->setText (owner.getProperty(Ids::panelMidiControllerChannelDevice), dontSendNotification);
    pluginOutputChannel->setText (owner.getProperty(Ids::panelMidiOutputChannelHost), dontSendNotification);
    pluginInputChannel->setText (owner.getProperty(Ids::panelMidiInputChannelHost), dontSendNotification);
    pluginOutput->setToggleState (owner.getProperty(Ids::panelMidiOutputToHost), dontSendNotification);
    pluginInput->setToggleState (owner.getProperty(Ids::panelMidiInputFromHost), dontSendNotification);
}

CtrlrMIDISettingsDevices::~CtrlrMIDISettingsDevices()
{
    inputDevices = nullptr;
    controllerDevices = nullptr;
    outputDevices = nullptr;
    label = nullptr;
    label2 = nullptr;
    label3 = nullptr;
    oscProtocol = nullptr;
    label4 = nullptr;
    oscPort = nullptr;
    label5 = nullptr;
    label6 = nullptr;
    oscEnabled = nullptr;
    label7 = nullptr;
    inputChannel = nullptr;
    controllerChannel = nullptr;
    outputChannel = nullptr;
    label8 = nullptr;
    pluginOutputChannel = nullptr;
    pluginOutput = nullptr;
    label9 = nullptr;
    pluginInput = nullptr;
    pluginInputChannel = nullptr;
}

    void CtrlrMIDISettingsDevices::paint (Graphics& g){}

void CtrlrMIDISettingsDevices::resized()
{
    inputDevices->setBounds (proportionOfWidth (0.0803f), proportionOfHeight (0.1109f), proportionOfWidth (0.6004f), proportionOfHeight (0.0597f));
    controllerDevices->setBounds (proportionOfWidth (0.0803f), proportionOfHeight (0.2409f), proportionOfWidth (0.6004f), proportionOfHeight (0.0597f));
    outputDevices->setBounds (proportionOfWidth (0.0803f), proportionOfHeight (0.3689f), proportionOfWidth (0.6004f), proportionOfHeight (0.0597f));
    label->setBounds (proportionOfWidth (0.0803f), proportionOfHeight (0.0490f), proportionOfWidth (0.6004f), proportionOfHeight (0.0597f));
    label2->setBounds (proportionOfWidth (0.0803f), proportionOfHeight (0.1770f), proportionOfWidth (0.7992f), proportionOfHeight (0.0597f));
    label3->setBounds (proportionOfWidth (0.0803f), proportionOfHeight (0.3028f), proportionOfWidth (0.7992f), proportionOfHeight (0.0597f));
    oscProtocol->setBounds (proportionOfWidth (0.6305f), proportionOfHeight (0.8614f), proportionOfWidth (0.2008f), proportionOfHeight (0.0810f));
    label4->setBounds (proportionOfWidth (0.0803f), proportionOfHeight (0.7313f), proportionOfWidth (0.7992f), proportionOfHeight (0.0810f));
    oscPort->setBounds (proportionOfWidth (0.2309f), proportionOfHeight (0.8614f), proportionOfWidth (0.2992f), proportionOfHeight (0.0810f));
    label5->setBounds (proportionOfWidth (0.6305f), proportionOfHeight (0.8124f), proportionOfWidth (0.2992f), proportionOfHeight (0.0490f));
    label6->setBounds (proportionOfWidth (0.2309f), proportionOfHeight (0.8124f), proportionOfWidth (0.2992f), proportionOfHeight (0.0490f));
    oscEnabled->setBounds (proportionOfWidth (0.0803f), proportionOfHeight (0.8614f), proportionOfWidth (0.0502f), proportionOfHeight (0.0810f));
    label7->setBounds (proportionOfWidth (0.0803f), proportionOfHeight (0.8124f), proportionOfWidth (0.1506f), proportionOfHeight (0.0490f));
    inputChannel->setBounds (proportionOfWidth (0.7410f), proportionOfHeight (0.1109f), proportionOfWidth (0.2008f), proportionOfHeight (0.0597f));
    controllerChannel->setBounds (proportionOfWidth (0.7410f), proportionOfHeight (0.2409f), proportionOfWidth (0.2008f), proportionOfHeight (0.0597f));
    outputChannel->setBounds (proportionOfWidth (0.7410f), proportionOfHeight (0.3689f), proportionOfWidth (0.2008f), proportionOfHeight (0.0597f));
    label8->setBounds (proportionOfWidth (0.0803f), proportionOfHeight (0.4307f), proportionOfWidth (0.7992f), proportionOfHeight (0.0597f));
    pluginOutputChannel->setBounds (proportionOfWidth (0.7410f), proportionOfHeight (0.4968f), proportionOfWidth (0.2008f), proportionOfHeight (0.0597f));
    pluginOutput->setBounds (proportionOfWidth (0.0803f), proportionOfHeight (0.4968f), proportionOfWidth (0.6004f), proportionOfHeight (0.0597f));
    label9->setBounds (proportionOfWidth (0.7209f), proportionOfHeight (0.0490f), proportionOfWidth (0.2410f), proportionOfHeight (0.0597f));
    pluginInput->setBounds (proportionOfWidth (0.0803f), proportionOfHeight (0.6226f), proportionOfWidth (0.6004f), proportionOfHeight (0.0597f));
    pluginInputChannel->setBounds (proportionOfWidth (0.7410f), proportionOfHeight (0.6226f), proportionOfWidth (0.2008f), proportionOfHeight (0.0597f));
}

void CtrlrMIDISettingsDevices::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == inputDevices)
    {
        owner.setProperty(Ids::panelMidiInputDevice, inputDevices->getText());
    }
    else if (comboBoxThatHasChanged == controllerDevices)
    {
        owner.setProperty(Ids::panelMidiControllerDevice, controllerDevices->getText());
    }
    else if (comboBoxThatHasChanged == outputDevices)
    {
        owner.setProperty(Ids::panelMidiOutputDevice, outputDevices->getText());
    }
    else if (comboBoxThatHasChanged == oscProtocol)
    {
        owner.setProperty(Ids::panelOSCProtocol, oscProtocol->getSelectedItemIndex());
    }
    else if (comboBoxThatHasChanged == inputChannel)
    {
        owner.setProperty(Ids::panelMidiInputChannelDevice, inputChannel->getText());
    }
    else if (comboBoxThatHasChanged == controllerChannel)
    {
        owner.setProperty(Ids::panelMidiControllerChannelDevice, controllerChannel->getText());
    }
    else if (comboBoxThatHasChanged == outputChannel)
    {
        owner.setProperty(Ids::panelMidiOutputChannelDevice, outputChannel->getText());
    }
    else if (comboBoxThatHasChanged == pluginOutputChannel)
    {
        owner.setProperty(Ids::panelMidiOutputChannelHost, pluginOutputChannel->getText());
    }
    else if (comboBoxThatHasChanged == pluginInputChannel)
    {
        owner.setProperty(Ids::panelMidiInputChannelHost, pluginInputChannel->getText());
    }
}

void CtrlrMIDISettingsDevices::labelTextChanged (Label* labelThatHasChanged)
{
    if (labelThatHasChanged == oscPort)
    {
        owner.setProperty(Ids::panelOSCPort, oscPort->getText().getIntValue());
    }
}

void CtrlrMIDISettingsDevices::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == oscEnabled)
    {
        owner.setProperty(Ids::panelOSCEnabled, oscEnabled->getToggleState());
    }
    else if (buttonThatWasClicked == pluginOutput)
    {
        owner.setProperty(Ids::panelMidiOutputToHost, pluginOutput->getToggleState());
    }
    else if (buttonThatWasClicked == pluginInput)
    {
        owner.setProperty(Ids::panelMidiInputFromHost, pluginInput->getToggleState());
    }
}