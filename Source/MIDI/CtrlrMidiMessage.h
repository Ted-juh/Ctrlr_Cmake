#pragma once
#include "CtrlrMidiMessageEx.h"

class CtrlrLuaObjectWrapper;

static const uint8 MidiStartStatus		= 0xFA;
static const uint8 MidiStopStatus		= 0xFC;
static const uint8 MidiTickStatus		= 0xF9;
static const uint8 MidiContinueStatus	= 0xFB;
static const uint8 MidiSysexData[]		= {0xF0, 00, 0xF7 };

class LMemoryBlock;

enum CtrlrMidiMessageType
{
	CC,
	Aftertouch,
	ChannelPressure,
	NoteOn,
	NoteOff,
	SysEx,
	Multi,
	ProgramChange,
	PitchWheel,
	None,
	MidiClock,
	MidiClockContinue,
	MidiClockStop,
	MidiClockStart,
	ActiveSense,
	kMidiMessageType,
};

class TimestampComparator
{
	public:
		int compareElements (CtrlrMidiMessageEx first, CtrlrMidiMessageEx second)
		{
			return (first.m.getTimeStamp() < second.m.getTimeStamp()) ? -1 : ((second.m.getTimeStamp() < first.m.getTimeStamp()) ? 1 : 0);
		}
};

class CtrlrMidiMessage : public ValueTree::Listener
{
	public:
		CtrlrMidiMessage();
		CtrlrMidiMessage (const CtrlrMidiMessage &other);
		CtrlrMidiMessage (const MidiMessage& other);
		CtrlrMidiMessage (MemoryBlock& other);
		CtrlrMidiMessage (const String& hexData);
		CtrlrMidiMessage (const CtrlrLuaObjectWrapper& other);

		virtual ~CtrlrMidiMessage();
		virtual void setNumber(const int number);
		int getNumber() const;
		void setValue (const int value);
		int getValue();
		virtual void setChannel(const int midiChannel);
		virtual int getChannel() const ;
		int getNumMessages() const																		{ return (messageArray.size()); }
		void setSysExFormula (const String &formula);

		const CtrlrMidiMessageEx &getMidiMessageEx(const int index) const									{ return (messageArray.getReference(index)); }
		const String toString() const;
		CtrlrMidiMessageType getMidiMessageType() const;
		virtual void setMidiMessageType (const CtrlrMidiMessageType newType);

		void restoreState (const ValueTree &stateTree);
		ValueTree &getMidiTree()																		{ return (midiTree); }

		void setProperty (const Identifier& name, const var &newValue, const bool isUndoable=false)		{ midiTree.setProperty (name, newValue, nullptr); }
		const var &getProperty (const Identifier& name) const											{ return midiTree.getProperty (name); }
		const var getProperty (const Identifier& name, const var &defaultReturnValue) const				{ return midiTree.getProperty (name, defaultReturnValue); }
		virtual void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
		void valueTreeChildrenChanged (ValueTree &/*treeWhoseChildHasChanged*/){}
		void valueTreeParentChanged (ValueTree &/*treeWhoseParentHasChanged*/){}
		void valueTreeChildAdded (ValueTree& /*parentTree*/, ValueTree& /*childWhichHasBeenAdded*/){}
		void valueTreeChildRemoved (ValueTree& /*parentTree*/, ValueTree& /*childWhichHasBeenRemoved*/, int){}
		void valueTreeChildOrderChanged (ValueTree& /*parentTreeWhoseChildrenHaveMoved*/, int, int){}
		void setNumberToSingle (const int index, const int number);
		void setValueToSingle (const int index, const int value);
		void setNumberToMulti (const int number);
		void setValueToMulti (const int value);
		void setMultiMessageFromString (const String &savedState);
		void addMidiMessage (const MidiMessage &message);
		void sortMidiArray() { messageArray.sort(timestampComparator); }
		MidiBuffer getMidiBuffer(const int startSample=1);
		void clear();
		virtual void patternChanged();
		void memoryMerge (const CtrlrMidiMessage &otherMessage);
		const MemoryBlock &getMidiPattern()	const;
		const LMemoryBlock getData() const;
		int getSize() const;
		CtrlrMidiMessageEx &getReference(const int messageIndex) const;
		Result fillMessagePropertiesFromData();
		Result fillMessagePropertiesFromData(const MemoryBlock &data);
		Result fillMessagePropertiesFromJuceMidi(const MidiMessage &m);
		Result getInitializationResult() { return (initializationResult); }
		void initializeEmptyMessage();
		Array <CtrlrMidiMessageEx> &getMidiMessageArray();

		virtual const Array<int,CriticalSection> &getGlobalVariables()
		{
			return (emptyGlobals);
		}

		virtual CtrlrSysexProcessor *getSysexProcessor() { return (nullptr); }
		ValueTree &getObjectTree() { return (midiTree); }

		static void wrapForLua (lua_State *L);

		JUCE_LEAK_DETECTOR(CtrlrMidiMessage)

	protected:
        CtrlrMidiMessage (const Identifier &treeType);
		ValueTree midiTree;
		Array <CtrlrMidiMessageEx> messageArray;

	private:
		Result initializationResult;
		bool restoring;
		Array<int,CriticalSection> emptyGlobals;
		StringPairArray multiTemplates;
		CtrlrMidiMessageType messageType;
		String messageTypeFromTemplate;
		String sysExFormula;
		int multiMasterValue, multiMasterNumber;
		MidiBuffer midiBuffer;
		MemoryBlock messagePattern;
		TimestampComparator timestampComparator;
};