#include "CutAction.h"


CutAction::CutAction(ApplicationManager * pApp):Action(pApp)
{
	if (!pManager->getSound())
		PlaySound("Sounds\\Cut.wav", NULL, SND_ASYNC);
}

void CutAction::ReadActionParameters()
{
}


void CutAction::Execute() {
	Output* pOut = pManager->GetOutput();

	CFigure* selectedFigure = pManager->GetSelectedFig(); // Gets the selected figure

	if (selectedFigure == NULL) {
		pOut->PrintMessage("No figure is selected");
		return;
	}
	Point P1 = { 0,0 }, P2 = { 0,0 }, P3 = { 0,0 }; GfxInfo TempGfx; // Temporary variables 
	CFigure* copiedFigure;
	TempGfx = selectedFigure->GetFigGfxInfo();
	TempGfx.DrawClr = selectedFigure->getPrevDrawColor();

	if (dynamic_cast<CRectangle*>(selectedFigure)) { // If the figure is a rectangle, create a copy of it
		selectedFigure->GetFigPoints(P1, P2);
		copiedFigure = new CRectangle(P1, P2, TempGfx);
	}
	else if (dynamic_cast<CLine*>(selectedFigure)) { // If the figure is a line, create a copy of it
		selectedFigure->GetFigPoints(P1, P2);
		copiedFigure = new CLine(P1, P2, TempGfx);
	}
	else if (dynamic_cast<CEllipse*>(selectedFigure)) { // If the figure is an ellipse, create a copy of it
		selectedFigure->GetFigPoints(P1);
		copiedFigure = new CEllipse(P1, TempGfx);
		copiedFigure->ChngFigSize(selectedFigure->GetFigSize());
	}
	else if (dynamic_cast<CTriangle*>(selectedFigure)) { // If the figure is a triangle, create a copy of it
		selectedFigure->GetFigPoints(P1, P2, P3);
		copiedFigure = new CTriangle(P1, P2, P3, TempGfx);
	}
	else if (dynamic_cast<CRhombus*>(selectedFigure)) { // If the figure is a rhombus, create a copy of it
		selectedFigure->GetFigPoints(P1);
		copiedFigure = new CRhombus(P1, TempGfx);
		copiedFigure->ChngFigSize(selectedFigure->GetFigSize());
	}

	if (pManager->GetCutFig() != NULL) { // If there was a cut figure before this one, reset it's fill color to the original color
		(pManager->GetCutFig())->ChngFillClr((pManager->GetClipboardFig())->GetFigGfxInfo().FillClr); 
		pManager->SetCutFig(NULL);
	}

	pManager->ClearClipboard();

	pManager->SetClipboard(copiedFigure);
	pManager->SetCutFig(selectedFigure);

	pManager->DeselectAll();
	selectedFigure = NULL;
	pOut->PrintMessage("Cut the figure to the clipboard");
}

CutAction::~CutAction()
{
}
