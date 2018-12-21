#pragma once
#include "Action.h"
class PickByColorAction :
	public Action
{
	Point pClicked;
public:
	PickByColorAction(ApplicationManager* pApp);
	void ReadActionParameters();
	void Execute();
	~PickByColorAction();
};

