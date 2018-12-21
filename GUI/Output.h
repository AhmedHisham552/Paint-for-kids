#ifndef OUPTUT_H
#define OUPTUT_H
#include "Input.h"
class Output	//The application manager should have a pointer to this class
{
private:	
	window* pWind;	//Pointer to the Graphics Window
public:
	Output();		

	window* CreateWind(int, int, int , int) const; //creates the application window
	void CreateDrawToolBar() const;	               //creates Draw mode toolbar & menu
	void CreateDrawToolBar(bool m);	
	void CreatePlayToolBar() const;	               //creates Play mode toolbar & menu
	void CreateStatusBar() const;	               //create the status bar
	void CreateToolBar() const;                    //create the tool bar 

	Input* CreateInput() const;                    //creates a pointer to the Input object	
	void ClearStatusBar() const;	               //Clears the status bar
	void ClearDrawArea() const;	                   //Clears the drawing area
	void ClearColorPallete() const;                //Clears the color pallete
	void ClearToolBar() const;                     //Clears the tool bar 
	
	// -- Figures Drawing functions
	void DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected = false) const;         //Draw a rectangle
	void DrawLine(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected=false) const;         //Draw a Line
	void DrawTri(Point P1, Point P2, Point P3, GfxInfo TriGfxInfo, bool selected=false) const; //Draw a triangle
	void DrawRhombus(Point P1, Point P2, Point P3, Point P4, GfxInfo RhombusGfxInfo, bool selected) const;                   //Draw a Rhombus
	void DrawEllipse(Point P1, Point P2, GfxInfo EllipseGfxInfo, bool selected) const;                   //Draw a Ellipse 
	
	void PrintMessage(string msg) const;	       //Print a message on Status bar

	color getCrntDrawColor() const;	               //get current drwawing color
	color getCrntFillColor() const;	               //get current filling color
	int getCrntPenWidth() const;		           //get current pen width
	void DrawColorPallete(int x) const;            //Draws color pallete

	void DrawResizePallete() const;

	
	~Output();
};

#endif