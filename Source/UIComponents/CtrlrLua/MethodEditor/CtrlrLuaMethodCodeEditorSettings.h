#pragma once
#include "Methods/CtrlrLuaMethod.h"
#include "CtrlrTextEditor.h"
#include "CtrlrWindowManagers/CtrlrChildWindowContent.h"
#include "CtrlrWindowManagers/CtrlrPanelWindowManager.h"
#include "CtrlrLuaCodeTokeniser.h"
#include "CtrlrPropertyEditors/CtrlrPropertyComponent.h"
class CtrlrLuaMethodEditor;

class CtrlrLuaMethodCodeEditorSettings  : public Component,
                                          public ChangeListener,
										  public ComboBox::Listener,
										  public Button::Listener,
										  public Slider::Listener
{
public:
    CtrlrLuaMethodCodeEditorSettings (CtrlrLuaMethodEditor &_owner);
    ~CtrlrLuaMethodCodeEditorSettings();

    void changeListenerCallback (ChangeBroadcaster* source);
	const Font getFont();
	const Colour getColour();
    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void buttonClicked (Button* buttonThatWasClicked);
    void sliderValueChanged (Slider* sliderThatWasMoved);

private:
	CtrlrLuaCodeTokeniser luaTokeniser;
	CodeDocument codeDocument;
	CtrlrLuaMethodEditor &owner;
	Font codeFont;
    ComboBox* fontTypeface;
    ToggleButton* fontBold;
    ToggleButton* fontUnderline;
    ToggleButton* fontItalic;
    Slider* fontSize;
    CtrlrColourEditorComponent* bgColour;
    CodeEditorComponent* fontTest;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrLuaMethodCodeEditorSettings);
};