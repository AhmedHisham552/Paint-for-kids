#pragma once
#include "Action.h"
#include "../ApplicationManager.h"
#include "../GUI/input.h"
#include "../GUI/output.h"
class ChngDrawColor : public Action
{
private:
	ActionType ChooseClr;            //Choose color action
	Output * pOut; Input* pIn;
public:
	ChngDrawColor(ApplicationManager * pApp, Output* pOut, Input* pIn);
	void ReadActionParameters();
	void Execute();
	~ChngDrawColor();
};

