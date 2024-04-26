#include "AddCircleAction.h"
#include "Undo.h"
#include"Actions/Action.h"
#include "ApplicationManager.h"

#include "GUI\input.h"
#include "GUI\Output.h"

Undo::Undo(ApplicationManager* pApp, Action* A, CFigure* F) :Action(pApp) {
	Act = A;
	Fig = F;
}
void Undo::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	if (pManager->Getispclicked())//pManager->GetRecordControl()->GetPclicked())//note here if play is clicked not record
	{
		Act = pManager->GetRecordControl()->GetActList()[pManager->getundocount()-1].ActTosnd;//error is here as it must start from 0 then increase to 1, here its start from 2
		Fig = pManager->GetRecordControl()->GetActList()[pManager->getundocount()-1].cf;
		pManager->setundocount((pManager->getundocount()) - 1);
		if (pManager->getundocount() < 0)
		{
			pManager->setundocount(0);
		}
		pManager->setPcount((pManager->GetPcount()) + 1);

	}
	
}

//Execute the action
void Undo::Execute()
{
	pManager->UnSelectAll();
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	if (Act != NULL && Fig != NULL)
	{
		Act->AddArrColorRedo(Fig->GetColorIn());
		Act->AddArrPointRedo(Fig->MakeCenter());//add point
		pOut->PrintMessage("Undo The Last Action");
		pManager->AddActionRedo(Act);
		pManager->AddFigForRedo(Fig);
		if (pManager->isclicked())
		{
			Action* pAct = new Undo(pManager, Act, Fig);
			pManager->GetRecordControl()->AddAction(pAct);
			pManager->GetRecordControl()->Execute();
		}
			pManager->DeleteAction();
			Act->UndoFig(Fig);
	}
	else
	pOut->PrintMessage("Can`t Undo The Last Action");
	pOut->CreateDrawToolBar();
	pOut->CreateStatusBar();
}
void Undo::UndoFig(CFigure* F)
{

}
void Undo::RedoFig(CFigure* F)
{

}