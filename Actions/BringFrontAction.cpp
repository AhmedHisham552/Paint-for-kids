#include "BringFrontAction.h"



BringFrontAction::BringFrontAction(ApplicationManager * pApp) :Action(pApp)
{
	if (!pManager->getSound())
		PlaySound("Sounds\\bringToFront.wav", NULL, SND_ASYNC);
}

void BringFrontAction::ReadActionParameters() {
}

void BringFrontAction::Execute() {
	Output* pOut = pManager->GetOutput();
	if (pManager->GetSelectedFig() == NULL) {
		pOut->PrintMessage("No figure is selected");
	}
	else {
		CFigure* selectedFigure = pManager->GetSelectedFig(); // Gets the selected figure
		CFigure* tempFig;
		Point P1 = { 0,0 }, P2 = { 0,0 }, P3 = { 0,0 }; GfxInfo TempGfx; // Temporary variables
		TempGfx = selectedFigure->GetFigGfxInfo();
		TempGfx.DrawClr = selectedFigure->getPrevDrawColor(); // Gets the original color of the selectedFigure (not MAGENTA)

		if (dynamic_cast<CRectangle*>(selectedFigure)) { // If the selected figure is a rectangle
			selectedFigure->GetFigPoints(P1, P2);
			tempFig = new CRectangle(P1, P2, TempGfx);
		}
		else if (dynamic_cast<CLine*>(selectedFigure)) { // If the selected figure is a line
			selectedFigure->GetFigPoints(P1, P2);
			tempFig = new CLine(P1, P2, TempGfx);
		}
		else if (dynamic_cast<CEllipse*>(selectedFigure)) { // If the selected figure is an ellipse
			selectedFigure->GetFigPoints(P1);
			tempFig = new CEllipse(P1, TempGfx);
			tempFig->ChngFigSize(selectedFigure->GetFigSize());
		}
		else if (dynamic_cast<CTriangle*>(selectedFigure)) { // If the selected figure is a triangle
			selectedFigure->GetFigPoints(P1, P2, P3);
			tempFig = new CTriangle(P1, P2, P3, TempGfx);
		}
		else if (dynamic_cast<CRhombus*>(selectedFigure)) { // If the selected figure is a rhombus
			selectedFigure->GetFigPoints(P1);
			tempFig = new CRhombus(P1, TempGfx);
			tempFig->ChngFigSize(selectedFigure->GetFigSize());
		}

		pManager->AddFigure(tempFig);			// Adds the temporary stored figure 
		pManager->DeleteFigure(selectedFigure); // Deletes the selected figure
		pManager->SetSelectedFig(NULL);
		pManager->DeselectAll();

		pOut->PrintMessage("Figure brought to front");
	}
}

BringFrontAction::~BringFrontAction()
{
}
