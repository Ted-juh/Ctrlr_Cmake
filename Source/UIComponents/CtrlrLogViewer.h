#pragma once
#include "CtrlrMacros.h"
#include "CtrlrLog.h"
#include "CtrlrWindowManagers/CtrlrChildWindowContent.h"

class CtrlrManager;

class CtrlrLogViewerTokeniser : public CodeTokeniser
{
	public:
		CtrlrLogViewerTokeniser();
		~CtrlrLogViewerTokeniser();
		int readNextToken (CodeDocument::Iterator& source);
		CodeEditorComponent::ColourScheme getDefaultColourScheme();
		JUCE_LEAK_DETECTOR (CtrlrLogViewerTokeniser);
};

class CtrlrLogViewer  : public CtrlrChildWindowContent,
                        public CtrlrLog::Listener
{
public:
 
    CtrlrLogViewer (CtrlrManager &_owner);
    ~CtrlrLogViewer();

	enum ToolbarItems
	{
		_none,
		clearLog
	};
	void messageLogged (CtrlrLog::CtrlrLogMessage message);
	String getContentName()					{ return ("Log viewer"); }
	uint8 getType()							{ return (CtrlrManagerWindowManager::LogViewer); }
	StringArray getMenuBarNames();
	PopupMenu getMenuForIndex(int topLevelMenuIndex, const String &menuName);
	void menuItemSelected(int menuItemID, int topLevelMenuIndex);
    
    void paint (Graphics& g);
    void resized();

	juce_UseDebuggingNewOperator

private:
    CtrlrManager &owner;
	CodeDocument logDocument;
	CtrlrLogViewerTokeniser logViewerTokeniser;
    CodeEditorComponent* logEditor;

	CtrlrLogViewer (const CtrlrLogViewer&);
    
	const CtrlrLogViewer& operator= (const CtrlrLogViewer&);
};
