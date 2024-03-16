#pragma once
#include "CtrlrMacros.h"

class CtrlrPanelCanvas;
class CtrlrPanelLayerList;
class CtrlrPanelCanvasLayer;
class CtrlrColourEditorComponent;

class CtrlrPanelLayerListItem  : public Component,
                                 public ChangeListener,
								 public Label::Listener,
								 public Button::Listener
{
public:

    CtrlrPanelLayerListItem (CtrlrPanelLayerList &_owner);
    ~CtrlrPanelLayerListItem();

    void setLayer(CtrlrPanelCanvasLayer *_layer);
	void changeListenerCallback (ChangeBroadcaster* source);
	CtrlrPanelCanvasLayer *getLayer() { return (layer); }
	void setRow(const int _rowIndex);
	const int getRow() { return (rowIndex); }

    void paint (Graphics& g);
    void resized();
    void labelTextChanged (Label* labelThatHasChanged);
    void buttonClicked (Button* buttonThatWasClicked);
    void mouseDown (const MouseEvent& e);

    JUCE_LEAK_DETECTOR(CtrlrPanelLayerListItem)

private:

	CtrlrPanelCanvasLayer *layer;
	CtrlrPanelLayerList &owner;
	int rowIndex;

    Label* layerName;
    ToggleButton* layerVisibility;
    CtrlrColourEditorComponent* layerColour;
    Label* layerIndex;

    CtrlrPanelLayerListItem (const CtrlrPanelLayerListItem&);
    const CtrlrPanelLayerListItem& operator= (const CtrlrPanelLayerListItem&);
};
