#pragma once
#include "Action.h"
#include"../ApplicationManager.h"

class SaveByTypeAction :
	public Action
{
private:
	string name;
	Figure_Type type;
	int number;
	bool flag=false;
public:
	SaveByTypeAction(ApplicationManager* pApp);
	void ReadActionParameters();
	void Execute();
	~SaveByTypeAction();
};

