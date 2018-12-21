#include "AddEllipseAction.h"
#include "../Figures/CEllipse.h"

#include "../ApplicationManager.h"

#include "../GUI/input.h"
#include "../GUI/Output.h"




AddEllipseAction::AddEllipseAction(ApplicationManager * pApp):Action(pApp)
{
	if (!pManager->getSound())
		PlaySound("Sounds\\ellipse.wav", NULL, SND_ASYNC);
}

void AddEllipseAction::ReadActionParameters() 
{	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	

	pOut->PrintMessage("New Ellipse: Click at midpoint");

	//Read midpoint and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);
	if (!((P1.y-150) >= UI.ToolBarHeight && (P1.y+150) < UI.height - UI.StatusBarHeight)) {
		valid = false;
		return;
	}
	ElliGfxInfo.isFilled = true;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	ElliGfxInfo.DrawClr = pOut->getCrntDrawColor();
	ElliGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

//Execute the action
void AddEllipseAction::Execute() 
{
	//This action needs to read some parameters first
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();

	//if  the clicked point is in the drawing area
	if (valid) {

		//Create a ellipse with the parameters read from the user
		CEllipse *E = new CEllipse(P1, ElliGfxInfo);

		//Add the ellipse to the list of figures
		pManager->AddFigure(E);

	}
	// if the point isn't on the drawing area
	else {
		pOut->PrintMessage("Error: Can't draw on the toolbar or the status bar");
	}
}
