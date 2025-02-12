#include "stdafx.h"
#include "CtrlrFixedImageSlider.h"
#include "CtrlrComponents/CtrlrFilmStripPainter.h"
#include "CtrlrSliderInternal.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"
#include "CtrlrPanel/CtrlrPanelResource.h"

CtrlrFixedImageSlider::CtrlrFixedImageSlider (CtrlrModulator &owner)
    : CtrlrComponent(owner),
      ctrlrSlider (0)
{
	valueMap = new CtrlrValueMap();
	lf = new CtrlrImageSliderLF(*this);
    addAndMakeVisible (ctrlrSlider = new CtrlrSliderInternal (*this));
    ctrlrSlider->setName ("ctrlrSlider");
	ctrlrSlider->addListener (this);
	ctrlrSlider->setLookAndFeel(lf);
	componentTree.addListener (this);
	setProperty (Ids::uiImageSliderResource, "");
	setProperty (Ids::resourceImageWidth, 32);
	setProperty (Ids::resourceImageHeight, 32);
	setProperty (Ids::resourceImagePaintMode, 36);
	setProperty (Ids::resourceImageOrientation, 1);
	setProperty (Ids::uiSliderStyle, "RotaryVerticalDrag");
	setProperty (Ids::uiSliderMin, 0);
	setProperty (Ids::uiSliderMax, 1);
	setProperty (Ids::uiSliderInterval, 1);
	setProperty (Ids::uiSliderDoubleClickEnabled, true);
	setProperty (Ids::uiSliderDoubleClickValue, 0);
	setProperty (Ids::uiSliderValueHeight, 12);
	setProperty (Ids::uiSliderValuePosition, (int)Slider::TextBoxBelow);
	setProperty (Ids::uiSliderValueWidth, 64);
	setProperty (Ids::uiSliderValueTextColour, "0xff000000");
	setProperty (Ids::uiSliderValueBgColour, "0xffffffff");
	setProperty (Ids::uiSliderRotaryOutlineColour, "0xff0000ff");
	setProperty (Ids::uiSliderRotaryFillColour, "0xff0000ff");
	setProperty (Ids::uiSliderThumbColour, "0xffff0000");
	setProperty (Ids::uiSliderValueHighlightColour, "0xff0000ff");
	setProperty (Ids::uiSliderValueOutlineColour, "0xffffffff");
	setProperty (Ids::uiSliderTrackColour, "0xff0f0f0f");
	setProperty (Ids::uiFixedSliderContent, "");
	setProperty (Ids::uiSliderValueFont, FONT2STR (Font(12)));
	setProperty (Ids::uiSliderIncDecButtonColour, "0xff0000ff");
	setProperty (Ids::uiSliderIncDecTextColour, "0xffffffff");
	setProperty (Ids::uiSliderValueTextJustification, "centred");
	setProperty (Ids::uiSliderVelocitySensitivity, 1.0);
	setProperty (Ids::uiSliderVelocityThreshold, 1);
	setProperty (Ids::uiSliderVelocityOffset, 0.0);
	setProperty (Ids::uiSliderVelocityMode, false);
	setProperty (Ids::uiSliderVelocityModeKeyTrigger, true);
	setProperty (Ids::uiSliderSpringMode, false);
	setProperty (Ids::uiSliderSpringValue, 0);
	setProperty (Ids::uiSliderMouseWheelInterval, 1);
	setProperty (Ids::uiSliderPopupBubble, false);

    setSize (64, 64);
}

CtrlrFixedImageSlider::~CtrlrFixedImageSlider()
{
    deleteAndZero (ctrlrSlider);
}

void CtrlrFixedImageSlider::paint (Graphics& g)
{
}

void CtrlrFixedImageSlider::resized()
{
	if (restoreStateInProgress)
		return;
	ctrlrSlider->setBounds (getUsableRect());
}

void CtrlrFixedImageSlider::mouseUp (const MouseEvent& e)
{
	if ((bool)getProperty(Ids::uiSliderSpringMode) == true)
	{
		ctrlrSlider->setValue ((double)getProperty(Ids::uiSliderSpringValue), sendNotificationSync);
	}
}

