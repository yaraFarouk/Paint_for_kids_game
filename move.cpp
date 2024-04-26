#include "Move.h"
#include "Figures/CFigure.h"
#include"ToRecord.h"
#include "ApplicationManager.h"
#include "GUI/Input.h"
#include "GUI/Output.h"

Move::Move(ApplicationManager* pApp) :Action(pApp)
{
	CountC = 0;//count for color undo
	CountIn = 0;//count for point undo
	CountIn2 = 0;//count for point redo
	CountC2 = 0;
}

void Move::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	//Read user click on a figure
	if (pManager->Getispclicked())//pManager->GetRecordControl()->GetPclicked())//note here if play is clicked not record
	{
		p1 = pManager->GetRecordControl()->GetActList()[pManager->GetPcount()].p;//error is here as it must start from 0 then increase to 1, here its start from 2
		pManager->setPcount((pManager->GetPcount()) + 1);
	}
	else
	{
		pOut->PrintMessage("click at a point to move the figure");
		pIn->GetPointClicked(p1.x, p1.y);
	}
}
void Move::Execute()
{
	pManager->setlastact(this);

	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();

	CFigure* fig = pManager->GetTheSelected();
	if (fig != NULL)
	{
		AddArrPoint(fig->MakeCenter());//add point
		AddArrColor(fig->GetColorIn());//add color
		pManager->AddAction(this);
		this->SetAct(true);
		pManager->AddFigForUndo(fig);
		if (fig->GetFillingStatus())
		{
	
			color cdraw = fig->GetDrawColor();
			color cfill = fig->GetFillColor();
			fig->ChngDrawClr(UI.BkGrndColor);//change the draw color to back ground color to delete
			fig->ChngFillClr(UI.BkGrndColor);
			pManager->UnSelectAll();
			fig->Draw(pOut);//draw this figure by back ground color to delete
			fig->ChngDrawClr(cdraw);
			fig->ChngFillClr(cfill);
			pManager->rearrange(fig);
			fig->movefigure(p1.x, p1.y, pOut);
			pOut->CreateDrawToolBar();
			pOut->CreateStatusBar();
			pOut->PrintMessage("the figure is moved");
			pManager->IfNotUndo();

			if (pManager->Getispclicked())//pManager->GetRecordControl()->GetPclicked())//note here if play is clicked not record
			{
				pManager->setlastact(this);
				pManager->setlastfig(fig);
				pManager->getundoedactionandfig();
				pManager->getredoedactionandfig(this, fig);
				pManager->GetRecordControl()->GetActList()[pManager->getredoinfo()].cfill = fig->GetFillColor();
				pManager->GetRecordControl()->GetActList()[pManager->getredoinfo()].cdraw = fig->GetDrawColor();
				pManager->setredoinfo((pManager->getredoinfo()) + 1);
			}
		}
		else
		{
			color cdraw = fig->GetDrawColor();
			fig->ChngDrawClr(UI.BkGrndColor);//change the draw color to back ground color to delete
			pManager->UnSelectAll();
			fig->Draw(pOut);//draw this figure by back ground color to delete
			fig->ChngDrawClr(cdraw);//change the draw color to back ground color to delete
			pManager->rearrange(fig);
			fig->movefigure(p1.x, p1.y, pOut);
			pOut->CreateDrawToolBar();
			pOut->CreateStatusBar();
			pOut->PrintMessage("the figure is moved");

			if (pManager->Getispclicked())//pManager->GetRecordControl()->GetPclicked())//note here if play is clicked not record
			{
				pManager->setlastact(this);
				pManager->setlastfig(fig);
				pManager->getundoedactionandfig();
				pManager->getredoedactionandfig(this, fig);
				pManager->GetRecordControl()->GetActList()[pManager->getredoinfo()].cfill = fig->GetFillColor();
				pManager->GetRecordControl()->GetActList()[pManager->getredoinfo()].cdraw = fig->GetDrawColor();
				pManager->setredoinfo((pManager->getredoinfo()) + 1);
			}
		}
	}
	else
	{
		pOut->PrintMessage("Please, Select the figure first");
	}
	if (pManager->isclicked())
	{
		pManager->GetRecordControl()->GetActList()[pManager->GetRecordControl()->getActCount()].p = p1;
		Action* pAct = new Move(pManager);
		pManager->GetRecordControl()->AddAction(pAct);
		pManager->GetRecordControl()->Execute();
	}
}void Move::UndoFig(CFigure* F)
{
	Output* pOut = pManager->GetOutput();
	F->DeleteFi();//remove the movefd one
	F->Draw(pOut);//draw this figure by back ground color to delete
	pManager->rearrange(F);
	F->movefigure(ArrPoint[CountIn - 1].x, ArrPoint[CountIn - 1].y, pOut);//i save last point in arrpoint 
	F->ChngDrawClr(ArrColor[CountC - 1].DrawClr);//to make it take the last color
	F->ChngFillClr(ArrColor[CountC - 1].FillClr);

	CountC--;//decrease count
	CountIn--;//decrease count 
}
void Move::RedoFig(CFigure* F)
{
	if (CountC2 > 0)
	{
		Output* pOut = pManager->GetOutput();
		F->DeleteFi();//remove the movefd one
		F->Draw(pOut);//draw this figure by
		pManager->rearrange(F);
		F->movefigure(ArrPoint2[CountIn2 - 1].x, ArrPoint2[CountIn2 - 1].y, pOut);//i save last point in arrpoint 
		F->ChngDrawClr(ArrColor2[CountC2 - 1].DrawClr);//to make it take the last color
		F->ChngFillClr(ArrColor2[CountC2 - 1].FillClr);
		CountC2--;//decrease count
		CountIn2--;//decrease count 
	}
}
