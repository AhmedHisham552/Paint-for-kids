#include "loadAction.h"
#include<iostream>
#include "../includeFiles/AllFigures.h"
#include <sstream>      
#include <string> 
using namespace std;

loadAction::loadAction(ApplicationManager * pApp) :Action(pApp)
{
	if (!pManager->getSound())
		PlaySound("Sounds\\Load.wav", NULL, SND_ASYNC);
}

void loadAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Enter file name : ");
	InputFile = "Savefile/" + pIn->GetSrting(pOut) + ".txt";
	pOut->ClearStatusBar();
}

void loadAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	ReadActionParameters();
	ifstream File(InputFile, ios::in);
	CFigure* Fig;
	string read;
	bool Empty = false;
	//checks if the file is open
	if (File.is_open()) {
		while (!File.eof()) {		//checks if the file didn't end
			getline(File, read); // Saves the line in STRING.
			if (read.find("Number") != -1) {
				istringstream iss(read);
				string word[2];
				int i = 0;
				while (getline(iss, read , ':')) {
					word[i] = read;
					i++;
				}
				if (stoi(word[1])!=0) {
						pManager->DeleteAllFigures();
						pOut->ClearDrawArea();
				}
				else {
						Empty = true;
						pOut->PrintMessage("File is empty");
						break;
				}
			}
			//if the figure is ellipse
			if (read.find("Ellipse")!=-1) {
				Fig = new CEllipse;
				Fig->Load(read);
				pManager->AddFigure(Fig);
			}
			//if the figure is triangle
			else if (read.find("Triangle")!=-1) {
				Fig = new CTriangle;
				Fig->Load(read);
				pManager->AddFigure(Fig);
			}
			//if the figure is rectangle
			else if (read.find("Rectangle")!=-1) {
				Fig = new CRectangle;
				Fig->Load(read);
				pManager->AddFigure(Fig);
			}
			//if the figure is rhombus
			else if (read.find("Rhombus")!=-1) {
				Fig = new CRhombus;
				Fig->Load(read);
				pManager->AddFigure(Fig);
			}
			//if the figure is line
			else if (read.find("Line")!=-1) {
				Fig = new CLine;
				Fig->Load(read);
				pManager->AddFigure(Fig);
			}
		}
		//if the file isn't empty
		if(!Empty)
			pOut->PrintMessage("Loaded Successfully");
		File.close();
	}
	//if the file doesn't exist
	else {
		pOut->PrintMessage("Couldn't find the file");

	}
}


loadAction::~loadAction()
{
}
