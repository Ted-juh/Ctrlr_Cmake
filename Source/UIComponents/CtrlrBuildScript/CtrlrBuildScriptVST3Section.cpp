#include "stdafx.h"
#include "CtrlrBuildScriptVST3Section.h"
#include "CtrlrBuildScriptMain.h"

CtrlrBuildScriptVST3Section::CtrlrBuildScriptVST3Section()
{
	lProductName = std::make_unique<Label>("");
	addAndMakeVisible(*lProductName);
	lProductName->setJustificationType(Justification::centred);
	lProductName->setText("Product Name", dontSendNotification);

	tProductName = std::make_unique<Label>("");
	addAndMakeVisible(*tProductName);
	tProductName->setText("", dontSendNotification);

	lCompanyName = std::make_unique<Label>("");
	addAndMakeVisible(*lCompanyName);
	lCompanyName->setJustificationType(Justification::centred);

	tCompanyName = std::make_unique<Label>("");
	addAndMakeVisible(*tCompanyName);
	tCompanyName->setText("", dontSendNotification);

	lCompanyURL = std::make_unique<Label>("");
	addAndMakeVisible(*lCompanyURL);
	lCompanyURL->setJustificationType(Justification::centred);

	tCompanyURL = std::make_unique<Label>("");
	addAndMakeVisible(*tCompanyURL);
	tCompanyURL->setText("", dontSendNotification);

	setSize(480, 250);
}

CtrlrBuildScriptVST3Section::~CtrlrBuildScriptVST3Section(){}

void CtrlrBuildScriptVST3Section::paint(Graphics& g)
{
	const int buttonHeight = getHeight() / 10;

	g.setColour(Colours::darkgrey);
	g.fillRect(0, 0, getWidth(), buttonHeight);

	g.setColour(Colours::white);
	g.setFont(Font(14.0f, Font::bold));
	g.drawText("VST3 Options", 0, 0, getWidth(), buttonHeight, Justification::centred);

	g.setColour(Colours::whitesmoke);
	g.fillRect(0, buttonHeight, getWidth(), getHeight());
}

void CtrlrBuildScriptVST3Section::resized()
{
	const int amountBut = 4;
	const int buttonSpace = getWidth() / amountBut;
	const int buttonHeight = getHeight() / 10;

	lProductName->setBounds(			0,						buttonHeight,			buttonSpace,	buttonHeight);
	tProductName->setBounds(			0 + buttonSpace,		buttonHeight,			buttonSpace,	buttonHeight);
	lCompanyName->setBounds(			0 ,						buttonHeight * 2,		buttonSpace,	buttonHeight);
	tCompanyName->setBounds(			0 + buttonSpace,		buttonHeight * 2,		buttonSpace,	buttonHeight);

	lCompanyURL->setBounds(				0 + buttonSpace *2,		buttonHeight,			buttonSpace,	buttonHeight);
	tCompanyURL->setBounds(				0 + buttonSpace *3,		buttonHeight,			buttonSpace,	buttonHeight);
	

}

void CtrlrBuildScriptVST3Section::buttonClicked(Button* button)
{
}