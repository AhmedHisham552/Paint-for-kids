#ifndef CELLI_H
#define CELLI_H

#include "CFigure.h"

class CEllipse : public CFigure
{
private:
	Point Corner1, P2, P3;					   //Corner point and 2 point for resize
	int dx, dy;								   //Delta varibles to add to the corner
	double figSize;							   //Indicates the figure size
public:
	CEllipse();                                //Default constractor
	CEllipse(Point , GfxInfo FigureGfxInfo );  //Non-default constractor
	bool ChngFigSize(double figSize);          //Change the size of the ellipse
	double GetFigSize();					   //Returns the figure size
	virtual void Draw(Output* pOut) const;     //Draw the Ellipse
	bool PointInFigure(Point P1);              //Check if the point is in the ellipse or not
	void PrintInfo(Output* pOut);              //Print the info of the Ellipse
	void Save(ofstream &OutFile);              //Save the info of the ellipse in text file
	void Hide(bool h);                         //
	void Load(string);                         //Load the ellipse from the saved text file
	GfxInfo GetFigGfxInfo();                   //Get the graphics info of the ellipse 
	bool checkHidden();                        //
	void GetFigPoints(Point &P1);              //Get the points of the ellipse
};

#endif