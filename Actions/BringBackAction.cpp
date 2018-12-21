#include "BringBackAction.h"



BringBackAction::BringBackAction(ApplicationManager * pApp) :Action(pApp)
{
	if (!pManager->getSound())
		PlaySound("Sounds\\sendToBack.wav", NULL, SND_ASYNC);
}

void BringBackAction::ReadActionParameters() {
}

void BringBackAction::Execute() {
	Output* pOut = pManager->GetOutput();
	if (pManager->GetSelectedFig() == NULL) {
		pOut->PrintMessage("No figure is selected");
	}
	else {
		CFigure* selectedFigure = pManager->GetSelectedFig(); // Gets selected figure from the user
		CFigure* tempFig;
		Point P1 = { 0,0 }, P2 = { 0,0 }, P3 = { 0,0 }; GfxInfo TempGfx; // Temporary variables
		TempGfx = selectedFigure->GetFigGfxInfo();
		TempGfx.DrawClr = selectedFigure->getPrevDrawColor(); // Sets the temporary draw color to the original draw color of the selected figure (NOT MAGENTA)

		if (dynamic_cast<CRectangle*>(selectedFigure)) { // If the figure is a rectangle
			selectedFigure->GetFigPoints(P1, P2);		 // Gets the points from the selected figure and puts them into the temporary variables
			tempFig = new CRectangle(P1, P2, TempGfx);   // Creates a new figure with the temporary variables
		}
		else if (dynamic_cast<CLine*>(selectedFigure)) { // If the figure is a line
			selectedFigure->GetFigPoints(P1, P2);
			tempFig = new CLine(P1, P2, TempGfx);
		}
		else if (dynamic_cast<CEllipse*>(selectedFigure)) { // If the figure is an ellipse
			selectedFigure->GetFigPoints(P1);
			tempFig = new CEllipse(P1, TempGfx);
			tempFig->ChngFigSize(selectedFigure->GetFigSize());
		}
		else if (dynamic_cast<CTriangle*>(selectedFigure)) { // If the figure is a triangle
			selectedFigure->GetFigPoints(P1, P2, P3);
			tempFig = new CTriangle(P1, P2, P3, TempGfx);
		}
		else if (dynamic_cast<CRhombus*>(selectedFigure)) { // If the figure is a rhombus
			selectedFigure->GetFigPoints(P1);
			tempFig = new CRhombus(P1, TempGfx);
			tempFig->ChngFigSize(selectedFigure->GetFigSize());
		}

		pManager->AddFigureOnTop(tempFig); // Adds the copied figure on top of the figure list
		pManager->DeleteFigure(selectedFigure); // Deletes the selected figure

		pManager->SetSelectedFig(NULL);
		pManager->DeselectAll();
		pOut->PrintMessage("Figure sent to back");
	}
}

BringBackAction::~BringBackAction()
{
}
