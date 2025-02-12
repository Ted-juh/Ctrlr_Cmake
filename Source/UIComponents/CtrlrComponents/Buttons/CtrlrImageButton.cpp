#include "stdafx.h"
#include "CtrlrImageButton.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrCustomButtonInternal.h"
#include "CtrlrPanel/CtrlrPanelResource.h"

CtrlrImageButton::CtrlrImageButton (CtrlrModulator &owner)
    : CtrlrComponent(owner),
      ctrlrButton (0)
{
	valueMap = new CtrlrValueMap();
    addAndMakeVisible (ctrlrButton = new CtrlrCustomButtonInternal (*this));

	setBufferedToImage (true);
	ctrlrButton->addListener (this);
	setProperty (Ids::uiImageButtonMode, 0);
	setProperty (Ids::uiImageButtonResource, "");
	setProperty (Ids::resourceImageWidth, 32);
	setProperty (Ids::resourceImageHeight, 32);
	setProperty (Ids::resourceImagePaintMode, 36);
	setProperty (Ids::resourceImageOrientation, 1);
	setProperty (Ids::uiImageButtonTextColour, "0xff000000");
	setProperty (Ids::uiImageButtonContent, "");
	setProperty (Ids::uiImageButtonTextPosition, 4);
	setProperty (Ids::uiImageButtonTextWidth, 0);
	setProperty (Ids::uiImageButtonTextHeight, 32);
	setProperty (Ids::uiButtonTextFont, Font(12).toString());
	setProperty (Ids::uiButtonTextJustification, "centred");
	setProperty (Ids::uiImageButtonTextPosition, "bottom");
	setProperty (Ids::uiImageButtonContent, "False\nTrue");
	setProperty (Ids::uiButtonRepeat, false);
	setProperty (Ids::uiButtonRepeatRate, 100);

    setSize (96, 32);
}

CtrlrImageButton::~CtrlrImageButton()
{
    deleteAndZero (ctrlrButton);
}

void CtrlrImageButton::paint (Graphics& g)
{
}

void CtrlrImageButton::resized()
{
    ctrlrButton->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
	ctrlrButton->setBounds (getUsableRect());
}

void CtrlrImageButton::timerCallback()
{
	if (ctrlrButton->isMouseButtonDown())
	{
		ctrlrButton->triggerClick();
	}
	else
	{
		stopTimer();
	}
}

void CtrlrImageButton::mouseDown (const MouseEvent& e)
{
	if (e.eventComponent == ctrlrButton)
	{
		if (!isTimerRunning())
		{
			startTimer ((int)getProperty(Ids::uiButtonRepeatRate));
		}
	}
	CtrlrComponent::mouseDown(e);
}

double CtrlrImageButton::getComponentMaxValue()
{
	return (valueMap->getNonMappedMax());
}

double CtrlrImageButton::getComponentValue()
{
	return (valueMap->getCurrentNonMappedValue());
}

const String CtrlrImageButton::getComponentText()
{
	return (ctrlrButton->getButtonText());
}

void CtrlrImageButton::setComponentValue (const double newValue, const bool sendChangeMessage)
{
	if (!owner.getOwnerPanel().checkRadioGroup(this, ctrlrButton->getToggleState()))
		return;

	valueMap->setCurrentNonMappedValue (newValue);

	ctrlrButton->setButtonText (valueMap->getCurrentText());

	if (ctrlrButton->getClickingTogglesState())
	{
		ctrlrButton->setToggleState (newValue ? true : false, dontSendNotification);
		ctrlrButton->setButtonText (valueMap->getTextForIndex(newValue));
	}

	if (sendChangeMessage)
	{
		owner.getProcessor().setValueGeneric (CtrlrModulatorValue(newValue,CtrlrModulatorValue::changedByGUI), sendChangeMessage);
	}
}

void CtrlrImageButton::setComponentMidiValue (const int newValue, const bool sendChangeMessage)
{
	if (!owner.getOwnerPanel().checkRadioGroup(this, ctrlrButton->getToggleState()))
		return;

	valueMap->setCurrentMappedValue (newValue);

	ctrlrButton->setButtonText (valueMap->getCurrentText());

	if (ctrlrButton->getClickingTogglesState())
	{
		ctrlrButton->setToggleState (newValue ? true : false, dontSendNotification);
		ctrlrButton->setButtonText (valueMap->getTextForIndex(newValue));
	}

	if (sendChangeMessage)
	{
		owner.getProcessor().setValueGeneric (CtrlrModulatorValue (newValue, CtrlrModulatorValue::changedByGUI), sendChangeMessage);
	}
}

int CtrlrImageButton::getComponentMidiValue()
{
	return (valueMap->getCurrentMappedValue());
}

