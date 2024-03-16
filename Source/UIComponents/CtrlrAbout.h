
#pragma once
#include "CtrlrManager/CtrlrManager.h"

class CtrlrAbout  : public Component,
					public Button::Listener
{
public:
    CtrlrAbout (CtrlrManager &_owner);
    ~CtrlrAbout();

	void addVersionInfo (const String &componentName, const String &componentVersion);
	void updateVersionLabel();
    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);

private:

	CtrlrManager &owner;
	StringPairArray versionInformationArray;

    ScopedPointer<Label> ctrlrName;
    ScopedPointer<DrawableButton> ctrlrLogo;
    ScopedPointer<TextEditor> versionInfoLabel;
    ScopedPointer<Label> label;
    ScopedPointer<Label> label2;
	ScopedPointer<Label> labelDonate;
	ScopedPointer<Label> labelAuthorEmail;
	ScopedPointer<Label> label3;
    ScopedPointer<Label> label4;
    ScopedPointer<HyperlinkButton> instanceUrl;
	ScopedPointer<HyperlinkButton> instanceAuthorDonateUrl;
	ScopedPointer<HyperlinkButton> instanceAuthorEmail;
	ScopedPointer<Label> instanceVersion;
    ScopedPointer<Label> instanceAuthor;
    ScopedPointer<Label> instanceName;
    ScopedPointer<TextEditor> instanceDescription;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrAbout)
};
