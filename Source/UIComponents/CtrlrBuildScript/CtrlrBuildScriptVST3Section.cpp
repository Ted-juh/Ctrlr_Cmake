#include "stdafx.h"
#include "CtrlrBuildScriptVST3Section.h"
#include "CtrlrBuildScriptMain.h"

CtrlrBuildScriptVST3Section::CtrlrBuildScriptVST3Section(CtrlrBuildScriptOutputSection *outputSection)	: outputSection(outputSection)
{
	// First row
	lProductName = std::make_unique<Label>("");
	addAndMakeVisible(*lProductName);
	lProductName->setJustificationType(Justification::left);
	lProductName->setText("Product Name", dontSendNotification);

	tProductName = std::make_unique<Label>("");
	addAndMakeVisible(*tProductName);
	tProductName->setText("...", dontSendNotification);
	tProductName->setEditable(true);

	lVersion = std::make_unique<Label>("");
	addAndMakeVisible(*lVersion);
	lVersion->setJustificationType(Justification::left);
	lVersion->setText("Version", dontSendNotification);

	tVersion = std::make_unique<Label>("");
	addAndMakeVisible(*tVersion);
	tVersion->setText("...", dontSendNotification);
	tVersion->setEditable(true);

	lPluginName = std::make_unique<Label>("");
	addAndMakeVisible(*lPluginName);
	lPluginName->setJustificationType(Justification::left);
	lPluginName->setText("Plugin Name", dontSendNotification);

	tPluginName = std::make_unique<Label>("");
	addAndMakeVisible(*tPluginName);
	tPluginName->setText("...", dontSendNotification);
	tPluginName->setEditable(true);

	lDescription = std::make_unique<Label>("");
	addAndMakeVisible(*lDescription);
	lDescription->setJustificationType(Justification::left);
	lDescription->setText("Description", dontSendNotification);

	tDescription = std::make_unique<Label>("");
	addAndMakeVisible(*tDescription);
	tDescription->setText("...", dontSendNotification);
	tDescription->setEditable(true);

	lPluginMC = std::make_unique<Label>("");
	addAndMakeVisible(*lPluginMC);
	lPluginMC->setJustificationType(Justification::left);
	lPluginMC->setText("Plugin Manufacturer Code", dontSendNotification);

	tPluginMC = std::make_unique<LimitedLengthLabel>("Plugin Manufacturer Code","...");
	addAndMakeVisible(*tPluginMC);
	tPluginMC->setText("...", dontSendNotification);
	tPluginMC->setEditable(true);

	lPluginCode = std::make_unique<Label>("");
	addAndMakeVisible(*lPluginCode);
	lPluginCode->setJustificationType(Justification::left);
	lPluginCode->setText("Plugin Code", dontSendNotification);

	tPluginCode = std::make_unique<LimitedLengthLabel>("Plugin Code","...");
	addAndMakeVisible(*tPluginCode);
	tPluginCode->setText("...", dontSendNotification);
	tPluginCode->setEditable(true);

	// Second row
	lBundleID = std::make_unique<Label>("");
	addAndMakeVisible(*lBundleID);
	lBundleID->setJustificationType(Justification::left);
	lBundleID->setText("Bundle ID", dontSendNotification);

	tBundleID = std::make_unique<Label>("");
	addAndMakeVisible(*tBundleID);
	tBundleID->setText("...", dontSendNotification);
	tBundleID->setEditable(true);

	lCompanyName = std::make_unique<Label>("");
	addAndMakeVisible(*lCompanyName);
	lCompanyName->setJustificationType(Justification::left);
	lCompanyName->setText("Company Name", dontSendNotification);

	tCompanyName = std::make_unique<Label>("");
	addAndMakeVisible(*tCompanyName);
	tCompanyName->setText("...", dontSendNotification);
	tCompanyName->setEditable(true);

	lNeedsMidiInput = std::make_unique<Label>("");
	addAndMakeVisible(*lNeedsMidiInput);
	lNeedsMidiInput->setJustificationType(Justification::left);
	lNeedsMidiInput->setText("Needs Midi Input", dontSendNotification);

	tNeedsMidiInput = std::make_unique<ComboBox>("");
	addAndMakeVisible(*tNeedsMidiInput);
	tNeedsMidiInput->addItem("FALSE", 1);
	tNeedsMidiInput->addItem("TRUE", 2);
	tNeedsMidiInput->setSelectedItemIndex(1);

	lNeedsMidiOutput = std::make_unique<Label>("");
	addAndMakeVisible(*lNeedsMidiOutput);
	lNeedsMidiOutput->setJustificationType(Justification::left);
	lNeedsMidiOutput->setText("Needs Midi Output", dontSendNotification);

	tNeedsMidiOutput = std::make_unique<ComboBox>("");
	addAndMakeVisible(*tNeedsMidiOutput);
	tNeedsMidiOutput->addItem("FALSE", 1);
	tNeedsMidiOutput->addItem("TRUE", 2);
	tNeedsMidiOutput->setSelectedItemIndex(1);

	lVSTMidiInputs = std::make_unique<Label>("");
	addAndMakeVisible(*lVSTMidiInputs);
	lVSTMidiInputs->setJustificationType(Justification::left);
	lVSTMidiInputs->setText("VST Midi Inputs", dontSendNotification);
	
	tVSTMidiInputs = std::make_unique<ComboBox>("");
	addAndMakeVisible(*tVSTMidiInputs);
	tVSTMidiInputs->addItem("0", 1);
	tVSTMidiInputs->addItem("1", 2);
	tVSTMidiInputs->addItem("2", 3);
	tVSTMidiInputs->addItem("3", 4);
	tVSTMidiInputs->addItem("4", 5);
	tVSTMidiInputs->addItem("5", 6);
	tVSTMidiInputs->addItem("6", 7);
	tVSTMidiInputs->addItem("7", 8);
	tVSTMidiInputs->addItem("8", 9);
	tVSTMidiInputs->addItem("9", 10);
	tVSTMidiInputs->addItem("10", 11);
	tVSTMidiInputs->addItem("11", 12);
	tVSTMidiInputs->addItem("12", 13);
	tVSTMidiInputs->addItem("13", 14);
	tVSTMidiInputs->addItem("14", 15);
	tVSTMidiInputs->addItem("15", 16);
	tVSTMidiInputs->addItem("16", 17);
	tVSTMidiInputs->setSelectedItemIndex(1);

	lVSTMidiOutputs = std::make_unique<Label>("");
	addAndMakeVisible(*lVSTMidiOutputs);
	lVSTMidiOutputs->setJustificationType(Justification::left);
	lVSTMidiOutputs->setText("VST Midi Outputs", dontSendNotification);
	
	tVSTMidiOutputs = std::make_unique<ComboBox>("");
	addAndMakeVisible(*tVSTMidiOutputs);
	tVSTMidiOutputs->addItem("0", 1);
	tVSTMidiOutputs->addItem("1", 2);
	tVSTMidiOutputs->addItem("2", 3);
	tVSTMidiOutputs->addItem("3", 4);
	tVSTMidiOutputs->addItem("4", 5);
	tVSTMidiOutputs->addItem("5", 6);
	tVSTMidiOutputs->addItem("6", 7);
	tVSTMidiOutputs->addItem("7", 8);
	tVSTMidiOutputs->addItem("8", 9);
	tVSTMidiOutputs->addItem("9", 10);
	tVSTMidiOutputs->addItem("10", 11);
	tVSTMidiOutputs->addItem("11", 12);
	tVSTMidiOutputs->addItem("12", 13);
	tVSTMidiOutputs->addItem("13", 14);
	tVSTMidiOutputs->addItem("14", 15);
	tVSTMidiOutputs->addItem("15", 16);
	tVSTMidiOutputs->addItem("16", 17);
	tVSTMidiOutputs->setSelectedItemIndex(1);
}

