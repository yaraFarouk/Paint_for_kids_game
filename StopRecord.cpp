#include"StopRecord.h"
#include "Figures/CFigure.h"

#include "ApplicationManager.h"

#include "GUI/Input.h"
#include "GUI/Output.h"


StopRecord::StopRecord(ApplicationManager* pApp) :Action(pApp)
{}
void StopRecord::ReadActionParameters()
{
	if (pManager->IsAnyFigureIsSelected())
	{
		pManager->UnSelectAll();
	}
}
void StopRecord::Execute()
{
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();
	if (pManager->isclicked())
	{
		pManager->seticclicked(false);
		pOut->PrintMessage("stop recording");
	}
	else
	{
		pOut->PrintMessage("You did't record anythig to stop it!");
	}
}
void StopRecord::UndoFig(CFigure* F)
{

}
void StopRecord::RedoFig(CFigure* F)
{

}
