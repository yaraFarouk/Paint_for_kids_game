#pragma once
#include"Actions/Action.h"
//Add SQuare Action class
class AddSquareAction : public Action
{
private:
	Point P1; //square center
	GfxInfo SquareGfxInfo;
public:
	AddSquareAction(ApplicationManager* pApp);

	//Reads rectangle parameters
	virtual void ReadActionParameters();

	//Add rectangle to the ApplicationManager
	virtual void Execute();
	virtual void UndoFig(CFigure* F);
	virtual void RedoFig(CFigure* F1);//function for redo fig

};

