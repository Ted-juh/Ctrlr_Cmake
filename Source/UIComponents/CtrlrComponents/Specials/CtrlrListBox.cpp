#include "stdafx.h"
#include "CtrlrListBox.h"
#include "CtrlrValueMap.h"
#include "CtrlrIDs.h"
#include "CtrlrFontManager.h"
#include "CtrlrUtilitiesGUI.h"
#include "CtrlrModulator/CtrlrModulator.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrLuaManager.h"

CtrlrListBox::CtrlrListBox (CtrlrModulator &owner)
    : CtrlrComponent(owner),
      listBox (0)
{
	valueMap = new CtrlrValueMap();
	addAndMakeVisible (listBox = new ListBox ("List Box", this));
	listBox->setModel( this );

	setProperty (Ids::uiListBoxContent, "");
	setProperty (Ids::uiListBoxRowHeight, 16);
	setProperty (Ids::uiListBoxBackgroundColour, "0xffffffff");
	setProperty (Ids::uiListBoxHighlightBgColour, "0xff0000ff");
	setProperty (Ids::uiListBoxHighlightFgColour, "0xff000000");
	setProperty (Ids::uiListBoxTextColour, "0xff000000");
	setProperty (Ids::uiListBoxFont, FONT2STR (Font(14)));
	setProperty (Ids::uiListBoxHighlightFont, FONT2STR (Font(14)));
	setProperty (Ids::uiListBoxOutline, 0);
	setProperty (Ids::uiListBoxOutlineColour, "0xff000000");
	setProperty (Ids::uiListBoxVScrollBgColour, "0xffffffff");
	setProperty (Ids::uiListBoxVScrollThumbColour, "0xffababab");
	setProperty (Ids::uiListBoxVScrollTrackColour, "0xffff0000");
	setProperty (Ids::uiListBoxHScrollBgColour, "0xffffffff");
	setProperty (Ids::uiListBoxHScrollThumbColour, "0xffababab");
	setProperty (Ids::uiListBoxHScrollTrackColour, "0xffff0000");
	setProperty (Ids::uiListBoxJustification, "centred");
	setProperty (Ids::uiListBoxMultipleSelection, false);
	setProperty (Ids::uiListBoxItemClicked, COMBO_NONE_ITEM);
	setProperty (Ids::uiListBoxItemDoubleClicked, COMBO_NONE_ITEM);
	setProperty (Ids::uiListBoxItemDeleteKeyPressed, COMBO_NONE_ITEM);
	setProperty (Ids::uiListBoxItemReturnKeyPressed, COMBO_NONE_ITEM);

    setSize (128, 256);
}

CtrlrListBox::~CtrlrListBox()
{
    deleteAndZero (listBox);
}

void CtrlrListBox::paint (Graphics& g)
{
}

void CtrlrListBox::resized()
{
    listBox->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
	listBox->setBounds (getUsableRect());

}

int CtrlrListBox::getNumRows()
{
	return (valueMap->getNumValues());
}

void CtrlrListBox::paintListBoxItem (int rowNumber, Graphics &g, int width, int height, bool rowIsSelected)
{
	if (rowIsSelected)
	{
		g.setFont (STR2FONT(getProperty(Ids::uiListBoxHighlightFont)));
		g.fillAll (VAR2COLOUR(getProperty(Ids::uiListBoxHighlightBgColour)));
		g.setColour (VAR2COLOUR(getProperty(Ids::uiListBoxHighlightFgColour)));
		g.drawText (valueMap->getTextForIndex(rowNumber), 0, 0,  width, height, justificationFromProperty(getProperty(Ids::uiListBoxJustification)), true);
	}
	else
	{
		g.setFont (STR2FONT(getProperty(Ids::uiListBoxFont)));
		g.setColour (VAR2COLOUR(getProperty(Ids::uiListBoxTextColour)));
		g.drawText (valueMap->getTextForIndex(rowNumber), 0, 0,  width, height, justificationFromProperty(getProperty(Ids::uiListBoxJustification)), true);
	}
}

