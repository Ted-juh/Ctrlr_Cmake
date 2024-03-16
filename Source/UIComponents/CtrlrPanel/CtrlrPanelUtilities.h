#pragma once
#include "CtrlrMacros.h"

class CtrlrPanelEditor;

class CtrlrPanelUtilities  : public Component,
                             public ChangeListener
{
public:
    CtrlrPanelUtilities (CtrlrPanelEditor &_owner);
    ~CtrlrPanelUtilities();

    void changeListenerCallback (ChangeBroadcaster* source);
	void visibilityChanged();
	void reloadContent();
    void paint (Graphics& g);
    void resized();

private:
	CtrlrPanelEditor &owner;
	CodeDocument codeDocument;
	XmlTokeniser xmlTokeniser;
    CodeEditorComponent* xmlPreview;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrPanelUtilities);
};
