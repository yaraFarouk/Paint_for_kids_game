#include"PlayRecord.h"
#include "Figures/CFigure.h"

#include "ApplicationManager.h"
#include<Windows.h> 
#include "GUI/Input.h"
#include "GUI/Output.h"


PlayRecord::PlayRecord(ApplicationManager* pApp) :Action(pApp)
{}
void PlayRecord::ReadActionParameters()
{
	if (pManager->IsAnyFigureIsSelected())
	{
		pManager->UnSelectAll();
	}
}
void PlayRecord::Execute()
{
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();
	if (pManager->GetRecordControl() != NULL)
	{
		if (pManager->isclicked())
		{
			pOut->PrintMessage("Please, stop recording first then play the record");
		}
		else
		{
			if (pManager->GetRecordControl()->getActCount() != 0)
			{
				pManager->setispclicked(true);
				pManager->ClearAll();
				pOut->ClearDrawArea();
				pOut->ClearStatusBar();
				pOut->CreateDrawToolBar();
				//pOut->PrintMessage("playing the record");
				for (int i = 0; i < pManager->GetRecordControl()->getActCount(); i++)
				{
					if (pManager->GetRecordControl()->GetActList()[i].Actnx != NULL)
					{
						pManager->GetRecordControl()->GetActList()[i].Actnx->Execute();
						Sleep(1000);
						pManager->UpdateInterface();
					}
				}
				pOut->PrintMessage("The End of the record");
				pManager->setispclicked(false);
				pManager->setPcount(0);
				pManager->setundocount(0);
				pManager->setredoinfo(0);
				pManager->setrr(0);

				//pManager->setrndocount(0);

				//pManager->setreundocnt(0);
			}
			else
			{
				pOut->PrintMessage("there is nothing to play");
			}
		}
	}
	else
	{
		pOut->PrintMessage("There is no recorded actions to play, Please record then play the record");
	}

}
void PlayRecord::UndoFig(CFigure* F)
{

}
void PlayRecord::RedoFig(CFigure* F)
{

}
