#include"ApplicationManager.h"
#include"Actions/AddRectAction.h"
#include"AddSquareAction.h"
#include"AddTriAction.h"
#include"Figures/CFigure.h"
#include"AddCircleAction.h"
#include"AddHexaAction.h"
#include"ToSelect.h"
#include"Delete.h"
#include"Clear.h"
#include"ChangeColor.h"
#include"Move.h"
#include"saveaction.h"
#include"loadaction.h"
#include<fstream>
#include"CCircle.h"
#include"CHexa.h"
#include"CSquare.h"
#include"CTriangle.h"
#include"Figures/CRectangle.h"
#include"pickfigure.h"
#include"pickbycolor.h"
#include"pickbyfigandcolor.h"
#include"ToRecord.h"
#include"StopRecord.h"
#include"PlayRecord.h"
#include"SwitchToDraw.h"
#include"SwitchToPlay.h"
#include"Undo.h"
#include"Redo.h"
//Constructor
ApplicationManager::ApplicationManager()

{
	rr = 0;
	redoinfo = 0;
	reredocnt = 0;
	reundocnt = 0;
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	isclick = false;
	ispclicked = false;
	Pcount = 0;
	FigCount = 0;
	TR = NULL;
	CountF = 0;
	CountF2 = 0;//inslization CountF2=0
	CountA2 = 0;
	CountA = 0;
	//Create an array of figure pointers and set them to NULL		
	for (int i = 0; i < MaxFigCount; i++)
		FigList[i] = NULL;
	for (int j = 0; j < 5; j++)
		ArrActionUndo[j] = NULL;

	for (int i = 0; i < 5; i++)
		ArrFigUndo[i] = NULL;

	for (int j = 0; j < 5; j++)
		ArrActionRedo[j] = NULL;

	for (int i = 0; i < 5; i++)
		ArrFigRedo[i] = NULL;
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;
	CFigure* pFig = NULL;
	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
		case DRAW_RECT:
			pAct = new AddRectAction(this);
			SetTheLastAction(ActType);
			break;
		case DRAW_SQUARE:
			pAct = new AddSquareAction(this);
			SetTheLastAction(ActType);
			break;
		case DRAW_TRI:
			pAct = new AddTriAction(this);
			SetTheLastAction(ActType);
			break;
		case DRAW_CIRCLE:
			pAct = new AddCircleAction(this);
			SetTheLastAction(ActType);
			break;
		case DRAW_HEXA:
			pAct = new AddHexaAction(this);
			SetTheLastAction(ActType);
			break;
		case TO_PLAY:
			pAct = new SwitchToPlay(this);
			break;
		case TO_DRAW:
			pAct = new SwitchToDraw(this);
			break;
		case TO_UNDO:
			if (CountA > 0)
			{
				pAct = new Undo(this, ArrActionUndo[CountA - 1], ArrFigUndo[CountF - 1]);
				SetTheLastAction(ActType);
			}
			break;
		case TO_REDO:
			if (CountA2 > 0)
				pAct = new Redo(this, ArrActionRedo[CountA2 - 1], ArrFigRedo[CountF2 - 1]);
			break;
		case TO_SELECT:
			pAct = new ToSelect(this);
			break;
		case TO_START:
			pAct = new ToRecord(this);
			TR = (ToRecord*)pAct;
			//isclick = TR->getper();//note if it doesnt work then make a pointer of to record instead pf act then execute it here
			break;
		case TO_STOP:
			pAct = new StopRecord(this);
			break;
		case TO_PLAY_RECORD:
			pAct = new PlayRecord(this);
			SetTheLastAction(ActType);

			break;
		case EXIT:
			break;///create ExitAction here
		case C_FRAM:
			pAct = new ChangeColor(this);
			SetTheLastAction(ActType);
			break;

		case C_RED:
			pAct = new ChangeColor(this);
			SetTheLastAction(ActType);

			break;
		case C_YELLOW:
			pAct = new ChangeColor(this);
			SetTheLastAction(ActType);

			break;
		case C_GREEN:
			pAct = new ChangeColor(this);
			SetTheLastAction(ActType);

			break;
		case C_BLUE:
			pAct = new ChangeColor(this);
			SetTheLastAction(ActType);

			break;
		case C_BLACK:
			pAct = new ChangeColor(this);
			SetTheLastAction(ActType);

			break;
		case C_ORANGE:
			pAct = new ChangeColor(this);
			SetTheLastAction(ActType);

			break;
		case TO_CLEAN:
			pAct = new Clear(this);
			 break;
		case DRAWING_AREA:
			UnSelectAll();
			break;
		case TO_DELETE:
			pAct = new Delete(this);
			SetTheLastAction(ActType);

			break;
		case TO_MOVE:
			SetTheLastAction(ActType);
			pAct = new Move(this);
			break;
		case TO_SAVE:
			pAct = new saveaction(this,FigCount);
			break;
		case TO_LOAD:
		pAct = new loadaction(this);
		 break;
		case TO_PICK:
			pAct = new pickfigure(this,FigCount);
			break;

		case TO_PICK_COLOR:
			pAct = new pickbycolor(this,FigCount);
			break;
		case TO_PICK_COLORED_FIGURE:
			pAct = new pickbyfigandcolor(this,FigCount);
			break;
		case STATUS:	//a click on the status bar ==> no action
			return;
	}
	
	//Execute the created action
	if (pAct != NULL)
	{
		pAct->Execute();//Execute
		if (!pAct->getAct()&& ActType != TO_START)
		{
			if (pAct != NULL)
				delete pAct;	//You may need to change this line depending to your implementation
		}
		pAct = NULL;
	}
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	   if(FigCount < MaxFigCount )
		FigList[FigCount++] = pFig;	
}

