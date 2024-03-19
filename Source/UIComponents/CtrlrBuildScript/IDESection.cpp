#include "stdafx.h"
#include "IDESection.h"

IDESection::IDESection()
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

        setSize(240, 125);
    }

    IDESection::~IDESection(){}

    void IDESection::paint(Graphics& g) 
    {
        const int buttonHeight = getHeight() / 5;

        // Space for Title Folder Options
        g.setColour(Colours::darkgrey);
        g.fillRect(                             0,          0,      getWidth(),     buttonHeight);
        //Title Folder Options 
        g.setColour(Colours::white);
        g.setFont(Font(14.0f, Font::bold));
        g.drawText("Choose IDE and set folder", 5,          0,      getWidth(),     buttonHeight, Justification::left, true);
        // Space for Folder Options Buttons
        g.setColour(Colours::whitesmoke);
        g.fillRect(                             0, buttonHeight,    getWidth(),     getHeight());
    }

    void IDESection::paintOverChildren(Graphics& g)
    {
        const int amountBut = 4;
        const int buttonSpace = getWidth() / amountBut;
        const int buttonHeight = getHeight() / 5;

		g.setColour(Colours::darkgrey);
        g.drawLine(0, 0, 0, getHeight(), 1.0);
        g.drawLine(getWidth(), 0, getWidth(), getHeight(), 1.0);
        g.drawLine(buttonSpace, 0, buttonSpace, getHeight(), 1.0);

        g.drawLine(0, buttonHeight * 2, getWidth(), buttonHeight * 2, 1.0);
        g.drawLine(0, buttonHeight * 3, getWidth(), buttonHeight * 3, 1.0);
        g.drawLine(0, buttonHeight * 4, getWidth(), buttonHeight * 4, 1.0);
        g.drawLine(0, buttonHeight * 5, getWidth(), buttonHeight * 5, 1.0);
	}

    void IDESection::resized()
    {
        const int amountBut = 4;
        const int buttonSpace = getWidth() / amountBut;
        const int buttonHeight = getHeight() / 5;

        //Folder Buttons                        X				   Y                   W                   H
        lIDE->setBounds(                        0,                  buttonHeight,       buttonSpace,        buttonHeight);
        cIDE->setBounds(                        0 + buttonSpace,    buttonHeight,       buttonSpace * 3,    buttonHeight);
        bBuildFolder->setBounds(                0,                  buttonHeight * 2,   buttonSpace,        buttonHeight);
        lBuildFolder->setBounds(                0 + buttonSpace,    buttonHeight * 2,   buttonSpace * 3,    buttonHeight);
        bVSTFolder->setBounds(                  0,                  buttonHeight * 3,   buttonSpace,        buttonHeight);
        lVSTFolder->setBounds(                  0 + buttonSpace,    buttonHeight * 3,   buttonSpace * 3,    buttonHeight);
        bDAWFolder->setBounds(                  0,                  buttonHeight * 4,   buttonSpace,        buttonHeight);
        lDAWFolder->setBounds(                  0 + buttonSpace,    buttonHeight * 4,   buttonSpace * 3,    buttonHeight);
    }

    void IDESection::buttonClicked(Button* button)
    {
        if (button = bBuildFolder.get())
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

