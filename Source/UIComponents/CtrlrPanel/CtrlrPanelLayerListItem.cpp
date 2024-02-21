#include "stdafx.h"
#include "CtrlrPanelLayerListItem.h"
#include "CtrlrPropertyEditors/CtrlrPropertyComponent.h"
#include "CtrlrPanelCanvasLayer.h"
#include "CtrlrPanelLayerList.h"
#include "CtrlrInlineUtilitiesGUI.h"

CtrlrPanelLayerListItem::CtrlrPanelLayerListItem (CtrlrPanelLayerList &_owner)
    : layer(0), owner(_owner),
      layerName (0),
      layerVisibility (0),
      layerColour (0),
      layerIndex (0)
{
    addAndMakeVisible (layerName = new Label ("",
                                              L"Layer Name"));
    layerName->setFont (Font (12.0000f, Font::plain));
    layerName->setJustificationType (Justification::centredLeft);
    layerName->setEditable (true, true, false);
    layerName->setColour (TextEditor::textColourId, Colours::black);
    layerName->setColour (TextEditor::backgroundColourId, Colour (0x0));
    layerName->addListener (this);

    addAndMakeVisible (layerVisibility = new ToggleButton(""));
    layerVisibility->addListener (this);

    addAndMakeVisible (layerColour = new CtrlrColourEditorComponent (this));
    addAndMakeVisible (layerIndex = new Label (L"layerIndex",
                                               L"2"));
    layerIndex->setFont (Font (12.0000f, Font::plain));
    layerIndex->setJustificationType (Justification::centred);
    layerIndex->setEditable (false, false, false);
    layerIndex->setColour (TextEditor::textColourId, Colours::black);
    layerIndex->setColour (TextEditor::backgroundColourId, Colour (0x0));

	layerName->addMouseListener (this, true);
	layerVisibility->addMouseListener (this, true);
	layerColour->addMouseListener (this, true);
	layerIndex->addMouseListener (this, true);

	layerVisibility->setMouseCursor (MouseCursor::PointingHandCursor);

    setSize (355, 40);
}

CtrlrPanelLayerListItem::~CtrlrPanelLayerListItem()
{
    deleteAndZero (layerName);
    deleteAndZero (layerVisibility);
    deleteAndZero (layerColour);
    deleteAndZero (layerIndex);
}

//==============================================================================
void CtrlrPanelLayerListItem::paint (Graphics& g)
{
    g.setColour(Colours::black);
    g.drawLine(0, getHeight(), getWidth(), getHeight(), 1.0f);
}

void CtrlrPanelLayerListItem::resized()
{
    layerName->setBounds (48, 4, proportionOfWidth (0.5183f), 12);
    layerVisibility->setBounds (8, 4, 32, 32);
    layerColour->setBounds (48, 16, getWidth() - 144, 16);
    layerIndex->setBounds (getWidth() - 83, getHeight() - 16, 14, 16);
}

void CtrlrPanelLayerListItem::labelTextChanged (Label* labelThatHasChanged)
{
    if (labelThatHasChanged == layerName)
    {
		if (layer)
		{
			layer->setProperty (Ids::uiPanelCanvasLayerName, layerName->getText());
		}
    }
}

void CtrlrPanelLayerListItem::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == layerVisibility)
    {
		if (layer)
		{
			layer->setProperty (Ids::uiPanelCanvasLayerVisibility, layerVisibility->getToggleState());
		}
    }
}

void CtrlrPanelLayerListItem::mouseDown (const MouseEvent& e)
{
	if (layer)
	{
		owner.setSelectedRow (rowIndex);
	}
}

void CtrlrPanelLayerListItem::setLayer (CtrlrPanelCanvasLayer *_layer)
{
	if (_layer == nullptr)
		return;

	layer = _layer;

	layerName->setText (layer->getProperty(Ids::uiPanelCanvasLayerName), dontSendNotification);
	layerVisibility->setToggleState (layer->getProperty(Ids::uiPanelCanvasLayerVisibility), sendNotification);
	layerColour->setColour (VAR2COLOUR(layer->getProperty(Ids::uiPanelCanvasLayerColour)), false);
	layerIndex->setText (layer->getProperty(Ids::uiPanelCanvasLayerIndex).toString(), dontSendNotification);
}

void CtrlrPanelLayerListItem::changeListenerCallback (ChangeBroadcaster* source)
{
	if (layer)
	{
		layer->setProperty (Ids::uiPanelCanvasLayerColour, layerColour->getColour().toString());
        layerColour->updateLabel();
	}
}

void CtrlrPanelLayerListItem::setRow(const int _rowIndex)
{
	rowIndex = _rowIndex;
}