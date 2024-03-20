#include "stdafx.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrBuildScriptDialogWindow.h"

CtrlrBuildScriptDialogWindow::CtrlrBuildScriptDialogWindow(CtrlrManager &_owner) 
    : owner(_owner)
{
    ideSection = std::make_unique<IDESection>();
    addAndMakeVisible (*ideSection);

    optionsSection = std::make_unique<OptionsSection>();
    addAndMakeVisible (*optionsSection);

    outputSection = std::make_unique<OutputSection>();
    addAndMakeVisible (*outputSection);

    saveFileButton = std::make_unique<TextButton>("");
    addAndMakeVisible (*saveFileButton);
    saveFileButton->setButtonText("Save options");
    saveFileButton->setVisible(true);
    saveFileButton->addListener(this);

    loadFileButton = std::make_unique<TextButton>("");
    addAndMakeVisible (*loadFileButton);
    loadFileButton->setButtonText("Load options");
    loadFileButton->setVisible(true);
    loadFileButton->addListener(this);

    okButton = std::make_unique<TextButton>("");
    addAndMakeVisible(*okButton);
    okButton->setButtonText("OK");
    okButton->setVisible(false);
    okButton->addListener(this);

    setSize(500, 240);
}

CtrlrBuildScriptDialogWindow::~CtrlrBuildScriptDialogWindow(){}

void CtrlrBuildScriptDialogWindow::paint(Graphics& g)
{
    g.fillAll(Colours::lightgrey);
}

void CtrlrBuildScriptDialogWindow::paintOverChildren(Graphics& g)
{
    const int startRect = getWidth() * 0.05;
    const int rectWidth = getWidth() - (startRect * 2);
    const int buttonHeight = getHeight() * 0.05;
    const int rectLineHeight = buttonHeight / 2;

    const int amountBut = 4;
    const int buttonSpace = rectWidth / amountBut;
    
    g.setColour(Colours::darkgrey);
    g.drawRect(startRect,                       rectLineHeight * 23,    buttonSpace,    buttonHeight, 1.0);
    g.drawRect(startRect + buttonSpace,         rectLineHeight * 23,    buttonSpace,    buttonHeight, 1.0);

    if (okButton->isVisible())
    {
    g.setColour(Colours::darkgrey);
    g.drawRect(startRect + (buttonSpace * 3),   rectLineHeight * 23,    buttonSpace,    buttonHeight, 1.0);
	}
}

void CtrlrBuildScriptDialogWindow::resized()
{

    const int startRect         = getWidth() * 0.05;
    const int rectWidth         = getWidth() - (startRect * 2);
    const int buttonHeight      = getHeight() * 0.05;
    const int rectLineHeight    = buttonHeight / 2;

    const int amountBut         = 4;
    const int buttonSpace       = rectWidth / amountBut;

    ideSection          ->setBounds(startRect,                          rectLineHeight * 1,        rectWidth,          buttonHeight * 5);
    optionsSection      ->setBounds(startRect,                          rectLineHeight * 12,       rectWidth,          buttonHeight * 5);

    saveFileButton      ->setBounds(startRect,                          rectLineHeight * 23,       buttonSpace,        buttonHeight);
    loadFileButton      ->setBounds(startRect + buttonSpace,            rectLineHeight * 23,       buttonSpace,        buttonHeight);

    okButton            ->setBounds(startRect + (buttonSpace * 3),      rectLineHeight * 23,       buttonSpace,        buttonHeight);
    outputSection       ->setBounds(startRect,                          rectLineHeight * 26,       rectWidth,          buttonHeight * 7);
}

void CtrlrBuildScriptDialogWindow::setButtonStateAndColour(TextButton* button, bool state)
{
    button->setToggleState(state, dontSendNotification);    // ON                   OFF
    button->setColour(TextButton::buttonColourId,   state ? Colours::darkgrey : Colours::whitesmoke);       
    button->setColour(TextButton::buttonOnColourId, state ? Colours::darkgrey : Colours::whitesmoke);       
    button->setColour(TextButton::textColourOffId,  state ? Colours::black : Colours::black);               
    button->setColour(TextButton::textColourOnId,   state ? Colours::white : Colours::white);			    
}

