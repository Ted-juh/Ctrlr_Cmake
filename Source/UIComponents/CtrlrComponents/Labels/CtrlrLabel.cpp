#include "stdafx.h"
#include "CtrlrLabel.h"
#include "CtrlrUtilitiesGUI.h"
#include "CtrlrLuaManager.h"
#include "JuceClasses/LLookAndFeel.h"

CtrlrLabelInternal::CtrlrLabelInternal(CtrlrLabel &_owner, const String &componentName, const String &labelText)
	: Label (componentName, labelText), owner(_owner)
{
}

TextEditor *CtrlrLabelInternal::createEditorComponent()
{
	TextEditor* const ed = new TextEditor (getName());
	ed->setFont (getFont());
	ed->setInputRestrictions (owner.getProperty(::Ids::uiLabelInputMaxLength), owner.getProperty(::Ids::uiLabelInputAllowedChars));

	const int cols[] = { TextEditor::backgroundColourId,
                       TextEditor::textColourId,
                       TextEditor::highlightColourId,
                       TextEditor::highlightedTextColourId,
                       TextEditor::outlineColourId,
                       TextEditor::focusedOutlineColourId,
                       TextEditor::shadowColourId,
                       CaretComponent::caretColourId };

	for (int i = 0; i < numElementsInArray (cols); ++i)
		ed->setColour (cols[i], findColour (cols[i]));

	return ed;
}

bool CtrlrLabelInternal::keyPressed (const KeyPress &key)
{
	return (false);
}

CtrlrLabel::CtrlrLabel (CtrlrModulator &owner)
    : CtrlrComponent(owner),
      ctrlrLabel (0)
{
    addAndMakeVisible (ctrlrLabel = new CtrlrLabelInternal (*this, "ctrlrLabel",
                                               "label text"));
    ctrlrLabel->setFont (Font (15.0000f, Font::plain));
    ctrlrLabel->setJustificationType (Justification::centredLeft);
    ctrlrLabel->setEditable (false, false, false);
    ctrlrLabel->setColour (TextEditor::textColourId, Colours::black);
    ctrlrLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

	owner.setProperty (Ids::modulatorIsStatic, true);
	owner.setProperty (Ids::modulatorVstExported, false);

	setProperty (Ids::uiLabelBgColour, "0x00000000");
	setProperty (Ids::uiLabelTextColour, "0xff000000");
	setProperty (Ids::uiLabelOutline, 0);
	setProperty (Ids::uiLabelOutlineColour, "0x00000000");
	setProperty (Ids::uiLabelJustification, "centred");
	setProperty (Ids::uiLabelFitFont, false);
	setProperty (Ids::uiLabelFont, FONT2STR (Font(14)));
	setProperty (Ids::uiLabelText, "Label text");
	setProperty (Ids::uiLabelDisplaysAllValues, false);
	setProperty (Ids::uiLabelDisplayFormat, "%n(%N) = %v(%h)");
	setProperty (Ids::uiLabelInputHighlightTextColour, "0xffffffff");
	setProperty (Ids::uiLabelInputHighlightColour, "0xff0000ff");
	setProperty (Ids::uiLabelEditOnSingleClick, false);
	setProperty (Ids::uiLabelEditOnDoubleClick, false);
	setProperty (Ids::uiLabelEditFocusDiscardsChanges, true);
	setProperty (Ids::uiLabelInputAllowedChars, "");
	setProperty (Ids::uiLabelInputAllowedChars, "");
	setProperty (Ids::uiLabelInputMaxLength, 1024);
	setProperty (Ids::uiLabelChangedCbk, COMBO_NONE_ITEM);

	ctrlrLabel->addListener (this);
	componentTree.addListener (this);

    setSize (88, 24);
}

CtrlrLabel::~CtrlrLabel()
{
	owner.getOwnerPanel().removePanelListener(this);
    deleteAndZero (ctrlrLabel);
}

void CtrlrLabel::paint (Graphics& g)
{
	const int i = getProperty(Ids::uiLabelOutline);
	const int i2 = 2*i;
	g.setColour (VAR2COLOUR(getProperty(Ids::uiLabelBgColour)));

	if (getWidth() > i2 && getHeight() > i2)
	    g.fillRect( i, i, (getWidth() - 2*i), (getHeight() - 2*i));
	g.setColour (VAR2COLOUR(getProperty(Ids::uiLabelOutlineColour)));
	g.drawRect (0, 0, getWidth(), getHeight(),  i);
}

void CtrlrLabel::resized()
{
	if (restoreStateInProgress)
		return;
	if ((bool)ctrlrLabel->getProperties() ["fh"] == true)
	{
		Font f = ctrlrLabel->getFont();
		f.setHeight (getHeight()*0.95f);
		ctrlrLabel->setFont (f);
	}
	ctrlrLabel->setBounds (getUsableRect());
}

double CtrlrLabel::getComponentMaxValue()
{
	return (1);
}

void CtrlrLabel::setComponentValue (const double newValue, const bool sendChangeMessage)
{
	if (sendChangeMessage)
	{
		owner.getProcessor().setValueGeneric (CtrlrModulatorValue(newValue,CtrlrModulatorValue::changedByGUI), true);
	}
}

double CtrlrLabel::getComponentValue()
{
	return (1);
}

int CtrlrLabel::getComponentMidiValue()
{
	return (1);
}

