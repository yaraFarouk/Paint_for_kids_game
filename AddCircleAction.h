#pragma once
#include "Actions/Action.h"

//Add Circle Action class
class AddCircleAction : public Action
{
private:
	Point P1, P2; //Circle Corners
	GfxInfo CircleGfxInfo;
public:
	AddCircleAction(ApplicationManager* pApp);

	//Reads circle parameters
	virtual void ReadActionParameters();

	//Add circle to the ApplicationManager
	virtual void Execute();
	virtual void UndoFig(CFigure* F);//functio to undo figure
	virtual void RedoFig(CFigure* F1);//function for redo fig
};
