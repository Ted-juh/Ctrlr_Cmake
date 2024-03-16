#include "stdafx.h"
#include "OptionsSection.h"
#include "CtrlrBuildScriptDialogWindow.h"

OptionsSection::OptionsSection()
{
    addAndMakeVisible(cCMakeButton = new TextButton(""));
    cCMakeButton->setButtonText("Check CMake");
    cCMakeButton->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
    cCMakeButton->addListener(this);

    addAndMakeVisible(buildButton = new TextButton(""));
    buildButton->setButtonText("Build files");
    buildButton->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
    buildButton->addListener(this);

    addAndMakeVisible(releaseButton = new TextButton(""));
    releaseButton->setButtonText("Release");
    releaseButton->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
    releaseButton->addListener(this);

    addAndMakeVisible(VST3Button = new TextButton(""));
    VST3Button->setButtonText("VST3");
    VST3Button->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
    VST3Button->addListener(this);

    addAndMakeVisible(cleanBuildButton = new TextButton(""));
    cleanBuildButton->setButtonText("Clean->Rebuild");
    cleanBuildButton->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
    cleanBuildButton->setVisible(false);
    cleanBuildButton->addListener(this);

    addAndMakeVisible(vstFolderButton = new TextButton(""));
    vstFolderButton->setButtonText("VST Folder");
    vstFolderButton->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
    vstFolderButton->setVisible(false);
    vstFolderButton->addListener(this);

    addAndMakeVisible(dawButton = new TextButton(""));
    dawButton->setButtonText("Open DAW");
    dawButton->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
    dawButton->setVisible(false);
    dawButton->addListener(this);

    addAndMakeVisible(buildFolderButton = new TextButton(""));
    buildFolderButton->setButtonText("Open build folder");
    buildFolderButton->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
    buildFolderButton->setVisible(false);
    buildFolderButton->addListener(this);

    setSize(240, 115);
}

OptionsSection::~OptionsSection()
{
	cCMakeButton = nullptr;
	buildButton = nullptr;
	releaseButton = nullptr;
	VST3Button = nullptr;
	cleanBuildButton = nullptr;
	vstFolderButton = nullptr;
	dawButton = nullptr;
	buildFolderButton = nullptr;
}

void OptionsSection::paint (Graphics& g)
{
    const int space = getHeight() / 10;
    const int buttonHeight = (getHeight() - space) / 4;



    // Space for Title Project Options
    g.setColour(Colours::darkgrey);
    g.fillRect(                                             0,      0,                           getWidth(),        buttonHeight);
    //Title Project Options
    g.setColour(Colours::white);
    g.setFont(Font(14.0f, Font::bold));
    g.drawText("Choose the project configuration to build", 5,      0,                           getWidth(),        buttonHeight, Justification::left, true);
    // Space for  Project Option Buttons 
    g.setColour(Colours::whitesmoke);
    g.fillRect(                                             0,      buttonHeight,                getWidth(),        buttonHeight);

    // Title Extra Options
    g.setColour(Colours::darkgrey);
    g.fillRect(                                             0,      buttonHeight * 2 + space,    getWidth(),        buttonHeight);
    // Space for Extra Options Title
    g.setColour(Colours::white);
    g.setFont(Font(14.0f, Font::bold));
    g.drawText("Extra options",                             5,      buttonHeight * 2 + space,    getWidth(),        buttonHeight, Justification::left, true);
    // Space for Extra Options Buttons
    g.setColour(Colours::whitesmoke);
    g.fillRect(                                             0,      buttonHeight * 3 + space,    getWidth(),        buttonHeight);
}

void OptionsSection::paintOverChildren(Graphics& g)
{

    const int space = getHeight() / 10;
    const int buttonHeight = (getHeight() - space) / 4;

    const int amountBut = 4;
    const int buttonSpace = getWidth() / amountBut;

    g.setColour(Colours::darkgrey);
    g.drawRect(0, buttonHeight, getWidth(), buttonHeight, 1.0);
    g.drawRect(0, buttonHeight * 3 + space, getWidth(), buttonHeight, 1.0);

    g.drawLine(buttonSpace,         buttonHeight,               buttonSpace,        buttonHeight * 2,           1.0);
    g.drawLine(buttonSpace * 2,     buttonHeight,               buttonSpace * 2,    buttonHeight * 2,           1.0);
    g.drawLine(buttonSpace * 3,     buttonHeight,               buttonSpace * 3,    buttonHeight * 2,           1.0);

    g.drawLine(buttonSpace * 2,     buttonHeight * 3 + space,   buttonSpace * 2,    buttonHeight * 4 + space,   1.0);

}

