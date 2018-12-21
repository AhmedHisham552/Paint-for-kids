#pragma once
#include "Action.h"
class SelectAction :
	public Action
{
protected:
	Point pClicked;
public:
	SelectAction(ApplicationManager *pApp);
	void ReadActionParameters();
	void Execute();
	~SelectAction();
};

