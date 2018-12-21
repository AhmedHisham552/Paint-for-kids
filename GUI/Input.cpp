#include "Input.h"
#include "Output.h"


Input::Input(window* pW) 
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int &x, int &y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string Input::GetSrting(Output *pO) const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction() const
{	
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_RECT:          return DRAW_RECT;
			case ITM_LINE:          return DRAW_LINE;
			case ITM_EXIT:          return EXIT;			
			case ITM_TRI:			return DRAW_TRI;
			case ITM_RHOMBUS:		return DRAW_RHOMBUS;
			case ITM_ELLIPSE:		return DRAW_ELLIPSE;
			case ITM_DRAW_CLR:	    return CHNG_DRAW_CLR;
			case ITM_FILL_CLR:	    return CHNG_FILL_CLR;
			case ITM_FRONT:			return BRING_FRONT;
			case ITM_BACK:			return BRING_BACK;
			//case ITM_PLAY:      return TO_PLAY;
			case ITM_SELECT:		return SELECT;
			case ITM_DEL: 			return DEL;
			case ITM_CPY:			return CPY;
			case ITM_CUT:			return CUT;
			case ITM_PST:			return PASTE;
			case ITM_RESIZE:		return RESIZE;
			case ITM_SAVE: 			return SAVE;
			case ITM_SAVEBT:	    return SAVE_BY_TYPE;
			case ITM_LOAD:          return LOAD;
			case ITM_SWITCH:        return TO_PLAY;	
			case ITM_SOUND:			return MUTE_UNMUTE;
			
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;	
		}
		
		
		//[3] User clicks on the status bar
		return STATUS;
	}
	else	//GUI is in PLAY mode
	{
		
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
			switch (ClickedItemOrder)
			{
				case ITM_PickByFigure: return PICK_BY_FIGURE;
				case ITM_PickByColor: return PICK_BY_COLOR;
				case ITM_TO_DRAW: return TO_DRAW;
				case ITM_ExitProg: return EXIT;
				default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		///TODO:
		//perform checks similar to Draw mode checks above
		//and return the correspoding action
		return TO_PLAY;	//just for now. This should be updated
	}	

}
}
/////////////////////////////////
ActionType Input::GetClr() const
{
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click
		//[1] If user clicks on the Toolbar
	if ( y >= UI.ColorY && y < UI.ColorY + UI.ColorBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = ((x-UI.ColorX) / UI.ColorItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case CLR_BLACK : return PICK_BLACK;
							 break;
			case CLR_WHITE : return PICK_WHITE;
							break;
			case CLR_RED : return PICK_RED;
							break;
			case CLR_BLUE : return PICK_BLUE;
							break;
			case CLR_GREEN : return PICK_GREEN;
					 break;
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}
			//[2] User clicks on the drawing area
		if ( y >= UI.ColorY+UI.ColorBarHeight && (x<UI.ColorX || x> UI.ColorX+UI.ColorItemWidth*5) && y< UI.height-UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
}
////////////////////////////////

ActionType Input::GetSize()	const 
{
	int x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click
									//[1] If user clicks on the Toolbar
	if (y >= UI.ResizeY && y < UI.ResizeY + UI.ResizeBarHeight)
	{
		//Check whick Menu item was clicked
		//==> This assumes that menu items are lined up horizontally <==
		int ClickedItemOrder = ((x - UI.ResizeX) / UI.ResizeItemWidth);
		//Divide x coord of the point clicked by the menu item width (int division)
		//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

		switch (ClickedItemOrder)
		{
		case SIZE_1_4: return PICK_QUARTER;
			break;
		case SIZE_1_2: return PICK_HALF;
			break;
		case SIZE_2: return PICK_DOUBLE;
			break;
		case SIZE_4: return PICK_QUAD;
			break;
		default: return EMPTY;	//A click on empty place in desgin toolbar
		}
	}
	//[2] User clicks on the drawing area
	if (y >= UI.ColorY + UI.ColorBarHeight && (x<UI.ColorX || x> UI.ColorX + UI.ColorItemWidth * 5) && y< UI.height - UI.StatusBarHeight)
	{
		return DRAWING_AREA;
	}

	//[3] User clicks on the status bar
	return STATUS;

}
	
Input::~Input()
{
}
