#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

//This file contains some global constants and definitions to be used in the project.
enum ActionType //The actions supported (you can add more if needed)
{
	DRAW_LINE,		//Draw Line
	DRAW_RECT,		//Draw Rectangle
	DRAW_TRI,		//Draw Triangle
	DRAW_RHOMBUS,		//Draw Rhombus
	DRAW_ELLIPSE,		//Draw Ellipse
	CHNG_DRAW_CLR,	//Change the drawing color
	CHNG_FILL_CLR,	//Change the filling color
	RESIZE,			//Resizes the figure
	SELECT,			//Open the selection mode
	DEL,			//Delete a figure(s)
	CPY,			//Copies a figure to the clipboard
	CUT,			//Cuts the figure to the clipboard
	PASTE,			//Pastes the figure from the clipboard
	SAVE,			//Save the whole graph to a file
	SAVE_BY_TYPE,	//Save the all the figures that have a specific type
	LOAD,			//Load a graph from a file
	EXIT,			//Exit the application
	PICK_BY_FIGURE, //pick the figure
	PICK_BY_COLOR,  //pich the color
	DRAWING_AREA,	//A click on the drawing area
	STATUS,			//A click on the status bar
	EMPTY,			//A click on empty place in the toolbar
	TO_DRAW,		//Switch interface to Draw mode
	TO_PLAY,	    //Switch interface to Play mode
	BRING_FRONT,	//Brings the selected figure to front
	BRING_BACK,		//Brings the selected figure to back
	MUTE_UNMUTE,	//controls the sound of the application
	PICK_BLACK,     //pick the black color     
	PICK_WHITE,     //pick the white color 
	PICK_RED,       //pick the red color
	PICK_GREEN,     //pick the green color
	PICK_BLUE,      //pick the blue color 

	PICK_HALF,		//picked half size
	PICK_QUARTER,	//picked quarter size
	PICK_DOUBLE,	//picked double size
	PICK_QUAD		//picked quad size
};

struct Point	//To be used for figures points
{ int x,y; };

struct GfxInfo	//Graphical info of each figure (you may add more members)
{
	color DrawClr;	//Draw color of the figure
	color FillClr;	//Fill color of the figure
	bool isFilled;	//Figure Filled or not
	int BorderWdth;	//Width of figure borders

};

#endif