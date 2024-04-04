#pragma once
#include "stdafx.h"
#include "CtrlrBuildScriptOutputSection.h" 

class CtrlrBuildScriptIDESection : public Component, 
                                    public Button::Listener
{
public:
    CtrlrBuildScriptIDESection(CtrlrBuildScriptOutputSection *outputSection);
    ~CtrlrBuildScriptIDESection();

    void paint(Graphics& g);
    void paintOverChildren(Graphics& g);
    void resized() override;
    void buttonClicked(Button* button);
    void mouseDown(const MouseEvent& event);
   
    String getIDE() { return cIDE->getText(); }
    String getBuildFolderPath() { return lBuildFolder->getText(); }
    String getVSTFolderPath() { return lVSTFolder->getText(); }
    String getDAWFolderPath() { return lDAWFolder->getText(); }

    int   getIDEIndex() { return cIDE->getSelectedItemIndex(); }
    void  setIDEIndex(int index) { cIDE->setSelectedItemIndex(index); }
    void  setBuildFolderPath(String path) { this->buildFolderPath = path; }
    void  setVSTFolderPath(String path) { this->vstFolderPath = path; }
    void  setDAWFolderPath(String path) { this->dawFolderPath = path; }
    void  setBuildFolder(String Text) { lBuildFolder->setText(Text, dontSendNotification); }

    //ComboBox*   IDESection::getIDEComboBox() { return cIDE; }
    ComboBox* CtrlrBuildScriptIDESection::getIDEComboBox() { return cIDE.get(); }
    Label* CtrlrBuildScriptIDESection::getBuildFolderLabel() { return lBuildFolder.get(); }
    Label* CtrlrBuildScriptIDESection::getVSTFolderLabel() { return lVSTFolder.get(); }
    Label* CtrlrBuildScriptIDESection::getDAWFolderLabel() { return lDAWFolder.get(); }

private:
    std::unique_ptr<Label>      lIDE;
    std::unique_ptr<ComboBox>   cIDE;
    std::unique_ptr<TextButton> bBuildFolder;

    std::unique_ptr<Label>      lBuildFolder;
    std::unique_ptr<TextButton> bVSTFolder;
    std::unique_ptr<Label>      lVSTFolder;
	std::unique_ptr<TextButton> bDAWFolder;
    std::unique_ptr<Label>      lDAWFolder;

    int         IDEIndex;
    String      buildFolderPath;
    String      vstFolderPath;
    String      dawFolderPath;

    juce::Rectangle<int> questionMarkArea;
    CtrlrBuildScriptOutputSection *outputSection;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CtrlrBuildScriptIDESection)
};