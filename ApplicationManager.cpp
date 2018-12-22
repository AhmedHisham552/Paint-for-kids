#include "ApplicationManager.h"
#include "includeFiles/AllFigures.h"
#include "includeFiles/AllActions.h"
#include <Windows.h>
#include <MMSystem.h>



//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	SelectedFig = NULL;
	Clipboard = NULL;
	CutFig = NULL;
	FigCount = 0;
		
	//Create an array of figure pointers and set them to NULL		
	for(int i=0; i<MaxFigCount; i++)
		FigList[i] = NULL;	
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;
	
	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
		case DRAW_RECT:
			pAct = new AddRectAction(this);
			break;

		case DRAW_LINE:
			pAct = new AddLineAction(this);
			break;

		case DRAW_TRI:
			pAct = new AddTriAction(this);
			break;

		case DRAW_ELLIPSE:
			pAct = new AddEllipseAction(this);
			break;

		case DRAW_RHOMBUS:
			pAct = new AddRhomAction(this);
			break;
		case TO_DRAW:
			if (!muted)
				PlaySound("Sounds\\toDraw.wav", NULL, SND_ASYNC);
			pOut->CreateDrawToolBar(!muted);
			pOut->ClearStatusBar();
			break;
		case TO_PLAY:
			if (!muted)
				PlaySound("Sounds\\toPlay.wav", NULL, SND_ASYNC);
			pOut->CreatePlayToolBar();
			pOut->ClearStatusBar();
			break;

		case SELECT:
			pAct = new SelectAction(this);
			break;
		
		case CHNG_DRAW_CLR:
			pAct = new ChngDrawColor(this, pOut, pIn);
			break;

		case CHNG_FILL_CLR:
			pAct = new ChngFillColor(this, pOut, pIn);
			break;

		case RESIZE:
			pAct = new ResizeFigure(this, pOut, pIn);
			break;
		case CPY:
			pAct = new CopyAction(this);
			break;
		case CUT:
			pAct = new CutAction(this);
			break;
		case PASTE:
			pAct = new PasteAction(this);
			break;
		case BRING_FRONT:
			pAct = new BringFrontAction(this);
			break;
		case BRING_BACK:
			pAct = new BringBackAction(this);
			break;
		case DEL:
			pAct = new DeleteAction(this);
			break;
		case SAVE:
			pAct = new SaveAction(this);
			break;
		case SAVE_BY_TYPE:
			pAct = new SaveByTypeAction(this);
			break;
		case LOAD:
			pAct = new loadAction(this);
			break;
		case PICK_BY_FIGURE:
			pAct = new PickByFigureAction(this);
			break;
		case PICK_BY_COLOR:
			pAct = new PickByColorAction(this);
			break;
		case MUTE_UNMUTE:
			pAct = new SoundAction(this);
			pOut->CreateDrawToolBar(muted);
			break;
		case EXIT:
			pAct = new ExitAction(this);
			break;
		
		case STATUS:	//a click on the status bar ==> no action
			return ;
	}
	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
		pAct = NULL;
	}
}
bool ApplicationManager::CheckDrawings()
{
	for (int i = 0; i < FigCount; i++) {
		if (FigList[i] != NULL) {
			return true;
		}
	}
	return false;
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if (FigCount < MaxFigCount) {
		FigList[FigCount++] = pFig;
		CFigure::counter++;
	}
}

//Get the cut figure 
CFigure* ApplicationManager::GetCutFig() {
	return CutFig;
}

////////////////////////////////////////////////////////////////////////////////////
//Sets the cut figure
void ApplicationManager::SetCutFig(CFigure* pFig) {
	if (pFig != NULL)
		pFig->ChngFillClr(UI.CutColor);
	CutFig = pFig;
}
////////////////////////////////////////////////////////////////////////////////////
//Get the figure given a point 
CFigure *ApplicationManager::GetFigure(int x, int y) const
{
	Point P1;
	P1.x = x;
	P1.y = y;
	for (int i = FigCount - 1; i >= 0; i--) {
		if (FigList[i] == NULL)
			continue;
		if (FigList[i]->PointInFigure(P1)) {
			return FigList[i];
		}
	}
	return NULL;
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL


	//Add your code here to search for a figure given a point x,y	
	//Remember that ApplicationManager only calls functions do NOT implement it.
}

