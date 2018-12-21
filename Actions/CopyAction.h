#pragma once
#include "Action.h"
#include "../ApplicationManager.h"
#include "../includeFiles/AllFigures.h"

class CopyAction : public Action
{
private:
	Point pClicked;
public:
	CopyAction(ApplicationManager * pApp);
	void ReadActionParameters();
	void Execute();
	~CopyAction();

};

