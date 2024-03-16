#pragma once
#include "JuceHeader.h"
#include "CtrlrWindowManagers/CtrlrChildWindowContent.h"
#include "CtrlrWindowManagers/CtrlrPanelWindowManager.h"

class CtrlrPanel;

class CtrlrPanelLayerList  : public CtrlrChildWindowContent,
                             public ListBoxModel
{
public:

    CtrlrPanelLayerList (CtrlrPanel &_owner);
    ~CtrlrPanelLayerList();

    int getNumRows();
    void paintListBoxItem (int rowNumber, Graphics& g, int width, int height, bool rowIsSelected);
    Component* refreshComponentForRow (int rowNumber, bool isRowSelected, Component* existingComponentToUpdate);
	void setSelectedRow(const int rowToSelect);
	String getContentName()					{ return ("Panel layers"); }
	uint8 getType()							{ return (CtrlrPanelWindowManager::LayerEditor); }
	void buttonClicked (Button *button);
	CtrlrPanel &getOwner();
	StringArray getMenuBarNames();
	PopupMenu getMenuForIndex(int topLevelMenuIndex, const String &menuName);
	void menuItemSelected(int menuItemID, int topLevelMenuIndex);
	void addLayer();
	void removeLayer();
	void moveLayerUp();
	void moveLayerDown();
	void refresh();
    
    void paint (Graphics& g);
    void resized();

    JUCE_LEAK_DETECTOR(CtrlrPanelLayerList)

private:
	CtrlrPanel &owner;
    ListBox* layerList;
    CtrlrPanelLayerList (const CtrlrPanelLayerList&);
    const CtrlrPanelLayerList& operator= (const CtrlrPanelLayerList&);
};