void CtrlrListBox::setComponentValue (const double newValue, const bool sendChangeMessage)
{
	listBox->selectRow (newValue, false, true);

	if (sendChangeMessage)
	{
		owner.getProcessor().setValueGeneric (CtrlrModulatorValue(newValue,CtrlrModulatorValue::changedByGUI));
	}
}

double CtrlrListBox::getComponentValue()
{
	return (listBox->getSelectedRow());
}

int CtrlrListBox::getComponentMidiValue()
{
	return (valueMap->getMappedValue(listBox->getSelectedRow()));
}

double CtrlrListBox::getComponentMaxValue()
{
	return (valueMap->getNonMappedMax());
}

const String CtrlrListBox::getComponentText()
{
	return (valueMap->getTextForIndex(listBox->getSelectedRow()));
}

const String CtrlrListBox::getTextForValue(const double value)
{
	return (valueMap->getTextForIndex(value));
}

void CtrlrListBox::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (property == Ids::uiListBoxContent)
	{
		listboxContentChanged();
	}

	else if (property == Ids::uiListBoxBackgroundColour)
	{
		listBox->setColour (ListBox::backgroundColourId, VAR2COLOUR(getProperty (property)));
	}

	else if (property == Ids::uiListBoxOutline)
	{
		listBox->setOutlineThickness (getProperty (property));
	}

	else if (property == Ids::uiListBoxOutlineColour)
	{
		listBox->setColour (ListBox::outlineColourId, VAR2COLOUR(getProperty (property)));
	}

	else if (property == Ids::uiListBoxRowHeight)
	{
		listBox->setRowHeight (getProperty(property));
	}

	else if (property == Ids::uiListBoxHScrollBgColour
		|| property == Ids::uiListBoxHScrollThumbColour
		|| property == Ids::uiListBoxHScrollTrackColour
		|| property == Ids::uiListBoxVScrollBgColour
		|| property == Ids::uiListBoxVScrollThumbColour
		|| property == Ids::uiListBoxVScrollTrackColour
		)
	{
		listBox->getVerticalScrollBar().setColour (ScrollBar::backgroundColourId, VAR2COLOUR(getProperty (Ids::uiListBoxVScrollBgColour)));
		listBox->getVerticalScrollBar().setColour (ScrollBar::thumbColourId, VAR2COLOUR(getProperty (Ids::uiListBoxVScrollThumbColour)));
		listBox->getVerticalScrollBar().setColour (ScrollBar::trackColourId, VAR2COLOUR(getProperty (Ids::uiListBoxVScrollTrackColour)));
		listBox->getHorizontalScrollBar().setColour (ScrollBar::backgroundColourId, VAR2COLOUR(getProperty (Ids::uiListBoxHScrollBgColour)));
		listBox->getHorizontalScrollBar().setColour (ScrollBar::thumbColourId, VAR2COLOUR(getProperty (Ids::uiListBoxHScrollThumbColour)));
		listBox->getHorizontalScrollBar().setColour (ScrollBar::trackColourId, VAR2COLOUR(getProperty (Ids::uiListBoxHScrollTrackColour)));
	}
	else if (property == Ids::uiListBoxItemClicked)
	{
		if (getProperty(property) == "")
			return;

		itemClickedCbk = owner.getOwnerPanel().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::uiListBoxItemDoubleClicked)
	{
		if (getProperty(property) == "")
			return;

		itemDoubleClickedCbk = owner.getOwnerPanel().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::uiListBoxItemDeleteKeyPressed)
	{
		if (getProperty(property) == "")
			return;

		itemDeleteKeyPressedCbk = owner.getOwnerPanel().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::uiListBoxItemReturnKeyPressed)
	{
		if (getProperty(property) == "")
			return;

		itemReturnKeyPressedCbk = owner.getOwnerPanel().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::uiListBoxMultipleSelection)
	{
		listBox->setMultipleSelectionEnabled ((bool)getProperty(property));
	}
	else
	{
		CtrlrComponent::valueTreePropertyChanged (treeWhosePropertyHasChanged, property);
	}

	resized();
	listBox->updateContent();
	listBox->repaint();
}

