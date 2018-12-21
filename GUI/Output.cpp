#include "Output.h"


Output::Output()
{
	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;
	
	UI.width = 1276;
	UI.height = 780;
	UI.wx = 5;
	UI.wy =5;

	
	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 60;
	UI.ColorBarHeight = 40;
	UI.ColorItemWidth = 40;
	UI.ResizeItemWidth = 40;
	UI.ResizeBarHeight = 40;
	UI.DrawColor = BLUE;	//Drawing color
	UI.FillColor = GREEN;	//Filling color
	UI.MsgColor = RED;		//Messages color
	UI.BkGrndColor = LIGHTGOLDENRODYELLOW;	//Background color
	UI.HighlightColor = MAGENTA;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = TURQUOISE;
	UI.PenWidth = 3;	//width of the figures frames
	UI.ResizeX = UI.wx + UI.MenuItemWidth * 7;
	UI.ResizeY = UI.wy + UI.ToolBarHeight;
	
	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Paint for Kids");
	
	CreateDrawToolBar();
	CreateStatusBar();
}


Input* Output::CreateInput() const
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int w, int h, int x, int y) const
{ 
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);	
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateToolBar() const {
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateDrawToolBar() const
{
	UI.InterfaceMode = MODE_DRAW;
	//You can draw the tool bar icons in any way you want.
	//Below is one possible way
	
	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem
	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_RECT] = "images\\MenuItems\\Menu_Rect.jpg";
	MenuItemImages[ITM_LINE] = "images\\MenuItems\\Menu_Line.jpg";
	MenuItemImages[ITM_TRI] = "images\\MenuItems\\Menu_Tri.jpg";
	MenuItemImages[ITM_RHOMBUS] = "images\\MenuItems\\Menu_Rhombus.jpg";
	MenuItemImages[ITM_ELLIPSE] = "images\\MenuItems\\Menu_Ellipse.jpg";
	MenuItemImages[ITM_DRAW_CLR] = "images\\MenuItems\\Menu_Draw_Color.jpg";
	MenuItemImages[ITM_FILL_CLR] = "images\\MenuItems\\Menu_Fill_Color.jpg";
	MenuItemImages[ITM_RESIZE] = "images\\MenuItems\\Menu_Resize.jpg";
	MenuItemImages[ITM_SWITCH] = "images\\MenuItems\\Menu_Switch.jpg";
	MenuItemImages[ITM_SELECT] = "images\\MenuItems\\Menu_Select.jpg";
	MenuItemImages[ITM_FRONT] = "images\\MenuItems\\Menu_Front.jpg";
	MenuItemImages[ITM_BACK] = "images\\MenuItems\\Menu_Back.jpg";
	MenuItemImages[ITM_DEL] = "images\\MenuItems\\Menu_Delete.jpg";
	MenuItemImages[ITM_CPY] = "images\\MenuItems\\Menu_Copy.jpg";
	MenuItemImages[ITM_CUT] = "images\\MenuItems\\Menu_Cut.jpg";
	MenuItemImages[ITM_PST] = "images\\MenuItems\\Menu_Paste.jpg";
	MenuItemImages[ITM_SAVE] = "images\\MenuItems\\Menu_Save.jpg";
	MenuItemImages[ITM_SAVEBT] = "images\\MenuItems\\Menu_SaveByType.jpg";
	MenuItemImages[ITM_LOAD] = "images\\MenuItems\\Menu_Load.jpg";
	MenuItemImages[ITM_EXIT] = "images\\MenuItems\\Menu_Exit.jpg";
	MenuItemImages[ITM_SOUND] = "images\\MenuItems\\unmute.jpg";
	

	//TODO: Prepare images for each menu item and add it to the list

	//Draw menu item one image at a time
	for(int i=0; i<DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);



	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	

}
//overloaded function to control sound button
void Output::CreateDrawToolBar(bool m)
{
	UI.InterfaceMode = MODE_DRAW;
	//You can draw the tool bar icons in any way you want.
	//Below is one possible way

	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem
	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_RECT] = "images\\MenuItems\\Menu_Rect.jpg";
	MenuItemImages[ITM_LINE] = "images\\MenuItems\\Menu_Line.jpg";
	MenuItemImages[ITM_TRI] = "images\\MenuItems\\Menu_Tri.jpg";
	MenuItemImages[ITM_RHOMBUS] = "images\\MenuItems\\Menu_Rhombus.jpg";
	MenuItemImages[ITM_ELLIPSE] = "images\\MenuItems\\Menu_Ellipse.jpg";
	MenuItemImages[ITM_DRAW_CLR] = "images\\MenuItems\\Menu_Draw_Color.jpg";
	MenuItemImages[ITM_FILL_CLR] = "images\\MenuItems\\Menu_Fill_Color.jpg";
	MenuItemImages[ITM_RESIZE] = "images\\MenuItems\\Menu_Resize.jpg";
	MenuItemImages[ITM_SWITCH] = "images\\MenuItems\\Menu_Switch.jpg";
	MenuItemImages[ITM_SELECT] = "images\\MenuItems\\Menu_Select.jpg";
	MenuItemImages[ITM_FRONT] = "images\\MenuItems\\Menu_Front.jpg";
	MenuItemImages[ITM_BACK] = "images\\MenuItems\\Menu_Back.jpg";
	MenuItemImages[ITM_DEL] = "images\\MenuItems\\Menu_Delete.jpg";
	MenuItemImages[ITM_CPY] = "images\\MenuItems\\Menu_Copy.jpg";
	MenuItemImages[ITM_CUT] = "images\\MenuItems\\Menu_Cut.jpg";
	MenuItemImages[ITM_PST] = "images\\MenuItems\\Menu_Paste.jpg";
	MenuItemImages[ITM_SAVE] = "images\\MenuItems\\Menu_Save.jpg";
	MenuItemImages[ITM_SAVEBT] = "images\\MenuItems\\Menu_SaveByType.jpg";
	MenuItemImages[ITM_LOAD] = "images\\MenuItems\\Menu_Load1.jpg";
	MenuItemImages[ITM_EXIT] = "images\\MenuItems\\Menu_Exit.jpg";
	if (!m) {
		MenuItemImages[ITM_SOUND] = "images\\MenuItems\\mute.jpg";
	}
	else {
		MenuItemImages[ITM_SOUND] = "images\\MenuItems\\unmute.jpg";
	}

	//TODO: Prepare images for each menu item and add it to the list

	//Draw menu item one image at a time
	for (int i = 0; i < DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);



	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::DrawColorPallete(int x) const //x -> 1 : Fill color , x-> 2 : Draw color
{
	string ColorPalleteImages[CLR_ITM_COUNT];
	ColorPalleteImages[CLR_BLACK] = "images\\Colors\\Color_Black.jpg";
	ColorPalleteImages[CLR_WHITE] = "images\\Colors\\Color_White.jpg";
	ColorPalleteImages[CLR_RED] = "images\\Colors\\Color_Red.jpg";
	ColorPalleteImages[CLR_GREEN] = "images\\Colors\\Color_Green.jpg";
	ColorPalleteImages[CLR_BLUE] = "images\\Colors\\Color_Blue.jpg";
	UI.ColorY = UI.wy + UI.ToolBarHeight;
	if(x==1)
		UI.ColorX = UI.wx + UI.MenuItemWidth*6;
	else if(x==2)
		UI.ColorX = UI.wx + UI.MenuItemWidth*5;

	for(int i=0; i<CLR_ITM_COUNT; i++)
		pWind->DrawImage(ColorPalleteImages[i], UI.ColorX + i*UI.ColorItemWidth, UI.ColorY, UI.ColorItemWidth, UI.ColorBarHeight);
}

