#pragma once
#include "../CtrlrComponent.h"
#include "CtrlrModulator/CtrlrModulator.h"
#include "CtrlrIDs.h"
#include "CtrlrXYModulator.h"

class CtrlrXYSurface  : public CtrlrComponent
{
public:

    CtrlrXYSurface (CtrlrModulator &owner);
    ~CtrlrXYSurface();

	void setComponentValue (const double newValue, const bool sendChangeMessage=false);
	double getComponentValue();
	int getComponentMidiValue();
	double getComponentMaxValue();
	void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
	void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
	void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
	void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
    void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved, int){}
	void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved, int, int){}
	void modulatorMoved();
	void syncDestination();
	void allModulatorsInitialized();
	void showPopupMenu();
	const PopupMenu getModulatorListAsMenu(const int startIndex=0, const String &itemToSelect="");
	const int getValueForPosition(const int position, const bool forX=true);
	const int getPositionForValue(const int value, const bool forX=true);
	void rebuildModulatorList();
	void reloadResources(Array <CtrlrPanelResource*> resourcesThatChanged);
	void setResource();
	void customLookAndFeelChanged(LookAndFeelBase *customLookAndFeel = nullptr) {}
    void paint (Graphics& g);
    void resized();
    void mouseDown (const MouseEvent& e);
    void mouseDrag (const MouseEvent& e);

    juce_UseDebuggingNewOperator

private:
	Image backgroundImage;
	WeakReference<CtrlrModulator> destinationX, destinationY;
	bool initialized;
	Rectangle<int> usableRectangle;
	StringArray modulatorList;
    CtrlrXYModulator* surfaceModulator;
    CtrlrXYSurface (const CtrlrXYSurface&);
    const CtrlrXYSurface& operator= (const CtrlrXYSurface&);
};