cmake_minimum_required(VERSION 3.23)

if(APPLE)
	set(CMAKE_OSX_DEPLOYMENT_TARGET 10.15 CACHE STRING "")
	set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE STRING "Build architectures for Mac OS X" FORCE)
elseif(MSVC)
add_compile_options(/wd4206)
endif()

project(Ctrlr VERSION 5.6.23)
set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_MODULE_PATH
	${CMAKE_SOURCE_DIR}/cmake
	${CMAKE_SOURCE_DIR}/config
	${CMAKE_SOURCE_DIR}/config/platform
)

add_subdirectory(JUCE)

if (APPLE)
	juce_set_vst2_sdk_path(Source/Misc/vst2sdk)
elseif(UNIX)
	juce_set_vst2_sdk_path(Source/Misc/vst2sdk)
elseif(WIN32)
	juce_set_vst2_sdk_path(Source/Misc/vst2sdk)
endif(APPLE)

juce_add_plugin(Ctrlr
	PRODUCT_NAME 				    "Ctrlr"									# The name of the output built by this target.
	VERSION						    5.6.23									# Version number in the format: "major, minor, bugfix"
	COMPANY_NAME 					"Instigator"							# The name of the company that owns this product.		
	COMPANY_WEBSITE 				"https://ctrlr.org"						# The website of the company that owns this product.

	DOCUMENT_EXTENSIONS 			.panel .exe .vst3. .vst .au				# The file extensions that this plugin can open.
	ICON_BIG						"Source/Resources/Icons/ctrlr_logo.svg" # The icon file for the plugin.

	IS_SYNTH 						TRUE									# Is this a synth or an effect?
	NEEDS_MIDI_INPUT				TRUE									# Does this plugin need MIDI input?
	NEEDS_MIDI_OUTPUT				TRUE									# Does this plugin produce MIDI output?				
	IS_MIDI_EFFECT					TRUE									# Is this a MIDI effect?
	EDITOR_WANTS_KEYBOARD_FOCUS		TRUE									# Does the editor need keyboard focus?

	FORMATS							VST3 Standalone VST						# The formats that this plugin can be built for.
	VST2_CATEGORY 				    kPlugCategSynth							# The VST2 category for the plugin					
	VST3_CATEGORY    		        Instrument Synth						# The VST3 category for the plugin
	VS_COPY_TO_OUT_DIR				TRUE									# Copy the VST3 to the output directory?
	VST3_COPY_DIR 					"${PROJECT_BINARY_DIR}/VST3"			# The directory to copy the VST3 to.
	VST3_AUTO_MANIFEST 				FALSE									# Automatically generate the VST3 manifest?
	VST_NUM_MIDI_INPUTS 	        16										# The number of MIDI inputs for the VST
	VST_NUM_MIDI_OUTPUTS 	        16										# The number of MIDI outputs for the VST

	PLUGIN_NAME 					Ctrlr									# The name of the plugin when loaded into a DAW
	DESCRIPTION 					Ctrlr									# A short description of the plugin
	PLUGIN_MANUFACTURER_CODE 		inSt									# A four-character unique ID for your company. Wise: First letter to be uppercase
	PLUGIN_CODE 					cTrl									# A four-character unique ID for this plugin. Wise: First letter to be uppercase
	BUNDLE_ID        			    "com.instigator.Ctrlr"					# An identifier string in the form "com.yourcompany.productname" which should uniquely identify this target.

	AU_EXPORT_PREFIX         	    "AU"									# The prefix for the AudioUnit name
	AU_MAIN_TYPE 				    kAudioUnitType_MusicDevice				# The main type for the AudioUnit
	AU_SANDBOX_SAFE 			    TRUE									# Is the AudioUnit sandbox safe?				
	PLUGINHOST_AU 				    TRUE									# Is this plugin an AudioUnit?
	SUPPRESS_AU_PLIST_RESOURCE_USAGE TRUE									# Suppress the AU plist resource usage warning?
 				
	#INCLUDE_BINARYDATA 			    TRUE
	DISPLAY_THE_JUCE_SPLASH_SCREEN  TRUE
	SPLASH_SCREEN_COLOUR 		    Light
)

target_precompile_headers(Ctrlr
	PUBLIC
	Source/Core/stdafx.h
	Source/Core/stdafx_luabind.h
)

foreach(file ${SOURCE_FILES})
    if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${file}")
        message(WARNING "Source file \"${CMAKE_CURRENT_SOURCE_DIR}/${file}\" does not exist.")
    endif()
endforeach()