//Adds a figure to the top of the figure list
void ApplicationManager::AddFigureOnTop(CFigure * pFig)
{
	if (FigCount < MaxFigCount) {
		for (int i = FigCount - 1; i >= 0; i--) {
			FigList[i + 1] = FigList[i];			// shifts the figures 
		}
		FigCount++;
		FigList[0] = pFig;
	}
}

//Deletes a figure
void ApplicationManager::DeleteFigure(CFigure* pFig) {
		for (int i = 0; i < FigCount ; i++) {
			if (FigList[i] == pFig) {
				delete FigList[i];
				for (int j = i; j < FigCount - 1; j++) { // shifts the figures after figure i
					FigList[j] = FigList[j + 1];
				}
				FigList[FigCount - 1] = NULL;
				FigCount--;
				pOut->ClearDrawArea();
				break;
			}
		}
}
////////////////////////////////////////////////////////////////////////////////////
//Deselect all the selected figures
void ApplicationManager::DeselectAll()
{
	//Loop over the figList, finds the selected item and deselect it
	for (int i = FigCount - 1; i >= 0; i--) {
		if (FigList[i] == NULL)
			continue;
		if (FigList[i]->IsSelected()) {
			FigList[i]->SetSelected(false);
			FigList[i]->ChngDrawClr(FigList[i]->getPrevDrawColor());
			break;
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////
//Delete the selected figure from list
void ApplicationManager::DeleteSelectedFigure()
{
	if (SelectedFig != NULL) {

		int index;
		for (int i = 0; i < FigCount; i++) {
			if (FigList[i] == SelectedFig) {
				index = i;
				break;
			}
		}

		for (int i = index; i < FigCount - 1; i++) {
			FigList[i] = FigList[i + 1];
		}

		FigCount--;
		SelectedFig = NULL;
		pOut->ClearDrawArea();
	}
	else {
		pOut->PrintMessage("No figure is selected");
	}

}
////////////////////////////////////////////////////////////////////////////////////
//Delete all the figures from the list
void ApplicationManager::DeleteAllFigures() {
	for (int i = 0; i < FigCount; i++) {
		delete FigList[i];
		FigList[i] = NULL;
	}
	FigCount = 0;
	CFigure::counter = 1;
	pOut->ClearDrawArea();
}
////////////////////////////////////////////////////////////////////////////////////
//
void ApplicationManager::Hide_UnhideAll(bool h)
{
	for (int i = 0; i < FigCount; i++) {
		FigList[i]->Hide(h);
	}
}
////////////////////////////////////////////////////////////////////////////////////
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{	
	for (int i = 0; i < FigCount; i++) {
		if ((FigList[i]->checkHidden())==false) {
			FigList[i]->Draw(pOut);	//Call Draw function (virtual member fn)
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////
//save all figures function on the user interface
void ApplicationManager::SaveAll(ofstream &OutFile ) {
	OutFile << getcolorname(UI.DrawColor) << "  " << getcolorname(UI.FillColor) << endl;
	OutFile << "Number of Figures :" << FigCount << endl;
		for (int i = 0; i < FigCount; i++)
		{
			FigList[i]->Save(OutFile);
			if (FigList[i]->IsSelected())
				OutFile << getcolorname(FigList[i]->getPrevDrawColor());
			else
				OutFile << getcolorname(FigList[i]->getDrawColor());


			CLine *ptrLine = dynamic_cast<CLine*>(FigList[i]);
			if (ptrLine != NULL)
			{
				OutFile << endl;
			}
			else {
				OutFile << " " << getcolorname(FigList[i]->getFillColor()) << endl;
			}
			OutFile << endl;
		}
}
////////////////////////////////////////////////////////////////////////////////////
//Save the figures by the selected type icon
void ApplicationManager::SaveByType(ofstream &OutFile, Figure_Type Figtype)
{
	OutFile << getcolorname(UI.DrawColor) << "  " << getcolorname(UI.FillColor) << endl;
	OutFile << "Number of Figures :";
	int x = Figtype;
	switch (x) {
	case RECTANGLE:
		OutFile << NumOfrect() << endl;
		break;
	case TRIANGLE:
		OutFile << NumOfTris() << endl;
		break;
	case RHUMBOS:
		OutFile << NumOfRhom() << endl;
		break;
	case ELLIPSE:
		OutFile << NumOfEli() << endl;
		break;
	case LINE:
		OutFile << NumOfLines() << endl;
		break;
	}

	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->type == Figtype) {
			FigList[i]->Save(OutFile);
			if (FigList[i]->IsSelected())
				OutFile << getcolorname(FigList[i]->getPrevDrawColor());
			else
				OutFile << getcolorname(FigList[i]->getDrawColor());


			CLine *ptrLine = dynamic_cast<CLine*>(FigList[i]);
			if (ptrLine != NULL)
			{
				OutFile << endl;
			}
			else {
				OutFile << " " << getcolorname(FigList[i]->getFillColor()) << endl;
			}
			OutFile << endl;
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////
//function to get the name of colors of figures on the user interface
string ApplicationManager::getcolorname(color fig)
{
	if (fig == BLACK)  
		return "BLACK";
	else if (fig == GREEN)
		return "GREEN";
	else if (fig == BLUE)
		return "BLUE";
	else if (fig == RED)
		return "RED";
	else if (fig == WHITE)
		return "WHITE";
	else return "ERROR";
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////
//==================================================================================//
//							Clipboard Management Functions							//
//==================================================================================//

void ApplicationManager::SetClipboard(CFigure* pFig) 
{
	this->Clipboard = pFig;
}
////////////////////////////////////////////////////////////////////////////////////
//
void ApplicationManager::SetSelectedFig(CFigure * pFig)
{
	this->SelectedFig = pFig;
}
////////////////////////////////////////////////////////////////////////////////////
//
void ApplicationManager::ClearClipboard()
{
	if (Clipboard!=NULL)
		delete Clipboard;
	Clipboard = NULL;
}
////////////////////////////////////////////////////////////////////////////////////
//
CFigure * ApplicationManager::GetSelectedFig()
{
	return this->SelectedFig;
}
////////////////////////////////////////////////////////////////////////////////////
//
CFigure * ApplicationManager::GetClipboardFig()
{
	return this->Clipboard;
}
void ApplicationManager::setSound(bool b)
{
	muted = b;
}
bool ApplicationManager::getSound()
{
	return muted;
}
////////////////////////////////////////////////////////////////////////////////////
//get the number of the rectangles
int ApplicationManager::NumOfrect() {
	CRectangle* rect;
	int number = 0;
	for (int i = 0; i < FigCount; i++) {
		rect = dynamic_cast<CRectangle*>(FigList[i]);
		if (rect != NULL)
			number++;
	}
	return number;
}
////////////////////////////////////////////////////////////////////////////////////
//get the number of the triangles
int ApplicationManager::NumOfTris() {
	CTriangle* tri;
	int number = 0;
	for (int i = 0; i < FigCount; i++) {
		tri = dynamic_cast<CTriangle*>(FigList[i]);
		if (tri != NULL)
			number++;
	}
	return number;
}
////////////////////////////////////////////////////////////////////////////////////
//get the number of the ellipses
int ApplicationManager::NumOfEli() {
	CEllipse* eli;
	int number = 0;
	for (int i = 0; i < FigCount; i++) {
		eli = dynamic_cast<CEllipse*>(FigList[i]);
		if (eli != NULL)
			number++;
	}
	return number;
}
////////////////////////////////////////////////////////////////////////////////////
//get the number on rhombuses
int ApplicationManager::NumOfRhom() {
	CRhombus* rhom;
	int number = 0;
	for (int i = 0; i < FigCount; i++) {
		rhom = dynamic_cast<CRhombus*>(FigList[i]);
		if (rhom != NULL)
			number++;
	}
	return number;
}
////////////////////////////////////////////////////////////////////////////////////
//get the number of lines
int ApplicationManager::NumOfLines() {
	CLine* line;
	int number = 0;
	for (int i = 0; i < FigCount; i++) {
		line = dynamic_cast<CLine*>(FigList[i]);
		if (line != NULL)
			number++;
	}
	return number;
}
////////////////////////////////////////////////////////////////////////////////////
//get the number of the black figures
int ApplicationManager::NumOfBlack() {
	GfxInfo g1;
	int number = 0;
	for (int i = 0; i < FigCount; i++) {
		g1 = FigList[i]->GetFigGfxInfo();
		CLine* rPtr = dynamic_cast<CLine*>(FigList[i]);
		if (rPtr != NULL) {
			if (g1.DrawClr == BLACK) {
				number++;
			}
		}
		else {
			if (g1.FillClr == BLACK) {
				number++;
			}
		}
	}
	return number;
}
////////////////////////////////////////////////////////////////////////////////////
//get the number of white figures
int ApplicationManager::NumOfWhite() {
	GfxInfo g1;
	int number = 0;
	for (int i = 0; i < FigCount; i++) {
		g1 = FigList[i]->GetFigGfxInfo();
		CLine* rPtr = dynamic_cast<CLine*>(FigList[i]);
		if (rPtr != NULL) {
			if (g1.DrawClr == WHITE) {
				number++;
			}
		}
		else {
			if (g1.FillClr == WHITE) {
				number++;
			}
		}
	}
	return number;
}
////////////////////////////////////////////////////////////////////////////////////
//get the number of red figures
int ApplicationManager::NumOfRed() {
	GfxInfo g1;
	int number = 0;
	for (int i = 0; i < FigCount; i++) {
		g1 = FigList[i]->GetFigGfxInfo();
		CLine* rPtr = dynamic_cast<CLine*>(FigList[i]);
		if (rPtr != NULL) {
			if (g1.DrawClr == RED) {
				number++;
			}
		}
		else {
			if (g1.FillClr == RED) {
				number++;
			}
		}
	}
	return number;
}
////////////////////////////////////////////////////////////////////////////////////
//get the number of green figures
int ApplicationManager::NumOfGreen() {
	GfxInfo g1;
	int number = 0;
	for (int i = 0; i < FigCount; i++) {
		g1 = FigList[i]->GetFigGfxInfo();
		CLine* rPtr = dynamic_cast<CLine*>(FigList[i]);
		if (rPtr != NULL) {
			if (g1.DrawClr == GREEN) {
				number++;
			}
		}
		else {
			if (g1.FillClr == GREEN) {
				number++;
			}
		}
	}
	return number;
}
////////////////////////////////////////////////////////////////////////////////////
//get the number of blue figures
int ApplicationManager::NumOfBlue() {
	GfxInfo g1;
	int number = 0;
	for (int i = 0; i < FigCount; i++) {
		g1 = FigList[i]->GetFigGfxInfo();
		CLine* rPtr = dynamic_cast<CLine*>(FigList[i]);
		if (rPtr != NULL) {
			if (g1.DrawClr == BLUE) {
				number++;
			}
		}
		else {
			if (g1.FillClr == BLUE) {
				number++;
			}
		}
	}
	return number;
}
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<FigCount; i++)
		delete FigList[i];
	delete pIn;
	delete pOut;
	
}
