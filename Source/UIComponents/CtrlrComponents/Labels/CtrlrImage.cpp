#include "stdafx.h"
#include "CtrlrImage.h"
#include "CtrlrProcessor.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrPanel/CtrlrPanelResource.h"

CtrlrImage::CtrlrImage (CtrlrModulator &owner)
    : CtrlrComponent(owner)
{
	owner.setProperty (Ids::modulatorIsStatic, true);
	owner.setProperty (Ids::modulatorVstExported, false);
	setProperty (Ids::uiImageResource, "");
	componentTree.addListener (this);

	setSize (128, 128);
}

CtrlrImage::~CtrlrImage()
{}

void CtrlrImage::paint (Graphics& g)
{
	if (!currentImage.isValid())
	{
		g.setColour (Colours::red);
		g.setFont (Font (15.0000f, Font::bold));
		g.drawFittedText ("Invalid Resource", 0, 0, getWidth(), getHeight(), Justification::left, 2);
	}
	else
	{
		const Rectangle<int> r = getUsableRect();
		g.drawImage(currentImage, r.getX(), r.getY(), r.getWidth(), r.getHeight(), 0, 0, currentImage.getWidth(), currentImage.getHeight(), false);
	}

	CtrlrComponent::resized();
	CtrlrComponent::paint (g);
}

void CtrlrImage::resized()
{
	if (restoreStateInProgress)
		return;
}

double CtrlrImage::getComponentMaxValue()
{
	return (1);
}

double CtrlrImage::getComponentValue()
{
	return (1);
}

int CtrlrImage::getComponentMidiValue()
{
	return (1);
}

void CtrlrImage::setComponentValue (const double newValue, const bool sendChangeMessage)
{
}

void CtrlrImage::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (property == Ids::uiImageResource)
	{
		setResource();
	}

	CtrlrComponent::valueTreePropertyChanged(treeWhosePropertyHasChanged, property);
	if (restoreStateInProgress == false)
	{
		resized();
	}
}

void CtrlrImage::resetSize()
{
	setSize (currentImage.getWidth(), currentImage.getHeight());
}

void CtrlrImage::restoreState (const ValueTree &savedState)
{
	CtrlrComponent::restoreState(savedState);
}

void CtrlrImage::setResource()
{
	currentImage = owner.getOwnerPanel().getResourceManager().getResourceAsImage (getProperty(Ids::uiImageResource));
	repaint();
	resized();
}

void CtrlrImage::reloadResources(Array <CtrlrPanelResource*> resourcesThatChanged)
{
	for (int i=0; i<resourcesThatChanged.size(); i++)
	{
		if (resourcesThatChanged[i]->getName() == getProperty(Ids::uiImageResource).toString())
		{
			setResource();
		}
	}
}