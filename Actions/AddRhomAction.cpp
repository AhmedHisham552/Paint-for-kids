#include "AddRhomAction.h"
#include "../Figures/CRhombus.h"

#include "../ApplicationManager.h"

AddRhomAction::AddRhomAction(ApplicationManager * pApp):Action(pApp)
{
	if (!pManager->getSound())
		PlaySound("Sounds\\rhombus.wav", NULL, SND_ASYNC);
}

void AddRhomAction::ReadActionParameters() 
{	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Rhombus: Click at first corner");
	
	//Read Midpoint and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);
	if (!((P1.y-150) >= UI.ToolBarHeight && (P1.y+150) < UI.height - UI.StatusBarHeight)) {
		valid = false;
		return;
	}
	RhomGfxInfo.isFilled = true;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	RhomGfxInfo.DrawClr = pOut->getCrntDrawColor();
	RhomGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

//Execute the action
void AddRhomAction::Execute() 
{
	//This action needs to read some parameters first
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();

	//if  the clicked point is in the drawing area
	if (valid) {

		//Create a rhombus with the parameters read from the user
		CRhombus *R = new CRhombus(P1, RhomGfxInfo);

		//Add the rhombus to the list of figures
		pManager->AddFigure(R);

	}
	// if the point isn't on the drawing area
	else {
		pOut->PrintMessage("Error: The figure will be drawn out of the drawing area.");
	}
}