void CtrlrBuildScriptDialogWindow::buttonClicked(Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == saveFileButton.get())                                             // Do saveOptionsToFile method when the saveFileButton is clicked
    {
        saveOptionsToFile();
    }

    if (buttonThatWasClicked == loadFileButton.get())											    // Do loadOptionsFromFile method when the loadFileButton is clicked
    {
        loadOptionsFromFile();
    }

    if (buttonThatWasClicked == okButton.get())                                                   // Do the following when the okButton is clicked
        {   
            // Check if an IDE is selected
            if (ideSection->getIDEIndex() == -1)
            {
                outputSection->getOutputView().insertTextAtCaret("Please select an IDE.\n");
                return;
            }

            if (ideSection->getBuildFolderPath().isEmpty())
			{
				outputSection->getOutputView().insertTextAtCaret("Please select a build folder.\n");
				return;
			}

            if (optionsSection->isCCMakeButtonToggled()) { checkCMake(); }                  // Check CMake button

            if (optionsSection->isBuildButtonToggled())                                     // Build button 
            {
                generateBuildFiles();													    // Generate build files

                if (optionsSection->isBuildFolderButtonToggled())                           // Open build folder button
                {
                    openBuildFolder();
                }
            }

            if (optionsSection->isReleaseButtonToggled())                                   // Release button
            {
                if (optionsSection->isCleanBuildButtonToggled())                            // Clean build button
                {
                    generateBuildFiles();                                                   // Generate build files
                }

                buildFiles();

                if (optionsSection->isBuildFolderButtonToggled())                           // Open build folder button
                {
                    openBuildFolder();
                }
            }
        }
 }

void CtrlrBuildScriptDialogWindow::setOkButtonVisible(const bool isVisible)
{
	okButton->setVisible(isVisible);
}

void CtrlrBuildScriptDialogWindow::labelTextChanged(Label* labelThatHasChanged){}

void CtrlrBuildScriptDialogWindow::buttonStateChanged(Button* button){}

void CtrlrBuildScriptDialogWindow::checkCMake()                                                                     // Check if CMake is installed and added to the PATH
{
    // Add CMake to the PATH
    String cmakePath = "C:\\Program Files\\CMake\\bin";                                                             // Actual path to CMake bin directory
    String currentPath = getenv("PATH");                                                                            // Get the current PATH
        
    if (currentPath.indexOf(cmakePath) == -1)                                                                       // If CMake is not in the PATH
    {
        outputSection->getOutputView().insertTextAtCaret("Check if PATH is set for CMake.\n\n");                    // Opening message
        outputSection->getOutputView().insertTextAtCaret("Adding CMake as a variable to your System's PATH environment.\n");
        _putenv_s("PATH", (currentPath + ";" + cmakePath).toRawUTF8());						                        // Add CMake to the PATH
        outputSection->getOutputView().insertTextAtCaret("CMake check passed.\n");
    }
    else
    {
        outputSection->getOutputView().insertTextAtCaret("Check if PATH is set for CMake.\n\n");                    // Opening message
        outputSection->getOutputView().insertTextAtCaret("CMake check passed\n");       							// CMake is in the PATH
    }

     ChildProcess cmakeCheck;
     if (cmakeCheck.start("cmake --version"))																        // Double check, get the version of CMake
     {
        String output = cmakeCheck.readAllProcessOutput();                                                          // Read the output
        outputSection->getOutputView().insertTextAtCaret("" + output + "\n");							            // Output the version
     }
     else
     {
         outputSection->getOutputView().insertTextAtCaret("CMake check failed. Please ensure CMake is correctly installed and added to the PATH.\n");
        return;
     }
}

