#pragma once
#include "JuceHeader.h"

class CtrlrPanelEditor;
class CtrlrComponent;
class CtrlrPanelEditor;

class CtrlrComponentSelection : public SelectedItemSet<CtrlrComponent*>
{
	public:
		CtrlrComponentSelection(CtrlrPanelEditor &_owner);
		~CtrlrComponentSelection();
		void itemSelected (CtrlrComponent *selectedComponent);
		void itemDeselected (CtrlrComponent *deselectedComponent);
		void deselectAll();
		JUCE_LEAK_DETECTOR(CtrlrComponentSelection)

	private:
		CtrlrPanelEditor &owner;
};