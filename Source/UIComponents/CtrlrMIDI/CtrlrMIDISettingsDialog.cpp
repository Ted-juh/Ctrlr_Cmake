#include "stdafx.h"
#include "CtrlrInlineUtilitiesGUI.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"
#include "CtrlrMIDISettingsDialog.h"
#include "CtrlrMIDISettingsDevices.h"
#include "CtrlrMIDISettingsRouting.h"

CtrlrMIDISettingsDialog::CtrlrMIDISettingsDialog (CtrlrPanel &_owner)
    : owner(_owner)
{
    addAndMakeVisible (midiTabs = new TabbedComponent (TabbedButtonBar::TabsAtTop));
    midiTabs->setTabBarDepth (30);
    midiTabs->addTab (TRANS("Devices"), Colour (0xa2d2d2d2), new CtrlrMIDISettingsDevices (owner), true);
    midiTabs->addTab (TRANS("Routing"), Colour (0xa1d2d2d2), new CtrlrMIDISettingsRouting (owner), true);
    midiTabs->setCurrentTabIndex (0);

    setSize (500, 500);
}

CtrlrMIDISettingsDialog::~CtrlrMIDISettingsDialog()
{
    midiTabs = nullptr;
}

void CtrlrMIDISettingsDialog::resized()
{
    midiTabs->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
}

void CtrlrMIDISettingsDialog::showDialog(CtrlrPanel &_owner)
{
    DialogWindow::LaunchOptions opts;
    auto* dialogContent = new CtrlrMIDISettingsDialog(_owner);
    opts.content.setOwned(dialogContent);
    opts.dialogTitle = "MIDI Settings";
    opts.componentToCentreAround = dynamic_cast<Component*>(_owner.getEditor());
    opts.dialogBackgroundColour = Colours::white;
    opts.useNativeTitleBar = true;
    opts.useBottomRightCornerResizer = true;
    opts.resizable = true;
    opts.escapeKeyTriggersCloseButton = true;
    opts.runModal();
}
