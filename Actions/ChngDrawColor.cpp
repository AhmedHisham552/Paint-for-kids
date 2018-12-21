#include "ChngDrawColor.h"



ChngDrawColor::ChngDrawColor(ApplicationManager * pApp,Output* pOut, Input* pIn) :Action(pApp)
{
	this->pOut = pOut;
	this->pIn = pIn;
	if (!pManager->getSound())
		PlaySound("Sounds\\drawClr.wav", NULL, SND_ASYNC);
}

void ChngDrawColor::ReadActionParameters() {
}

void ChngDrawColor::Execute()
{
	pOut->DrawColorPallete(2); // Draws the pallete
	ChooseClr = pIn->GetClr(); // Gets the input from the user 
	switch (ChooseClr) {
		case PICK_BLACK: UI.DrawColor = BLACK; pOut->PrintMessage("Draw Color changed to Black");
			break;
		case PICK_WHITE: UI.DrawColor = WHITE; pOut->PrintMessage("Draw Color changed to White");
			break;
		case PICK_RED:   UI.DrawColor = RED; pOut->PrintMessage("Draw Color changed to Red");
			break;
		case PICK_GREEN: UI.DrawColor = GREEN; pOut->PrintMessage("Draw Color changed to Green");
			break;
		case PICK_BLUE:  UI.DrawColor = BLUE; pOut->PrintMessage("Draw Color changed to Blue");
			break;
	}
	if (pManager->GetSelectedFig() != NULL) {
		pManager->DeselectAll();
		(pManager->GetSelectedFig())->ChngDrawClr(UI.DrawColor); // Changes the draw color to the color selected from UI
		pManager->SetSelectedFig(NULL);
	}
	pOut->ClearColorPallete();
}




ChngDrawColor::~ChngDrawColor()
{
}
