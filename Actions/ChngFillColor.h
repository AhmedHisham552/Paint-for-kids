#pragma once
#include "Action.h"
#include "../ApplicationManager.h"
#include "../GUI/input.h"
#include "../GUI/output.h"
class ChngFillColor :public Action
{
private:
	ActionType ChooseClr;            //Choose color action
	Output * pOut; Input* pIn;
public:
	ChngFillColor(ApplicationManager * pApp, Output* pOut, Input* pIn);
	void ReadActionParameters();
	void Execute();
	~ChngFillColor();
};

