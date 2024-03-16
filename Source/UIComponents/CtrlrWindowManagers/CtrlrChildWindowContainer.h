#pragma

#include "CtrlrMacros.h"

class CtrlrChildWindowContent;
class CtrlrPanelWindowManager;
class CtrlrChildWindowContainer;
class CtrlrWindowManager;

class CtrlrChildWindowContainer  : public Component,
                                   public MenuBarModel
{
public:

    CtrlrChildWindowContainer (CtrlrWindowManager &_owner);
    ~CtrlrChildWindowContainer();

	void setContent(CtrlrChildWindowContent *_content);
	CtrlrChildWindowContent *getContent();
	CtrlrWindowManager &getOwner();
	StringArray getMenuBarNames();
	PopupMenu getMenuForIndex(int topLevelMenuIndex, const String &menuName);
	void menuItemSelected(int menuItemID, int topLevelMenuIndex);
	void closeWindow();

    void paint (Graphics& g);
    void resized();



private:
	CtrlrChildWindowContent *content;
	CtrlrWindowManager &owner;
    MenuBarComponent* menuBar;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrChildWindowContainer);
};
