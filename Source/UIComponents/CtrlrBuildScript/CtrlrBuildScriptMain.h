#pragma once
#include "CtrlrWindowManagers/CtrlrChildWindowContent.h"
#include "CtrlrWindowManagers/CtrlrManagerWindowManager.h"
#include "CtrlrBuildScriptIDESection.h"
#include "CtrlrBuildScriptOptionsSection.h"
#include "CtrlrBuildScriptOutputSection.h"
#include "CtrlrBuildScriptVST3Section.h"

class CtrlrManager;

class CtrlrBuildScriptMain : public CtrlrChildWindowContent,
                                     public Label::Listener,
									 public Button::Listener
{
 public:

    CtrlrBuildScriptMain(CtrlrManager &_owner);
    ~CtrlrBuildScriptMain();

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

    void animateButtons();
    
private:
    CtrlrManager &owner;

    std::unique_ptr<CtrlrBuildScriptIDESection>               ideSection;
    std::unique_ptr<CtrlrBuildScriptOptionsSection>           optionsSection;
    std::unique_ptr<CtrlrBuildScriptOutputSection>	          outputSection;
    std::unique_ptr<CtrlrBuildScriptVST3Section>              vst3Section;

    std::unique_ptr<TextButton>               saveFileButton;
    std::unique_ptr<TextButton>               loadFileButton;

    std::unique_ptr<TextButton>               okButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CtrlrBuildScriptMain)
};