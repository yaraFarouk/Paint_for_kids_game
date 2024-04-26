#include "ToRecord.h"
#include "Figures/CFigure.h"

#include "ApplicationManager.h"
#include"AddSquareAction.h"
#include "GUI/Input.h"
#include "GUI/Output.h"
ToRecord::ToRecord(ApplicationManager* pApp) :Action(pApp)
{
	for (int i = 0; i < MAX_ACTIONS; i++)//delete all saved actions to begin a new one
	{
		ActList[i].Actnx = NULL;
	}
	ActCount = 0;
	Actn = NULL;
	bool ispalycliked = false;
}
void ToRecord::ReadActionParameters()
{
	if (pManager->IsAnyFigureIsSelected())
	{
		pManager->UnSelectAll();
	}
}
void ToRecord::Execute()
{
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();

	// idea it begins after clicking it first delete the old list and creat new one then sent it to play class to play it
	if (pManager->isfigurelistempty())
	{
		pOut->PrintMessage("start recording");
		if (Actn != NULL)
		{
			if (ActCount < MAX_ACTIONS)
			{
				ActList[ActCount++].Actnx = Actn;
			}
			else
			{
				pOut->PrintMessage("can't record more.");
				pManager->seticclicked(false);
			}
		}
		pManager->seticclicked(true);
	}
	else
	{
		if (pManager->isclicked())
		{
			pOut->PrintMessage("recording");

			if (Actn != NULL)
			{
				if (ActCount < MAX_ACTIONS)
				{
					ActList[ActCount++].Actnx = Actn;
					//pOut->PrintMessage(to_string(pManager->GetRecordControl()->getActCount()));

				}
				else
				{
					pOut->PrintMessage("can't record more.");
				}
			}
		}
		else
		{
			pOut->PrintMessage("can't record, clear all first");
		}
	}
}
void ToRecord::AddAction(Action* ActTR)
{
	Actn = ActTR;
}
int ToRecord::getActCount()
{
	return ActCount;
}
/*CFigure* ToRecord::getfig(int i)
{
	return ActList[i].cf;
}
Action* ToRecord::getactionfromlist(int i)
{
	return ActList[i].Actnx;
}*/

void ToRecord::UndoFig(CFigure* F)
{

}
void ToRecord::RedoFig(CFigure* F)
{

}




