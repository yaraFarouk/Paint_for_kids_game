#include"SwitchToDraw.h"
#include "Figures/CFigure.h"

#include "ApplicationManager.h"

#include "GUI/Input.h"
#include "GUI/Output.h"


SwitchToDraw::SwitchToDraw(ApplicationManager* pApp) :Action(pApp)
{}
void SwitchToDraw::ReadActionParameters()
{
	if (pManager->IsAnyFigureIsSelected())
	{
		pManager->UnSelectAll();
	}
}
void SwitchToDraw::Execute()
{
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->CreateDrawToolBar();
	pOut->PrintMessage("Welcome to DrawMode :)");
	pManager->CallLoad();
}
void SwitchToDraw::UndoFig(CFigure* F)
{

}
void SwitchToDraw::RedoFig(CFigure* F)
{

}