double CtrlrFixedImageSlider::getComponentMaxValue()
{
	return (valueMap->getNonMappedMax());
}

double CtrlrFixedImageSlider::getComponentValue()
{
	return ((int)ctrlrSlider->getValue());
}

int CtrlrFixedImageSlider::getComponentMidiValue()
{
	return (valueMap->getMappedValue(ctrlrSlider->getValue()));

}
const String CtrlrFixedImageSlider::getComponentText()
{
	return (valueMap->getTextForIndex (ctrlrSlider->getValue()));
}

void CtrlrFixedImageSlider::setComponentValue (const double newValue, const bool sendChangeMessage)
{
	ctrlrSlider->setValue (newValue, dontSendNotification);
	if (sendChangeMessage)
	{
		owner.getProcessor().setValueGeneric (CtrlrModulatorValue(newValue,CtrlrModulatorValue::changedByGUI));
	}
}

void CtrlrFixedImageSlider::sliderContentChanged()
{
	valueMap->copyFrom (owner.getProcessor().setValueMap (getProperty(Ids::uiFixedSliderContent)));
	ctrlrSlider->setRange (valueMap->getNonMappedMin(), valueMap->getNonMappedMax(), 1);
}


void CtrlrFixedImageSlider::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (property == Ids::resourceImagePaintMode)
	{
		lf->setPaintMode ((RectanglePlacement)(int)getProperty(Ids::resourceImagePaintMode));
	}
	else if (property == Ids::resourceImageWidth)
	{
		lf->setImage (filmStripImage, (int)getProperty(Ids::resourceImageWidth), (int)getProperty(Ids::resourceImageHeight));
	}
	else if (property == Ids::resourceImageHeight)
	{
		lf->setImage (filmStripImage, (int)getProperty(Ids::resourceImageWidth), (int)getProperty(Ids::resourceImageHeight));
	}
	else if (property == Ids::resourceImageOrientation)
	{
		lf->setOrientation((bool)getProperty(Ids::resourceImageOrientation));
	}
	else if(property == Ids::uiImageSliderResource)
	{
		setResource();
	}
	else if (property == Ids::uiSliderStyle)
	{
		ctrlrSlider->setSliderStyle ((Slider::SliderStyle)CtrlrComponentTypeManager::sliderStringToStyle (getProperty (Ids::uiSliderStyle)));
	}
	else if (property == Ids::uiSliderRotaryFillColour)
	{
		ctrlrSlider->setColour (Slider::rotarySliderFillColourId, VAR2COLOUR(getProperty (Ids::uiSliderRotaryFillColour)) );
	}
	else if (property == Ids::uiSliderRotaryOutlineColour)
	{
		ctrlrSlider->setColour (Slider::rotarySliderOutlineColourId, VAR2COLOUR(getProperty (Ids::uiSliderRotaryOutlineColour)) );
	}
	else if (property == Ids::uiSliderValueTextColour)
	{
		ctrlrSlider->setColour (Slider::textBoxTextColourId, VAR2COLOUR(getProperty (Ids::uiSliderValueTextColour)) );
	}
	else if (property == Ids::uiSliderValueBgColour)
	{
		ctrlrSlider->setColour (Slider::textBoxBackgroundColourId, VAR2COLOUR(getProperty (Ids::uiSliderValueBgColour)));
	}
	else if (property == Ids::uiSliderThumbColour)
	{
		ctrlrSlider->setColour (Slider::thumbColourId, VAR2COLOUR(getProperty (Ids::uiSliderThumbColour)) );
	}
	else if (property == Ids::uiSliderValueOutlineColour)
	{
		ctrlrSlider->setColour (Slider::textBoxOutlineColourId, VAR2COLOUR(getProperty (Ids::uiSliderValueOutlineColour)) );
	}
	else if (property == Ids::uiSliderTrackColour)
	{
		ctrlrSlider->setColour (Slider::trackColourId, VAR2COLOUR(getProperty (Ids::uiSliderTrackColour)) );
	}
	else if (property == Ids::uiFixedSliderContent)
	{
		sliderContentChanged();
	}
	else if (property == Ids::uiSliderValuePosition || property == Ids::uiSliderValueHeight || property == Ids::uiSliderValueWidth)
	{
		ctrlrSlider->setTextBoxStyle (
			(Slider::TextEntryBoxPosition)(int)getProperty (Ids::uiSliderValuePosition),
			false,
			getProperty (Ids::uiSliderValueWidth, 64),
			getProperty (Ids::uiSliderValueHeight, 12));
	}

	else if (property == Ids::uiSliderIncDecButtonColour
		|| property == Ids::uiSliderIncDecTextColour
		|| property == Ids::uiSliderValueFont
		|| property == Ids::uiSliderValueTextJustification
		)
	{
		filmStripImage = owner.getOwnerPanel().getResourceManager().getResourceAsImage (getProperty(Ids::uiImageSliderResource));
		lf->setImage (filmStripImage, (int)getProperty(Ids::resourceImageWidth), (int)getProperty(Ids::resourceImageHeight));
		lf->setPaintMode ((RectanglePlacement)(int)getProperty(Ids::resourceImagePaintMode));
		ctrlrSlider->setLookAndFeel(0);
		ctrlrSlider->setLookAndFeel(lf);
	}

	else if (property == Ids::uiSliderVelocityMode
		|| property == Ids::uiSliderVelocityModeKeyTrigger
		|| property == Ids::uiSliderVelocitySensitivity
		|| property == Ids::uiSliderVelocityThreshold
		|| property == Ids::uiSliderVelocityOffset
		)
	{
		ctrlrSlider->setVelocityBasedMode((bool)getProperty(Ids::uiSliderVelocityMode));
		ctrlrSlider->setVelocityModeParameters ((double)getProperty(Ids::uiSliderVelocitySensitivity),
												(int)getProperty(Ids::uiSliderVelocityThreshold),
												(double)getProperty(Ids::uiSliderVelocityOffset),
												(bool)getProperty(Ids::uiSliderVelocityModeKeyTrigger));
	}

	else if (property == Ids::uiSliderSpringValue)
	{
		ctrlrSlider->setValue (getProperty(property), dontSendNotification);
	}
	else if (property == Ids::uiSliderDoubleClickValue
			|| property == Ids::uiSliderDoubleClickEnabled)
	{
		ctrlrSlider->setDoubleClickReturnValue ((bool)getProperty(Ids::uiSliderDoubleClickEnabled), getProperty(Ids::uiSliderDoubleClickValue));
	}
	else if (property == Ids::uiSliderSpringMode)
	{
		if ((bool)getProperty(property) == true)
		{
			ctrlrSlider->setValue (getProperty(Ids::uiSliderSpringValue), dontSendNotification);
		}
	}

	else if (property == Ids::uiSliderPopupBubble)
	{
		ctrlrSlider->setPopupDisplayEnabled ((bool)getProperty(property), (bool)getProperty(property), owner.getOwnerPanel().getEditor());
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

const String CtrlrFixedImageSlider::getTextForValue(const double value)
{
	return (valueMap->getTextForIndex(value));
}

void CtrlrFixedImageSlider::sliderValueChanged (Slider* sliderThatWasMoved)
{
	setComponentValue(ctrlrSlider->getValue(), true);
}

void CtrlrFixedImageSlider::setResource()
{
	filmStripImage = owner.getOwnerPanel().getResourceManager().getResourceAsImage (getProperty(Ids::uiImageSliderResource));
	lf->setImage (filmStripImage, (int)getProperty(Ids::resourceImageWidth), (int)getProperty(Ids::resourceImageHeight));
	lookAndFeelChanged();
	repaint();
	resized();
}

void CtrlrFixedImageSlider::reloadResources(Array <CtrlrPanelResource*> resourcesThatChanged)
{
	for (int i=0; i<resourcesThatChanged.size(); i++)
	{
		if (resourcesThatChanged[i]->getName() == getProperty(Ids::uiImageSliderResource).toString())
		{
			setResource();
		}
	}
}

Slider *CtrlrFixedImageSlider::getOwnedSlider()
{
	return (ctrlrSlider);
}