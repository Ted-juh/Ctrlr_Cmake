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

    int IDESection::getIDEIndex() { return cIDE->getSelectedItemIndex(); }

private:
    Label* lIDE;
    ComboBox* cIDE;
    TextButton* bBuildFolder;
    Label* lBuildFolder;
    TextButton* bVSTFolder;
    Label* lVSTFolder;
    TextButton* bDAWFolder;
    Label* lDAWFolder;
};