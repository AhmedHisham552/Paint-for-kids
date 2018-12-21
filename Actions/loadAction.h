#pragma once
#include "Action.h"
#include "../ApplicationManager.h"
#include<string>
#include<fstream>
using namespace std;
class loadAction :
	public Action
{
private:
	string InputFile;
public:
	loadAction(ApplicationManager * pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	~loadAction();
};

