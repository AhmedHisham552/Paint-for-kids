#include "ResizeFigure.h"



ResizeFigure::ResizeFigure(ApplicationManager * pApp, Output* pOut, Input* pIn) :Action(pApp)
{
	this->pOut = pOut;
	this->pIn = pIn;
	if (!pManager->getSound())
		PlaySound("Sounds\\Resize.wav", NULL, SND_ASYNC);
}

void ResizeFigure::ReadActionParameters() {
}


void ResizeFigure::Execute() {
	if (pManager->GetSelectedFig() == NULL) {
		pOut->PrintMessage("No figure is selected");
		return;
	}
	pOut->PrintMessage("A click on Resize button");
	pOut->DrawResizePallete();
	Size = pIn->GetSize();
	bool resized;
	switch (Size) {
		case PICK_QUARTER:
			resized = (pManager->GetSelectedFig())->ChngFigSize(0.25);
			if (resized) {
				pOut->PrintMessage("Figure resized to quarter it's size");
			}
			else {
				pOut->PrintMessage("Can't resize the figure out of the drawing area");
			}
			break;
		case PICK_HALF: 
			resized = (pManager->GetSelectedFig())->ChngFigSize(0.5);
			if (resized) {
				pOut->PrintMessage("Figure resized to half it's size");
			}
			else {
				pOut->PrintMessage("Can't resize the figure out of the drawing area");
			}
			break;
		case PICK_DOUBLE:   
			resized = (pManager->GetSelectedFig())->ChngFigSize(2);
			if (resized) {
				pOut->PrintMessage("Figure resized to double it's size");
			}
			else {
				pOut->PrintMessage("Can't resize the figure out of the drawing area");
			}
			break;
		case PICK_QUAD:
			resized = (pManager->GetSelectedFig())->ChngFigSize(4);
			if (resized) {
				pOut->PrintMessage("Figure resized to four it's size");
			}
			else {
				pOut->PrintMessage("Can't resize the figure out of the drawing area");
			}
			break;
	}
	pOut->ClearDrawArea();
}

ResizeFigure::~ResizeFigure()
{
}
