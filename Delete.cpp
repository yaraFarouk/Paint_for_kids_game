#include "Delete.h"
#include "Figures/CFigure.h"

#include "ApplicationManager.h"
#include"ToRecord.h"
#include "GUI/Input.h"
#include "GUI/Output.h"


Delete::Delete(ApplicationManager* pApp) :Action(pApp)
{
	CountC = 0;//count for color undo
	CountIn = 0;//count for point undo
	CountIn2 = 0;
	CountC2 = 0;
}

void Delete::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();


}
void Delete::Execute()
{
	pManager->setlastact(this);

	Output* pOut = pManager->GetOutput();
	pManager->AddAction(this);
	this->SetAct(true);
	pOut->PrintMessage("Delete The Selected Figure");
	CFigure* ptr = pManager->GetTheSelected();//get the selected figure
	if (ptr != NULL)
	{
		pManager->IfNotUndo();

		AddArrPoint(ptr->MakeCenter());//add point
		AddArrColor(ptr->GetColorIn());//to add the information about color this figure in array to undo
		pManager->AddFigForUndo(ptr);//add this figure in array for undo
		pManager->UnSelectAll();
		ptr->DeleteFi();//function neded to delete
		pManager->UpdateInterface();
		pManager->DeleteFigure(ptr);//so the item to be selected it should be in the figure list to change the color it must be in the figure list as there ia an implemented function in somewhere depends on that
		ptr->SetIsDeleted(true);//draw this figure by back ground color to delete
		if (pManager->Getispclicked())//pManager->GetRecordControl()->GetPclicked())//note here if play is clicked not record
		{
			pManager->setPcount((pManager->GetPcount()) + 1);
			pManager->setlastact(this);
			pManager->setlastfig(ptr);
		    pManager->getundoedactionandfig();
			pManager->getredoedactionandfig(this, ptr);
			pManager->GetRecordControl()->GetActList()[pManager->getredoinfo()].cfill = ptr->GetFillColor();
			pManager->GetRecordControl()->GetActList()[pManager->getredoinfo()].cdraw = ptr->GetDrawColor();
			pManager->setredoinfo((pManager->getredoinfo()) + 1);
		}	
		
	}
	pOut->CreateStatusBar();
	pOut->CreateDrawToolBar();
	if (pManager->isclicked())
	{
		Action* pAct = new Delete(pManager);
		pManager->GetRecordControl()->AddAction(pAct);
		pManager->GetRecordControl()->Execute();
	}
}
void Delete::UndoFig(CFigure* F)
{
	F->ChngDrawClr(ArrColor[CountC - 1].DrawClr);//make the deleted figure take color befor deleted
	F->ChngFillClr(ArrColor[CountC - 1].FillClr);//make the deleted figure take color befor deleted
	CountC--;//decrease Count
	CountIn--;//decrease Count
	pManager->AddFigure(F);//re but this figure in figlist
	F->SetIsDeleted(false);

}
void Delete::RedoFig(CFigure* F)
{
	if (CountC2 > 0)
	{
		pManager->UnSelectAll();
		F->DeleteFi();//function neded to delete
		pManager->UpdateInterface();
		pManager->DeleteFigure(F);//so the item to be selected it should be in the figure list to change the color it must be in the figure list as there ia an implemented function in somewhere depends on that
	}
}