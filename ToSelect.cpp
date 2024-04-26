#include "ToSelect.h"
#include "Figures/CFigure.h"

#include "ApplicationManager.h"
#include"ToRecord.h"
#include "GUI/Input.h"
#include "GUI/Output.h"


ToSelect::ToSelect(ApplicationManager* pApp) :Action(pApp)
{}

void ToSelect::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	if (pManager->Getispclicked())//pManager->GetRecordControl()->GetPclicked())//note here if play is clicked not record
	{
		p1 = pManager->GetRecordControl()->GetActList()[pManager->GetPcount()].p;//error is here as it must start from 0 then increase to 1, here its start from 2
		pManager->setPcount((pManager->GetPcount()) + 1);
	}
	else
	{
		pOut->PrintMessage("Please, select a figure");

		//Read user click on a figure
		pIn->GetPointClicked(p1.x, p1.y);
	}


}
void ToSelect::Execute()
{
	if (pManager->IsAnyFigureIsSelected())
	{
		pManager->UnSelectAll();
	}
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	ReadActionParameters();
	if (pManager->isclicked())
	{
		pManager->GetRecordControl()->GetActList()[pManager->GetRecordControl()->getActCount()].p = p1;
		Action* pAct = new ToSelect(pManager);
		pManager->GetRecordControl()->AddAction(pAct);
	}
	pManager->UnSelectAll();
	CFigure* fig = pManager->GetFigure(p1.x, p1.y);
	if (fig == NULL)
	{
		pOut->PrintMessage("there is no figure is selected");
	}
	else
	{
		if (pManager->isclicked())
		{
			pManager->GetRecordControl()->Execute();
		}
		fig->SetSelected(true);
	}

}
void ToSelect::UndoFig(CFigure* F)
{

}
void ToSelect::RedoFig(CFigure* F)
{

}
