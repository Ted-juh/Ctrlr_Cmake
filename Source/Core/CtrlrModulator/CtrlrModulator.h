#pragma once

#include "CtrlrMacros.h"
#include "CtrlrModulatorProcessor.h"
#include "CtrlrLuaObject.h"

typedef WeakReference <CtrlrModulator>							CtrlrModulatorReference;

#define EXP_MODULATOR_FORWARD		"modulatorValue"
#define EXP_MODULATOR_REVERSE		"midiValue"
#define EXP_MODULATOR_CONTROLLER    "value"

class CtrlrComponent;
class CtrlrManager;
class CtrlrPanel;
class CtrlrModulator;

/** @brief Class that represents a Ctrlr Modulator, this is the engine that runs under each	component on a panel. */

class CtrlrModulator : public ChangeBroadcaster, public ValueTree::Listener, public CtrlrLuaObject
{
	public:
		CtrlrModulator(CtrlrPanel &_owner);
		CtrlrModulator(CtrlrPanel &_owner, const int suggestedVstIndex);
		~CtrlrModulator();

		int getVstIndex() const;
		int getModulatorValue() const;
		int getValueMapped() const;
		int getValueNonMapped() const;
		int getMaxModulatorValue() const;
		int getMinModulatorValue() const;
		CtrlrComponent *getComponent();
		bool getRestoreState();
		void setValueMapped (const int newValue, const bool force, const bool mute=false);
		void setValueMappedCompat (const int newValue, const bool force);
		void setValueNonMapped (const int newValue, const bool force, const bool mute=false);
		CtrlrMidiMessage &getMidiMessage(const CtrlrMIDIDeviceType source);
		CtrlrMidiMessage &getMidiMessage();
		void setValue(const int newValue, const bool force=false, const bool mute=false);
		void setValue(const int newValue, const bool force=false);
		void setRestoreState(const bool _restoreState);
		int getMaxMapped();
		int getMaxNonMapped();
		int getMinMapped();
		int getMinNonMapped();

		class ModulatorListener
		{
			public:
				virtual void modulatorChanged (CtrlrModulator *source, const int newModulatorValue)=0;
				virtual ~ModulatorListener() {}
		};



		const Identifier getComponentType();
		void setModulatorValue(const int newValue, bool vst, bool midi, bool ui);
		const String getName();
		bool hasName();
		const std::string getLuaName() { return (getName().toUTF8().getAddress()); }
		float getVstValue(const int intValueToUse=-1) const;
		CtrlrMidiMessage *getMidiMessagePtr(const CtrlrMIDIDeviceType source = inputDevice);
		void restoreState (const ValueTree &savedState);
		CtrlrManager &getCtrlrManagerOwner();
		void allModulatorsInitialized();
		CtrlrModulator* getReference();
		void setProperty (const Identifier& name, const var &newValue, const bool isUndoable=false);
		void removeProperty(const Identifier& name);
		const String getModulatorText();
		void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
		void valueTreeChildrenChanged (ValueTree &/*treeWhoseChildHasChanged*/){}
		void valueTreeParentChanged (ValueTree &/*treeWhoseParentHasChanged*/){}
		void valueTreeChildAdded (ValueTree& /*parentTree*/, ValueTree& /*childWhichHasBeenAdded*/){}
		void valueTreeChildRemoved (ValueTree& /*parentTree*/, ValueTree& /*childWhichHasBeenRemoved*/, int){}
		void valueTreeChildOrderChanged (ValueTree& /*parentTreeWhoseChildrenHaveMoved*/, int, int){}
		void setComponentType (const Identifier &componentType, const bool forceIfAlreadyThisType=false);
		void setComponentType (const ValueTree &savedState);
		void setMidiType (const ValueTree &savedState);
		void modifyReference(const int newValue);
		void setReference (const String &modulatorToReference);
		void setPanelReference(CtrlrPanel *referencedPanel);
		bool isDelayedProperty(const Identifier &name);
		void setDelayedProperty(const Identifier &name, const var value);
		CtrlrOwnedMidiMessage &getOwnedMidiMessage(const CtrlrMIDIDeviceType idx = inputDevice);
		static void wrapForLua (lua_State *L);
		ValueTree &getObjectTree()																		{ return (modulatorTree); }
		ValueTree &getModulatorTree()																	{ return (modulatorTree); }
		const var &getProperty (const Identifier& name) const											{ return (modulatorTree.getProperty (name)); }
		bool hasProperty(const Identifier& name) const											{ return (modulatorTree.hasProperty (name)); }
		const var getProperty (const Identifier& name, const var &defaultReturnValue) const				{ return modulatorTree.getProperty (name, defaultReturnValue); }
		CtrlrPanel &getOwnerPanel()																			{ return (owner); }
		CtrlrModulatorProcessor &getProcessor()															{ return (processor); }
		void addModulatorListener (ModulatorListener *l)													{ modulatorListeners.add(l); }
		void removeModulatorListener (ModulatorListener *l)													{ modulatorListeners.remove(l); }
		bool isExportedToVst()																		{ return (vstExported); }
		bool isStatic();
		const String getNameForHost();
		const String getTextForHost();
		const String getGroupName();

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CtrlrModulator)

	private:
		ReadWriteLock modulatorLock;
		bool restoreStateStatus;
		bool removeComponent();
		friend class WeakReference<CtrlrModulator>;
		WeakReference<CtrlrModulator>::Master masterReference;
		WeakReference<CtrlrModulator> ctrlrModulatorReference;
		WeakReference<CtrlrPanel> ctrlrPanelReference;
		uint32 vstIndex;
		CtrlrComponent *ctrlrComponent;
		CtrlrPanel &owner;
		ValueTree modulatorTree;
		ValueTree delayedProperties;
		CtrlrModulatorProcessor processor;
		ListenerList <ModulatorListener> modulatorListeners;
		bool vstExported;
};
