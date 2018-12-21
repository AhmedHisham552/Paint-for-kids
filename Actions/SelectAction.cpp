#include "SelectAction.h"
#include "../ApplicationManager.h"
#include "../includeFiles/AllFigures.h"
#include <cmath>


SelectAction::SelectAction(ApplicationManager *pApp):Action(pApp)
{
	if (!pManager->getSound())
		PlaySound("Sounds\\selectFigure.wav", NULL, SND_ASYNC);
}

void SelectAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Input* pIn = pManager->GetInput();
	pIn->GetPointClicked(pClicked.x, pClicked.y);

}

void SelectAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	
	ReadActionParameters();
	// get the clicked figure
	CFigure* clickedFigure = pManager->GetFigure(pClicked.x, pClicked.y);

	CRectangle* ptrRectangle = dynamic_cast <CRectangle*>(clickedFigure);
	CLine* ptrLine = dynamic_cast <CLine*>(clickedFigure);
	CRhombus* ptrRhombus = dynamic_cast <CRhombus*>(clickedFigure);
	CTriangle* ptrTriangle = dynamic_cast <CTriangle*>(clickedFigure);
	CEllipse* ptrEllipse = dynamic_cast <CEllipse*>(clickedFigure);

	if (clickedFigure){ // if user selects a figure

		if (clickedFigure->IsSelected() == true) {		// if the figure is already selected
			pManager->DeselectAll();
		}
		else {											// the figure isn't already selected
			pManager->DeselectAll();					// deselects the selected figure
			clickedFigure->SetSelected(true);			// make the clickedfigure selected
			pManager->SetSelectedFig(clickedFigure);
			clickedFigure->setPrevDrawColor(clickedFigure->getDrawColor()); 
			clickedFigure->ChngDrawClr(MAGENTA);
			//Checking the type of the figure and print specific message for every type;
			if (ptrRectangle != NULL) {
				pOut->PrintMessage("Rectangle ID: " + to_string(ptrRectangle->getID()) + " Width: " + to_string(ptrRectangle->getWidth()) + " Height: " + to_string(ptrRectangle->getHeight()));
			}
			if (ptrLine != NULL) {
				Point P1, P2;
				ptrLine->GetFigPoints(P1, P2);
				float length = sqrt( pow((P2.x - P1.x),2) + pow((P2.y-P1.y),2) );
				pOut->PrintMessage("Line ID: " + to_string(ptrLine->getID()) + " Length : " + to_string(length));
			}
			if (ptrRhombus != NULL) {
				Point P1;
				ptrRhombus->GetFigPoints(P1);
				pOut->PrintMessage("Rhombus ID: " + to_string(ptrRhombus->getID()) + " Center (" + to_string(P1.x) + "," + to_string(P1.y) + ")");
			}
			if (ptrTriangle != NULL) {
				Point P1, P2, P3;
				ptrTriangle->GetFigPoints(P1, P2, P3);
				pOut->PrintMessage("Triangle ID: " + to_string(ptrTriangle->getID()) + " Corner1 ("+ to_string(P1.x) + "," + to_string(P1.y) + ")" + " Corner2 (" + to_string(P2.x) + "," + to_string(P2.y) + ")"+ " Corner3 (" + to_string(P3.x) + "," + to_string(P3.y) + ")");
			}
			if (ptrEllipse != NULL) {
				Point P1;
				ptrEllipse->GetFigPoints(P1);
				pOut->PrintMessage("Ellipse ID: " + to_string(ptrEllipse->getID()) + " Center (" + to_string(P1.x) + "," + to_string(P1.y) + ")");

			}
		}
	}
	else {
		pManager->DeselectAll();
		pOut->PrintMessage("no figure is selected");
	}
}


SelectAction::~SelectAction()
{
}
