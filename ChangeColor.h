#pragma once
#ifndef ChangeColor_ACTION_H
#define ChangeColor_ACTION_H
#include"Actions/Action.h"
class ChangeColor :public Action
{
	Point p1;

public:
	ChangeColor(ApplicationManager* pApp);

	//Reads  parameters
	virtual void ReadActionParameters();


	virtual void Execute();//Execute change color action
	virtual void UndoFig(CFigure* F);
	virtual void RedoFig(CFigure* F1);//function for redo fig

};
#endif