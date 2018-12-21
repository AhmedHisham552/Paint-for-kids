#pragma once
#include "Action.h"

class DeleteAction :
	public Action
{
protected:
	Point pClicked;
public:
	DeleteAction(ApplicationManager *pApp);
	void ReadActionParameters();
	void Execute();
	~DeleteAction();
};

