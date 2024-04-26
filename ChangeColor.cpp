#include "ChangeColor.h"
#include"Actions/Action.h"
#include "ApplicationManager.h"
#include"ToRecord.h"

#include "GUI\input.h"
#include "GUI\Output.h"

ChangeColor::ChangeColor(ApplicationManager* pApp) :Action(pApp)
{
	CountC = 0;//count for color undo
	CountIn = 0;//count for point undo
	CountC2 = 0;//count for color redo
	CountIn2 = 0;
}

void ChangeColor::ReadActionParameters()
{

	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();


}

//Execute the action
void ChangeColor::Execute()
{
	this->SetAct(true);
	pManager->setlastact(this);

	ActionType ActType;
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	CFigure* ptr = pManager->GetTheSelected();//get the selected figure
	if (ptr != NULL)
	{
		pManager->AddFigForUndo(ptr);
		AddArrPoint(ptr->MakeCenter());
		AddArrColor(ptr->GetColorIn());

	}
	
	ActType = pManager->GetTheAlreadyAction();
	pManager->AddAction(this);
	
	if (pManager->isclicked())
	{
		pManager->GetRecordControl()->GetActList()[pManager->GetRecordControl()->getActCount()].ac = ActType;
		Action* pAct = new ChangeColor(pManager);
		pManager->GetRecordControl()->AddAction(pAct);
	}
	if (pManager->Getispclicked())//pManager->GetRecordControl()->GetPclicked())//note here if play is clicked not record
	{
		ActType = pManager->GetRecordControl()->GetActList()[pManager->GetPcount()].ac;//error is here as it must start from 0 then increase to 1, here its start from 2
	}



	
	if (ActType == C_FRAM)
	{
		pOut->PrintMessage("change color frame click on color");
		if (ptr != NULL)
		{
			if (pManager->Getispclicked())//pManager->GetRecordControl()->GetPclicked())//note here if play is clicked not record
			{
				ActType = pManager->GetRecordControl()->GetActList()[pManager->GetPcount()].ac1;//error is here as it must start from 0 then increase to 1, here its start from 2
				pManager->setPcount((pManager->GetPcount()) + 1);
			}
			else
			{
				ActType = pIn->GetUserAction();
			}

			if (pManager->Getispclicked())//pManager->GetRecordControl()->GetPclicked())//note here if play is clicked not record
			{
				pManager->setlastact(this);
				pManager->setlastfig(ptr);
				pManager->getundoedactionandfig();
				pManager->getredoedactionandfig(this, ptr);
			}
			if (pManager->isclicked())
			{
				pManager->GetRecordControl()->GetActList()[pManager->GetRecordControl()->getActCount()].ac1 = ActType;
				pManager->GetRecordControl()->Execute();
			}

			switch (ActType)
			{
			case C_RED:
			{
				pOut->PrintMessage("Change Color frame To Red ");
				ptr->ChngDrawClr(RED);//change frame color to red
			}
			break;
			case C_GREEN:
			{
				pOut->PrintMessage("Change frame Color To Green ");
				ptr->ChngDrawClr(GREEN);//change frame color to green
			}break;
			case C_YELLOW:
			{
				pOut->PrintMessage("Change frame Color To Yellow ");
				ptr->ChngDrawClr(YELLOW);//change frame color to yellow
			}break;
			case C_BLACK:
			{
				pOut->PrintMessage("Change frame Color To Black ");
				ptr->ChngDrawClr(BLACK);//change frame color to black
			}break;
			case C_BLUE:
			{
				pOut->PrintMessage("Change frame Color To blue ");
				ptr->ChngDrawClr(BLUE);//change frame color to blue
			}break;
			case C_ORANGE:
			{
				pOut->PrintMessage("Change frame Color To orange");
				ptr->ChngDrawClr(ORANGE);//change frame color to orange
			}break;

			default:
				pOut->PrintMessage("You don`t  select a Color");
				break;
			}
			if (pManager->Getispclicked())//pManager->GetRecordControl()->GetPclicked())//note here if play is clicked not record
			{
				pManager->GetRecordControl()->GetActList()[pManager->getredoinfo()].cfill = ptr->GetFillColor();
				pManager->GetRecordControl()->GetActList()[pManager->getredoinfo()].cdraw = ptr->GetDrawColor();
				pManager->setredoinfo((pManager->getredoinfo()) + 1);
			}
			pManager->UnSelectAll();
			pManager->IfNotUndo();


		}

	}
	else
	{
		if (ptr != NULL)
		{
			if (pManager->Getispclicked())//pManager->GetRecordControl()->GetPclicked())//note here if play is clicked not record
			{
				pManager->setPcount((pManager->GetPcount()) + 1);
			}
			if (pManager->Getispclicked())//pManager->GetRecordControl()->GetPclicked())//note here if play is clicked not record
			{
				pManager->setlastact(this);
				pManager->setlastfig(ptr);
				pManager->getundoedactionandfig();
				pManager->getredoedactionandfig(this, ptr);
				
			}
			if (pManager->isclicked())
			{
				pManager->GetRecordControl()->Execute();
			}
			switch (ActType)
			{
			case C_RED:
			{
				pOut->PrintMessage("Change Color To Red ");
				ptr->ChngFillClr(RED);//change color to red
			}
			break;
			case C_GREEN:
			{
				pOut->PrintMessage("Change Color To Green ");
				ptr->ChngFillClr(GREEN);//change color to green
			}break;
			case C_YELLOW:
			{
				pOut->PrintMessage("Change Color To Yellow ");
				ptr->ChngFillClr(YELLOW);//change color to yellow
			}break;
			case C_BLACK:
			{
				pOut->PrintMessage("Change Color To Black ");
				ptr->ChngFillClr(BLACK);//change color to black
			}break;
			case C_BLUE:
			{
				pOut->PrintMessage("Change Color To blue");
				ptr->ChngFillClr(BLUE);//change color to blue
			}break;
			case C_ORANGE:
			{
				pOut->PrintMessage("Change Color To orange ");
				ptr->ChngFillClr(ORANGE);//change color to orange
			}
			}
			if (pManager->Getispclicked())//pManager->GetRecordControl()->GetPclicked())//note here if play is clicked not record
			{
				pManager->GetRecordControl()->GetActList()[pManager->getredoinfo()].cfill = ptr->GetFillColor();
				pManager->GetRecordControl()->GetActList()[pManager->getredoinfo()].cdraw = ptr->GetDrawColor();
				pManager->setredoinfo((pManager->getredoinfo()) + 1);
			}
			pManager->UnSelectAll();
			pManager->IfNotUndo();

		}
	}

}
void ChangeColor::UndoFig(CFigure* F)
{
	pManager->UnSelectAll();
	F->ChngDrawClr(ArrColor[CountC - 1].DrawClr);//to make it color the color brfore change
	F->ChngFillClr(ArrColor[CountC - 1].FillClr);//to make it color the color brfore change
	CountC--;
	CountIn--;
}
void ChangeColor::RedoFig(CFigure* F)
{
	if (CountC2 > 0)
	{
		pManager->UnSelectAll();
		F->ChngDrawClr(ArrColor2[CountC2 - 1].DrawClr);//to make it color the color brfore change
		F->ChngFillClr(ArrColor2[CountC2 - 1].FillClr);//to make it color the color brfore change
		CountC2--;
		CountIn2--;
	}
}