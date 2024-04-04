#pragma once
#include "stdafx.h"
#include "CtrlrBuildScriptOutputSection.h"

class LimitedLengthLabel : public Label
{
public:
    LimitedLengthLabel(const String& componentName, const String& labelText)
        : Label(componentName, labelText)
    {
    }

    void editorShown(TextEditor* limitedLengthEditor)
    {
        Label::editorShown(limitedLengthEditor);
        limitedLengthEditor->setInputFilter(new TextEditor::LengthAndCharacterRestriction(4, ""), true);
		previousText = getText();
    }

    void textEditorReturnKeyPressed(TextEditor& limitedLengthEditor) override
    {
        String text = limitedLengthEditor.getText();
		 
        if (text.isEmpty() || text == "...")
        {
            setText("...", dontSendNotification);
        }

		else if (!text.containsAnyOf("ABCDEFGHIJKLMNOPQRSTUVWXYZ"))
        {
            AlertWindow::showMessageBox(AlertWindow::WarningIcon, "Invalid Input", "The first character needs to be an uppercase letter.\n ");
        }
		else
		{
			Label::textEditorReturnKeyPressed(limitedLengthEditor);
		}
    }

private:
	String previousText;
};

class CtrlrBuildScriptVST3Section : public Component, public Button::Listener
{

public:
	CtrlrBuildScriptVST3Section(CtrlrBuildScriptOutputSection *outputSection);
	~CtrlrBuildScriptVST3Section();

	void paint(Graphics& g);
	void paintOverChildren(Graphics& g);

	void resized();

	void buttonClicked(Button* button);
	void mouseDown(const MouseEvent& event);

	String getProductName() { return tProductName->getText(); }
	String getVersion() { return tVersion->getText(); }
	String getPluginName() { return tPluginName->getText(); }
	String getDescription() { return tDescription->getText(); }
	String getPluginMC() { return tPluginMC->getText(); }
	String getPluginCode() { return tPluginCode->getText(); }
	String getBundleID() { return tBundleID->getText(); }
	String getCompanyName() { return tCompanyName->getText(); }
	String getNeedsMidiInput() { return tNeedsMidiInput->getText(); }
	int getVSTMidiInputs() { return tVSTMidiInputs->getSelectedItemIndex(); }
	String getNeedsMidiOutput() { return tNeedsMidiOutput->getText(); }
	int getVSTMidiOutputs() { return tVSTMidiOutputs->getSelectedItemIndex(); }

	void setProductName(String text) { tProductName->setText(text, dontSendNotification); }
	void setVersion(String text) { tVersion->setText(text, dontSendNotification); }
	void setPluginName(String text) { tPluginName->setText(text, dontSendNotification); }
	void setDescription(String text) { tDescription->setText(text, dontSendNotification); }
	void setPluginMC(String text) { tPluginMC->setText(text, dontSendNotification); }
	void setPluginCode(String text) { tPluginCode->setText(text, dontSendNotification); }
	void setBundleID(String text) { tBundleID->setText(text, dontSendNotification); }
	void setCompanyName(String text) { tCompanyName->setText(text, dontSendNotification); }
	void setNeedsMidiInput(String text) { tNeedsMidiInput->setText(text, dontSendNotification); }
	void setVSTMidiInputs(int index) { tVSTMidiInputs->setSelectedItemIndex(index); }
	void setNeedsMidiOutput(String text) { tNeedsMidiOutput->setText(text, dontSendNotification); }
	void setVSTMidiOutputs(int index) { tVSTMidiOutputs->setSelectedItemIndex(index); }

	Label* getProductNameLabel() { return lProductName.get(); }
	Label* getVersionLabel() { return lVersion.get(); }
	Label* getPluginNameLabel() { return lPluginName.get(); }
	Label* getDescriptionLabel() { return lDescription.get(); }
	Label* getPluginMCLabel() { return lPluginMC.get(); }
	Label* getPluginCodeLabel() { return lPluginCode.get(); }
	Label* getBundleIDLabel() { return lBundleID.get(); }
	Label* getCompanyNameLabel() { return lCompanyName.get(); }
	ComboBox* getNeedsMidiInputComboBox() { return tNeedsMidiInput.get(); }
	ComboBox* getNeedsMidiOutputComboBox() { return tNeedsMidiOutput.get(); }
	ComboBox* getVSTMidiInputsComboBox() { return tVSTMidiInputs.get(); }
	ComboBox* getVSTMidiOutputsComboBox() { return tVSTMidiOutputs.get(); }


private:
	std::unique_ptr<Label> lProductName;
	std::unique_ptr<Label> tProductName;

	std::unique_ptr<Label> lVersion;
	std::unique_ptr<Label> tVersion;

	std::unique_ptr<Label> lPluginName;
	std::unique_ptr<Label> tPluginName;

	std::unique_ptr<Label> lDescription;
	std::unique_ptr<Label> tDescription;

	std::unique_ptr<Label> lPluginMC;
	std::unique_ptr<LimitedLengthLabel> tPluginMC;

	std::unique_ptr<Label> lPluginCode;
	std::unique_ptr<LimitedLengthLabel> tPluginCode;

	std::unique_ptr<Label> lBundleID;
	std::unique_ptr<Label> tBundleID;

	std::unique_ptr<Label> lCompanyName;
	std::unique_ptr<Label> tCompanyName;
	
	std::unique_ptr<Label> lNeedsMidiInput;
	std::unique_ptr<ComboBox> tNeedsMidiInput;

	std::unique_ptr<Label> lNeedsMidiOutput;
	std::unique_ptr<ComboBox> tNeedsMidiOutput;

	std::unique_ptr<Label> lVSTMidiInputs;
	std::unique_ptr<ComboBox> tVSTMidiInputs;

	std::unique_ptr<Label> lVSTMidiOutputs;
	std::unique_ptr<ComboBox> tVSTMidiOutputs;

	juce::Rectangle<int> questionMarkAreaVST3;
	CtrlrBuildScriptOutputSection* outputSection;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CtrlrBuildScriptVST3Section)

};