////////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(int x, int y) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL
	for (int i = FigCount - 1; i >= 0; i--)
		if (FigList[i]->IsInside(x, y))
		{
			FigList[i]->printtypeoffigureselected(pOut);
			return FigList[i];
		}

	//Add your code here to search for a figure given a point x,y	
	//Remember that ApplicationManager only calls functions do NOT implement it.

	return NULL;
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{	
	for(int i=0; i<FigCount; i++)
		if(FigList[i]!=NULL)//&&FigList[i]->GetDrawColor()!=UI.BkGrndColor)
		FigList[i]->Draw(pOut);		//Call Draw function (virtual member fn)
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for (int i = 0; i < FigCount; i++)
		delete FigList[i];//to delete FigList
	delete pIn;
	delete pOut;
	for (int i = 0; i < CountA; i++)
	{
		if (ArrActionUndo[i] != NULL)
		{
			delete ArrActionUndo[i];//to delete ArrActionUndo
			ArrActionUndo[i] = NULL;
		}
	}
	for (int i = 0; i < CountF; i++)
	{
		ArrFigUndo[i] = NULL;//to make it NULL
	}
	for (int i = 0; i < CountA2; i++)
	{
		if (ArrActionRedo[i] != NULL)
		{
			delete ArrActionRedo[i]; // to delete ArrActionRedo
			ArrActionRedo[i] = NULL;
		}
	}
	for (int i = 0; i < CountF2; i++)
	{
		ArrFigRedo[i] = NULL;
	}
	
	
}
void ApplicationManager::UnSelectAll()
{
	for (int i = FigCount - 1; i >= 0; i--)
		FigList[i]->SetSelected(false);
}
bool ApplicationManager::IsAnyFigureIsSelected()
{
	for (int i = 0; i < FigCount; i++)
		if (FigList[i]->IsSelected())
			return true;
	return false;
}
CFigure* ApplicationManager:: GetTheSelected()
{//return the selected figure
	
		for (int i = 0; i < FigCount; i++)
			if (FigList[i]->IsSelected())
				return FigList[i];
	
	return NULL;

}
void ApplicationManager::ClearAll()
{
	if (FigCount >= 0)
	{
		for (int i = 0; i < FigCount; i++)
		{
			if (FigList[i] != NULL && GetTheAlreadyAction() != TO_PLAY_RECORD)
			{
				delete FigList[i];
				FigList[i] = NULL;
			}
			else
				FigList[i] = NULL;


		}//Make All Figure NULL To Delete Figures
		for (int i = 0; i < CountA; i++)
		{
			if (ArrActionUndo[i] != NULL)
			{
				delete ArrActionUndo[i];
				ArrActionUndo[i] = NULL;
				ArrFigUndo[i] = NULL;

			}


		}//Make All Figure NULL To Delete Figures
		for (int i = 0; i < CountA2; i++)
		{
			if (ArrActionRedo[i] != NULL)
			{
				delete ArrActionRedo[i];
				ArrActionRedo[i] = NULL;
				ArrFigRedo[i] = NULL;
			}

		}//Make All Figure NULL To Delete Figures

		FigCount = 0;
		CountA = 0;
		CountA2 = 0;
		CountF = 0;
		CountF2 = 0;
	}

}
ActionType  ApplicationManager::GetTheAlreadyAction()
{
	return A;//get the  last action
}
void  ApplicationManager::SetTheLastAction(ActionType Act)
{
	A = Act;//put the last action
}
void ApplicationManager::DeleteFigure(CFigure* ptr)
{
//	pOut->PrintMessage("he");
	for (int i = 0; i < FigCount; i++)
		if (FigList[i] == ptr)
		{
			//pOut->PrintMessage("he;;o");
			for (int j = i; j < FigCount - 1; j++)
			{
				FigList[j] = FigList[j + 1];
			}
			FigCount--;
			FigList[FigCount] = NULL;
			break;
		}
	//pOut->PrintMessage(to_string(FigCount));
}
void ApplicationManager::rearrange(CFigure* ptr)
{
	for (int i = 0; i < FigCount; i++)
		if (FigList[i] == ptr)
		{
			CFigure* ptrx = FigList[i];
			FigList[i] = FigList[FigCount-1];
			FigList[FigCount-1] = ptrx;
		}
}

