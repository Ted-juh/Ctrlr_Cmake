#include "stdafx.h"
#include "stdafx_luabind.h"
#include "CtrlrAbout.h"
#include "CtrlrRevision.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrInlineUtilitiesGUI.h"

CtrlrAbout::CtrlrAbout (CtrlrManager &_owner)
    : owner(_owner)
{
    String authorEmail;
    if(owner.getActivePanel()) authorEmail = owner.getActivePanel()->getProperty(Ids::panelAuthorEmail);
        else authorEmail = "";
    String authorDonateUrl;
    if(owner.getActivePanel()) authorDonateUrl =   owner.getActivePanel()->getProperty(Ids::panelAuthorDonateUrl);
        else authorDonateUrl = "";

    addAndMakeVisible (ctrlrName = new Label ("",
                                              TRANS("Ctrlr")));
    ctrlrName->setFont (Font (48.00f, Font::bold));
    ctrlrName->setJustificationType (Justification::centredLeft);
    ctrlrName->setEditable (false, false, false);
    ctrlrName->setColour (Label::textColourId, Colour (0xd6000000));
    ctrlrName->setColour (TextEditor::textColourId, Colours::black);
    ctrlrName->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (ctrlrLogo = gui::createDrawableButton("Ctrlr", BIN2STR(ctrlr_logo_svg)));
    ctrlrLogo->addListener (this);

    addAndMakeVisible (versionInfoLabel = new TextEditor (""));
    versionInfoLabel->setMultiLine (true);
    versionInfoLabel->setReturnKeyStartsNewLine (true);
    versionInfoLabel->setReadOnly (true);
    versionInfoLabel->setScrollbarsShown (true);
    versionInfoLabel->setCaretVisible (false);
    versionInfoLabel->setPopupMenuEnabled (true);
    versionInfoLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    versionInfoLabel->setColour (TextEditor::outlineColourId, Colour (0x9c000000));
    versionInfoLabel->setColour (TextEditor::shadowColourId, Colour (0x00000000));
    versionInfoLabel->setText ("");

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Instance name")));
    label->setFont (Font (24.00f, Font::bold));
    label->setJustificationType (Justification::topRight);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

	if (!authorDonateUrl.isEmpty())
	{
		addAndMakeVisible(labelDonate = new Label("new label", TRANS("Donate")));
		labelDonate->setFont(Font(24.00f, Font::plain));
		labelDonate->setJustificationType(Justification::topRight);
		labelDonate->setEditable(false, false, false);
		labelDonate->setColour(TextEditor::textColourId, Colours::black);
		labelDonate->setColour(TextEditor::backgroundColourId, Colour(0x00000000));
	}

	addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("Author")));
    label2->setFont (Font (24.00f, Font::plain));
    label2->setJustificationType (Justification::topRight);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

	if (!authorEmail.isEmpty())
	{
		addAndMakeVisible(labelAuthorEmail = new Label("new label", TRANS("Contact")));
		labelAuthorEmail->setFont(Font(24.00f, Font::plain));
		labelAuthorEmail->setJustificationType(Justification::topRight);
		labelAuthorEmail->setEditable(false, false, false);
		labelAuthorEmail->setColour(TextEditor::textColourId, Colours::black);
		labelAuthorEmail->setColour(TextEditor::backgroundColourId, Colour(0x00000000));
	}

	addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("Version")));
    label3->setFont (Font (24.00f, Font::plain));
    label3->setJustificationType (Justification::topRight);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label4 = new Label ("new label",
                                           TRANS("URL")));
    label4->setFont (Font (24.00f, Font::plain));
    label4->setJustificationType (Justification::topRight);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (instanceUrl = new HyperlinkButton ("",
                                                          URL ("http://www.rawmaterialsoftware.com/juce")));
    instanceUrl->setTooltip (TRANS("http://www.rawmaterialsoftware.com/juce"));
	instanceUrl->setJustificationType(Justification::topLeft);

	if (!authorEmail.isEmpty())
	{
		addAndMakeVisible(instanceAuthorEmail = new HyperlinkButton(authorEmail,URL("mailto:" + authorEmail)));
		instanceAuthorEmail->setJustificationType(Justification::topLeft);
	}

	if (!authorDonateUrl.isEmpty())
	{
		addAndMakeVisible(instanceAuthorDonateUrl = new HyperlinkButton(authorDonateUrl, URL(authorDonateUrl)));
		instanceAuthorDonateUrl->setJustificationType(Justification::topLeft);
	}

	addAndMakeVisible (instanceVersion = new Label ("",
                                                    ""));
    instanceVersion->setFont (Font (22.00f, Font::bold));
    instanceVersion->setJustificationType (Justification::topLeft);
    instanceVersion->setEditable (false, false, false);
    instanceVersion->setColour (TextEditor::textColourId, Colours::black);
    instanceVersion->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (instanceAuthor = new Label ("",
                                                   ""));
    instanceAuthor->setFont (Font (22.00f, Font::bold));
    instanceAuthor->setJustificationType (Justification::topLeft);
    instanceAuthor->setEditable (false, false, false);
    instanceAuthor->setColour (TextEditor::textColourId, Colours::black);
    instanceAuthor->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (instanceName = new Label ("",
                                                 ""));
    instanceName->setFont (Font (24.00f, Font::bold));
    instanceName->setJustificationType (Justification::topLeft);
    instanceName->setEditable (false, false, false);
    instanceName->setColour (TextEditor::textColourId, Colours::black);
    instanceName->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (instanceDescription = new TextEditor (""));
    instanceDescription->setMultiLine (true);
    instanceDescription->setReturnKeyStartsNewLine (true);
    instanceDescription->setReadOnly (true);
    instanceDescription->setScrollbarsShown (true);
    instanceDescription->setCaretVisible (false);
    instanceDescription->setPopupMenuEnabled (false);
    instanceDescription->setColour (TextEditor::backgroundColourId, Colour (0x00ffffff));
    instanceDescription->setColour (TextEditor::outlineColourId, Colour (0x59000000));
    instanceDescription->setColour (TextEditor::shadowColourId, Colour (0x00000000));
    instanceDescription->setText ("");

	ctrlrLogo->setMouseCursor(MouseCursor::PointingHandCursor);
	addVersionInfo ("Version", STR(ctrlrRevision));
	addVersionInfo ("Build date", STR(ctrlrRevisionDate));