void CtrlrListBox::listBoxItemClicked (int value, const MouseEvent &e)
{
	if (itemClickedCbk && !itemClickedCbk.wasObjectDeleted())
	{
		if (itemClickedCbk->isValid())
		{
			owner.getOwnerPanel().getCtrlrLuaManager().getMethodManager().call (itemClickedCbk, &owner, value);
		}
	}
}

void CtrlrListBox::listBoxItemDoubleClicked (int value, const MouseEvent &e)
{
	if (itemDoubleClickedCbk && !itemDoubleClickedCbk.wasObjectDeleted())
	{
		if (itemDoubleClickedCbk->isValid())
		{
			owner.getOwnerPanel().getCtrlrLuaManager().getMethodManager().call (itemDoubleClickedCbk, &owner, value);
		}
	}
}

void CtrlrListBox::deleteKeyPressed (int value)
{
	if (itemDeleteKeyPressedCbk && !itemDeleteKeyPressedCbk.wasObjectDeleted())
	{
		if (itemDeleteKeyPressedCbk->isValid())
		{
			owner.getOwnerPanel().getCtrlrLuaManager().getMethodManager().call (itemDeleteKeyPressedCbk, &owner, value);
		}
	}
}

void CtrlrListBox::returnKeyPressed (int value)
{
	if (itemReturnKeyPressedCbk && !itemReturnKeyPressedCbk.wasObjectDeleted())
	{
		if (itemReturnKeyPressedCbk->isValid())
		{
			owner.getOwnerPanel().getCtrlrLuaManager().getMethodManager().call (itemReturnKeyPressedCbk, &owner, value);
		}
	}
}


void CtrlrListBox::listboxContentChanged()
{
	valueMap->copyFrom (owner.getProcessor().setValueMap (getProperty (Ids::uiListBoxContent)));
}

void CtrlrListBox::selectedRowsChanged (int lastRowSelected)
{
	if ((bool)getProperty(Ids::uiListBoxMultipleSelection))
	{
		return;
	}
	else
	{
		if (lastRowSelected >= 0)
		{
			setComponentValue (lastRowSelected, true);
		}
	}
}

void CtrlrListBox::updateContent()
{
	listBox->updateContent();
}

void CtrlrListBox::selectRow(int rowNumber, bool dontScrollToShowThisRow, bool deselectOthersFirst)
{
	listBox->selectRow(rowNumber, dontScrollToShowThisRow, deselectOthersFirst);
}

void CtrlrListBox::selectRangeOfRows(int firstRow, int lastRow)
{
	listBox->selectRangeOfRows (firstRow, lastRow);
}

void CtrlrListBox::deselectRow(int rowNumber)
{
	listBox->deselectRow (rowNumber);
}

void CtrlrListBox::deselectAllRows()
{
	listBox->deselectAllRows();
}

void CtrlrListBox::flipRowSelection(int rowNumber)
{
	listBox->flipRowSelection(rowNumber);
}

int CtrlrListBox::getNumSelectedRows() const
{
	return (listBox->getNumSelectedRows());
}

int CtrlrListBox::getSelectedRow(int index) const
{
	return (listBox->getSelectedRow(index));
}

int CtrlrListBox::getLastRowSelected() const
{
	return (listBox->getLastRowSelected());
}

bool CtrlrListBox::isRowSelected(int rowNumber) const
{
	return (listBox->isRowSelected(rowNumber));
}

SparseSet <int> CtrlrListBox::getSelectedRows() const
{
	return (listBox->getSelectedRows());
}

void CtrlrListBox::setMultipleSelectionEnabled (bool shouldBeEnabled)
{
	listBox->setMultipleSelectionEnabled(shouldBeEnabled);
}