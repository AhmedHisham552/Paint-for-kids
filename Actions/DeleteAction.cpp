#include "DeleteAction.h"
#include "../ApplicationManager.h"



DeleteAction::DeleteAction(ApplicationManager *pApp) :Action(pApp)
{
	if (!pManager->getSound())
		PlaySound("Sounds\\delete.wav", NULL, SND_ASYNC);
}

void DeleteAction::ReadActionParameters()
{
}

void DeleteAction::Execute() {
	pManager->DeleteSelectedFigure();
}

DeleteAction::~DeleteAction()
{
	
}
