#include "stdafx.h"
#include "CtrlrXYSurface.h"
#include "../CtrlrComponentTypeManager.h"
#include "CtrlrUtilities.h"
#include "CtrlrUtilitiesGUI.h"
#include "CtrlrXYModulator.h"

CtrlrXYModulator::CtrlrXYModulator (CtrlrXYSurface &_owner)
    : owner(_owner)
{
    setSize (32, 32);
}

CtrlrXYModulator::~CtrlrXYModulator()
{
}

void CtrlrXYModulator::paint (Graphics& g)
{
	const float outline = (float)owner.getProperty(Ids::uiXYSurfaceModulatorOutlineThickness)/2.0f;

	gradientFromProperty (g, getBounds(), owner.getObjectTree(), Ids::uiXYSurfaceModulatorBgGradientType, Ids::uiXYSurfaceModulatorBgColour1, Ids::uiXYSurfaceModulatorBgColour2);
    g.fillEllipse (outline, outline, (float) (getWidth() - outline*2), (float) (getHeight() - outline*2));

	gradientFromProperty (g, getBounds(), owner.getObjectTree(), Ids::uiXYSurfaceModulatorOutlineGradientType, Ids::uiXYSurfaceModulatorOutlineColour1, Ids::uiXYSurfaceModulatorOutlineColour2);
    g.drawEllipse (outline, outline, (float) (getWidth() - outline*2), (float) (getHeight() - outline*2), owner.getProperty(Ids::uiXYSurfaceModulatorOutlineThickness));
}

void CtrlrXYModulator::resized()
{
}

void CtrlrXYModulator::moved()
{
	owner.modulatorMoved();
}

void CtrlrXYModulator::mouseEnter (const MouseEvent& e)
{
	setMouseCursor (MouseCursor::PointingHandCursor);
}

void CtrlrXYModulator::mouseExit (const MouseEvent& e)
{
}

void CtrlrXYModulator::mouseDown (const MouseEvent& e)
{
	if (e.mods.isPopupMenu())
	{
		return;
	}
	dragger.startDraggingComponent (this, e);
}

void CtrlrXYModulator::mouseDrag (const MouseEvent& e)
{
    //[UserCode_mouseDrag] -- Add your code here...
	if (e.mods.isPopupMenu())
	{
		return;
	}

	MouseEvent er = e.getEventRelativeTo (&owner);

	if (er.x > 0 && er.x < owner.getWidth() && er.y > 0 && er.y < owner.getHeight())
	{
		dragger.dragComponent (this, e, 0);
		owner.modulatorMoved();
	}
}