/////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawResizePallete() const
{
	string ResizePalleteImages[RESIZE_ITM_COUNT];
	ResizePalleteImages[SIZE_1_4] = "images\\Sizes\\Size_Quarter.jpg";
	ResizePalleteImages[SIZE_1_2] = "images\\Sizes\\Size_Half.jpg";
	ResizePalleteImages[SIZE_2] = "images\\Sizes\\Size_Double.jpg";
	ResizePalleteImages[SIZE_4] = "images\\Sizes\\Size_Quad.jpg";
	for (int i = 0; i<RESIZE_ITM_COUNT; i++)
		pWind->DrawImage(ResizePalleteImages[i], UI.ResizeX + i * UI.ColorItemWidth, UI.ResizeY, UI.ColorItemWidth, UI.ColorBarHeight);
}

/////////////////////////////////////////////////////////////////////////////////////////

void Output::CreatePlayToolBar() const
{
	UI.InterfaceMode = MODE_PLAY;
	ClearToolBar();
	string PlayToolBarImages[PLAY_ITM_COUNT];

	PlayToolBarImages[ITM_PickByFigure] = "images\\MenuItems\\Menu_PickType.jpg";
	PlayToolBarImages[ITM_PickByColor] = "images\\MenuItems\\Menu_PickColor.jpg";
	PlayToolBarImages[ITM_TO_DRAW] = "images\\MenuItems\\Menu_Switch.jpg";
	PlayToolBarImages[ITM_ExitProg] = "images\\MenuItems\\Menu_Exit.jpg";

	for(int i=0; i<PLAY_ITM_COUNT; i++)
		pWind->DrawImage(PlayToolBarImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	///TODO: write code to create Play mode menu



	//TODO: Prepare images for each menu item and add it to the list [DONE]

	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

	///TODO: write code to create Play mode menu [DONE]
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
	
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearToolBar() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearColorPallete() const
{
	GfxInfo ClearRectangle;
	ClearRectangle.FillClr = UI.BkGrndColor;
	ClearRectangle.DrawClr = UI.BkGrndColor;
	ClearRectangle.BorderWdth = 0;
	ClearRectangle.isFilled = true;
	Point P1 = {UI.ColorX,UI.ColorY},
		  P2 = {UI.ColorX+UI.ColorItemWidth*5 , UI.ColorY + UI.ColorBarHeight};
	DrawRect(P1,P2,ClearRectangle,false);

}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight/1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntDrawColor() const	//get current drawing color
{	return UI.DrawColor;	}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntFillColor() const	//get current filling color
{	return UI.FillColor;	}
//////////////////////////////////////////////////////////////////////////////////////////
	
int Output::getCrntPenWidth() const		//get current pen width
{	return UI.PenWidth;	}

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

//Draw a Rectangle
void Output::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else			
		DrawingClr = RectGfxInfo.DrawClr;
	
	pWind->SetPen(DrawingClr,1);
	drawstyle style;
	if (RectGfxInfo.isFilled)	
	{
		style = FILLED;		
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else	
		style = FRAME;

	
	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);
	
}

//Draw a Line
void Output::DrawLine(Point P1, Point P2, GfxInfo LineGfxInfo, bool selected) const
{
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else			
		DrawingClr = LineGfxInfo.DrawClr;
	
	pWind->SetPen(DrawingClr,1);
	drawstyle style;
	if (LineGfxInfo.isFilled)	
	{
		style = FILLED;		
		pWind->SetBrush(LineGfxInfo.FillClr);
	}
	else	
		style = FRAME;

	
	pWind->DrawLine(P1.x, P1.y, P2.x, P2.y, style);
}

//Draw a Triangle
void Output::DrawTri(Point P1, Point P2, Point P3, GfxInfo TriGfxInfo, bool selected) const
{
	color DrawingClr;
	if(selected)
		DrawingClr = UI.HighlightColor;
	else
		DrawingClr = TriGfxInfo.DrawClr;

	pWind -> SetPen(DrawingClr,1);

	drawstyle style;

	if(TriGfxInfo.isFilled){
		style = FILLED;
		pWind-> SetBrush(TriGfxInfo.FillClr);
	}else{
		style = FRAME;
	}

	pWind -> DrawTriangle(P1.x,P1.y,P2.x,P2.y,P3.x,P3.y,style);
}

//Draw a Rhombus
void Output::DrawRhombus(Point P1, Point P2, Point P3, Point P4, GfxInfo RhombusGfxInfo, bool selected) const
{
	color DrawingClr;
	if(selected)
		DrawingClr = UI.HighlightColor;
	else
		DrawingClr = RhombusGfxInfo.DrawClr;

	pWind -> SetPen(DrawingClr,1);

	int xCoordinates[4]={P1.x,P2.x,P3.x,P4.x},
		yCoordinates[4]={P1.y,P2.y,P3.y,P4.y};

	drawstyle style;

	if(RhombusGfxInfo.isFilled){
		style = FILLED;
		pWind-> SetBrush(RhombusGfxInfo.FillClr);
	}else{
		style = FRAME;
	}

	pWind -> DrawPolygon(*&xCoordinates,*&yCoordinates,4,style);
}

//Draw a Ellipse
void Output::DrawEllipse(Point P1 , Point P2, GfxInfo EllipseGfxInfo, bool selected) const
{
	color DrawingClr;
	if(selected)
		DrawingClr = UI.HighlightColor;
	else
		DrawingClr = EllipseGfxInfo.DrawClr;

	pWind -> SetPen(DrawingClr,1);

	drawstyle style;

	if(EllipseGfxInfo.isFilled){
		style = FILLED;
		pWind-> SetBrush(EllipseGfxInfo.FillClr);
	}else{
		style = FRAME;
	}

	pWind -> DrawEllipse(P1.x,P1.y,P2.x,P2.y,style);
}

//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output()
{
	delete pWind;
}

