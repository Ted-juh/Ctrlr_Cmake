#pragma once
#include "CtrlrComponents/CtrlrComponent.h"
#include "CtrlrPanel/CtrlrPanel.h"

class CtrlrLabel;

class CtrlrLabelInternal : public Label
{
	public:
		CtrlrLabelInternal(CtrlrLabel &_owner, const String &componentName="", const String &labelText="");
		TextEditor *createEditorComponent();
		bool keyPressed (const KeyPress &key);
	private:
		CtrlrLabel &owner;
};

class CtrlrLabel  : public CtrlrComponent,
                    public CtrlrPanel::Listener,
                    public Label::Listener
{
public:
    CtrlrLabel (CtrlrModulator &owner);
    ~CtrlrLabel();

	void setComponentValue (const double newValue, const bool sendChangeMessage=false);
	double getComponentValue();
	int getComponentMidiValue();
	double getComponentMaxValue();
	const String getComponentText();
	void setComponentText (const String &componentText);
	void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
	void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
	void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
	void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
    void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved, int){}
	void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved, int, int){}
	void modulatorChanged (CtrlrModulator *modulatorThatChanged);
	void labelTextChanged (Label* labelThatHasChanged);
	void lookAndFeelChanged ();
	static void wrapForLua(lua_State *L);
	bool keyPressed (const KeyPress &key);
	CtrlrLabel &setLabelText(const String &text);
	CtrlrLabel &appendText(const String &text);
	const String getText();
	void customLookAndFeelChanged(LookAndFeelBase *customLookAndFeel = nullptr);
    void paint (Graphics& g);
    void resized();

    juce_UseDebuggingNewOperator

private:
	Array <int> values;
	WeakReference <CtrlrLuaMethod> labelChangedCbk;
    CtrlrLabelInternal* ctrlrLabel;
    CtrlrLabel (const CtrlrLabel&);
    const CtrlrLabel& operator= (const CtrlrLabel&);
};