target_sources(Ctrlr
	PRIVATE

	JuceLibraryCode/BinaryData.cpp

	# Source files	\Core
	Source/Core/CtrlrFontManager.cpp
	Source/Core/CtrlrFontManager.h
	Source/Core/CtrlrIDManager.cpp
	Source/Core/CtrlrIDManager.h
	Source/Core/CtrlrIDs.h
	Source/Core/CtrlrInlineUtilitiesGUI.h
	Source/Core/CtrlrLog.cpp
	Source/Core/CtrlrLog.h
	Source/Core/CtrlrMacros.h
	Source/Core/CtrlrMainPage.h
	Source/Core/CtrlrProperties.cpp
	Source/Core/CtrlrProperties.h
	Source/Core/CtrlrSysexProcessor.cpp
	Source/Core/CtrlrSysexProcessor.h
	Source/Core/CtrlrSysexProcessorOwned.cpp
	Source/Core/CtrlrSysexProcessorOwned.h
	Source/Core/CtrlrSysexToken.cpp
	Source/Core/CtrlrSysexToken.h
	Source/Core/CtrlrUtilities.cpp
	Source/Core/CtrlrUtilities.h
	Source/Core/CtrlrUtilitiesGUI.cpp
	Source/Core/CtrlrUtilitiesGUI.h
	Source/Core/dxtrans.h
	Source/Core/Stdafx.cpp
	Source/Core/Stdafx.h
	Source/Core/Stdafx_luabind.h
	Source/Core/Stdafx_luabind.cpp

	# Source files	\Core\CtrlrManager
	Source/Core/CtrlrManager/CtrlrManager.cpp
	Source/Core/CtrlrManager/CtrlrManager.h
	Source/Core/CtrlrManager/CtrlrManagerInstance.cpp
	Source/Core/CtrlrManager/CtrlrManagerVst.cpp
	Source/Core/CtrlrManager/CtrlrManagerVst.h

	# Source files	\Core\CtrlrModulator
	Source/Core/CtrlrModulator/CtrlrModulator.cpp
	Source/Core/CtrlrModulator/CtrlrModulator.h
	Source/Core/CtrlrModulator/CtrlrModulatorProcessor.cpp
	Source/Core/CtrlrModulator/CtrlrModulatorProcessor.h
	
	# Source files	\Core\CtrlrPanel
	Source/Core/CtrlrPanel/CtrlrEvaluationScopes.cpp
	Source/Core/CtrlrPanel/CtrlrEvaluationScopes.h
	Source/Core/CtrlrPanel/CtrlrPanel.cpp
	Source/Core/CtrlrPanel/CtrlrPanel.h
	Source/Core/CtrlrPanel/CtrlrPanelFileOperations.cpp
	Source/Core/CtrlrPanel/CtrlrPanelMIDIInputThread.cpp
	Source/Core/CtrlrPanel/CtrlrPanelMIDIInputThread.h
	Source/Core/CtrlrPanel/CtrlrPanelMIDISnapshot.cpp
	Source/Core/CtrlrPanel/CtrlrPanelMIDISnapshot.h
	Source/Core/CtrlrPanel/CtrlrPanelProcessor.cpp
	Source/Core/CtrlrPanel/CtrlrPanelProcessor.h
	Source/Core/CtrlrPanel/CtrlrPanelResource.cpp
	Source/Core/CtrlrPanel/CtrlrPanelResource.h
	Source/Core/CtrlrPanel/CtrlrPanelResourceManager.cpp
	Source/Core/CtrlrPanel/CtrlrPanelResourceManager.h
	Source/Core/CtrlrPanel/CtrlrPanelSchemeMigration.cpp
	Source/Core/CtrlrPanel/CtrlrPanelSchemeMigration.h
	Source/Core/CtrlrPanel/CtrlrPanelUndoManager.cpp
	Source/Core/CtrlrPanel/CtrlrPanelUndoManager.h
		
	# Source files	\Core\CtrlrPanel\CtrlrPanelEditor
	Source/Core/StandaloneWrapper/CtrlrStandaloneApplication.cpp
	Source/Core/StandaloneWrapper/CtrlrStandaloneWindow.cpp
	Source/Core/StandaloneWrapper/CtrlrStandaloneWindow.h

	# Source files	\Lua
	Source/Lua/CtrlrLuaAudioConverter.cpp
	Source/Lua/CtrlrLuaAudioConverter.h
	Source/Lua/CtrlrLuaConverters.h
	Source/Lua/CtrlrLuaDebugger.cpp
	Source/Lua/CtrlrLuaDebugger.h
	Source/Lua/CtrlrLuaManager.cpp
	Source/Lua/CtrlrLuaManager.h
	Source/Lua/CtrlrLuaMultiTimer.h
	Source/Lua/CtrlrLuaObject.cpp
	Source/Lua/CtrlrLuaObject.h
	Source/Lua/CtrlrLuaObjectWrapper.cpp
	Source/Lua/CtrlrLuaObjectWrapper.h
	Source/Lua/CtrlrLuaPanelCanvasLayer.cpp
	Source/Lua/CtrlrLuaUtils.cpp
	Source/Lua/CtrlrLuaUtils.h

	# Source files	\Lua\Deprecated
	Source/Lua/Deprecated/CtrlrLuaBigInteger.cpp
	Source/Lua/Deprecated/CtrlrLuaBigInteger.h
	Source/Lua/Deprecated/CtrlrLuaComponentAnimator.cpp
	Source/Lua/Deprecated/CtrlrLuaComponentAnimator.h
	Source/Lua/Deprecated/CtrlrLuaFile.cpp
	Source/Lua/Deprecated/CtrlrLuaFile.h
	Source/Lua/Deprecated/CtrlrLuaMemoryBlock.cpp
	Source/Lua/Deprecated/CtrlrLuaMemoryBlock.h
	Source/Lua/Deprecated/CtrlrLuaRectangle.cpp
	Source/Lua/Deprecated/CtrlrLuaRectangle.h

	# Source files	\Lua\JuceClasses
	Source/Lua/JuceClasses/LAffineTransform.h
	Source/Lua/JuceClasses/LAlertWindow.h
	Source/Lua/JuceClasses/LAsyncUpdater.h
	Source/Lua/JuceClasses/LAttributedString.h
	Source/Lua/JuceClasses/LAudio.cpp
	Source/Lua/JuceClasses/LAudioFile.h
	Source/Lua/JuceClasses/LAudioFormat.h
	Source/Lua/JuceClasses/LAudioPlayHead.h
	Source/Lua/JuceClasses/LAudioSampleBuffer.h
	Source/Lua/JuceClasses/LAudioThumbnail.h
	Source/Lua/JuceClasses/LBigInteger.h
	Source/Lua/JuceClasses/LBorderSize.h
	Source/Lua/JuceClasses/LBubbleMessageComponent.h
	Source/Lua/JuceClasses/LButton.h
	Source/Lua/JuceClasses/LColour.h
	Source/Lua/JuceClasses/LColourGradient.h
	Source/Lua/JuceClasses/LComboBox.h
	Source/Lua/JuceClasses/LComponent.h
	Source/Lua/JuceClasses/LComponentPeer.h
	Source/Lua/JuceClasses/LComponents.cpp
	Source/Lua/JuceClasses/LCore.cpp
	Source/Lua/JuceClasses/LDrawable.h
	Source/Lua/JuceClasses/LExpression.h
	Source/Lua/JuceClasses/Lfile.h
	Source/Lua/JuceClasses/LFileListComponent.h
	Source/Lua/JuceClasses/LFileTreeComponent.h
	Source/Lua/JuceClasses/LFont.h
	Source/Lua/JuceClasses/LGlobalFunctions.h
	Source/Lua/JuceClasses/LGlyphArrangement.h
	Source/Lua/JuceClasses/LGraphics.cpp
	Source/Lua/JuceClasses/LGraphics.h
	Source/Lua/JuceClasses/LImage.h
	Source/Lua/JuceClasses/LInputStream.h
	Source/Lua/JuceClasses/LJuce.cpp
	Source/Lua/JuceClasses/LJuce.h
	Source/Lua/JuceClasses/LJustification.h
	Source/Lua/JuceClasses/LKeyPress.h
	Source/Lua/JuceClasses/LLabel.h
	Source/Lua/JuceClasses/LLine.h
	Source/Lua/JuceClasses/LLookAndFeel.h
	Source/Lua/JuceClasses/LMemory.cpp
	Source/Lua/JuceClasses/LMemoryBlock.h
	Source/Lua/JuceClasses/LMemoryInputStream.h
	Source/Lua/JuceClasses/LMidiBuffer.h
	Source/Lua/JuceClasses/LMidiKeyboardComponent.h
	Source/Lua/JuceClasses/LMidiMessage.h
	Source/Lua/JuceClasses/LModifierKeys.h
	Source/Lua/JuceClasses/LMouseCursor.h
	Source/Lua/JuceClasses/LMouseEvent.h
	Source/Lua/JuceClasses/LMouseInputSource.h
	Source/Lua/JuceClasses/LPath.h
	Source/Lua/JuceClasses/LPoint.h
	Source/Lua/JuceClasses/LPopupMenu.h
	Source/Lua/JuceClasses/LRandom.h
	Source/Lua/JuceClasses/LRange.h
	Source/Lua/JuceClasses/LRectangle.h
	Source/Lua/JuceClasses/LRelativeCoordinate.h
	Source/Lua/JuceClasses/LResult.h
	Source/Lua/JuceClasses/LSlider.h
	Source/Lua/JuceClasses/LSparseSet.h
	Source/Lua/JuceClasses/LString.h
	Source/Lua/JuceClasses/LTextButton.h
	Source/Lua/JuceClasses/LTextEditor.h
	Source/Lua/JuceClasses/LThread.h
	Source/Lua/JuceClasses/LThreadWithProgressWindow.h
	Source/Lua/JuceClasses/LTime.h
	Source/Lua/JuceClasses/LTimer.h
	Source/Lua/JuceClasses/LToggleButton.h
	Source/Lua/JuceClasses/LTypeFace.h
	Source/Lua/JuceClasses/LURL.h
	Source/Lua/JuceClasses/LValue.h
	Source/Lua/JuceClasses/LValueTree.h
	Source/Lua/JuceClasses/LXmlElement.h
	Source/Lua/JuceClasses/LZipFile.h

	# Source files	\Lua\Methods
	Source/Lua/Methods/CtrlrLuaMethod.cpp
	Source/Lua/Methods/CtrlrLuaMethod.h
	Source/Lua/Methods/CtrlrLuaMethodManager.cpp
	Source/Lua/Methods/CtrlrLuaMethodManager.h
	Source/Lua/Methods/CtrlrLuaMethodManagerCalls.cpp

	# Source files	\MIDI
	Source/MIDI/CtrlrMIDIDevice.cpp
	Source/MIDI/CtrlrMIDIDevice.h
	Source/MIDI/CtrlrMIDIDeviceManager.cpp
	Source/MIDI/CtrlrMIDIDeviceManager.h
	Source/MIDI/CtrlrMIDIFilter.cpp
	Source/MIDI/CtrlrMIDIFilter.h
	Source/MIDI/CtrlrMidiInputComparator.cpp
	Source/MIDI/CtrlrMidiInputComparator.h
	Source/MIDI/CtrlrMidiInputComparatorMulti.cpp
	Source/MIDI/CtrlrMidiInputComparatorMulti.h
	Source/MIDI/CtrlrMidiInputComparatorSingle.cpp
	Source/MIDI/CtrlrMidiInputComparatorSingle.h
	Source/MIDI/CtrlrMidiMessage.cpp
	Source/MIDI/CtrlrMidiMessage.h
	Source/MIDI/CtrlrMidiMessageEx.cpp
	Source/MIDI/CtrlrMidiMessageEx.h
	Source/MIDI/CtrlrOwnedMidiMessage.cpp
	Source/MIDI/CtrlrOwnedMidiMessage.h

	# Source files	\MIDI\CtrlrMidiLibrary
	Source/Midi/CtrlrMidiLibrary/CtrlrMidiLibrary.h

	# Source files	\Misc
	Source/Misc/libr.c
	Source/Misc/libr-bfd.c
	Source/Misc/keys.cpp

	# Source files	\Misc\libusb
	Source/Misc/libusb/src/compat.c
	Source/Misc/libusb/src/core.c
	Source/Misc/libusb/src/darwin_usb.c
	Source/Misc/libusb/src/descriptor.c
	Source/Misc/libusb/src/enums.c
	Source/Misc/libusb/src/hotplug.c
	Source/Misc/libusb/src/io.c
	Source/Misc/libusb/src/linux_udev.c
	Source/Misc/libusb/src/linux_usbfs.c
	Source/Misc/libusb/src/poll_posix.c
	Source/Misc/libusb/src/poll_windows.c
	Source/Misc/libusb/src/strerror.c
	Source/Misc/libusb/src/structs.c
	Source/Misc/libusb/src/sync.c
	Source/Misc/libusb/src/threads_posix.c
	Source/Misc/libusb/src/threads_windows.c
	Source/Misc/libusb/src/usb.c
	Source/Misc/libusb/src/windows_usb.c

	# Source files	\Misc\lua
	Source/Misc/lua/src/lua.c

	# Source files	\Misc\luabind
	Source/Misc/luabind/src/class.cpp
	Source/Misc/luabind/src/class_info.cpp
	Source/Misc/luabind/src/class_registry.cpp
	Source/Misc/luabind/src/class_rep.cpp
	Source/Misc/luabind/src/create_class.cpp
	Source/Misc/luabind/src/error.cpp
	Source/Misc/luabind/src/exception_handler.cpp
	Source/Misc/luabind/src/function.cpp
	Source/Misc/luabind/src/function_introspection.cpp
	Source/Misc/luabind/src/inheritance.cpp
	Source/Misc/luabind/src/link_compatibility.cpp
	Source/Misc/luabind/src/lua51compat.cpp
	Source/Misc/luabind/src/object_rep.cpp
	Source/Misc/luabind/src/open.cpp
	Source/Misc/luabind/src/operator.cpp
	Source/Misc/luabind/src/pcall.cpp
	Source/Misc/luabind/src/scope.cpp
	Source/Misc/luabind/src/set_package_preload.cpp
	Source/Misc/luabind/src/shared_ptr_converter.cpp
	Source/Misc/luabind/src/stack_content_by_name.cpp
	Source/Misc/luabind/src/weak_ref.cpp
	Source/Misc/luabind/src/wrapper_base.cpp

	# Source files	\Native
	Source/Native/CtrlrGeneric.h
	Source/Native/CtrlrLinux.cpp
	Source/Native/CtrlrLinux.h	
	Source/Native/CtrlrMac.cpp
	Source/Native/CtrlrMac.h
	Source/Native/CtrlrNative.h
	Source/Native/CtrlrNative.cpp
	Source/Native/CtrlrWindows.cpp
	Source/Native/CtrlrWindows.h

	# Source files	\Plugin
	Source/Plugin/CtrlrProcessor.cpp
	Source/Plugin/CtrlrProcessor.h
	Source/Plugin/CtrlrProcessorEditorForLive.cpp
	Source/Plugin/CtrlrProcessorEditorForLive.h

	# Source files	\UIComponents
	Source/UIComponents/CtrlrAbout.cpp
	Source/UIComponents/CtrlrAbout.h
	Source/UIComponents/CtrlrComponentSelection.cpp
	Source/UIComponents/CtrlrComponentSelection.h
	Source/UIComponents/CtrlrLogViewer.cpp
	Source/UIComponents/CtrlrLogViewer.h
	Source/UIComponents/CtrlrTextEditor.cpp
	Source/UIComponents/CtrlrTextEditor.h
	Source/UIComponents/CtrlrValueMap.cpp
	Source/UIComponents/CtrlrValueMap.h
	Source/UIComponents/CtrlrValueTreeEditor.cpp
	Source/UIComponents/CtrlrValueTreeEditor.h
	
	# Source files	\UIComponents\CtrlrApplicationWindow
	Source/UIComponents/CtrlrApplicationWindow/CtrlrDocumentPanel.cpp
	Source/UIComponents/CtrlrApplicationWindow/CtrlrDocumentPanel.h
	Source/UIComponents/CtrlrApplicationWindow/CtrlrEditor.cpp
	Source/UIComponents/CtrlrApplicationWindow/CtrlrEditor.h
	Source/UIComponents/CtrlrApplicationWindow/CtrlrEditorApplicationCommands.cpp
	Source/UIComponents/CtrlrApplicationWindow/CtrlrEditorApplicationCommandsHandlers.cpp
	Source/UIComponents/CtrlrApplicationWindow/CtrlrEditorApplicationCommandsMenus.cpp
	Source/UIComponents/CtrlrApplicationWindow/CtrlrSettings.cpp
	Source/UIComponents/CtrlrApplicationWindow/CtrlrSettings.h

	# Source files	\UIComponents\CtrlrBuildScript
	Source/UIComponents/CtrlrBuildScript/CtrlrBuildScriptMain.cpp
	Source/UIComponents/CtrlrBuildScript/CtrlrBuildScriptMain.h
	Source/UIComponents/CtrlrBuildScript/CtrlrBuildScriptIDEsection.cpp
	Source/UIComponents/CtrlrBuildScript/CtrlrBuildScriptIDEsection.h
	Source/UIComponents/CtrlrBuildScript/CtrlrBuildScriptOptionsSection.cpp
	Source/UIComponents/CtrlrBuildScript/CtrlrBuildScriptOptionsSection.h
	Source/UIComponents/CtrlrBuildScript/CtrlrBuildScriptOutputSection.cpp
	Source/UIComponents/CtrlrBuildScript/CtrlrBuildScriptOutputSection.h
	Source/UIComponents/CtrlrBuildScript/CtrlrBuildScriptVST3Section.cpp
	Source/UIComponents/CtrlrBuildScript/CtrlrBuildScriptVST3Section.h

	# Source files	\UIComponents\CtrlrComponents
	Source/UIComponents/CtrlrComponents/CtrlrCombo.cpp
	Source/UIComponents/CtrlrComponents/CtrlrCombo.h
	Source/UIComponents/CtrlrComponents/CtrlrComponent.cpp
	Source/UIComponents/CtrlrComponents/CtrlrComponent.h
	Source/UIComponents/CtrlrComponents/CtrlrComponentLuaRegistration.cpp
	Source/UIComponents/CtrlrComponents/CtrlrComponentTypeManager.cpp
	Source/UIComponents/CtrlrComponents/CtrlrComponentTypeManager.h
	Source/UIComponents/CtrlrComponents/CtrlrCustomComponent.cpp
	Source/UIComponents/CtrlrComponents/CtrlrCustomComponent.h
	Source/UIComponents/CtrlrComponents/CtrlrFilmStripPainter.cpp
	Source/UIComponents/CtrlrComponents/CtrlrFilmStripPainter.h

	# Source files	\UIComponents\CtrlrComponents\Statics
	Source/UIComponents/CtrlrComponents/Statics/CtrlrArrow.cpp
	Source/UIComponents/CtrlrComponents/Statics/CtrlrArrow.h

	# Source files	\UIComponents\CtrlrComponents\Specials
	Source/UIComponents/CtrlrComponents/Specials/CtrlrFileListBox.cpp
	Source/UIComponents/CtrlrComponents/Specials/CtrlrFileListBox.h
	Source/UIComponents/CtrlrComponents/Specials/CtrlrListBox.cpp
	Source/UIComponents/CtrlrComponents/Specials/CtrlrListBox.h
	Source/UIComponents/CtrlrComponents/Specials/CtrlrMidiKeyboard.cpp
	Source/UIComponents/CtrlrComponents/Specials/CtrlrMidiKeyboard.h
	Source/UIComponents/CtrlrComponents/Specials/CtrlrProgressBar.cpp
	Source/UIComponents/CtrlrComponents/Specials/CtrlrProgressBar.h
	Source/UIComponents/CtrlrComponents/Specials/CtrlrWaveform.cpp
	Source/UIComponents/CtrlrComponents/Specials/CtrlrWaveform.h
	Source/UIComponents/CtrlrComponents/Specials/CtrlrXYModulator.cpp
	Source/UIComponents/CtrlrComponents/Specials/CtrlrXYModulator.h
	Source/UIComponents/CtrlrComponents/Specials/CtrlrXYSurface.cpp
	Source/UIComponents/CtrlrComponents/Specials/CtrlrXYSurface.h

	# Source files	\UIComponents\CtrlrComponents\Sliders
	Source/UIComponents/CtrlrComponents/Sliders/CtrlrFixedImageSlider.cpp
	Source/UIComponents/CtrlrComponents/Sliders/CtrlrFixedImageSlider.h
	Source/UIComponents/CtrlrComponents/Sliders/CtrlrFixedSlider.cpp
	Source/UIComponents/CtrlrComponents/Sliders/CtrlrFixedSlider.h
	Source/UIComponents/CtrlrComponents/Sliders/CtrlrImageSlider.cpp
	Source/UIComponents/CtrlrComponents/Sliders/CtrlrImageSlider.h
	Source/UIComponents/CtrlrComponents/Sliders/CtrlrSlider.cpp
	Source/UIComponents/CtrlrComponents/Sliders/CtrlrSlider.h
	Source/UIComponents/CtrlrComponents/Sliders/CtrlrSliderInternal.cpp
	Source/UIComponents/CtrlrComponents/Sliders/CtrlrSliderInternal.h

	# Source files	\UIComponents\CtrlrComponents\Labels
	Source/UIComponents/CtrlrComponents/Labels/CtrlrImage.cpp
	Source/UIComponents/CtrlrComponents/Labels/CtrlrImage.h
	Source/UIComponents/CtrlrComponents/Labels/CtrlrLabel.cpp
	Source/UIComponents/CtrlrComponents/Labels/CtrlrLabel.h
	Source/UIComponents/CtrlrComponents/Labels/CtrlrLCDLabel.cpp
	Source/UIComponents/CtrlrComponents/Labels/CtrlrLCDLabel.h

	# Source files	\UIComponents\CtrlrComponents\Groups
	Source/UIComponents/CtrlrComponents/Groups/CtrlrGroup.cpp
	Source/UIComponents/CtrlrComponents/Groups/CtrlrGroup.h
	Source/UIComponents/CtrlrComponents/Groups/CtrlrTabsComponent.cpp
	Source/UIComponents/CtrlrComponents/Groups/CtrlrTabsComponent.h

	# Source files	\UIComponents\CtrlrComponents\Buttons
	Source/UIComponents/CtrlrComponents/Buttons/CtrlrButton.cpp
	Source/UIComponents/CtrlrComponents/Buttons/CtrlrButton.h
	Source/UIComponents/CtrlrComponents/Buttons/CtrlrCustomButtonInternal.cpp
	Source/UIComponents/CtrlrComponents/Buttons/CtrlrCustomButtonInternal.h
	Source/UIComponents/CtrlrComponents/Buttons/CtrlrHyperlink.cpp
	Source/UIComponents/CtrlrComponents/Buttons/CtrlrHyperlink.h
	Source/UIComponents/CtrlrComponents/Buttons/CtrlrImageButton.cpp
	Source/UIComponents/CtrlrComponents/Buttons/CtrlrImageButton.h
	Source/UIComponents/CtrlrComponents/Buttons/CtrlrToggleButton.cpp
	Source/UIComponents/CtrlrComponents/Buttons/CtrlrToggleButton.h

	# Source files	\UIComponents\CtrlrLua
	Source/UIComponents/CtrlrLua/CtrlrLuaConsole.cpp
	Source/UIComponents/CtrlrLua/CtrlrLuaConsole.h

	# Source files	\UIComponents\CtrlrLua\MethodEditor
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaCodeTokeniser.cpp
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaCodeTokeniser.h
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaCodeTokeniserFunctions.h
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodCodeEditor.cpp
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodCodeEditor.h
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodCodeEditorSettings.cpp
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodCodeEditorSettings.h
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodDebuggerControls.cpp
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodDebuggerControls.h
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodDebuggerInfo.cpp
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodDebuggerInfo.h
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodDebuggerPrompt.cpp
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodDebuggerPrompt.h
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodDebuggerStackTrace.cpp
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodDebuggerStackTrace.h
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodDebuggerVars.cpp
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodDebuggerVars.h
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodEditArea.cpp
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodEditArea.h
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodEditorConsole.cpp
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodEditorConsole.h
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodEditor.cpp
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodEditor.h
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodEditorTabs.cpp
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodEditorTabs.h
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodFind.cpp
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodFind.h
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrMethodEditorTabCloseButton.cpp
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrMethodEditorTabCloseButton.h

	# Source files	\UIComponents\CtrlrMIDI
	Source/UIComponents/CtrlrMIDI/CtrlrMIDIBuffer.cpp
	Source/UIComponents/CtrlrMIDI/CtrlrMIDIBuffer.h
	Source/UIComponents/CtrlrMidi/CtrlrMidiBufferEditor.cpp
	Source/UIComponents/CtrlrMidi/CtrlrMidiBufferEditor.h
	Source/UIComponents/CtrlrMIDI/CtrlrMIDICalculator.cpp
	Source/UIComponents/CtrlrMIDI/CtrlrMIDICalculator.h
	Source/UIComponents/CtrlrMIDI/CtrlrMIDIMon.cpp
	Source/UIComponents/CtrlrMIDI/CtrlrMIDIMon.h
	Source/UIComponents/CtrlrMIDI/CtrlrMIDISettingsDevices.cpp
	Source/UIComponents/CtrlrMIDI/CtrlrMIDISettingsDevices.h
	Source/UIComponents/CtrlrMIDI/CtrlrMIDISettingsDialog.cpp
	Source/UIComponents/CtrlrMIDI/CtrlrMIDISettingsDialog.h
	Source/UIComponents/CtrlrMIDI/CtrlrMIDISettingsRouting.cpp
	Source/UIComponents/CtrlrMIDI/CtrlrMIDISettingsRouting.h

	# Source files	\UIComponents\CtrlrPanel
	Source/UIComponents/CtrlrPanel/CtrlrPanelCanvas.cpp
	Source/UIComponents/CtrlrPanel/CtrlrPanelCanvas.h
	Source/UIComponents/CtrlrPanel/CtrlrPanelCanvasHandlers.cpp
	Source/UIComponents/CtrlrPanel/CtrlrPanelCanvasLayer.cpp
	Source/UIComponents/CtrlrPanel/CtrlrPanelCanvasLayer.h
	Source/UIComponents/CtrlrPanel/CtrlrPanelCanvasLayers.cpp
	Source/UIComponents/CtrlrPanel/CtrlrPanelComponentProperties.cpp
	Source/UIComponents/CtrlrPanel/CtrlrPanelComponentProperties.h
	Source/UIComponents/CtrlrPanel/CtrlrPanelEditor.cpp
	Source/UIComponents/CtrlrPanel/CtrlrPanelEditor.h
	Source/UIComponents/CtrlrPanel/CtrlrPanelFindProperty.cpp
	Source/UIComponents/CtrlrPanel/CtrlrPanelFindProperty.h
	Source/UIComponents/CtrlrPanel/CtrlrPanelLayerList.cpp
	Source/UIComponents/CtrlrPanel/CtrlrPanelLayerList.h
	Source/UIComponents/CtrlrPanel/CtrlrPanelLayerListItem.cpp
	Source/UIComponents/CtrlrPanel/CtrlrPanelLayerListItem.h
	Source/UIComponents/CtrlrPanel/CtrlrPanelModulatorList.cpp
	Source/UIComponents/CtrlrPanel/CtrlrPanelModulatorList.h
	Source/UIComponents/CtrlrPanel/CtrlrPanelModulatorListTree.cpp
	Source/UIComponents/CtrlrPanel/CtrlrPanelModulatorListTree.h
	Source/UIComponents/CtrlrPanel/CtrlrPanelProperties.cpp
	Source/UIComponents/CtrlrPanel/CtrlrPanelProperties.h
	Source/UIComponents/CtrlrPanel/CtrlrPanelResourceEditor.cpp
	Source/UIComponents/CtrlrPanel/CtrlrPanelResourceEditor.h
	Source/UIComponents/CtrlrPanel/CtrlrPanelUtilities.cpp
	Source/UIComponents/CtrlrPanel/CtrlrPanelUtilities.h
	Source/UIComponents/CtrlrPanel/CtrlrPanelViewport.cpp
	Source/UIComponents/CtrlrPanel/CtrlrPanelViewport.h
	Source/UIComponents/CtrlrPanel/CtrlrViewport.cpp
	Source/UIComponents/CtrlrPanel/CtrlrViewport.h

	# Source files	\UIComponents\CtrlrPropertyEditors
	Source/UIComponents/CtrlrPropertyEditors/CtrlrPropertyComponent.cpp
	Source/UIComponents/CtrlrPropertyEditors/CtrlrPropertyComponent.h

	# Source files	\UIComponents\CtrlrWindowManagers
	Source/UIComponents/CtrlrWindowManagers/CtrlrChildWindow.cpp
	Source/UIComponents/CtrlrWindowManagers/CtrlrChildWindow.h
	Source/UIComponents/CtrlrWindowManagers/CtrlrChildWindowContainer.cpp
	Source/UIComponents/CtrlrWindowManagers/CtrlrChildWindowContainer.h
	Source/UIComponents/CtrlrWindowManagers/CtrlrChildWindowContent.cpp
	Source/UIComponents/CtrlrWindowManagers/CtrlrChildWindowContent.h
	Source/UIComponents/CtrlrWindowManagers/CtrlrDialogWindow.cpp
	Source/UIComponents/CtrlrWindowManagers/CtrlrDialogWindow.h
	Source/UIComponents/CtrlrWindowManagers/CtrlrManagerWindowManager.cpp
	Source/UIComponents/CtrlrWindowManagers/CtrlrManagerWindowManager.h
	Source/UIComponents/CtrlrWindowManagers/CtrlrPanelWindowManager.cpp
	Source/UIComponents/CtrlrWindowManagers/CtrlrPanelWindowManager.h
)