#if CTRLR_NIGHTLY == 1
	addVersionInfo ("Branch", "Nightly");
#else
	addVersionInfo ("Branch", "master");
#endif
	addVersionInfo ("Juce", SystemStats::getJUCEVersion().fromLastOccurrenceOf("JUCE v", false, true));

	addVersionInfo ("libusb", "1.0.19");
    addVersionInfo ("liblo", "0.28");
	addVersionInfo ("lua", LUA_RELEASE);
	addVersionInfo ("luabind", _STR(LUABIND_VERSION / 1000) + "." + _STR(LUABIND_VERSION / 100 % 100) + "." + _STR(LUABIND_VERSION % 100));
	addVersionInfo ("boost", _STR(BOOST_VERSION / 100000) + "." + _STR(BOOST_VERSION / 100 % 1000) + "." + _STR(BOOST_VERSION % 100));
	versionInfoLabel->setFont (Font (owner.getFontManager().getDefaultMonoFontName(), 14.0f, Font::plain));

	if (owner.isSingleInstance())
	{
		int height = 380;
		if (!authorEmail.isEmpty())
		{
			height += 40;
		}

		if (!authorDonateUrl.isEmpty())
		{
			height += 40;
		}

		setSize (600, height);

		if (owner.getActivePanel())
		{
			instanceName->setText (owner.getActivePanel()->getProperty(Ids::name).toString(), dontSendNotification);
			instanceAuthor->setText (owner.getActivePanel()->getProperty(Ids::panelAuthorName).toString(), dontSendNotification);
			instanceDescription->setText (owner.getActivePanel()->getProperty(Ids::panelAuthorDesc).toString(), dontSendNotification);
			instanceUrl->setButtonText (owner.getActivePanel()->getProperty(Ids::panelAuthorUrl));
			instanceUrl->setURL(URL(owner.getActivePanel()->getProperty(Ids::panelAuthorUrl)));
			instanceVersion->setText (owner.getActivePanel()->getVersionString(false, false, "."), dontSendNotification);
		}
	}
	else
	{
		setSize (600, 96);
	}
	updateVersionLabel();
}

