#pragma once
#include "cfigure.h"

class CLine :
	public CFigure
{
private:
	Point Corner1;	
	Point Corner2;
public:
	CLine();
	CLine(Point , Point, GfxInfo FigureGfxInfo );
	bool ChngFigSize(double figSize);
	virtual void Draw(Output* pOut) const;
	bool PointInFigure(Point P1);
	void PrintInfo(Output* pOut);
	void Save(ofstream &);
	void Hide(bool);
	GfxInfo GetFigGfxInfo();
	bool checkHidden();
	void Load(string);

	void GetFigPoints(Point &P1, Point &P2);
};

