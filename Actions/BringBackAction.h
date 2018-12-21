#pragma once
#include "Action.h"
#include "../ApplicationManager.h"
#include "../includeFiles/AllFigures.h"
class BringBackAction :
	public Action
{
public:
	BringBackAction(ApplicationManager * pApp);
	void ReadActionParameters();
	void Execute();
	~BringBackAction();
};

