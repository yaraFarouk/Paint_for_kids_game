#include "AddCircleAction.h"
#include "CCircle.h"
#include"Actions/Action.h"
#include "ApplicationManager.h"
#include"ToRecord.h"
#include "GUI\input.h"
#include "GUI\Output.h"

AddCircleAction::AddCircleAction(ApplicationManager* pApp) :Action(pApp)
{
	CountC = 0;//count for color undo
	CountIn = 0;//count for point undo
	CountC2 = 0;//count for color redo
	CountIn2 = 0;//count for point redo
}

void AddCircleAction::ReadActionParameters()
{
	if (pManager->IsAnyFigureIsSelected())
	{
		pManager->UnSelectAll();
	}
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	if (pManager->Getispclicked())//pManager->GetRecordControl()->GetPclicked())//note here if play is clicked not record
	{
		P1 = pManager->GetRecordControl()->GetActList()[pManager->GetPcount()].p;//error is here as it must start from 0 then increase to 1, here its start from 2
		P2 = pManager->GetRecordControl()->GetActList()[pManager->GetPcount()].p1;
		pManager->setPcount((pManager->GetPcount()) + 1);
	}
	else
	{
		pOut->PrintMessage("New Circle: Click at  center");

		//Read 1st corner and store in point P1
		pIn->GetPointClicked(P1.x, P1.y);

		pOut->PrintMessage("New Circle: Click at radius point");

		//Read 2nd corner and store in point P2
		pIn->GetPointClicked(P2.x, P2.y);
	}


	CircleGfxInfo.isFilled = false;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	CircleGfxInfo.DrawClr = pOut->getCrntDrawColor();
	CircleGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

//Execute the action
void AddCircleAction::Execute()
{
	//This action needs to read some parameters first
	// This action needs to read some parameters first
	Output* pOut = pManager->GetOutput();

	ReadActionParameters();
	pManager->AddAction(this);
	this->SetAct(true);
	//Create a circle with the parameters read from the user
	CCircle* R = new CCircle(P1, P2, CircleGfxInfo);
	pManager->IfNotUndo();
	//Add the circle to the list of figures
	pManager->AddFigure(R);
	pManager->AddFigForUndo(R);
	AddArrPoint(R->MakeCenter());//add point
	AddArrColor(R->GetColorIn());//add color
	if (pManager->Getispclicked())//pManager->GetRecordControl()->GetPclicked())//note here if play is clicked not record
	{
		pManager->setlastact(this);
		pManager->setlastfig(R);
	    pManager->getundoedactionandfig();
		pManager->getredoedactionandfig(this, R);
		pManager->GetRecordControl()->GetActList()[pManager->getredoinfo()].cfill = R->GetFillColor();
		pManager->GetRecordControl()->GetActList()[pManager->getredoinfo()].cdraw = R->GetDrawColor();
		pManager->setredoinfo((pManager->getredoinfo()) + 1);
	}
	if (pManager->isclicked())
	{
		pManager->GetRecordControl()->GetActList()[pManager->GetRecordControl()->getActCount()].p = P1;
		pManager->GetRecordControl()->GetActList()[pManager->GetRecordControl()->getActCount()].p1 = P2;
		Action* pAct = new AddCircleAction(pManager);
		pManager->GetRecordControl()->AddAction(pAct);
		pManager->GetRecordControl()->Execute();
	}
	
}void AddCircleAction::UndoFig(CFigure* F)
{
	pManager->UnSelectAll();
	F->DeleteFi();
	pManager->UpdateInterface();
	pManager->DeleteFigure(F);//to delete this figure
	F->SetIsDeleted(true);
	CountIn--;//to decrease count point
	CountC--;//to decrease count Color

}
void AddCircleAction::RedoFig(CFigure* F)
{
	if (CountC2 > 0) {
		pManager->UnSelectAll();
		F->ChngDrawClr(ArrColor2[CountC2 - 1].DrawClr);
		F->ChngFillClr(ArrColor2[CountC2 - 1].FillClr);
		pManager->AddFigure(F);//Add this figure after delete it because undo
		CountIn2--;//to decrease count point
		CountC2--;//to decrease count Color
	}

}
