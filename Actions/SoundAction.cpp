#include "SoundAction.h"



SoundAction::SoundAction(ApplicationManager* pApp):Action(pApp)
{
}

void SoundAction::Execute() {
	Output* pOut=pManager->GetOutput();
	//gets voice status
	bool muted=pManager->getSound();
	//reverse sound status
	pManager->setSound(!muted);
	if (!(pManager->getSound())) {
		pOut->PrintMessage("Sound is activated");
	}
	else {
		pOut->PrintMessage("Sound is deactivated");
	}
}

void SoundAction::ReadActionParameters()
{
}

SoundAction::~SoundAction()
{
}
