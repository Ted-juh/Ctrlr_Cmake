#pragma once
#include "stdafx.h"

class CtrlrBuildScriptOptionsSection : public Component, public Button::Listener
{
public:
    CtrlrBuildScriptOptionsSection();
	~CtrlrBuildScriptOptionsSection();

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

    TextButton* getcCMakeButton()        const { return cCMakeButton.get(); }
    TextButton* getBuildButton()         const { return buildButton.get(); }
    TextButton* getReleaseButton()       const { return releaseButton.get(); }
    TextButton* getCleanBuildButton()    const { return cleanBuildButton.get(); }
    TextButton* getBuildFolderButton()   const { return buildFolderButton.get(); }
    TextButton* getVSTFolderButton()     const { return vstFolderButton.get(); }
    TextButton* getDAWButton()           const { return dawButton.get(); }
    TextButton* getVST3Button()          const { return VST3Button.get(); }

private:

    std::unique_ptr<TextButton> cCMakeButton;
    std::unique_ptr<TextButton> releaseButton;
    std::unique_ptr<TextButton> buildButton;
    std::unique_ptr<TextButton> VST3Button;
    std::unique_ptr<TextButton> cleanBuildButton;
    std::unique_ptr<TextButton> buildFolderButton;
    std::unique_ptr<TextButton> vstFolderButton;
    std::unique_ptr<TextButton> dawButton;
};

