#include "stdafx.h"
#include "CtrlrBuildScriptIDESection.h"

CtrlrBuildScriptIDESection::CtrlrBuildScriptIDESection(CtrlrBuildScriptOutputSection *outputSection) : IDEIndex(0), outputSection(outputSection)
    {
        lIDE = std::make_unique<Label>("");
        addAndMakeVisible(*lIDE);
        lIDE->setJustificationType(Justification::centred);
        lIDE->setText("Choose IDE", dontSendNotification);

        cIDE = std::make_unique<ComboBox>("");
        addAndMakeVisible(*cIDE);
        cIDE->addItem("Visual Studio 2022", 1);
        cIDE->addItem("Visual Studio 2019", 2);
        cIDE->addItem("Visual Studio 2017", 3);
        cIDE->addItem("Xcode", 4);

        bBuildFolder = std::make_unique<TextButton>("");
        addAndMakeVisible(*bBuildFolder);
        bBuildFolder->setButtonText("Project Folder");
        bBuildFolder->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
        bBuildFolder->addListener(this);

		lBuildFolder = std::make_unique<Label>("");
        addAndMakeVisible(*lBuildFolder);
        lBuildFolder->setText("No folder selected..", dontSendNotification);

        bVSTFolder = std::make_unique<TextButton>("");
        addAndMakeVisible(*bVSTFolder);
        bVSTFolder->setButtonText("VST Folder");
        bVSTFolder->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
        bVSTFolder->addListener(this);

        lVSTFolder = std::make_unique<Label>("");
        addAndMakeVisible(*lVSTFolder);
        lVSTFolder->setText("No folder selected..", dontSendNotification);

        bDAWFolder = std::make_unique<TextButton>("");
        addAndMakeVisible(*bDAWFolder);
        bDAWFolder->setButtonText("DAW Folder");
        bDAWFolder->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
        bDAWFolder->addListener(this);

        lDAWFolder = std::make_unique<Label>("");
        addAndMakeVisible(*lDAWFolder);
        lDAWFolder->setText("No folder selected..", dontSendNotification);
    }

CtrlrBuildScriptIDESection::~CtrlrBuildScriptIDESection(){}

