#pragma once
#include "Action.h"
#include "../ApplicationManager.h"
#include "../includeFiles/AllFigures.h"
class PasteAction : public Action
{
private:
	Point pClicked;
public:
	PasteAction(ApplicationManager * pApp);
	void ReadActionParameters();
	void Execute();
	~PasteAction();
};

