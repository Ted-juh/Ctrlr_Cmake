#pragma once
#include "CtrlrMacros.h"

class CtrlrLuaMethodEditor;

class CtrlrMethodEditorTabCloseButton  : public Button
{
public:

    CtrlrMethodEditorTabCloseButton (CtrlrLuaMethodEditor &_owner, const int _tabIndex);
    ~CtrlrMethodEditorTabCloseButton();

    void resized();
    void paintButton (Graphics& g, bool isMouseOverButton, bool isButtonDown);
    void mouseDown (const MouseEvent& e);

private:

	CtrlrLuaMethodEditor &owner;
	int tabIndex;
    Path internalPath1;
    Path internalPath2;
    Path internalPath3;
    Path internalPath4;
    Path internalPath5;
    Path internalPath6;

    CtrlrMethodEditorTabCloseButton (const CtrlrMethodEditorTabCloseButton&);
    const CtrlrMethodEditorTabCloseButton& operator= (const CtrlrMethodEditorTabCloseButton&);

    JUCE_LEAK_DETECTOR (CtrlrMethodEditorTabCloseButton)
};