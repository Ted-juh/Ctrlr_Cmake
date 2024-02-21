#include "stdafx.h"
#include "CtrlrBuildScriptDialogWindow.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "JuceHeader.h"

CtrlrBuildScriptDialogWindow::CtrlrBuildScriptDialogWindow()
{
    addAndMakeVisible(debugButton);
    debugButton.setButtonText("Debug");
    debugButton.addListener(this);
    addAndMakeVisible(releaseButton);
    releaseButton.setButtonText("Release");
    releaseButton.addListener(this);
    addAndMakeVisible(VST2Button);
    VST2Button.setButtonText("VST2");
    VST2Button.addListener(this);
    addAndMakeVisible(VST3Button);
    VST3Button.setButtonText("VST3");
    VST3Button.addListener(this);

    addAndMakeVisible(cancelButton);
    cancelButton.setButtonText("Cancel");
    cancelButton.addListener(this);
    addAndMakeVisible(okButton);
    okButton.setVisible(false);
    okButton.setButtonText("OK");
    okButton.addListener(this);

    addAndMakeVisible(cleanBuildButton);
    cleanBuildButton.setVisible(false);
    cleanBuildButton.setButtonText("Clean Build?");
    cleanBuildButton.addListener(this);
    addAndMakeVisible(buildFolderButton);
    buildFolderButton.setVisible(false);
    buildFolderButton.setButtonText("Open /build Folder?");
    buildFolderButton.addListener(this);

    addAndMakeVisible(vstFolderButton);
    vstFolderButton.setVisible(false);
    vstFolderButton.setButtonText("Open VST Folder?");
    vstFolderButton.addListener(this);
    addAndMakeVisible(dawButton);
    dawButton.setVisible(false);
    dawButton.setButtonText("Open Daw?");
    dawButton.addListener(this);

    setSize(440, 190);
    setCentreRelative(0.5f, 0.5f);
    setVisible(true);
    toFront(true);
    enterModalState();
    setAlwaysOnTop(true);
}

CtrlrBuildScriptDialogWindow::~CtrlrBuildScriptDialogWindow(){}

void CtrlrBuildScriptDialogWindow::paint(Graphics& g)
{
    g.fillAll(Colours::lightgrey);

    g.setColour(Colours::black);
    g.setFont(Font(16.0f, Font::bold));
    g.drawText("Choose the project configuration to build", 0, 5, getWidth(), 30, Justification::centred, true);

    g.setColour(Colours::whitesmoke);
    g.fillRect(5, 35, getWidth() - 10, 30);

    g.setColour(Colours::black);
    g.setFont(Font(14.0f, Font::bold));
    g.drawText("Extra options", 0, 60, getWidth(), 30, Justification::centred, true);

    g.setColour(Colours::whitesmoke);
    g.fillRect(5, 85, getWidth() - 10, 60);
}

void CtrlrBuildScriptDialogWindow::resized()
{
    const int startX = getWidth() * 0.01;
    const int xDivided = getWidth() / 4;

    debugButton.setBounds       (startX,                    35, 110, 30);
    releaseButton.setBounds     (startX + xDivided,         35, 110, 30);
    VST2Button.setBounds        (startX + (xDivided * 2),   35, 110, 30);
    VST3Button.setBounds        (startX + (xDivided * 3),   35, 110, 30);

    cleanBuildButton.setBounds  (startX,                    85,    150, 30);
    buildFolderButton.setBounds (startX,                    115,   150, 30);
    vstFolderButton.setBounds   (startX + (xDivided *2),    85, 150, 30);
    dawButton.setBounds         (startX + (xDivided * 2),   115, 150, 30);

    cancelButton.setBounds(10, getHeight() - 40, 100, 30);
    okButton.setBounds(getWidth() - 110, getHeight() - 40, 100, 30);
}

void CtrlrBuildScriptDialogWindow::buttonClicked(Button* button)
{
    if (button == &cancelButton)
    {
		window->exitModalState(0);
    }

    if (button == &okButton)
    {
		generateAndExecuteBuildScript();
	}

    vstFolderButton.setVisible (
                                    VST2Button.getToggleState() || 
                                    VST3Button.getToggleState()
                                );

    dawButton.setVisible (
                          VST2Button.getToggleState() || 
                          VST3Button.getToggleState()
                         );

    cleanBuildButton.setVisible(
								debugButton.getToggleState() || 
								releaseButton.getToggleState()
								);

    buildFolderButton.setVisible(
                                 debugButton.getToggleState() || 
                                 releaseButton.getToggleState()
                                );

    okButton.setVisible(
                        debugButton.getToggleState() || 
                        releaseButton.getToggleState() || 
                        VST2Button.getToggleState() || 
                        VST3Button.getToggleState()
                        );  
}

void CtrlrBuildScriptDialogWindow::generateAndExecuteBuildScript()
{
    // Generate the build script
    File buildScriptFile = File::getSpecialLocation(File::userDesktopDirectory).getFullPathName() + "/BuildScript.ps1";

    //Write to the build script
    buildScriptFile.appendText("# Directory where the /build folder is located\n");

    //get Ids::panelBatchProjectDir from getPanelBatchProjectDir from CtrlrPanel
    //String buildDir = panel->getPanelBatchProjectDir();
    //buildScriptFile.appendText("$buildDir = \"" + buildDir + "\"\n");

} 
