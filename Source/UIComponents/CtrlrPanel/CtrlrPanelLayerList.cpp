#include "stdafx.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"
#include "CtrlrPanel/CtrlrPanelCanvas.h"
#include "CtrlrPanelLayerListItem.h"
#include "CtrlrInlineUtilitiesGUI.h"
#include "CtrlrPanelLayerList.h"

CtrlrPanelLayerList::CtrlrPanelLayerList (CtrlrPanel &_owner)
    : owner(_owner), layerList (0)
{
    addAndMakeVisible (layerList = new ListBox ("Layer List", this));
	layerList->setRowHeight (40);
	layerList->setMultipleSelectionEnabled (false);

    setSize (600, 400);
}

CtrlrPanelLayerList::~CtrlrPanelLayerList()
{
    deleteAndZero (layerList);
}

void CtrlrPanelLayerList::paint (Graphics& g)
{
}

void CtrlrPanelLayerList::resized()
{
    layerList->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
}

int CtrlrPanelLayerList::getNumRows()
{
	return (owner.getEditor()->getCanvas()->getNumLayers());
}

void CtrlrPanelLayerList::paintListBoxItem (int rowNumber, Graphics& g, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected)
    {
        gui::drawSelectionRectangle (g, width, height);
    }
}

Component* CtrlrPanelLayerList::refreshComponentForRow (int rowNumber, bool isRowSelected, Component* existingComponentToUpdate)
{
	CtrlrPanelLayerListItem* itemInfo = (CtrlrPanelLayerListItem*) existingComponentToUpdate;

	if (itemInfo == 0)
		itemInfo = new CtrlrPanelLayerListItem (*this);

	itemInfo->setRow (rowNumber);
	itemInfo->setLayer (owner.getEditor()->getCanvas()->getLayerFromArray(rowNumber));
	return itemInfo;
}

void CtrlrPanelLayerList::setSelectedRow(const int rowToSelect)
{
	layerList->selectRow (rowToSelect);
}

void CtrlrPanelLayerList::buttonClicked (Button *button)
{
}

CtrlrPanel &CtrlrPanelLayerList::getOwner()
{
	return (owner);
}

void CtrlrPanelLayerList::addLayer()
{
	if (owner.getEditor())
	{
		owner.getEditor()->getCanvas()->addLayer(ValueTree());
	}
	layerList->updateContent();
}

void CtrlrPanelLayerList::removeLayer()
{
	const int selectedRow = layerList->getSelectedRow();
	CtrlrPanelLayerListItem *item = dynamic_cast <CtrlrPanelLayerListItem*> (layerList->getComponentForRowNumber (selectedRow));
	CtrlrPanelCanvasLayer *layer = 0;
	if (item != nullptr)
	{
		layer = item->getLayer();
	}

	if (owner.getEditor())
	{
		owner.getEditor()->getCanvas()->removeLayer(layer);
	}
	layerList->updateContent();
}

void CtrlrPanelLayerList::moveLayerUp()
{
	const int selectedRow = layerList->getSelectedRow();
	CtrlrPanelLayerListItem *item = dynamic_cast <CtrlrPanelLayerListItem*> (layerList->getComponentForRowNumber (selectedRow));
	CtrlrPanelCanvasLayer *layer = 0;
	if (item != nullptr)
	{
		layer = item->getLayer();
	}

	if (selectedRow-1 < 0)
		return;

	if (owner.getEditor())
	{
		owner.getEditor()->getCanvas()->moveLayer(layer);
	}
	layerList->updateContent();
	layerList->selectRow (selectedRow-1);
}

void CtrlrPanelLayerList::moveLayerDown()
{
	const int selectedRow = layerList->getSelectedRow();
	CtrlrPanelLayerListItem *item = dynamic_cast <CtrlrPanelLayerListItem*> (layerList->getComponentForRowNumber (selectedRow));
	CtrlrPanelCanvasLayer *layer = 0;
	if (item != nullptr)
	{
		layer = item->getLayer();
	}

	if (selectedRow+1 >= getNumRows())
		return;

	if (owner.getEditor())
	{
		owner.getEditor()->getCanvas()->moveLayer(layer,false);
	}
	layerList->updateContent();
	layerList->selectRow (selectedRow+1);
}

void CtrlrPanelLayerList::refresh()
{
	layerList->updateContent();
}

StringArray CtrlrPanelLayerList::getMenuBarNames()
{
	const char* const names[] = { "File", "Edit", "View", nullptr };
	return StringArray (names);
}

PopupMenu CtrlrPanelLayerList::getMenuForIndex(int topLevelMenuIndex, const String &menuName)
{
	PopupMenu menu;
	if (topLevelMenuIndex == 0)
	{
		menu.addItem (1, "Close");
	}
	else if (topLevelMenuIndex == 1)
	{
		menu.addItem (2, "Add layer");
		menu.addItem (3, "Remove layer");
		menu.addSectionHeader ("Reposition");
		menu.addItem (4, "Move up");
		menu.addItem (5, "Move down");
	}
	else if (topLevelMenuIndex == 2)
	{
		menu.addItem (6, "Refresh view");
	}
	return (menu);
}

void CtrlrPanelLayerList::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
	if (topLevelMenuIndex == 1)
	{
		if (menuItemID == 2)
			addLayer();
		if (menuItemID == 3)
			removeLayer();
		if (menuItemID == 4)
			moveLayerUp();
		if (menuItemID == 5)
			moveLayerDown();
	}
	if (topLevelMenuIndex == 2)
	{
		if (menuItemID == 6)
			refresh();
	}
	if (topLevelMenuIndex == 0 && menuItemID==1)
	{
		owner.getWindowManager().toggle (CtrlrPanelWindowManager::LayerEditor, false);
	}
	
}