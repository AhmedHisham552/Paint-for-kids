#pragma once
#include "Action.h"
class PickByFigureAction :
	public Action
{
	Point pClicked;

public:
	PickByFigureAction(ApplicationManager* pApp);
	void ReadActionParameters();
	void Execute();
	~PickByFigureAction();
};

