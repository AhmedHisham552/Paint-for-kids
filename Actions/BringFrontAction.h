#pragma once
#include "Action.h"
#include "../ApplicationManager.h"
#include "../includeFiles/AllFigures.h"
class BringFrontAction : public Action
{
private:
public:
	BringFrontAction(ApplicationManager * pApp);
	void ReadActionParameters();
	void Execute();
	~BringFrontAction();
};

