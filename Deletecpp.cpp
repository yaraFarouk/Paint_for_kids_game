#include "Delete.h"
#include "Figures/CFigure.h"

#include "ApplicationManager.h"

#include "GUI/Input.h"
#include "GUI/Output.h"


Delete::Delete(ApplicationManager* pApp) :Action(pApp)
{}

void Delete::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();


}
void Delete::Execute()
{
	
	Output* pOut = pManager->GetOutput();

	pOut->PrintMessage("Delete The Selected Figure");
	CFigure* ptr = pManager->GetTheSelected();
	if (ptr != NULL)
	{
		ptr->ChngDrawClr(LIGHTGOLDENRODYELLOW);
		pManager->DeleteFigure();
		//pManager->UnSelectAll();
	}
}