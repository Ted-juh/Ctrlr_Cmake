#include "stdafx.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrBuildScriptMain.h"

CtrlrBuildScriptMain::CtrlrBuildScriptMain(CtrlrManager &_owner) 
    : owner(_owner)
{
    saveFileButton = std::make_unique<TextButton>("");
    addAndMakeVisible(*saveFileButton);
    saveFileButton->setButtonText("Save options");
    saveFileButton->setVisible(true);
    saveFileButton->addListener(this);

    loadFileButton = std::make_unique<TextButton>("");
    addAndMakeVisible(*loadFileButton);
    loadFileButton->setButtonText("Load options");
    loadFileButton->setVisible(true);
    loadFileButton->addListener(this);

    okButton = std::make_unique<TextButton>("");
    addAndMakeVisible(*okButton);
    okButton->setButtonText("OK");
    okButton->setVisible(false);
    okButton->addListener(this);

    outputSection = std::make_unique<CtrlrBuildScriptOutputSection>();
    addAndMakeVisible(*outputSection);

    ideSection = std::make_unique<CtrlrBuildScriptIDESection>(outputSection.get());
    addAndMakeVisible (*ideSection);

    optionsSection = std::make_unique<CtrlrBuildScriptOptionsSection>(outputSection.get());
    addAndMakeVisible (*optionsSection);

    vst3Section = std::make_unique<CtrlrBuildScriptVST3Section>(outputSection.get());
    vst3Section->setVisible(true);
    addAndMakeVisible(*vst3Section);    

}

CtrlrBuildScriptMain::~CtrlrBuildScriptMain(){}

void CtrlrBuildScriptMain::paint(Graphics& g)
{
    g.fillAll(Colours::lightgrey);
}

void CtrlrBuildScriptMain::paintOverChildren(Graphics& g)
{
    const int startRect = getWidth() * 0.05;
    const int rectWidth = getWidth() - (startRect * 2);
    const int buttonHeight = getHeight() * 0.032;
    const int rlH = buttonHeight / 2;

    const int amountBut = 4;
    const int buttonSpace = rectWidth / amountBut;

    int componentBottom = 0;

    // The drawRect for saveFileButton and loadFileButton are underneath the VST3Section
    componentBottom = vst3Section->getBottom();
        
    g.setColour(Colours::darkgrey);
    g.drawRect(startRect,                       componentBottom + rlH,    buttonSpace,    buttonHeight, 1.0);
    g.drawRect(startRect + buttonSpace,         componentBottom + rlH,    buttonSpace,    buttonHeight, 1.0);

    if (okButton->isVisible())
    {
    g.setColour(Colours::darkgrey);
    g.drawRect(startRect + (buttonSpace * 3),   componentBottom + rlH,    buttonSpace,    buttonHeight, 1.0);
	}

}

void CtrlrBuildScriptMain::resized()
{

    const int startRect         = getWidth() * 0.05;                // Margin
    const int rectWidth         = getWidth() - (startRect * 2);	    // Width of the section

    const int buttonHeight      = getHeight() * 0.032;			    // Height of the buttons
    const int rlH               = buttonHeight / 2;				    // Height of the lines

    const int amountBut         = 4;								// Amount of buttons
    const int buttonSpace       = rectWidth / amountBut;			// Space for buttons, max 4 buttons in rectWidth

    int componentBottom = 0;

    ideSection->                                setBounds(startRect,                          componentBottom,          rectWidth,          buttonHeight * 5);
    componentBottom = ideSection->getBottom();

    optionsSection->                            setBounds(startRect,                          componentBottom + rlH,    rectWidth,          buttonHeight * 5);
    componentBottom = optionsSection->getBottom();

    vst3Section->                               setBounds(startRect,                          componentBottom + rlH,    rectWidth,          buttonHeight * 7);
    componentBottom = vst3Section->getBottom();

    saveFileButton->                            setBounds(startRect,                          componentBottom + rlH,    buttonSpace,        buttonHeight);
    loadFileButton->                            setBounds(startRect + (buttonSpace),          componentBottom + rlH,    buttonSpace,        buttonHeight);
    okButton->                                  setBounds(startRect + (buttonSpace * 3),      componentBottom + rlH,    buttonSpace,        buttonHeight);
    componentBottom = okButton->getBottom();

    outputSection->                             setBounds(startRect,                          componentBottom + rlH ,   rectWidth,          buttonHeight * 11);
    componentBottom = outputSection->getBottom();

}

void CtrlrBuildScriptMain::setButtonStateAndColour(TextButton* button, bool state)
{
    button->setToggleState(state, dontSendNotification);    // ON                   OFF
    button->setColour(TextButton::buttonColourId,   state ? Colours::darkgrey : Colours::whitesmoke);       
    button->setColour(TextButton::buttonOnColourId, state ? Colours::darkgrey : Colours::whitesmoke);       
    button->setColour(TextButton::textColourOffId,  state ? Colours::black : Colours::black);               
    button->setColour(TextButton::textColourOnId,   state ? Colours::white : Colours::white);			    
}

void CtrlrBuildScriptMain::buttonClicked(Button* buttonThatWasClicked)
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

void CtrlrBuildScriptMain::setOkButtonVisible(const bool isVisible)
{
	okButton->setVisible(isVisible);
}

void CtrlrBuildScriptMain::labelTextChanged(Label* labelThatHasChanged){}

void CtrlrBuildScriptMain::buttonStateChanged(Button* button){}

void CtrlrBuildScriptMain::checkCMake()                                                                             // Check if CMake is installed and added to the PATH
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

void CtrlrBuildScriptMain::generateBuildFiles()										            // Re-Generate the build folder + build/solution files   
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
    //String argument4 = "cmake -S .. -B . -G \"" + generator + "\"";                           // generate the build files

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

