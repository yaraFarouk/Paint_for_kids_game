#include "Redo.h"
#include "Figures/CFigure.h"

#include "ApplicationManager.h"

#include "GUI/Input.h"
#include "GUI/Output.h"


Redo::Redo(ApplicationManager* pApp, Action* A, CFigure* F) :Action(pApp)
{
	Act = A;
	Fig = F;
}

void Redo::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	if (pManager->Getispclicked())//pManager->GetRecordControl()->GetPclicked())//note here if play is clicked not record
	{

		Act = pManager->GetRecordControl()->GetActList()[pManager->getrr()].Actnxtoredo;//error is here as it must start from 0 then increase to 1, here its start from 2
		Fig = pManager->GetRecordControl()->GetActList()[pManager->getrr()].cftoredo;
		pManager->setrr(pManager->getrr()+1);
		pManager->setPcount((pManager->GetPcount()) + 1);

	}

}
void Redo::Execute()
{
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();
	if (Fig != NULL && Act != NULL)
	{
		//pOut->PrintMessage(to_string(pManager->getrndocount()));

		if (pManager->GetTheAlreadyAction() == TO_UNDO)
		{

			if (pManager->Getispclicked())//pManager->GetRecordControl()->GetPclicked())//note here if play is clicked not record
			{
				pManager->UnSelectAll();
				
				Fig->ChngDrawClr(pManager->GetRecordControl()->GetActList()[pManager->getredoinfo() - 1].cdraw);
				Fig->ChngFillClr(pManager->GetRecordControl()->GetActList()[pManager->getredoinfo() - 1].cfill);
				pManager->setredoinfo((pManager->getredoinfo()) - 1);

				if (pManager->getredoinfo() < 0)
				{
					pManager->setredoinfo(0);
				}
				//pManager->setPcount((pManager->GetPcount()) + 1);
				pManager->AddFigure(Fig);
				pManager->AddAction(Act);//to save for undo
				pManager->AddFigForUndo(Fig);//to save for undo
				Act->AddArrColor(Fig->GetColorIn());//to save for undo
				Act->AddArrPoint(Fig->MakeCenter());//to save for undo
				//Fig->Draw(pOut);
				pOut->PrintMessage("Redo The Last Action");
				//if (pManager->Getispclicked())//pManager->GetRecordControl()->GetPclicked())//note here if play is clicked not record
				//{
				//	pManager->setlastact(this);
				//	pManager->setlastfig(Fig);
				//	pManager->getundoedactionandfig();
				//	pManager->getredoedactionandfig(this, Fig);
				//	pManager->GetRecordControl()->GetActList()[pManager->getredoinfo()].cfill = Fig->GetFillColor();
				//	pManager->GetRecordControl()->GetActList()[pManager->getredoinfo()].cdraw = Fig->GetDrawColor();
				//	pManager->setredoinfo((pManager->getredoinfo()) + 1);
				//}
				//pManager->DeleteActionRedo();//to delete action from arr

			}
			else
			{
				pManager->UnSelectAll();

				pManager->AddAction(Act);//to save for undo
				pManager->AddFigForUndo(Fig);//to save for undo
				Act->AddArrColor(Fig->GetColorIn());//to save for undo
				Act->AddArrPoint(Fig->MakeCenter());//to save for undo
				pOut->PrintMessage("Redo The Last Action");
				Act->RedoFig(Fig);//call function 
				pManager->DeleteActionRedo();//to delete action from arr
			}
			
			/*if (pManager->isclicked())
			{
				Action* pAct = new Redo(pManager, Act, Fig);
				pManager->GetRecordControl()->AddAction(pAct);
				pManager->GetRecordControl()->Execute();
			}*/
		}
		else
		{
			pOut->PrintMessage("Can`t Redo The Last Action"); // if i dont make undo before redo
			pManager->DeleteActionRedo();//to delete action from arr

		}
	}
	else
		pOut->PrintMessage("Can`t Redo The Last Action");
	if (pManager->isclicked())
	{
		Action* pAct = new Redo(pManager,pManager->getlastact(), pManager->getlastfig());
		pManager->GetRecordControl()->AddAction(pAct);
		pManager->GetRecordControl()->Execute();
	}
	//pOut->ClearStatusBar();
}
void Redo::UndoFig(CFigure* F)
{

}
void Redo::RedoFig(CFigure* F)
{

}