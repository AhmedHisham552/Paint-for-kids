#include "SaveAction.h"
#include<fstream>


SaveAction::SaveAction(ApplicationManager* pApp):Action(pApp)
{
	if (!pManager->getSound())
		PlaySound("Sounds\\save.wav", NULL, SND_ASYNC);
}

void SaveAction::ReadActionParameters()
{
	
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Enter name to save your file : ");
	name=pIn->GetSrting(pOut);
	
}


void SaveAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	if (pManager->CheckDrawings()) {
		Input* pIn = pManager->GetInput();
		ReadActionParameters();
		ofstream OutFile;
		OutFile.open("Savefile/" + name + ".txt");
		pManager->SaveAll(OutFile);
		OutFile.close();
		pManager->SaveAll(OutFile);
		pOut->PrintMessage("Saved");
	}
	else {
		pOut->PrintMessage("File is empty, please draw shapes first to save them");
	}
	
}

SaveAction::~SaveAction()
{
}
