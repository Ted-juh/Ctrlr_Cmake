#include "stdafx.h"
#include "CtrlrImageSlider.h"
#include "CtrlrComponents/CtrlrFilmStripPainter.h"
#include "CtrlrPanel/CtrlrPanelResource.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"

CtrlrImageSlider::CtrlrImageSlider (CtrlrModulator &owner)
    : CtrlrComponent(owner),
      ctrlrSlider (0)
{
	lf = new CtrlrImageSliderLF(*this);
    addAndMakeVisible (ctrlrSlider = new CtrlrSliderInternal (*this));
    ctrlrSlider->setRange (0, 10, 0);
    ctrlrSlider->setSliderStyle (Slider::LinearHorizontal);
    ctrlrSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    ctrlrSlider->addListener (this);


    //[UserPreSize]
	ctrlrSlider->setSliderStyle (Slider::RotaryVerticalDrag);
	ctrlrSlider->setLookAndFeel (lf);
	setProperty (Ids::uiSliderStyle, "RotaryVerticalDrag");
	setProperty (Ids::uiImageSliderResource, COMBO_ITEM_NONE);
	setProperty (Ids::resourceImageWidth, 32);
	setProperty (Ids::resourceImageHeight, 32);
	setProperty (Ids::resourceImagePaintMode, 36);
	setProperty (Ids::resourceImageOrientation, 1);
	setProperty (Ids::uiSliderMin, 0);
	setProperty (Ids::uiSliderMax, 127);
	setProperty (Ids::uiSliderInterval, 1);
	setProperty (Ids::uiSliderDoubleClickEnabled, true);
	setProperty (Ids::uiSliderDoubleClickValue, 0);
	setProperty (Ids::uiSliderValuePosition, (int)Slider::TextBoxBelow);
	setProperty (Ids::uiSliderValueHeight, 12);
	setProperty (Ids::uiSliderValueWidth, 64);
	setProperty (Ids::uiSliderValueTextColour, "0xff000000");
	setProperty (Ids::uiSliderValueBgColour, "0xffffffff");
	setProperty (Ids::uiSliderValueFont, FONT2STR (Font(12)));
	setProperty (Ids::uiSliderValueTextJustification, "centred");
	setProperty (Ids::uiSliderValueHighlightColour, "0xff0000ff");
	setProperty (Ids::uiSliderValueOutlineColour, "0xffffffff");
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

CtrlrImageSlider::~CtrlrImageSlider()
{
    deleteAndZero (ctrlrSlider);
}

void CtrlrImageSlider::paint (Graphics& g)
{
}

void CtrlrImageSlider::resized()
{
	if (restoreStateInProgress)
		return;
	ctrlrSlider->setBounds (getUsableRect());
}

void CtrlrImageSlider::sliderValueChanged (Slider* sliderThatWasMoved)
{
    if (sliderThatWasMoved == ctrlrSlider)
    {
		setComponentValue ((int)ctrlrSlider->getValue(), true);
    }
}

void CtrlrImageSlider::mouseUp (const MouseEvent& e)
{
	if ((bool)getProperty(Ids::uiSliderSpringMode) == true)
	{
		ctrlrSlider->setValue ((double)getProperty(Ids::uiSliderSpringValue), sendNotificationSync);
	}
}

double CtrlrImageSlider::getComponentMaxValue()
{
	return ((int)ctrlrSlider->getMaximum());
}

double CtrlrImageSlider::getComponentValue()
{
	return ((int)ctrlrSlider->getValue());
}

int CtrlrImageSlider::getComponentMidiValue()
{
	return ((int)ctrlrSlider->getValue());
}

void CtrlrImageSlider::setComponentValue (const double newValue, const bool sendChangeMessage)
{
	ctrlrSlider->setValue (newValue, dontSendNotification);
	if (sendChangeMessage)
	{
		owner.getProcessor().setValueGeneric (CtrlrModulatorValue(newValue,CtrlrModulatorValue::changedByGUI));
	}
}

void CtrlrImageSlider::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (property == Ids::uiImageSliderResource)
	{
		setResource();
	}
	else if (property == Ids::resourceImageWidth)
	{
		lf->setImage (filmStripImage, (int)getProperty(Ids::resourceImageWidth), (int)getProperty(Ids::resourceImageHeight));
	}
	else if (property == Ids::resourceImageHeight)
	{
		lf->setImage (filmStripImage, (int)getProperty(Ids::resourceImageWidth), (int)getProperty(Ids::resourceImageHeight));
	}
	else if (property == Ids::resourceImagePaintMode)
	{
		lf->setPaintMode ((RectanglePlacement)(int)getProperty(Ids::resourceImagePaintMode));
	}
	else if (property == Ids::resourceImageOrientation)
	{
		lf->setOrientation((bool)getProperty(Ids::resourceImageOrientation));
	}
	else if (property == Ids::uiSliderInterval || property == Ids::uiSliderMax || property == Ids::uiSliderMin)
	{
		ctrlrSlider->setRange ( getProperty (Ids::uiSliderMin), getProperty (Ids::uiSliderMax), getProperty (Ids::uiSliderInterval) );
		owner.setProperty (Ids::modulatorMax, ctrlrSlider->getMaximum());
		owner.setProperty (Ids::modulatorMin, ctrlrSlider->getMinimum());
	}
	else if (property == Ids::uiSliderValueTextColour)
	{
		ctrlrSlider->setColour (Slider::textBoxTextColourId, VAR2COLOUR(getProperty (Ids::uiSliderValueTextColour)) );
	}
	else if (property == Ids::uiSliderValueBgColour)
	{
		ctrlrSlider->setColour (Slider::textBoxBackgroundColourId, VAR2COLOUR(getProperty (Ids::uiSliderValueBgColour)) );
	}
	else if (property == Ids::uiSliderValueHighlightColour)
	{
		ctrlrSlider->setColour (Slider::textBoxHighlightColourId, VAR2COLOUR(getProperty (Ids::uiSliderValueOutlineColour)) );
	}
	else if (property == Ids::uiSliderValueOutlineColour)
	{
		ctrlrSlider->setColour (Slider::textBoxOutlineColourId, VAR2COLOUR(getProperty (Ids::uiSliderValueOutlineColour)) );
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
		lf->setOrientation((bool)getProperty(Ids::resourceImageOrientation));
		lf->setImage (filmStripImage, (int)getProperty(Ids::resourceImageWidth), (int)getProperty(Ids::resourceImageHeight));
		lookAndFeelChanged();
	}

	else if (property == Ids::uiSliderStyle)
	{
		ctrlrSlider->setSliderStyle ((Slider::SliderStyle)CtrlrComponentTypeManager::sliderStringToStyle (getProperty (Ids::uiSliderStyle)));
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

const String CtrlrImageSlider::getComponentText()
{
	return (String(getComponentValue()));
}

void CtrlrImageSlider::setResource()
{
	filmStripImage = owner.getOwnerPanel().getResourceManager().getResourceAsImage (getProperty(Ids::uiImageSliderResource));
	lf->setImage (filmStripImage, (int)getProperty(Ids::resourceImageWidth), (int)getProperty(Ids::resourceImageHeight));
	lookAndFeelChanged();
	repaint();
	resized();
}

void CtrlrImageSlider::reloadResources(Array <CtrlrPanelResource*> resourcesThatChanged)
{
	for (int i=0; i<resourcesThatChanged.size(); i++)
	{
		if (resourcesThatChanged[i]->getName() == getProperty(Ids::uiImageSliderResource).toString())
		{
			setResource();
		}
	}
}