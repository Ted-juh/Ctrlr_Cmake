#pragma once
#include "CtrlrComponents/CtrlrComponent.h"

class CtrlrFileListBox;

class CtrlrFileListBoxLF : public LookAndFeel_V2
{
	public:
		CtrlrFileListBoxLF (CtrlrFileListBox &_owner);
		void drawFileBrowserRow (Graphics &g, int width, int height, const String &filename, Image *icon, const String &fileSizeDescription, const String &fileTimeDescription, bool isDirectory, bool isItemSelected, int itemIndex, DirectoryContentsDisplayComponent &component);

	private:
		CtrlrFileListBox &owner;
};

class CtrlrFileTreeComponent : public FileTreeComponent
{
public:
	CtrlrFileTreeComponent ( CtrlrFileListBox &_owner, DirectoryContentsList &listToShow );
	void paint( Graphics& g );
private:
	CtrlrFileListBox &owner;
};

class CtrlrFileListBox  : public CtrlrComponent, public FileBrowserListener
{
public:
    //==============================================================================
    CtrlrFileListBox (CtrlrModulator &owner);
    ~CtrlrFileListBox();

	void setComponentValue (const double newValue, const bool sendChangeMessage=false);
	double getComponentValue();
	int getComponentMidiValue();
	double getComponentMaxValue();
	const String getComponentText();
	void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
	void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
	void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
	void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
    void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved, int){}
	void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved, int, int){}
	void selectionChanged ();
	void fileClicked (const File &file, const MouseEvent &e);
	void fileDoubleClicked (const File &file);
//	void deleteKeyPressed (const int value);
//	void returnKeyPressed (const int value);
	void browserRootChanged (const File &newRoot);
	static void wrapForLua(lua_State *L);
	int getNumSelectedFiles() const;
	File getSelectedFile(int index=0) const;
	void deselectAllFiles();
	void scrollToTop();
	void setSelectedFile(const File &file);
	void refresh();
	void customLookAndFeelChanged(LookAndFeelBase *customLookAndFeel = nullptr) {}
    void paint (Graphics& g);
    void resized();

	juce_UseDebuggingNewOperator

private:
	ScopedPointer <DirectoryContentsList> directoryContentsList;
	TimeSliceThread timeSliceThread;
//	ScopedPointer <FileTreeComponent> treeComponent;
	ScopedPointer <CtrlrFileTreeComponent> treeComponent;
//	ScopedPointer <FileListComponent> fileListComponent;
	CtrlrFileListBoxLF fileListBoxLookAndFeel;
	WeakReference <CtrlrLuaMethod> fileClickedCbk,fileDoubleClickedCbk; //,itemDeleteKeyPressedCbk,itemReturnKeyPressedCbk;
    CtrlrFileListBox (const CtrlrFileListBox&);
    const CtrlrFileListBox& operator= (const CtrlrFileListBox&);
};