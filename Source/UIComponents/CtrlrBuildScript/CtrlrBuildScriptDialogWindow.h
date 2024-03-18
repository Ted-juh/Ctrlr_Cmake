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

    ScopedPointer<IDESection>                       ideSection;
    ScopedPointer<OptionsSection>                   optionsSection;
    ScopedPointer<OutputSection>	                outputSection;

    ScopedPointer<TextButton>                       saveFileButton;
    ScopedPointer<TextButton>                       loadFileButton;

    ScopedPointer<TextButton>                       okButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CtrlrBuildScriptDialogWindow)
};