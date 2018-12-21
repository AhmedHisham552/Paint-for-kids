#include "CRectangle.h"
#include<iostream>
#include <sstream>      // std::istringstream
#include <string> 
#include "../ApplicationManager.h"
using namespace std;
CRectangle::CRectangle()  
{
	
}
//Rectangle Constractor
CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
	type = Figure_Type::RECTANGLE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Rectagle Change Figure Size 
bool CRectangle::ChngFigSize(double figSize)
{
	Point tempP1{ 0,0 }, tempP2{ 0,0 };
	Point C = { (Corner1.x + Corner2.x) / 2 , (Corner1.y + Corner2.y) / 2 };
	tempP1.x = Corner1.x - C.x; tempP1.y = Corner1.y - C.y;
	tempP2.x = Corner2.x - C.x; tempP2.y = Corner2.y - C.y;
	tempP1.x = tempP1.x * figSize; tempP1.y = tempP1.y * figSize;
	tempP2.x = tempP2.x * figSize; tempP2.y = tempP2.y * figSize;
	tempP1.x += C.x; tempP1.y += C.y;
	tempP2.x += C.x; tempP2.y += C.y;

	if ((tempP1.y >= UI.ToolBarHeight && tempP1.y < UI.height - UI.StatusBarHeight) && (tempP2.y >= UI.ToolBarHeight && tempP2.y < UI.height - UI.StatusBarHeight)) {
		Corner1.x = tempP1.x;
		Corner1.y = tempP1.y;
		Corner2.x = tempP2.x;
		Corner2.y = tempP2.y;
		return true;
	}
	return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//function to check if the point is in figure or not
bool CRectangle::PointInFigure(Point P1)
{
	bool inX = ((Corner1.x < P1.x) && (P1.x < Corner2.x)) || ((Corner2.x < P1.x) && (P1.x < Corner1.x));
	bool inY = ((Corner1.y < P1.y) && (P1.y < Corner2.y)) || ((Corner2.y < P1.y) && (P1.y < Corner1.y));

	if ( inX && inY ) {
		return true;
	}
	else {
		return false;
	}
	
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Draw the rectangle 
void CRectangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawRect(Corner1, Corner2, FigGfxInfo, Selected);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//print info of rectangle  
void CRectangle::PrintInfo(Output * pOut)
{ 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//get the width of the rectangle
int CRectangle::getWidth()
{
	return abs(Corner1.x - Corner2.x);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//get the hight of the rectangle
int CRectangle::getHeight()
{
	return abs(Corner1.y - Corner2.y);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//save the rectangle info in text file
void CRectangle::Save(ofstream &OutFile) {
	OutFile << "Rectangle " << ID << " " << Corner1.x << " " << Corner1.y << " " << Corner2.x << " " << Corner2.y << " ";
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//load the saved info of the rectangle from text file
void CRectangle::Load(string s)
{
	string word = s;
	istringstream iss(s);
	string arr[10];
	int k = 0;
	color DrawColor, FillColor;
	while (getline(iss, word, ' '))
	{
		arr[k] = word;
		k++;
	}
	this->type = RECTANGLE;
	this->ID = counter;
	this->Corner1.x = stoi(arr[2]);
	this->Corner1.y = stoi(arr[3]);
	this->Corner2.x = stoi(arr[4]);
	this->Corner2.y = stoi(arr[5]);
	//Checks the draw color
	if (arr[6] == "BLACK") {
		DrawColor = BLACK;
	}
	else if (arr[6] == "BLUE") {
		DrawColor = BLUE;
	}
	else if (arr[6] == "WHITE") {
		DrawColor = WHITE;
	}
	else if (arr[6] == "RED") {
		DrawColor = RED;
	}
	else if (arr[6] == "GREEN") {
		DrawColor = GREEN;
	}
	//Checks the fill color
	if (arr[7] == "BLACK") {
		FillColor = BLACK;
	}
	else if (arr[7] == "BLUE") {
		FillColor = BLUE;
	}
	else if (arr[7] == "WHITE") {
		FillColor = WHITE;
	}
	else if (arr[7] == "RED") {
		FillColor = RED;
	}
	else if (arr[7] == "GREEN") {
		FillColor = GREEN;
	}
	this->FigGfxInfo.DrawClr = DrawColor;
	this->FigGfxInfo.FillClr = FillColor;
	this->isHidden = false;
	this->Selected = false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CRectangle::Hide(bool h)
{
	isHidden = h;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CRectangle::checkHidden()
{
	return isHidden;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//get the rectangle graphics figure info
GfxInfo CRectangle::GetFigGfxInfo()
{
	return FigGfxInfo;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//get the rectangle corners 
void CRectangle::GetFigPoints(Point &P1, Point &P2)
{
	P1 = Corner1;
	P2 = Corner2;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