void CtrlrImageButton::buttonContentChanged()
{
	valueMap->copyFrom (owner.getProcessor().setValueMap (getProperty(Ids::uiImageButtonContent)));
}

void CtrlrImageButton::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (property == Ids::componentRadioGroupId)
	{
		ctrlrButton->setToggleState (false, dontSendNotification);
	}

	if (property == Ids::uiImageButtonContent)
	{
		buttonContentChanged();
	}

	else if (property == Ids::uiImageButtonResource
		|| property == Ids::resourceImageWidth
		|| property == Ids::resourceImageHeight
		|| property == Ids::resourceImagePaintMode
		|| property == Ids::resourceImageOrientation)
	{
		setResource();
		ctrlrButton->setOrientation ((bool)getProperty(Ids::resourceImageOrientation));
		ctrlrButton->setImage (filmStripImage, (int)getProperty(Ids::resourceImageWidth), (int)getProperty(Ids::resourceImageHeight));
		ctrlrButton->setPaintMode ((RectanglePlacement)(int)getProperty(Ids::resourceImagePaintMode));
		ctrlrButton->repaint();
	}

	else if (property == Ids::uiButtonTextFont
		|| property == Ids::uiImageButtonTextColour
		|| property == Ids::uiImageButtonTextPosition
		|| property == Ids::resourceImageWidth
		|| property == Ids::resourceImageHeight
		|| property == Ids::uiButtonTextJustification
		|| property == Ids::uiImageButtonTextWidth
		|| property == Ids::uiImageButtonTextHeight)
	{
		ctrlrButton->repaint();
	}

	else if (property == Ids::uiImageButtonMode)
	{
		buttonModeChanged((ImageButtonMode)(int)getProperty(property));
	}
	else if (property == Ids::uiButtonRepeat)
	{
		if ((bool)getProperty(property) == true)
		{
			ctrlrButton->addMouseListener (this, false);
		}
		else
		{
			ctrlrButton->removeMouseListener (this);
			stopTimer();
		}
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

const Array<Font> CtrlrImageButton::getFontList()
{
	Array <Font> ret;
	Font f = STR2FONT(getProperty(Ids::uiButtonTextFont));
	if (f.getTypefaceName() != Font::getDefaultSerifFontName()
		&& f.getTypefaceName() != Font::getDefaultSansSerifFontName()
		&& f.getTypefaceName() != Font::getDefaultMonospacedFontName()
		&& f.getTypefaceName() != "<Sans-Serif>")
	{
		ret.add (f);
	}
	return (ret);
}

void CtrlrImageButton::buttonModeChanged(const ImageButtonMode newMode)
{
	switch (newMode)
	{
		case Normal:
			if (valueMap->getNumValues() == 2)
			{
				ctrlrButton->setClickingTogglesState(true);
			}
			else
				ctrlrButton->setClickingTogglesState(false);
			break;

		case Momentary:
		case MomentaryMouseOver:
		case NormalMouseOver:
			ctrlrButton->setClickingTogglesState(false);
			break;

		default:
			break;
	}
}

const CtrlrImageButton::ImageButtonMode CtrlrImageButton::getButtonMode()
{
	return ((ImageButtonMode)(int)getProperty(Ids::uiImageButtonMode));
}

void CtrlrImageButton::click()
{
	ctrlrButton->triggerClick();
}

bool CtrlrImageButton::isToggleButton()
{
	return (ctrlrButton->getClickingTogglesState());
}

void CtrlrImageButton::setToggleState(const bool toggleState, const bool sendChangeMessage)
{
	ctrlrButton->setToggleState (toggleState, sendChangeMessage ? sendNotification : dontSendNotification);
}

bool CtrlrImageButton::getToggleState()
{
	return (ctrlrButton->getToggleState());
}

void CtrlrImageButton::buttonClicked (Button* button)
{
	if (isInternal())
	{
		owner.getOwnerPanel().performInternalComponentFunction(this);
		return;
	}

	if (!owner.getOwnerPanel().checkRadioGroup(this, button->getToggleState()))
		return;

	if (button == ctrlrButton)
	{
		valueMap->increment();
		ctrlrButton->setButtonText (valueMap->getCurrentText());
		setComponentValue (valueMap->getCurrentNonMappedValue(), true);
	}
}

void CtrlrImageButton::setResource()
{
	filmStripImage = owner.getOwnerPanel().getResourceManager().getResourceAsImage (getProperty(Ids::uiImageButtonResource));
	lookAndFeelChanged();
	repaint();
	resized();
}

void CtrlrImageButton::reloadResources(Array <CtrlrPanelResource*> resourcesThatChanged)
{
	for (int i=0; i<resourcesThatChanged.size(); i++)
	{
		if (resourcesThatChanged[i]->getName() == getProperty(Ids::uiImageButtonResource).toString())
		{
			setResource();
		}
	}
}