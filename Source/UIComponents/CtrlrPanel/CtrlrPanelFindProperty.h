#pragma once
#include "CtrlrMacros.h"
#include "CtrlrInlineUtilitiesGUI.h"

class CtrlrPanelEditor;
class CtrlrPanelComponentProperties;

class CtrlrPanelFindProperty  : public juce::Component, public juce::TextEditor::Listener
{
public:
    CtrlrPanelFindProperty(CtrlrPanelEditor &_owner, CtrlrPanelComponentProperties *_props);
    ~CtrlrPanelFindProperty() override;
	void textEditorReturnKeyPressed (TextEditor&) override;
	void textEditorEscapeKeyPressed (TextEditor&) override;
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrPanelFindProperty)
    std::unique_ptr<TextEditor> filterInput;
    std::unique_ptr<DrawableButton> filterButton;
	CtrlrPanelEditor &owner;
	CtrlrPanelComponentProperties *props;
};
