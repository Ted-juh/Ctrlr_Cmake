#include "stdafx.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrBuildScriptDialogWindow.h"


CtrlrBuildScriptDialogWindow::CtrlrBuildScriptDialogWindow(CtrlrManager &_owner) 
    : owner(_owner)
{
    ideSection = new IDESection();
    addAndMakeVisible (ideSection);

    optionsSection = new OptionsSection();
    addAndMakeVisible (optionsSection);

    outputSection = new OutputSection();
    addAndMakeVisible (outputSection);

    /*
    addAndMakeVisible(cancelButton = new TextButton(""));
    cancelButton->setButtonText("Cancel");
    cancelButton->addListener(this);
    */

    addAndMakeVisible(okButton = new TextButton(""));
    okButton->setButtonText("OK");
    okButton->setVisible(false);
    okButton->addListener(this);

    const float factor = 1.5f;
    int newWidth = jmax(240, (int)(getWidth() * factor));
    int newHeight = jmax(700, (int)(getHeight() * factor));

    if (newWidth != getWidth() || newHeight != getHeight())
    {
        setSize(newWidth, newHeight);
    }
}

CtrlrBuildScriptDialogWindow::~CtrlrBuildScriptDialogWindow()
{
    ideSection = nullptr;
	optionsSection = nullptr;
    outputSection = nullptr;
    okButton = nullptr;

    //cancelButton = nullptr;
}

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

    if (okButton->isVisible())
    {
    g.setColour(Colours::darkgrey);
    g.drawRect(startRect + (buttonSpace * 2), rectLineHeight * 23, buttonSpace * 2, buttonHeight, 1.0);
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

    ideSection          ->setBounds(startRect,                          rectLineHeight * 1,     rectWidth,          buttonHeight * 5);
    optionsSection      ->setBounds(startRect,                          rectLineHeight * 12,    rectWidth,          buttonHeight * 5);
    okButton            ->setBounds(startRect + (buttonSpace * 2),      rectLineHeight * 23,    buttonSpace * 2,    buttonHeight);
    outputSection       ->setBounds(startRect,                          rectLineHeight * 26,    rectWidth,          buttonHeight * 7);


    //cancelButton->setBounds(10, getHeight() - 40, 100, 30);
}

void CtrlrBuildScriptDialogWindow::setButtonStateAndColour(TextButton* button, bool state)
{
    button->setToggleState(state, dontSendNotification);
    button->setColour(TextButton::buttonColourId,   state ? Colours::darkgrey : Colours::whitesmoke);       // on/off
    button->setColour(TextButton::buttonOnColourId, state ? Colours::darkgrey : Colours::whitesmoke);       // on/off
    button->setColour(TextButton::textColourOffId,  state ? Colours::black : Colours::black);               // on/off
    button->setColour(TextButton::textColourOnId,   state ? Colours::white : Colours::white);			    // on/off          
}

void CtrlrBuildScriptDialogWindow::buttonClicked(Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == okButton) 
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



































  