void CtrlrBuildScriptDialogWindow::generateBuildFiles()										    // Re-Generate the build folder + build/solution files   
{
    std::map<int, String> generatorMap =
    {
        {0, "Visual Studio 17 2022" },
        {1, "Visual Studio 16 2019" },
		{2, "Visual Studio 15 2017" },
 		{3, "Xcode" },
    };

    String generator = generatorMap[ideSection->getIDEIndex()];
    outputSection->getOutputView().insertTextAtCaret("The generator is " + generator + "\n");


    String projectFolderPath = ideSection->getBuildFolderPath();
	String buildFolderPath = projectFolderPath + "\\build";

    String command = "cmd /C ";                                                                 // command to run in the command prompt
    String argument1 = "\"rmdir /S /Q \"" + buildFolderPath + "\" && ";                         // delete the build folder
	String argument2 = "mkdir \"" + buildFolderPath + "\" && ";                                 // create a new build folder
	String argument3 = "cd \"" + buildFolderPath + "\" && ";                                    // change directory to the build folder
    //String argument4 = "cmake -S .. -B . -G \"" + generator + "\"";                             // generate the build files

    String argument4;
    if (generator == "Xcode")
    {
        String sourcePath = projectFolderPath + "\\..";
        argument4 = "cmake -S \"" + sourcePath + "\" -B . -G \"" + generator + "\"";
    }
    	else
	{
		argument4 = "cmake -S .. -B . -G \"" + generator + "\"";
	}

	ChildProcess cp;
	bool success = cp.start(command + argument1 + argument2 + argument3 + argument4);

    if (success)
    {
        outputSection->getOutputView().insertTextAtCaret("The build folder is going to be deleted and the build files will be generated into a new build folder.\n");
        String output = cp.readAllProcessOutput();
        outputSection->getOutputView().insertTextAtCaret("" + output + "\n");
    }
    else
    {
			outputSection->getOutputView().insertTextAtCaret("Build process failed. Please check your setup and try again.\n");
	}
}

void CtrlrBuildScriptDialogWindow::openBuildFolder()
{
    String projectFolderPath = ideSection->getBuildFolderPath();
    String buildFolderPath = projectFolderPath + "\\build";

    outputSection->getOutputView().insertTextAtCaret("The build folder is going to be opened.\n");
    String command = "cmd /C ";
    String openFolderCommand = "explorer " + buildFolderPath;
    system(openFolderCommand.toStdString().c_str());
}

void CtrlrBuildScriptDialogWindow::buildFiles()
{
    String projectFolderPath = ideSection->getBuildFolderPath();
    String buildFolderPath = projectFolderPath + "\\build";

    String command = "cmd /C ";
    String argument1 = "cd \"" + buildFolderPath + "\" && ";
    String argument2 = "cmake --build . --config Release";

    ChildProcess cp;
    bool success = cp.start(command + argument1 + argument2);

    if (success)
	{
		outputSection->getOutputView().insertTextAtCaret("The build process is going to start.\n");
		String output = cp.readAllProcessOutput();
		outputSection->getOutputView().insertTextAtCaret("" + output + "\n");
	}
	else
	{
		outputSection->getOutputView().insertTextAtCaret("Build process failed. Please check your setup and try again.\n");
	} 
}

void CtrlrBuildScriptDialogWindow::saveOptionsToFile()
{
    FileChooser chooser("Save options to file", File::getSpecialLocation(File::userDesktopDirectory), "*.bso", true);

    if (chooser.browseForFileToSave(true))
    {
        File file = chooser.getResult();

        if (file.exists())
		{
			file.deleteFile();
		}

        FileOutputStream outputStream(file, false);

        if (outputStream.openedOk())
        {
            outputStream << "This file's purpose is to store the options for the build script dialog window in Ctrlr.\n\n";
            outputStream << "IDE="                  << ideSection       ->getIDEIndex()                         << newLine;
            outputStream << "ProjectFolder=\""      << ideSection       ->getBuildFolderPath()      <<"\""      << newLine;
            outputStream << "VSTFolder=\""          << ideSection       ->getVSTFolderPath()        <<"\""      << newLine;
            outputStream << "DAWFolder=\""          << ideSection       ->getDAWFolderPath()        <<"\""      << newLine;
            outputStream << "CheckCMake="           << optionsSection   ->isCCMakeButtonToggled()               << newLine;
            outputStream << "GenerateBuildFiles="   << optionsSection   ->isBuildButtonToggled()                << newLine;
            outputStream << "Release="              << optionsSection   ->isReleaseButtonToggled()              << newLine;
            outputStream << "CleanBuild="           << optionsSection   ->isCleanBuildButtonToggled()           << newLine;
            outputStream << "BuildFolder="          << optionsSection   ->isBuildFolderButtonToggled()          << newLine;
            outputStream << "openVSTFolder="        << optionsSection   ->isVSTFolderButtonToggled()            << newLine;
            outputStream << "openDAWFolder="        << optionsSection   ->isDAWButtonToggled()                  << newLine;

            outputStream.flush();

            outputSection->getOutputView().insertTextAtCaret("Options file saved.\n");
        }
        else
        {
            outputSection->getOutputView().insertTextAtCaret("Failed to save options to file.\n");
        }
    }
}

