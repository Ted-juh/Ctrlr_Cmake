#pragma once
#include "stdafx.h"

class CtrlrBuildScriptVST3Section : public Component, public Button::Listener
{

public:
	CtrlrBuildScriptVST3Section();
	~CtrlrBuildScriptVST3Section();

	void paint(Graphics& g);

	void resized();

	void buttonClicked(Button* button);

private:
	std::unique_ptr<Label> lProductName;
	std::unique_ptr<Label> tProductName;
	std::unique_ptr<Label> lCompanyName;
	std::unique_ptr<Label> tCompanyName;
	std::unique_ptr<Label> lCompanyURL;
	std::unique_ptr<Label> tCompanyURL;
	std::unique_ptr<Label> lCompanyEmail;
	std::unique_ptr<Label> tCompanyEmail;
	std::unique_ptr<Label> lPluginName;
	std::unique_ptr<Label> tPluginName;




};

