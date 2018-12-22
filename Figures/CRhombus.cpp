#include "CRhombus.h"
#include <iostream>
#include <sstream>
#include <string> 
using namespace std;

CRhombus::CRhombus()
{
	
}

CRhombus::CRhombus(Point P, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	this->Corner1 = P;
	d = 150;
	P1.x = Corner1.x + d; P1.y = Corner1.y;
	P2.x = Corner1.x; P2.y = Corner1.y + d;
	P3.x = Corner1.x - d; P3.y = Corner1.y;
	P4.x = Corner1.x; P4.y = Corner1.y - d;
	type = Figure_Type::RHUMBOS;
	figSize = 1.0;
}

bool CRhombus::ChngFigSize(double figSize)
{
	Point tempP1{ 0,0 }, tempP2{ 0,0 }, tempP3{ 0,0 }, tempP4{ 0,0 };
	

	tempP2.x = P2.x - Corner1.x; tempP2.y = P2.y - Corner1.y;
	tempP4.x = P4.x - Corner1.x; tempP4.y = P4.y - Corner1.y;
	tempP2.x *= figSize; tempP2.y *= figSize;
	tempP4.x *= figSize; tempP4.y *= figSize;
	tempP2.x += Corner1.x; tempP2.y += Corner1.y;
	tempP4.x += Corner1.x; tempP4.y += Corner1.y;
	if ((tempP2.y >= UI.ToolBarHeight && tempP2.y < UI.height - UI.StatusBarHeight) && (tempP4.y >= UI.ToolBarHeight && tempP4.y < UI.height - UI.StatusBarHeight)) {
		P1.x -= Corner1.x; P1.y -= Corner1.y;
		P3.x -= Corner1.x; P3.y -= Corner1.y;
		P1.x *= figSize; P1.y *= figSize;
		P3.x *= figSize; P3.y *= figSize;
		P1.x += Corner1.x; P1.y += Corner1.y;
		P3.x += Corner1.x; P3.y += Corner1.y;
		P2.x = tempP2.x;
		P2.y = tempP2.y;
		P4.x = tempP4.x;
		P4.y = tempP4.y;

		this->figSize = this->figSize * figSize;
		return true;
	}
	return false;
}

void CRhombus::Draw(Output* pOut) const
{	

	pOut->DrawRhombus(P1,P2,P3,P4, FigGfxInfo, Selected);
}

bool CRhombus::PointInFigure(Point P1)
{
	// Check if the point lies inside the rhombus or no
	bool condition = ( (abs((P1.x - Corner1.x)*1.0 / (d*figSize)) + abs((P1.y - Corner1.y)*1.0 / (d*figSize))) <= 1 );
	if (condition) {
		return true;
	}
	return false;
}

Point CRhombus::getCenter()
{
	return Corner1;
}

double CRhombus::GetFigSize() // returns the figure size of the rhombus
{
	return this->figSize;
}

void CRhombus::PrintInfo(Output * pOut)
{
}

void CRhombus::Save(ofstream &OutFile) {
	OutFile << "Rhombus " << ID << " " << Corner1.x << " " << Corner1.y << " " << figSize << " ";
}
void CRhombus::Hide(bool h)
{
	isHidden = h;
}

void CRhombus::Load(string s)
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
	this->type = RHUMBOS;
	this->ID = counter;
	this->Corner1.x = stoi(arr[2]);
	this->Corner1.y = stoi(arr[3]);
	this->figSize = stof(arr[4]);
	//Checks the draw color
	if (arr[5] == "BLACK") {
		DrawColor = BLACK;
	}
	else if (arr[5] == "BLUE") {
		DrawColor = BLUE;
	}
	else if (arr[5] == "WHITE") {
		DrawColor = WHITE;
	}
	else if (arr[5] == "RED") {
		DrawColor = RED;
	}
	else if (arr[5] == "GREEN") {
		DrawColor = GREEN;
	}
	//Checks the fill color
	if (arr[6] == "BLACK") {
		FillColor = BLACK;
	}
	else if (arr[6] == "BLUE") {
		FillColor = BLUE;
	}
	else if (arr[6] == "WHITE") {
		FillColor = WHITE;
	}
	else if (arr[6] == "RED") {
		FillColor = RED;
	}
	else if (arr[6] == "GREEN") {
		FillColor = GREEN;
	}
	this->FigGfxInfo.DrawClr = DrawColor;
	this->FigGfxInfo.FillClr = FillColor;
	this->isHidden = false;
	this->Selected = false;
	this->d = 150;
	P1.x =(int)(Corner1.x + (d*figSize)); P1.y = Corner1.y;
	P2.x = Corner1.x; P2.y =(int)(Corner1.y + (d*figSize));
	P3.x = (int)(Corner1.x - (d*figSize)); P3.y = Corner1.y;
	P4.x = Corner1.x; P4.y = (int)(Corner1.y - (d*figSize));
}

GfxInfo CRhombus::GetFigGfxInfo()
{
	return FigGfxInfo;
}

bool CRhombus::checkHidden()
{
	return isHidden;
}

void CRhombus::GetFigPoints(Point & P)
{
	P = Corner1;
}
