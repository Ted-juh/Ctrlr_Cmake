#pragma once
#include "CtrlrComponents/CtrlrComponent.h"
#include "CtrlrPanel/CtrlrPanel.h"

class CtrlrTabsComponent;

class CtrlrTabsLF : public LookAndFeel_V2
{
	public:
		CtrlrTabsLF(CtrlrTabsComponent &_owner);
		int getTabButtonBestWidth (int tabIndex,
										const String& text,
										int tabDepth,
										Button &button);

		void drawTabButtonText (TabBarButton& button, Graphics& g, bool isMouseOver, bool isMouseDown);
		void fillTabButtonShape (TabBarButton& button, Graphics& g, const Path& path,  bool /*isMouseOver*/, bool /*isMouseDown*/);

	private:
		CtrlrTabsComponent &owner;
};

class CtrlrTabsContentComponent : public Component, public ValueTree::Listener
{
	public:
		CtrlrTabsContentComponent(const ValueTree &_tabTree, CtrlrTabsComponent &_owner);
		~CtrlrTabsContentComponent();
		void resized();
		void paint(Graphics &g);
		const var &getProperty (const Identifier& name) const;
		void setBackgroundImage (const Image &_tabBackgroundImage) { tabBackgroundImage = _tabBackgroundImage; }
		const Array<int> getResourceList();
		void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
		void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
		void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
		void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
        void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved, int){}
        void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved, int, int){}
		void parentNameChanged(const String &newName);
        void customLookAndFeelChanged(LookAndFeelBase *customLookAndFeel = nullptr);

	private:
		ValueTree tabTree;
		CtrlrTabsComponent &owner;
		Image tabBackgroundImage;
};

class CtrlrTabsComponent;

class CtrlrTabsInternal : public TabbedComponent
{
	public:
		CtrlrTabsInternal(CtrlrTabsComponent &_owner);
		~CtrlrTabsInternal();
		void currentTabChanged (int newCurrentTabIndex, const String &newCurrentTabName);

	private:
		CtrlrTabsComponent &owner;
};

class CtrlrTabsComponent  : public CtrlrComponent,
                            public CtrlrPanel::Listener,
							public DragAndDropTarget,
							public CtrlrGrouppingComponent
{
public:

    CtrlrTabsComponent (CtrlrModulator &owner);
    ~CtrlrTabsComponent();

	void setComponentValue (const double newValue, const bool sendChangeMessage=false);
	double getComponentValue();
	int getComponentMidiValue();
	double getComponentMaxValue();

	void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
	void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
	void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
	void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded);
    void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved, int);
	void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved, int, int){}
	void modulatorChanged (CtrlrModulator *modulatorThatChanged);
	TabbedComponent *getTabs() { return ((TabbedComponent *)ctrlrTabs); }
	void setOwned (CtrlrComponent *componentToOwn, const int subIndexInGroup = 0, const bool shouldOwnThisComponent = true);
	void canvasStateRestored();
	void addTab(const ValueTree tabToAdd);
	void removeTab(const ValueTree tabToRemove);
	const Array<int> getResourceList();
	void modulatorNameChanged (const String &newName);
	static void wrapForLua(lua_State *L);
	bool isInterestedInDragSource (const SourceDetails &dragSourceDetails);
	void itemDropped (const SourceDetails &dragSourceDetails);
	void itemDragExit (const SourceDetails &dragSourceDetails);
	void itemDragEnter (const SourceDetails &dragSourceDetails);
	bool isOwned(CtrlrComponent *componentToCheck);
	Array <CtrlrComponent*> getOwnedChildren();
	void customLookAndFeelChanged(LookAndFeelBase *customLookAndFeel = nullptr);
    void paint (Graphics& g);
    void resized();

private:
	CtrlrTabsLF lf;
	WeakReference <CtrlrLuaMethod> tabChangedCbk;
    CtrlrTabsInternal* ctrlrTabs;
    CtrlrTabsComponent (const CtrlrTabsComponent&);
    const CtrlrTabsComponent& operator= (const CtrlrTabsComponent&);

	JUCE_LEAK_DETECTOR(CtrlrTabsComponent)
};