void CtrlrBuildScriptIDESection::paint(Graphics& g)
    {
        const int buttonHeight = getHeight() / 5;
        int w = getWidth();
        int y = getHeight();
        int qy = static_cast<int>(y / 25);
        int qx = w - static_cast<int>(qy * 5);

        // Space for Title Folder Options
        g.setColour(Colours::darkgrey);
        g.fillRect(                             0,          0,              getWidth(),     buttonHeight);
        //Title Folder Options 
        g.setColour(Colours::white);
        g.setFont(Font(14.0f, Font::bold));
        g.drawText("Choose IDE and set folder", 5,          0,              getWidth(),     buttonHeight, Justification::left, true);
        // Space for Folder Options Buttons
        g.setColour(Colours::whitesmoke);
        g.fillRect(                             0,          buttonHeight,    getWidth(),     getHeight());
        // Space for Question Mark
        g.setColour(Colours::darkgrey);
        g.fillRect(                             qx,         0 + qy,               buttonHeight - qy,     buttonHeight -  2 * qy);
        g.setColour(Colours::whitesmoke);
        g.drawRect(                             qx,         0 + qy,               buttonHeight - qy,     buttonHeight -  2 * qy,    1);
        g.setFont(Font(17.0f, Font::bold));
        g.drawText("?",                         qx,         0 + qy,               buttonHeight - qy,     buttonHeight -  2 * qy, Justification::centred, true);

        questionMarkArea = juce::Rectangle<int>(qx, 0 + qy, buttonHeight - qy, buttonHeight - 2 * qy);
    }

    void CtrlrBuildScriptIDESection::paintOverChildren(Graphics& g)
    {
        const int amountBut = 4;
        const int buttonSpace = getWidth() / amountBut;
        const int buttonHeight = getHeight() / 5;

		g.setColour(Colours::darkgrey);
        g.drawLine(0.0f, 0.0f, 0.0f, static_cast<float>(getHeight()), 1.0f);
        g.drawLine(static_cast<float>(getWidth()), 0.0f, static_cast<float>(getWidth()),static_cast<float>(getHeight()), 1.0f);
        g.drawLine(static_cast<float>(buttonSpace), 0.0f, static_cast<float>(buttonSpace),static_cast<float>(getHeight()), 1.0f);

        g.drawLine(0.0f, static_cast<float>(buttonHeight * 2), static_cast<float>(getWidth()), static_cast<float>(buttonHeight * 2), 1.0f);
        g.drawLine(0.0f, static_cast<float>(buttonHeight * 3), static_cast<float>(getWidth()), static_cast<float>(buttonHeight * 3), 1.0f);
        g.drawLine(0.0f, static_cast<float>(buttonHeight * 4), static_cast<float>(getWidth()), static_cast<float>(buttonHeight * 4), 1.0f);
        g.drawLine(0.0f, static_cast<float>(buttonHeight * 5), static_cast<float>(getWidth()), static_cast<float>(buttonHeight * 5), 1.0f);
	}

    void CtrlrBuildScriptIDESection::resized()
    {
        const int amountBut = 4;
        const int buttonSpace = getWidth() / amountBut;
        const int buttonHeight = getHeight() / 5;

        //Folder Buttons                        X				   Y                   W                   H
        lIDE->setBounds(                        0,                  buttonHeight,       buttonSpace,        buttonHeight);
        cIDE->setBounds(                        0 + buttonSpace,    buttonHeight,       buttonSpace * 3 + 2,    buttonHeight);
        bBuildFolder->setBounds(                0,                  buttonHeight * 2,   buttonSpace,        buttonHeight);
        lBuildFolder->setBounds(                0 + buttonSpace,    buttonHeight * 2,   buttonSpace * 3,    buttonHeight);
        bVSTFolder->setBounds(                  0,                  buttonHeight * 3,   buttonSpace,        buttonHeight);
        lVSTFolder->setBounds(                  0 + buttonSpace,    buttonHeight * 3,   buttonSpace * 3,    buttonHeight);
        bDAWFolder->setBounds(                  0,                  buttonHeight * 4,   buttonSpace,        buttonHeight);
        lDAWFolder->setBounds(                  0 + buttonSpace,    buttonHeight * 4,   buttonSpace * 3,    buttonHeight);
    }

    void CtrlrBuildScriptIDESection::buttonClicked(Button* button)
    {
        if (button == bBuildFolder.get())
        {
            // Create a FileChooser object
            FileChooser bBuildchooser("Select a folder", File::getSpecialLocation(File::userDesktopDirectory));

            if (bBuildchooser.browseForDirectory())
            {
                File folder(bBuildchooser.getResult());
                lBuildFolder->setText(folder.getFullPathName(), dontSendNotification);
            }
        }

        if (button == bVSTFolder.get())
        {
            // Create a FileChooser object
            FileChooser bVSTchooser("Select a folder", File::getSpecialLocation(File::userDesktopDirectory));

            if (bVSTchooser.browseForDirectory())
            {
                File folder(bVSTchooser.getResult());
                lVSTFolder->setText(folder.getFullPathName(), dontSendNotification);
            }
        }

        if (button == bDAWFolder.get())
        {
			// Create a FileChooser object
			FileChooser bDAWchooser("Select a folder", File::getSpecialLocation(File::userDesktopDirectory));

            if (bDAWchooser.browseForDirectory())
            {
				File folder(bDAWchooser.getResult());
				lDAWFolder->setText(folder.getFullPathName(), dontSendNotification);
			}
		}
    }

    void CtrlrBuildScriptIDESection::mouseDown(const juce::MouseEvent& event)
    {
        if (questionMarkArea.contains(event.getPosition()))
        {
            if (outputSection != nullptr)
            {
                outputSection->getOutputView().clear();
                outputSection->insertTextAtCaret("\n");
                outputSection->setFont(Font(15.0f, Font::bold));
                outputSection->insertTextAtCaret("Choose IDE: \n");
                outputSection->setFont(Font(14.0f, Font::plain));
                outputSection->insertTextAtCaret(
                                        "Choose the IDE you want to use for building the project.\n"
                                        "The IDE needs to be installed on your system.\n\n");
                outputSection->setFont(Font(15.0f, Font::bold));
                outputSection->insertTextAtCaret("Project Folder: \n");
                outputSection->setFont(Font(14.0f, Font::plain));
                outputSection->insertTextAtCaret( 
                                        "Choose the folder where the project will be created.\n"
                                        "This needs to be the Source Folder, not the CMake build folder.\n\n");
                outputSection->setFont(Font(15.0f, Font::bold));
                outputSection->insertTextAtCaret("VST Folder: \n");
                outputSection->setFont(Font(14.0f, Font::plain));
                outputSection->insertTextAtCaret(
                                        "Choose the folder where the VST plugin will be created. (Experimental)\n\n");
                outputSection->setFont(Font(15.0f, Font::bold));
                outputSection->insertTextAtCaret("DAW Folder: \n");
                outputSection->setFont(Font(14.0f, Font::plain));
                outputSection->insertTextAtCaret(
                                        "Choose the execute file for your DAW.\n\n");
            }
        }
    }