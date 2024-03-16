#include "stdafx.h"
#include "CtrlrImageButton.h"
#include "../CtrlrComponentTypeManager.h"
#include "CtrlrIDs.h"
#include "CtrlrUtilities.h"
#include "CtrlrUtilitiesGUI.h"
#include "CtrlrFontManager.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrCustomButtonInternal.h"

CtrlrCustomButtonInternal::CtrlrCustomButtonInternal (CtrlrImageButton &_owner)
    : Button (""),
      owner(_owner),
	  paintMode(RectanglePlacement::stretchToFit)
{
    setSize (128, 32);
}

CtrlrCustomButtonInternal::~CtrlrCustomButtonInternal()
{

}

void CtrlrCustomButtonInternal::resized()
{
}

void CtrlrCustomButtonInternal::paintButton (Graphics& g, bool isMouseOverButton, bool isButtonDown)
{
	drawFrame (g, getFrameDestinationRect(), isMouseOverButton, isButtonDown);
	drawTextBoxText (g, getFrameDestinationRect(), getBounds());
}

void CtrlrCustomButtonInternal::setPaintMode(const RectanglePlacement _paintMode)
{
	paintMode = _paintMode;
}

void CtrlrCustomButtonInternal::setImage (const Image imageToSet, const int _frameWidth, const int _frameHeight)
{
	possibleValues.clear();

	if (imageToSet == Image())
	{
		frameWidth	= 0;
		frameHeight = 0;
		return;
	}

	int totalSpace  = 0;
	frameWidth		= _frameWidth;
	frameHeight		= _frameHeight;
	filmStripImage	= imageToSet;

	if (isVertical)
	{
		totalSpace		= filmStripImage.getHeight()/frameHeight;
		for (int y=0; y<totalSpace; y++)
		{
			Rectangle<int> rect(0, y*frameHeight, frameWidth, frameHeight);
			possibleValues.add (rect);
		}
	}
	else
	{
		totalSpace		= filmStripImage.getWidth()/frameWidth;
		for (int x=0; x<totalSpace; x++)
		{
			Rectangle<int> rect(x*frameWidth, 0, frameWidth, frameHeight);
			possibleValues.add (rect);
		}
	}
}

const Rectangle<int> CtrlrCustomButtonInternal::getFrameDestinationRect()
{
	Rectangle <int> frameDestinationRectangle;
	const String textBoxPosition						= owner.getProperty(::Ids::uiImageButtonTextPosition);
	const int textBoxHeight								= (int)owner.getProperty(::Ids::uiImageButtonTextHeight);
	const int textBoxWidth								= (int)owner.getProperty(::Ids::uiImageButtonTextWidth);

	if (textBoxPosition == "top")
	{
		frameDestinationRectangle = Rectangle<int>(0, textBoxHeight, getWidth(), getHeight() - textBoxHeight);
	}
	else if (textBoxPosition == "bottom")
	{
		frameDestinationRectangle = Rectangle<int>(0, 0, getWidth(), getHeight() - textBoxHeight);
	}
	else if (textBoxPosition == "left")
	{
		frameDestinationRectangle = Rectangle<int>(textBoxWidth, 0, getWidth() - textBoxWidth, getHeight());
	}
	else if (textBoxPosition == "right")
	{
		frameDestinationRectangle = Rectangle<int>(0, 0, getWidth() - textBoxWidth, getHeight());
	}
	else
	{
		frameDestinationRectangle = Rectangle<int>(0,0,getWidth(),getHeight());
	}

	return (frameDestinationRectangle);
}

Rectangle<int> CtrlrCustomButtonInternal::getFrameCoordsFromStrip(const bool isMouseOver, const bool isMouseDown)
{
	Rectangle<int> stripRectangle;

	if (owner.getButtonMode() == CtrlrImageButton::Momentary)
	{
		if (isMouseDown)
		{
			stripRectangle = possibleValues[1];
		}
		else
		{
			stripRectangle = possibleValues[0];
		}
	}
	else if (owner.getButtonMode() == CtrlrImageButton::MomentaryMouseOver)
	{
		if (isMouseOver && !isMouseDown)
		{
			stripRectangle = possibleValues[0];
		}
		else if (isMouseDown && isMouseOver)
		{
			stripRectangle = possibleValues[2];
		}
		else
		{
			stripRectangle = possibleValues[1];
		}
	}
	else if (isMouseOver && !isMouseDown && getMouseOverMode())
	{
		/* need to draw the mouseOver[1] frame */
		stripRectangle = possibleValues[0];
	}
	else if (isMouseDown && getMouseOverMode())
	{
		/* mouse is not over, draw a normal frame for the current value, but move the index by one to include the mouseOver frame */
		stripRectangle = possibleValues[(int)owner.getComponentValue()+1];
	}
	else if (getMouseOverMode())
	{
		stripRectangle = possibleValues[(int)owner.getComponentValue()+1];
	}
	else if (!getMouseOverMode())
	{
		/* normal event, draw a frame that corresponds to the value */
		stripRectangle = possibleValues[(int)owner.getComponentValue()];
	}

	return (stripRectangle);
}

const bool CtrlrCustomButtonInternal::getMouseOverMode()
{
	switch (owner.getButtonMode())
	{
		case CtrlrImageButton::NormalMouseOver:
		case CtrlrImageButton::MomentaryMouseOver:
			return (true);
		default:
			break;
	}

	return (false);
}

void CtrlrCustomButtonInternal::drawTextBoxText(Graphics &g, const Rectangle<int> &frameRect, const Rectangle<int> &totalAreaToDraw)
{
	RectangleList<int> list;
	list.add (totalAreaToDraw);
	list.subtract (frameRect);
	Rectangle<int> destination = list.getBounds();

	const int destinationWidth = (int)owner.getProperty(::Ids::uiImageButtonTextWidth)  ? (int)owner.getProperty(::Ids::uiImageButtonTextWidth)  : destination.getWidth();
	const int destinatioHeight = (int)owner.getProperty(::Ids::uiImageButtonTextHeight) ? (int)owner.getProperty(::Ids::uiImageButtonTextHeight) : destination.getHeight();

	destination.setSize (destinationWidth, destinatioHeight);

	g.setColour (VAR2COLOUR(owner.getProperty(::Ids::uiImageButtonTextColour)));
	g.setFont (owner.getOwner().getOwnerPanel().getCtrlrManagerOwner().getFontManager().getFontFromString(owner.getProperty(::Ids::uiButtonTextFont)));

	g.drawFittedText (getButtonText(),
							destination.getX(),
							destination.getY(),
							destination.getWidth(),
							destination.getHeight(),
							justificationFromProperty (owner.getProperty(::Ids::uiButtonTextJustification)),
							2);
}

void CtrlrCustomButtonInternal::drawFrame(Graphics &g, const Rectangle<int> &destinationRect, const bool isMouseOver, const bool isMouseDown)
{
	g.drawImageWithin (filmStripImage.getClippedImage(getFrameCoordsFromStrip(isMouseOver, isMouseDown)),
						destinationRect.getX(),
						destinationRect.getY(),
						destinationRect.getWidth(),
						destinationRect.getHeight(),
						relativePostionFromProperty (owner.getProperty(::Ids::resourceImagePaintMode)),
						false);
}