#ifndef CFIGURE_H
#define CFIGURE_H

#include "..\defs.h"
#include "..\GUI\Output.h"
#include <fstream>

//The types of figures
enum Figure_Type {
	RECTANGLE,
	TRIANGLE,
	RHUMBOS,
	LINE,
	ELLIPSE
};
//Base class for all figures
class CFigure
{
protected:
	int ID;		                //Each figure has an ID
	bool Selected;              //true if the figure is selected.
	GfxInfo FigGfxInfo;      	//Figure graphis info
	color PrevDrawColor;        //
	bool isHidden=false;        //

public:
	CFigure();                                                     //Default Constractor
	Figure_Type type;                                              //the type of figures                                       
	CFigure(GfxInfo FigureGfxInfo);                                //Non-Default Constractor 
	static int counter;         //count the numbeer of created figures in the list
	void SetSelected(bool s);	                                   //select/unselect the figure
	bool IsSelected() const;	                                   //check whether fig is selected
	virtual bool PointInFigure(Point P1) = 0;                      //check whether the point is in the figure or not
	virtual void Draw(Output* pOut) const  = 0 ;		           //Draw the figure
	virtual void Hide(bool)=0;                                     //
	void ChngDrawClr(color Dclr);	                               //changes the figure's drawing color
	void ChngFillClr(color Fclr);	                               //changes the figure's filling color
	virtual bool ChngFigSize(double figSize);	                   //changes the figue's size
	virtual void GetFigPoints(Point &P1);                          //gets point of figure
	virtual void GetFigPoints(Point &P1, Point &P2);               //gets 2 points of figure
	virtual void GetFigPoints(Point &P1, Point &P2, Point &P3);    //gets 3 points of figure
	virtual GfxInfo GetFigGfxInfo();                               //get the graphics info of the figure 
	virtual double GetFigSize();								   //get the fig size
	virtual bool checkHidden() = 0;                                //
	virtual void Load(string) = 0;	                               //Load the figure parameters to the file
	void setPrevDrawColor(color c);                                //
	color getPrevDrawColor();                                      //
	color getDrawColor();                                          //get the draw color of the figure
	color getFillColor();                                          //get the fill color of the figure
	virtual void PrintInfo(Output* pOut) = 0;	                   //print all figure info on the status bar
	virtual void Save(ofstream &OutFile) = 0;                      //Save the figure parameters to the file
	int getID();
};
#endif