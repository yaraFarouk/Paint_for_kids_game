#include "AddHexaAction.h"
#include "CHexa.h"
#include"Actions/Action.h"
#include "ApplicationManager.h"
#include"ToRecord.h"
#include "GUI\input.h"
#include "GUI\Output.h"

AddHexaAction::AddHexaAction(ApplicationManager* pApp) :Action(pApp)
{
	CountC = 0;//count for color undo
	CountIn = 0;//count for point undo
	CountC2 = 0;//count for color redo
	CountIn2 = 0;
}
void AddHexaAction::ReadActionParameters()

{
	if (pManager->IsAnyFigureIsSelected())
	{
		pManager->UnSelectAll();
	}
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Hexa: Click at  center");

	if (pManager->Getispclicked())//pManager->GetRecordControl()->GetPclicked())//note here if play is clicked not record
	{
		P1 = pManager->GetRecordControl()->GetActList()[pManager->GetPcount()].p;//error is here as it must start from 0 then increase to 1, here its start from 2
		pManager->setPcount((pManager->GetPcount()) + 1);

	}
	else
	{
		pIn->GetPointClicked(P1.x, P1.y);
	}
	HexaGfxInfo.isFilled = false;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	HexaGfxInfo.DrawClr = pOut->getCrntDrawColor();
	HexaGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

//Execute the action
void AddHexaAction::Execute()
{
	Output* pOut = pManager->GetOutput();

	//This action needs to read some parameters first
	ReadActionParameters();
	pManager->AddAction(this);
	this->SetAct(true);
	
	//Create a circle with the parameters read from the user
	CHexa* R = new CHexa(P1, HexaGfxInfo);
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
		Action* pAct = new AddHexaAction(pManager);
		pManager->GetRecordControl()->AddAction(pAct);
		pManager->GetRecordControl()->Execute();
	}
	
	//Add the circle to the list of figures
	//pManager->AddFigure(R);
	AddArrPoint(R->MakeCenter());//add point
	AddArrColor(R->GetColorIn());//add color
	pManager->AddFigForUndo(R);
	//Add the circle to the list of figures
	pManager->AddFigure(R);
}
void AddHexaAction::UndoFig(CFigure* F)
{
	pManager->UnSelectAll();
	F->DeleteFi();
	pManager->UpdateInterface();
	pManager->DeleteFigure(F);//to delete this figure
	F->SetIsDeleted(true);

	CountIn--;//to decrease count point
	CountC--;//to decrease count Color

}
void AddHexaAction::RedoFig(CFigure* F)
{
	pManager->UnSelectAll();
	if (CountC2 > 0) {
		F->ChngDrawClr(ArrColor2[CountC2 - 1].DrawClr);
		F->ChngFillClr(ArrColor2[CountC2 - 1].FillClr);
		pManager->AddFigure(F);//Add this figure after delete it because undo
		CountIn2--;//to decrease count point
		CountC2--;//to decrease count Color
	}
}