void CtrlrLabel::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (property == Ids::uiLabelDisplaysAllValues)
	{
		if ((bool)getProperty(property) == true)
		{
			owner.getOwnerPanel().addPanelListener(this);
		}
		else
		{
			owner.getOwnerPanel().removePanelListener(this);
		}
	}
	else if (property == Ids::uiLabelText)
	{
		ctrlrLabel->setText (getProperty(Ids::uiLabelText), sendNotification);
	}
	else if (property == Ids::uiLabelBgColour)
	{
		ctrlrLabel->setColour (Label::backgroundColourId, VAR2COLOUR(getProperty(Ids::uiLabelBgColour)));
	}
	else if (property == Ids::uiLabelTextColour)
	{
		ctrlrLabel->setColour (Label::textColourId, VAR2COLOUR(getProperty(Ids::uiLabelTextColour)));
		ctrlrLabel->setColour (TextEditor::textColourId, VAR2COLOUR(getProperty(Ids::uiLabelTextColour)));
	}
	else if (property == Ids::uiLabelOutline)
	{
		ctrlrLabel->setBorderSize (BorderSize <int> (getProperty (property)));
		repaint();
	}
	else if (property == Ids::uiLabelOutlineColour)
	{
		ctrlrLabel->setColour (Label::outlineColourId, VAR2COLOUR(getProperty(Ids::uiLabelOutlineColour)));
		repaint();
	}
	else if (property == Ids::uiLabelFitFont || property == Ids::uiLabelFont)
	{
		ctrlrLabel->getProperties().set ("fh", getProperty(Ids::uiLabelFitFont));
		const String t = ctrlrLabel->getText();
		ctrlrLabel->setFont (STR2FONT(getProperty(Ids::uiLabelFont)));
		ctrlrLabel->setText (t, dontSendNotification);
	}
	else if (property == Ids::uiLabelJustification)
	{
		ctrlrLabel->setJustificationType (justificationFromProperty (getProperty(property)));
	}

	else if (property == Ids::uiLabelEditOnSingleClick
		|| property == Ids::uiLabelEditOnDoubleClick
		|| property == Ids::uiLabelEditFocusDiscardsChanges)
	{
		ctrlrLabel->setEditable ((bool)getProperty(Ids::uiLabelEditOnSingleClick),(bool)getProperty(Ids::uiLabelEditOnDoubleClick),(bool)getProperty(Ids::uiLabelEditFocusDiscardsChanges));
	}
	else if (property == Ids::uiLabelChangedCbk)
	{
		if (getProperty(property) == "")
			return;

		labelChangedCbk = owner.getOwnerPanel().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::uiLabelInputHighlightTextColour || property == Ids::uiLabelInputHighlightColour)
	{
		ctrlrLabel->setColour (TextEditor::highlightColourId, VAR2COLOUR(getProperty(Ids::uiLabelInputHighlightColour)));
		ctrlrLabel->setColour (TextEditor::highlightedTextColourId, VAR2COLOUR(getProperty(Ids::uiLabelInputHighlightTextColour)));
	}
	else
	{
		CtrlrComponent::valueTreePropertyChanged(treeWhosePropertyHasChanged, property);
	}

	if (restoreStateInProgress == false)
	{
		resized();
	}
}

void CtrlrLabel::setComponentText(const String &componentText)
{
	setProperty (Ids::uiLabelText, componentText);
}

const String CtrlrLabel::getComponentText()
{
	return (ctrlrLabel->getText());
}

void CtrlrLabel::modulatorChanged (CtrlrModulator *modulatorThatChanged)
{
	if (modulatorThatChanged == 0 || modulatorThatChanged->getComponent() == 0)
		return;

	if ((bool)modulatorThatChanged->getComponent()->getProperty(Ids::componentExcludedFromLabelDisplay) == true)
		return;

	ctrlrLabel->setText (labelFromProperty (modulatorThatChanged, getProperty (Ids::uiLabelDisplayFormat)), dontSendNotification);
}

void CtrlrLabel::labelTextChanged (Label* labelThatHasChanged)
{
	if (getProperty (Ids::uiLabelText).toString() != labelThatHasChanged->getText())
        setProperty (Ids::uiLabelText, labelThatHasChanged->getText(), false);

	setComponentValue(0, true);

	if (labelChangedCbk && !labelChangedCbk.wasObjectDeleted())
	{
		if (labelChangedCbk->isValid())
		{
			owner.getOwnerPanel().getCtrlrLuaManager().getMethodManager().call (labelChangedCbk, dynamic_cast<CtrlrComponent*>(this), labelThatHasChanged->getText());
		}
	}
}

void CtrlrLabel::lookAndFeelChanged ()
{
}

CtrlrLabel &CtrlrLabel::setLabelText(const String &text)
{
	setProperty (Ids::uiLabelText, text);

	return (*this);
}

CtrlrLabel &CtrlrLabel::appendText(const String &text)
{
	setProperty (Ids::uiLabelText, ctrlrLabel->getText() + text);

	return (*this);
}

const String CtrlrLabel::getText()
{
	return (ctrlrLabel->getText());
}

void CtrlrLabel::customLookAndFeelChanged(LookAndFeelBase *customLookAndFeel)
{
    ctrlrLabel->setLookAndFeel (customLookAndFeel);
}

bool CtrlrLabel::keyPressed (const KeyPress &key)
{
	return (false);
}