CtrlrBuildScriptVST3Section::~CtrlrBuildScriptVST3Section(){}

void CtrlrBuildScriptVST3Section::paint(Graphics& g)
{
	const int w = getWidth();
	const int y = getHeight();
 	const int buttonHeight = y / 7;
	const int qmX = (w * 0.95);
    const int qmY = (y * 0.02);
    

	g.setColour(Colours::darkgrey);
	g.fillRect(0, 0, getWidth(), buttonHeight);

	g.setColour(Colours::white);
	g.setFont(Font(14.0f, Font::bold));
	g.drawText("VST3 Options", 5, 0, getWidth(), buttonHeight, Justification::left);

	g.setColour(Colours::whitesmoke);
	g.fillRect(0, buttonHeight, getWidth(), getHeight());

	g.setColour(Colours::black);
	g.drawRect(0, 0, getWidth(), getHeight());

    // Space for Question Mark
    g.setColour(Colours::darkgrey);
    g.fillRect(                             qmX,         qmY,      buttonHeight - qmY,     buttonHeight -  (2 * qmY));
    g.setColour(Colours::whitesmoke);
    g.drawRect(                             qmX,         qmY,      buttonHeight - qmY,     buttonHeight -  (2 * qmY),    1);
    g.setFont(Font(17.0f, Font::bold));
    g.drawText("?",                         qmX,         qmY,      buttonHeight - qmY,     buttonHeight -  (2 * qmY), Justification::centred, true);

    questionMarkAreaVST3 = juce::Rectangle<int>(qmX, 0 + qmY, buttonHeight - qmY, buttonHeight - (2 * qmY));
}

