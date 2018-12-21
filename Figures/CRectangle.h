#ifndef CRECT_H
#define CRECT_H

#include "CFigure.h"

class CRectangle : public CFigure
{
private:
	Point Corner1;	//1st corner of rectangle 
	Point Corner2;  //2nd corner of rectangle
public:
	CRectangle();                                               //Default Constractor
	CRectangle(Point , Point, GfxInfo FigureGfxInfo );          //Non-default Constractor
	bool ChngFigSize(double figSize);                           //Change the size of rectangle
	bool PointInFigure(Point P1);                               //Check the point in rectangle or not
	virtual void Draw(Output* pOut) const;                      //Draw the rectangle on the screen
	void PrintInfo(Output* pOut);                               //Print the info the rectangle 
	int getWidth();                                             //Get the width of the rectangle
	int getHeight();                                            //Get the height of the rectangle 
	void Save(ofstream &OutFile);                               //Save the info of the rectangle in text file 
	void Load(string);                                          //Load the info of the rectangle from text file
	void Hide(bool);                                            //
	bool checkHidden();                                         //
	GfxInfo GetFigGfxInfo();                                    //Get the graphics info of the rectangle 
	void GetFigPoints(Point &P1, Point &P2);                    //Get the corners of the  rectangle
};

#endif