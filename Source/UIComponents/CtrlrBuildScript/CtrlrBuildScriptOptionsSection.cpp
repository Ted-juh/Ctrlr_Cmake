#pragma once
#include "stdafx.h"
#include "CtrlrBuildScriptOptionsSection.h"
#include "CtrlrBuildScriptMain.h"

CtrlrBuildScriptOptionsSection::CtrlrBuildScriptOptionsSection(CtrlrBuildScriptOutputSection *outputSection) : outputSection(outputSection)
{
    cCMakeButton = std::make_unique<TextButton>("");
    addAndMakeVisible(*cCMakeButton);
    cCMakeButton->setButtonText("Check CMake");
    cCMakeButton->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
    cCMakeButton->addListener(this);

    buildButton = std::make_unique<TextButton>("");
    addAndMakeVisible(*buildButton);
    buildButton->setButtonText("Generate build files");
    buildButton->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
    buildButton->addListener(this);

    releaseButton = std::make_unique<TextButton>("");
    addAndMakeVisible(*releaseButton);
    releaseButton->setButtonText("Release");
    releaseButton->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
    releaseButton->addListener(this);

    VST3Button = std::make_unique<TextButton>("");
    addAndMakeVisible(*VST3Button);
    VST3Button->setButtonText("VST3");
    VST3Button->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
    VST3Button->addListener(this);

    cleanBuildButton = std::make_unique<TextButton>("");
    addAndMakeVisible(*cleanBuildButton);
    cleanBuildButton->setButtonText("Clean->Rebuild");
    cleanBuildButton->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
    cleanBuildButton->setVisible(false);
    cleanBuildButton->addListener(this);

    vstFolderButton = std::make_unique<TextButton>("");
    addAndMakeVisible(*vstFolderButton);
    vstFolderButton->setButtonText("VST Folder");
    vstFolderButton->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
    vstFolderButton->setVisible(false);
    vstFolderButton->addListener(this);

    dawButton = std::make_unique<TextButton>("");
    addAndMakeVisible(*dawButton);
    dawButton->setButtonText("Open DAW");
    dawButton->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
    dawButton->setVisible(false);
    dawButton->addListener(this);

    buildFolderButton = std::make_unique<TextButton>("");
    addAndMakeVisible(*buildFolderButton);
    buildFolderButton->setButtonText("Open build folder");
    buildFolderButton->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
    buildFolderButton->setVisible(false);
    buildFolderButton->addListener(this);

}

CtrlrBuildScriptOptionsSection::~CtrlrBuildScriptOptionsSection(){}

void CtrlrBuildScriptOptionsSection::paint (Graphics& g)
{
    const int w   = getWidth();
    const int y   = getHeight();

    const int space = y / 10;
    const int buttonHeight = (y - space) / 4;

    const int qmX = static_cast<int>(w * 0.941f);
    const int qmY = static_cast<int>(y * 0.02f);
 
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

    // Space for Question Mark
    g.setColour(Colours::darkgrey);
    g.fillRect(                             qmX,         qmY,               buttonHeight - qmY,     buttonHeight -  (2 * qmY));
    g.setColour(Colours::whitesmoke);
    g.drawRect(                             qmX,         qmY,               buttonHeight - qmY,     buttonHeight -  (2 * qmY),    1);
    g.setFont(Font(17.0f, Font::bold));
    g.drawText("?",                         qmX,         qmY,               buttonHeight - qmY,     buttonHeight -  (2 * qmY), Justification::centred, true);

    questionMarkAreaOptions = juce::Rectangle<int>(qmX, qmY, buttonHeight - qmY, buttonHeight - (2 * qmY));
}

void CtrlrBuildScriptOptionsSection::paintOverChildren(Graphics& g)
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

void CtrlrBuildScriptOptionsSection::resized()
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
    buildFolderButton   ->setBounds(0 + (buttonSpace * 2),  buttonHeight * 3 + space,   buttonSpace * 2 + 3,    buttonHeight);

    vstFolderButton     ->setBounds(0,                      buttonHeight * 3 + space,   buttonSpace * 2,    buttonHeight);
    dawButton           ->setBounds(0 + (buttonSpace * 2),  buttonHeight * 3 + space,   buttonSpace * 2 + 3,    buttonHeight);

}

void CtrlrBuildScriptOptionsSection::setButtonStateAndColour(TextButton* button, bool state)
{
    button->setToggleState(state, dontSendNotification);
    button->setColour(TextButton::buttonColourId, state ? Colours::darkgrey : Colours::whitesmoke);         // on/off
    button->setColour(TextButton::buttonOnColourId, state ? Colours::darkgrey : Colours::whitesmoke);       // on/off
    button->setColour(TextButton::textColourOffId, state ? Colours::black : Colours::black);                // on/off
    button->setColour(TextButton::textColourOnId, state ? Colours::white : Colours::white);			        // on/off          
}