void CtrlrBuildScriptVST3Section::paintOverChildren(Graphics& g)
{
	const int amountBut = 4;
	const int buttonSpace = getWidth() / amountBut;
	const int buttonHeight = getHeight() / 7;

	g.setColour(Colours::darkgrey);
	
for (int i = 1; i <= 3; ++i) {
    float x = static_cast<float>(buttonSpace * i);
    g.drawLine(x, 0.0f, x, static_cast<float>(getHeight()), 1.0f);
}


for (int i = 2; i <= 6; ++i) {
    float y = static_cast<float>(buttonHeight * i);
    g.drawLine(0.0f, y, static_cast<float>(getWidth()), y, 1.0f);
}

}

void CtrlrBuildScriptVST3Section::resized()
{
	const int amountBut = 4;
	const int buttonSpace = getWidth() / amountBut;
	const int buttonHeight = getHeight() / 7;

	//First row
	lProductName->setBounds(			0,						buttonHeight,				buttonSpace,		buttonHeight);
	tProductName->setBounds(			0 + buttonSpace,		buttonHeight,				buttonSpace,		buttonHeight);

	lVersion->setBounds(				0,						buttonHeight * 2,			buttonSpace,		buttonHeight);
	tVersion->setBounds(				0 + buttonSpace,		buttonHeight * 2,			buttonSpace,		buttonHeight);

	lPluginName->setBounds(				0,						buttonHeight * 3,			buttonSpace,		buttonHeight);
	tPluginName->setBounds(				0 + buttonSpace,		buttonHeight * 3,			buttonSpace,		buttonHeight);

	lDescription->setBounds(			0,						buttonHeight * 4,			buttonSpace,		buttonHeight);
	tDescription->setBounds(			0 + buttonSpace,		buttonHeight * 4,			buttonSpace,		buttonHeight);

	lPluginMC->setBounds(				0,						buttonHeight * 5,			buttonSpace,		buttonHeight);
	tPluginMC->setBounds(				0 + buttonSpace,		buttonHeight * 5,			buttonSpace,		buttonHeight);

	lPluginCode->setBounds(				0,						buttonHeight * 6,			buttonSpace,		buttonHeight);
	tPluginCode->setBounds(				0 + buttonSpace,		buttonHeight * 6,			buttonSpace,		buttonHeight);


	//Second row
	lBundleID->setBounds(				0 + buttonSpace * 2,	buttonHeight,				buttonSpace,		buttonHeight);
	tBundleID->setBounds(				0 + buttonSpace * 3,	buttonHeight,				buttonSpace,		buttonHeight);

	lCompanyName->setBounds(			0 + buttonSpace * 2,	buttonHeight * 2,			buttonSpace,		buttonHeight);
	tCompanyName->setBounds(			0 + buttonSpace * 3,	buttonHeight * 2,			buttonSpace,		buttonHeight);

	lNeedsMidiInput->setBounds(			0 + buttonSpace * 2,	buttonHeight * 3,			buttonSpace,		buttonHeight);
	tNeedsMidiInput->setBounds(			0 + buttonSpace * 3,	buttonHeight * 3,			buttonSpace+2,		buttonHeight);

	lVSTMidiInputs->setBounds(			0 + buttonSpace * 2,	buttonHeight * 4,			buttonSpace,		buttonHeight);
	tVSTMidiInputs->setBounds(			0 + buttonSpace * 3,	buttonHeight * 4,			buttonSpace+2,		buttonHeight);

	lNeedsMidiOutput->setBounds(		0 + buttonSpace * 2,	buttonHeight * 5,			buttonSpace,		buttonHeight);
	tNeedsMidiOutput->setBounds(		0 + buttonSpace * 3,	buttonHeight * 5,			buttonSpace+2,		buttonHeight);

	lVSTMidiOutputs->setBounds(			0 + buttonSpace * 2,	buttonHeight * 6,			buttonSpace+2,		buttonHeight);
	tVSTMidiOutputs->setBounds(			0 + buttonSpace * 3,	buttonHeight * 6,			buttonSpace+2,		buttonHeight-1);
}

