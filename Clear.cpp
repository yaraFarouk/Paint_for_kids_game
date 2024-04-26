#include "Clear.h"
#include "Figures/CFigure.h"

#include "ApplicationManager.h"
#include"ToRecord.h"
#include "GUI/Input.h"
#include "GUI/Output.h"


Clear::Clear(ApplicationManager* pApp) :Action(pApp)
{}

void Clear::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();


}
void Clear::Execute()
{
	pManager->setlastact(this);

	Output* pOut = pManager->GetOutput();
	if (pManager->isclicked())
	{
		Action* pAct = new Clear(pManager);
		pManager->GetRecordControl()->AddAction(pAct);
		pManager->GetRecordControl()->Execute();
	}
	pOut->PrintMessage("Clear The Selected Figure");
	pOut->ClearDrawArea();
	pOut->ClearStatusBar();
	pManager->UnSelectAll();
	pOut->CreateDrawToolBar();
	pManager->ClearAll();
	//pManager->cleanfiglist();
}
void Clear::UndoFig(CFigure* F)
{

}
void Clear::RedoFig(CFigure* F)
{

}