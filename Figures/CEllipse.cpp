#include "CEllipse.h"
#include<iostream>
#include <sstream>      // std::istringstream
#include <string> 
#include "../ApplicationManager.h"
using namespace std;
CEllipse::CEllipse() { }
////////////////////////////////////////////////////////////////////////////////////
CEllipse::CEllipse(Point Corner1,  GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	this->Corner1 = Corner1;
	dx = 93.75, dy = 150;
	P2 = { Corner1.x + dx, Corner1.y + dy}; //Upper right corner
	P3 = { Corner1.x - dx, Corner1.y - dy}; //Lower left corner
	type=Figure_Type::ELLIPSE;
	figSize = 1.0;
}
////////////////////////////////////////////////////////////////////////////////////
//change the figure size
bool CEllipse::ChngFigSize(double figSize) 
{
	Point tempP2{ 0,0 }, tempP3{ 0,0 };
	Point C = { (P2.x + P3.x) / 2 , (P2.y + P3.y) / 2 };
	tempP2.x = P2.x - C.x; tempP2.y = P2.y - C.y;
	tempP3.x = P3.x - C.x; tempP3.y = P3.y - C.y;
	tempP2.x *= figSize; tempP2.y *= figSize;
	tempP3.x *= figSize; tempP3.y *= figSize;
	tempP2.x += C.x; tempP2.y += C.y;
	tempP3.x += C.x; tempP3.y += C.y;
	if ((tempP2.y >= UI.ToolBarHeight && tempP2.y < UI.height - UI.StatusBarHeight) && (tempP3.y >= UI.ToolBarHeight && tempP3.y < UI.height - UI.StatusBarHeight)) {
		P2.x = tempP2.x;
		P2.y = tempP2.y;
		P3.x = tempP3.x;
		P3.y = tempP3.y;
		this->figSize = this->figSize * figSize;
		return true;
	}
	return false;

}

double CEllipse::GetFigSize() // returns the figure size of the ellipse
{
	return figSize;
}
////////////////////////////////////////////////////////////////////////////////////
//Draw the Ellipse
void CEllipse::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawEllipse(P2, P3,  FigGfxInfo, Selected);
}
////////////////////////////////////////////////////////////////////////////////////
//Check if the point in the figure or not
bool CEllipse::PointInFigure(Point Corner1)
{
	bool condition = (pow( (Corner1.x - this->Corner1.x)*1.0 / dx , 2)+pow((Corner1.y - this->Corner1.y)*1.0 / dy, 2) <= 1);
	if (condition) {
		return true;
	}
	return false;
}
////////////////////////////////////////////////////////////////////////////////////
//Print all the info of the ellipse
void CEllipse::PrintInfo(Output * pOut)
{
}
////////////////////////////////////////////////////////////////////////////////////
//Save all the info of the ellipse in text file
void CEllipse::Save(ofstream &OutFile) {
	OutFile << "Ellipse " << ID << " " << Corner1.x << " " << Corner1.y << " ";
}
////////////////////////////////////////////////////////////////////////////////////
//
void CEllipse::Hide(bool h)
{
	isHidden = h;
}
////////////////////////////////////////////////////////////////////////////////////
//load the ellipse info from saved file text
void CEllipse::Load(string s)
{
	string word=s;
	istringstream iss(s);
	string arr[10];
	int k = 0;
	color DrawColor,FillColor;
	while (getline(iss, word, ' '))
	{
		arr[k] = word;
		k++;
	}
	this->type = RECTANGLE;
	this->ID = counter;
	this->Corner1.x = stoi(arr[2]);
	this->Corner1.y = stoi(arr[3]);
	//Checks the draw color
	if (arr[4] == "BLACK") {
		DrawColor = BLACK;
	}
	else if (arr[4] == "BLUE") {
		DrawColor = BLUE;
	}
	else if (arr[4] == "WHITE") {
		DrawColor = WHITE;
	}
	else if (arr[4] == "RED") {
		DrawColor = RED;
	}
	else if (arr[4] == "GREEN") {
		DrawColor = GREEN;
	}
	//Checks the fill color
	if (arr[5] == "BLACK") {
		FillColor = BLACK;
	}
	else if (arr[5] == "BLUE") {
		FillColor = BLUE;
	}
	else if (arr[5] == "WHITE") {
		FillColor = WHITE;
	}
	else if (arr[5] == "RED") {
		FillColor = RED;
	}
	else if (arr[5] == "GREEN") {
		FillColor = GREEN;
	}
	this->FigGfxInfo.DrawClr = DrawColor;
	this-> FigGfxInfo.FillClr = FillColor;
	this->isHidden = false;
	this->Selected = false;
	dx = 93.75, dy = 150;
	P2 = { Corner1.x + dx, Corner1.y + dy }; //Upper right corner
	P3 = { Corner1.x - dx, Corner1.y - dy }; //Lower left corner
}
////////////////////////////////////////////////////////////////////////////////////
//get the graphics info of the ellipse
GfxInfo CEllipse::GetFigGfxInfo()
{
	return FigGfxInfo;
}
////////////////////////////////////////////////////////////////////////////////////
//
bool CEllipse::checkHidden()
{
	return isHidden;
}
////////////////////////////////////////////////////////////////////////////////////
//get the point of the ellipse
void CEllipse::GetFigPoints(Point & Corner1)
{
	Corner1 = this->Corner1;
}
////////////////////////////////////////////////////////////////////////////////////