CtrlrAbout::~CtrlrAbout()
{
    ctrlrName = nullptr;
    ctrlrLogo = nullptr;
    versionInfoLabel = nullptr;
    label = nullptr;
	labelAuthorEmail = nullptr;
	labelDonate = nullptr;
    label2 = nullptr;
    label3 = nullptr;
    label4 = nullptr;
    instanceUrl = nullptr;
    instanceVersion = nullptr;
    instanceAuthor = nullptr;
    instanceName = nullptr;
    instanceDescription = nullptr;
}

void CtrlrAbout::paint (Graphics& g)
{
    g.setColour (Colour (0xff4c4c4c));
    g.fillRect (proportionOfWidth (0.0200f), 163, proportionOfWidth (0.9600f), 2);
}

void CtrlrAbout::resized()
{
    ctrlrName->setBounds (proportionOfWidth (0.0200f) + proportionOfWidth (0.0800f) - -8, 8, proportionOfWidth (0.2000f), 48);
    ctrlrLogo->setBounds (proportionOfWidth (0.0200f), 8, proportionOfWidth (0.0800f), 48);
    versionInfoLabel->setBounds ((proportionOfWidth (0.0200f) + proportionOfWidth (0.0800f) - -8) + proportionOfWidth (0.2000f) - -8, 8, proportionOfWidth (0.6600f), 76);
	label->setBounds (proportionOfWidth (0.0133f), 120, proportionOfWidth (0.4600f), 24);
	instanceName->setBounds(proportionOfWidth(0.5000f), 120, proportionOfWidth(0.4800f), 24);
	int height = 136;
	if (labelDonate)
	{
		height += 40;
		labelDonate->setBounds(proportionOfWidth(0.0133f), height, proportionOfWidth(0.4600f), 24);
		instanceAuthorDonateUrl->setBounds(proportionOfWidth(0.5000f), height, proportionOfWidth(0.4800f), 24);
	}
	height += 40;
	label2->setBounds (proportionOfWidth (0.0133f), height, proportionOfWidth (0.4600f), 24);
	instanceAuthor->setBounds(proportionOfWidth(0.5000f), height, proportionOfWidth(0.4800f), 24);
	if (labelAuthorEmail)
	{
		height += 40;
		labelAuthorEmail->setBounds(proportionOfWidth(0.0133f), height, proportionOfWidth(0.4600f), 24);
		instanceAuthorEmail->setBounds(proportionOfWidth(0.5000f), height, proportionOfWidth(0.4800f), 24);
	}
	height += 40;
	label3->setBounds (proportionOfWidth (0.0133f), height, proportionOfWidth (0.4600f), 24);
	instanceVersion->setBounds(proportionOfWidth(0.5000f), height, proportionOfWidth(0.4800f), 24);
	height += 40;
	label4->setBounds (proportionOfWidth (0.0133f), height, proportionOfWidth (0.4600f), 24);
    instanceUrl->setBounds (proportionOfWidth (0.5000f), height, proportionOfWidth (0.4800f), 24);
	height += 32;
	instanceDescription->setBounds (proportionOfWidth (0.0200f), height, proportionOfWidth (0.9600f), 80);
}

void CtrlrAbout::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == ctrlrLogo)
    {
    }
}

void CtrlrAbout::addVersionInfo (const String &name, const String &version)
{
	versionInformationArray.set (name, version);
}

void CtrlrAbout::updateVersionLabel()
{
	for (int i = 0; i < versionInformationArray.size(); i++)
	{
		versionInfoLabel->insertTextAtCaret(versionInformationArray.getAllKeys()[i] + ": ");
		versionInfoLabel->insertTextAtCaret(versionInformationArray.getAllValues()[i] + "\n");
	}
	versionInfoLabel->setText (versionInformationArray.getDescription());
}
