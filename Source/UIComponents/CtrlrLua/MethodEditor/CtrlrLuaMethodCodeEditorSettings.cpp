#include "stdafx.h"
#include "CtrlrLuaMethodEditor.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrLuaMethodCodeEditorSettings.h"

CtrlrLuaMethodCodeEditorSettings::CtrlrLuaMethodCodeEditorSettings (CtrlrLuaMethodEditor &_owner)
    : owner(_owner),
      fontTypeface (0),
      fontBold (0),
      fontUnderline (0),
      fontItalic (0),
      fontSize (0),
      bgColour (0),
      fontTest (0)
{
    addAndMakeVisible (fontTypeface = new ComboBox (""));
    fontTypeface->setEditableText (false);
    fontTypeface->setJustificationType (Justification::centredLeft);
    fontTypeface->setTextWhenNothingSelected ("");
    fontTypeface->setTextWhenNoChoicesAvailable (L"(no choices)");
    fontTypeface->addListener (this);

    addAndMakeVisible (fontBold = new ToggleButton (""));
    fontBold->setButtonText (L"Bold");
    fontBold->addListener (this);

    addAndMakeVisible (fontUnderline = new ToggleButton (""));
    fontUnderline->setButtonText (L"Underline");
    fontUnderline->addListener (this);

    addAndMakeVisible (fontItalic = new ToggleButton (""));
    fontItalic->setButtonText (L"Italic");
    fontItalic->addListener (this);

    addAndMakeVisible (fontSize = new Slider (""));
    fontSize->setRange (0, 128, 1);
    fontSize->setSliderStyle (Slider::IncDecButtons);
    fontSize->setTextBoxStyle (Slider::TextBoxLeft, false, 32, 24);
    fontSize->addListener (this);

    addAndMakeVisible (bgColour = new CtrlrColourEditorComponent (this));
    addAndMakeVisible (fontTest = new CodeEditorComponent (codeDocument, &luaTokeniser));

	codeFont = owner.getOwner().getCtrlrManagerOwner().getFontManager().getFontFromString(owner.getComponentTree().getProperty(Ids::luaMethodEditorFont, owner.getOwner().getCtrlrManagerOwner().getFontManager().getStringFromFont (Font(owner.getOwner().getCtrlrManagerOwner().getFontManager().getDefaultMonoFontName(), 14.0f, Font::plain))));
	bgColour->setColour (VAR2COLOUR(owner.getComponentTree().getProperty(Ids::luaMethodEditorBgColour, Colours::white.toString())));

	fontSize->setValue (codeFont.getHeight(), dontSendNotification);
	fontUnderline->setToggleState (codeFont.isUnderlined(), dontSendNotification);
	fontBold->setToggleState (codeFont.isBold(), dontSendNotification);
	fontItalic->setToggleState (codeFont.isItalic(), dontSendNotification);
	owner.getOwner().getCtrlrManagerOwner().getFontManager().fillCombo (*fontTypeface);
	fontTypeface->setText (codeFont.getTypefaceName(), sendNotification);
	codeDocument.replaceAllContent ("-- This is a comment\nfunction myFunction(argument)\n\tcall(\"string\")\nend");

    setSize (320, 200);
}

CtrlrLuaMethodCodeEditorSettings::~CtrlrLuaMethodCodeEditorSettings()
{
    deleteAndZero (fontTypeface);
    deleteAndZero (fontBold);
    deleteAndZero (fontUnderline);
    deleteAndZero (fontItalic);
    deleteAndZero (fontSize);
    deleteAndZero (bgColour);
    deleteAndZero (fontTest);
}

void CtrlrLuaMethodCodeEditorSettings::paint (Graphics& g)
{
}

void CtrlrLuaMethodCodeEditorSettings::resized()
{
    fontTypeface->setBounds (8, 8, 304, 24);
    fontBold->setBounds (8, 40, 56, 24);
    fontUnderline->setBounds (136, 40, 88, 24);
    fontItalic->setBounds (72, 40, 64, 24);
    fontSize->setBounds (232, 40, 78, 24);
    bgColour->setBounds (8, 72, 304, 24);
    fontTest->setBounds (8, 104, 304, 88);
}

void CtrlrLuaMethodCodeEditorSettings::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == fontTypeface)
    {
    }
	changeListenerCallback(nullptr);
}

void CtrlrLuaMethodCodeEditorSettings::buttonClicked (Button* buttonThatWasClicked)
{

    if (buttonThatWasClicked == fontBold)
    {
    }
    else if (buttonThatWasClicked == fontUnderline)
    {
    }
    else if (buttonThatWasClicked == fontItalic)
    {
    }

	changeListenerCallback(nullptr);
}

void CtrlrLuaMethodCodeEditorSettings::sliderValueChanged (Slider* sliderThatWasMoved)
{
    if (sliderThatWasMoved == fontSize)
    {
    }
	changeListenerCallback(nullptr);
}

void CtrlrLuaMethodCodeEditorSettings::changeListenerCallback (ChangeBroadcaster* source)
{
	fontTest->setColour (CodeEditorComponent::backgroundColourId, bgColour->getColour());
	fontTest->setFont (getFont());
	repaint();
}

const Font CtrlrLuaMethodCodeEditorSettings::getFont()
{
	Font font = owner.getOwner().getCtrlrManagerOwner().getFontManager().getFont (fontTypeface->getSelectedItemIndex());

	if (fontTypeface)
		font.setTypefaceName (fontTypeface->getText());
	else
		return (font);

	font.setHeight (fontSize->getValue());
	font.setBold (fontBold->getToggleState());
	font.setItalic (fontItalic->getToggleState());
	font.setUnderline (fontUnderline->getToggleState());
	return (font);
}

const Colour CtrlrLuaMethodCodeEditorSettings::getColour()
{
	return (bgColour->getColour());
}