#include "stdafx.h"
#include "../../CtrlrPanel/CtrlrPanelEditor.h"
#include "../CtrlrComponentTypeManager.h"
#include "CtrlrUtilitiesGUI.h"
#include "CtrlrHyperlink.h"

CtrlrHyperlink::CtrlrHyperlink (CtrlrModulator &owner)
    : CtrlrComponent(owner),
      hyperlinkButton (0)
{
    addAndMakeVisible (hyperlinkButton = new HyperlinkButton ("http://ctrlr.org",
                                                              URL ("http://ctrlr.org")));
    hyperlinkButton->setTooltip ("http://ctrlr.org");
    hyperlinkButton->setButtonText ("http://ctrlr.org");
    hyperlinkButton->addListener (this);

    setProperty (Ids::uiButtonContent, "False\nTrue");
	setProperty (Ids::uiHyperlinkColour, "0xff0000ff");
	setProperty (Ids::uiHyperlinkFont, Font (14, Font::underlined).toString());
	setProperty (Ids::uiHyperlinkFitTextToSize, true);
	setProperty (Ids::uiHyperlinkTextJustification, "centred");
	setProperty (Ids::uiHyperlinkOpensUrl, true);

    setSize (128, 48);
}

CtrlrHyperlink::~CtrlrHyperlink()
{
    deleteAndZero (hyperlinkButton);
}

void CtrlrHyperlink::paint (Graphics& g)
{
}

void CtrlrHyperlink::resized()
{
    hyperlinkButton->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
	hyperlinkButton->setBounds (getUsableRect());
}

void CtrlrHyperlink::buttonClicked (Button* buttonThatWasClicked)
{
    if (isInternal())
	{
		owner.getOwnerPanel().performInternalComponentFunction(this);
		return;
	}

    if (!owner.getOwnerPanel().checkRadioGroup(this, buttonThatWasClicked->getToggleState()))
		return;

    if (buttonThatWasClicked == hyperlinkButton)
    {
		valueMap.increment();
		hyperlinkButton->setButtonText (valueMap.getCurrentText());
		setComponentValue (valueMap.getCurrentNonMappedValue(), true);
    }
}

void CtrlrHyperlink::setComponentValue (const double newValue, const bool sendChangeMessage)
{
    valueMap.setCurrentNonMappedValue (newValue);
	hyperlinkButton->setButtonText (valueMap.getTextForIndex (newValue));

	if (sendChangeMessage)
	{
		owner.getProcessor().setValueGeneric (CtrlrModulatorValue(newValue,CtrlrModulatorValue::changedByGUI), sendChangeMessage);
	}
}

double CtrlrHyperlink::getComponentValue()
{
	return (valueMap.getCurrentNonMappedValue());
}

int CtrlrHyperlink::getComponentMidiValue()
{
	return (valueMap.getCurrentMappedValue());
}

double CtrlrHyperlink::getComponentMaxValue()
{
	return (valueMap.getNonMappedMax());
}

const String CtrlrHyperlink::getComponentText()
{
	return (hyperlinkButton->getButtonText());
}

void CtrlrHyperlink::setComponentText (const String &componentText)
{
	setComponentValue (valueMap.getNonMappedValue(componentText));
}

void CtrlrHyperlink::buttonContentChanged()
{
	const String buttonContent = getProperty(Ids::uiButtonContent);
	valueMap.copyFrom (owner.getProcessor().setValueMap (buttonContent));
	setComponentValue (0, false);
}

bool CtrlrHyperlink::hyperlinkOpensUrl()
{
	return getProperty(Ids::uiHyperlinkOpensUrl);
}

void CtrlrHyperlink::setHyperlinkUrl(const String& newURL)
{
	hyperlinkButton->setURL(URL(newURL));
	hyperlinkButton->setTooltip(newURL);
}

void CtrlrHyperlink::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
    if (property == Ids::uiButtonContent)
	{
		buttonContentChanged();
	}
	else if (property == Ids::uiHyperlinkColour)
	{
		hyperlinkButton->setColour (HyperlinkButton::textColourId, VAR2COLOUR(getProperty(property)));
	}
	else if (property == Ids::uiHyperlinkOpensUrl)
    {
		setHyperlinkUrl(hyperlinkOpensUrl() ? getProperty(Ids::uiHyperlinkUrl).toString() : "");
    }
	else if (property == Ids::uiHyperlinkUrl)
	{
		if (hyperlinkOpensUrl()) {
			setHyperlinkUrl(getProperty(Ids::uiHyperlinkUrl));
		}
	}
	else if (property == Ids::uiHyperlinkFont
		|| property == Ids::uiHyperlinkFitTextToSize
		|| property == Ids::uiHyperlinkTextJustification)
	{
		hyperlinkButton->setFont (STR2FONT(getProperty(Ids::uiHyperlinkFont)), getProperty(Ids::uiHyperlinkFitTextToSize), justificationFromProperty(getProperty(Ids::uiHyperlinkTextJustification)));
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