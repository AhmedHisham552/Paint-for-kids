#ifndef CRHOM_H
#define CRHOM_H

#include "CFigure.h"

class CRhombus : public CFigure
{
private:
	double figSize;
	int d;						//delta to be added to corner
	Point Corner1,P1,P2,P3,P4;
public:
	CRhombus();
	CRhombus(Point , GfxInfo FigureGfxInfo );
	bool ChngFigSize(double figSize);
	virtual void Draw(Output* pOut) const;
	bool PointInFigure(Point P1);
	void GetFigPoints(Point & P1);
	Point getCenter();
	double GetFigSize();
	void PrintInfo(Output* pOut);
	void Save(ofstream &);
	void Hide(bool);
	void Load(string);

	GfxInfo GetFigGfxInfo();
	bool checkHidden();
};

#endif