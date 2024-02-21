#include "stdafx.h"
#include "CtrlrArrow.h"
#include "CtrlrModulator/CtrlrModulator.h"

CtrlrArrow::CtrlrArrow (CtrlrModulator &owner)
    : CtrlrComponent(owner)
{
	owner.setProperty (Ids::modulatorIsStatic, true);
	owner.setProperty (Ids::modulatorVstExported, false);
	setProperty (Ids::uiArrowColour, "0xff000000");
	setProperty (Ids::uiArrowLineThickness, 2);
	setProperty (Ids::uiArrowHeadWidth, 8);
	setProperty (Ids::uiArrowHeadHeight, 16);
	setProperty (Ids::uiArrowOrientation, 0);
	setProperty (Ids::uiArrowRotation, 0);
	setProperty (Ids::uiArrowStokeThickness, 1);
	componentTree.addListener (this);
    setSize (32, 96);
}

CtrlrArrow::~CtrlrArrow()
{
	componentTree.removeListener (this);
}

void CtrlrArrow::paint (Graphics& g)
{
	const int orientation	= getProperty(Ids::uiArrowOrientation);
	const int thick			= getProperty(Ids::uiArrowStokeThickness);

	g.setColour (VAR2COLOUR(getProperty (Ids::uiArrowColour)));
	Path arrowPath;

	switch (orientation)
	{
		case 0: /* points top */
			arrowPath.addArrow (Line<float>(getWidth()/2.0f, (float)getHeight()-thick, getWidth()/2.0f, (float)thick), getProperty(Ids::uiArrowLineThickness), getProperty(Ids::uiArrowHeadWidth), getProperty(Ids::uiArrowHeadHeight));
			break;

		case 1: /* points down */
			arrowPath.addArrow (Line<float>(getWidth()/2.0f, (float)thick, getWidth()/2.0f, (float)getHeight()-thick), getProperty(Ids::uiArrowLineThickness), getProperty(Ids::uiArrowHeadWidth), getProperty(Ids::uiArrowHeadHeight));
			break;

		case 2: /* points left */
			arrowPath.addArrow (Line<float>((float)getWidth()-thick, (float)getHeight()/2.0f, (float)thick, (float)getHeight()/2.0f), getProperty(Ids::uiArrowLineThickness), getProperty(Ids::uiArrowHeadWidth), getProperty(Ids::uiArrowHeadHeight));
			break;

		case 3: /* points right */
			arrowPath.addArrow (Line<float>((float)thick, (float)getHeight()/2.0f, (float)getWidth()-thick, (float)getHeight()/2.0f), getProperty(Ids::uiArrowLineThickness), getProperty(Ids::uiArrowHeadWidth), getProperty(Ids::uiArrowHeadHeight));
			break;

		default:
			break;
	}

	g.strokePath (arrowPath, PathStrokeType(getProperty(Ids::uiArrowStokeThickness)), AffineTransform::rotation ((float)getProperty(Ids::uiArrowRotation)*(float_Pi/180), getWidth()/2.0f, getHeight()/2.0f));
}

void CtrlrArrow::resized()
{
	CtrlrComponent::resized();
}

void CtrlrArrow::setComponentValue (const double newValue, const bool sendChangeMessage)
{
}

double CtrlrArrow::getComponentValue()
{
	return (1);
}

int CtrlrArrow::getComponentMidiValue()
{
	return (1);
}

double CtrlrArrow::getComponentMaxValue()
{
	return (1);
}

void CtrlrArrow::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	CtrlrComponent::valueTreePropertyChanged(treeWhosePropertyHasChanged, property);
	resized();
	repaint();
}

void CtrlrArrow::restoreState (const ValueTree &savedState)
{
	CtrlrComponent::restoreState(savedState);
}