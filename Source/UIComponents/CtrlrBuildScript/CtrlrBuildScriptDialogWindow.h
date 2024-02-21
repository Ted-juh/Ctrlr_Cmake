#pragma once
#include "JuceHeader.h"
#include "CtrlrManager/CtrlrManager.h"

class CtrlrPanel;

class CtrlrBuildScriptDialogWindow : public Component, public Button::Listener
{
    public:
        CtrlrBuildScriptDialogWindow();

        ~CtrlrBuildScriptDialogWindow();

        void paint (Graphics& g);

        void resized();

        void buttonClicked(Button* button);

        void setDialogWindow(DialogWindow* _window) 
            {   
                window = _window; 
            };

        void generateAndExecuteBuildScript();




    private:

            DialogWindow *window;
            ToggleButton debugButton;
            ToggleButton releaseButton;
            ToggleButton VST2Button;
            ToggleButton VST3Button;
            ToggleButton cleanBuildButton;
            ToggleButton buildFolderButton;
            ToggleButton vstFolderButton;
            ToggleButton dawButton;
            TextButton cancelButton;
            TextButton okButton;

JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CtrlrBuildScriptDialogWindow)
};