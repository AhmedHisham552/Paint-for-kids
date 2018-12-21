#include "CopyAction.h"



CopyAction::CopyAction(ApplicationManager * pApp):Action(pApp)
{
	if (!pManager->getSound())
		PlaySound("Sounds\\Copy.wav", NULL, SND_ASYNC);
}

void CopyAction::ReadActionParameters() {
}

void CopyAction::Execute() {
	Output* pOut = pManager->GetOutput();

	CFigure* selectedFigure = pManager->GetSelectedFig(); // Gets the selected figure

	Point P1 = { 0,0 }, P2 = { 0,0 }, P3 = { 0,0 }; GfxInfo TempGfx; // Creates temporary points and GfxInfo
	CFigure* copiedFigure;

	if (pManager->GetCutFig() != NULL) {
		(pManager->GetCutFig())->ChngFillClr((pManager->GetClipboardFig())->GetFigGfxInfo().FillClr); // If there was a CUT figure, then return it to it's original color
		pManager->SetCutFig(NULL); // Resets the cut figure to NULL
	}

	if (selectedFigure == NULL) { // If no figure was selected, print an error
		pOut->PrintMessage("No figure is selected");
		return;
	}else if (dynamic_cast<CRectangle*>(selectedFigure)) {	// If the figure is a rectangle, create a copy of it

		selectedFigure->GetFigPoints(P1,P2);
		copiedFigure = new CRectangle(P1,P2, selectedFigure->GetFigGfxInfo());

	}else if (dynamic_cast<CLine*>(selectedFigure)) { // If the figure is a line, create a copy of it

		selectedFigure->GetFigPoints(P1, P2);
		copiedFigure = new CLine(P1,P2, selectedFigure->GetFigGfxInfo());

	}else if (dynamic_cast<CEllipse*>(selectedFigure)) { // If the figure is an ellipse , create a copy of it

		selectedFigure->GetFigPoints(P1);
		copiedFigure = new CEllipse(P1, selectedFigure->GetFigGfxInfo());
		copiedFigure->ChngFigSize(selectedFigure->GetFigSize());

	}else if (dynamic_cast<CTriangle*>(selectedFigure)) { // If the figure is a triangle, create a copy of it

		selectedFigure->GetFigPoints(P1, P2, P3);
		copiedFigure = new CTriangle(P1,P2,P3, selectedFigure->GetFigGfxInfo());

	}else if (dynamic_cast<CRhombus*>(selectedFigure)) { // If the figure is a rhombus, create a copy of it
		selectedFigure->GetFigPoints(P1);
		copiedFigure = new CRhombus(P1, selectedFigure->GetFigGfxInfo());
		copiedFigure->ChngFigSize(selectedFigure->GetFigSize());
	}


	pManager->ClearClipboard();

	copiedFigure->ChngDrawClr(selectedFigure->getPrevDrawColor()); // Makes the copied figure has the original color of the selected figure (NOT MAGENTA)
	pManager->SetClipboard(copiedFigure); // Inserts the copied figure into the clipboard
	pManager->DeselectAll(); // Deselects the selected figure
	selectedFigure = NULL; // Resets the selected figure pointer to NULL
	pOut->PrintMessage("Copied the figure to the clipboard");
}

CopyAction::~CopyAction()
{

}
