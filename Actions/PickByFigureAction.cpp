#include "PickByFigureAction.h"
#include "../ApplicationManager.h"
#include "../includeFiles/AllFigures.h"
#include<iostream>



PickByFigureAction::PickByFigureAction(ApplicationManager *pApp):Action(pApp)
{
	if (!pManager->getSound())
		PlaySound("Sounds\\Pickbyfigure.wav", NULL, SND_ASYNC);
}

void PickByFigureAction::ReadActionParameters()
{
	
}

void PickByFigureAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	int CorrectPicks = 0;
	int WrongPicks = 0;
	int numOfSelected = 0;
	int num;
	bool ended = true;
	ActionType act = EMPTY;
	string msg;
	//checks if there is drawings then generates a random number to select a random figure
	if (pManager->CheckDrawings()) {
		do {
			int range = 5;
			num = std::rand() % range + 1;
			
			switch (num) {
			case 1: {
				msg = "Lines";
				numOfSelected = pManager->NumOfLines();

			}
					break;
			case 2: {
				msg = "Rectangles";
				numOfSelected = pManager->NumOfrect();
			}
					break;
			case 3: {
				msg = "Triangles";
				numOfSelected = pManager->NumOfTris();
			}
					break;
			case 4: {
				msg = "Rhombuses";
				numOfSelected = pManager->NumOfRhom();
			}
					break;
			case 5: {
				msg = "Elipses";
				numOfSelected = pManager->NumOfEli();
			}
					break;
			}
		} while (numOfSelected == 0);
		pOut->PrintMessage("Select All " + msg);
		//Game loop
		while (numOfSelected > 0) {
			pIn->GetPointClicked(pClicked.x, pClicked.y);
			CFigure* selected = pManager->GetFigure(pClicked.x, pClicked.y);
			//checks if the user clicks on any action
			if (pClicked.y >= 0 && pClicked.y < UI.ToolBarHeight) {
				int ClickedItemOrder = (pClicked.x / UI.MenuItemWidth);
				switch (ClickedItemOrder)
				{
				case ITM_PickByFigure: 
					act= PICK_BY_FIGURE;
					break;
				case ITM_PickByColor: 
					act= PICK_BY_COLOR;
					break;
				case ITM_TO_DRAW: 
					act= TO_DRAW;
					break;
				case ITM_ExitProg: 
					act= EXIT;
					break;
				default: act= EMPTY;	//A click on empty place in desgin toolbar
				}
				if (act != EMPTY) {
					ended = false;
					break;
				}
			}
			//checks if the user clicked on an empty area in the drawing area
			if (selected == NULL) {
				continue;
			}
			//checks if the user clicked on an hidden figure and ignores the click
			if (selected->checkHidden()) {
				continue;
			}
			//checks if the user selected a correct or wrong figure
			switch (num) {
			case 2: {
				CRectangle* rPtr = dynamic_cast<CRectangle*>(selected);
				if (rPtr != NULL) {
					CorrectPicks++;
					numOfSelected--;
				}
				else {
					WrongPicks++;
				}
				selected->Hide(true);
			}
				break;
			case 1: {
				CLine* rPtr = dynamic_cast<CLine*>(selected);
				if (rPtr != NULL) {
					CorrectPicks++;
					numOfSelected--;
				}
				else {
					WrongPicks++;
				}
				selected->Hide(true);
			}
				break;
			case 3: {
				CTriangle* rPtr = dynamic_cast<CTriangle*>(selected);
				if (rPtr != NULL) {
					CorrectPicks++;
					numOfSelected--;
				}
				else {
					WrongPicks++;
				}
				selected->Hide(true);
			}
				break;
			case 4: {
				CRhombus* rPtr = dynamic_cast<CRhombus*>(selected);
				if (rPtr != NULL) {
					CorrectPicks++;
					numOfSelected--;
				}
				else {
					WrongPicks++;
				}
				selected->Hide(true);
			}
				break;
			
			case 5: {
				CEllipse* rPtr = dynamic_cast<CEllipse*>(selected);
				if (rPtr != NULL) {
					CorrectPicks++;
					numOfSelected--;
				}
				else {
					WrongPicks++;
				}

				selected->Hide(true);
			}
				break;
			}
			//updates interface to hide selected figures
			pOut->ClearDrawArea();
			pManager->UpdateInterface();
		}
		if (ended) {
			pOut->PrintMessage("Game Ended, Final score is : Correct picks= " + std::to_string(CorrectPicks) + " , Wrong picks= " + std::to_string(WrongPicks));
		}
		//unhides all the figures 
		pManager->Hide_UnhideAll(false);
		pManager->UpdateInterface();
		if (!ended) {
			pManager->ExecuteAction(act);
		}
	}
	//if the user didn't draw shapes before playing
	else {
		pOut->PrintMessage("You need to draw some shapes before you play");
	}
}


PickByFigureAction::~PickByFigureAction()
{
}
