#pragma once
#include "stdafx.h"

class CtrlrBuildScriptOutputSection : public Component, public Button::Listener
{
	public:
	CtrlrBuildScriptOutputSection();
	~CtrlrBuildScriptOutputSection();

	void paint(Graphics& g);
	void paintOverChildren(Graphics& g);
	void resized();
	void buttonClicked(Button* button);

	TextEditor& getOutputView() { return *outputView; }

	void insertTextAtCaret(const String &text);
	void setFont(const Font &font);

	private:

		std::unique_ptr<TextEditor>       outputView;
		std::unique_ptr<TextButton>       clearButton;
};