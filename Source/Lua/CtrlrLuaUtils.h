#pragma once

#ifdef _WIN32
#pragma warning(disable:4100)
#endif // _WIN32

#include "CtrlrMacros.h"
#include "CtrlrRevision.h"
#include "luabind/object_fwd.hpp"

extern "C"
{
	#include "lua.h"
}

class LMemoryBlock;

class CtrlrLuaUtils
{
	public:
		static void wrapForLua(lua_State *L);
		static LMemoryBlock *unpackDsiData (MemoryBlock &dataToUnpack);
		static LMemoryBlock *packDsiData (MemoryBlock &dataToUnpack);
		static void warnWindow (const String title, const String message);
		static void infoWindow (const String title, const String message);
		static bool questionWindow (const String title, const String message, const String button1Text, const String button2Text);
		static String askForTextInputWindow (const String title, const String message, const String initialInputContent,
											const String onScreenLabel, const bool isPassword, const String button1Text,
											const String button2Text);
		static File openFileWindow (const String &dialogBoxTitle, const File &initialFileOrDirectory,
									const String &filePatternsAllowed, bool useOSNativeDialogBox);
		void openMultipleFilesWindow(const String &dialogBoxTitle, const File &initialFileOrDirectory,
									const String &filePatternsAllowed, bool useOSNativeDialogBox,
									luabind::object const& table);
		static File saveFileWindow(const String &dialogBoxTitle, const File &initialFileOrDirectory,
									const String &filePatternsAllowed, bool useOSNativeDialogBox);
		static File getDirectoryWindow(const String &dialogBoxTitle, const File &initialFileOrDirectory);

        static int getVersionMajor() { return (_STR(ctrlrRevision).upToFirstOccurrenceOf(".", false, true).getIntValue()); }
        static int getVersionMinor() { return (_STR(ctrlrRevision).fromFirstOccurrenceOf(".", false, true).getIntValue()); }
        static int getVersionRevision() { return (_STR(ctrlrRevision).fromLastOccurrenceOf(".", false, true).getIntValue()); }
        static double getPi() { return (double_Pi); }
        static String getVersionString() { return (_STR(ctrlrRevision)); }
		static StringArray getMidiInputDevices();
		static StringArray getMidiOutputDevices();
		void testMethod(const String &haystack, const String &needle);

		JUCE_LEAK_DETECTOR(CtrlrLuaUtils)
};