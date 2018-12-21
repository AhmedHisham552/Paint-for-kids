#include "AddLineAction.h"

#include "../Figures/CLine.h"

#include "../ApplicationManager.h"

#include "../GUI/Input.h"
#include "../GUI/Output.h"

AddLineAction::AddLineAction(ApplicationManager * pApp):Action(pApp)
{
	if (!pManager->getSound())
		PlaySound("Sounds\\line.wav", NULL, SND_ASYNC);
}

void AddLineAction::ReadActionParameters() 
{	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Line: Click at start point");
	
	//Read start point and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);
	//checks if the points are in the drawing area
	if (!(P1.y >= UI.ToolBarHeight && P1.y < UI.height - UI.StatusBarHeight)) {
		valid = false;
		return;
	}
	pOut->PrintMessage("New Line: Click at end point");

	//Read end point and store in point P2
	pIn->GetPointClicked(P2.x, P2.y);
	if (!(P2.y >= UI.ToolBarHeight && P2.y < UI.height - UI.StatusBarHeight)) {
		valid = false;
		return;
	}
	LineGfxInfo.isFilled = false;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	LineGfxInfo.DrawClr = pOut->getCrntDrawColor();
	LineGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

//Execute the action
void AddLineAction::Execute() 
{
	//This action needs to read some parameters first
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();

	//if  the clicked point is in the drawing area
	if (valid) {

		//Create a line with the parameters read from the user
		CLine *L = new CLine(P1, P2, LineGfxInfo);

		//Add the line to the list of figures
		pManager->AddFigure(L);

	}
	// if the point isn't on the drawing area
	else {
		pOut->PrintMessage("Error: Can't draw on the toolbar or the status bar");
	}
}