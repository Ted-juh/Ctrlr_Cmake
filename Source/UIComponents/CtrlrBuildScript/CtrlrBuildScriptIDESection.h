#include "stdafx.h"

class CtrlrBuildScriptIDESection : public Component, public Button::Listener
{
public:
    CtrlrBuildScriptIDESection();
    ~CtrlrBuildScriptIDESection();

    void CtrlrBuildScriptIDESection::paint(Graphics& g);
    void CtrlrBuildScriptIDESection::paintOverChildren(Graphics& g);
    void CtrlrBuildScriptIDESection::resized();
    void CtrlrBuildScriptIDESection::buttonClicked(Button* button);

    String CtrlrBuildScriptIDESection::getIDE() { return cIDE->getText(); }
    String CtrlrBuildScriptIDESection::getBuildFolderPath() { return lBuildFolder->getText(); }
    String CtrlrBuildScriptIDESection::getVSTFolderPath() { return lVSTFolder->getText(); }
    String CtrlrBuildScriptIDESection::getDAWFolderPath() { return lDAWFolder->getText(); }

    int   CtrlrBuildScriptIDESection::getIDEIndex() { return cIDE->getSelectedItemIndex(); }
    void  CtrlrBuildScriptIDESection::setIDEIndex(int index) { cIDE->setSelectedItemIndex(index); }
    void  CtrlrBuildScriptIDESection::setBuildFolderPath(String path) { this->buildFolderPath = path; }
    void  CtrlrBuildScriptIDESection::setVSTFolderPath(String path) { this->vstFolderPath = path; }
    void  CtrlrBuildScriptIDESection::setDAWFolderPath(String path) { this->dawFolderPath = path; }
    void  CtrlrBuildScriptIDESection::setBuildFolder(String Text) { lBuildFolder->setText(Text, dontSendNotification); }

    //ComboBox*   IDESection::getIDEComboBox() { return cIDE; }
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
};