void CtrlrBuildScriptVST3Section::buttonClicked(Button* button)
{

}

void CtrlrBuildScriptVST3Section::mouseDown(const juce::MouseEvent& event)
{
	        if (questionMarkAreaVST3.contains(event.getPosition()))
        {
            if (outputSection != nullptr)
            {
                outputSection->getOutputView().clear();

                outputSection->setFont(Font(15.0f, Font::bold));
                outputSection->insertTextAtCaret("Product Name: \n");
                outputSection->setFont(Font(14.0f, Font::plain));
                outputSection->insertTextAtCaret(
                                        "The name of the output built by this target.\n\n");
                outputSection->setFont(Font(15.0f, Font::bold));
                outputSection->insertTextAtCaret("Version: \n");
                outputSection->setFont(Font(14.0f, Font::plain));
                outputSection->insertTextAtCaret( 
                                        "Version number in format: major.minor.bugfix .\n\n");
                outputSection->setFont(Font(15.0f, Font::bold));
                outputSection->insertTextAtCaret("Plugin Name \n");
                outputSection->setFont(Font(14.0f, Font::plain));
                outputSection->insertTextAtCaret(
                                        "Name of the Plugin that will be displayed in DAW.\n\n");
                outputSection->setFont(Font(15.0f, Font::bold));
                outputSection->insertTextAtCaret("Description: \n");
                outputSection->setFont(Font(14.0f, Font::plain));
                outputSection->insertTextAtCaret(
                                        "Short description of the plugin or leave blank.\n\n");
				outputSection->setFont(Font(15.0f, Font::bold));
				outputSection->insertTextAtCaret("Plugin Manufacturer Code: \n");
				outputSection->setFont(Font(14.0f, Font::plain));
				outputSection->insertTextAtCaret(
										"Manufacturer code of the plugin. 4-Character unique-id. Use one uppercase letter.\n\n");
				outputSection->setFont(Font(15.0f, Font::bold));
				outputSection->insertTextAtCaret("Plugin Code: \n");
				outputSection->setFont(Font(14.0f, Font::plain));
				outputSection->insertTextAtCaret(
										"A 4-character unique ID of your plugin. Use one uppercase letter.\n\n");
				outputSection->setFont(Font(15.0f, Font::bold));
				outputSection->insertTextAtCaret("Bundle ID: \n");
				outputSection->setFont(Font(14.0f, Font::plain));
				outputSection->insertTextAtCaret(
										"Unique identifier for the plugin. Use notation: com.yourcompany.productname .\n\n");
				outputSection->setFont(Font(15.0f, Font::bold));
				outputSection->insertTextAtCaret("Company Name: \n");
				outputSection->setFont(Font(14.0f, Font::plain));
				outputSection->insertTextAtCaret(
										"Name of the company that owns the plugin.\n\n");
				outputSection->setFont(Font(15.0f, Font::bold));
				outputSection->insertTextAtCaret("Needs Midi Input/ Output: \n");
				outputSection->setFont(Font(14.0f, Font::plain));
				outputSection->insertTextAtCaret(
										"Does the plugin need Midi Input/ Output? Yes or No?.\n\n");
				outputSection->setFont(Font(15.0f, Font::bold));
				outputSection->insertTextAtCaret("VST Midi Inputs/ Outputs: \n");
				outputSection->setFont(Font(14.0f, Font::plain));
				outputSection->insertTextAtCaret(
										"Number of Midi Inputs/ Outputs for the VST plugin.\n\n");

				outputSection->setCaretPosition(0);																				

            }
        }
}