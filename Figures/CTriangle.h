#ifndef CTRI_H
#define CTRI_H

#include "CFigure.h"

class CTriangle : public CFigure
{
private:
	Point Corner1;	
	Point Corner2;
	Point Corner3;
public:
	CTriangle();
	CTriangle(Point , Point, Point , GfxInfo FigureGfxInfo );
	bool ChngFigSize(double figSize);
	virtual void Draw(Output* pOut) const;
	bool PointInFigure(Point P1);
	void PrintInfo(Output* pOut);
	void Save(ofstream &);
	void Hide(bool);
	GfxInfo GetFigGfxInfo();
	bool checkHidden();
	void Load(string);

	void GetFigPoints(Point &P1, Point &P2, Point &P3);
};

#endif