void CtrlrBuildScriptMain::openBuildFolder()
{
    String projectFolderPath = ideSection->getBuildFolderPath();
    String buildFolderPath = projectFolderPath + "\\build";

    outputSection->getOutputView().insertTextAtCaret("The build folder is going to be opened.\n");
    String command = "cmd /C ";
    String openFolderCommand = "explorer " + buildFolderPath;
    system(openFolderCommand.toStdString().c_str());
}

void CtrlrBuildScriptMain::buildFiles()
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

void CtrlrBuildScriptMain::saveOptionsToFile()
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
            outputStream << "VST3="                 << optionsSection   ->isVST3ButtonToggled()                 << newLine;           
            outputStream << "CleanBuild="           << optionsSection   ->isCleanBuildButtonToggled()           << newLine;
            outputStream << "BuildFolder="          << optionsSection   ->isBuildFolderButtonToggled()          << newLine;
            outputStream << "openVSTFolder="        << optionsSection   ->isVSTFolderButtonToggled()            << newLine;
            outputStream << "openDAWFolder="        << optionsSection   ->isDAWButtonToggled()                  << newLine;
            outputStream << "productName="          << vst3Section      ->getProductName()                      << newLine;
            outputStream << "version="              << vst3Section      ->getVersion()                          << newLine;
            outputStream << "pluginName="           << vst3Section      ->getPluginName()                       << newLine;
            outputStream << "description="          << vst3Section      ->getDescription()                      << newLine;
            outputStream << "pluginMC="             << vst3Section      ->getPluginMC()                         << newLine;
            outputStream << "pluginCode="           << vst3Section      ->getPluginCode()                       << newLine;
            outputStream << "bundleID="             << vst3Section      ->getBundleID()                         << newLine;
            outputStream << "companyName="          << vst3Section      ->getCompanyName()                      << newLine;
            outputStream << "needsMidiInput="       << vst3Section      ->getNeedsMidiInput()                   << newLine;
            outputStream << "VSTMidiInputs="        << vst3Section      ->getVSTMidiInputs()                    << newLine;
            outputStream << "needsMidiOutput="      << vst3Section      ->getNeedsMidiOutput()                  << newLine;
            outputStream << "VSTMidiOutputs="       << vst3Section      ->getVSTMidiOutputs()                   << newLine;

            outputStream.flush();

            outputSection->getOutputView().insertTextAtCaret("Options file saved.\n");
        }
        else
        {
            outputSection->getOutputView().insertTextAtCaret("Failed to save options to file.\n");
        }
    }
}

void CtrlrBuildScriptMain::loadOptionsFromFile()
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
                    ideSection->setIDEIndex(tokens[1].getIntValue());
                    ideSection->getIDEComboBox()->setSelectedItemIndex(tokens[1].getIntValue());
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

                if (tokens[0] == "VST3")
                {
                    bool state = tokens[1].getIntValue() == 1;
                    optionsSection->setVST3ButtonToggled(state);
                    optionsSection->setButtonStateAndColour(optionsSection->getVST3Button(), state);
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

                if (tokens[0] == "productName")
                {
                    vst3Section->setProductName(tokens[1]);
                    vst3Section->getProductNameLabel()->setText(tokens[1], dontSendNotification);
                }

                if (tokens[0] == "version")
                {
                    vst3Section->setVersion(tokens[1]);
                    vst3Section->getVersionLabel()->setText(tokens[1], dontSendNotification);
                }

                if (tokens[0] == "pluginName")
                {
                    vst3Section->setPluginName(tokens[1]);
                    vst3Section->getPluginNameLabel()->setText(tokens[1], dontSendNotification);
                }

                if (tokens[0] == "description")
                {
                    vst3Section->setDescription(tokens[1]);
                    vst3Section->getDescriptionLabel()->setText(tokens[1], dontSendNotification);
                }

                if (tokens[0] == "pluginMC")
                {
                    vst3Section->setPluginMC(tokens[1]);
                    vst3Section->getPluginMCLabel()->setText(tokens[1], dontSendNotification);
                }

                if (tokens[0] == "pluginCode")
                {
                    vst3Section->setPluginCode(tokens[1]);
                    vst3Section->getPluginCodeLabel()->setText(tokens[1], dontSendNotification);
                }

                if (tokens[0] == "bundleID")
                {
                    vst3Section->setBundleID(tokens[1]);
                    vst3Section->getBundleIDLabel()->setText(tokens[1], dontSendNotification);
                }

                if (tokens[0] == "companyName")
                {
                    vst3Section->setCompanyName(tokens[1]);
                    vst3Section->getCompanyNameLabel()->setText(tokens[1], dontSendNotification);
                }   

                if (tokens[0] == "needsMidiInput")
                {
                    vst3Section->setNeedsMidiInput(tokens[1]);
                    vst3Section->getNeedsMidiInputComboBox()->setText(tokens[1], dontSendNotification);
                }

                if (tokens[0] == "VSTMidiInputs")
                {
                    vst3Section->setVSTMidiInputs(tokens[1].getIntValue());
                    vst3Section->getVSTMidiInputsComboBox()->setSelectedItemIndex(tokens[1].getIntValue());
                }

                if (tokens[0] == "needsMidiOutput")
                {
                    vst3Section->setNeedsMidiOutput(tokens[1]);
                    vst3Section->getNeedsMidiOutputComboBox()->setText(tokens[1], dontSendNotification);
                }

                if (tokens[0] == "VSTMidiOutputs")
                {
                    vst3Section->setVSTMidiOutputs(tokens[1].getIntValue());
                    vst3Section->getVSTMidiOutputsComboBox()->setSelectedItemIndex(tokens[1].getIntValue());
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