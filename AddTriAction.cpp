#include "AddTriAction.h"
#include "CTriangle.h"

#include "ApplicationManager.h"
#include"ToRecord.h"
#include "GUI/Input.h"
#include "GUI/Output.h"

AddTriAction::AddTriAction(ApplicationManager* pApp) :Action(pApp)
{
	CountC = 0;//count for color undo
	CountIn = 0;//count for point undo
	CountC2 = 0;//count for color redo
	CountIn2 = 0;
}

void AddTriAction::ReadActionParameters()
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
		P3 = pManager->GetRecordControl()->GetActList()[pManager->GetPcount()].p2;
		pManager->setPcount((pManager->GetPcount()) + 1);
	}
	else
	{
		pOut->PrintMessage("New Triangle: Click at first corner");

		//Read 1st corner and store in point P1
		pIn->GetPointClicked(P1.x, P1.y);

		pOut->PrintMessage("New Triangle: Click at second corner");

		//Read 2nd corner and store in point P2
		pIn->GetPointClicked(P2.x, P2.y);

		//Read 3rd corner and store in point P3
		pOut->PrintMessage("New Triangle: Click at third corner");

		pIn->GetPointClicked(P3.x, P3.y);
	}


	TriGfxInfo.isFilled = false;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	TriGfxInfo.DrawClr = pOut->getCrntDrawColor();
	TriGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

//Execute the action
void AddTriAction::Execute()
{
	Output* pOut = pManager->GetOutput();

	//This action needs to read some parameters first
	ReadActionParameters();
	pManager->AddAction(this);
	this->SetAct(true);
	CTriangle* R = new CTriangle(P1, P2, P3, TriGfxInfo);
	pManager->IfNotUndo();

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
		pManager->GetRecordControl()->GetActList()[pManager->GetRecordControl()->getActCount()].p2 = P3;
		Action* pAct = new AddTriAction(pManager);
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
void AddTriAction::UndoFig(CFigure* F)
{
	pManager->UnSelectAll();
	F->DeleteFi();
	F->SetIsDeleted(true);

	pManager->UpdateInterface();
	pManager->DeleteFigure(F);//to delete this figure
	CountC--;//to decrease count Color

}
void AddTriAction::RedoFig(CFigure* F)
{
	pManager->UnSelectAll();
	if (CountC2 > 0)
	{
		F->ChngDrawClr(ArrColor2[CountC2 - 1].DrawClr);
		F->ChngFillClr(ArrColor2[CountC2 - 1].FillClr);
		pManager->AddFigure(F);//Add this figure after delete it because undo
		CountIn2--;//to decrease count point
		CountC2--;//to decrease count Color
	}

}