void ApplicationManager::SaveAll(ofstream& OutFile)
{

	for (int i = 0; i < FigCount; i++)
	{
		FigList[i]->Save(OutFile);
		OutFile << endl;
	}
}

bool ApplicationManager::isfigurelistempty()
{
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i] != NULL)
		{
			return false;
		}
	}
	return true;
}
bool ApplicationManager::isclicked()
{
	return isclick;
}
void ApplicationManager::seticclicked(bool a)
{
	isclick = a;
}
bool ApplicationManager::Getispclicked()
{
	return ispclicked;
}
void ApplicationManager::setispclicked(bool a)
{
	ispclicked = a;
}
int ApplicationManager::GetPcount()
{
	return Pcount;
}
void ApplicationManager::setPcount(int a)
{
	Pcount = a;
}
ToRecord* ApplicationManager::GetRecordControl()
{
	return TR;
}
void ApplicationManager::AddFigForUndo(CFigure* fi)//function to put figure in arr for undo
{
	if (CountF < 5)
	{
		ArrFigUndo[CountF] = fi;
		CountF++;
	}
	else
	{
		if (ArrFigUndo[0] != NULL && ArrFigUndo[0]->GetIsDeleted())
		{
			delete ArrFigUndo[0];//because to deleted the daynamic figure
		}
		for (int i = 0; i < CountF - 1; i++)
		{
			ArrFigUndo[i] = ArrFigUndo[i + 1];
		}
		CountF = CountF - 1;
		ArrFigUndo[CountF] = fi;
		CountF++;
	}
}
void ApplicationManager::AddFigForRedo(CFigure* fi)//function to put figure in arrFigRedo
{
	if (CountF2 < 5)
	{
		ArrFigRedo[CountF2] = fi;
		CountF2++;
	}
	else
	{
		if (ArrFigRedo[0] != NULL && ArrFigRedo[0]->GetIsDeleted())
		{
			delete ArrFigRedo[0]; //because to deleted the daynamic figure
		}
		for (int i = 0; i < CountF2 - 1; i++)
		{
			ArrFigRedo[i] = ArrFigRedo[i + 1];
		}
		CountF2 = CountF2 - 1;
		ArrFigRedo[CountF2] = fi;
		CountF2++;
	}
}
void ApplicationManager::AddAction(Action* A)//function to put action in arr
{
	if (CountA < 5)
	{
		ArrActionUndo[CountA++] = A;
	}
	else
	{
		delete ArrActionUndo[0];
		for (int i = 0; i < CountA - 1; i++)
		{
			ArrActionUndo[i] = ArrActionUndo[i + 1];

		}
		ArrActionUndo[CountA - 1] = A;

	}
}

