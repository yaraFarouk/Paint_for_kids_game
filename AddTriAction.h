#pragma once
#include "Actions/Action.h"

//Add Rectangle Action class
class AddTriAction : public Action
{
private:
	Point P1, P2, P3; //Rectangle Corners
	GfxInfo TriGfxInfo;
public:
	AddTriAction(ApplicationManager* pApp);

	//Reads rectangle parameters
	virtual void ReadActionParameters();

	//Add rectangle to the ApplicationManager
	virtual void Execute();
	virtual void UndoFig(CFigure* F);
	virtual void RedoFig(CFigure* F1);//function for redo fig

};
