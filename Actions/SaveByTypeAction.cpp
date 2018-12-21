#include "SaveByTypeAction.h"
#include<fstream>


SaveByTypeAction::SaveByTypeAction(ApplicationManager* pApp) :Action(pApp)
{
	if (!pManager->getSound())
		PlaySound("Sounds\\saveByType.wav", NULL, SND_ASYNC);
}

void SaveByTypeAction::ReadActionParameters()
{

	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("select the type from tool bar");
	ActionType action = pIn->GetUserAction();
	switch (action) {
	case DRAW_RECT:
		type = RECTANGLE;
		number = pManager->NumOfrect();
		break;
	case DRAW_ELLIPSE:
		type = ELLIPSE;
		number= pManager->NumOfEli();
		break;
	case DRAW_LINE:
		type = LINE;
		number = pManager->NumOfLines();
		break;
	case DRAW_RHOMBUS:
		type = RHUMBOS;
		number = pManager->NumOfRhom();
		break;
	case DRAW_TRI:
		type = TRIANGLE;
		number = pManager->NumOfTris();
		break;
	default:
		EMPTY;
		number = -1;
		break;
	}
	if (number == 0||number==-1) {
		pOut->PrintMessage("No figures of this type is found");
		flag = true;
	}
	else {
		pOut->PrintMessage("Enter name to save your file : ");
		name = pIn->GetSrting(pOut);
	}
}


void SaveByTypeAction::Execute()
{
	if (pManager->CheckDrawings()) {
		Output* pOut = pManager->GetOutput();
		Input* pIn = pManager->GetInput();
		ReadActionParameters();
		if (!flag){
			ofstream OutFile;
			OutFile.open("Savefile/" + name + ".txt");
			pManager->SaveByType(OutFile, type);
			OutFile.close();
			//pManager->SaveByType(OutFile, type);
			pOut->PrintMessage("Saved");
		}
	}
}

SaveByTypeAction::~SaveByTypeAction()
{
}
