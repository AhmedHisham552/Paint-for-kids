#pragma once
#include "Action.h"
#include"../ApplicationManager.h"

class SaveAction :
	public Action
{
private:
	string name;
public:
	SaveAction(ApplicationManager* pApp);
	void ReadActionParameters();
	void Execute();
	~SaveAction();
};

