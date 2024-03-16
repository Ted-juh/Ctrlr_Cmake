#include "stdafx.h"
#include "CtrlrPanelUtilities.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"
#include "CtrlrComponents/CtrlrComponent.h"

CtrlrPanelUtilities::CtrlrPanelUtilities (CtrlrPanelEditor &_owner)
    : owner(_owner),
      xmlPreview (0)
{
    addAndMakeVisible (xmlPreview = new CodeEditorComponent (codeDocument, &xmlTokeniser));
    xmlPreview->setName (L"xmlPreview");
    xmlPreview->setScrollbarThickness(owner.getOwner().getOwner().getProperty(Ids::ctrlrScrollbarThickness));
	xmlPreview->setColour (CodeEditorComponent::backgroundColourId, Colours::white);
	xmlPreview->setColour (CodeEditorComponent::highlightColourId, Colours::lightgrey);
	xmlPreview->setColour(CodeEditorComponent::lineNumberBackgroundId, Colours::lightgrey);

    if (owner.getSelection())
        owner.getSelection()->addChangeListener(this);
    
    setSize (216, 340);
}

CtrlrPanelUtilities::~CtrlrPanelUtilities()
{
    deleteAndZero (xmlPreview);
}

void CtrlrPanelUtilities::paint (Graphics& g)
{
}

void CtrlrPanelUtilities::resized()
{
    xmlPreview->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
}

void CtrlrPanelUtilities::changeListenerCallback (ChangeBroadcaster* source)
{
    if (owner.getSelection() == nullptr || !isVisible())
        return;

	if (owner.getSelection()->getNumSelected() == 0)
		return;

    reloadContent();
}

void CtrlrPanelUtilities::reloadContent()
{
    if ((owner.isVisible() && owner.getSelection()->getNumSelected() == 0) || owner.getSelection()->getNumSelected() > 1)
	{
		ScopedPointer <XmlElement> xml (owner.getOwner().getPanelTree().createXml().release());
		if (xml)
		{
			codeDocument.replaceAllContent (xml->createDocument(""));
		}
	}
	else if (owner.isVisible() && owner.getSelection()->getNumSelected() == 1)
	{
		CtrlrComponent *c =  owner.getSelection()->getSelectedItem(0);
		if (c)
		{
			ScopedPointer <XmlElement> xml (c->getOwner().getModulatorTree().createXml().release());
			String doc = xml->createDocument("");
			if (doc.length() <= 8192)
			{
				codeDocument.replaceAllContent (doc);
			}
		}
	}
}

void CtrlrPanelUtilities::visibilityChanged()
{
    if (isVisible())
    {
        reloadContent();
    }
}