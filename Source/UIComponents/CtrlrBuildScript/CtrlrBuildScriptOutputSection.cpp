#pragma once
#include "stdafx.h"
#include "CtrlrBuildScriptOutputSection.h"

CtrlrBuildScriptOutputSection::CtrlrBuildScriptOutputSection()
{
    outputView = std::make_unique<TextEditor>("Output");
    addAndMakeVisible(*outputView);
    outputView->setFont(Font(14.0f, Font::plain));
    outputView->setJustification(Justification::topLeft);
    outputView->setReadOnly(true);
    outputView->setColour(TextEditor::textColourId, Colours::black);
    outputView->setColour(TextEditor::backgroundColourId, Colours::white);
    outputView->setMultiLine(true);
    outputView->setScrollbarsShown(true);

    clearButton = std::make_unique<TextButton>("");
    addAndMakeVisible(*clearButton);
    clearButton->setButtonText("Clear Output");
    clearButton->addListener(this);
}

CtrlrBuildScriptOutputSection::~CtrlrBuildScriptOutputSection() {}

void CtrlrBuildScriptOutputSection::paint(Graphics& g)
{
    const int buttonHeight = getHeight() / 5;
    
    // Space for outputView Title
    g.setColour(Colours::darkgrey);
    g.fillRect(                             0,      0,  getWidth(),     buttonHeight / 2);

    // Title for outputView
    g.setColour(Colours::white);
    g.setFont(Font(14.0f, Font::bold));
    g.drawText("Output",                    5,      0,  getWidth(),     buttonHeight / 2, Justification::left, true);
}

void CtrlrBuildScriptOutputSection::paintOverChildren(Graphics& g)
{
    g.setColour(Colours::darkgrey);
    g.drawRect(0, 0,getWidth(), getHeight(), 1);
}

void CtrlrBuildScriptOutputSection::resized()
{
    const int buttonHeight = getHeight() / 5;

	outputView->        setBounds(0,                    buttonHeight / 2,   getWidth(),     getHeight());
    clearButton->       setBounds(getWidth() - 100,     getHeight() - 40,   85,             35);
}

void CtrlrBuildScriptOutputSection::buttonClicked(Button* button)
{
	if (button == clearButton.get())
	{
		outputView->clear();
	}
}

void CtrlrBuildScriptOutputSection::insertTextAtCaret(const String &text)
{ 
    outputView->insertTextAtCaret(text); 
}

void CtrlrBuildScriptOutputSection::setCaretPosition(int newPosition)
{ 
    outputView->setCaretPosition(newPosition); 
}

void CtrlrBuildScriptOutputSection::setFont(const Font &font)
{
    outputView->setFont(font);
}