void OptionsSection::resized()
{
    const int space = getHeight() / 10;
    const int buttonHeight = (getHeight() - space) / 4;

    const int amountBut = 4;
    const int buttonSpace = getWidth() / amountBut;
    
    //Options Buttons                   X                   Y                           W               H
    cCMakeButton        ->setBounds(0,                      buttonHeight,               buttonSpace,        buttonHeight);
    buildButton         ->setBounds(0 + (buttonSpace),      buttonHeight,               buttonSpace,        buttonHeight);
    releaseButton       ->setBounds(0 + (buttonSpace * 2),  buttonHeight,               buttonSpace,        buttonHeight);
    VST3Button          ->setBounds(0 + (buttonSpace * 3),  buttonHeight,               buttonSpace  + 3,   buttonHeight);

    //Extra Options Buttons
    cleanBuildButton    ->setBounds(0,                      buttonHeight * 3 + space,   buttonSpace * 2,    buttonHeight);
    buildFolderButton   ->setBounds(0 + (buttonSpace * 2),  buttonHeight * 3 + space,   buttonSpace * 2,    buttonHeight);

    vstFolderButton     ->setBounds(0,                      buttonHeight * 3 + space,   buttonSpace * 2,    buttonHeight);
    dawButton           ->setBounds(0 + (buttonSpace * 2),  buttonHeight * 3 + space,   buttonSpace * 2,    buttonHeight);

}

void OptionsSection::setButtonStateAndColour(TextButton* button, bool state)
{
    button->setToggleState(state, dontSendNotification);
    button->setColour(TextButton::buttonColourId, state ? Colours::darkgrey : Colours::whitesmoke);         // on/off
    button->setColour(TextButton::buttonOnColourId, state ? Colours::darkgrey : Colours::whitesmoke);       // on/off
    button->setColour(TextButton::textColourOffId, state ? Colours::black : Colours::black);                // on/off
    button->setColour(TextButton::textColourOnId, state ? Colours::white : Colours::white);			        // on/off          
}

void OptionsSection::buttonClicked(Button *button)
{

    if (button == cCMakeButton)
    {
        setButtonStateAndColour(cCMakeButton, !cCMakeButton->getToggleState());
        if (cCMakeButton->getToggleState()) {
            setButtonStateAndColour(releaseButton, false);
            setButtonStateAndColour(buildButton, false);
            setButtonStateAndColour(VST3Button, false);
        }
    }

    if (button == buildButton)
    {
        setButtonStateAndColour(buildButton, !buildButton->getToggleState());
        if (buildButton->getToggleState()) {
            setButtonStateAndColour(cCMakeButton, false);
            setButtonStateAndColour(releaseButton, false);
            setButtonStateAndColour(VST3Button, false);
        }
    }

    if (button == releaseButton)
    {
        setButtonStateAndColour(releaseButton, !releaseButton->getToggleState());
        if (releaseButton->getToggleState()) {
            setButtonStateAndColour(cCMakeButton, false);
            setButtonStateAndColour(buildButton, false);
            setButtonStateAndColour(VST3Button, false);
        }
    }

    if (button == VST3Button)
    {
        setButtonStateAndColour(VST3Button, !VST3Button->getToggleState());
        if (VST3Button->getToggleState()) {
            setButtonStateAndColour(cCMakeButton, false);
            setButtonStateAndColour(releaseButton, false);
            setButtonStateAndColour(buildButton, false);
        }
    }
    if (button == cleanBuildButton) { setButtonStateAndColour(cleanBuildButton, !cleanBuildButton->getToggleState()); }
    if (button == buildFolderButton) { setButtonStateAndColour(buildFolderButton, !buildFolderButton->getToggleState()); }
    if (button == vstFolderButton) { setButtonStateAndColour(vstFolderButton, !vstFolderButton->getToggleState()); }
    if (button == dawButton) { setButtonStateAndColour(dawButton, !dawButton->getToggleState()); }

    vstFolderButton->setVisible(VST3Button->getToggleState());
    dawButton->setVisible(VST3Button->getToggleState());
    cleanBuildButton->setVisible(releaseButton->getToggleState());
    buildFolderButton->setVisible(releaseButton->getToggleState() || buildButton->getToggleState());

    ((CtrlrBuildScriptDialogWindow*)findParentComponentOfClass<CtrlrBuildScriptDialogWindow>())->setOkButtonVisible(cCMakeButton->getToggleState() || buildButton->getToggleState() || releaseButton->getToggleState() || VST3Button->getToggleState());
}