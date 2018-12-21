#ifndef ADD_TRI_ACTION_H
#define ADD_TRI_ACTION_H

#include "Action.h"

//Add Rectangle Action class
class AddTriAction: public Action
{
private:
	Point P1, P2 , P3; //Rectangle Corners
	GfxInfo TriGfxInfo;
	bool valid = true;
public:
	AddTriAction(ApplicationManager *pApp);

	//Reads rectangle parameters
	virtual void ReadActionParameters();
	
	//Add rectangle to the ApplicationManager
	virtual void Execute() ;
	
};

#endif