void CtrlrBuildScriptDialogWindow::loadOptionsFromFile()
{
	FileChooser chooser("Load options from file", File::getSpecialLocation(File::userDesktopDirectory), "*.bso", true);

	if (chooser.browseForFileToOpen())
	{
		File file = chooser.getResult();

		FileInputStream inputStream(file);

		if (inputStream.openedOk())
		{
			StringArray lines;
			lines.addTokens(inputStream.readEntireStreamAsString(), true);

			for (int i = 0; i < lines.size(); i++)
			{
				StringArray tokens;
				tokens.addTokens(lines[i], "=", "");

                if (tokens[0] == "IDE")                
                { 
                    int index = tokens[1].getIntValue();
                    ideSection->setIDEIndex(tokens[1].getIntValue()); 
                }

                if (tokens[0] == "ProjectFolder")      
                { 
                    String unquotedPath = tokens[1].unquoted();
                    ideSection->setBuildFolderPath(unquotedPath);
                    ideSection->getBuildFolderLabel()->setText(unquotedPath, dontSendNotification);
                }

                if (tokens[0] == "VSTFolder")          
				{ 
                    String unqoutedPath = tokens[1].unquoted();
					ideSection->setVSTFolderPath(unqoutedPath);
					ideSection->getVSTFolderLabel()->setText(unqoutedPath, dontSendNotification);
				}

                if (tokens [0] == "DAWFolder")
				{
                    String unqoutedPath = tokens[1].unquoted();
					ideSection->setDAWFolderPath(unqoutedPath);
					ideSection->getDAWFolderLabel()->setText(unqoutedPath, dontSendNotification);
				}

                if (tokens[0] == "CheckCMake")               
				{ 
				    bool state = tokens[1].getIntValue() == 1;
					optionsSection->setCCMakeButtonToggled(state);
					optionsSection->setButtonStateAndColour(optionsSection->getcCMakeButton(), state);
                    optionsSection->getcCMakeButton()->repaint();
				}

                if (tokens[0] == "GenerateBuildFiles")
                {
                	bool state = tokens[1].getIntValue() == 1;
					optionsSection->setBuildButtonToggled(state);
					optionsSection->setButtonStateAndColour(optionsSection->getBuildButton(), state);

                }

                if (tokens[0] == "Release")
                {
                    bool state = tokens[1].getIntValue() == 1;
                    optionsSection->setReleaseButtonToggled(state);
                    optionsSection->setButtonStateAndColour(optionsSection->getReleaseButton(), state);
                }

                if (tokens[0] == "CleanBuild")
				{
					bool state = tokens[1].getIntValue() == 1;
					optionsSection->setCleanBuildButtonToggled(state);
					optionsSection->setButtonStateAndColour(optionsSection->getCleanBuildButton(), state);
				}

                if (tokens[0] == "BuildFolder")
                {
                    bool state = tokens[1].getIntValue() == 1;
                    optionsSection->setBuildFolderButtonToggled(state);
                    optionsSection->setButtonStateAndColour(optionsSection->getBuildFolderButton(), state);
                    optionsSection->getBuildFolderButton()->setVisible(true);
                    setOkButtonVisible(true);
                }

                if (tokens[0] == "openVSTFolder")
				{
					bool state = tokens[1].getIntValue() == 1;
					optionsSection->setVSTFolderButtonToggled(state);
					optionsSection->setButtonStateAndColour(optionsSection->getVSTFolderButton(), state);
				}

                if (tokens[0] == "openDAWFolder")
				{
					bool state = tokens[1].getIntValue() == 1;
					optionsSection->setDAWButtonToggled(state);
					optionsSection->setButtonStateAndColour(optionsSection->getDAWButton(), state);
				}
			}

            outputSection->getOutputView().insertTextAtCaret("Options file loaded.\n");
		}
		else
		{
			outputSection->getOutputView().insertTextAtCaret("Failed to load options from file.\n");
		}
	}
}  