file(GLOB_RECURSE SOURCE_FILES Source/*)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Source PREFIX "Source Files" FILES ${SOURCE_FILES})

file(GLOB_RECURSE JUCE_FILES JUCE/*)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/JUCE PREFIX "JUCE" FILES ${JUCE_FILES})

#target_compile_options(Ctrlr PUBLIC "-w")

target_compile_definitions(Ctrlr
	PRIVATE
	JUCE_WEB_BROWSER=0
	JUCE_USE_CURL=0
	JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:Ctrlr,JUCE_PRODUCT_NAME>"
	JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:Ctrlr,JUCE_VERSION>"
	JUCE_VST3_CAN_REPLACE_VST2=0
	JUCE_USE_CUSTOM_PLUGIN_STANDALONE_APP=1
	JUCE_DISPLAY_SPLASH_SCREEN=1
    JUCE_REPORT_APP_USAGE=0
    JUCE_USE_DARK_SPLASH_SCREEN=0
    JUCE_ALLOW_STATIC_NULL_VARIABLES=0
    JUCE_STRICT_REFCOUNTEDPOINTER=0
)

target_include_directories(Ctrlr
	PUBLIC
	Source/Misc/lua/include
	Source/Misc/luabind
	Source/Misc/boost
	Source/Misc
	Source/Misc/include
	Source/Misc/libusb/include
	Source/Core
	Source/MIDI
	Source/Lua
	Source/UIComponents
	Source/Plugin
	Source/
	include
	JuceLibraryCode
	${CMAKE_CURRENT_BINARY_DIR}
)

if(UNIX AND NOT APPLE)
	list(APPEND ctrlrLibs "X11")
	list(APPEND ctrlrLibs "z")
	list(APPEND ctrlrLibs "udev")
	list(APPEND ctrlrLibs "bfd")
endif()

target_link_libraries(Ctrlr
		PRIVATE						# Those libraries are linked to the target, they are not included when other targets link to this target. 
									# They are used only by this target.This is useful for libraries that are used only by the target and not by other targets that link to this target.
			juce::juce_gui_extra
			juce::juce_audio_basics
			juce::juce_audio_devices
			juce::juce_audio_formats
			juce::juce_audio_processors
			juce::juce_audio_utils
			${ctrlrLibs}
		PUBLIC						# Those libraries are linked to the target, they are included when other targets link to this target. 
									# They are used by this target and by other targets that link to this target.

			juce::juce_recommended_config_flags
			juce::juce_recommended_lto_flags
			juce::juce_recommended_warning_flags
	)

set_source_files_properties(
	JUCE/modules/juce_gui_extra/juce_gui_extra.cpp
	JUCE/modules/juce_gui_extra/juce_gui_extra.mm
	JUCE/modules/juce_gui_basics/juce_gui_basics.cpp
	JUCE/modules/juce_gui_basics/juce_gui_basics.mm
	JUCE/modules/juce_graphics/juce_graphics.cpp
	JUCE/modules/juce_graphics/juce_graphics.mm
	JUCE/modules/juce_events/juce_events.cpp
	JUCE/modules/juce_events/juce_events.mm
	JUCE/modules/juce_core/juce_core.cpp
	JUCE/modules/juce_core/juce_core.mm
	JUCE/modules/juce_data_structures/juce_data_structures.cpp
	JUCE/modules/juce_data_structures/juce_data_structures.mm
	JUCE/modules/juce_audio_basics/juce_audio_basics.cpp
	JUCE/modules/juce_audio_basics/juce_audio_basics.mm
	JUCE/modules/juce_audio_devices/juce_audio_devices.cpp
	JUCE/modules/juce_audio_devices/juce_audio_devices.mm
	JUCE/modules/juce_audio_formats/juce_audio_formats.cpp
	JUCE/modules/juce_audio_formats/juce_audio_formats.mm
	JUCE/modules/juce_audio_processors/juce_audio_processors.cpp
	JUCE/modules/juce_audio_processors/juce_audio_processors.mm
	JUCE/modules/juce_audio_utils/juce_audio_utils.cpp
	JUCE/modules/juce_audio_utils/juce_audio_utils.mm
	JUCE/modules/juce_audio_plugin_client/VST/juce_VST_Wrapper.cpp
	JUCE/modules/juce_audio_plugin_client/VST/juce_VST_Wrapper.mm
	JUCE/modules/juce_audio_plugin_client/juce_audio_plugin_client_VST2.cpp
	JUCE/modules/juce_audio_plugin_client/VST3/juce_VST3_Wrapper.cpp
	JUCE/modules/juce_audio_plugin_client/VST3/juce_VST3_Wrapper.mm
	JUCE/modules/juce_audio_plugin_client/juce_audio_plugin_client_AAX.mm
	JUCE/modules/juce_audio_plugin_client/juce_audio_plugin_client_RTAS_3.cpp
	JUCE/modules/juce_audio_plugin_client/juce_audio_plugin_client_VST3.cpp
	JUCE/modules/juce_audio_plugin_client/juce_audio_plugin_client_Unity.cpp
	JUCE/modules/juce_audio_plugin_client/juce_audio_plugin_client_Standalone.cpp
	JUCE/modules/juce_audio_plugin_client/juce_audio_plugin_client_RTAS_4.cpp
	JUCE/modules/juce_audio_plugin_client/juce_audio_plugin_client_RTAS_2.cpp
	JUCE/modules/juce_audio_plugin_client/juce_audio_plugin_client_RTAS_1.cpp
	JUCE/modules/juce_audio_plugin_client/juce_audio_plugin_client_VST2.cpp
	JUCE/modules/juce_audio_plugin_client/juce_audio_plugin_client_RTAS_utils.mm
	JUCE/modules/juce_audio_plugin_client/juce_audio_plugin_client_VST_utils.mm
	JUCE/modules/juce_audio_plugin_client/juce_audio_plugin_client_AUv3.mm
	JUCE/modules/juce_audio_plugin_client/juce_audio_plugin_client_AU_2.mm
	JUCE/modules/juce_audio_plugin_client/juce_audio_plugin_client_AU_1.mm
	Source/Misc/lua/src/lua.c
	Source/Misc/luabind/src/class.cpp
	Source/Misc/luabind/src/class_info.cpp
	Source/Misc/luabind/src/class_registry.cpp
	Source/Misc/luabind/src/class_rep.cpp
	Source/Misc/luabind/src/create_class.cpp
	Source/Misc/luabind/src/error.cpp
	Source/Misc/luabind/src/exception_handler.cpp
	Source/Misc/luabind/src/function.cpp
	Source/Misc/luabind/src/function_introspection.cpp
	Source/Misc/luabind/src/inheritance.cpp
	Source/Misc/luabind/src/link_compatibility.cpp
	Source/Misc/luabind/src/lua51compat.cpp
	Source/Misc/luabind/src/object_rep.cpp
	Source/Misc/luabind/src/open.cpp
	Source/Misc/luabind/src/operator.cpp
	Source/Misc/luabind/src/pcall.cpp
	Source/Misc/luabind/src/scope.cpp
	Source/Misc/luabind/src/set_package_preload.cpp
	Source/Misc/luabind/src/shared_ptr_converter.cpp
	Source/Misc/luabind/src/stack_content_by_name.cpp
	Source/Misc/luabind/src/weak_ref.cpp
	Source/Misc/luabind/src/wrapper_base.cpp
	Source/Misc/libusb/src/compat.c
	Source/Misc/libusb/src/core.c
	Source/Misc/libusb/src/darwin_usb.c
	Source/Misc/libusb/src/descriptor.c
	Source/Misc/libusb/src/enums.c
	Source/Misc/libusb/src/hotplug.c
	Source/Misc/libusb/src/io.c
	Source/Misc/libusb/src/linux_udev.c
	Source/Misc/libusb/src/linux_usbfs.c
	Source/Misc/libusb/src/poll_posix.c
	Source/Misc/libusb/src/poll_windows.c
	Source/Misc/libusb/src/strerror.c
	Source/Misc/libusb/src/structs.c
	Source/Misc/libusb/src/sync.c
	Source/Misc/libusb/src/threads_posix.c
	Source/Misc/libusb/src/threads_windows.c
	Source/Misc/libusb/src/usb.c
	Source/Misc/libusb/src/windows_usb.c
	Source/Misc/keys.cpp
	JuceLibraryCode/BinaryData.cpp
	PROPERTIES SKIP_PRECOMPILE_HEADERS ON
)
