#include "AddSquareAction.h"
#include "CSquare.h"
#include<Windows.h>
#include "ApplicationManager.h"
#include"ToRecord.h"
#include "GUI/Input.h"
#include "GUI/Output.h"

AddSquareAction::AddSquareAction(ApplicationManager* pApp) :Action(pApp)
{
	CountC = 0;//count for color undo
	CountIn = 0;//count for point undo
	CountC2 = 0;//count for color redo
	CountIn2 = 0;
}

void AddSquareAction::ReadActionParameters()
{
	if (pManager->IsAnyFigureIsSelected())
	{
		pManager->UnSelectAll();
	}
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Square: Click at the center"); // +to_string(a));

	//Read 1st corner and store in point P1
	if (pManager->Getispclicked())//pManager->GetRecordControl()->GetPclicked())//note here if play is clicked not record
	{
		P1 = pManager->GetRecordControl()->GetActList()[pManager->GetPcount()].p;//error is here as it must start from 0 then increase to 1, here its start from 2
		pManager->setPcount((pManager->GetPcount()) + 1);
	}
	else
	{
		pIn->GetPointClicked(P1.x, P1.y);
	}
	SquareGfxInfo.isFilled = false;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	SquareGfxInfo.DrawClr = pOut->getCrntDrawColor();
	SquareGfxInfo.FillClr = pOut->getCrntFillColor();
	pOut->ClearStatusBar();
}

//Execute the action
void AddSquareAction::Execute()
{
	//This action needs to read some parameters first
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	pManager->AddAction(this);
	this->SetAct(true);
	CSquare* R = new CSquare(P1, SquareGfxInfo);
	pManager->IfNotUndo();

	//pManager->setlastfig(R);

	if (pManager->Getispclicked())//pManager->GetRecordControl()->GetPclicked())//note here if play is clicked not record
	{
		pManager->setlastact(this);
		pManager->setlastfig(R);
		pManager->getundoedactionandfig();
		pManager->getredoedactionandfig(this,R);
		pManager->GetRecordControl()->GetActList()[pManager->getredoinfo()].cfill = R->GetFillColor();
		pManager->GetRecordControl()->GetActList()[pManager->getredoinfo()].cdraw = R->GetDrawColor();
		pManager->setredoinfo((pManager->getredoinfo()) + 1);
	}
	if (pManager->isclicked())
	{
		pManager->GetRecordControl()->GetActList()[pManager->GetRecordControl()->getActCount()].p = P1;
		Action* pAct = new AddSquareAction(pManager);
		pManager->GetRecordControl()->AddAction(pAct);
		pManager->GetRecordControl()->Execute();
	}

	//Create a rectangle with the parameters read from the user
	//Add the rectangle to the list of figures
	pManager->AddFigure(R);
	AddArrPoint(R->MakeCenter());//add point
	AddArrColor(R->GetColorIn());//add color
	pManager->AddFigForUndo(R);
}
void AddSquareAction::UndoFig(CFigure* F)
{
	pManager->UnSelectAll();
	F->DeleteFi();
	pManager->UpdateInterface();
	pManager->DeleteFigure(F);//to delete this figure
	F->SetIsDeleted(true);

	CountIn--;//to decrease count point
	CountC--;//to decrease count Color

}
void AddSquareAction::RedoFig(CFigure* F)
{
	if (CountC2 > 0)
	{
		pManager->UnSelectAll();
		F->ChngDrawClr(ArrColor2[CountC2 - 1].DrawClr);
		F->ChngFillClr(ArrColor2[CountC2 - 1].FillClr);
		pManager->AddFigure(F);//Add this figure after delete it because undo
		CountIn2--;//to decrease count point
		CountC2--;//to decrease count Color
	}
}