void ApplicationManager::AddActionRedo(Action* A)//function to put action in arr for redo
{
	if (CountA2 < 5)
	{
		ArrActionRedo[CountA2++] = A;
	}
	else
	{
		delete ArrActionRedo[0];
		for (int i = 0; i < CountA2 - 1; i++)
		{
			ArrActionRedo[i] = ArrActionRedo[i + 1];

		}
		ArrActionRedo[CountA2 - 1] = A;

	}
}
void ApplicationManager::DeleteAction()
{
	if (CountA > 0)
	{
		ArrFigUndo[CountF - 1] = NULL;
		ArrActionUndo[CountA - 1] = NULL;
		CountA--;
		CountF--;
	}
}
void ApplicationManager::DeleteActionRedo()
{
	if (CountA2 > 0)
	{//remove this action from array after make redo
		ArrFigRedo[CountF2 - 1] = NULL;
		ArrActionRedo[CountA2 - 1] = NULL;
		CountA2--;
		CountF2--;
	}
}
void ApplicationManager::CallLoad()
{
	loadaction load(this);
	load.loadplaymodefigs();
}

void ApplicationManager::CallSave()
{
	saveaction save(this,FigCount);
	save.saveplaymodefigs();
}
void ApplicationManager::cleanfiglist()
{
	for (int i = 0; i < FigCount; ++i)
		FigList[i] = NULL;
	FigCount = 0;
}
void ApplicationManager::setlastact(Action* acr)
{
	LAAct = acr;
}
Action* ApplicationManager::getlastact()
{
	return LAAct;
}
void ApplicationManager::getundoedactionandfig()
{
	TR->GetActList()[reundocnt].ActTosnd = LAAct;
	TR->GetActList()[reundocnt].cf = ftg;
	reundocnt++;
}
void ApplicationManager::setlastfig(CFigure* acr)
{
	ftg = acr;
}
CFigure* ApplicationManager::getlastfig()
{
	return ftg;
}
int ApplicationManager::getundocount()
{
	return reundocnt;
}
void ApplicationManager::setundocount(int a)
{
	reundocnt = a;
}
void ApplicationManager::getredoedactionandfig(Action* ttr,CFigure* cgg)
{
	TR->GetActList()[reredocnt].Actnxtoredo = ttr;
	TR->GetActList()[reredocnt].cftoredo = cgg;
	reredocnt++;
}
//int ApplicationManager::getrndocount()
//{
//	return reredocnt;
//}
//void ApplicationManager::setrndocount(int a)
//{
//	reredocnt = a;
//}
void ApplicationManager::IfNotUndo()
{
	for (int i = 0; i < CountA2; i++)
	{
		if (ArrActionRedo[i] != NULL&&ArrFigRedo[i]!=NULL)
		{
			delete ArrActionRedo[i];
			if (ArrFigRedo[i]->GetIsDeleted())
			{
				delete ArrFigRedo[i];
			}
			ArrActionRedo[i] = NULL;
			ArrFigRedo[i] = NULL;

		}

	}//Make All Figure NULL To Delete Figures
	CountA2 = 0;
	CountF2 = 0;
}

int ApplicationManager::figuretype(int i)
{

	return FigList[i]->figuretype();

}

color ApplicationManager::figurecolor(int i)
{
	return FigList[i]->GetFillColor();
}

