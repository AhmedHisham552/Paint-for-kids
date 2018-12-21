#include "PickByColorAction.h"
#include "../ApplicationManager.h"
#include "../includeFiles/AllFigures.h"
#include<iostream>


PickByColorAction::PickByColorAction(ApplicationManager * pApp) :Action(pApp)
{
	if (!pManager->getSound())
		PlaySound("Sounds\\pickbycolor.wav", NULL, SND_ASYNC);
}

void PickByColorAction::ReadActionParameters()
{
}

void PickByColorAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	int CorrectPicks = 0;
	int WrongPicks = 0;
	int numOfSelected = 0;
	int num;		//variable to store random number
	string msg;
	bool ended = true;
	ActionType act = EMPTY;
	if (pManager->CheckDrawings()) {
		//generates a random number and selects a color that exists in the draw area
		do {
			int range = 5;
			num = std::rand() % range + 1;

			switch (num) {
			case 1:
				msg = "Black Figures";
				numOfSelected = pManager->NumOfBlack();
				break;
			case 2:
				msg = "White Figures";
				numOfSelected = pManager->NumOfWhite();
				break;
			case 3:
				msg = "Red Figures";
				numOfSelected = pManager->NumOfRed();
				break;
			case 4:
				msg = "Green Figures";
				numOfSelected = pManager->NumOfGreen();
				break;
			case 5:
				msg = "Blue Figures";
				numOfSelected = pManager->NumOfBlue();
				break;
			}
		} while (numOfSelected == 0);
		pOut->PrintMessage("Select All " + msg);
		while (numOfSelected > 0) {
			pIn->GetPointClicked(pClicked.x, pClicked.y);
			CFigure* selected = pManager->GetFigure(pClicked.x, pClicked.y);
			//Checks if the user clicked on any icon
			if (pClicked.y >= 0 && pClicked.y < UI.ToolBarHeight) {
				int ClickedItemOrder = (pClicked.x / UI.MenuItemWidth);
				switch (ClickedItemOrder)
				{
				case ITM_PickByFigure:
					act = PICK_BY_FIGURE;
					break;
				case ITM_PickByColor:
					act = PICK_BY_COLOR;
					break;
				case ITM_TO_DRAW:
					act = TO_DRAW;
					break;
				case ITM_ExitProg:
					act = EXIT;
					break;
				default: act = EMPTY;	//A click on empty place in desgin toolbar
				}
				if (act != EMPTY) {
					ended = false;
					break;
				}
			}
			//checks if the user clicks on the drawing area
			if (selected == NULL) {
				continue;
			}
			//checks if the user selects a hidden figure
			if (selected->checkHidden()) {
				continue;
			}
			//creates a line pointer to check if the selected is not a line
			CLine* rPtr = dynamic_cast<CLine*>(selected);
			GfxInfo g1;
			g1 = selected->GetFigGfxInfo();
			//Switch case to check if the selected figure has the right color or not
			switch (num) {
			case 1: {
				GfxInfo g1;
				g1=selected->GetFigGfxInfo();
				if (rPtr != NULL) {
					if (g1.DrawClr == BLACK) {
						CorrectPicks++;
						numOfSelected--;
					}
					else {
						WrongPicks++;
					}
				}
				else {
					if (g1.FillClr == BLACK) {
						CorrectPicks++;
						numOfSelected--;
					}
					else {
						WrongPicks++;
					}
				}
				selected->Hide(true);
			}
					break;
			case 2: {
				GfxInfo g1;
				g1 = selected->GetFigGfxInfo();
				if (rPtr != NULL) {
					if (g1.DrawClr == WHITE) {
						CorrectPicks++;
						numOfSelected--;
					}
					else {
						WrongPicks++;
					}
				}
				else {
					if (g1.FillClr == WHITE) {
						CorrectPicks++;
						numOfSelected--;
					}
					else {
						WrongPicks++;
					}
				}
				selected->Hide(true);
			}
					break;
			case 3: {
				if (rPtr != NULL) {
					if (g1.DrawClr == RED) {
						CorrectPicks++;
						numOfSelected--;
					}
					else {
						WrongPicks++;
					}
				}
				else {
					if (g1.FillClr == RED) {
						CorrectPicks++;
						numOfSelected--;
					}
					else {
						WrongPicks++;
					}
				}
				selected->Hide(true);
			}
					break;
			case 4: {
				if (rPtr != NULL) {
					if (g1.DrawClr == GREEN) {
						CorrectPicks++;
						numOfSelected--;
					}
					else {
						WrongPicks++;
					}
				}
				else {
					if (g1.FillClr == GREEN) {
						CorrectPicks++;
						numOfSelected--;
					}
					else {
						WrongPicks++;
					}
				}
				selected->Hide(true);
			}
					break;

			case 5: {
				if (rPtr != NULL) {
					if (g1.DrawClr == BLUE) {
						CorrectPicks++;
						numOfSelected--;
					}
					else {
						WrongPicks++;
					}
				}
				else {
					if (g1.FillClr == BLUE) {
						CorrectPicks++;
						numOfSelected--;
					}
					else {
						WrongPicks++;
					}
				}
				selected->Hide(true);
			}
					break;
			}
			pOut->ClearDrawArea();
			pManager->UpdateInterface();
		}
		if (ended) {
			pOut->PrintMessage("Game Ended, Final score is : Correct picks= " + std::to_string(CorrectPicks) + " , Wrong picks= " + std::to_string(WrongPicks));
		}
		//unhides all figures and updates interface to restore everyting after the game ends
		pManager->Hide_UnhideAll(false);
		pManager->UpdateInterface();
		//if the game didn't end and the user interrupted it by clicking on any other action
		if (!ended) {
			pManager->ExecuteAction(act);
		}
	}
	//if the user didn't draw any shape before playing
	else {
		pOut->PrintMessage("You need to draw some shapes before you play");
	}
	
}

PickByColorAction::~PickByColorAction()
{
}
