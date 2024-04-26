#pragma once
#include"Actions/Action.h"
#include"Figures/CFigure.h"

class ToSelect : public Action
{
	Point p1;
public:

	ToSelect(ApplicationManager* pApp);

	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();
	virtual void UndoFig(CFigure* F);
	virtual void RedoFig(CFigure* F1);//function for redo fig

};