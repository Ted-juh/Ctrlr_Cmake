#include "stdafx.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrChildWindowContent.h"
#include "CtrlrLog.h"
#include "CtrlrChildWindow.h"
#include "CtrlrPanelWindowManager.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrChildWindowContainer.h"

CtrlrChildWindowContainer::CtrlrChildWindowContainer (CtrlrWindowManager &_owner)
    : content(nullptr), owner(_owner),
      menuBar (0)
{
    addAndMakeVisible (menuBar = new MenuBarComponent (this));

    setSize (600, 400);
}

CtrlrChildWindowContainer::~CtrlrChildWindowContainer()
{
    deleteAndZero (menuBar);
}

void CtrlrChildWindowContainer::paint (Graphics& g)
{
}

void CtrlrChildWindowContainer::resized()
{
	if (menuBar)
	{
		menuBar->setBounds(0, 0, getWidth() - 0, owner.managerOwner.getProperty(Ids::ctrlrMenuBarHeight));
	}

	if (content)
	{
		content->setBounds (0, owner.managerOwner.getProperty(Ids::ctrlrMenuBarHeight), getWidth(), getHeight() - (int)owner.managerOwner.getProperty(Ids::ctrlrMenuBarHeight));
	}
}


void CtrlrChildWindowContainer::setContent(CtrlrChildWindowContent* _content)
{
	content = _content;

	if (content != nullptr)
	{
		deleteAndZero(menuBar);
			if (content->getType() != CtrlrManagerWindowManager::BuildScript)
			{
				addAndMakeVisible(menuBar = new MenuBarComponent(this));
			}

		addAndMakeVisible(content);
		content->setContainer(this);

	}

	resized();
}


CtrlrChildWindowContent *CtrlrChildWindowContainer::getContent()
{
	return (content);
}

CtrlrWindowManager &CtrlrChildWindowContainer::getOwner()
{
	return (owner);
}

void CtrlrChildWindowContainer::closeWindow()
{
	if (getParentComponent())
	{
		delete getParentComponent();
	}
}

StringArray CtrlrChildWindowContainer::getMenuBarNames()
{
	if (content)
	{
		if (content->getMenuBarNames().size() != 0)
		{
			return (content->getMenuBarNames());
		}
	}
	const char* const names[] = { "File", nullptr };
	return StringArray (names);
}

PopupMenu CtrlrChildWindowContainer::getMenuForIndex(int topLevelMenuIndex, const String &menuName)
{
	if (content)
	{
		if (content->getMenuForIndex (topLevelMenuIndex, menuName).getNumItems() > 0)
		{
			return (content->getMenuForIndex (topLevelMenuIndex, menuName));
		}
	}

	PopupMenu m;
	if (topLevelMenuIndex == 0)
	{
		m.addItem (1, "Close");
	}

	return (m);
}

void CtrlrChildWindowContainer::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
	if (content)
	{
		content->menuItemSelected(menuItemID, topLevelMenuIndex);
	}
}