void CtrlrBuildScriptOptionsSection::buttonClicked(Button *button)
{

    if (button == cCMakeButton.get())
    {
        setButtonStateAndColour(cCMakeButton.get(), !cCMakeButton->getToggleState());
        if (cCMakeButton->getToggleState()) {
            setButtonStateAndColour(buildButton.get(), false);
            setButtonStateAndColour(buildFolderButton.get(), false);
            setButtonStateAndColour(releaseButton.get(), false);
            setButtonStateAndColour(cleanBuildButton.get(), false);
            setButtonStateAndColour(VST3Button.get(), false);
            setButtonStateAndColour(vstFolderButton.get(), false);
            setButtonStateAndColour(dawButton.get(), false);
        }
    }

    if (button == buildButton.get())
    {
        setButtonStateAndColour(buildButton.get(), !buildButton->getToggleState());
        if (buildButton->getToggleState()) {
            setButtonStateAndColour(cCMakeButton.get(), false);
            setButtonStateAndColour(releaseButton.get(), false);
            setButtonStateAndColour(buildFolderButton.get(), false);
            setButtonStateAndColour(cleanBuildButton.get(), false);

            setButtonStateAndColour(VST3Button.get(), false);
            setButtonStateAndColour(vstFolderButton.get(), false);
            setButtonStateAndColour(dawButton.get(), false);
        }
    }

    if (button == releaseButton.get())
    {
        setButtonStateAndColour(releaseButton.get(), !releaseButton->getToggleState());
        if (releaseButton->getToggleState()) {
            setButtonStateAndColour(cCMakeButton.get(), false);
            setButtonStateAndColour(buildButton.get(), false);
            setButtonStateAndColour(buildFolderButton.get(), false);
            setButtonStateAndColour(VST3Button.get(), false);
            setButtonStateAndColour(vstFolderButton.get(), false);
            setButtonStateAndColour(dawButton.get(), false);
        }
    }

    if (button == VST3Button.get())
    {
        setButtonStateAndColour(VST3Button.get(), !VST3Button->getToggleState());

        if (VST3Button->getToggleState()) {
            setButtonStateAndColour(cCMakeButton.get(), false);
            setButtonStateAndColour(releaseButton.get(), false);
            setButtonStateAndColour(buildButton.get(), false);
            setButtonStateAndColour(buildFolderButton.get(), false);
            setButtonStateAndColour(cleanBuildButton.get(), false);
		}
    }

    if (button == cleanBuildButton.get())   { setButtonStateAndColour(cleanBuildButton.get(),   !cleanBuildButton   ->getToggleState()); }
    if (button == buildFolderButton.get())  { setButtonStateAndColour(buildFolderButton.get(),  !buildFolderButton  ->getToggleState()); }
    if (button == vstFolderButton.get())    { setButtonStateAndColour(vstFolderButton.get(),    !vstFolderButton    ->getToggleState()); }
    if (button == dawButton.get())          { setButtonStateAndColour(dawButton.get(),          !dawButton          ->getToggleState()); }

    vstFolderButton->setVisible(VST3Button->getToggleState());
    dawButton->setVisible(VST3Button->getToggleState());
    cleanBuildButton->setVisible(releaseButton->getToggleState());
    buildFolderButton->setVisible(releaseButton->getToggleState() || buildButton->getToggleState());

    ((CtrlrBuildScriptMain*)findParentComponentOfClass<CtrlrBuildScriptMain>())->setOkButtonVisible(cCMakeButton->getToggleState() || buildButton->getToggleState() || releaseButton->getToggleState() || VST3Button->getToggleState());
}

void CtrlrBuildScriptOptionsSection::mouseDown(const juce::MouseEvent& event)
{
    if (questionMarkAreaOptions.contains(event.getPosition()))
        {
            if (outputSection != nullptr)
            {
                outputSection->getOutputView().clear();
                outputSection->setFont(Font(15.0f, Font::bold));
                outputSection->insertTextAtCaret("Check CMake: \n");
                outputSection->setFont(Font(14.0f, Font::plain));
                outputSection->insertTextAtCaret(
                                        "Checks if CMake is added to the System Path.\n\n");
                outputSection->setFont(Font(15.0f, Font::bold));
                outputSection->insertTextAtCaret("Generate Build Files: \n");
                outputSection->setFont(Font(14.0f, Font::plain));
                outputSection->insertTextAtCaret( 
                                        "Generates the build files to debug, release or VST3.\n\n");
                outputSection->setFont(Font(15.0f, Font::bold));
                outputSection->insertTextAtCaret("Release / VST3 \n");
                outputSection->setFont(Font(14.0f, Font::plain));
                outputSection->insertTextAtCaret(
                                        "Builds the actual Release Version or ctrlr.vst3 with given credentials.\n\n");
                outputSection->setFont(Font(15.0f, Font::bold));
                outputSection->insertTextAtCaret("Clean->Rebuild: \n");
                outputSection->setFont(Font(14.0f, Font::plain));
                outputSection->insertTextAtCaret(
                                        "Cleans the build folder and generates the project files as new.\n"
                                        "This is usually a last resort if the project folder is corrupted.\n\n");
                outputSection->setFont(Font(15.0f, Font::bold));
                outputSection->insertTextAtCaret("Open Build/ VST3 Folder \n");
                outputSection->setFont(Font(14.0f, Font::plain));
                outputSection->insertTextAtCaret(
                                        "Opens the build folder or VST3 folder of choice in the file explorer\n\n");
                outputSection->setFont(Font(15.0f, Font::bold));
                outputSection->insertTextAtCaret("Open DAW: \n");
                outputSection->setFont(Font(14.0f, Font::plain));
                outputSection->insertTextAtCaret(
                                        "Should open the DAW folder or nameofdaw.exe after building the VST3. (Experimental)\n\n");
            }
        }
}
