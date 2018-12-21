#pragma once
#include "Action.h"
#include"../ApplicationManager.h"
class SoundAction :
	public Action
{
public:
	SoundAction(ApplicationManager* pApp);
	void Execute();
	void ReadActionParameters();
	~SoundAction();
};

