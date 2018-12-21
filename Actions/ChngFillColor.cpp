#include "ChngFillColor.h"



ChngFillColor::ChngFillColor(ApplicationManager * pApp, Output* pOut, Input* pIn) :Action(pApp)
{
	this->pOut = pOut;
	this->pIn = pIn;
	if (!pManager->getSound())
		PlaySound("Sounds\\fillClr.wav", NULL, SND_ASYNC);
}

void ChngFillColor::ReadActionParameters() {
}

void ChngFillColor::Execute()
{
	pOut->PrintMessage("Choose a color for object to be filled with");
	pOut->DrawColorPallete(1); // Draws the pallete
	ChooseClr = pIn->GetClr(); // Gets the input from the user 
	switch (ChooseClr) {
	case PICK_BLACK: UI.FillColor = BLACK; pOut->PrintMessage("Fill Color changed to Black");
		break;
	case PICK_WHITE: UI.FillColor = WHITE; pOut->PrintMessage("Fill Color changed to White");
		break;
	case PICK_RED:   UI.FillColor = RED; pOut->PrintMessage("Fill Color changed to Red");
		break;
	case PICK_GREEN: UI.FillColor = GREEN; pOut->PrintMessage("Fill Color changed to Green");
		break;
	case PICK_BLUE:  UI.FillColor = BLUE; pOut->PrintMessage("Fill Color changed to Blue");
		break;
	}
	if (pManager->GetSelectedFig() != NULL) {
		pManager->DeselectAll();
		(pManager->GetSelectedFig())->ChngFillClr(UI.FillColor); // Changes the draw color to the color selected from UI
		pManager->SetSelectedFig(NULL);
	}
	pOut->ClearColorPallete();
}

ChngFillColor::~ChngFillColor()
{
}
