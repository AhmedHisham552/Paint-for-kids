#pragma once
#include "Action.h"
#include "../ApplicationManager.h"
#include "../includeFiles/AllFigures.h"
class CutAction :
	public Action
{
private:
	Point pClicked;
public:
	CutAction(ApplicationManager * pApp);
	void ReadActionParameters();
	void Execute();
	~CutAction();
};

