#pragma once

#include "stdafx.h"

class OptionsSection : public Component, public Button::Listener
{
public:
	OptionsSection();
	~OptionsSection();

	void paint(Graphics& g) override;
    void paintOverChildren(Graphics& g) override;
	void resized() override;
    void setButtonStateAndColour(TextButton* button, bool state);
	void buttonClicked(Button* button) override;

    bool isCCMakeButtonToggled()        const { return cCMakeButton     ->getToggleState(); }
    bool isReleaseButtonToggled()       const { return releaseButton    ->getToggleState(); }
    bool isBuildButtonToggled()         const { return buildButton      ->getToggleState(); }
    bool isVST3ButtonToggled()          const { return VST3Button       ->getToggleState(); }
    bool isCleanBuildButtonToggled()    const { return cleanBuildButton ->getToggleState(); }
    bool isBuildFolderButtonToggled()   const { return buildFolderButton->getToggleState(); }
    bool isVSTFolderButtonToggled()     const { return vstFolderButton  ->getToggleState(); }
    bool isDAWButtonToggled()           const { return dawButton        ->getToggleState(); }

    void setCCMakeButtonToggled     (int value) { cCMakeButton      ->setToggleState(value, dontSendNotification); }
    void setBuildButtonToggled      (int value) { buildButton       ->setToggleState(value, dontSendNotification); }
    void setReleaseButtonToggled    (int value) { releaseButton     ->setToggleState(value, dontSendNotification); }
    void setCleanBuildButtonToggled (int value) { cleanBuildButton  ->setToggleState(value, dontSendNotification); }
    void setBuildFolderButtonToggled(int value) { buildFolderButton ->setToggleState(value, dontSendNotification); }
    void setVSTFolderButtonToggled  (int value) { vstFolderButton   ->setToggleState(value, dontSendNotification); }
    void setDAWButtonToggled        (int value) { dawButton         ->setToggleState(value, dontSendNotification); }

    TextButton* getcCMakeButton()        const { return cCMakeButton; }
    TextButton* getBuildButton()         const { return buildButton; }
    TextButton* getReleaseButton()       const { return releaseButton; }
    TextButton* getCleanBuildButton()    const { return cleanBuildButton; }
    TextButton* getBuildFolderButton()   const { return buildFolderButton; }
    TextButton* getVSTFolderButton()     const { return vstFolderButton; }
    TextButton* getDAWButton()           const { return dawButton; }
private:

    ScopedPointer<TextButton> cCMakeButton;
    ScopedPointer<TextButton> releaseButton;
    ScopedPointer<TextButton> buildButton;
    ScopedPointer<TextButton> VST3Button;
    ScopedPointer<TextButton> cleanBuildButton;
    ScopedPointer<TextButton> buildFolderButton;
    ScopedPointer<TextButton> vstFolderButton;
    ScopedPointer<TextButton> dawButton;


};

