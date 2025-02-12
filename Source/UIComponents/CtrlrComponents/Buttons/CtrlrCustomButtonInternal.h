#pragma once
#include "CtrlrMacros.h"

class CtrlrImageButton;

class CtrlrCustomButtonInternal  : public Button
{
public:
  
    CtrlrCustomButtonInternal (CtrlrImageButton &_owner);
    ~CtrlrCustomButtonInternal();

	void setImage (const Image imageToSet, const int _frameWidth, const int _frameHeight);
	void setPaintMode(const RectanglePlacement _paintMode);
	void setOrientation(const bool _isVertical)						{ isVertical = _isVertical; }

	Rectangle<int> getFrameCoordsFromStrip(const bool isMouseOver, const bool isMouseDown);
	const Rectangle<int> getFrameDestinationRect();
	void drawFrame(Graphics &g, const Rectangle<int> &destinationRect, const bool isMouseOver, const bool isMouseDown);
	void drawTextBoxText(Graphics &g, const Rectangle<int> &frameRect, const Rectangle<int> &totalAreaToDraw);
	const bool getMouseOverMode();
    void resized();
    void paintButton (Graphics& g, bool isMouseOverButton, bool isButtonDown);

    juce_UseDebuggingNewOperator

private:
	CtrlrImageButton &owner;
	int frameHeight;
	int frameWidth;
	Image filmStripImage;
	Array <Rectangle<int> > possibleValues;
	RectanglePlacement paintMode;
	bool isVertical;
    CtrlrCustomButtonInternal (const CtrlrCustomButtonInternal&);
    const CtrlrCustomButtonInternal& operator= (const CtrlrCustomButtonInternal&);
};
