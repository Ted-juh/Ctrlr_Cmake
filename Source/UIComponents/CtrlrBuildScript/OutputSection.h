#include "stdafx.h"

class OutputSection : public Component, public Button::Listener
{
	public:
	OutputSection();
	~OutputSection();

	void paint(Graphics& g);
	void paintOverChildren(Graphics& g);
	void resized();
	void buttonClicked(Button* button);

	TextEditor& getOutputView() { return *outputView; }

	private:

		ScopedPointer<TextEditor>       outputView;
		ScopedPointer<TextButton>       clearButton;
};