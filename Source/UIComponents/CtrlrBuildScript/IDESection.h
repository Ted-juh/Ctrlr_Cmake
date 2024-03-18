#include "stdafx.h"

class IDESection : public Component, public Button::Listener
{
public:
    IDESection();
    ~IDESection();

    void IDESection::paint(Graphics& g);
    void IDESection::paintOverChildren(Graphics& g);
    void IDESection::resized();
    void IDESection::buttonClicked(Button* button);

    String IDESection::getIDE() { return cIDE->getText(); }
    String IDESection::getBuildFolderPath() { return lBuildFolder->getText(); }
    String IDESection::getVSTFolderPath() { return lVSTFolder->getText(); }
    String IDESection::getDAWFolderPath() { return lDAWFolder->getText(); }

    int   IDESection::getIDEIndex() { return cIDE->getSelectedItemIndex(); }
    void  IDESection::setIDEIndex(int index) { cIDE->setSelectedItemIndex(index); }
    void  IDESection::setBuildFolderPath(String path) { this->buildFolderPath = path; }
    void  IDESection::setVSTFolderPath(String path) { this->vstFolderPath = path; }
    void  IDESection::setDAWFolderPath(String path) { this->dawFolderPath = path; }
    void  IDESection::setBuildFolder(String Text) { lBuildFolder->setText(Text, dontSendNotification); }

    //ComboBox*   IDESection::getIDEComboBox() { return cIDE; }
    Label*      IDESection::getBuildFolderLabel() { return lBuildFolder; }
    Label*      IDESection::getVSTFolderLabel() { return lVSTFolder; }
    Label*      IDESection::getDAWFolderLabel() { return lDAWFolder; }




private:
    Label*      lIDE;
    ComboBox*   cIDE;
    TextButton* bBuildFolder;
    Label*      lBuildFolder;
    TextButton* bVSTFolder;
    Label*      lVSTFolder;
    TextButton* bDAWFolder;
    Label*      lDAWFolder;

    int         IDEIndex;
    String      buildFolderPath;
    String      vstFolderPath;
    String      dawFolderPath;
};