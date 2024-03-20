#pragma once
#include "CtrlrWindowManagers/CtrlrChildWindowContent.h"
#include "CtrlrWindowManagers/CtrlrManagerWindowManager.h"
#include "IDESection.h"
#include "OptionsSection.h"
#include "OutputSection.h"

class CtrlrManager;

class CtrlrBuildScriptDialogWindow : public CtrlrChildWindowContent,
                                     public Label::Listener,
									 public Button::Listener
{
 public:

    CtrlrBuildScriptDialogWindow(CtrlrManager &_owner);
    ~CtrlrBuildScriptDialogWindow();

    String getContentName()             { return ("Build Script Editor"); }
    uint8 getType()                     { return (CtrlrManagerWindowManager::BuildScript);}

    void paint (Graphics& g);
    void paintOverChildren (Graphics& g);
    void resized();

    void setButtonStateAndColour(TextButton* button, bool state);
    void buttonClicked(Button* buttonThatWasClicked);
    void buttonStateChanged(Button* button);
    void setOkButtonVisible (const bool isVisible);

    void labelTextChanged (Label* labelThatHasChanged);

    void checkCMake();
    void openBuildFolder();
    void generateBuildFiles();
    void buildFiles();

    void saveOptionsToFile();
    void loadOptionsFromFile();

    int getIDEIndex() { return ideSection->getIDEIndex(); }
    
private:
    CtrlrManager &owner;

    std::unique_ptr<IDESection>               ideSection;
    std::unique_ptr<OptionsSection>           optionsSection;
    std::unique_ptr<OutputSection>	          outputSection;

    std::unique_ptr<TextButton>               saveFileButton;
    std::unique_ptr<TextButton>               loadFileButton;

    std::unique_ptr<TextButton>               okButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CtrlrBuildScriptDialogWindow)
};