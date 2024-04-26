#include"SwitchToPlay.h"
#include "Figures/CFigure.h"

#include "ApplicationManager.h"

#include "GUI/Input.h"
#include "GUI/Output.h"


SwitchToPlay::SwitchToPlay(ApplicationManager* pApp) :Action(pApp)
{}
void SwitchToPlay::ReadActionParameters()
{
	if (pManager->IsAnyFigureIsSelected())
	{
		pManager->UnSelectAll();
	}
}
void SwitchToPlay::Execute()
{
	ReadActionParameters();
	//pManager->SaveAll();
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->CreatePlayToolBar();
	pIn->ClearDrawToolBar();
	pOut->PrintMessage("Welcome to PlayMode :)");
	pManager->CallSave();
}
void SwitchToPlay::UndoFig(CFigure* F)
{

}
void SwitchToPlay::RedoFig(CFigure* F)
{

}
