#pragma once
#include "JuceHeader.h"

class CtrlrPanel;

class CtrlrBuildScriptDialogWindow : public Component, public Button::Listener
{
    public:
        CtrlrBuildScriptDialogWindow(CtrlrPanel *_panel);

        ~CtrlrBuildScriptDialogWindow();

        void paint (Graphics& g);

        void resized();

            void buttonClicked(Button* button);

            void setDialogWindow(DialogWindow* _window) 
            {   
                window = _window; 
            };

        void generateAndExecuteBuildScript();
void NewFunction();
void buildFunction(juce::File &buildScriptFile);

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

CtrlrPanel *panel;

JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CtrlrBuildScriptDialogWindow)
};