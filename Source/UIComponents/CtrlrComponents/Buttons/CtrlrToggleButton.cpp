#include "stdafx.h"
#include "CtrlrToggleButton.h"
#include "CtrlrValueMap.h"
#include "CtrlrModulator/CtrlrModulator.h"
#include "CtrlrIDs.h"
#include "CtrlrPanel/CtrlrPanel.h"

CtrlrToggleButton::CtrlrToggleButton (CtrlrModulator &owner)
    : CtrlrComponent(owner),
      ctrlrButton (0)
{
	valueMap = new CtrlrValueMap();
    addAndMakeVisible (ctrlrButton = new ToggleButton ("ctrlrButton"));
    ctrlrButton->setButtonText ("Button");
    ctrlrButton->addListener (this);
	ctrlrButton->setBufferedToImage (true);
	setProperty (Ids::uiButtonTextColourOn, "0xff000000");
	setProperty (Ids::uiToggleButtonFocusOutline, "0x00000000");
	setProperty (Ids::uiToggleButtonText, "Button");
	setProperty (Ids::uiButtonTrueValue, 1);
	setProperty (Ids::uiButtonFalseValue, 0);
	setProperty (Ids::uiButtonColourOff, "0xff0000ff");
	owner.setProperty (Ids::modulatorMax, 1);
	owner.setProperty (Ids::modulatorMin, 0);

    setSize (88, 32);
}

CtrlrToggleButton::~CtrlrToggleButton()
{
    deleteAndZero (ctrlrButton);
}

void CtrlrToggleButton::paint (Graphics& g)
{
}

void CtrlrToggleButton::resized()
{
    ctrlrButton->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
}

void CtrlrToggleButton::buttonClicked (Button* buttonThatWasClicked)
{
    if (isInternal())
	{
		owner.getOwnerPanel().performInternalComponentFunction(this);
		return;
	}

	if (!owner.getOwnerPanel().checkRadioGroup(this, buttonThatWasClicked->getToggleState()))
		return;

    if (buttonThatWasClicked == ctrlrButton)
    {
		setComponentValue (ctrlrButton->getToggleState(), true);
    }
}

void CtrlrToggleButton::mouseDown (const MouseEvent& e)
{
    CtrlrComponent::mouseDown(e);
}

void CtrlrToggleButton::setComponentValue (const double newValue, const bool sendChangeMessage)
{
	if (!owner.getOwnerPanel().checkRadioGroup(this, ctrlrButton->getToggleState()))
		return;

	if (ctrlrButton->getClickingTogglesState())
	{
		ctrlrButton->setToggleState (newValue ? true : false, dontSendNotification);
	}

	if (sendChangeMessage)
	{
		owner.getProcessor().setValueGeneric (CtrlrModulatorValue(newValue, CtrlrModulatorValue::changedByGUI), true);
	}
}

void CtrlrToggleButton::setComponentMidiValue (const int newValue, const bool sendChangeMessage)
{
	if (!owner.getOwnerPanel().checkRadioGroup(this, ctrlrButton->getToggleState()))
		return;

	if (ctrlrButton->getClickingTogglesState())
	{
		ctrlrButton->setToggleState (valueMap->getIndexForValue(newValue) ? true : false, dontSendNotification);
	}

	if (sendChangeMessage)
	{
		owner.getProcessor().setValueGeneric (CtrlrModulatorValue(newValue, CtrlrModulatorValue::changedByGUI), true);
	}
}

double CtrlrToggleButton::getComponentMaxValue()
{
	return (1);
}

bool CtrlrToggleButton::getToggleState()
{
	return (ctrlrButton->getToggleState());
}

double CtrlrToggleButton::getComponentValue()
{
	if (ctrlrButton->getToggleState())
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

int CtrlrToggleButton::getComponentMidiValue()
{
	return (valueMap->getMappedValue(ctrlrButton->getToggleState()));
}

void CtrlrToggleButton::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (property == Ids::componentRadioGroupId)
	{
		ctrlrButton->setToggleState (false, dontSendNotification);
	}

	if (property == Ids::uiButtonTextColourOn
		|| property == Ids::uiButtonColourOff)
	{
		ctrlrButton->setColour (ToggleButton::textColourId, VAR2COLOUR(getProperty(Ids::uiButtonTextColourOn)));
		ctrlrButton->setColour (TextButton::buttonColourId, VAR2COLOUR(getProperty(Ids::uiButtonColourOff)));
	}
	else if (property == Ids::uiToggleButtonText)
	{
		ctrlrButton->setButtonText (getProperty(Ids::uiToggleButtonText));
	}
	else if (property == Ids::uiButtonTrueValue || property == Ids::uiButtonFalseValue)
	{
		valueMap->setPair (0, getProperty(Ids::uiButtonFalseValue), "");
		valueMap->setPair (1, getProperty(Ids::uiButtonTrueValue), "");
		owner.getProcessor().setValueMap (*valueMap);
	}
	else if (property == Ids::uiToggleButtonFocusOutline)
    {
        ctrlrButton->setColour (TextEditor::focusedOutlineColourId, VAR2COLOUR(getProperty(Ids::uiToggleButtonFocusOutline)));
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

void CtrlrToggleButton::click()
{
	ctrlrButton->triggerClick();
}

bool CtrlrToggleButton::isToggleButton()
{
	return (true);
}

void CtrlrToggleButton::setToggleState(const bool toggleState, const bool sendChangeMessage)
{
	ctrlrButton->setToggleState (toggleState, sendChangeMessage ? sendNotification : dontSendNotification);
}