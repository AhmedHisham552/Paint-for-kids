#pragma once
#include "Action.h"
#include "../ApplicationManager.h"
#include "../includeFiles/AllFigures.h"
class ResizeFigure :public Action
{
private:
	ActionType Size;            //Choose color action
	Output * pOut; Input* pIn;
public:
	ResizeFigure(ApplicationManager * pApp, Output* pOut, Input* pIn);
	void ReadActionParameters();
	void Execute();
	~ResizeFigure();
};

