#include "AddRectAction.h"
#include "..\Figures\CRectangle.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"


AddRectAction::AddRectAction(ApplicationManager * pApp):Action(pApp)
{
	if (!pManager->getSound())
		PlaySound("Sounds\\rectangle.wav", NULL, SND_ASYNC);
}

void AddRectAction::ReadActionParameters() 
{	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Rectangle: Click at first corner");

	//Read 1st corner and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);
	if (!(P1.y >= UI.ToolBarHeight && P1.y < UI.height - UI.StatusBarHeight)) {
		valid = false;
		return;
	}
	pOut->PrintMessage("New Rectangle: Click at second corner");

	//Read 2nd corner and store in point P2
	pIn->GetPointClicked(P2.x, P2.y);
	if (!(P2.y >= UI.ToolBarHeight && P2.y < UI.height - UI.StatusBarHeight)) {
		valid = false;
		return;
	}
	RectGfxInfo.isFilled = true;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	RectGfxInfo.DrawClr = pOut->getCrntDrawColor();
	RectGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

//Execute the action
void AddRectAction::Execute() 
{
	Output* pOut = pManager->GetOutput();
	//This action needs to read some parameters first
	ReadActionParameters();
	
	//if  the clicked point is in the drawing area
	if (valid) {
		
		//Create a rectangle with the parameters read from the user
		CRectangle *R = new CRectangle(P1, P2, RectGfxInfo);

		//Add the rectangle to the list of figures
		pManager->AddFigure(R);
	
	}
	// if the point isn't on the drawing area
	else {
		pOut->PrintMessage("Error: Can't draw on the toolbar or the status bar");
	}

	
}