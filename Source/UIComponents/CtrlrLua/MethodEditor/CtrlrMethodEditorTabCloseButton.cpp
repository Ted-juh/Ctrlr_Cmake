#include "stdafx.h"
#include "CtrlrLuaMethodEditor.h"
#include "CtrlrMethodEditorTabCloseButton.h"

CtrlrMethodEditorTabCloseButton::CtrlrMethodEditorTabCloseButton (CtrlrLuaMethodEditor &_owner, const int _tabIndex)
    : Button (""),
      owner(_owner), tabIndex(_tabIndex)
{
    setSize (24, 24);
}

CtrlrMethodEditorTabCloseButton::~CtrlrMethodEditorTabCloseButton()
{
}

//==============================================================================
void CtrlrMethodEditorTabCloseButton::resized()
{
    internalPath1.clear();
    internalPath1.startNewSubPath ((float) (proportionOfWidth (0.7000f)), (float) (proportionOfHeight (0.2500f)));
    internalPath1.lineTo ((float) (proportionOfWidth (0.7500f)), (float) (proportionOfHeight (0.3000f)));
    internalPath1.lineTo ((float) (proportionOfWidth (0.3000f)), (float) (proportionOfHeight (0.7500f)));
    internalPath1.lineTo ((float) (proportionOfWidth (0.2500f)), (float) (proportionOfHeight (0.7000f)));
    internalPath1.closeSubPath();

    internalPath2.clear();
    internalPath2.startNewSubPath ((float) (proportionOfWidth (0.3000f)), (float) (proportionOfHeight (0.2500f)));
    internalPath2.lineTo ((float) (proportionOfWidth (0.7500f)), (float) (proportionOfHeight (0.7000f)));
    internalPath2.lineTo ((float) (proportionOfWidth (0.7000f)), (float) (proportionOfHeight (0.7500f)));
    internalPath2.lineTo ((float) (proportionOfWidth (0.2500f)), (float) (proportionOfHeight (0.3000f)));
    internalPath2.closeSubPath();

    internalPath3.clear();
    internalPath3.startNewSubPath ((float) (proportionOfWidth (0.7000f)), (float) (proportionOfHeight (0.2500f)));
    internalPath3.lineTo ((float) (proportionOfWidth (0.7500f)), (float) (proportionOfHeight (0.3000f)));
    internalPath3.lineTo ((float) (proportionOfWidth (0.3000f)), (float) (proportionOfHeight (0.7500f)));
    internalPath3.lineTo ((float) (proportionOfWidth (0.2500f)), (float) (proportionOfHeight (0.7000f)));
    internalPath3.closeSubPath();

    internalPath4.clear();
    internalPath4.startNewSubPath ((float) (proportionOfWidth (0.3000f)), (float) (proportionOfHeight (0.2500f)));
    internalPath4.lineTo ((float) (proportionOfWidth (0.7500f)), (float) (proportionOfHeight (0.7000f)));
    internalPath4.lineTo ((float) (proportionOfWidth (0.7000f)), (float) (proportionOfHeight (0.7500f)));
    internalPath4.lineTo ((float) (proportionOfWidth (0.2500f)), (float) (proportionOfHeight (0.3000f)));
    internalPath4.closeSubPath();

    internalPath5.clear();
    internalPath5.startNewSubPath ((float) (proportionOfWidth (0.7000f)), (float) (proportionOfHeight (0.2500f)));
    internalPath5.lineTo ((float) (proportionOfWidth (0.7500f)), (float) (proportionOfHeight (0.3000f)));
    internalPath5.lineTo ((float) (proportionOfWidth (0.3000f)), (float) (proportionOfHeight (0.7500f)));
    internalPath5.lineTo ((float) (proportionOfWidth (0.2500f)), (float) (proportionOfHeight (0.7000f)));
    internalPath5.closeSubPath();

    internalPath6.clear();
    internalPath6.startNewSubPath ((float) (proportionOfWidth (0.3000f)), (float) (proportionOfHeight (0.2500f)));
    internalPath6.lineTo ((float) (proportionOfWidth (0.7500f)), (float) (proportionOfHeight (0.7000f)));
    internalPath6.lineTo ((float) (proportionOfWidth (0.7000f)), (float) (proportionOfHeight (0.7500f)));
    internalPath6.lineTo ((float) (proportionOfWidth (0.2500f)), (float) (proportionOfHeight (0.3000f)));
    internalPath6.closeSubPath();
}

void CtrlrMethodEditorTabCloseButton::paintButton (Graphics& g, bool isMouseOverButton, bool isButtonDown)
{
    if (isButtonDown)
    {
        g.setGradientFill (ColourGradient (Colour (0xff9e9e9e),
                                           (float) ((getWidth() / 2)), (float) ((getHeight() / 2)),
                                           Colour (0xffe0e0e0),
                                           (float) (getWidth()), 0.0f,
                                           true));
        g.fillEllipse ((float) (proportionOfWidth (0.0500f)), (float) (proportionOfHeight (0.0500f)), (float) (proportionOfWidth (0.9000f)), (float) (proportionOfHeight (0.9000f)));

        g.setColour (Colour (0xcf000000));
        g.fillPath (internalPath5);

        g.setColour (Colour (0xcf000000));
        g.fillPath (internalPath6);
    }
    else if (isMouseOverButton)
    {
        g.setGradientFill (ColourGradient (Colour (0xffdbdbdb),
                                           (float) ((getWidth() / 2)), (float) ((getHeight() / 2)),
                                           Colour (0xffcfcfcf),
                                           (float) (getWidth()), 0.0f,
                                           true));
        g.fillEllipse ((float) (proportionOfWidth (0.0500f)), (float) (proportionOfHeight (0.0500f)), (float) (proportionOfWidth (0.9000f)), (float) (proportionOfHeight (0.9000f)));

        g.setColour (Colour (0xcf000000));
        g.fillPath (internalPath3);

        g.setColour (Colour (0xcf000000));
        g.fillPath (internalPath4);
    }
    else
    {
        g.setColour (Colour (0xcf000000));
        g.fillPath (internalPath1);

        g.setColour (Colour (0xcf000000));
        g.fillPath (internalPath2);
    }
}

void CtrlrMethodEditorTabCloseButton::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
	Button::mouseDown (e);
	TabBarButton *parent = dynamic_cast<TabBarButton*>(getParentComponent());

	if (parent)
	{
		owner.closeTab (parent->getIndex());
	}
    //[/UserCode_mouseDown]
}