#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H
#include "DEFS.h"
#include "Figures\CFigure.h"
#include "GUI\input.h"
#include "GUI\output.h"

//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxFigCount = 200 };	//Max no of figures

private:
	int FigCount;		            //Actual number of figures
	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)
	CFigure* SelectedFig;           //Pointer to the selected figure
	CFigure* Clipboard;             //Pointer to the copied/cut figure
	CFigure* CutFig;                //Pointer to the cut figure 
	GfxInfo gfxInfo;                //to be used with draw function of the class Ouput
	//Pointers to Input and Output classes
	Input *pIn;                     //Pointer to the input class
	Output *pOut;                   //pointer to the output class
	bool muted = false;
public:	
	ApplicationManager(); 
	~ApplicationManager();
	// -- Action-Related Functions
	//Reads the input command from the user and returns the corresponding action type
	ActionType GetUserAction() const;         //Get the user action 
	void ExecuteAction(ActionType) ;          //Creates an action and executes it
	bool CheckDrawings();					  //Checks if there is Figures Drawn	
	// -- Figures Management Functions
	void AddFigure(CFigure* pFig);            //Adds a new figure to the FigList
	CFigure *GetCutFig();
	void SetCutFig(CFigure * pFig);
	CFigure *GetFigure(int x, int y) const;
	void AddFigureOnTop(CFigure* pFig);
	//Search for a figure given a point inside the figure
	void DeselectAll();                       //Unselect the selected figure 
	void DeleteSelectedFigure();              //Delete the selected figure 
	void DeleteFigure(CFigure* pFig);         //Delete the figure
	void DeleteAllFigures();                  //Delete all figures
	void Hide_UnhideAll(bool);                //
	// -- Interface Management Functions
	Input *GetInput() const;                  //Return pointer to the input
	Output *GetOutput() const;                //Return pointer to the output
	int NumOfrect();                          //number of the rectangles
	int NumOfTris();                          //number of the triangles
	int NumOfEli();                           //number of the ellipses
	int NumOfRhom();                          //number of the rhombuses
	int NumOfLines();                         //number of the lines  
	int NumOfBlack();                         //number of the black figures
	int NumOfWhite();                         //number of the white figures
	int NumOfRed();                           //number of the red figures
	int NumOfGreen();                         //number of the green figures
	int NumOfBlue();                          //number of the blue figures
	void UpdateInterface() const;	          //Redraws all the drawing window	
	void SaveByType(ofstream &,Figure_Type);  //Save the figures by the selected type from icons 
	void SaveAll(ofstream &);                 //Save the figures drawn on the screen
	string getcolorname(color);               //get color name of the figures
	// -- ClipboardFig & SelectedFig Management Functions
	void SetClipboard(CFigure* pFig);         //
	void SetSelectedFig(CFigure* pFig);       //
	void ClearClipboard();                    //
	CFigure* GetSelectedFig();                //
	CFigure* GetClipboardFig();               //
	void setSound(bool);
	bool getSound();
};

#endif